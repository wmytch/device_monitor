/*
*Usage: ./client Num Size Fps
*Num: the number of client [0-1000]
*Size: packet size 
*Fps: frame per second
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <memory.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <locale>
#include <iostream>
#include <sstream>
#include "csproto_generated.h"
#include "ServerConfig.h"
#include "log_client.h"
#pragma pack(1)

//init esaylogging 
INITIALIZE_EASYLOGGINGPP


int64_t time_get()
{
#if defined(WIN32) || defined(_WIN32)
    return (int64_t)GetTickCount64();
#elif defined(ANDROID)
   volatile struct timeval tv;    
   gettimeofday(&tv,NULL);    
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
#endif
}
unsigned long GetTickCount()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
typedef struct _csproto_header_t
{
    uint8_t     type;       // 协议类型
    uint8_t     subtype;    // 协议子类型
    uint32_t    len;        // 这里指定协议内容的长度，不包含此头
} csproto_header_t;
typedef struct Arg
{
	int id;
	int size;
	int fps;
}Argument;

int client_sockfd[1000];

void setid(char (*id)[20])
{
	 char filename[] = "/home/dedev/ycl/id.txt"; //文件名
	 FILE *fp; 
	 char StrLine[20];            //每行最大读取的字符数
	int i;
	 if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
	 { 
	 	LOG(INFO)<<"error!";
		exit(1); 
	 } 
	i = 0;
	 while (!feof(fp)) 
	 { 
	 	fgets(StrLine,20,fp);  //读取一行
	 	//i = 0;
		//LOG(INFO)<<"i:%d\n", i);
		memcpy(id + i, StrLine, sizeof(StrLine));
		//LOG(INFO)<<"idaddress:%d,id:%d, %s\n",id + i, i, id + i);
		//LOG(INFO)<<"stridaddress:%x,strid:%d, %s\n",id, i, strid[i][20]);	
		bzero(StrLine, 20);
		i = i + 1;
	 }
	 fclose(fp); 
}

void send_delay(const int fd)
{
				//发送delay
	int status;
	uint8_t * data_recv;
	size_t len_recv;
	int64_t curtime ;
	char buf[1024*1024*3];
	csproto_header_t header;
	char time_str[64] = {0};

	bzero(buf, 1024*1024*3);
	bzero(&header, sizeof(header));
	curtime = GetTickCount();
    snprintf(time_str, sizeof(time_str), "%lld", curtime);
	LOG(INFO)<<"time_str = "<<time_str;
    flatbuffers::FlatBufferBuilder builder_recv;
    flatbuffers::Offset<CSProto::ControlDelay> cd = CSProto::CreateControlDelayDirect(builder_recv, time_str);
    builder_recv.Finish(cd);
    data_recv = builder_recv.GetBufferPointer();
    len_recv = builder_recv.GetSize();
								
	header={1,2,(uint32_t)len_recv};
	memcpy(buf, &header, sizeof(header));
	memcpy(buf + sizeof(header), data_recv, (size_t)len_recv);
	LOG(INFO)<<"start to send delay";	
	status = send(fd, buf, sizeof(header) + (size_t)len_recv, 0) ;
	if(status == -1)
	{
		LOG(INFO)<<"send failed";
	}
	else
	LOG(INFO)<<"send success byte: "<<status;
}

void send_delay_r(const int fd, uint8_t * buffer)
{
	int status;
	csproto_header_t header;	
	const CSProto::ControlDelayR * fbsobj = flatbuffers::GetRoot<CSProto::ControlDelayR>(buffer + sizeof(header));
	int64_t time;
	int64_t time_now;
	int64_t time_scale;
	char time_str[64] = {0};
	uint8_t * data_recv;
	int64_t len_recv;

	time = atoll(fbsobj->time()->c_str());
	LOG(INFO)<<"get time ="<<time;
	time_now = GetTickCount();
	LOG(INFO)<<"time_now = "<<time_now;
	time_scale = time_now - time;
	LOG(INFO)<<"time_scale:"<<time_scale;
    snprintf(time_str, sizeof(time_str), "%lld", time_scale);
	
	bzero(&header, sizeof(header));
    flatbuffers::FlatBufferBuilder builder_recv;
    flatbuffers::Offset<CSProto::ControlDelay> cd = CSProto::CreateControlDelayDirect(builder_recv, time_str);
    builder_recv.Finish(cd);
    data_recv = builder_recv.GetBufferPointer();
    len_recv = builder_recv.GetSize();
		
	bzero(buffer, 1024*1024*3);
	header={1,3,(uint32_t)len_recv};
	memcpy(buffer, &header, sizeof(header));
	memcpy(buffer + sizeof(header), data_recv, (size_t)len_recv);
	LOG(INFO)<<"start to send delay_r";	
	LOG(INFO)<<"fd = "<<fd<<", send data_header ["<<header.type<<","<<header.subtype<<","<<header.len<<"]";
	status = send(fd, buffer, sizeof(header) + (size_t)len_recv, 0) ;
	if(status == -1)
	{
		LOG(INFO)<<"send failed";
	}
	else
		LOG(INFO)<<"send success byte:"<< status;
									
}

void send_av(const int fd, uint8_t * buffer)
{
		
				
	int n = 0;
	int status;
	uint64_t len;
	uint8_t buf[25606];
	uint8_t buf_a[1606];
	char data_a[1600] = {0};
	csproto_header_t header;
	char data[25600] = {0};
	int64_t time;
				
	//parse data
	const CSProto::ControlAVTrans * fbsobj = flatbuffers::GetRoot<CSProto::ControlAVTrans>(buffer + sizeof(header));
	LOG(INFO)<<"v:"<< fbsobj->video()<<" , a:"<<fbsobj->audio();
	if(fbsobj->video() == 1)
	{
		bzero(buf, 25606);
		bzero(&header, sizeof(header));
		len = sizeof(data);
		header={4, 1,(uint32_t) len};
		memcpy(buf, &header, sizeof(header));
		time = rand();
        snprintf(data, 64, "%lld", time);
		LOG(INFO)<<"data:"<< data;
		memcpy(buf + sizeof(header), data, 64);
		while((status = send(fd, buf, sizeof(header) + (size_t)len, 0)) ) 
		{
			if(status < 1)
			{
				LOG(INFO)<<"send failed";
				break;
			}
			else 
			{
				n += status;
				if ( n < 25600 + 6)
					continue;
				else 
					break;
			}
		}
			LOG(INFO)<<"send vedio len totally: "<< n;
	}
	n = 0;
	if( fbsobj->audio() == 1)
	{
		bzero(buf_a, 1606);
		bzero(&header, sizeof(header));
		len = sizeof(data_a);
		header={4, 0,(uint32_t) len};
		memcpy(buf_a, &header, sizeof(header));
		time = rand();
        snprintf(data_a, 64, "%lld", time);
		LOG(INFO)<<"data_a:"<< data_a;
		memcpy(buf + sizeof(header), data_a, 64);
		while((status = send(fd, buf_a, sizeof(header) + (size_t)len, 0)) ) 
		{
			if(status < 1)
			{
				LOG(INFO)<<"send failed";
				break;
			}
			else 
			{
				n += status;
				if ( n < 1600 + 6)
					continue;
				else 
					break;
			}
		}
		LOG(INFO)<<"send audio len totally:"<< n;
	}
}

void handle_input(const int fd, uint8_t  * buffer)
{
	csproto_header_t header;	
	const CSProto::InputTouch * fbsobj = flatbuffers::GetRoot<CSProto::InputTouch>(buffer + sizeof(header));

	LOG(INFO)<<"index : "<< fbsobj->index();
	if (fbsobj->index() > 0)
	{
		const flatbuffers::Vector<const CSProto::TouchInfo * > *touch = fbsobj->touch();
		LOG(INFO)<<"size: "<< touch->size();
		if (touch->size() > 0)
		{
			int x[touch->size()];// = { 0 };
			int y[touch->size()];// = { 0 };
			float force[touch->size()];// = { 0 };
			LOG(INFO)<<"input touch index:"<< fbsobj->index() <<" type: "<<fbsobj->type();//<<"    x : "<<x[i] <<"   y :"<<y[i] <<"    force :"<<  force;
			for (int i = 0; i < touch->size(); i++)
			{
				x[i] = touch->Get(i)->x();
				y[i] = touch->Get(i)->y();
				force[i] = touch->Get(i)->force();
				LOG(INFO)<<"x:"<<x[i]<<" y:"<<y[i]<<" f:"<< force[i];
			}
		}
	}
	else
	{
		LOG(INFO)<<"input touch else";
	}
}

void handle_input_keyboard(const int fd, uint8_t * buffer)
{
	const CSProto::InputKeyboard * fbsobj = flatbuffers::GetRoot<CSProto::InputKeyboard>(buffer + 6);
	LOG(INFO)<<"input key : "<<fbsobj->key()<<", presses :"<<  fbsobj->pressed();
}

void set_video_parameter(const int fd, uint8_t * buffer)
{
	const CSProto::ControlVideo * fbsobj = flatbuffers::GetRoot<CSProto::ControlVideo>(buffer + 6);
	LOG(INFO)<<"control video info    mode :"<< fbsobj->mode()<<"    bitrate :"<<fbsobj->bitrate() <<"		fps : "<< fbsobj->fps();
}
void send_dongdong(int sig)
{
	int i;	
	
	for( i= 0; i < 1; i++)
	{
		send_delay(client_sockfd[i]);
	}
	alarm(13);
}

bool send_H264_packet(int sock, unsigned int size, bool bIsKeyFrame)
{
	int len = size + 9;
	unsigned char *body = new unsigned char[len];
	
	size_t i = 0;

	if (bIsKeyFrame)
	{
		body[i++] = 0x02;// 1:Iframe  7:AVC  关键帧
	}
	else
	{
		body[i++] = 0x27;// 2:Pframe  7:AVC  
	}
	body[i++] = 0x01;// AVC NALU  
	body[i++] = 0x00;
	body[i++] = 0x00;
	body[i++] = 0x00;

	// NALU size  
	body[i++] = size >> 24;
	body[i++] = size >> 16;
	body[i++] = size >> 8;
	body[i++] = size & 0xff;;

	// NALU data  
	
	
	csproto_header_t av_header = {4, 1,(uint32_t) len};
	unsigned char *av_packet = new unsigned char[len + sizeof(av_header)];
	memset(av_packet,0,len + sizeof(av_header));
	memcpy(av_packet,&av_header,sizeof(av_header));
	memcpy(av_packet + sizeof(av_header),body,len);
	
	LOG(INFO)<<"sock id :"<<sock<< " body size :"<<len<<" , av_packet* size:"<< sizeof(av_packet)<<", length:"<<len + sizeof(av_header)<<" , size of header: "<< sizeof(av_header);
	
	int status = send(client_sockfd[sock], (char *)av_packet, (len + sizeof(av_header)), 0) ;
//	perror
	if(status <= 0)
	{
//		LOG(INFO)<<"av_packet send failed: %d\n", status);
		LOG(ERROR)<<"av_packet send failed:"<<strerror(errno);
		delete[] body;
		delete[] av_packet;
		return false;
	}
	else
	{
		LOG(INFO)<<"av_packet send success byte: "<< status;
		delete[] body;
		delete[] av_packet;
		return true;
	}

}

///////////////////////////////////////
int opts;
uint8_t* buf;  //数据传送的缓冲区
char strid[1000][20];
char pad_code[15]={0};
struct epoll_event ev,events[1000];	
csproto_header_t header;
csproto_header_t *header_recv;

int epfd;
////////////////////////////////////////
bool connect_control_server(int i,struct sockaddr_in& remote_addr)
{
		int status;
		int client_sockfd;
		if(( client_sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			LOG(ERROR)<<"socket create error!"<<strerror(errno);
			return false;
		}
		LOG(INFO)<<"connect control server :["<<remote_addr.sin_addr.s_addr<<":"<<remote_addr.sin_port<<"]";
		/*将套接字绑定到服务器的网络地址上*/
		if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
		{
			LOG(ERROR)<<"connect error!";
			return false;
		}
		LOG(INFO)<<"client:" << client_sockfd <<" connected to server";
		bzero(buf, 1024*1024*3);
		//pad_code = &strid[i][20];
		memcpy(pad_code, strid[i], 14);
		LOG(INFO)<<"pad_code :"<< pad_code;
		flatbuffers::FlatBufferBuilder builder;
		flatbuffers::Offset<CSProto::ShakeOnline> fbs = CSProto::CreateShakeOnlineDirect(builder, pad_code);
		builder.Finish(fbs);
		uint8_t * data = builder.GetBufferPointer();
		uint32_t len = builder.GetSize();
			LOG(INFO)<<"len_data:"<< len;
		/*******************
		*Testing part
		*********************/
	//		char* data = "fuck ,work overtime once again";
	//		uint32_t len = strlen(data);
		/*******************
		*Testing part
		*********************/
		header ={(uint8_t)0, (uint8_t)0, len};
		memcpy(buf, &header, sizeof(header));
		memcpy(buf + sizeof(header), data, (size_t)len);
		status = send(client_sockfd, buf, sizeof(header) + (size_t)len, 0) ;
		if(status == -1)
		{
			LOG(INFO)<<"shake send failed:"<<strerror(errno);
			return false;
		}
		else
			LOG(INFO)<<"shake send success byte:"<<  status;
		status=recv(client_sockfd,buf,sizeof(header),MSG_WAITALL);
		if(status!=sizeof(header))
		{
			LOG(ERROR)<<"recv shake hand header error";	
			return false;
		}
		status=recv(client_sockfd,buf,header.len,MSG_WAITALL);
		if(status!=header.len)
		{
			LOG(ERROR)<<"recv shake hand body error";	
			return false;
		}
		LOG(INFO)<<"shake hand success.";
	
		//设置非阻塞
		opts = fcntl (client_sockfd, F_GETFL);
		if (opts < 0)
		{
			LOG(ERROR)<<"fcntl(F_GETFL)";
			return false;
		}
		opts = (opts | O_NONBLOCK);
		if (fcntl (client_sockfd, F_SETFL, opts) < 0)
		{
			LOG(ERROR)<<"fcntl(F_SETFL)";
			return false;
		}

		//使用epoll监控所有fd
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = client_sockfd;
		if (epoll_ctl (epfd, EPOLL_CTL_ADD, client_sockfd, &ev) == -1)
		{
			LOG(ERROR)<<"epoll_ctl: client_sockfd";
			return false;
		}
		return true;
}
#if 0
void* impersonate_client(void* arg)
{
	//int i, int size, int frame_per_sec
//	pthread_detach(pthread_self());
	
	Argument* info = (Argument*)arg;
	int i = info->id;
//	int size = info->size;
//	int frame_per_sec = info->fps;
	
#if 0
//Ignore signal.
	sigset_t mask;
	sigfillset(&mask);
	int err = pthread_sigmask(SIG_BLOCK, &mask, NULL);
	if (err != 0)
		LOG(INFO)<<"%s pthread_sigmask error: %d .", i, err);
