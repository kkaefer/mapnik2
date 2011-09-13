/*****************************************************************************
 * 
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2006 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

//$Id: datasource.hpp 43 2005-04-22 18:52:47Z pavlenko $

#ifndef DATASOURCE_HPP
#define DATASOURCE_HPP
// mapnik
#include <mapnik/config.hpp>
#include <mapnik/ctrans.hpp>
#include <mapnik/params.hpp>
#include <mapnik/feature.hpp>
#include <mapnik/query.hpp>
#include <mapnik/feature_layer_desc.hpp>

// boost
#include <boost/utility.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/threadpool.hpp>

// stl
#include <map>
#include <string>

namespace mapnik {
   
typedef MAPNIK_DECL boost::shared_ptr<Feature> feature_ptr;
    
struct MAPNIK_DECL Featureset
{
    virtual feature_ptr next()=0;
    virtual ~Featureset() {};
};
    
typedef MAPNIK_DECL boost::shared_ptr<Featureset> featureset_ptr;
    
class MAPNIK_DECL datasource_exception : public std::exception
{
private:
    std::string message_;
public:
    datasource_exception(const std::string& message=std::string("no reason"))
        :message_(message) {}

    ~datasource_exception() throw() {}
    virtual const char* what() const throw()
    {
        return message_.c_str();
    }
};

class datasource;
typedef boost::shared_ptr<datasource> datasource_ptr;
class MAPNIK_DECL datasource : private boost::noncopyable
{
public:        
    enum datasource_t {
        Vector,
        Raster
    };

    class MAPNIK_DECL retrieval : private boost::noncopyable {
    public:
        retrieval(datasource_ptr ds, query_ptr q) : datasource_(ds), query_(q) {
            mutex_.lock();
            pool().schedule(boost::bind(&retrieval::retrieve, this));
        }

        featureset_ptr features() {
            boost::mutex::scoped_lock lock(mutex_);
            return features_;
        }

        datasource_ptr datasource() {
            return datasource_;
        }

        query_ptr query() {
            return query_;
        }

    private:
        void retrieve() {
            try {
                features_ = datasource_->features(*query_);
            }
            catch (const mapnik::datasource_exception& ex) {
                std::clog << "Datasource exception in retrieval thread: " << ex.what() << "\n";
            }
            catch (const std::exception& ex) {
                std::clog << "Exception in retrieval thread: " << ex.what() << "\n";
            }
            catch (...) {
                std::clog << "Exception in retrieval thread\n";
            }

            mutex_.unlock();
        }

        static boost::threadpool::pool& pool() {
            static boost::threadpool::pool pool(25);
            return pool;
        }

    private:
        datasource_ptr datasource_;
        query_ptr query_;
        featureset_ptr features_;
        mutable boost::mutex mutex_;
    };
    typedef boost::shared_ptr<retrieval> retrieval_ptr;

    datasource (parameters const& params)
        : params_(params),
          is_bound_(false)
        {}
    
    /*!
     * @brief Get the configuration parameters of the data source.
     *
     * These vary depending on the type of data source.
     *
     * @return The configuration parameters of the data source.
     */
    parameters const& params() const
    {
        return params_;
    }
        
    /*!
     * @brief Get the type of the datasource
     * @return The type of the datasource (Vector or Raster)
     */
    virtual int type() const=0;
        
    /*!
     * @brief Connect to the datasource
     */
    virtual void bind() const {};
    
    virtual featureset_ptr features(const query& q) const=0;
    virtual featureset_ptr features_at_point(coord2d const& pt) const=0;
    virtual box2d<double> envelope() const=0;
    virtual layer_descriptor get_descriptor() const=0;
    virtual ~datasource() {};
protected:
    parameters params_;
    mutable bool is_bound_;
};
    
typedef std::string datasource_name();
typedef datasource* create_ds(const parameters& params, bool bind);
typedef void destroy_ds(datasource *ds);

    
class datasource_deleter
{
public:
    void operator() (datasource* ds)
    {
        delete ds;
    }
};


#define DATASOURCE_PLUGIN(classname)                                    \
    extern "C" MAPNIK_EXP std::string datasource_name()                 \
    {                                                                   \
        return classname::name();                                       \
    }                                                                   \
    extern "C"  MAPNIK_EXP datasource* create(const parameters &params, bool bind) \
    {                                                                   \
        return new classname(params, bind);                             \
    }                                                                   \
    extern "C" MAPNIK_EXP void destroy(datasource *ds)                  \
    {                                                                   \
        delete ds;                                                      \
    }                                                                   \
    //
}

#endif //DATASOURCE_HPP
