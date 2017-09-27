#ifndef __LOG_CLIENT_H__
#define __LOG_CLIENT_H__

#include "easylogging++.h"
#include "zhelpers.hpp"

class NetworkDispatcher:public el::LogDispatchCallback {
  public:
	NetworkDispatcher(){}
	~NetworkDispatcher(){}

	void Init(std::string module,std::string proxy_proto,std::string proxy_host,unsigned short proxy_port,std::string local_host,zmq::context_t * p_context);
	void connect();
  protected:
    void handle(const el::LogDispatchData * data) noexcept override
	{
        m_data = data;
        dispatch(m_data->logMessage()->logger()->logBuilder()->
                 build(m_data->logMessage(),
                       m_data->dispatchAction() ==
                       el::base::DispatchAction::NormalLog));
	}
  private:
    const el::LogDispatchData * m_data;
    std::string m_proxy_host;
	std::string m_proxy_proto;
    unsigned short m_proxy_port;
    std::string m_local_host;
	std::string m_module;
	zmq::context_t* m_context;
	zmq::socket_t* m_requester;

    void dispatch(el::base::type::string_t && logLine) noexcept;
};

#endif
