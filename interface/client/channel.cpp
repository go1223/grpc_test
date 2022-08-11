#include "client/channel.h"


CGRPCChannel::CGRPCChannel(const time_t &timeout)
{
    this->n_timeout = timeout;
}

CGRPCChannel::~CGRPCChannel()
{
}

bool CGRPCChannel::GetChannel(const std::string &conn,std::shared_ptr<grpc::ChannelInterface> & channel)
{
    gpr_timespec tm_out{n_timeout,0,GPR_TIMESPAN};
    std::lock_guard<std::mutex> lock(m_mutex);
   
    if(m_channels.find(conn) == m_channels.end())
    {
        //说明没找到,需要建立通道
        //grpc::ChannelArguments args;
        m_channels[conn] = grpc::CreateChannel(conn,::grpc::InsecureChannelCredentials());
    }
   channel = m_channels[conn];
   if(channel->WaitForConnected(tm_out))
   {
        return true;
   }
   else
   {
        return false;
   }

}

