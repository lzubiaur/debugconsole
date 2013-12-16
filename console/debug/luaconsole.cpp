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

#include "debug/luaconsole.h"
#include "scene/levelloader.h"
#include "debug/dictmaker.h"
#include "debug/debuglayer.h"
#include <fstream>

#define LUA_LIB
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

/// tolua++
#include <tolua/tolua++.h>
#include "debug/tolua/luaconsole.hpp"

#include <cocos2dx/support/base64.h>

USING_NS_PIX2D;

NS_PIX2D_DEBUG_BEGIN

LuaConsole::LuaConsole()
{
    /// Create the lua state object
    L = luaL_newstate();

    /// Load Lua libraries
    luaL_openlibs(L);

    /// Load tolua binding packages
    tolua_luaconsole_open(L);
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

    std::cout << output << std::endl;
}

bool LuaConsole::reloadLevel()
{
    if (CCScene *scene = LevelLoader::createWithData(DebugSettings::getInstance()->levelData.c_str()))
        CCDirector::sharedDirector()->replaceScene(scene);
    return true;
}

bool LuaConsole::reloadLevel(const char *data)
{
    if (CCScene *scene = LevelLoader::createWithData(data)) {
        CCDirector::sharedDirector()->replaceScene(scene);
        DebugSettings::getInstance()->levelData = std::string(data);
    }
    return true;
}

/** Original code from CCSpriteFrameCache::addSpriteFramesWithDictionary */
void LuaConsole::replaceSpriteFrames(CCDictionary *pDict, CCTexture2D *pTexture)
{
    CCDictionary *metadataDict = (CCDictionary*)pDict->objectForKey("metadata");
    CCDictionary *framesDict = (CCDictionary*)pDict->objectForKey("frames");
    int format = 0;

    // get the format
    if(metadataDict != NULL)
        format = metadataDict->valueForKey("format")->intValue();

    // check the format
    CCAssert(format == 2, "Only format 2 is supported");

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
        std::string spriteFrameName = pElement->getStrKey();

        /*
        if (CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName.c_str()))
            continue;
        */
        
        CCRect frame = CCRectFromString(frameDict->valueForKey("frame")->getCString());
        bool rotated = false;

        // rotation
        if (format == 2) {
            rotated = frameDict->valueForKey("rotated")->boolValue();
        }

        CCPoint offset = CCPointFromString(frameDict->valueForKey("offset")->getCString());
        CCSize sourceSize = CCSizeFromString(frameDict->valueForKey("sourceSize")->getCString());

        // create frame
        CCSpriteFrame *spriteFrame = new CCSpriteFrame();
        spriteFrame->initWithTexture(pTexture, frame, rotated, offset, sourceSize);
        // add sprite frame
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spriteFrame, spriteFrameName.c_str());
        spriteFrame->release();
    }
}

void LuaConsole::updateSpriteFrames(const char *pPlist, const char *pTexture)
{
    char *plist_data;
    int plist_data_len = base64Decode((unsigned char*)pPlist, strlen(pPlist), (unsigned char**)&plist_data);
    /// std::cout << plist_data << std::endl;

    char *texture_data;
    int texture_data_len = base64Decode((unsigned char*)pTexture, strlen(pTexture), (unsigned char**)&texture_data);

    DictMaker maker;
    CCDictionary *dict = maker.createDictionaryWithString(plist_data, plist_data_len);

    CCImage *img = new CCImage();
    img->initWithImageData(texture_data, texture_data_len);
    CCTexture2D *texture = new CCTexture2D();
    texture->initWithImage(img);

    replaceSpriteFrames(dict, texture);

    delete plist_data;
    delete texture_data;
}

NS_PIX2D_DEBUG_END
