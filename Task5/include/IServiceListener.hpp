#ifndef TASKS_ISERVICE_H
#define TASKS_ISERVICE_H

#include "BufConnection.hpp"

namespace Tasks {

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

} //namespace Tasks

#endif