#include "ServerConfig.h"
#include "ini.h"

CServerConfig CServerConfig::s_ServerConfig;

CServerConfig & CServerConfig::GetConfig()
{
    return s_ServerConfig;
}

CServerConfig::CServerConfig()
{
}

CServerConfig::~CServerConfig()
{

}

void CServerConfig::GetConfigFromFile()
{
    if (m_file_path.empty()) {
        return;
    }
    CIni ini;
    if (ini.OpenFile(m_file_path.c_str(), "r") == INI_SUCCESS) {
		m_client_num=ini.GetInt("common","client_num");

		m_proxy_proto=ini.GetStr("log_proxy","proxy_proto");
        m_proxy_ip= ini.GetStr("log_proxy", "proxy_ip");
        m_proxy_port= ini.GetInt("log_proxy", "proxy_port");
	
		m_server_ip=ini.GetStr("control_server","server_ip");
		m_server_port=ini.GetInt("control_server","server_port");
			
    }

    ini.CloseFile();

}
