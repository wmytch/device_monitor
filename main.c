#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/un.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include "/home/webapps/ycl/csproto_generated.h"
#include <memory.h>
#include <locale>
#include <errno.h>
#pragma pack(1)

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#elif defined(ANDROID)
#include <sys/time.h>
#endif

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

int64_t time_get2()
{
#if defined(LINUX)
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
}

typedef struct _csproto_header_t
{
    uint8_t     type;       // 协议类型
    uint8_t     subtype;    // 协议子类型
    uint32_t    len;        // 这里指定协议内容的长度，不包含此头
} csproto_header_t;

void setid(char (*id)[20])
{
	 char filename[] = "/home/webapps/ycl/id.txt"; //文件名
	 FILE *fp; 
	 char StrLine[20];            //每行最大读取的字符数
	int i;
	 if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
	 { 
	 	printf("error!");
		exit(1); 
	 } 
	i = 0;
	 while (!feof(fp)) 
	 { 
	 	fgets(StrLine,20,fp);  //读取一行
	 	//i = 0;
		//printf("i:%d\n", i);
		memcpy(id + i, StrLine, sizeof(StrLine));
		//printf("idaddress:%d,id:%d, %s\n",id + i, i, id + i);
		//printf("stridaddress:%x,strid:%d, %s\n",id, i, strid[i][20]);	
		bzero(StrLine, 20);
		i = i + 1;
	 }
	 fclose(fp); 
}

void send_delay(int fd)
{
				//发送delay
					int status;
					uint8_t * data_recv;
					uint64_t len_recv;
					int64_t curtime ;
					char buf[1024*1024*3];
					csproto_header_t header;
		        	char time_str[64] = {0};

					bzero(buf, 1024*1024*3);
					bzero(&header, sizeof(header));
					curtime = GetTickCount();
        			snprintf(time_str, sizeof(time_str), "%lld", curtime);
					printf("time_str = %s\n",time_str);
       				flatbuffers::FlatBufferBuilder builder_recv;
        			flatbuffers::Offset<CSProto::ControlDelay> cd = CSProto::CreateControlDelayDirect(builder_recv, time_str);
        			builder_recv.Finish(cd);
        			data_recv = builder_recv.GetBufferPointer();
        			len_recv = builder_recv.GetSize();
								
					header={1,2,len_recv};
					memcpy(buf, &header, sizeof(header));
					//printf("header len: %d\n", sizeof(header));
					memcpy(buf + sizeof(header), data_recv, (size_t)len_recv);
				//printf("data_recv len:%d\n", len_recv);
			//sleep(1);
					printf("start to send delay\n");	
					status = send(fd, buf, sizeof(header) + (size_t)len_recv, 0) ;
					if(status < 1)
					{
						printf("send failed\n");
					}
					else
						printf("send success byte: %d\n", status);
					//sleep(10);
}



void send_delay_r(int fd, uint8_t * buffer)
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
					printf("get time =%lld\n", time);
					time_now = GetTickCount();
					printf("time_now = %lld\n", time_now);
					time_scale = time_now - time;
					printf("time_scale:%lld\n", time_scale);
        			snprintf(time_str, sizeof(time_str), "%lld", time_scale);
	
					bzero(&header, sizeof(header));
       				flatbuffers::FlatBufferBuilder builder_recv;
        			flatbuffers::Offset<CSProto::ControlDelay> cd = CSProto::CreateControlDelayDirect(builder_recv, time_str);
        			builder_recv.Finish(cd);
        			data_recv = builder_recv.GetBufferPointer();
        			len_recv = builder_recv.GetSize();
		
					bzero(buffer, 1024*1024*3);
					header={1,3,len_recv};
					memcpy(buffer, &header, sizeof(header));
				//printf("header len: %d\n", sizeof(header));
					memcpy(buffer + sizeof(header), data_recv, (size_t)len_recv);
				//printf("time_get() - time len:%d\n", sizeof(time_scale));
				//sleep(1);
					printf("start to send delay_r\n");	
					printf("fd = %d , send data_header [%d,%d,%d]\n", fd, header.type, header.subtype, header.len);
					status = send(fd, buffer, sizeof(header) + (size_t)len_recv, 0) ;
					if(status == -1)
					{
						printf("send failed\n");
					}
					else
						printf("send success byte:%d\n", status);
									

}


