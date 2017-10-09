#ifndef __CSPROTO_HEADER_H__
#define __CSPROTO_HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(WIN32) || defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#define SHUT_RDWR   SD_BOTH
#define close       closesocket
#elif defined(ANDROID)
#include <sys/socket.h>
#include <linux/in.h>
#include <linux/tcp.h>
#include <arpa/inet.h>
#endif

#ifdef __cplusplus
#define CSPROTO_API_BEGIN   extern "C" {
#define CSPROTO_API_END     }
#else
#define CSPROTO_API_BEGIN   
#define CSPROTO_API_END     
#endif

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#define usleep(x)           Sleep(x / 1000)
#if defined (USRDLL) || defined(_USRDLL)
#define CSPROTO_API         __declspec(dllexport)
#else
#define CSPROTO_API        
//__declspec(dllimport)
#endif
#else
#define CSPROTO_API         
#endif

CSPROTO_API_BEGIN

#pragma pack(push)
#pragma pack(1)

#define CSPROTO_HEADER_MAGIC_0  0x47
#define CSPROTO_HEADER_MAGIC_1  0x43
#define CSPROTO_HEADER_MAGIC_2  0x50
#define CSPROTO_HEADER_MAGIC_3  0x43

typedef struct _csproto_header_t
{
    uint8_t     type;       // 协议类型
    uint8_t     subtype;    // 协议子类型
    uint32_t    len;        // 这里指定协议内容的长度，不包含此头
} csproto_header_t;

#pragma pack(pop)

// 主消息类型
enum MSG_TYPE
{
    MSG_SHAKE                   = 0,    // 握手协议
    MSG_CONTROL                 = 1, 	// 控制协议
    MSG_INPUT                   = 2, 	// 操控/输入协议
    MSG_OUTPUT                  = 3, 	// 输出协议
    MSG_AV                      = 4,    // 音视频协议
    MSG_AUTH                    = 5,    // 权限协议，专用于设备和流媒体服务器
};

// SHAKE子消息类型
enum MSG_SHAKE_TYPE
{
    MSG_SHAKE_ONLINE            = 0, 	// 上线请求
    MSG_SHAKE_ONLINE_R          = 1, 	// 上线应答
    MSG_SHAKE_OFFLINE           = 2, 	// 下线请求
    MSG_SHAKE_OFFLINE_R         = 3, 	// 下线应答
    MSG_SHAKE_KICK              = 4, 	// 强制踢出请求
};

// CONTROL子消息类型
enum MSG_CONTROL_TYPE
{
    MSG_CONTROL_MTU					= 0,	// MTU测试请求
    MSG_CONTROL_MTU_R				= 1,	// MTU测试应答
    MSG_CONTROL_DELAY				= 2, 	// 延迟测试请求
    MSG_CONTROL_DELAY_R				= 3, 	// 延迟测试应答
    MSG_CONTROL_APP					= 4,    // 应用请求
    MSG_CONTROL_APP_R				= 5,    // 应用应答 
    MSG_CONTROL_AVFMT				= 6, 	// 音视频格式请求，数据结构内的值只是个要求，真正的值由服务器决定
    MSG_CONTROL_AVFMT_R				= 7, 	// 音视频格式应答
    MSG_CONTROL_AVTRANS				= 8, 	// 音视频传输控制请求（是否传输音频、视频）
    MSG_CONTROL_AVTRANS_R			= 9,    // 音视频传输控制应答
    MSG_CONTROL_IFRAME				= 10, 	// 视频关键帧请求
    MSG_CONTROL_AUDIO				= 11,   // 音频参数调整请求
	MSG_CONTROL_AUDIO_R				= 12,	// 音频参数应答
    MSG_CONTROL_VIDEO				= 13, 	// 视频参数调整请求
	MSG_CONTROL_VIDEO_R				= 14,	// 视频参数应答
	MSG_CONTROL_TIME				= 15,	// 控制倒计时
	MSG_CONTROL_SCREEN				= 16,   // 屏幕分辨率比例设置
	MSG_CONTROL_KILL_APP			=17,   //杀死app
	MSG_CONTROL_KILL_APP_R			=18,	//杀死app应答
	MSG_CONTROL_RESOLUTIONLEVEL		=19,	//分辨率级别
	MSG_CONTROL_QUERYAUTH			= 20,	// 询问是否收回控制权
	MSG_CONTROL_QUERYAUTH_R			= 21,	// 控制权应答
};

