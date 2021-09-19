#ifndef PROJECT_ISERVICE
#define PROJECT_ISERVICE

#include "BufConnection.hpp"

namespace Project {

namespace net {

class BufConnection;

class IServiceListener {
public:
    virtual void onNewConnection(BufConnection *) = 0;
    virtual void onClose(BufConnection *) = 0;
    virtual void onWriteDone(BufConnection *) = 0;
    virtual void onReadAvailable(BufConnection *) = 0;
    virtual void onError(BufConnection *) = 0;
};

} //namespace net

} //namespace Project

#endif