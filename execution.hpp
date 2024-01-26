#pragma once

#include <queue>
#include <Luau/Compiler.h>
#include <Luau/BytecodeBuilder.h>
#include <Luau/BytecodeUtils.h>
#include <mutex>
#include <functional>

namespace exec
{
    auto execute_script(const std::string& script) -> void;
    auto wait_for_tick(lua_State* ls) -> void;
    auto handle_script(lua_State* ls, int narg) -> int;
}
