#ifndef __SERVER_H__
#define __SERVER_H__

#include "grpc_gen/message.grpc.pb.h"

class CMessageServer;
class CGRPCServer final
{
private:
    CMessageServer * m_messageServer;
    std::string m_port;
public:
    bool RunServer();
    CGRPCServer(const std::string &port);
    ~CGRPCServer();
};


#endif