// INPUT子消息类型
enum MSG_INPUT_TYPE
{
    // 通用
    MSG_INPUT_STRING            = 0,	// 字符串
    MSG_INPUT_GAMECONTROLLER    = 1, 	// 游戏控制器

    // PC
    MSG_INPUT_KEYBOARD          = 100, 	// 键盘
    MSG_INPUT_MOUSE_KEY         = 101, 	// 鼠标按键
    MSG_INPUT_MOUSE_WHEEL       = 102, 	// 鼠标滚轮
    MSG_INPUT_MOUSE_MOVE        = 103, 	// 鼠标移动
    MSG_INPUT_CURSOR            = 104,  // 光标，你可以认为就是鼠标箭头

    // 手机
    MSG_INPUT_TOUCH             = 200, 	// 触摸
    MSG_INPUT_LOCATION          = 201,  // 位置数据
    MSG_INPUT_ACCELEROMETER     = 202,  // 加速度
    MSG_INPUT_ALTIMETER         = 203,  // 高度计
    MSG_INPUT_GYRO              = 204,  // 陀螺仪
    MSG_INPUT_MAGNETOMETER      = 205,  // 磁力计
    MSG_INPUT_PEDOMETER         = 206,  // 计步器
    MSG_INPUT_PROXIMITY         = 207,  // 距离传感器
    MSG_INPUT_AMBIENTLIGHT      = 208,  // 环境光传感器
    MSG_INPUT_TEMPERATURE       = 209,  // 温度传感器
    MSG_INPUT_MOISTURE          = 210,  // 湿度传感器
};

// OUTPUT子消息类型
enum MSG_OUTPUT_TYPE
{
    MSG_OUTPUT_STRING           = 0,    // 字符串
    MSG_OUTPUT_SCREEN           = 1,    // 屏幕相关，分辨率，刷新率，旋转
    MSG_OUTPUT_VIBRATION        = 2, 	// 震动
    MSG_OUTPUT_CURSOR           = 3, 	// 光标位置及可见性
};

// AV子消息类型
enum MSG_AV_TYPE
{
    MSG_AV_AUDIO                = 0,    // 音频
    MSG_AV_VIDEO                = 1,    // 视频
    MSG_AV_SUBTITLE             = 2,    // 字幕
    MSG_AV_CLIENT_AUDIO         = 3,    // 客户端音频
    MSG_AV_CLIENT_VIDEO         = 4,    // 客户端视频
    MSG_AV_CLIENT_SUBTITLE      = 5,    // 客户端字幕
};

// AUTH子消息类型
enum MSG_AUTH_TYPE
{
    MSG_AUTH_LIST               = 0,    // 权限列表
};

// 声音格式
enum AUDIO_FMT_TYPE
{
    AUDIO_FMT_AAC           = 0, 
};

// aac profile
enum AAC_PROFILE_TYPE
{
    AAC_PROFILE_LD          = 0,     // 低延迟
    AAC_PROFILE_LC          = 1,     // 低复杂度
};

// 视频格式
enum VIDEO_FMT_TYPE
{
    VIDEO_FMT_H264          = 0, 
    VIDEO_FMT_HEVC          = 1, 
};

// h264 profile
enum H264_PROFILE_TYPE
{
    H264_PROFILE_BASELINE   = 0, 
    H264_PROFILE_MAIN       = 1, 
};

// hevc profile
enum HEVC_PROFILE_TYPE
{
    HEVC_PROFILE_BASELINE   = 0, 
    HEVC_PROFILE_MAIN       = 1, 
};

// 游戏控制器按钮
#define GAMEPAD_DPAD_UP          0x0001
#define GAMEPAD_DPAD_DOWN        0x0002
#define GAMEPAD_DPAD_LEFT        0x0004
#define GAMEPAD_DPAD_RIGHT       0x0008
#define GAMEPAD_START            0x0010
#define GAMEPAD_BACK             0x0020
#define GAMEPAD_LEFT_THUMB       0x0040
#define GAMEPAD_RIGHT_THUMB      0x0080
#define GAMEPAD_LEFT_SHOULDER    0x0100
#define GAMEPAD_RIGHT_SHOULDER   0x0200
#define GAMEPAD_A                0x1000
#define GAMEPAD_B                0x2000
#define GAMEPAD_X                0x4000
#define GAMEPAD_Y                0x8000

