/*
 * ScriptEngine.cpp
 *
 *  Created on: Mar 8, 2014
 *      Author: sammy
 */

#include "scripting/script_engine.hpp"
#include "tracks/track_object.hpp"
#include "karts/kart.hpp"
#include <stdint.h>

ScriptEngine::ScriptEngine()
{
    m_lua_state = luaL_newstate();
    luaL_openlibs(m_lua_state);
}

void ScriptEngine::registerFunction(std::string name, lua_CFunction funcptr) {
//    lua_pushcfunction(m_lua_state, funcptr);
//    lua_setglobal(m_lua_state, name.c_str());
}

void ScriptEngine::onInitialize(void* ptr)
{
//    lua_getglobal(m_lua_state, "onInitialize");
//    TrackObject **pptr = (TrackObject**) lua_newuserdata(m_lua_state,
//            sizeof(TrackObject*));
//    *pptr = (TrackObject*) ptr;
//    luaL_getmetatable(m_lua_state, "stk.trackobj");
//    lua_setmetatable(m_lua_state, -2);
////    lua_pushinteger(m_lua_state, (uintptr_t)ptr);
//    if (lua_pcall(m_lua_state, 1, 0, 0))
//    {
//        Log::error("ScriptEngine", "onInitialize handler error:");
//        Log::error("ScriptEngine", "%s", lua_tostring(m_lua_state, -1));
//        lua_pop(m_lua_state, 1);
//    }
}

void ScriptEngine::onUpdate(void* ptr)
{
//    lua_getglobal(m_lua_state, "onUpdate");
//    TrackObject **pptr = (TrackObject**) lua_newuserdata(m_lua_state,
//            sizeof(TrackObject*));
//    *pptr = (TrackObject*) ptr;
//    luaL_getmetatable(m_lua_state, "stk.trackobj");
//    lua_setmetatable(m_lua_state, -2);
//    //    lua_pushinteger(m_lua_state, (uintptr_t)ptr);
//    if (lua_pcall(m_lua_state, 1, 0, 0))
//    {
//        Log::error("ScriptEngine", "onUpdate handler error:");
//        Log::error("ScriptEngine", "%s", lua_tostring(m_lua_state, -1));
//        lua_pop(m_lua_state, 1);
//    }
}

void ScriptEngine::onKartCollision(void* this_kart, void* other_kart)
{
    lua_getglobal(m_lua_state, "onKartCollision");
    Kart **pptr_this = (Kart**) lua_newuserdata(m_lua_state,
            sizeof(Kart*));
    *pptr_this = (Kart*) this_kart;
    luaL_getmetatable(m_lua_state, "stk.kart");
    lua_setmetatable(m_lua_state, -2);
    Kart **pptr_other = (Kart**) lua_newuserdata(m_lua_state,
            sizeof(Kart*));
    *pptr_other = (Kart*) other_kart;
    luaL_getmetatable(m_lua_state, "stk.kart");
    lua_setmetatable(m_lua_state, -2);
    //    lua_pushinteger(m_lua_state, (uintptr_t)ptr);
    if (lua_pcall(m_lua_state, 2, 0, 0))
    {
        Log::error("ScriptEngine", "onUpdate handler error:");
        Log::error("ScriptEngine", "%s", lua_tostring(m_lua_state, -1));
        lua_pop(m_lua_state, 1);
    }
}

void ScriptEngine::registerNumber(std::string name, double number) {
//    lua_pushnumber(m_lua_state, number);
//    lua_setglobal(m_lua_state, name.c_str());
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
//    lua_getglobal(m_lua_state, name.c_str());
//    if (lua_pcall(m_lua_state, 0, 0, 0))
//    {
//        Log::error("ScriptEngine", "Error executing lua script.");
//        Log::error("ScriptEngine", "%s", lua_tostring(m_lua_state, -1));
//        lua_pop(m_lua_state, 1);
//        return false;
//    }
    return true;
}

ScriptEngine::~ScriptEngine()
{
    lua_close(m_lua_state);
}

