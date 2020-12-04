#ifndef TASKS_SERVICE_H
#define TASKS_SERVICE_H

#include "tcp.hpp"
#include <algorithm>
#include <list>


#include "IServiceListener.hpp"
#include "BufConnection.hpp"
#include "EPoll.hpp"
#include "Events.hpp"

namespace Tasks {

namespace net {

class EPoll;

class Service {
private:
    IServiceListener *listener_;
    std::list<BufConnection> connections_;
    tcp::Server server_;
    EPoll epoll_;
    
public:
    explicit Service(IServiceListener *);
    Service(const Service &);
    void setListener(IServiceListener *);
    void open(const std::string &, uint16_t);
    void close();
    void run();
    void closeConnection(const tcp::Connection &);
    void subscribeTo(const tcp::Connection &, EVENT_FLAG );
    void unsubscribeFrom(const tcp::Connection &, EVENT_FLAG );
};

} //namespace net

} //namespace Tasks

#endif