#pragma once

#include "Socket.h"

namespace pva
{
    
    Socket::Socket(const int domain, const int type, const int protocol, const __u_int__ port, std::string &ip, const __u_long__ address_ip, const __flag__ is_server)
    :Socket(__socket_node__(domain, type, protocol, port, ip, address_ip, is_server), false)
    {
        connection();
    }
        
    Socket::Socket(const __socket_node__ node, const __flag__ is_connect)
        :_in(node), _is_connect(is_connect) {}
    
    void Socket::connection()
    {
        if (bind(_in.socket_, reinterpret_cast<__socket_address__  *>(&_in.address_), sizeof(_in.address_)) < 0)
            throw std::logic_error("Error");
    }
    
}