#endif	
	
//	while(1)
	{
		/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
		if((client_sockfd[i]=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			perror("socket create error!");
			//pthread_exit(0); ;
			return false;
		}
		/*将套接字绑定到服务器的网络地址上*/
		if(connect(client_sockfd[i],(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
		{
			perror("connect error!");
			return false;
			//pthread_exit(0); ;
		}
		//发送id到control端
		bzero(buf, 1024*1024*3);
		LOG(INFO)<<"client: %d connected to server\n" , client_sockfd[i]);
		//pad_code = &strid[i][20];
		memcpy(pad_code, strid[i], 14);
		LOG(INFO)<<"pad_code : %s\n", pad_code);
		flatbuffers::FlatBufferBuilder builder;
		flatbuffers::Offset<CSProto::ShakeOnline> fbs = CSProto::CreateShakeOnlineDirect(builder, pad_code);
		builder.Finish(fbs);
		uint8_t * data = builder.GetBufferPointer();
		uint32_t len = builder.GetSize();
			LOG(INFO)<<"len_data:%d\n", len);
		/*******************
		*Testing part
		*********************/
	//		char* data = "fuck ,work overtime once again";
	//		uint32_t len = strlen(data);
		/*******************
		*Testing part
		*********************/
		header ={(uint8_t)0, (uint8_t)0, len};
		LOG(INFO)<<"header len:%d\n", sizeof(header));
		memcpy(buf, &header, sizeof(header));
		//LOG(INFO)<<"buf_headerlen:%d\n", sizeof(buf));
		memcpy(buf + sizeof(header), data, (size_t)len);
		status = send(client_sockfd[i], buf, sizeof(header) + (size_t)len, 0) ;
		if(status == -1)
		{
			LOG(INFO)<<"shake send failed\n");
		}
		else
			LOG(INFO)<<"shake send success byte: %d\n", status);

	
		//设置非阻塞
		opts = fcntl (client_sockfd[i], F_GETFL);
		if (opts < 0)
		{
			perror ("fcntl(F_GETFL)\n");
			return false;
		//	pthread_exit(0);;
		}
		opts = (opts | O_NONBLOCK);
		if (fcntl (client_sockfd[i], F_SETFL, opts) < 0)
		{
			perror ("fcntl(F_SETFL)\n");
			return false;
		//	pthread_exit(0);;
		}

		//使用epoll监控所有fd
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = client_sockfd[i];
		if (epoll_ctl (epfd, EPOLL_CTL_ADD, client_sockfd[i], &ev) == -1)
		{
			perror ("epoll_ctl: client_sockfd");
			return false;
		//	pthread_exit(0);;
		}