// 键盘按键
enum KEY_TYPE
{
    KEY_LBUTTON             = 0x01,
    KEY_RBUTTON             = 0x02,
    KEY_CANCEL              = 0x03,
    KEY_MBUTTON             = 0x04, /* NOT contiguous with L & RBUTTON */

    KEY_XBUTTON1            = 0x05, /* NOT contiguous with L & RBUTTON */
    KEY_XBUTTON2            = 0x06, /* NOT contiguous with L & RBUTTON */

    KEY_BACK                = 0x08,
    KEY_TAB                 = 0x09,

    KEY_CLEAR               = 0x0C,
    KEY_RETURN              = 0x0D,

    KEY_SHIFT               = 0x10,
    KEY_CONTROL             = 0x11,
    KEY_MENU                = 0x12,
    KEY_PAUSE               = 0x13,
    KEY_CAPITAL             = 0x14,

    KEY_KANA                = 0x15,
    KEY_HANGEUL             = 0x15, /* old name - should be here for compatibility */
    KEY_HANGUL              = 0x15,
    KEY_JUNJA               = 0x17,
    KEY_FINAL               = 0x18,
    KEY_HANJA               = 0x19,
    KEY_KANJI               = 0x19,

    KEY_ESCAPE              = 0x1B,

    KEY_CONVERT             = 0x1C,
    KEY_NONCONVERT          = 0x1D,
    KEY_ACCEPT              = 0x1E,
    KEY_MODECHANGE          = 0x1F,

    KEY_SPACE               = 0x20,
    KEY_PRIOR               = 0x21,
    KEY_NEXT                = 0x22,
    KEY_END                 = 0x23,
    KEY_HOME                = 0x24,
    KEY_LEFT                = 0x25,
    KEY_UP                  = 0x26,
    KEY_RIGHT               = 0x27,
    KEY_DOWN                = 0x28,
    KEY_SELECT              = 0x29,
    KEY_PRINT               = 0x2A,
    KEY_EXEC                = 0x2B, // 其实应该叫KEY_EXECUTE，但是和Windows的一些宏重名，所以改了
    KEY_SNAPSHOT            = 0x2C,
    KEY_INSERT              = 0x2D,
    KEY_DELETE              = 0x2E,
    KEY_HELP                = 0x2F,

    KEY_0                   = 0x30,
    KEY_1                   = 0x31,
    KEY_2                   = 0x32,
    KEY_3                   = 0x33,
    KEY_4                   = 0x34,
    KEY_5                   = 0x35,
    KEY_6                   = 0x36,
    KEY_7                   = 0x37,
    KEY_8                   = 0x38,
    KEY_9                   = 0x39,

    KEY_A                   = 0x41,
    KEY_B                   = 0x42,
    KEY_C                   = 0x43,
    KEY_D                   = 0x44,
    KEY_E                   = 0x45,
    KEY_F                   = 0x46,
    KEY_G                   = 0x47,
    KEY_H                   = 0x48,
    KEY_I                   = 0x49,
    KEY_J                   = 0x4A,
    KEY_K                   = 0x4B,
    KEY_L                   = 0x4C,
    KEY_M                   = 0x4D,
    KEY_N                   = 0x4E,
    KEY_O                   = 0x4F,
    KEY_P                   = 0x50,
    KEY_Q                   = 0x51,
    KEY_R                   = 0x52,
    KEY_S                   = 0x53,
    KEY_T                   = 0x54,
    KEY_U                   = 0x55,
    KEY_V                   = 0x56,
    KEY_W                   = 0x57,
    KEY_X                   = 0x58,
    KEY_Y                   = 0x59,
    KEY_Z                   = 0x5A,

    KEY_LWIN                = 0x5B,
    KEY_RWIN                = 0x5C,
    KEY_APPS                = 0x5D,

    KEY_SLEEP               = 0x5F,

