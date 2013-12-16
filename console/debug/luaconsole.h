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
 * @file:   luaconsole.h
 * @author: Laurent Zubiaur
 * @brief:
 */

#ifndef PIX2D_DEBUG_LUACONSOLE_H
#define PIX2D_DEBUG_LUACONSOLE_H

#include "debug/forwards.h"
#include "debug/console.h"

/// Forward declaration
struct lua_State;

NS_PIX2D_DEBUG_BEGIN

class LuaConsole : public Console {
public:
    explicit LuaConsole();
    virtual ~LuaConsole();

    CREATE_FUNC(LuaConsole);

    /// Implement ServerSocket::handleRequest
    virtual void handleRequest(const std::string &input, std::string &output);

    /// Exposed methods to lua
    bool reloadLevel();
    bool reloadLevel(const char *data);
    void updateSpriteFrames(const char *plist_data, const char *texture_data);

protected:
    void replaceSpriteFrames(CCDictionary *pDict, CCTexture2D *pTexture);

protected:
    lua_State *L;
};

NS_PIX2D_DEBUG_END
#endif // PIX2D_LUA_CONSOLE_H
