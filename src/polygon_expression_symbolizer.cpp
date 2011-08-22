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

// mapnik
#include <mapnik/polygon_expression_symbolizer.hpp>

namespace mapnik
{

const double polygon_expression_symbolizer::default_opacity_ = 1.0;
const double polygon_expression_symbolizer::default_gamma_ = 1.0;

polygon_expression_symbolizer::polygon_expression_symbolizer()
    : expression_symbolizer_base(),
    fill_(color(128,128,128)),
    opacity_(expression_ptr_empty),
    gamma_(expression_ptr_empty) {}

polygon_expression_symbolizer::polygon_expression_symbolizer(color const& fill)
    : expression_symbolizer_base(),
    fill_(fill),
    opacity_(expression_ptr_empty),
    gamma_(expression_ptr_empty) {}

color const& polygon_expression_symbolizer::get_fill() const
{
    return fill_;
}

void polygon_expression_symbolizer::set_fill(color const& fill)
{
    fill_ = fill;
}

void polygon_expression_symbolizer::set_opacity(expression_ptr opacity)
{
    opacity_ = opacity;
}

expression_ptr polygon_expression_symbolizer::get_opacity() const
{
    return opacity_;
}

double polygon_expression_symbolizer::get_opacity(Feature const& feature) const
{
    return std::max(0.0, std::min(1.0, to_double(opacity_, feature, default_opacity_)));
}

void polygon_expression_symbolizer::set_gamma(expression_ptr gamma)
{
    gamma_ = gamma;
}

expression_ptr polygon_expression_symbolizer::get_gamma() const
{
    return gamma_;
}

double polygon_expression_symbolizer::get_gamma(Feature const& feature) const
{
    return to_double(gamma_, feature, default_gamma_);
}

} // namespace mapnik
