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
#include <sys/epoll.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <locale>
#include "ServerConfig.h"
#include "device_func.h"
#pragma pack(1)

//init esaylogging 
INITIALIZE_EASYLOGGINGPP 

std::vector<std::string> strid;
std::vector<int> client_sockfd;
struct epoll_event ev, events[1000];
int epfd;
int heart_beat;
/*
 * heartbeat
 */
void send_dongdong(int sig)
{
    for (auto sockfd:client_sockfd) 
        control_delay(sockfd);
    alarm(heart_beat);
}
bool connect_control_server(int i, struct sockaddr_in &remote_addr)
{
    int status;
	int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        LOG(ERROR) << "socket create error!" << strerror(errno);
        return false;
    }
    LOG(INFO) << "connect control server :[" << remote_addr.sin_addr.
      s_addr << ":" << remote_addr.sin_port << "]";
    if (connect
        (fd, (struct sockaddr *) &remote_addr,
         sizeof(struct sockaddr)) < 0) {
        LOG(ERROR) << "connect to control server error:"<<strerror(errno);
        return false;
    }
	client_sockfd.push_back(fd);
    LOG(INFO) << "client:" << i << " connected to server";
	if(shake_online(fd,i))
	{
		LOG(INFO) << "client:" << i << " send shake online to server success.";
	}
	else
	{
		LOG(INFO) << "client:" << i << " send shake online to server failed.";
		return false;	
	}
    auto opts = fcntl(fd, F_GETFL);
    if (opts < 0) {
        LOG(ERROR) << "fcntl(F_GETFL)";
        return false;
    }
    opts = (opts | O_NONBLOCK);
    if (fcntl(fd, F_SETFL, opts) < 0) {
        LOG(ERROR) << "fcntl(F_SETFL)";
        return false;
    }
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD,fd, &ev) == -1) {
        LOG(ERROR) << "epoll_ctl add client_sockfd:"<<fd;
        return false;
    }
	return true;
}


