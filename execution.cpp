#include "execution.hpp"
#include <thread>

std::vector<lua_State*> yielded_states = {};
constexpr const bool IS_DEBUGGING = false;

static int wait_for_tick(lua_State* ls) {
    yielded_states.push_back(ls);   
    return lua_yield(ls, 0);
}

void handle_script(lua_State* ls, int narg) {    
    int res = lua_resume(ls, narg);
    if (res == 0)
        dprintf("[*] state %p finished execution.\n", ls), lua_close(ls);
    else if (res == LUA_YIELD)
        dprintf("[*] yielded state %p\n", ls);
    else if (res > LUA_YIELD)
        dprintf("[-] state %p error: %s\n", ls, lua_tostring(ls, -1)), lua_close(ls);
}

void execute_script(lua_State* ls, const std::string& src) {
    luaL_loadstring(ls, src.c_str());
    std::thread(handle_script, ls, 0).detach();
}
