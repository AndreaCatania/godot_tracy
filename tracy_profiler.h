#pragma once

#include "core/config/engine.h"
#include "core/object/object.h"
#include "tracy/public/common/TracyColor.hpp"

class TracyProfiler : public Object {
	GDCLASS(TracyProfiler, Object);

	static TracyProfiler *singleton;

public:
	static void _bind_methods();

	static void init_singleton();
	static void finalize_singleton();

	static TracyProfiler *get_singleton();

	uint64_t zone_begin(const String &p_zone_name);
	uint64_t zone_begin_v(const String &p_zone_name, uint64_t p_value);
	uint64_t zone_begin_t(const String &p_zone_name, const String &p_text);
	uint64_t zone_begin_tv(const String &p_zone_name, const String &p_text, uint64_t p_value);
	uint64_t zone_begin_c(const String &p_zone_name, const Color &p_color);
	uint64_t zone_begin_ct(const String &p_zone_name, const Color &p_color, const String &p_text);
	uint64_t zone_begin_cv(const String &p_zone_name, const Color &p_color, uint64_t p_value);
	uint64_t zone_begin_ctv(const String &p_zone_name, const Color &p_color, const String &p_text, uint64_t p_value);
	void zone_set_color(uint64_t p_zone_id, const Color &p_color);
	void zone_set_text(uint64_t p_zone_id, const String &p_text);
	void zone_set_value(uint64_t p_zone_id, uint64_t p_value);
	void zone_end(uint64_t p_zone_id);

	void message(const String &p_text, const Color &p_color = Color(1.0, 1.0, 1.0, 1.0));
};
