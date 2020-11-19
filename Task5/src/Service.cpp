#include "Service.hpp"

namespace Tasks {

namespace net {

Service::Service(IServiceListener *listener) : listener_{listener} {}

void Service::setListener(IServiceListener *listener) {
    listener_ = listener;
}

void Service::open(const std::string &addr, uint16_t port) {
    server_.open(addr, port);
    epoll_.add(server_.get_fd(), EVENT_FLAG::RDW);
}

void Service::close() {
    server_.close();
}

void Service::closeConnection(const tcp::Connection &con) {
    epoll_.del(con.get_fd());
}

void Service::subscribeTo(const tcp::Connection &con, EVENT_FLAG flag) {
    epoll_.mod(con.get_fd(), flag);
}

void Service::unsubscribeFrom(const tcp::Connection &con, EVENT_FLAG flag) {
    epoll_.mod(con.get_fd(), flag);
}

void Service::run() {
    while (true) {
        std::vector<::epoll_event> event_vec = epoll_.wait(-1);
        for (::epoll_event &epevent : event_vec) {
            if (epevent.data.fd == server_.get_fd()) {
                connections_.emplace_back(this, server_.accept());
                epoll_.add(connections_.back().get_fd(), EVENT_FLAG::BASIC);
                listener_->onNewConnection(&(connections_.back()));
            } else {
                int fd = epevent.data.fd;
                std::_List_iterator<BufConnection> iter_client = std::find_if(connections_.begin(),
                        connections_.end(), [fd](BufConnection& client)
                                                { return client.get_fd() == fd; });
                if (epevent.events & EPOLLRDHUP) {
                    listener_->onClose(&*iter_client) ;
                    connections_.erase(iter_client);
                }
                if (epevent.events & EPOLLERR) {
                    listener_->onError(&*iter_client);
                }
                if (epevent.events & EPOLLIN) {
                    std::string buf(1024, '\0');
                    size_t len = iter_client->get_connection().read(buf.data(), buf.size());
                    buf.resize(len);
                    iter_client->get_read_buf() += buf;
                    if (len) {
                        listener_->onReadAvailable(&*iter_client);
                    } else {
                        listener_->onError(&*iter_client);
                    }
                }
                if (epevent.events & EPOLLOUT) {
                    std::string &write_buf = iter_client->get_write_buf();
                    if (!write_buf.empty()) {
                        size_t len = iter_client->get_connection().write(write_buf.data(), write_buf.size());
                        if (len) {
                            write_buf = write_buf.substr(len);
                        } else {
                            listener_->onError(&*iter_client);
                        }
                    }
                    if (write_buf.empty()) {
                        listener_->onWriteDone(&*iter_client);
                    }
                }
            }
        }
    }
}


} //namespace net

} //namespace Tasks