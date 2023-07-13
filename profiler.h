#ifndef GODOT_TRACY_PROFILER_H
#define GODOT_TRACY_PROFILER_H

#include "tracy/public/tracy/Tracy.hpp"

#include "core/variant/variant.h"

class Profiler {
public:
	static CharString stringify_method(const StringName &p_method, const Variant **p_args, int p_argcount) {
#ifdef TRACY_ENABLE
		String out = p_method;
		out += "(";
		for (int i = 0; i < p_argcount; i += 1) {
			if (i != 0) {
				out += ", ";
			}
			out += p_args[i]->operator String();
		}
		out += ")";
		CharString c = out.utf8();
		if (c.size() >= std::numeric_limits<uint16_t>::max()) {
			c.resize(std::numeric_limits<uint16_t>::max() - 1);
		}
		return c;
#else
		return CharString();
#endif
	}
};

#endif
