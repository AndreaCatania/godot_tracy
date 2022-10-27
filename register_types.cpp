#include "register_types.h"

#include "core/engine.h"
#include "tracy_profiler.h"

void register_godot_tracy_types() {
	ClassDB::register_class<TracyProfiler>();

	TracyProfiler::init_singleton();
	Engine::get_singleton()->add_singleton(Engine::Singleton("TracyProfiler", TracyProfiler::get_singleton()));
}

void unregister_godot_tracy_types() {
	TracyProfiler::finalize_singleton();
}