int main(int argc, char *argv[]) 
{
    signal(SIGPIPE, SIG_IGN);
    zmq::context_t context(1);

    CServerConfig::GetConfig().SetConfigFile("./config.ini");
    CServerConfig::GetConfig().GetConfigFromFile();

    std::string proxy_proto = CServerConfig::GetConfig().GetProxyProto();
    std::string proxy_ip = CServerConfig::GetConfig().GetProxyIP();
    unsigned short proxy_port = CServerConfig::GetConfig().GetProxyPort();

    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::Format,
                            "%level|%datetime %thread %file:%line] %msg");
    defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "true");
    el::Loggers::reconfigureLogger("default", defaultConf);
    el::Helpers::installLogDispatchCallback < NetworkDispatcher >
      ("NetworkDispatcher");
    NetworkDispatcher *dispatcher =
      el::Helpers::logDispatchCallback < NetworkDispatcher >
      ("NetworkDispatcher");
    dispatcher->setEnabled(true);

    char hname[128];
    gethostname(hname, sizeof(hname));
    struct hostent *hent = gethostbyname(hname);
    std::string native_ip {inet_ntoa(*(struct in_addr *) (hent->h_addr_list[0]))};
    dispatcher->Init(argv[0], proxy_proto, proxy_ip, proxy_port, native_ip,
                     &context);

    struct sockaddr_in remote_addr;     //服务器端网络地址结构体
    remote_addr.sin_family = AF_INET;   //设置为IP通信
    remote_addr.sin_addr.s_addr = inet_addr(CServerConfig::GetConfig().GetServerIP().c_str());  //服务器IP地址
    remote_addr.sin_port = htons(CServerConfig::GetConfig().GetServerPort());   //服务器端口号  

    int num_of_client = CServerConfig::GetConfig().GetClientNum();
    num_of_client = num_of_client > 1000 ? 1000 : num_of_client;
    epfd = epoll_create(num_of_client); //生成用于处理accept的epoll专用的文件描述符

    set_device_id(strid);               //设置id
    for (auto i = 0; i < num_of_client; ++i) {
        auto result = connect_control_server(i, remote_addr);
        if (!result) {
            LOG(ERROR) << "client ["<<i<<"] connect control server error:[" <<CServerConfig::GetConfig().GetServerIP()
              << ":" << CServerConfig::GetConfig().GetServerPort() << "]";
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
*/
    //循环等待control端发回消息
		
	heart_beat=CServerConfig::GetConfig().GetHeartBeat();
	signal(SIGALRM, send_dongdong);
	alarm(heart_beat);

    int nfds;
    int n;
    int readfd;
    int nread;
    uint8_t buffer[3 * 1024 * 1024]={0};
	csproto_header_t header;
    while (1) 
	{
        LOG(INFO) << "epoll waiting";
        nfds = epoll_wait(epfd, events, 1000, -1);
        if (nfds == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                LOG(INFO) << "epoll_wait error, " << strerror(errno);
                break;
            }
        }

        LOG(INFO) << "nfds:" << nfds;
        LOG(INFO) << "epoll wait successfully";
        for (auto i = 0; i < nfds; i++) {
            readfd = events[i].data.fd;
            if (events[i].events & EPOLLIN)
            {
                n = 0;
                while ((nread = recv(readfd, buffer + n, 6 - n, 0))) 
				{
                    if (nread == -1) {
                        LOG(INFO) << "recv header error:"<<strerror(errno);
                        break;
                    }
                    if (nread == 0) {
                        LOG(INFO) << "recv header:no more data." ;
                        break;
                    }
                    else 
					{
                        n += nread;
                        if (n < 6)
                            continue;
                        else
                            break;
                    }
                }
                memcpy(&header, buffer, sizeof(header));
                int m = 0;
                while ((nread = recv(readfd, buffer +sizeof(header) , header.len, 0)))
				{
                    if (nread == -1) 
					{
                        LOG(INFO) << "recv body error :" << strerror(errno);
                        break;
                    }
                    if (nread == 0) {
                        LOG(INFO) << "recv body :no more data." ;
                        break;
                    } else {
                        m += nread;
                        if (m < header.len)
                            continue;
                        else
                            break;
                    }
                }
                LOG(INFO) << "type:" <<(int) header.type<<" subtype:"<<(int)header.subtype;
				switch(header.type)
				{
					case MSG_SHAKE:
					{
						switch(header.subtype)
						{
							/*
							case MSG_SHAKE_ONLINE:
							{
								shake_online(readfd);
								break;	
							}
							*/
							case MSG_SHAKE_ONLINE_R:
							{
								shake_online_r(buffer);
								break;	
							}
							/*
							case MSG_SHAKE_OFFLINE:
							{
								shake_offline(readfd,);
								break;	
							}
							*/
							case MSG_SHAKE_OFFLINE_R:
							{
								shake_offline_r(buffer);
								break;	
							}
							case MSG_SHAKE_KICK:
							{
								shake_kick(readfd);
								break;	
							}
						}
						break;	
					}
					case MSG_CONTROL:
					{
						switch(header.subtype)
						{
							case MSG_CONTROL_MTU:
							{
								control_mtu(readfd);
								break;	
							}
							case MSG_CONTROL_MTU_R:
							{
								control_mtu_r(readfd);
								break;	
							}
							case MSG_CONTROL_DELAY:
							{
								control_delay_r(readfd,buffer);
								break;	
							}
							/*
							case MSG_CONTROL_DELAY_R:
							{
								control_delay_r(readfd,buffer);
								break;	
							}
							*/
							case MSG_CONTROL_APP:
							{
								control_app(readfd);
								break;	
							}
							case MSG_CONTROL_APP_R:
							{
								control_app_r(readfd);
								break;	
							}
							case MSG_CONTROL_AVFMT:
							{
								control_avfmt(readfd);
								break;	
							}
							case MSG_CONTROL_AVFMT_R:
							{
								control_avfmt_r(readfd);
								break;	
							}
							case MSG_CONTROL_AVTRANS:
							{
								control_avtrans(readfd,buffer);
								break;	
							}
							case MSG_CONTROL_AVTRANS_R:
							{
								control_avtrans_r(readfd);
								break;	
							}
							case MSG_CONTROL_IFRAME:
							{
								control_iframe(readfd);
								break;	
							}
							case MSG_CONTROL_AUDIO:
							{
								control_audio(readfd);
								break;	
							}
							case MSG_CONTROL_AUDIO_R:
							{
								control_audio_r(readfd);
								break;	
							}
							case MSG_CONTROL_VIDEO:
							{
								control_video(readfd,buffer);
								break;	
							}
							/*
							case MSG_CONTROL_VIDEO_R:
							{
								control_video_r(readfd);
								break;	
							}
							*/
							case MSG_CONTROL_TIME:
							{
								control_time(readfd);
								break;	
							}
							case MSG_CONTROL_SCREEN:
							{
								control_screen(readfd);
								break;	
							}
							case MSG_CONTROL_KILL_APP:
							{
								control_kill_app(readfd);
								break;	
							}
							case MSG_CONTROL_KILL_APP_R:
							{
								control_kill_app_r(readfd);
								break;	
							}
							case MSG_CONTROL_RESOLUTIONLEVEL:
							{
								control_resolutionlevel(readfd);
								break;	
							}
							case MSG_CONTROL_QUERYAUTH:
							{
								control_queryauth(readfd);
								break;	
							}
							case MSG_CONTROL_QUERYAUTH_R:
							{
								control_queryauth_r(readfd);
								break;	
							}
						}
						break;	
					}
					case MSG_INPUT:
					{
						switch(header.subtype)
						{
							case MSG_INPUT_STRING:
							{
								input_string(readfd);
								break;	
							}
							case MSG_INPUT_GAMECONTROLLER:
							{
								input_gamecontroller(readfd);
								break;	
							}
							case MSG_INPUT_KEYBOARD:
							{
								input_keyboard(buffer);
								break;	
							}
							case MSG_INPUT_MOUSE_KEY:
							{
								input_mouse_key(readfd);
								break;	
							}
							case MSG_INPUT_MOUSE_WHEEL:
							{
								input_mouse_wheel(readfd);
								break;	
							}
							case MSG_INPUT_MOUSE_MOVE:
							{
								input_mouse_move(readfd);
								break;	
							}
							case MSG_INPUT_CURSOR:
							{
								input_cursor(readfd);
								break;	
							}
							case MSG_INPUT_TOUCH:
							{
								input_touch(buffer);
								break;	
							}
							case MSG_INPUT_LOCATION:
							{
								input_location(readfd);
								break;	
							}
							case MSG_INPUT_ACCELEROMETER:
							{
								input_accelerometer(readfd);
								break;	
							}
							case MSG_INPUT_ALTIMETER:
							{
								input_altimeter(readfd);
								break;	
							}
							case MSG_INPUT_GYRO:
							{
								input_gyro(readfd);
								break;	
							}
							case MSG_INPUT_MAGNETOMETER:
							{
								input_magnetometer(readfd);
								break;	
							}
							case MSG_INPUT_PEDOMETER:
							{
								input_pedometer(readfd);
								break;	
							}
							case MSG_INPUT_PROXIMITY:
							{
								input_proximity(readfd);
								break;	
							}
							case MSG_INPUT_AMBIENTLIGHT:
							{
								input_ambientlight(readfd);
								break;	
							}
							case MSG_INPUT_TEMPERATURE:
							{
								input_temperature(readfd);
								break;	
							}
							case MSG_INPUT_MOISTURE:
							{
								input_moisture(readfd);
								break;	
							}
						}
						break;	
					}
					case MSG_OUTPUT:
					{
						switch(header.subtype)
						{
							case MSG_OUTPUT_STRING:
							{
								output_string(readfd);
								break;	
							}
							case MSG_OUTPUT_SCREEN:
							{
								output_screen(readfd);
								break;	
							}
							case MSG_OUTPUT_VIBRATION:
							{
								output_vibration(readfd);
								break;	
							}
							case MSG_OUTPUT_CURSOR:
							{
								output_cursor(readfd);
								break;	
							}
						}
						break;	
					}
					case MSG_AV:
					{
						switch(header.subtype)
						{
							case MSG_AV_AUDIO:
							{
								av_audio(readfd);
								break;	
							}
							case MSG_AV_VIDEO:
							{
								av_video(readfd);
								break;	
							}
							case MSG_AV_SUBTITLE:
							{
								av_subtitle(readfd);
								break;	
							}
							case MSG_AV_CLIENT_AUDIO:
							{
								av_client_audio(readfd);
								break;	
							}
							case MSG_AV_CLIENT_VIDEO:
							{
								av_client_video(readfd);
								break;	
							}
							case MSG_AV_CLIENT_SUBTITLE:
							{
								av_client_subtitle(readfd);
								break;	
							}
						}
						break;	
					}
					case MSG_AUTH:
					{
						switch(header.subtype)
						{
							case MSG_AUTH_LIST:
							{
								auth_list(readfd);
								break;	
							}
						}
						break;	
					}
				}
#if 0
                if (header.type == 0) {
                    send_delay(events[i].data.fd);
                } else if (header.type == 1) {
                    LOG(INFO) << "header.subtype:" << header.subtype;
                    if (header.subtype == 2) {
                        send_delay_r(events[i].data.fd, buf);
                    } else if (header.subtype == 16) {
                        LOG(INFO) << "header.subtype :" << header.
                          subtype << " continued to send delay.";
                    } else if (header.subtype == 8) {
                        //LOG(INFO)<<"header.subtype :%d,continued to send delay.\n",header.subtype);   
                        LOG(INFO) << "connection :" << i <<
                          " start to send av.";
                        for (auto j = 0; j < 20; j++) {
                            //LOG(INFO)<<"send i times\n");
                            send_av(events[i].data.fd, buf);
                            sleep(0.05);
                        }
                    } else if (header.subtype == 13) {
                        LOG(INFO) << "header.subtype :" << header.
                          subtype << " set video parameter.";
                        set_video_parameter(events[i].data.fd, buf);
                    }
                } else if (header.type == 2) {
                    LOG(INFO) << "input of header.subtype : " << header.subtype;
                    if (header.subtype == 200) {
                        //handle input touch, just printf
                        handle_input(events[i].data.fd, buf);
                    } else if (header.subtype == 100) {
                        handle_input_keyboard(events[i].data.fd, buf);
                    }
                }
#endif
            } else if (events[i].events & EPOLLERR) {

                LOG(INFO) << "epoll  fd  error";
            } else
                LOG(INFO) << " epoll recv abnormal";
        }
    }

    return 0;
}
#if 0
void set_video_parameter(const int fd, uint8_t * buffer)
{
    const CSProto::ControlVideo * fbsobj =
      flatbuffers::GetRoot < CSProto::ControlVideo > (buffer + 6);
    LOG(INFO) << "control video info mode :" << fbsobj->
      mode() << "    bitrate :" << fbsobj->
      bitrate() << "		fps : " << fbsobj->fps();
}
void *impersonate_client(void *arg)
{
    //int i, int size, int frame_per_sec
//      pthread_detach(pthread_self());

    Argument *info = (Argument *) arg;
    int i = info->id;
//      int size = info->size;
//      int frame_per_sec = info->fps;

#if 0
//Ignore signal.
    sigset_t mask;
    sigfillset(&mask);
    int err = pthread_sigmask(SIG_BLOCK, &mask, NULL);
    if (err != 0)
        LOG(INFO) << "%s pthread_sigmask error: %d .", i, err);