#if 0	
		
		while(1)
		{
			unsigned long StartEncodeTime = GetTickCount();
			
			if((send_H264_packet(i, size, 1)) <= 0)
			{
				close(client_sockfd[i]);
				break;
			}
			
			unsigned long TOPF = 1000/ frame_per_sec;//Time of per frame
			unsigned long ProcessTime = GetTickCount() - StartEncodeTime;
			if(ProcessTime < TOPF -1)
			{
				struct timeval delay;
				delay.tv_sec = 0;
				delay.tv_usec = (TOPF - ProcessTime -1)*1000;
				select(0,NULL,NULL,NULL,&delay);
			}
		}
#endif	
	}
//	LOG(INFO)<<"client :%d exit\n", i);
//	pthread_exit(0);
}
#endif

int main(int argc, char* argv[])
{
	signal(SIGPIPE,SIG_IGN);
	//int client_sockfd[1000];  
    zmq::context_t context(1);
	char hname[128];
    struct hostent *hent;

	gethostname(hname, sizeof(hname));
	hent = gethostbyname(hname);
	std::string native_ip{inet_ntoa(*(struct in_addr*)(hent->h_addr_list[0]))};

    CServerConfig::GetConfig().SetConfigFile("./config.ini");
    CServerConfig::GetConfig().GetConfigFromFile();

    std::string proxy_proto=CServerConfig::GetConfig().GetProxyProto();
	std::string proxy_ip=CServerConfig::GetConfig().GetProxyIP();
	unsigned short proxy_port=CServerConfig::GetConfig().GetProxyPort();

	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.setGlobally(el::ConfigurationType::Format, "[%level|%datetime %thread %file:%line] %msg"); 
	defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "true"); 
	el::Loggers::reconfigureLogger("default", defaultConf);

    el::Helpers::installLogDispatchCallback < NetworkDispatcher >
      ("NetworkDispatcher");
    NetworkDispatcher *dispatcher =
      el::Helpers::logDispatchCallback < NetworkDispatcher >
      ("NetworkDispatcher");
    dispatcher->setEnabled(true);
	dispatcher->Init(argv[0],proxy_proto,proxy_ip,proxy_port,native_ip,&context);
	

	buf = (uint8_t *)malloc(3 * 1024 * 1024);
	bzero(buf, sizeof(buf));

	struct sockaddr_in remote_addr; //服务器端网络地址结构体
	bzero(&remote_addr, sizeof(remote_addr));
	remote_addr.sin_family=AF_INET; //设置为IP通信
	remote_addr.sin_addr.s_addr=inet_addr(CServerConfig::GetConfig().GetServerIP().c_str());//服务器IP地址
	remote_addr.sin_port=htons(CServerConfig::GetConfig().GetServerPort()); //服务器端口号	

	bzero(strid, sizeof(strid));
	setid(strid);//设置id
	
	int num_of_client = CServerConfig::GetConfig().GetClientNum();
	num_of_client=num_of_client>1000?1000:num_of_client;
	epfd=epoll_create(num_of_client);//生成用于处理accept的epoll专用的文件描述符
	for(auto i=0;i<num_of_client;++i)
	{
		auto result=connect_control_server(i,remote_addr);
		if(!result)
		{
			LOG(ERROR)<<"connect control server error:["<<remote_addr.sin_addr.s_addr<<":"<<remote_addr.sin_port<<"]";
			exit(-1);
		}
	}
