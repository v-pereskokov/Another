#pragma once 

#include "Settings.hpp"
#include "Socket.h"

namespace pva
{
    using __socket__ = int;
    using __settings__ = Settings;

#pragma pack(push, 1)
    struct Socket_Node
    {
        using __socket_address_in__ = sockaddr_in;
        
    public:
        Socket_Node(const int, const int, const int, const __u_int__, std::string &, const __u_long__, const __flag__);
        
        Socket_Node() = default;
        
        ~Socket_Node();
        
    public:
        __socket__ socket_;
        __socket_address_in__ address_;
        __settings__ settings_;
        
    protected:
        void write_socket_address();
        
    private:
        Socket_Node(const __socket__, const __settings__);
        
        friend class Socket;

    };
#pragma pack(pop)
    
    char * string_to_pchar(const std::string &);
    
}
