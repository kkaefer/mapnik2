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

#include <map>
#include <string>
#include "ctrans.hpp"
#include "params.hpp"
#include "feature.hpp"
#include "query.hpp"
#include "feature_layer_desc.hpp"

#include <boost/shared_ptr.hpp>

namespace mapnik
{    
    typedef MAPNIK_DECL shared_ptr<Feature> feature_ptr;
    struct MAPNIK_DECL Featureset
    {
        virtual feature_ptr next()=0;
        virtual ~Featureset() {};
    };
    
    typedef shared_ptr<Featureset> featureset_ptr;    
    class MAPNIK_DECL datasource_exception : public std::exception
    {
    private:
        const std::string message_;
    public:
	datasource_exception(const std::string& message=std::string())
	    :message_(message) {}

	~datasource_exception() throw() {}
	virtual const char* what() const throw()
	{
	    return message_.c_str();
	}
    };
    
    class MAPNIK_DECL datasource
    {
    public:
	enum {
	    Vector,
	    Raster
	};
	virtual int type() const=0;
	virtual featureset_ptr features(const query& q) const=0;
	virtual Envelope<double> const& envelope() const=0;
	virtual layer_descriptor const& get_descriptor() const=0;
	virtual ~datasource() {};
    };
    
    typedef std::string datasource_name();
    typedef datasource* create_ds(const parameters& params);
    typedef void destroy_ds(datasource *ds);

    
    class datasource_deleter
    {
    public:
	void operator() (datasource* ds)
	{
	    delete ds;
	}
    };

    typedef boost::shared_ptr<datasource> datasource_p;
    
    ///////////////////////////////////////////
    #define DATASOURCE_PLUGIN(classname) \
        extern "C" MAPNIK_DECL std::string datasource_name() \
        { \
        return classname::name();\
        }\
        extern "C"  MAPNIK_DECL datasource* create(const parameters &params)	\
        { \
	    return new classname(params);	\
        }\
        extern "C" MAPNIK_DECL void destroy(datasource *ds) \
        { \
        delete ds;\
        }\
        ///////////////////////////////////////////
}
#endif                                            //DATASOURCE_HPP
