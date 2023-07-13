#include "tracy_profiler.h"

#include "core/math/color.h"
#include "tracy/public/tracy/Tracy.hpp"
#include "tracy/public/tracy/TracyC.h"

TracyProfiler *TracyProfiler::singleton = nullptr;

void TracyProfiler::_bind_methods() {
	ClassDB::bind_method(D_METHOD("zone_begin", "zone_name"), &TracyProfiler::zone_begin);
	ClassDB::bind_method(D_METHOD("zone_begin_v", "zone_name", "value"), &TracyProfiler::zone_begin_v);
	ClassDB::bind_method(D_METHOD("zone_begin_t", "zone_name", "text"), &TracyProfiler::zone_begin_t);
	ClassDB::bind_method(D_METHOD("zone_begin_tv", "zone_name", "text", "value"), &TracyProfiler::zone_begin_tv);
	ClassDB::bind_method(D_METHOD("zone_begin_c", "zone_name", "color"), &TracyProfiler::zone_begin_c);
	ClassDB::bind_method(D_METHOD("zone_begin_ct", "zone_name", "color", "text"), &TracyProfiler::zone_begin_ct);
	ClassDB::bind_method(D_METHOD("zone_begin_cv", "zone_name", "color", "value"), &TracyProfiler::zone_begin_cv);
	ClassDB::bind_method(D_METHOD("zone_begin_ctv", "zone_name", "color", "text", "value"), &TracyProfiler::zone_begin_ctv);
	ClassDB::bind_method(D_METHOD("zone_set_color", "zone_id", "color"), &TracyProfiler::zone_set_color);
	ClassDB::bind_method(D_METHOD("zone_set_text", "zone_id", "text"), &TracyProfiler::zone_set_text);
	ClassDB::bind_method(D_METHOD("zone_set_value", "zone_id", "value"), &TracyProfiler::zone_set_value);
	ClassDB::bind_method(D_METHOD("zone_end", "zone_id"), &TracyProfiler::zone_end);
	ClassDB::bind_method(D_METHOD("message", "text", "color"), &TracyProfiler::message, DEFVAL(Color()));
}

void TracyProfiler::init_singleton() {
	if (singleton == nullptr) {
		singleton = memnew(TracyProfiler);
	}
}

void TracyProfiler::finalize_singleton() {
	if (singleton) {
		memdelete(singleton);
		singleton = nullptr;
	}
}

TracyProfiler *TracyProfiler::get_singleton() {
	return singleton;
}

#ifdef TRACY_ENABLE
union TracyIdConverter {
	___tracy_c_zone_context tracy_id;
	uint64_t godot_id;
};
#endif

uint32_t to_rgb32(const Color &p_color) {
	uint32_t c = (uint8_t)Math::round(p_color.r * 255);
	c <<= 8;
	c |= (uint8_t)Math::round(p_color.g * 255);
	c <<= 8;
	c |= (uint8_t)Math::round(p_color.b * 255);

	return c;
}

uint64_t TracyProfiler::zone_begin(const String &p_zone_name) {
#ifdef TRACY_ENABLE
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));

	TracyCZone(zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c.ptr(), c.size());

	TracyIdConverter converter;
	converter.tracy_id = zone_id;
	return converter.godot_id;
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_v(const String &p_zone_name, uint64_t p_value) {
#ifdef TRACY_ENABLE
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));

	TracyCZone(zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c.ptr(), c.size());

	TracyCZoneValue(zone_id, p_value);

	TracyIdConverter converter;
	converter.tracy_id = zone_id;
	return converter.godot_id;
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_t(const String &p_zone_name, const String &p_text) {
#ifdef TRACY_ENABLE
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));

	TracyCZone(zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c.ptr(), c.size());

	const CharString t = p_zone_name.utf8();
	TracyCZoneText(zone_id, t.ptr(), t.size());

	TracyIdConverter converter;
	converter.tracy_id = zone_id;
	return converter.godot_id;
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_tv(const String &p_zone_name, const String &p_text, uint64_t p_value) {
#ifdef TRACY_ENABLE
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));

	TracyCZone(zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c.ptr(), c.size());

	const CharString t = p_zone_name.utf8();
	TracyCZoneText(zone_id, t.ptr(), t.size());
	TracyCZoneValue(zone_id, p_value);

	TracyIdConverter converter;
	converter.tracy_id = zone_id;
	return converter.godot_id;
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_c(const String &p_zone_name, const Color &p_color) {
#ifdef TRACY_ENABLE
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));

	TracyCZone(zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c.ptr(), c.size());

	TracyCZoneColor(zone_id, to_rgb32(p_color));

	TracyIdConverter converter;
	converter.tracy_id = zone_id;
	return converter.godot_id;
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_ct(const String &p_zone_name, const Color &p_color, const String &p_text) {
#ifdef TRACY_ENABLE
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));

	TracyCZone(zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c.ptr(), c.size());

	TracyCZoneColor(zone_id, to_rgb32(p_color));
	const CharString t = p_zone_name.utf8();
	TracyCZoneText(zone_id, t.ptr(), t.size());

	TracyIdConverter converter;
	converter.tracy_id = zone_id;
	return converter.godot_id;
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_cv(const String &p_zone_name, const Color &p_color, uint64_t p_value) {
#ifdef TRACY_ENABLE
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));

	TracyCZone(zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c.ptr(), c.size());

	TracyCZoneColor(zone_id, to_rgb32(p_color));
	TracyCZoneValue(zone_id, p_value);

	TracyIdConverter converter;
	converter.tracy_id = zone_id;
	return converter.godot_id;
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_ctv(const String &p_zone_name, const Color &p_color, const String &p_text, uint64_t p_value) {
#ifdef TRACY_ENABLE
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));

	TracyCZone(zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c.ptr(), c.size());

	TracyCZoneColor(zone_id, to_rgb32(p_color));
	const CharString t = p_zone_name.utf8();
	TracyCZoneText(zone_id, t.ptr(), t.size());
	TracyCZoneValue(zone_id, p_value);

	TracyIdConverter converter;
	converter.tracy_id = zone_id;
	return converter.godot_id;
#else
	return 0;
#endif
}

void TracyProfiler::zone_set_color(uint64_t p_zone_id, const Color &p_color) {
#ifdef TRACY_ENABLE
	TracyIdConverter converter;
	converter.godot_id = p_zone_id;
	TracyCZoneColor(converter.tracy_id, to_rgb32(p_color));
#endif
}

void TracyProfiler::zone_set_text(uint64_t p_zone_id, const String &p_text) {
#ifdef TRACY_ENABLE
	TracyIdConverter converter;
	converter.godot_id = p_zone_id;

	const CharString c = p_text.utf8();

	TracyCZoneText(converter.tracy_id, c.ptr(), c.size());
#endif
}

void TracyProfiler::zone_set_value(uint64_t p_zone_id, uint64_t p_value) {
#ifdef TRACY_ENABLE
	TracyIdConverter converter;
	converter.godot_id = p_zone_id;
	TracyCZoneValue(converter.tracy_id, p_value);
#endif
}

void TracyProfiler::zone_end(uint64_t p_zone_id) {
#ifdef TRACY_ENABLE
	TracyIdConverter converter;
	converter.godot_id = p_zone_id;
	TracyCZoneEnd(converter.tracy_id);
#endif
}

void TracyProfiler::message(const String &p_text, const Color &p_color) {
#ifdef TRACY_ENABLE
	const CharString c = p_text.utf8();
	TracyCMessageC(c.ptr(), c.size(), to_rgb32(p_color));
#endif
}