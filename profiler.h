#ifndef GODOT_TRACY_PROFILER_H
#define GODOT_TRACY_PROFILER_H

#include "core/string/string_name.h"
#include "tracy/public/tracy/Tracy.hpp"

class Variant;

class Profiler {
public:
	static CharString stringify_method(const StringName &p_method, const Variant **p_args, int p_argcount);
};

#endif