#endif

//      while(1)
    {
        /*创建客户端套接字--IPv4协议，面向连接通信，TCP协议 */
        if ((client_sockfd[i] = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket create error!");
            //pthread_exit(0); ;
            return false;
        }
        /*将套接字绑定到服务器的网络地址上 */
        if (connect
            (client_sockfd[i], (struct sockaddr *) &remote_addr,
             sizeof(struct sockaddr)) < 0) {
            perror("connect error!");
            return false;
            //pthread_exit(0); ;
        }
        //发送id到control端
        bzero(buf, 1024 * 1024 * 3);
        LOG(INFO) << "client: %d connected to server\n", client_sockfd[i]);
        //pad_code = &strid[i][20];
        memcpy(pad_code, strid[i], 14);
        LOG(INFO) << "pad_code : %s\n", pad_code);
        flatbuffers::FlatBufferBuilder builder;
        flatbuffers::Offset < CSProto::ShakeOnline > fbs =
          CSProto::CreateShakeOnlineDirect(builder, pad_code);
        builder.Finish(fbs);
        uint8_t *data = builder.GetBufferPointer();
        uint32_t len = builder.GetSize();
        LOG(INFO) << "len_data:%d\n", len);
                /*******************
		*Testing part
		*********************/
        //              char* data = "fuck ,work overtime once again";
        //              uint32_t len = strlen(data);
                /*******************
		*Testing part
		*********************/
        header = {
        (uint8_t) 0, (uint8_t) 0, len};
        LOG(INFO) << "header len:%d\n", sizeof(header));
        memcpy(buf, &header, sizeof(header));
        //LOG(INFO)<<"buf_headerlen:%d\n", sizeof(buf));
        memcpy(buf + sizeof(header), data, (size_t) len);
        status = send(client_sockfd[i], buf, sizeof(header) + (size_t) len, 0);
        if (status == -1) {
            LOG(INFO) << "shake send failed\n");
        } else
            LOG(INFO) << "shake send success byte: %d\n", status);


        //设置非阻塞
        opts = fcntl(client_sockfd[i], F_GETFL);
        if (opts < 0) {
            perror("fcntl(F_GETFL)\n");
            return false;
            //      pthread_exit(0);;
        }
        opts = (opts | O_NONBLOCK);
        if (fcntl(client_sockfd[i], F_SETFL, opts) < 0) {
            perror("fcntl(F_SETFL)\n");
            return false;
            //      pthread_exit(0);;
        }
        //使用epoll监控所有fd
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = client_sockfd[i];
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, client_sockfd[i], &ev) == -1) {
            perror("epoll_ctl: client_sockfd");
            return false;
            //      pthread_exit(0);;
        }
