#pragma once

#include "Socket_Node.h"

namespace pva {
    
    Socket_Node::Socket_Node(const int domain, const int type, const int protocol, const __u_int__ port, std::string &ip, const __u_long__ address_ip, const __flag__ is_server)
    :Socket_Node(socket(domain, type, protocol), __settings__(domain, type, protocol, port, ip, address_ip, is_server)) {}
    
    Socket_Node::~Socket_Node()
    {
        close(socket_);
    }
    
    Socket_Node::Socket_Node(const __socket__ socket, const __settings__ settings)
    :socket_(socket), settings_(settings)
    {
        write_socket_address();
    }
    
    void Socket_Node::write_socket_address()
    {
        address_.sin_family = settings_._domain;
        address_.sin_port = htons(settings_._port);
        address_.sin_addr.s_addr = settings_._is_server ? htons(settings_._address_ip) : inet_addr(string_to_pchar(settings_._ip));
    }
    
    char * string_to_pchar(const std::string &target)
    {
        return const_cast<char *>(target.c_str());
    }
    
}
