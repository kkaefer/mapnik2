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

#ifndef _PALETTE_HPP_
#define _PALETTE_HPP_


// mapnik
#include <mapnik/global.hpp>
#include <mapnik/config_error.hpp>

// boost
#include <boost/utility.hpp>
#include <boost/unordered_map.hpp>

// stl
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <cmath>

namespace mapnik {

typedef boost::uint8_t byte;
struct rgb;
struct rgba;


struct rgb
{
    byte r;
    byte g;
    byte b;

    rgb(byte r_, byte g_, byte b_);
    rgb(rgba const& c);
    bool operator==(const rgb& y) const;
};

struct rgba
{
    byte r;
    byte g;
    byte b;
    byte a;

    rgba(byte r_, byte g_, byte b_, byte a_);
    rgba(rgb const& c);
    bool operator==(const rgba& y) const;

    // ordering by mean(a,r,g,b), a, r, g, b
    struct mean_sort_cmp
    {
        bool operator() (const rgba& x, const rgba& y) const;
    };

    struct hash_func : public std::unary_function<rgba, std::size_t>
    {
        std::size_t operator()(rgba const& p) const;
    };
};

typedef boost::unordered_map<rgba, int, rgba::hash_func> rgba_hash_table;


class rgba_palette : private boost::noncopyable {
public:
    enum palette_type { PALETTE_RGBA = 0, PALETTE_RGB = 1, PALETTE_ACT = 2 };

    explicit rgba_palette(std::string const& pal, palette_type type = PALETTE_RGBA);
    explicit rgba_palette();

    const std::vector<rgb>& palette() const;
    const std::vector<unsigned>& alphaTable() const;
    unsigned int quantize(rgba const& c);
    bool valid();

private:
    void parse(std::string const& pal, palette_type type);

private:
    std::vector<rgba> sorted_pal_;
    rgba_hash_table color_hashmap_;

    unsigned colors_;
    std::vector<rgb> rgb_pal_;
    std::vector<unsigned> alpha_pal_;
};

static rgba_palette _rgba_palette;

} // namespace mapnik

#endif // _PALETTE_HPP_

