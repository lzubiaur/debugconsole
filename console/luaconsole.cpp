/**
 * Copyright (c) 2013 Laurent Zubiaur
 *
 * http://www.pix2d.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * @file:   luaconsole.cpp
 * @author: Laurent Zubiaur
 * @brief:
 */

#include "console/luaconsole.h"
#include <fstream>

#define LUA_LIB
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

/// tolua++
#include <tolua/tolua++.h>
#include "console/tolua/command.hpp"

NS_PIX2D_CONSOLE_BEGIN

LuaConsole::LuaConsole()
{
    /// Create the lua state object
    L = luaL_newstate();

    /// Load Lua libraries
    luaL_openlibs(L);

    /// Load tolua binding packages
    tolua_command_open(L);
}

LuaConsole::~LuaConsole()
{
    lua_close(L);
}

void LuaConsole::handleRequest(const std::string &input, std::string &output)
{
    /// std::cout << input << std::endl;
    output.append("ok");

    if (input.length() < 1) {
        output = std::string("ERROR: Lua script is empty.");
        return ;
    }

    if (luaL_loadstring(L, input.c_str())) {
        output = std::string(lua_tostring(L, -1));
        CCLOG("Lua error: %s", output.c_str());
        return;
    }

    if ( lua_pcall(L, 0, LUA_MULTRET, 0) != 0) {
        output = std::string(lua_tostring(L, -1));
        CCLOG("Lua error: %s", output.c_str());
    }

    /// std::cout << output << std::endl;
}

NS_PIX2D_CONSOLE_END