    KEY_NUMPAD0             = 0x60,
    KEY_NUMPAD1             = 0x61,
    KEY_NUMPAD2             = 0x62,
    KEY_NUMPAD3             = 0x63,
    KEY_NUMPAD4             = 0x64,
    KEY_NUMPAD5             = 0x65,
    KEY_NUMPAD6             = 0x66,
    KEY_NUMPAD7             = 0x67,
    KEY_NUMPAD8             = 0x68,
    KEY_NUMPAD9             = 0x69,
    KEY_MULTIPLY            = 0x6A,
    KEY_ADD                 = 0x6B,
    KEY_SEPARATOR           = 0x6C,
    KEY_SUBTRACT            = 0x6D,
    KEY_DECIMAL             = 0x6E,
    KEY_DIVIDE              = 0x6F,
    KEY_F1                  = 0x70,
    KEY_F2                  = 0x71,
    KEY_F3                  = 0x72,
    KEY_F4                  = 0x73,
    KEY_F5                  = 0x74,
    KEY_F6                  = 0x75,
    KEY_F7                  = 0x76,
    KEY_F8                  = 0x77,
    KEY_F9                  = 0x78,
    KEY_F10                 = 0x79,
    KEY_F11                 = 0x7A,
    KEY_F12                 = 0x7B,
    KEY_F13                 = 0x7C,
    KEY_F14                 = 0x7D,
    KEY_F15                 = 0x7E,
    KEY_F16                 = 0x7F,
    KEY_F17                 = 0x80,
    KEY_F18                 = 0x81,
    KEY_F19                 = 0x82,
    KEY_F20                 = 0x83,
    KEY_F21                 = 0x84,
    KEY_F22                 = 0x85,
    KEY_F23                 = 0x86,
    KEY_F24                 = 0x87,

    KEY_NUMLOCK             = 0x90,
    KEY_SCROLL              = 0x91,

    KEY_OEM_NEC_EQUAL       = 0x92, // '=' key on numpad

    KEY_OEM_FJ_JISHO        = 0x92, // 'Dictionary' key
    KEY_OEM_FJ_MASSHOU      = 0x93, // 'Unregister word' key
    KEY_OEM_FJ_TOUROKU      = 0x94, // 'Register word' key
    KEY_OEM_FJ_LOYA         = 0x95, // 'Left OYAYUBI' key
    KEY_OEM_FJ_ROYA         = 0x96, // 'Right OYAYUBI' key

    KEY_LSHIFT              = 0xA0,
    KEY_RSHIFT              = 0xA1,
    KEY_LCONTROL            = 0xA2,
    KEY_RCONTROL            = 0xA3,
    KEY_LMENU               = 0xA4,
    KEY_RMENU               = 0xA5,

    KEY_BROWSER_BACK        = 0xA6,
    KEY_BROWSER_FORWARD     = 0xA7,
    KEY_BROWSER_REFRESH     = 0xA8,
    KEY_BROWSER_STOP        = 0xA9,
    KEY_BROWSER_SEARCH      = 0xAA,
    KEY_BROWSER_FAVORITES   = 0xAB,
    KEY_BROWSER_HOME        = 0xAC,

    KEY_VOLUME_MUTE         = 0xAD,
    KEY_VOLUME_DOWN         = 0xAE,
    KEY_VOLUME_UP           = 0xAF,
    KEY_MEDIA_NEXT_TRACK    = 0xB0,
    KEY_MEDIA_PREV_TRACK    = 0xB1,
    KEY_MEDIA_STOP          = 0xB2,
    KEY_MEDIA_PLAY_PAUSE    = 0xB3,
    KEY_LAUNCH_MAIL         = 0xB4,
    KEY_LAUNCH_MEDIA_SELECT = 0xB5,
    KEY_LAUNCH_APP1         = 0xB6,
    KEY_LAUNCH_APP2         = 0xB7,

    KEY_OEM_1               = 0xBA, // ';:' for US
    KEY_OEM_PLUS            = 0xBB, // '+' any country
    KEY_OEM_COMMA           = 0xBC, // ',' any country
    KEY_OEM_MINUS           = 0xBD, // '-' any country
    KEY_OEM_PERIOD          = 0xBE, // '.' any country
    KEY_OEM_2               = 0xBF, // '/?' for US
    KEY_OEM_3               = 0xC0, // '`~' for US

