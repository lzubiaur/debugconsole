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
 * @file:   console.h
 * @author: Laurent Zubiaur
 * @brief:
 */

#ifndef PIX2D_DEBUG_CONSOLE_H
#define PIX2D_DEBUG_CONSOLE_H

#include "console/forwards.h"
#include <netinet/in.h>
#include <cocos2d.h>
USING_NS_CC;

NS_PIX2D_CONSOLE_BEGIN

class Console : public CCNode {
protected:
    struct Header {
        uint32_t length;        /// Message content-length (not including this header)
        // uint32_t tag;           /// Response to this request will echo this tag
        // uint8_t message;        /// Request type
        uint8_t version;        /// Protocol version
    } __attribute__((__packed__)); /// Disable structure padding

public:
    Console();
    Console(const char *ip, int port);

    virtual ~Console();

    virtual bool init();
    virtual void update(float dt);

    bool listen();
    bool close();

    /** @brief Pure virtual method */
    virtual void handleRequest(const std::string &input, std::string &output) = 0;

protected:
    /** @brief Send raw data */
    ssize_t send(int sock, size_t len, const void *msg);
    /** @brief Receave raw data  */
    ssize_t read(int sock, size_t len, void **msg);

    void log(const char *format, ...);

private:
    /// Main socket address
    struct sockaddr_in m_sock_addr;
    /// The server socket descriptor
    int m_server_sock;
    /// The ip address
    std::string m_server_ip;
    /// Port number
    int m_server_port;
};

NS_PIX2D_CONSOLE_END

#endif // PIX2D_DEBUG_CONSOLE_H
