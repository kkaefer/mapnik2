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

#ifndef SVG_RENDERER_HPP
#define SVG_RENDERER_HPP

// mapnik
#include <mapnik/feature_style_processor.hpp>

// stl
#include <string>

namespace mapnik 
{
    // parameterized with the type of ostream it will use for output.
    template <typename T>
    class MAPNIK_DECL svg_renderer : public feature_style_processor<svg_renderer<T> >, 
				     private boost::noncopyable
    {

    public:
	// the only parameter I'm sure of is the map.
	svg_renderer(Map const& m, T& output_stream);
	~svg_renderer();

	void start_map_processing(Map const& map);
	void end_map_processing(Map const& map);
	void start_layer_processing(layer const& lay);
	void end_layer_processing(layer const& lay);
	void process(point_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(line_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(line_pattern_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(polygon_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(polygon_pattern_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(raster_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(shield_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(text_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(building_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(markers_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	void process(glyph_symbolizer const& sym,
		     Feature const& feature,
		     proj_transform const& prj_trans);
	
	// should this function be inline?
	inline T& get_output_stream() 
	{
	    return output_stream_;
	}

	// should this function be inline?
	inline const T& get_output_stream() const
	{
	    return output_stream_;
	}

	// XML declaration.
	static const std::string XML_DECLARATION;
	// DTD urls.
	static const std::string SVG_DTD;
	// SVG version to which the generated document will be compliant.
	static const double SVG_VERSION;
	// SVG XML namespace url.
	static const std::string SVG_NAMESPACE_URL;

    private:
	T& output_stream_;
	const int width_;
	const int height_;
    };
}

#endif //SVG_RENDERER_HPP