void send_av(int fd)
{
		
				//发送delay
					int n = 0;
					int status;
					uint64_t len;
					uint8_t buf[512 * 2 * 500];
					csproto_header_t header;

					bzero(buf, 512 * 2 * 500);
					bzero(&header, sizeof(header));
					memset(buf, '1', 512 * 2 * 500);
					len = sizeof(buf);
					printf("av len: %d\nav: %d\n", len, buf);			
					header={4, 1, len};
					memcpy(buf, &header, sizeof(header));
					//printf("header len: %d\n", sizeof(header));
					memcpy(buf + sizeof(header), buf, (size_t)len);
				//printf("data_recv len:%d\n", len_recv);
			//sleep(1);
					printf("start to send delay\n");	
					while((status = send(fd, buf, sizeof(header) + (size_t)len, 0)) ) 
					{
						if(status < 1)
						{
							printf("send failed\n");
							break;
						}
						else 
						{
							n += status;
							if ( n < 512 + 6)
								continue;
							else 
								break;
						}
					//sleep(10);
					}
					printf("send av len totally: %d\n", n);
				
}

void send_dongdong(int * fd)
{
	int i;	
	for( i= 0; i < 1000; i++)
	{
		send_delay(fd[i]);
	}
}


main()
{
	int client_sockfd[1000];  
	int i, j, n;
	int nfds;
	int opts;
	int readfd;
	int nread;
	int epfd;
	char* id;
	uint8_t* buf;  //数据传送的缓冲区
	char strid[1000][20];
	char pad_code[15]={0};
	//char *pad_code;
	int status;
	struct sockaddr_in remote_addr; //服务器端网络地址结构体
	struct epoll_event ev,events[1000];	
	typedef struct _csproto_header_t
	{
    	uint8_t     type;       // 协议类型
    	uint8_t     subtype;    // 协议子类型
    	uint32_t    len;        // 这里指定协议内容的长度，不包含此头
	} csproto_header_t;
	csproto_header_t header;
	csproto_header_t *header_recv;
	buf = (uint8_t *)malloc(3 * 1024 * 1024);
	epfd=epoll_create(1000);//生成用于处理accept的epoll专用的文件描述符
	bzero(&remote_addr, sizeof(remote_addr));
	bzero(buf, sizeof(buf));
	bzero(strid, sizeof(strid));
	remote_addr.sin_family=AF_INET; //设置为IP通信
	remote_addr.sin_addr.s_addr=inet_addr("10.100.0.253");//服务器IP地址
	remote_addr.sin_port=htons(9926); //服务器端口号	
	

	setid(strid);//设置id

	for(i = 0; i < 941; i++)
	{
		/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
		if((client_sockfd[i]=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			perror("socket create error!");
			return 1;
		}
		/*将套接字绑定到服务器的网络地址上*/
		if(connect(client_sockfd[i],(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
		{
			perror("connect error!");
			return 1;
		}
		//发送id到control端
		bzero(buf, 1024*1024*3);
		printf("client: %d connected to server\n" , client_sockfd[i]);
		//pad_code = &strid[i][20];
		memcpy(pad_code, strid[i], 14);
		printf("pad_code : %s\n", pad_code);
		flatbuffers::FlatBufferBuilder builder;
		flatbuffers::Offset<CSProto::ShakeOnline> fbs = CSProto::CreateShakeOnlineDirect(builder, pad_code);
		builder.Finish(fbs);
		uint8_t * data = builder.GetBufferPointer();
		uint32_t len = builder.GetSize();
		printf("len_data:%d\n", len);
		header ={(uint8_t)0, (uint8_t)0, len};
		printf("header len:%d\n", sizeof(header));
		memcpy(buf, &header, sizeof(header));
		//printf("buf_headerlen:%d\n", sizeof(buf));
		memcpy(buf + sizeof(header), data, (size_t)len);
		status = send(client_sockfd[i], buf, sizeof(header) + (size_t)len, 0) ;
		if(status == -1)
		{
			printf("send failed\n");
		}
		else
			printf("send success byte: %d\n", status);
/*				
	const CSProto::ShakeOnline * fbss = flatbuffers::GetRoot<CSProto::ShakeOnline>(buf + sizeof(header));
        if (fbss == nullptr || fbss->id() == nullptr)
        {
            //LOG(ERROR) << "get null fbs";
            //disconnect();
            printf("_id parse errore\n");
            //return;
        }
        //char _id = fbss->padService()->c_str();
        std::string _id = fbss->id()->c_str();

		std::cout << "_id:::" << _id ;

*/		
		//设置非阻塞
		opts = fcntl (client_sockfd[i], F_GETFL);
		if (opts < 0)
		{
			perror ("fcntl(F_GETFL)\n");
			exit (1);
		}
		opts = (opts | O_NONBLOCK);
		if (fcntl (client_sockfd[i], F_SETFL, opts) < 0)
		{
			perror ("fcntl(F_SETFL)\n");
			exit (1);
		}

		//使用epoll监控所有fd
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = client_sockfd[i];
		if (epoll_ctl (epfd, EPOLL_CTL_ADD, client_sockfd[i], &ev) == -1)
		{
			perror ("epoll_ctl: client_sockfd");
			exit (1);
		}
	}
	//循环等待control端发回消息
	while(1)
	{
		printf("epoll waiting\n");
		nfds = epoll_wait (epfd, events, 1000, -1);
		if (nfds == -1)
		{
			perror ("epoll_wait error");
			exit (1);
		}
		printf("nfds:%d\n", nfds);
		printf("epoll wait successfully\n");
		for (i = 0; i < nfds; i++)
		{
			printf("i:%d\n",i);	
	//		printf("epoll wait successfully\n");
			readfd = events[i].data.fd;		
			//bzero(buf, 1024*1024*3);
			if (events[i].events & EPOLLIN)//读
            {
				n = 0;
				//bzero(buf, 1024*1024*3);
				//接收协议头
				while ((nread = recv(readfd, buf, 6, 0)) < 6)
				{
					if(nread == 0)
					{
						printf("recv error, nread= %d\n", nread);
						break;
					}	
					//else
					//	n += nread;
				}
				n += nread;
				printf("n=%d\n", nread);
				//memcpy(header_recv, buf, sizeof(*header_recv));
				header_recv = (csproto_header_t *)buf;
				bzero(&header, sizeof(header));
				memcpy(&header, header_recv, sizeof(*header_recv));
				printf("event =  %ld on fd = %d , recv data_header [%d,%d,%d], n:%d\n", events[i].events, events[i].data.fd, header_recv->type, header_recv->subtype, header_recv->len, n);
			

			//printf("header.type:%d\n",header.type);
				//接收协议体	
				while((nread = recv(readfd, buf + n, header.len, 0)) <  header.len)
				{	
					if(nread == -1)
					{
						printf("recv error, nread:%d", nread);
						break;
					}
				//	else
				//		n += nread;
				}
				n += nread;
				printf("n= %d\n", nread);

				printf("event =  %ld on fd = %d , recv header_len + data_len [%d]\n", events[i].events, events[i].data.fd, n);
			printf("header.type:%d\n",header.type);
				if(header.type == 0 )
				{
					send_delay(events[i].data.fd);


		
	/*
					bzero(buf, 1024*1024*3);

				//发送delay
					int64_t curtime = GetTickCount();
		        	char time_str[64] = {0};
        			snprintf(time_str, sizeof(time_str), "%lld", curtime);
					printf("time_str = %s\n",time_str);
       				flatbuffers::FlatBufferBuilder builder_recv;
        			flatbuffers::Offset<CSProto::ControlDelay> cd = CSProto::CreateControlDelayDirect(builder_recv, time_str);
        			builder_recv.Finish(cd);
        			uint8_t * data_recv = builder_recv.GetBufferPointer();
        			int64_t len_recv = builder_recv.GetSize();
								
					header={1,2,len_recv};
					memcpy(buf, &header, sizeof(header));
					//printf("header len: %d\n", sizeof(header));
					memcpy(buf + sizeof(header), data_recv, (size_t)len_recv);
				//printf("data_recv len:%d\n", len_recv);
			//sleep(1);
					printf("start to send\n");	
					status = send(events[i].data.fd, buf, sizeof(header) + (size_t)len_recv, 0) ;
					if(status < 1)
					{
						printf("send failed\n");
					}
					else
						printf("send success byte: %d\n", status);
					//sleep(10);
	*/
				}  
				
				//printf("header_recv .type:%d\n", header_recv->type);
				else if ( header.type == 1 )
				{
					printf("header.subtype: %d\n", header.subtype);
					if(header.subtype == 2)
					{		
						send_delay_r(events[i].data.fd, buf);
						sleep(0.001);
						send_delay(events[i].data.fd);
	/*
					const CSProto::ControlDelayR * fbsobj = flatbuffers::GetRoot<CSProto::ControlDelayR>(buf + sizeof(header));
					int64_t time = atoll(fbsobj->time()->c_str());
					printf("get time =%lld\n", time);
					int64_t time_now = GetTickCount();

					printf("time_now = %lld\n", time_now);
					int64_t time_scale = time_now - time;
					printf("time_scale:%lld\n", time_scale);
		        	char time_str1[64] = {0};
        			snprintf(time_str1, sizeof(time_str1), "%lld", time_scale);
	

       				flatbuffers::FlatBufferBuilder builder_recv1;
        			flatbuffers::Offset<CSProto::ControlDelay> cd1 = CSProto::CreateControlDelayDirect(builder_recv1, time_str1);
        			builder_recv1.Finish(cd1);
        			uint8_t * data_recv1 = builder_recv1.GetBufferPointer();
        			int64_t len_recv1 = builder_recv1.GetSize();
		
					bzero(buf, 1024*1024*3);
					header={1,3,len_recv1};
					memcpy(buf, &header, sizeof(header));
				//printf("header len: %d\n", sizeof(header));
					memcpy(buf + sizeof(header), data_recv1, (size_t)len_recv1);
				//printf("time_get() - time len:%d\n", sizeof(time_scale));
				//sleep(1);
					printf("start to send delay\n");	
				printf("event =  %ld on fd = %d , send data_header [%d,%d,%d]\n", events[i].events, events[i].data.fd, header.type, header.subtype, header.len);
					status = send(events[i].data.fd, buf, sizeof(header) + (size_t)len_recv1, 0) ;
					if(status == -1)
					{
						printf("send failed\n");
					}
					else
						printf("send success byte:%d\n", status);
									

				//printf("start to wait\n");

				//第二次发delay
					bzero(buf, 1024*1024*3);

				//暂停1秒，再次发送delay
					sleep(8);
					int64_t cur;
					cur = GetTickCount();
					//curtime2 = time_get();
					printf("cur = %lld\n",cur);
		        	char time_str2[64] = {0};
        			snprintf(time_str2, sizeof(time_str2), "%lld", cur);
					printf("time_str2:%s\n", time_str2);
       				flatbuffers::FlatBufferBuilder builder_recv2;
        			flatbuffers::Offset<CSProto::ControlDelay> cd2 = CSProto::CreateControlDelayDirect(builder_recv2, time_str2);
        			builder_recv2.Finish(cd2);
        			uint8_t * data_recv2 = builder_recv2.GetBufferPointer();
        			int64_t len_recv2 = builder_recv2.GetSize();
								
					header={1,2,len_recv2};
					memcpy(buf, &header, sizeof(header));
				//printf("header len: %d\n", sizeof(header));
					memcpy(buf + sizeof(header), data_recv2, (size_t)len_recv2);
				//printf("data_recv2 len:%d\n", len_recv2);
			//sleep(1);
					printf("start to send delay 1 \n");
	
					printf("event =  %ld on fd = %d , send data_header [%d,%d,%d]\n", events[i].events, events[i].data.fd, header.type, header.subtype, header.len);
					status = send(events[i].data.fd, buf, sizeof(header) + (size_t)len_recv2, 0) ;
					if(status == -1)
					{
						printf("send failed\n");
					}
					else
						printf("send success byte: %d\n", status);
	*/
					}

					else if (header.subtype == 16)
					{
						printf("header.subtype :%d,continued to send delay.\n",header.subtype);	
						sleep(0.001);
						send_delay(events[i].data.fd);			

	/*

				//第二次发delay
					bzero(buf, 1024*1024*3);

				//暂停1秒，再次发送delay
					sleep(8);
					int64_t cur1;
					cur1 = GetTickCount();
					//curtime2 = time_get();
					printf("cur1 = %lld\n",cur1);
		        	char time_str3[64] = {0};
        			snprintf(time_str3, sizeof(time_str3), "%lld", cur1);
					printf("time_str3:%s\n", time_str3);
       				flatbuffers::FlatBufferBuilder builder_recv3;
        			flatbuffers::Offset<CSProto::ControlDelay> cd3 = CSProto::CreateControlDelayDirect(builder_recv3, time_str3);
        			builder_recv3.Finish(cd3);
        			uint8_t * data_recv3 = builder_recv3.GetBufferPointer();
        			int64_t len_recv3 = builder_recv3.GetSize();
								
					header={1,2,len_recv3};
					memcpy(buf, &header, sizeof(header));
				//printf("header len: %d\n", sizeof(header));
					memcpy(buf + sizeof(header), data_recv3, (size_t)len_recv3);
				//printf("data_recv2 len:%d\n", len_recv2);
			//sleep(1);
					printf("start to send delay 1 \n");
	
				printf("event =  %ld on fd = %d , send data_header [%d,%d,%d]\n", events[i].events, events[i].data.fd, header.type, header.subtype, header.len);
					status = send(events[i].data.fd, buf, sizeof(header) + (size_t)len_recv3, 0) ;
					if(status == -1)
					{
						printf("send failed\n");
					}
					else
						printf("send success byte: %d\n", status);

*/
					}
					else if (header.subtype == 8)
					{
						//sleep(5);
						printf("header.subtype :%d,continued to send delay.\n",header.subtype);	
						printf("connection :%d,start to send av.\n", i);
						//for(j = 0; j < 1000; j++)
						//{
							send_av(events[i].data.fd); 
							send_delay(events[i].data.fd);			
							sleep(0.001);
						//}
						//sleep(5);
						//send_delay(events[i].data.fd);			
					}	
				}

			}

			else if(events[i].events&EPOLLERR)
            {  
           
				printf("epoll  fd  error\n");	
			}  
			else
				printf(" epoll recv abnormal\n");

		}

	}
	
	return 0;
}

