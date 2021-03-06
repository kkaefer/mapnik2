/*****************************************************************************
 * 
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2007 Artem Pavlenko
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
//$Id$

#ifndef SQLITE_FEATURESET_HPP
#define SQLITE_FEATURESET_HPP

// mapnik
#include <mapnik/datasource.hpp>
#include <mapnik/unicode.hpp> 
#include <mapnik/wkb.hpp> 

// boost
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

// sqlite
#include "sqlite_types.hpp"
  
  
class sqlite_featureset : public mapnik::Featureset
{
   public:
      sqlite_featureset(boost::shared_ptr<sqlite_resultset> rs,
                        std::string const& encoding,
                        mapnik::wkbFormat format,
                        bool multiple_geometries,
                        bool using_subquery);
      virtual ~sqlite_featureset();
      mapnik::feature_ptr next();
   private:
      boost::shared_ptr<sqlite_resultset> rs_;
      boost::scoped_ptr<mapnik::transcoder> tr_;
      mapnik::wkbFormat format_;
      bool multiple_geometries_;
      bool using_subquery_;
};

#endif // SQLITE_FEATURESET_HPP