/*
	Argument arg ;
	pthread_t thr_fd[1000];
	for(auto i = 0; i < num_of_client; i++)
	{
	//	arg = {i, av_size, arg_fps};
		arg = {i, 0, 0};
		
		int Ret = pthread_create(&thr_fd[i],NULL,impersonate_client,(void *)&arg);
		if(Ret != 0)
			LOG(INFO)<<"client[i] create failed\n");
		//impersonate_client(i, argv[2], argv[3]);
	}
//	signal(SIGALRM, send_dongdong);
//	alarm(13);
*/	
	//循环等待control端发回消息
	int nfds;
	int   n;
	int readfd;
	int nread;
	while(1)
	{
		LOG(INFO)<<"epoll waiting";
		nfds = epoll_wait (epfd, events, 1000, -1);

		if (nfds == -1)  
     	{  
        	if (errno == EINTR)  
          	{  
             	continue;  
          	}  
          	else  
          	{  
              	LOG(INFO)<<"epoll_wait error, "<<strerror (errno);  
              	break;  
          	}  
     	}  
		LOG(INFO)<<"nfds:"<<nfds;
		LOG(INFO)<<"epoll wait successfully";
		for (auto i = 0; i < nfds; i++)
		{
			LOG(INFO)<<"i:"<<i;	
			readfd = events[i].data.fd;		
			if (events[i].events & EPOLLIN)//读
            {
				n = 0;
				//接收协议头
				while ((nread = recv(readfd, buf+n, 6-n, 0)) )
				{
					if(nread == -1)
					{
						LOG(INFO)<<"recv error, nread:"<<nread;
						break;
					}
					if(nread == 0)
					{
						LOG(INFO)<<"no more data, nread= "<<nread;
						break;
					}	
					//else
					//	n += nread;
					else
					{
						n += nread;
						if ( n < 6)
							continue;
						else 
							break;
					}
				}
				//n += nread;
				//memcpy(header_recv, buf, sizeof(*header_recv));
				header_recv = (csproto_header_t *)buf;
				bzero(&header, sizeof(header));
				memcpy(&header, header_recv, sizeof(*header_recv));
				LOG(INFO)<<"event = "<< events[i].events<<" on fd ="<< events[i].data.fd<<" , recv data_header ["<<header_recv->type<<","<<header_recv->subtype<<","<<header_recv->len<<"], n:"<<n;
			

			//LOG(INFO)<<"header.type:%d\n",header.type);
				//接收协议体	
				int m = 0;
				while((nread = recv(readfd, buf + n, header.len, 0)) )
				{	
					if(nread == -1)
					{
						LOG(INFO)<<"recv error, nread:"<<nread;
						break;
					}
					if(nread == 0)
					{
						LOG(INFO)<<"no more data, nread= "<<nread;
						break;
					}	
					else
					{
						m += nread;
						if ( m < header.len)
							continue;
						else 
							break;
					}
				}
				//n += nread;
				LOG(INFO)<<"event = "<<events[i].events<< " on fd =" <<events[i].data.fd <<" recv header_len + data_len ["<<n + m<<"]";
				LOG(INFO)<<"header.type:"<<header.type;
				if(header.type == 0 )
				{
					send_delay(events[i].data.fd);
				}  
				else if ( header.type == 1 )
				{
					LOG(INFO)<<"header.subtype:"<<header.subtype;
					if(header.subtype == 2)
					{		
						send_delay_r(events[i].data.fd, buf);
					}
					else if (header.subtype == 16)
					{
						LOG(INFO)<<"header.subtype :"<<header.subtype<<" continued to send delay.";	
					}
					else if (header.subtype == 8)
					{
						//LOG(INFO)<<"header.subtype :%d,continued to send delay.\n",header.subtype);	
						LOG(INFO)<<"connection :"<<i<<" start to send av.";
						for(auto j = 0; j < 20; j++)
						{
							//LOG(INFO)<<"send i times\n");
							send_av(events[i].data.fd, buf); 
							sleep(0.05);
						}
					}	
					else if( header.subtype == 13)
					{
						LOG(INFO)<<"header.subtype :"<<header.subtype<<" set video parameter.";	
						set_video_parameter(events[i].data.fd, buf);
					}
				}
				else if( header.type == 2)
				{
					LOG(INFO)<<"input of header.subtype : "<<header.subtype;
					if(header.subtype == 200)
					{
						//handle input touch, just printf
						handle_input(events[i].data.fd, buf);
					}
					else if (header.subtype ==100)
					{
						handle_input_keyboard(events[i].data.fd, buf);
					}
				}	
			}
			else if(events[i].events&EPOLLERR)
            {  
           
				LOG(INFO)<<"epoll  fd  error";	
			}  
			else
				LOG(INFO)<<" epoll recv abnormal";
		}
	}
	
	return 0;
}

