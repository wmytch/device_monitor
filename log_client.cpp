#include "log_client.h"
#include "time.h"

void NetworkDispatcher::Init(std::string module,std::string proxy_proto,std::string proxy_host,unsigned short proxy_port,std::string local_host,zmq::context_t * p_context)
{
		auto pos=module.find_last_of("/");
		m_module=module.substr(pos==std::string::npos?0:pos+1);
		time_t now;
		struct tm* tm_now;
		char datetime[100];
		time(&now);
		tm_now=localtime(&now);
		strftime(datetime,100,"%Y%m%d-%H%M%S",tm_now);
		m_module=module+"_"+datetime;
		m_proxy_proto=proxy_proto;
		m_proxy_host=proxy_host;
		m_proxy_port=proxy_port;
		m_local_host=local_host;
		m_context=p_context;
    	m_requester=new zmq::socket_t(*m_context, ZMQ_DEALER);
		connect();
}	
void NetworkDispatcher::connect()
{
		std::stringstream connect_string;
		connect_string<<m_proxy_proto<<"://"<<m_proxy_host<<":"<<m_proxy_port;
    	m_requester->connect(connect_string.str());
}
void NetworkDispatcher::dispatch(el::base::type::string_t && logLine) noexcept 
{
		std::stringstream log_string;
		log_string<<m_local_host<<"|"<<m_module<<"|"<<getpid()<<"|"<<logLine.substr(0,logLine.length()-1);
        s_send(*m_requester,log_string.str());
}

