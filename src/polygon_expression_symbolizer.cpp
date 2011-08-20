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

expression_ptr expression_ptr_empty;

polygon_expression_symbolizer::polygon_expression_symbolizer()
    : expression_symbolizer_base(),
    fill_(color(128,128,128)),
    opacity_(expression_ptr_empty),
    gamma_(default_gamma_) {}

polygon_expression_symbolizer::polygon_expression_symbolizer(color const& fill)
    : expression_symbolizer_base(),
    fill_(fill),
    opacity_(expression_ptr_empty),
    gamma_(default_gamma_) {}

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
    fprintf(stderr, "setting filter %s\n", to_expression_string(*opacity).c_str());
    opacity_ = opacity;
}

expression_ptr polygon_expression_symbolizer::get_opacity() const
{
    return opacity_;
}

double polygon_expression_symbolizer::get_opacity(Feature const& feature) const
{
    if (opacity_ == expression_ptr_empty)
    {
        fprintf(stderr, "Returning default opacity\n");
        return default_opacity_;
    }
    else
    {
        // std::cout << feature;
        value_type result = boost::apply_visitor(evaluate<Feature, value_type>(feature), *opacity_);
        fprintf(stderr, "Returning opacity: %f\n", result.to_double());
        return std::max(0.0, std::min(1.0, result.to_double()));
    }
}

void polygon_expression_symbolizer::set_gamma(double gamma)
{
    gamma_ = gamma;
}

double polygon_expression_symbolizer::get_gamma() const
{
    return gamma_;
}

}