    KEY_OEM_4               = 0xDB, //  '[{' for US
    KEY_OEM_5               = 0xDC, //  '\|' for US
    KEY_OEM_6               = 0xDD, //  ']}' for US
    KEY_OEM_7               = 0xDE, //  ''"' for US
    KEY_OEM_8               = 0xDF,

    KEY_OEM_AX              = 0xE1, //  'AX' key on Japanese AX kbd
    KEY_OEM_102             = 0xE2, //  "<>" or "\|" on RT 102-key kbd.
    KEY_ICO_HELP            = 0xE3, //  Help key on ICO
    KEY_ICO_00              = 0xE4, //  00 key on ICO

    KEY_PROCESSKEY          = 0xE5,

    KEY_ICO_CLEAR           = 0xE6,

    KEY_PACKET              = 0xE7,

    KEY_OEM_RESET           = 0xE9,
    KEY_OEM_JUMP            = 0xEA,
    KEY_OEM_PA1             = 0xEB,
    KEY_OEM_PA2             = 0xEC,
    KEY_OEM_PA3             = 0xED,
    KEY_OEM_WSCTRL          = 0xEE,
    KEY_OEM_CUSEL           = 0xEF,
    KEY_OEM_ATTN            = 0xF0,
    KEY_OEM_FINISH          = 0xF1,
    KEY_OEM_COPY            = 0xF2,
    KEY_OEM_AUTO            = 0xF3,
    KEY_OEM_ENLW            = 0xF4,
    KEY_OEM_BACKTAB         = 0xF5,

    KEY_ATTN                = 0xF6,
    KEY_CRSEL               = 0xF7,
    KEY_EXSEL               = 0xF8,
    KEY_EREOF               = 0xF9,
    KEY_PLAY                = 0xFA,
    KEY_ZOOM                = 0xFB,
    KEY_NONAME              = 0xFC,
    KEY_PA1                 = 0xFD,
    KEY_OEM_CLEAR           = 0xFE,
};

// 游戏控制器数据结构
typedef struct _input_gc_t 
{
    uint16_t    buttons;
    uint8_t     lt;
    uint8_t     rt;
    int16_t     lx;
    int16_t     ly;
    int16_t     rx;
    int16_t     ry;
} input_gc_t;

// 触摸类型
enum TOUCH_TYPE
{
    TOUCH_DOWN      = 0, 
    TOUCH_UP        = 1, 
    TOUCH_MOVE      = 2, 
    TOUCH_CANCEL    = 3, 
};


static const int SEND_KEY_DOWN = 1;
static const int SEND_KEY_UP = (1 << 1);
static const int SEND_PAD_TOUCH_DOWN = (1 << 2);
static const int SEND_PAD_MOVE = (1 << 3);
static const int SEND_PAD_TOUCH_UP = (1 << 4);

static const int PLAY_VIDEO = 1;//播放视频
static const int PLAY_AUDIO = (1 << 1);//播放音频
static const int PLAY_SUBTITLE = (1 << 2);//播放字幕


//播放类型
enum CLIENT_TYPE
{
	PLAY_DEMO = 0,
	PLAY_REDFINGER
};

//应用场景
enum USED_CASE
{
	PLAY_PC = 0,
	PLAY_PHONE
};

//协议类型
enum PROTOCOL_TYPE
{
	PLAY_WEB = 0,
	PLAY_TCP
};

#define MAKE_PLAYING_TYPE(ct, uc, pt) ( (pt << 8) | (uc << 4) | ct) 
#define GET_CLIENT_TYPE(type) (type & 0xff)
#define GET_USED_CASE(type) ((type >> 4) & 0xff)
#define GET_PROTOCOL_TYPE(type) ((type >> 8) & 0xff)

// 播放类型
// static const int PLAY_DEMO = 1; //试玩
// static const int PLAY_REDFINGER = (1 << 1);//云游戏
// 应用场景
// static const int PLAY_PC = (1 << 4);//电脑端
// static const int PLAY_PHONE = (1 << 5);//手机端
// 协议类型
// static const int PLAY_WEB = (1 << 8);//web协议
// static const int PLAY_TCP = (1 << 9);//tcp协议

CSPROTO_API_END

#endif
