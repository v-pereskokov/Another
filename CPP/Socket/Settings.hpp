#pragma once

#include "Settings.h"

namespace pva {
    
    Settings::Settings(const __domain__ domain, const __type__ type, const __protocol__ protocol, const __port__ port, __ip__ &ip, const __address__ address_ip, const __flag__ is_server)
    :_domain(domain), _type(type), _protocol(protocol), _port(port), _ip(ip), _address_ip(address_ip), _is_server(is_server) {}
    
}