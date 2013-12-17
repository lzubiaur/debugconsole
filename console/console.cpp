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
 * @file:   console.cpp
 * @author: Laurent Zubiaur
 * @brief:
 */

#include "console/console.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/fcntl.h>
#include <errno.h>

// NO LOGGING   0
// ERROR        1
// INFO         2
// DEBUG        3
#define SERVER_SOCKET_DEBUG 3

#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0 || SERVER_SOCKET_DEBUG == 0
#define LOG_DEBUG(...)              do {} while (0)
#define LOG_INFO(...)               do {} while (0)
#define LOG_ERROR(...)              do {} while (0)

#elif SERVER_SOCKET_DEBUG == 1
#define LOG_DEBUG(...)              do {} while (0)
#define LOG_INFO(...)               do {} while (0)
#define LOG_ERROR(format, ...)      log("[ERROR] " format, ##__VA_ARGS__)

#elif SERVER_SOCKET_DEBUG == 2
#define LOG_DEBUG(...)              do {} while (0)
#define LOG_INFO(format, ...)       log("[INFO] " format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)      log("[ERROR] " format, ##__VA_ARGS__)

#elif SERVER_SOCKET_DEBUG == 3
#define LOG_DEBUG(format, ...)      log("[DEBUG] " format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)       log("[INFO] " format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)      log("[ERROR] " format, ##__VA_ARGS__)
#endif

NS_PIX2D_CONSOLE_BEGIN

Console::Console()
: m_server_ip("0.0.0.0")
, m_server_port(8080)
, m_server_sock(-1)
{}

Console::Console(const char *ip, int port)
: m_server_ip(ip)
, m_server_port(port)
, m_server_sock(-1)
{}

Console::~Console()
{
    Console::close();
}

bool Console::init()
{
    scheduleUpdate();
    return listen();
}

bool Console::close()
{
    LOG_INFO("Graceful shutdown...");
    if (m_server_sock > -1
        && ::shutdown(m_server_sock, SHUT_RDWR)
        && ::close(m_server_sock) != 0) {
        LOG_ERROR("Can't close the server socket: %s", strerror(errno));
        return false;
    }
    m_server_sock = -1;
    LOG_INFO("Server socket has closed.");
    return true;
}

