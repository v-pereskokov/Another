#pragma once

namespace pva {
    
    using __flag__ = bool;
    using __u_int__ = unsigned int;
    using __u_long__ = unsigned long;
    
#pragma pack(push, 1)
    struct Settings
    {
        using __domain__ = int;
        using __type__ = int;
        using __protocol__ = int;
        using __port__ = __u_int__;
        using __ip__ = std::string;
        using __address__ = __u_long__;
        
    public:
        Settings(const __domain__, const __type__, const __protocol__, const __port__, __ip__ &, const __address__, const __flag__);
        
        Settings() = default;
        
        ~Settings() noexcept = default;
        
        void operator =(const Settings &) = delete;
        
    public:
        __domain__ _domain;
        __type__ _type;
        __protocol__ _protocol;
        __port__ _port;
        __ip__ _ip;
        __address__ _address_ip;
        __flag__ _is_server;
    };
#pragma pack(pop)
    
}