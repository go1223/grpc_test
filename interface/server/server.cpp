#include "server/server.h"
#include "grpc_gen/message.grpc.pb.h"
#include "grpcpp/grpcpp.h"
#include "server/message/message.h"

CGRPCServer::CGRPCServer(const std::string &port)
{
    m_messageServer = new CMessageServer();
    m_port = port;
}

CGRPCServer::~CGRPCServer()
{
    if (m_messageServer)
    {
        delete m_messageServer;
        m_messageServer = nullptr;
    }
    
}

bool CGRPCServer::RunServer()
{
    //创建服务构建对象
    ::grpc::ServerBuilder builder;
    //输入监听的ip地址和端口
    builder.AddListeningPort("[::]:"+m_port,grpc::InsecureServerCredentials());

    //将RPC服务注册到服务构建对象上
    builder.RegisterService(m_messageServer);
    //构造grpc服务对象
    std::unique_ptr <::grpc::Server> server(builder.BuildAndStart());
    std::cout<< "grpc server running ,listening port ["<< m_port.c_str() << "]" <<std::endl;
    //启动grpc服务
    server->Wait();
}