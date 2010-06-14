// Module:  Log4CPLUS
// File:    socket-unix.cxx
// Created: 4/2003
// Author:  Tad E. Smith
//
//
// Copyright (C) Tad E. Smith  All rights reserved.
//
// This software is published under the terms of the Apache Software
// License version 1.1, a copy of which has been included with this
// distribution in the LICENSE.APL file.
//

#include <cstring>
//#include <vector>
#include <algorithm>
#include "dcmtk/oflog/helpers/socket.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/spi/logevent.h"

#if defined(__hpux__)
# ifndef _XOPEN_SOURCE_EXTENDED
# define _XOPEN_SOURCE_EXTENDED
# endif
# include <arpa/inet.h>
#endif


#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__hpux__) || defined (__CYGWIN__)
#include <netinet/in.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

#include <algorithm>

using namespace log4cplus;
using namespace log4cplus::helpers;


/////////////////////////////////////////////////////////////////////////////
// Global Methods
/////////////////////////////////////////////////////////////////////////////

SOCKET_TYPE
log4cplus::helpers::openSocket(unsigned short port, SocketState& state)
{
    SOCKET_TYPE sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        return INVALID_SOCKET;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    int optval = 1;
    setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval) );

    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        return INVALID_SOCKET;
    }

    if(::listen(sock, 10)) {
        return INVALID_SOCKET;
    }

    state = ok;
    return sock;
}


SOCKET_TYPE
log4cplus::helpers::connectSocket(const log4cplus::tstring& hostn,
                                  unsigned short port, SocketState& state)
{
    struct sockaddr_in server;
    struct hostent *hp;
    SOCKET_TYPE sock;
    int retval;

    hp = ::gethostbyname(LOG4CPLUS_TSTRING_TO_STRING(hostn).c_str());
    if(hp == 0) {
        return INVALID_SOCKET;
    }

    sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        return INVALID_SOCKET;
    }

    STD_NAMESPACE memcpy((char*)&server.sin_addr, hp->h_addr_list[0], hp->h_length);
    server.sin_port = htons(port);
    server.sin_family = AF_INET;

    while(   (retval = ::connect(sock, (struct sockaddr*)&server, sizeof(server))) == -1
          && (errno == EINTR))
        ;
    if(retval == INVALID_SOCKET) {
        ::close(sock);
        return INVALID_SOCKET;
    }

    state = ok;
    return sock;
}



SOCKET_TYPE
log4cplus::helpers::acceptSocket(SOCKET_TYPE sock, SocketState& state)
{
    struct sockaddr_in net_client;
    socklen_t len = sizeof(struct sockaddr);
    SOCKET_TYPE clientSock;
//    struct hostent *hostptr;

    while(   (clientSock = ::accept(sock, (struct sockaddr*)&net_client, &len)) == -1
          && (errno == EINTR))
        ;

//    hostptr = gethostbyaddr((char*)&(net_client.sin_addr.s_addr), 4, AF_INET);
    if(clientSock != INVALID_SOCKET) {
        state = ok;
    }

    return clientSock;
}



int
log4cplus::helpers::closeSocket(SOCKET_TYPE sock)
{
    return ::close(sock);
}



long
log4cplus::helpers::read(SOCKET_TYPE sock, SocketBuffer& buffer)
{
    long res, read = 0;

    do
    {
        res = ::read(sock, buffer.getBuffer() + read, buffer.getMaxSize() - read);
        if( res <= 0 ) {
            return res;
        }
        read += res;
    } while( read < static_cast<long>(buffer.getMaxSize()) );

    return read;
}



long
log4cplus::helpers::write(SOCKET_TYPE sock, const SocketBuffer& buffer)
{
#if defined(MSG_NOSIGNAL)
    int flags = MSG_NOSIGNAL;
#else
    int flags = 0;
#endif
     return ::send( sock, buffer.getBuffer(), buffer.getSize(), flags );
     // return ::write(sock, buffer.getBuffer(), buffer.getSize());
}


tstring
log4cplus::helpers::getHostname (bool fqdn)
{
    char const * hostname = "unknown";

#if defined (HAVE_GETHOSTNAME)
    int ret;
    size_t hn_size = 1024;
    char *hn = OFstatic_cast(char *, malloc(hn_size));

    while (true)
    {
        ret = ::gethostname (hn, hn_size - 1);
        if (ret == 0)
        {
            hostname = hn;
            break;
        }
#if defined (LOG4CPLUS_HAVE_ENAMETOOLONG)
        else if (ret != 0 && errno == ENAMETOOLONG)
        {
            // Our buffer was too short. Retry with buffer twice the size.
            hn_size *= 2;
            hn = OFstatic_cast(char *, realloc(hn, hn_size));
        }
#endif
        else
            break;
    }

    if (ret != 0 || (ret == 0 && ! fqdn))
    {
        tstring res = LOG4CPLUS_STRING_TO_TSTRING (hostname);
        free(hn);
        return res;
    }
#endif

#if defined (HAVE_GETHOSTBYNAME)
    struct ::hostent * hp = ::gethostbyname (hostname);
    if (hp)
        hostname = hp->h_name;
#endif

    tstring res = LOG4CPLUS_STRING_TO_TSTRING (hostname);
    free(hn);
    return res;
}
