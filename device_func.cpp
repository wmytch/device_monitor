#include "device_func.h"

extern std::vector<std::string> strid;
std::map <int,std::string> device_binded;
unsigned long GetTickCount()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void set_device_id(std::vector<std::string> &id)
{
    char filename[] = "./id.txt"; //文件名
    FILE *fp;
    char StrLine[20];           //每行最大读取的字符数
    if ((fp = fopen(filename, "r")) == NULL)    //判断文件是否存在及可读
    {
        LOG(INFO) << "Get device id error:"<<strerror(errno);
        exit(-1);
    }
	char pad_id[20]={0};
    while (!feof(fp)) {
        fgets(StrLine, 20, fp); //读取一行
		memcpy(pad_id,StrLine,14);
		id.push_back(pad_id);
    }
    fclose(fp);
}
size_t send_to_control(int fd,uint8_t type,uint8_t sub_type,uint8_t *data,uint32_t len)
{
	uint8_t buf[1024*1024*3]={0};
    csproto_header_t header = {type, sub_type, len};
	len=(len+sizeof(header))>sizeof(buf)?sizeof(buf)-sizeof(header):len;
	memcpy(buf,&header,sizeof(header));
	memcpy(buf+sizeof(header),data,len);
	size_t data_len=sizeof(header)+len;
	size_t n=0;
	size_t status;
	while((status=send(fd,buf+n,data_len-n,0)))
	{
		if(status<0)
		{
			if(errno==EAGAIN||errno==EWOULDBLOCK)
				continue;
			else
			{
				LOG(ERROR)<<"Send to control error:"<<strerror(errno);	
				return -1;
			}
		}
		n+=status;
		if(n>=data_len)
			break;
	}
	return n;
}
/* type:MSG_SHAKE*/
bool shake_online(int fd,int pad_num)
{
	LOG(INFO)<<__func__<<" begin.";
    LOG(INFO) << "pad_code :" << strid[pad_num];

    flatbuffers::FlatBufferBuilder builder;
    flatbuffers::Offset < CSProto::ShakeOnline > fbs =
      CSProto::CreateShakeOnlineDirect(builder, strid[pad_num].c_str());
    builder.Finish(fbs);
    uint8_t *data = builder.GetBufferPointer();
    uint32_t len = builder.GetSize();

	auto status= send_to_control(fd,MSG_SHAKE,MSG_SHAKE_ONLINE,data,len);
    if (status == -1)
	{
		LOG(ERROR)<<"Send shake online["<<pad_num<<":"<<strerror(errno)<<"]";
        return false;
	}
	else
	{
		device_binded[fd]=strid[pad_num];
		return true;
	}
}
bool shake_online_r(uint8_t *buf)
{
	LOG(INFO)<<__func__<<" begin.";
	const CSProto::ShakeOnlineR * fbs = unpack<CSProto::ShakeOnlineR>(buf);
	if (fbs == nullptr || fbs->id() == nullptr)
	{
		LOG(ERROR) << "recv shake online response:get null fbs";
		return false;
	}
	LOG(INFO)<<"Shake online response:["<<fbs->id()->c_str()<<":"<<fbs->code()<<":"<<fbs->msg()->c_str()<<"]";
	if(fbs->code()==0)
		return true;
	else
		return false;
}
bool shake_offline(int fd,int code ,char *msg)
{
	LOG(INFO)<<__func__<<" begin.";
    flatbuffers::FlatBufferBuilder builder;
    flatbuffers::Offset < CSProto::ShakeOffline > fbs =
      CSProto::CreateShakeOfflineDirect(builder, code,msg);
    builder.Finish(fbs);
    uint8_t *data = builder.GetBufferPointer();
    uint32_t len = builder.GetSize();

	auto status= send_to_control(fd,MSG_SHAKE,MSG_SHAKE_OFFLINE,data,len);
    if (status == -1)
	{
		LOG(ERROR)<<"Send shake online["<<device_binded[fd]<<":"<<code<<":"<<msg<<"]";
        return false;
	}
	else
		return true;
	
}
void shake_offline_r(uint8_t *buf)
{
	LOG(INFO)<<__func__<<" begin.";
	const CSProto::ShakeOfflineR * fbsobj = unpack<CSProto::ShakeOfflineR >(buf);
	if (fbsobj == nullptr )
	{
		LOG(ERROR) << "recv shake offline response:get null fbs";
		return ;
	}
}
void shake_kick(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
/*type:MSG_CONTROL*/
void control_mtu(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_mtu_r(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_delay(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
    int64_t curtime;
    char time_str[64] = { 0 };
    curtime = GetTickCount();
    snprintf(time_str, sizeof(time_str), "%lld", curtime);
    flatbuffers::FlatBufferBuilder builder;
    flatbuffers::Offset < CSProto::ControlDelay > cd =
      CSProto::CreateControlDelayDirect(builder, time_str);
    builder.Finish(cd);
    uint8_t *data= builder.GetBufferPointer();
    size_t len= builder.GetSize();

    LOG(INFO) << "send control delay["<<device_binded[fd]<<"]";
	auto status= send_to_control(fd,MSG_CONTROL,MSG_CONTROL_DELAY ,data,len);
    if (status == -1) {
        LOG(ERROR) << "send control delay failed["<<device_binded[fd]<<"]:"<<strerror(errno);
    } 
}
void control_delay_r(int fd,uint8_t *buf)
{
	LOG(INFO)<<__func__<<" begin.";

	const CSProto::ControlDelay * fbsobj =unpack<CSProto::ControlDelay>(buf);
	if (fbsobj == nullptr )
	{
		LOG(ERROR) << "recv control delay response:get null fbs";
		return ;
	}
	LOG(INFO) << "recv control delay:["<<device_binded[fd]<<"]";
    int64_t time = atoll(fbsobj->time()->c_str());
    LOG(INFO) <<" get time =" << time;
    int64_t time_now = GetTickCount();
    LOG(INFO) <<"time_now = " << time_now;
    int64_t time_scale = time_now - time;
    LOG(INFO) <<"time_scale:" << time_scale;
    char time_str[64] = { 0 };
    snprintf(time_str, sizeof(time_str), "%lld", time_scale);
	
    flatbuffers::FlatBufferBuilder builder;
    flatbuffers::Offset < CSProto::ControlDelayR> cd =
      CSProto::CreateControlDelayRDirect(builder, time_str);
    builder.Finish(cd);
    uint8_t *data= builder.GetBufferPointer();
    int64_t len= builder.GetSize();

    LOG(INFO) << "send control delay_r["<<device_binded[fd]<<"]";
	auto status= send_to_control(fd,MSG_CONTROL,MSG_CONTROL_DELAY_R ,data,len);
    if (status == -1) {
        LOG(ERROR) <<" send delay_r failed["<<device_binded[fd]<<"]";
    } 
}
void control_app(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_app_r(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_avfmt(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_avfmt_r(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_avtrans(int fd,uint8_t *buf)
{
	LOG(INFO)<<__func__<<" begin.";

    //parse data
    const CSProto::ControlAVTrans * fbsobj =unpack<CSProto::ControlAVTrans>(buf);
	if (fbsobj == nullptr )
	{
		LOG(ERROR) << "recv control avtrans:get null fbs";
		return ;
	}
    LOG(INFO) << "v:" << fbsobj->video() << " , a:" << fbsobj->audio();

    int64_t time=rand();
    if (fbsobj->video() == 1) 
	{
		char data[25600] = { 0 };
        snprintf(data, 64, "%lld", time);
		if (send_to_control(fd,MSG_AV,MSG_AV_VIDEO,(uint8_t *)data,sizeof(data))<0)
			LOG(ERROR)<<"Send video error.";
    }
    if (fbsobj->audio() == 1) 
	{
		char data_a[1600] = { 0 };
        snprintf(data_a, 64, "%lld", time);
		if (send_to_control(fd,MSG_AV,MSG_AV_AUDIO,(uint8_t *)data_a,sizeof(data_a))<0)
			LOG(ERROR)<<"Send audio error.";
    }
}
void control_avtrans_r(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_iframe(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_audio(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_audio_r(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_video(int fd,uint8_t *buf)
{
	LOG(INFO)<<__func__<<" begin.";
    const CSProto::ControlVideo * fbsobj =unpack<CSProto::ControlVideo>(buf);
	if (fbsobj == nullptr )
	{
		LOG(ERROR) << "recv control video:get null fbs";
		return ;
	}

	LOG(INFO) << "control video info mode :" << fbsobj->
			mode() << "    bitrate :" << fbsobj->
			bitrate() << "		fps : " << fbsobj->fps();
	control_video_r(fd);
}
void control_video_r(int fd)
{
	LOG(INFO)<<__func__<<" begin.";

    flatbuffers::FlatBufferBuilder builder;
    flatbuffers::Offset < CSProto::ControlVideoR> cd =
      CSProto::CreateControlVideoR(builder);
    builder.Finish(cd);
    uint8_t *data= builder.GetBufferPointer();
    size_t len= builder.GetSize();

    LOG(INFO) << "send control_video_r["<<device_binded[fd]<<"] ";
	auto status= send_to_control(fd,MSG_CONTROL,MSG_CONTROL_VIDEO_R,data,len);
    if (status == -1) {
        LOG(ERROR) << "send control_video_r failed["<<device_binded[fd]<<"]";
    } 
}
void control_time(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_screen(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_kill_app(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_kill_app_r(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_resolutionlevel(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_queryauth(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void control_queryauth_r(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}	
/*type MSG_INPUT*/
void input_string(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_gamecontroller(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_keyboard(uint8_t *buf)
{
	LOG(INFO)<<__func__<<" begin.";
    const CSProto::InputKeyboard * fbsobj =unpack<CSProto::InputKeyboard>(buf);
	if (fbsobj == nullptr )
	{
		LOG(ERROR) << "recv input keyboard:get null fbs";
		return ;
	}
    LOG(INFO) << "input key : " << fbsobj->key() << ", presses :" << fbsobj->
      pressed();
}
void input_mouse_key(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_mouse_wheel(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_mouse_move(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_cursor(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_touch(uint8_t *buf)
{
	LOG(INFO)<<__func__<<" begin.";
    const CSProto::InputTouch * fbsobj =unpack<CSProto::InputTouch>(buf);
	if (fbsobj == nullptr )
	{
		LOG(ERROR) << "recv input touch:get null fbs";
		return ;
	}

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
        LOG(INFO) << "input touch fault.";
    }
}
void input_location(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_accelerometer(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_altimeter(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_gyro(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_magnetometer(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_pedometer(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_proximity(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_ambientlight(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_temperature(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void input_moisture(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
/*type:MSG_OUTPUT */
void output_string(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void output_screen(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void output_vibration(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void output_cursor(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
/*type:MSG_AV*/
void av_audio(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void av_video(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void av_subtitle(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void av_client_audio(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void av_client_video(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
void av_client_subtitle(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
}
/*type:MSG_AUTH*/
void auth_list(int fd)
{
	LOG(INFO)<<__func__<<" begin.";
    flatbuffers::FlatBufferBuilder builder;
    flatbuffers::Offset < CSProto::AuthList> cd =
      CSProto::CreateAuthList(builder);
    builder.Finish(cd);
    uint8_t *data= builder.GetBufferPointer();
    size_t len= builder.GetSize();

    LOG(INFO) << "send auth list request["<<device_binded[fd]<<"]";
	auto status= send_to_control(fd,MSG_AUTH,MSG_AUTH_LIST,data,len);
    if (status == -1) {
        LOG(ERROR) << "send auth list request failed["<<device_binded[fd]<<"]";
    } 
}

