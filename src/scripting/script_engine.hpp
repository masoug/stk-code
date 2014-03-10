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

class ScriptEngine: public NoCopy {
public:
    ScriptEngine();

    bool        loadScriptFile(std::string script_path);
    bool        runScript();
    bool        callFunction(std::string name);

    virtual     ~ScriptEngine();

private:
    lua_State*  m_lua_state;
};

#endif /* SCRIPTENGINE_H_ */
