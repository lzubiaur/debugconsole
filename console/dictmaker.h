/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/**
 * @file:   dictmaker.h
 * @brief:  Create a CCDictionary from string data
 * 
 * Original code is part of the cocos2d-x distribution (platform/CCFileUtilsCommon_cpp.h)
 * Modified and adapted by Laurent Zubiaur http://www.pix2d.com/
 */

#ifndef PIX2D_DEBUG_DICTMAKER_H
#define PIX2D_DEBUG_DICTMAKER_H

#include "console/forwards.h"
#include <stack>
#include <cocos2d.h>
USING_NS_CC;

NS_PIX2D_CONSOLE_BEGIN

typedef enum
{
    SAX_NONE = 0,
    SAX_KEY,
    SAX_DICT,
    SAX_INT,
    SAX_REAL,
    SAX_STRING,
    SAX_ARRAY
}CCSAXState;

typedef enum
{
    SAX_RESULT_NONE = 0,
    SAX_RESULT_DICT,
    SAX_RESULT_ARRAY
}CCSAXResult;

class DictMaker : public CCSAXDelegator {
public:
    DictMaker();
    virtual ~DictMaker();

    CCDictionary* createDictionaryWithString(const char *data, int len);

protected:
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);

private:
    CCSAXResult m_eResultType;
    CCArray* m_pRootArray;
    CCDictionary *m_pRootDict;
    CCDictionary *m_pCurDict;
    std::stack<CCDictionary*> m_tDictStack;
    std::string m_sCurKey;   ///< parsed key
    std::string m_sCurValue; // parsed value
    CCSAXState m_tState;
    CCArray* m_pArray;

    std::stack<CCArray*> m_tArrayStack;
    std::stack<CCSAXState>  m_tStateStack;
};

NS_PIX2D_CONSOLE_END
#endif // PIX2D_DEBUG_DICTMAKER_H
