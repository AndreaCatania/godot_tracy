#include "register_types.h"

#include "core/object/class_db.h"
#include "core/config/engine.h"
#include "tracy_profiler.h"

void initialize_godot_tracy_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<TracyProfiler>();

	TracyProfiler::init_singleton();
	Engine::get_singleton()->add_singleton(Engine::Singleton("TracyProfiler", TracyProfiler::get_singleton()));
}

void uninitialize_godot_tracy_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	TracyProfiler::finalize_singleton();
}
