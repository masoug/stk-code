/*
 * ScriptEngine.cpp
 *
 *  Created on: Mar 8, 2014
 *      Author: sammy
 */

#include "scripting/script_engine.hpp"
#include <stdint.h>


extern "C" {
int stkSetKartVelocity(lua_State *lua_state) {
    printf("stkKartVelcity\n");
    return 0;
}
}

ScriptEngine::ScriptEngine()
{
    m_lua_state = luaL_newstate();
    luaL_openlibs(m_lua_state);
}

void ScriptEngine::registerFunction(std::string name, lua_CFunction funcptr) {
    lua_pushcfunction(m_lua_state, funcptr);
    lua_setglobal(m_lua_state, name.c_str());
}

void ScriptEngine::onInitialize(void* ptr) {
    lua_getglobal(m_lua_state, "onInitialize");
    lua_pushinteger(m_lua_state, (uintptr_t)ptr);
    if (lua_pcall(m_lua_state, 1, 0, 0))
    {
        Log::error("ScriptEngine", "onInitialize handler error:");
        Log::error("ScriptEngine", "%s", lua_tostring(m_lua_state, -1));
        lua_pop(m_lua_state, 1);
    }
}

void ScriptEngine::registerNumber(std::string name, double number) {
    lua_pushnumber(m_lua_state, number);
    lua_setglobal(m_lua_state, name.c_str());
}

bool ScriptEngine::loadScriptFile(std::string script_path)
{
    if (luaL_loadfile(m_lua_state, script_path.c_str()))
    {
        Log::error("ScriptEngine", "Failed to load lua script: %s",
                script_path.c_str());
        Log::error("ScriptEngine", "%s", lua_tostring(m_lua_state, -1));
        lua_pop(m_lua_state, 1);
        return false;
    }
    Log::info("ScriptEngine", "Loaded lua script: %s", script_path.c_str());
    return true;
}

bool ScriptEngine::runScript()
{
    if (lua_pcall(m_lua_state, 0, LUA_MULTRET, 0))
    {
        Log::error("ScriptEngine", "Error executing lua script.");
        Log::error("ScriptEngine", "%s", lua_tostring(m_lua_state, -1));
        lua_pop(m_lua_state, 1);
        return false;
    }
    return true;
}

bool ScriptEngine::callFunction(std::string name)
{
    lua_getglobal(m_lua_state, name.c_str());
    if (lua_pcall(m_lua_state, 0, 0, 0))
    {
        Log::error("ScriptEngine", "Error executing lua script.");
        Log::error("ScriptEngine", "%s", lua_tostring(m_lua_state, -1));
        lua_pop(m_lua_state, 1);
        return false;
    }
    return true;
}

ScriptEngine::~ScriptEngine()
{
    lua_close(m_lua_state);
}

