#ifndef __DEVICE_FUNC__
#define __DEVICE_FUNC__

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "csproto_generated.h"
#include "csproto_header.h"
#include "log_client.h"

void set_device_id(std::vector<std::string>& id);
template <typename T>
bool VerifyMonsterBuffer(T* data, uint32_t len)
{
	flatbuffers::Verifier verifier((uint8_t*)data, len);
	return verifier.VerifyBuffer<T>(nullptr);
}
template <typename Proto> 
const Proto *unpack(uint8_t *buf)
{
	LOG(INFO)<<__func__<<" begin.";
    csproto_header_t header;
	memcpy(&header,buf,sizeof(header));
	LOG(INFO)<<"msg type["<<(int)header.type<<":"<<(int)header.type<<"]";
	if (!VerifyMonsterBuffer((Proto *)(buf+sizeof(header)),header.len))
	{
		LOG(ERROR) << "Response Prototol Error["<<header.type<<":"<<header.subtype<<"].";
		return nullptr;
	}
	const Proto * fbs = flatbuffers::GetRoot<Proto>(buf+sizeof(header));
	return fbs;
}
/*
template <typename Proto>
Proto *unpack(uint8_t *buf)
{
	Proto *fbsobj=flatbuffer::GetRoot<Proto>(buf);
	return fbsobj;
}
*/

/*type:MSG_SHAKE*/
bool shake_online(int fd,int pad_num);
bool shake_online_r(uint8_t *buf);
bool shake_offline(int fd,int code,char *msg);
void shake_offline_r(uint8_t *buf);
void shake_kick(int fd);
/*type:MSG_CONTROL*/
void control_mtu(int fd);
void control_mtu_r(int fd);
void control_delay(int fd);
void control_delay_r(int fd,uint8_t *buffer);
void control_app(int fd);
void control_app_r(int fd);
void control_avfmt(int fd);
void control_avfmt_r(int fd);
void control_avtrans(int fd,uint8_t *buffer);
void control_avtrans_r(int fd);
void control_iframe(int fd);
void control_audio(int fd);
void control_audio_r(int fd);
void control_video(int fd,uint8_t *buffer);
void control_video_r(int fd);
void control_time(int fd);
void control_screen(int fd);
void control_kill_app(int fd);
void control_kill_app_r(int fd);
void control_resolutionlevel(int fd);
void control_queryauth(int fd);
void control_queryauth_r(int fd);
/*type:MSG_INPUT*/
void input_string(int fd);
void input_gamecontroller(int fd);
void input_keyboard(uint8_t *buffer);
void input_mouse_key(int fd);
void input_mouse_wheel(int fd);
void input_mouse_move(int fd);
void input_cursor(int fd);
void input_touch(uint8_t *buffer);
void input_location(int fd);
void input_accelerometer(int fd);
void input_altimeter(int fd);
void input_gyro(int fd);
void input_magnetometer(int fd);
void input_pedometer(int fd);
void input_proximity(int fd);
void input_ambientlight(int fd);
void input_temperature(int fd);
void input_moisture(int fd);
/*type:MSG_OUTPUT*/
void output_string(int fd);
void output_screen(int fd);
void output_vibration(int fd);
void output_cursor(int fd);
/*type:MSG_AV*/
void av_audio(int fd);
void av_video(int fd);
void av_subtitle(int fd);
void av_client_audio(int fd);
void av_client_video(int fd);
void av_client_subtitle(int fd);
/*type:MSG_AUTH*/
void auth_list(int fd);
#endif
