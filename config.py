def can_build(env, platform):
    return True


def configure(env):
    from SCons.Script import ARGUMENTS

    tracy_enable = ARGUMENTS.get("tracy_enable", "none")
    if tracy_enable != "none":
        env["tracy_enable"] = tracy_enable

    tracy_on_demand = ARGUMENTS.get("tracy_on_demand", "none")
    if tracy_on_demand != "none":
        env["tracy_on_demand"] = tracy_on_demand


def is_enabled():
    return True