#if 0

        while (1) {
            unsigned long StartEncodeTime = GetTickCount();

            if ((send_H264_packet(i, size, 1)) <= 0) {
                close(client_sockfd[i]);
                break;
            }

            unsigned long TOPF = 1000 / frame_per_sec;  //Time of per frame
            unsigned long ProcessTime = GetTickCount() - StartEncodeTime;
            if (ProcessTime < TOPF - 1) {
                struct timeval delay;
                delay.tv_sec = 0;
                delay.tv_usec = (TOPF - ProcessTime - 1) * 1000;
                select(0, NULL, NULL, NULL, &delay);
            }
        }
#endif
    }
//      LOG(INFO)<<"client :%d exit\n", i);
//      pthread_exit(0);
}
void send_delay(const int fd)
{
    //发送delay
    int status;
    uint8_t *data_recv;
    size_t len_recv;
    int64_t curtime;
    char buf[1024 * 1024 * 3];
    csproto_header_t header;
    char time_str[64] = { 0 };

    bzero(buf, 1024 * 1024 * 3);
    bzero(&header, sizeof(header));
    curtime = GetTickCount();
    snprintf(time_str, sizeof(time_str), "%lld", curtime);
    flatbuffers::FlatBufferBuilder builder_recv;
    flatbuffers::Offset < CSProto::ControlDelay > cd =
      CSProto::CreateControlDelayDirect(builder_recv, time_str);
    builder_recv.Finish(cd);
    data_recv = builder_recv.GetBufferPointer();
    len_recv = builder_recv.GetSize();

    header = {
    1, 2, (uint32_t) len_recv};
    memcpy(buf, &header, sizeof(header));
    memcpy(buf + sizeof(header), data_recv, (size_t) len_recv);
    LOG(INFO) << "start to send delay";
    status = send(fd, buf, sizeof(header) + (size_t) len_recv, 0);
    if (status == -1) {
        LOG(ERROR) << "send failed";
    } else
        LOG(INFO) << "send success byte: " << status;
}

