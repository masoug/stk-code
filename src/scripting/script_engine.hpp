/*
 * ScriptEngine.hpp
 *
 *  Created on: Mar 8, 2014
 *      Author: sammy
 */

#ifndef SCRIPTENGINE_H_
#define SCRIPTENGINE_H_

#include <string>

#include "lua.hpp"

#include "utils/no_copy.hpp"
#include "utils/log.hpp"
#include "utils/cpp2011.h"

class ScriptEngine: public NoCopy {
public:
    ScriptEngine();

    void        registerFunction(std::string name, lua_CFunction funcptr);
    void        onInitialize(void * ptr);
    void        registerNumber(std::string name, double number);
    bool        loadScriptFile(std::string script_path);
    bool        runScript();
    bool        callFunction(std::string name);
    lua_State*  getLuaState() { return m_lua_state; }

    virtual     ~ScriptEngine();

private:
    lua_State*  m_lua_state;
};

#endif /* SCRIPTENGINE_H_ */
