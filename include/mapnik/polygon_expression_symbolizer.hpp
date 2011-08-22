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

//$Id$

#ifndef POLYGON_EXPRESSION_SYMBOLIZER_HPP
#define POLYGON_EXPRESSION_SYMBOLIZER_HPP

// mapnik
#include <mapnik/color.hpp>
#include <mapnik/expression_symbolizer.hpp>

namespace mapnik
{
struct MAPNIK_DECL polygon_expression_symbolizer : public expression_symbolizer_base
{
    explicit polygon_expression_symbolizer();
    polygon_expression_symbolizer(color const& fill);

    color const& get_fill() const;
    void set_fill(color const& fill);

    expression_ptr get_opacity() const;
    void set_opacity(expression_ptr opacity);
    double get_opacity(Feature const& feature) const;

    expression_ptr get_gamma() const;
    void set_gamma(expression_ptr gamma);
    double get_gamma(Feature const& feature) const;

private:
    color fill_;
    expression_ptr opacity_;
    expression_ptr gamma_;

    // Default values
    static const double default_opacity_;
    static const double default_gamma_;
};

}

#endif // POLYGON_EXPRESSION_SYMBOLIZER_HPP