bool Console::listen()
{
    if (m_server_sock > -1) return true; /// server socket already created

    /// Create the IP address
    memset(&m_sock_addr, 0, sizeof(m_sock_addr));

    if (inet_aton(m_server_ip.c_str(), &m_sock_addr.sin_addr) == 0) {
        LOG_ERROR("Invalid IP address: %s", m_server_ip.c_str());
        return false;
    }

    m_sock_addr.sin_len = sizeof(m_sock_addr);
    m_sock_addr.sin_family = AF_INET; // or AF_INET6 for ipv6
    m_sock_addr.sin_port = htons(m_server_port);
    if (m_sock_addr.sin_port == 0) {
        std::cout << "Console: Invalid port number (" << m_server_port << ")" << std::endl;
    }

    /// Create the server socket
#ifdef __MACH__
    m_server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    m_server_sock = socket(AF_INET, SOCK_STREAM, 0);
#endif

    if (m_server_sock == -1) {
        LOG_ERROR("Can't create the server socket: %s", strerror(errno));
        return false;
    }

    ///////////// Socket options /////////////

    /// SO_RCVTIMEO:
    /*
    struct timeval tv;
    tv.tv_sec = 3;  /// 3 Secs Timeout
    tv.tv_usec = 0; /// Not init'ing this can cause strange errors
    setsockopt(m_server_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
    */

    /// SO_REUSEADDR: enables to get around the "Address already in use" error messages when trying to restart the server socket
    int optval = 1;
    if (setsockopt(m_server_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        LOG_ERROR("Can't enable reuse address: %s", strerror(errno));
        close();
        return false;
    }

    /// SO_LIGNER:
    /*
    struct linger so_linger;
    so_linger.l_onoff = 1;    /// Enabled
    so_linger.l_linger = 2;   /// Timeout
    if (setsockopt(m_server_sock, SOL_SOCKET, SO_LINGER, &so_linger, sizeof(so_linger)) < 0) {
        LOG_ERROR("Can't enable the linger options: %s", strerror(errno));("Console:  ");
        close();
        return false;
    }
    */

    /// Non-blocking mode socket
    if (fcntl(m_server_sock, F_SETFL, O_NDELAY) < 0) {
        LOG_ERROR("Can't set server socket to non-blocking: %s", strerror(errno));
        close();
        return false;
    }

    if (bind(m_server_sock,(struct sockaddr *)&m_sock_addr, sizeof(m_sock_addr)) < 0) {
        LOG_ERROR("Can't bind to server socket: %s", strerror(errno));
        close();
        return false;
    }

    /// Only 1 connection backlog is allowed
    if (::listen(m_server_sock, 1) < 0) {
        LOG_ERROR("Can't listen to server socket: %s", strerror(errno));
        close();
        return false;
    }

    /// todo
    std::cout << "Console: Wait for connection at "
              << std::hex << inet_ntoa(m_sock_addr.sin_addr) << ":"
              << std::dec << ntohs(m_sock_addr.sin_port)<<" ..."
              << std::endl;
    
    return true;
}

void Console::update(float dt)
{
    if (m_server_sock < 0) return; /// No server socket

    socklen_t addrlen = sizeof(struct sockaddr_in);
    struct sockaddr_in peer;

    int sock = ::accept(m_server_sock, (struct sockaddr *)&peer, &addrlen);

    if (sock < 1) return; /// Nothing to do. No client connection available.

    std::cout << "Console: Connected to " << std::hex << inet_ntoa(peer.sin_addr) << ":"
              << std::dec << ntohs(peer.sin_port) << std::endl;

    /// Read HEADER
    Header *header = NULL;
    if (read(sock, sizeof(Header), (void**)&header) != sizeof(Header)) {
        LOG_ERROR("Can't read request header from client: %s", strerror(errno));
        if (::close(sock) < 0)
            LOG_ERROR("Can't close the client connection: %s", strerror(errno));
        delete header;
        return;
    }
    /// Convert to network bytes to host bytes
    header->length = ntohl(header->length);
    header->version = ntohs(header->version);
    //header->message = ntohs(header->message);
    //header->tag = ntohl(header->tag)

    /// Read REQUEST content
    char *msg = NULL;
    if (read(sock, header->length, (void**)&msg) != header->length) {
        LOG_ERROR("Can't read request content from client: %s", strerror(errno));
        if (::close(sock) < 0)
            LOG_ERROR("Can't close the client connection: %s", strerror(errno));
        delete header;
        delete msg;
        return;
    }

    /// Invoke the callback method
    std::string output;
    std::string input(msg);
    handleRequest(input, output);

    /// Send RESPONSE
    if (send(sock, output.length(), output.c_str()) != output.length())
        LOG_ERROR("Can't send response to client: %s", strerror(errno));

    /// No more data to send or read
    shutdown(sock, SHUT_RDWR);

    /// Close the client socket.
    if (::close(sock) < 0)
        LOG_ERROR("Can't close the client connection: %s", strerror(errno));

    /// Cleanup
    delete header;
    delete msg;
}

ssize_t Console::read(int sock, size_t msg_len, void **msg)
{
    if (msg_len < 1) return 0;

#define BUF_CHUNK_SIZE 1024
    char chunk[BUF_CHUNK_SIZE];
    ssize_t recv_size = 0;
    size_t total_recv = 0;
    size_t chunk_len = 0;

    /// Message buffer allocation
    uint8_t *buf = new uint8_t[msg_len];

    do {
        /// Next chunk length to read
        chunk_len = (msg_len - total_recv) < BUF_CHUNK_SIZE ? msg_len - total_recv : BUF_CHUNK_SIZE;

        /// Read chunk of BUF_SIZE bytes
        recv_size = ::recv(sock, chunk, chunk_len, 0);
        if (recv_size < 0) {
            /// Error
            *msg = NULL;
            delete buf;
            return -1;
        } else if (recv_size == 0)
            /// EOF. No more data to read
            break;
        /// Append the chunk to the message buffer
        memcpy(&buf[total_recv], chunk, recv_size);
    } while ((total_recv += recv_size) < msg_len);

    LOG_DEBUG("Read %d byte(s)", total_recv);

    *msg = buf;
    return msg_len;
}

ssize_t Console::send(int sock, size_t msg_len, const void *msg)
{
    if (msg_len < 1) return 0;

    int sent = 0;
    int total_sent = 0;

    do {
        sent = ::send(sock, (const void *)msg, msg_len - total_sent, 0);
        if (sent < 1)
            return -1;
    } while ((total_sent += sent) < msg_len);

    LOG_DEBUG("Sent %d byte(s)", total_sent);
    return msg_len;
}

void Console::log(const char *format, ...)
{
    char buf[16 * 1024];

    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, 16 * 1024, format, ap);
    va_end(ap);
    printf("Console: %s\n", buf);
}

NS_PIX2D_CONSOLE_END