void send_delay_r(const int fd, uint8_t * buffer)
{
    int status;
    csproto_header_t header;
    const CSProto::ControlDelayR * fbsobj =
      flatbuffers::GetRoot < CSProto::ControlDelayR > (buffer + sizeof(header));
    int64_t time;
    int64_t time_now;
    int64_t time_scale;
    char time_str[64] = { 0 };
    uint8_t *data_recv;
    int64_t len_recv;

    time = atoll(fbsobj->time()->c_str());
    LOG(INFO) << "get time =" << time;
    time_now = GetTickCount();
    LOG(INFO) << "time_now = " << time_now;
    time_scale = time_now - time;
    LOG(INFO) << "time_scale:" << time_scale;
    snprintf(time_str, sizeof(time_str), "%lld", time_scale);

    bzero(&header, sizeof(header));
    flatbuffers::FlatBufferBuilder builder_recv;
    flatbuffers::Offset < CSProto::ControlDelay > cd =
      CSProto::CreateControlDelayDirect(builder_recv, time_str);
    builder_recv.Finish(cd);
    data_recv = builder_recv.GetBufferPointer();
    len_recv = builder_recv.GetSize();

    bzero(buffer, 1024 * 1024 * 3);
    header = {
    1, 3, (uint32_t) len_recv};
    memcpy(buffer, &header, sizeof(header));
    memcpy(buffer + sizeof(header), data_recv, (size_t) len_recv);
    LOG(INFO) << "start to send delay_r";
    LOG(INFO) << "fd = " << fd << ", send data_header [" << header.
      type << "," << header.subtype << "," << header.len << "]";
    status = send(fd, buffer, sizeof(header) + (size_t) len_recv, 0);
    if (status == -1) {
        LOG(ERROR) << "send failed";
    } else
        LOG(INFO) << "send success byte:" << status;

}
void send_av(const int fd, uint8_t * buffer)
{


    int n = 0;
    int status;
    uint64_t len;
    uint8_t buf[25606];
    uint8_t buf_a[1606];
    char data_a[1600] = { 0 };
    csproto_header_t header;
    char data[25600] = { 0 };
    int64_t time;

    //parse data
    const CSProto::ControlAVTrans * fbsobj =
      flatbuffers::GetRoot < CSProto::ControlAVTrans >
      (buffer + sizeof(header));
    LOG(INFO) << "v:" << fbsobj->video() << " , a:" << fbsobj->audio();
    if (fbsobj->video() == 1) {
        bzero(buf, 25606);
        bzero(&header, sizeof(header));
        len = sizeof(data);
        header = {
        4, 1, (uint32_t) len};
        memcpy(buf, &header, sizeof(header));
        time = rand();
        snprintf(data, 64, "%lld", time);
        LOG(INFO) << "data:" << data;
        memcpy(buf + sizeof(header), data, 64);
        while ((status = send(fd, buf, sizeof(header) + (size_t) len, 0))) {
            if (status < 1) {
                LOG(INFO) << "send failed";
                break;
            } else {
                n += status;
                if (n < 25600 + 6)
                    continue;
                else
                    break;
            }
        }
        LOG(INFO) << "send vedio len totally: " << n;
    }
    n = 0;
    if (fbsobj->audio() == 1) {
        bzero(buf_a, 1606);
        bzero(&header, sizeof(header));
        len = sizeof(data_a);
        header = {
        4, 0, (uint32_t) len};
        memcpy(buf_a, &header, sizeof(header));
        time = rand();
        snprintf(data_a, 64, "%lld", time);
        LOG(INFO) << "data_a:" << data_a;
        memcpy(buf + sizeof(header), data_a, 64);
        while ((status = send(fd, buf_a, sizeof(header) + (size_t) len, 0))) {
            if (status < 1) {
                LOG(INFO) << "send failed";
                break;
            } else {
                n += status;
                if (n < 1600 + 6)
                    continue;
                else
                    break;
            }
        }
        LOG(INFO) << "send audio len totally:" << n;
    }
}
void handle_input(const int fd, uint8_t * buffer)
{
    csproto_header_t header;
    const CSProto::InputTouch * fbsobj =
      flatbuffers::GetRoot < CSProto::InputTouch > (buffer + sizeof(header));

    LOG(INFO) << "index : " << fbsobj->index();
    if (fbsobj->index() > 0) {
        const flatbuffers::Vector < const CSProto::TouchInfo * >*touch =
          fbsobj->touch();
        LOG(INFO) << "size: " << touch->size();
        if (touch->size() > 0) {
            int x[touch->size()];       // = { 0 };
            int y[touch->size()];       // = { 0 };
            float force[touch->size()]; // = { 0 };
            LOG(INFO) << "input touch index:" << fbsobj->index() << " type: " << fbsobj->type();        //<<"    x : "<<x[i] <<"   y :"<<y[i] <<"    force :"<<  force;
            for (int i = 0; i < touch->size(); i++) {
                x[i] = touch->Get(i)->x();
                y[i] = touch->Get(i)->y();
                force[i] = touch->Get(i)->force();
                LOG(INFO) << "x:" << x[i] << " y:" << y[i] << " f:" << force[i];
            }
        }
    } else {
        LOG(INFO) << "input touch else";
    }
}
void handle_input_keyboard(const int fd, uint8_t * buffer)
{
    const CSProto::InputKeyboard * fbsobj =
      flatbuffers::GetRoot < CSProto::InputKeyboard > (buffer + 6);
    LOG(INFO) << "input key : " << fbsobj->key() << ", presses :" << fbsobj->
      pressed();
}
bool send_H264_packet(int sock, unsigned int size, bool bIsKeyFrame)
{
    int len = size + 9;
    unsigned char *body = new unsigned char[len];

    size_t i = 0;

    if (bIsKeyFrame) {
        body[i++] = 0x02;       // 1:Iframe  7:AVC  关键帧
    } else {
        body[i++] = 0x27;       // 2:Pframe  7:AVC  
    }
    body[i++] = 0x01;           // AVC NALU  
    body[i++] = 0x00;
    body[i++] = 0x00;
    body[i++] = 0x00;

    // NALU size  
    body[i++] = size >> 24;
    body[i++] = size >> 16;
    body[i++] = size >> 8;
    body[i++] = size & 0xff;;

    // NALU data  


    csproto_header_t av_header = { 4, 1, (uint32_t) len };
    unsigned char *av_packet = new unsigned char[len + sizeof(av_header)];
    memset(av_packet, 0, len + sizeof(av_header));
    memcpy(av_packet, &av_header, sizeof(av_header));
    memcpy(av_packet + sizeof(av_header), body, len);

    LOG(INFO) << "sock id :" << sock << " body size :" << len <<
      " , av_packet* size:" << sizeof(av_packet) << ", length:" << len +
      sizeof(av_header) << " , size of header: " << sizeof(av_header);

    int status =
      send(client_sockfd[sock], (char *) av_packet, (len + sizeof(av_header)),
           0);
//      perror
    if (status <= 0) {
//              LOG(INFO)<<"av_packet send failed: %d\n", status);
        LOG(ERROR) << "av_packet send failed:" << strerror(errno);
        delete[]body;
        delete[]av_packet;
        return false;
    } else {
        LOG(INFO) << "av_packet send success byte: " << status;
        delete[]body;
        delete[]av_packet;
        return true;
    }

}

typedef struct Arg {
    int id;
    int size;
    int fps;
} Argument;
#endif
