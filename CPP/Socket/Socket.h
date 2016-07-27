#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Socket_Node.hpp"

namespace pva {
    
#pragma pack(push, 1)
    class Socket
    {
        using __socket_node__ = Socket_Node;
        using __socket_address__ = sockaddr;
        
    public:
        Socket(const int, const int, const int, const __u_int__, std::string &, const __u_long__, const __flag__);
        
        ~Socket() noexcept = default;
        
        void operator =(const Socket &rhs) = delete;
        
    private:
        Socket(const __socket_node__, const __flag__);
        
        void connection();
        
    private:
        __socket_node__ _in;
        __socket_node__ _out;
        __flag__ _is_connect;
    };
#pragma pack(pop)
    
}
