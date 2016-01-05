#pragma once
#define DVS_API extern "C" __declspec(dllexport)
//#include "../src/MakeVer.h"
#define _3531_Version
//新dvr数据结构
#define DVS_MAX_SOLO_CHANNEL_16			16
#define DVS_MAX_SYSTEM_NAME_LEN			16	//系统名称最长字数
#define DVS_MAX_PTZ_NAME_LEN			16	//云台的名字长度
#define DVS_MAX_PTZ_NAME_SHOW			14	//云台名字显示长度
#define DVS_MAX_DEVICE_TYPE_NAME_LEN	8
#define MAX_NET_DAY_FILE_NUM			1024//发送某一天的录像文件名的时候最多一次发送的数量

#define DVX_MAX_WEEKDAYS				7
#define DVX_MAX_DAYHOURS				24
#define DVX_MAX_SENSOR_LEN			    16
#define DVX_MAX_VIDEOLINE				18
#define DVX_MAX_DDNSNAME				20//16//DDNS用户名长//11-11-02修改
#define DVX_MAX_DDNSNAME_OLD			16//11-11-02添加
#define DVX_MAX_DDNSNAME_32            32//12-9-12
#define DVX_MAX_DNSPWD					20//8//DDNS用户密码长度//11-11-02修改
#define DVX_MAX_DNSPWD_OLD				8//11-11-02添加
#define DVX_MAX_DOMAINLEN				32
#define DVX_MAX_EMAIL_NAME				32
#define DVX_MAX_EMAIL_PWD				20//16//11-11-02修改
#define DVX_MAX_EMAIL_PWD_OLD			16//11-11-02添加
#define DVX_MAX_EMAIL_SSL				32
#define DVX_MAX_EMAIL_SMTP				32
#define DVX_MAX_USERNAME				8
#define DVX_MAX_USERPWD					8
#define DVX_MAX_WATERKEY				16
#define DVX_MAX_SYSNAME					16
#define DVX_MAX_DISK_NAME				128
#define DVX_MAX_DISK_MOUNTPATH			128
#define DVX_MAX_DISK_NODE				12
#define DVX_MAX_HARDDISK_NUM			4	//系统最大硬盘数量
#define DVX_MAX_USERNUM					15
#define MAX_PTZ_PATTERN_POSITIONS		20
#define MAX_PTZ_PATTERN_POSITIONS_VER4	256
#define MAX_CHECK_INTERVAL_LEN  8   //DDNS更新时间的字符长度   2012.09.21 邱工添加

/****************** 数据类型预定义******************/
typedef unsigned char			UNS8;	/* 8-bit */
typedef unsigned short			UNS16;	/* 16-bit */
typedef unsigned int			UNS32;	/* 32-bit */
typedef unsigned __int64		UNS64;	/* 64-bit */
typedef char					S8;		/* 8-bit */
typedef short					S16;	/* 16-bit */
typedef int						S32;	/* 32-bit */
typedef __int64					S64;	/* 64-bit */


enum DVXVIDEO_QUALITY
{
	VQUALITY_SUPER_LOW,	//超低画质
	VQUALITY_LOW,			//低画质
	VQUALITY_NORMAL,		//普通画质
	VQUALITY_HIGH,			//高画质
	VQUALITY_SUPER_HIGH,	//超高画质
	VQUALITY_CBR_64K,		//CBR-64K
	VQUALITY_CBR_256K,		//CBR-256K
	VQUALITY_CBR_512K,		//CBR-512K
	VQUALITY_CBR_1024K,		//CBR-1024K
	VQUALITY_CBR_2048K,		//CBR-2048K	
	VQUALITY_MAX,
};

enum DVXVIDEO_RATE
{
	VRATE_OFF,
	VRATE_LEVEL1,  //PAL: 1;     NTSC: 1
	VRATE_LEVEL2,  //PAL: 2.5;   NTSC: 2
	VRATE_LEVEL3,  //PAL: 6.25;  NTSC: 6
	VRATE_LEVEL4,  //PAL: 12.5  NTSC:15
	VRATE_LEVEL5, //PAL: 25     NTSC:30
	VRATE_BUFFER,
	VRATE_MAX,
};	//帧速率模式

enum DNSSERVER
{
	DVX_CN3322,
	DVX_DYNDNS,
	DVX_VERSIONDEFINE,//nightowl, xixvision, myqsee, everfocus, changeip,DVX_ATLUPD,
	DVX_DDNSNOIP,
	DVX_DDNSORAY,
	DVX_DDNSLEANDINGDVR,	
	MAX_DNSSERVER
};

struct DVXRECBASICSETUP//对应REC_BASIC_SETUP
{
	DVXVIDEO_QUALITY	RecordQuality;                          //画质: 超低、低、普通、高、超高
	DVXVIDEO_RATE		RecordRate;	                            //录像帧速率，待定 2、6、12、25
	DVXVIDEO_RATE		PreRecOn;		                        //预录像设置，待定 2、6
	UNS8		RecordPlan[DVX_MAX_WEEKDAYS][DVX_MAX_DAYHOURS]; //录像计划,实际采用RECORD_MODE枚举型,用其中的0,2,3,4
	UNS8		Resolution;	                                    //三种:D1,HD1, CIF，实际采用VIDEO_SIZE枚举型
	UNS8		AudioChannel;	                                //录像的音频通道,0=关闭,或1~4
	UNS16		reserved;
};

typedef enum
{	
	DVX_OVERWRITE_OFF = 0,	      // 关闭
	DVX_OVERWRITE_AUTO,           // 自动
	DVX_OVERWRITE_ONE_DAY,        // 1 天
	DVX_OVERWRITE_SEVEN_DAYS,     // 7 天
	DVX_OVERWRITE_THIRTY_DAYS,    //30 天
	DVX_OVERWRITE_NINETY_DAYS,    //90 天
	DVX_OVERWRITE_MAX
}DVX_OVERWRITE_STATE; //循环覆盖，对应OVERWRITE_STATE

struct DVX_RECSETUP//对应RECORDSETUP
{
	UNS8				TailOverWrite;	                      /*硬盘满覆盖，DVX_OVERWRITE_STATE*/
	UNS8				OverlayTime;                         /*叠加时间信息 TRUE=叠加， FALSE = 不叠加*/
	UNS16				res;
	DVXRECBASICSETUP	RecBasic[DVS_MAX_SOLO_CHANNEL_16 + 1]; //录像设置(0~15,all)
};
//wuzy 2012.5.11 增加遮挡功能
typedef struct{
	UNS16 x;
	UNS16 y;
	UNS16 w;
	UNS16 h;
	UNS32 reserved;
}AreaAttr_BJ;
typedef struct {
	UNS8 ChanelState;  // 1:开  0:关
	UNS8 reseved1;
	UNS8 reseved2;
	UNS8 reseved3;
	UNS8 SelectArea[4];         // 1:hook  0: no
	AreaAttr_BJ AreaAttr[4];
}privacyzone_BJ;

///////////////////////////////////////////////////////////////////////////////
//摄像枪设置
//带隐私遮挡功能
struct DVX_CAMERAOPTS//对应CAMERASETUP
{
	UNS8	PTZName[DVS_MAX_PTZ_NAME_LEN];	//云台的名称
	UNS32	PTZModel;	//协议类型:
	UNS32	BaudRate;    //波特率:1200,2400,4800,9600
	UNS32	PTZAddr;	//每个云台的地址码
	S16		HUE;	//色调   -128~127
	S16		SAT;	//饱和度  0~255
	S16		CONT;	//对比度  0~255
	S16		BRT;	//亮度   -128~127
	UNS8	PanSpeed;	//云台控制速率级别
	UNS8	TiltSpeed;	//云台光圈速率级别	
	UNS8	HDelay; //horizontal delay -8~8,用于去掉画面左侧或右侧的黑边
	UNS8	VDelay; //vertical delay 垂直黑边
	privacyzone_BJ privacyzone;

};

//不带隐私遮挡功能
struct DVX_CAMERAOPTS_NO_PRIVACYZONE//对应CAMERASETUP
{
	UNS8	PTZName[DVS_MAX_PTZ_NAME_LEN];	//云台的名称
	UNS32	PTZModel;	//协议类型:
	UNS32	BaudRate;    //波特率:1200,2400,4800,9600
	UNS32	PTZAddr;	//每个云台的地址码
	S16		HUE;	//色调   -128~127
	S16		SAT;	//饱和度  0~255
	S16		CONT;	//对比度  0~255
	S16		BRT;	//亮度   -128~127
	UNS8	PanSpeed;	//云台控制速率级别
	UNS8	TiltSpeed;	//云台光圈速率级别	
	UNS8	HDelay; //horizontal delay -8~8,用于去掉画面左侧或右侧的黑边
	UNS8	VDelay; //vertical delay 垂直黑边

};


struct DVX_CAMERASETUP
{
	DVX_CAMERAOPTS opts[DVS_MAX_SOLO_CHANNEL_16 + 1];
};

struct DVX_CAMERASETUP_NO_PRIVACYZONE
{
	DVX_CAMERAOPTS opts[DVS_MAX_SOLO_CHANNEL_16 + 1];
};
////////////////////////////////////////////////////////////////////////////////

//事件设置
/******************** Event Setup *************************************/
struct DVX_ES_WARNING//对应ES_WARNING
{
	UNS8	EventName[DVX_MAX_SENSOR_LEN];	//报警器名称
	UNS32	SensorOut;	//报警输出 从低位算起，每1bit为一个
	UNS32	RecChannel;	//录像通道号 从低位算起，每1bit为一个通道
	UNS32	ContinueTime;//持续时间,单位是：秒, 3,5,10,20,30,60,120,180,300,600,900,1200
	UNS8	InOpenSensor;//常开型 常关型
	UNS8	OutOpenSensor;	//报警输出是常开型 本部分没有通过界面配置
	UNS8	MainSwitch;	//主显示器切换 0=关闭,或1~16
	UNS8	SpotSwitch;	//SPOT显示器切换	0=关闭，或1~16
	UNS8	PTZGroup;	//操作云台号 0=关闭 通道从1开始 
	UNS8	PTZCall;	//调用云台预置位号
	UNS8	PTZCancel;	//正常调用云台预置位号
	UNS8	BeepOn;	//蜂鸣器开关，0=关闭,1=打开
	UNS8	SendMail; //发送邮件；
	UNS8	res1;
	UNS16	res2;
};

struct DVX_ES_MOTION//对应ES_MOTION
{
	UNS32	MotionArea[DVX_MAX_VIDEOLINE];	//每一行用一个数字表示，数字每一bit表示一个区域，最低位表示最右边块
	//如果整屏，那就对应都为TRUE，如果清屏，那就都为FALSE.
	UNS32	RecChannel;	//录像通道号 从低位算起，每1bit为一个通道
	UNS32	ContinueTime;//持续录像时间	单位是：秒
	UNS32	SensorOut;	//报警输出 从低位算起，每1bit为一个	
	
	UNS8	Threshold;	//灵敏度
	UNS8	MainSwitch;	//主显示器切换
	UNS8	SpotSwitch;	//SPOT显示器切换	0=off
	UNS8	BeepOn;	//蜂鸣器开关
	
	UNS8	SendMail;//发送邮件 1 = 发送， 0 = 不发送
	UNS8	res1;
	UNS16	res2;
};

struct DVX_ES_HARDDISK//对应ES_HARDDISK
{
	UNS32	ContinueTime;//持续录像时间	单位是：秒
	UNS32	SensorOut;	//从低位算起，每1bit为一个输出报警
	UNS8	BeepOn;	//蜂鸣器开关
	UNS8	SendMail;  //发送邮件；
	UNS16	res;
};

struct DVX_ES_VIDEOLOSS//对应ES_VIDEOLOSS
{
	UNS32	ContinueTime;//持续录像时间	单位是：秒
	UNS32	SensorOut;	//报警输出 从低位算起，每1bit为一个输出报警
	UNS8	BeepOn;	//蜂鸣器开关
	UNS8	SendMail;  //发送邮件
	UNS16	res;
};

struct DVX_ES_VIDEOMASK
{
	UNS32	ContinueTime;//持续录像时间	单位是：秒
	UNS32	SensorOut;	//报警输出 从低位算起，每1bit为一个输出报警
	UNS8	BeepOn;	//蜂鸣器开关
	UNS8	SendMail;  //发送邮件
	UNS16	res;
};

struct DVX_ES_PWD//对应ES_PASSWD
{
	UNS32	ContinueTime;//持续录像时间	单位是：秒
	UNS32	SensorOut;	//报警输出 从低位算起，每1bit为一个输出报警
	UNS8	BeepOn;	//蜂鸣器开关
	UNS8	SendMail; //发送邮件
	UNS16	res;
};

struct DVX_EVENTSETUP//对应EVENTSETUP
{
	DVX_ES_WARNING		WARNING[DVS_MAX_SOLO_CHANNEL_16 + 1];	//报警设置
	DVX_ES_MOTION		Motion[DVS_MAX_SOLO_CHANNEL_16 + 1];	//动态侦测设置
	DVX_ES_HARDDISK		Harddisk;	              //磁盘设置
	DVX_ES_VIDEOLOSS	VideoLoss;	              //视频丢失错误
	DVX_ES_VIDEOMASK	VideoMask;
	DVX_ES_PWD			Pwd;	                    //密码错误
};

/******************** Display setup *******************************************/
struct DVX_VGASETUP//对应VGASETUP
{
	UNS32	MainInterval;	//主显示轮换通道间隔时间,1,2,3,5,10,15,20,30,40,50,60,120,180,300,600
	UNS32	SpotInterval;	//SPOT间隔,同上	
	UNS8	IgnoreVideoLoss;	//忽略视频丢失,TRUE=是,FALSE=否	
	UNS8	VGAMode;	//VGA类型,800x600@60=7,1024x768@60=8,1280x1024@60=9
	S16		reserved;
	S16		UpSide;            //上侧边距
	S16		DownSide;          //下侧边距
	S16		LeftSide;         //左侧边距
	S16		RightSide;        //右侧边距

#ifdef _3531_Version
	S16 ViewTimeDisplayPos; //预览状态下时间条显示位置。可选择的位置:    //2012.04.25 //wl
	//0:左上，1:右上，2:左下，3:右下，4:上中，5:下中
	S16 CHNameDisplayPos; //预览和回放下通道名称显示位置，所有通道一致   //2012.04.25 //wl
	//可选择的位置:0:左上，1:右上，2:左下。没有右下，因为右下要显示R,H,M等标志。
#endif

	

};

/******************** Network Setup *************************************/
struct DVX_NETSETUP_VER1//对应NETSETUP
{
	UNS32	IP; //IP 地址
	UNS32	NetMask;	//子网掩码
	UNS32	Gateway;	//网关地址
	UNS8	mac[20];
	UNS32	NTP; //NTP Server地址
	UNS32	HttpPort; 
	UNS32	ViewPort;	//视频监控端口
	UNS32	BackupPort;	//网络备份端口
	UNS32	SysPort;	//系统配置端口
	UNS32	RemoteAudioPort;	//远程音频端口
	UNS8	NetAccess;//网络接入方式
	UNS8	UPNPSwitch;
	UNS8	NetEncSwitch;	//开启双码流开关
	UNS8	EncResolution[DVS_MAX_SOLO_CHANNEL_16 + 1]; //CIF, QCIF,实际采用VIDEO_SIZE枚举型
	DVXVIDEO_QUALITY	NetEncQuality[DVS_MAX_SOLO_CHANNEL_16 + 1]; //画质
	DVXVIDEO_RATE		NetEncRate[DVS_MAX_SOLO_CHANNEL_16 + 1];	//帧速率
	DNSSERVER			DDNSServer;	//DDNS服务提供商
	UNS8	DDNSName[DVX_MAX_DDNSNAME_OLD];
	UNS8	DDNSPass[DVX_MAX_DNSPWD_OLD];
	UNS8	DDNSDomain[DVX_MAX_DOMAINLEN];
	UNS8	DDNSSwitch;	//DDNS开关标志
	UNS8	EMAILSwitch;    //EMAIL开关标志
	UNS8	reserved;
	UNS8 	PPPOESwitch;  //PPPOE 开关标志
	UNS8	PPPOEUserName[DVX_MAX_EMAIL_NAME];
	UNS8	PPPOEPass[DVX_MAX_EMAIL_PWD_OLD];
	UNS8	EMAILSName[DVX_MAX_EMAIL_NAME];
	UNS8	EMAILPass[DVX_MAX_EMAIL_PWD_OLD];
	UNS8	EMAIL_SSL[DVX_MAX_EMAIL_SSL];
	UNS8	EMAILRName[DVX_MAX_EMAIL_NAME];
	UNS8	EMAILSMTP[DVX_MAX_EMAIL_SMTP];	
	UNS32	EMAILSMTP_Port;
	UNS32	MobilePort;	
	UNS32	DNS1;
	UNS32	DNS2;
};

struct DVX_NETSETUP_VER2//对应NETSETUP
{
	UNS32	IP; //IP 地址
	UNS32	NetMask;	//子网掩码
	UNS32	Gateway;	//网关地址
	UNS8	mac[20];
	UNS32	NTP; //NTP Server地址
	UNS32	HttpPort; 
	UNS32	ViewPort;	//视频监控端口
	UNS32	BackupPort;	//网络备份端口
	UNS32	SysPort;	//系统配置端口
	UNS32	RemoteAudioPort;	//远程音频端口
	UNS8	NetAccess;//网络接入方式
	UNS8	UPNPSwitch;
	UNS8	NetEncSwitch;	//开启双码流开关
	UNS8	EncResolution[DVS_MAX_SOLO_CHANNEL_16 + 1]; //CIF, QCIF,实际采用VIDEO_SIZE枚举型
	DVXVIDEO_QUALITY	NetEncQuality[DVS_MAX_SOLO_CHANNEL_16 + 1]; //画质
	DVXVIDEO_RATE		NetEncRate[DVS_MAX_SOLO_CHANNEL_16 + 1];	//帧速率
	DNSSERVER			DDNSServer;	//DDNS服务提供商
	UNS8	DDNSName[DVX_MAX_DDNSNAME_OLD];
	UNS8	DDNSPass[DVX_MAX_DNSPWD_OLD];
	UNS8	DDNSDomain[DVX_MAX_DOMAINLEN];
	UNS8	DDNSSwitch;	//DDNS开关标志
	UNS8	EMAILSwitch;    //EMAIL开关标志
	UNS8 	PPPOESwitch;  //PPPOE 开关标志
	UNS8	PPPOETeleTial;  //0: 有线; 1: 3G    //新增
	UNS8	PPPOETelephone[DVX_MAX_EMAIL_NAME];  //新增
	UNS8	PPPOEUserName[2][DVX_MAX_EMAIL_NAME];//修改
	UNS8	PPPOEPass[2][DVX_MAX_EMAIL_PWD_OLD];//修改
	UNS8	EMAILSName[DVX_MAX_EMAIL_NAME];
	UNS8	EMAILPass[DVX_MAX_EMAIL_PWD_OLD];
	UNS8	EMAIL_SSL[DVX_MAX_EMAIL_SSL];
	UNS8	EMAILRName[DVX_MAX_EMAIL_NAME];
	UNS8	EMAILSMTP[DVX_MAX_EMAIL_SMTP];	
	UNS32	EMAILSMTP_Port;
	UNS32	MobilePort;	
	UNS32	DNS1;
	UNS32	DNS2;
};

struct DVX_NETSETUP_VER3//对应NETSETUP
{
	UNS32	IP; //IP 地址
	UNS32	NetMask;	//子网掩码
	UNS32	Gateway;	//网关地址
	UNS8	mac[20];
	UNS32	NTP; //NTP Server地址
	UNS32	HttpPort; 
	UNS32	ViewPort;	//视频监控端口
	UNS32	BackupPort;	//网络备份端口
	UNS32	SysPort;	//系统配置端口
	UNS32	RemoteAudioPort;	//远程音频端口
	UNS8	NetAccess;//网络接入方式
	UNS8	UPNPSwitch;
	UNS8	NetEncSwitch;	//开启双码流开关
	UNS8	EncResolution[DVS_MAX_SOLO_CHANNEL_16 + 1]; //CIF, QCIF,实际采用VIDEO_SIZE枚举型
	DVXVIDEO_QUALITY	NetEncQuality[DVS_MAX_SOLO_CHANNEL_16 + 1]; //画质
	DVXVIDEO_RATE		NetEncRate[DVS_MAX_SOLO_CHANNEL_16 + 1];	//帧速率
	DNSSERVER			DDNSServer;	//DDNS服务提供商
	UNS8	DDNSName[DVX_MAX_DDNSNAME];
	UNS8	DDNSPass[DVX_MAX_DNSPWD];
	UNS8	DDNSDomain[DVX_MAX_DOMAINLEN];
	UNS8	DDNSSwitch;	//DDNS开关标志
	UNS8	EMAILSwitch;    //EMAIL开关标志
	UNS8 	PPPOESwitch;  //PPPOE 开关标志
	UNS8	PPPOETeleTial;  //0: 有线; 1: 3G    //新增
	UNS8	PPPOETelephone[DVX_MAX_EMAIL_NAME];  //新增
	UNS8	PPPOEUserName[2][DVX_MAX_EMAIL_NAME];//修改
	UNS8	PPPOEPass[2][DVX_MAX_EMAIL_PWD];//修改
	UNS8	EMAILSName[DVX_MAX_EMAIL_NAME];
	UNS8	EMAILPass[DVX_MAX_EMAIL_PWD];
	UNS8	EMAIL_SSL[DVX_MAX_EMAIL_SSL];
	UNS8	EMAILRName[DVX_MAX_EMAIL_NAME];
	UNS8	EMAILSMTP[DVX_MAX_EMAIL_SMTP];	
	UNS32	EMAILSMTP_Port;
	UNS32	MobilePort;	
	UNS32	DNS1;
	UNS32	DNS2;
};

struct DVX_NETSETUP_VER4//对应NETSETUP
{
	UNS32	IP; //IP 地址
	UNS32	NetMask;	//子网掩码
	UNS32	Gateway;	//网关地址
	UNS8	mac[20];
	UNS32	NTP; //NTP Server地址
	UNS32	HttpPort; 
	UNS32	ViewPort;	//视频监控端口
	UNS32	BackupPort;	//网络备份端口
	UNS32	SysPort;	//系统配置端口
	UNS32	RemoteAudioPort;	//远程音频端口
	UNS8	NetAccess;//网络接入方式,  0: static IP; 1:DHCP
	UNS8	UPNPSwitch;
	UNS8	NetEncSwitch;	//开启双码流开关
	UNS8	EncResolution[DVS_MAX_SOLO_CHANNEL_16 + 1]; //CIF, QCIF,实际采用VIDEO_SIZE枚举型
	DVXVIDEO_QUALITY	NetEncQuality[DVS_MAX_SOLO_CHANNEL_16 + 1]; //画质
	DVXVIDEO_RATE		NetEncRate[DVS_MAX_SOLO_CHANNEL_16 + 1];	//帧速率
	DNSSERVER			DDNSServer;	//DDNS服务提供商
	UNS8	DDNSName[DVX_MAX_DDNSNAME];
	UNS8	DDNSPass[DVX_MAX_DNSPWD];
	UNS8	DDNSDomain[DVX_MAX_DOMAINLEN];
	UNS8	DDNSSwitch;	//DDNS开关标志
	UNS8	EMAILSwitch;    //EMAIL开关标志
	UNS8 	PPPOESwitch;  //PPPOE 开关标志
	UNS8	PPPOETeleTial;  //PPPOE_TYPE, 0: 有线; 1: 3G CDMA; 2: 3G WCDMA;
	UNS8	PPPOETelephone[3][DVX_MAX_EMAIL_NAME]; //由1个改为3个，//但是有线的时候[0]不用,//只用[1]和[2]
	UNS8	PPPOEUserName[3][DVX_MAX_EMAIL_NAME]; //由2个改为3个
	UNS8	PPPOEPass[3][DVX_MAX_EMAIL_PWD];  //由2个改为3个
	UNS8	PPPOE_APN[DVX_MAX_EMAIL_NAME]; //新增
	UNS8	EMAILSName[DVX_MAX_EMAIL_NAME];
	UNS8	EMAILPass[DVX_MAX_EMAIL_PWD];
	UNS8	EMAIL_SSL[DVX_MAX_EMAIL_SSL];
	UNS8	EMAILRName[DVX_MAX_EMAIL_NAME];
	UNS8	EMAILRName2[DVX_MAX_EMAIL_NAME]; //新增，菜单暂不修改
	UNS8	EMAILRName3[DVX_MAX_EMAIL_NAME]; ////新增，菜单暂不修改
	UNS8	EMAILSMTP[DVX_MAX_EMAIL_SMTP];
	UNS32	EMAILSMTP_Port;
	UNS32	MobilePort;
	UNS32	DNS1;
	UNS32	DNS2;
	UNS16	EmailInterval;//Email发送间隔，单位是秒
//	UNS16	reserved;

	UNS8 DDNSEMAIL[DVX_MAX_EMAIL_SMTP];                   //                      2012.9.10
	UNS8 DDNSEMAILSWITCH;
	UNS8 reserved;
	UNS8 CheckIPInterval[MAX_CHECK_INTERVAL_LEN];  //检查IP时间间隔    2012.09.21 邱工添加

};

/******************** System Setup *************************************/
enum DVX_SUMMER_TIMES
{
	DVX_SUMMER_OFF,	//关闭
	DVX_SUMMER_EUROPE,	//欧洲
	DVX_SUMMER_AMERICA,	//美国
	DVX_SUMMER_AUSTRILIA	//澳大利亚
}; //夏令时

typedef enum{	
	DVX_LANGUAGE_CHINESE_SIMPLE = 0,	//简体中文		
	DVX_LANGUAGE_ENGLISH,				//英文	
	DVX_LANGUAGE_RUSSIAN,               //俄语
	DVX_LANGUAGE_KEREAN,				//韩文	
	DVX_LANGUAGE_JAPANESE,				//日文	
	DVX_LANGUAGE_TAILAND,				//泰国文
	DVX_LANGUAGE_CHINESE_TRIDATIONAL,	//繁体中文
	DVX_LANGUAGE_FRANCH,                //法语
	DVX_LANGUAGE_SPANISH,               //西班牙语
	DVX_LANGUAGE_ETALIAN,               //意大利语
	DVX_LANGUAGE_GERMAN,                //德语
	DVX_LANGUAGE_HUNGARIAN,				//匈牙利语
	DVX_LANGUAGE_POLISH,				//波兰语
	DVX_LANGUAGE_PORTUGUESE, 			//葡萄牙语
	DVX_LANGUAGE_GREEK,					//希腊语
	DVX_LANGUAGE_TURKISH,				//土耳其语
	DVX_LANGUAGE_HEGREW,				//希伯来语
	DVX_LANGUAGE_FARSI,					//波斯语
	DVX_LANGUAGE_ARABIC,				//阿拉伯语
	DVX_LANGUAGE_THAI,					//泰语	
	DVX_LANGUAGE_DUTCH,                 //荷兰语
}DVX_SYSTEM_LANGUAGE;

enum DVX_DATE_FORMAT
{
	DVX_YEAR_MON_DAY =1,
	DVX_DAY_MON_YEAR,
	DVX_MON_DAY_YEAR
};

enum DVX_DISK_FORMAT_TYPE
{
	DVX_FORMAT_NULL,	//无操作
	DVX_FORMAT_INNER,	//内置
	DVX_FORMAT_OUTER,	//外置
	DVX_FORMAT_SYSLOG,	//系统日志
	DVX_FORMAT_EVENTLOG,	//事件日志
};	//硬盘格式化类型
typedef struct{ 
	S8 IntervaDay;	//重启间隔，天单位
	S8 Hour;	//重启时间点小时
	S8 Minute;	//重启时间点分
	S8 Second;	//重启时间点秒
}AutoMaintainRestart;
struct DVX_SYSSETUP//对应SYSSETUP
{
	UNS32	            MagicNum;	                    /*校验值*/
	UNS8	            PowerPwd[DVX_MAX_USERPWD];	  //开关机密码,保留
	DVX_SUMMER_TIMES	SummerTimes;	        //夏令时
	DVX_DATE_FORMAT	    DateFormat;	          //日期格式
	UNS8	            SystemName[DVX_MAX_SYSNAME];  //系统名称
	DVX_SYSTEM_LANGUAGE	Language;	          //系统语言
	DVX_DISK_FORMAT_TYPE FormatType;	      //硬盘格式化类型	
	UNS32	            AutoLock;		                  //自动锁定时间 0=关闭
	UNS16	            Zone;	                        //时区 内部另外地方存放一个每个时区的正负偏移量
	UNS8	            SmartDetect;	                //硬盘检测开关	TRUE FALSE
	UNS8	            SystemID;	                    //系统ID
	UNS8	            SysUpdate;	                  //系统升级:0系统BIOS,1:系统映像2:系统APP
	
	/*----------- 固定配置 -------------*/
	UNS8	PlayContinue;	//回放的时候，连续跨文件播放  =TRUE
	UNS8	PlayAddTime;	//回放的时候，需要加时间t  =TRUE
	UNS8	VideoMode;    //NTSC, PAL
	UNS32	WaterStrength;	//水印的力度
	UNS8	WaterKey[DVX_MAX_WATERKEY];		//水印的密码
	AutoMaintainRestart AutoRestart;	//!<    系统自动维护重启    bizhong @2012/9/6
};

/******************** 用户 Setup *************************************/
struct USER_LOCALRIGHT//对应LOCALACCESS
{
	UNS32	Search;		//本地搜索权限，单bit控制埠LSB=Channel 1，有效位：[15...0]，bit31为总开关标志位
	UNS8	SysSetup;	//本地配置系统权限
	UNS8	Record;		//本地录像权限
	UNS8	Log;		//本地查看日志权限
	UNS8	PTZ;		//本地调整PTZ控制权限
	UNS8	Backup;		//本地备份权限
	UNS8	res11;
	UNS16	res12;
};

struct USER_NETRIGHT//对应NETACCESS
{
	UNS32	Search;		  //网络搜索权限
	UNS32	NetView;	     //网络监控权限 单bit控制 LSB=Channel 1，有效位：[15...0]，bit31为总开关标志位
	UNS8	SysSetup;	  //网络配置系统权限
	UNS8	Log;		     //网络查看日志权限
	UNS8	PTZ;		     //网络调整PTZ控制权限
	UNS8	SysInfo;	     //网络查看系统信息权限
	UNS8	MobileAccess;  //手机访问
	UNS8	ExtRightBits;  //*modified by zhusy 2012-07-13*/
	UNS16	reserved2;
};

typedef struct{
	UNS8	MainStreamNum; //包括实时监视的主码流、回放、下载连接数
	UNS8	SubStreamNum; //实时监视的子码流连接数
	UNS8	UserNum; // 当前已登录的网络用户数，包括重复登录的用户
	UNS8	reserved;
}NET_LINK_INFO;

struct DVX_USEROPTS//对应USERSETUP
{
	UNS8			ValidUser;	//该用户是否有效
	UNS8			reserved1;
	UNS16			reserved2;
	UNS8			UserName[DVX_MAX_USERNAME];	//用户名
	UNS8			Pwd[DVX_MAX_USERPWD];		//密码	
	USER_LOCALRIGHT	LocalAccess;
	USER_NETRIGHT	NetAccess;	
};

struct DVX_USERSETUP
{
	DVX_USEROPTS opts[DVX_MAX_USERNUM];
};

typedef struct{
	UNS8	presetName;     //预置点名称
	UNS8	residenceTime;  //预置点停留时间
	UNS8	presetIsValid;  //预置点是否有效，实际赋值按BOOL：TRUE或FALSE
	UNS8	reserved;       //预留扩展位
}DVX_PRESETSETUP;

typedef struct{
	DVX_PRESETSETUP	gp_preset_param[MAX_PTZ_PATTERN_POSITIONS];
	UNS32  			presetNumber;         //总的预置点数，0~MAX_PTZ_PATTERN_POSITIONS  20
	UNS8  AutopanStatus;  //自动巡航状态  邱工与8月28号添加，如维护在此之前的版本，注意去掉。
}DVX_PTZSETUP;

typedef struct{
	UNS32			PtzChannel;
	DVX_PRESETSETUP	gp_preset_param[MAX_PTZ_PATTERN_POSITIONS_VER4];
	UNS32  			presetNumber;         //总的预置点数，0~MAX_PTZ_PATTERN_POSITIONS_VER4  256
}DVX_PTZCRUISE,*LPDVX_PTZCRUISE;

struct DVX_SYSFILE
{
	UNS32 StartTime;	//开始时间
	UNS32 EndTime;	//结束时间
};

enum DVX_DISKTYPE
{
	DVXDS_HARDDISK =1,	//硬盘
	DVXDS_USB,			//通过USB接入的硬盘
	DVXDS_CDROM,		//CDROM
	DVXDS_DVDROM,		//DVDROM
	DVXDS_CDRW			//CDRW 刻录机
};	//磁盘种类

enum DVX_DISKSTATUS
{
	DVXDS_NO =1,	//该硬盘不存在
	DVXDS_ERROR,	//硬盘出现错误
	DVXDS_ENOUGH,	//硬盘容量没有满，可用
	DVXDS_FULL		//硬盘已满
};

struct DVX_DISKINFO//对应DISK_INFO
{
	DVX_DISKTYPE	Type;	//磁盘种类
	DVX_DISKSTATUS	Status;	//磁盘状态
	UNS32		TotalSize;	//磁盘总容量大小 以MB为单位
	UNS32		UsedSize;	//磁盘使用容量大小 以MB为单位
	UNS32		Temp;		//磁盘温度
	UNS8		DiskName[DVX_MAX_DISK_NAME]; //磁盘名称
	UNS8		MountPoint[DVX_MAX_DISK_MOUNTPATH];	//如果有磁盘，Mount的目录名称，注意最后加上最后的"/"符号
	UNS8		DevNode[DVX_MAX_DISK_NODE];	// EX: /dev/sda
};

struct DVX_SYSDISK//对应SYS_DISK
{
	DVX_DISKINFO disk[DVX_MAX_HARDDISK_NUM];
};

struct DVX_SYSSTATUS//对应SYS_STATUS_INFO
{
	UNS32		SysVersion;	//系统版本 
	UNS8		FrontVersion;	//前面板版本号
	UNS8		VGAMode;	//PAL NTSC…
	UNS16		temp;   //设备温度
	UNS32		SysIP;	//系统IP地址
	UNS8		SysMAC[6];	//系统MAC地址
	UNS8		SysName[DVX_MAX_SYSNAME];	//系统名称
	UNS32		SysID;		//系统ID
	DVX_SYSFILE	SysFile;	//系统文件的属性
	DVX_SYSDISK	DiskInfo;	//连接到本地的硬盘信息
	UNS32		SysVideoIn;	//每一路视频通道是否有视频 单比特记录 LSB=Channel 1
	UNS32		SysRecordVideo;	//每一路视频是否在录像 单比特记录 LSB=Channel 1
	UNS32		SysRecordAudio;	//每一路音频是否在录音 单比特记录 LSB=Channel 1
	UNS32		SysMotion;	//系统动态感知 单比特记录 LSB=Channel 1
	UNS32		SysSensorIn;	//系统传感器输入 单比特记录 LSB=Channel 1
	UNS32		SysSensorOut;	//系统传感器输出 单比特记录 LSB=Channel 1
	UNS8		ChResolution[DVS_MAX_SOLO_CHANNEL_16]; //D1=0;CIF=1

};//pc0000

typedef enum{
	RECORD_CMD,
	CAMERA_CMD,
	EVENT_CMD,
	DISPLAY_CMD,
	NET_CMD,
	SYSTEM_CMD,
	USER_CMD,
	TIME_CMD,
	ALL_PARAM_CMD
}SETUP_CMD_ID;

enum DVX_SETUP
{
	SETUP_RECORD,
	SETUP_CAMERA,
	SETUP_EVENT,
	SETUP_DISPLAY,
	SETUP_NET,
	SETUP_SYS,
	SETUP_USER,
	SETUP_PTZ,
	SETUP_SYSTIME,
	SETUP_MAX    = 1000,

	//以下命令为只读命令
	CMD_SYSINFO,
};

typedef union
{
	DVX_RECSETUP		RecSet;
	DVX_CAMERASETUP		CameraSetup;
	DVX_CAMERASETUP_NO_PRIVACYZONE CameraSetup_NoPriZone;
	DVX_EVENTSETUP		EventSetup;
	DVX_VGASETUP		VgaSetup;
	DVX_NETSETUP_VER1	NetSetupVer1;
	DVX_NETSETUP_VER2	NetSetupVer2;
	DVX_NETSETUP_VER3	NetSetupVer3;
	DVX_NETSETUP_VER4	NetSetupVer4;
	DVX_SYSSETUP		SysSetup;
	DVX_USERSETUP		UserSetup;
	DVX_PTZSETUP		PtzSetup;
	DVX_PTZCRUISE		PtzCruise;
	UNS32				sysTime;
}DVRSETUP_UNION;

DVS_API BOOL  __stdcall DVX_SetConfig(HANDLE hDvx, int cmd, LPVOID lpvoid, int optSize);
DVS_API int  __stdcall DVX_GetConfig(HANDLE hDvx, int cmd, LPVOID lpvoid, int bufSize, int *pRetLen);


/*added by zhusy 2012-07-12 start*/
DVS_API int  __stdcall DVX_GetConfig_CheckCruise_Ex(HANDLE hDvx, int cmd, LPVOID lpvoid, int bufSize, int *pRetLen);
/*added by zhusy 2012-07-12 end*/


#define DVS_FILE_NAME_LEN				64
#define DVS_MOTION_ROWS					18//动态侦测中，屏幕侦测区域的行数
#define DVS_MOTION_COLS					22//动态侦测中，屏幕侦测区域的列数


//错误类型代号,对应DVS_GetLastError()函数返回值
#define DVS_NOERROR							0					//没有错误
#define DVS_ERROR							1					//未知错误
#define DVS_NOINIT							2					//没有初始化
#define DVS_INVALID_HANDLE					3					//无效的句柄
#define DVS_PARAM_ERROR						4					//用户参数非法
#define DVS_DEVINFO_DATAERROR				5					//传入的设备信息错误
#define DVS_CONFIG_DATAERROR				6					//传入的配置参数错误
#define DVS_NETWORK_ERROR					7					//网络错误
#define DVS_LOGIN_TIMEOUT					8					//登陆超时
#define DVS_LOGIN_PWD_ERROR					9					//登陆密码错误
#define DVS_LOGIN_USER_INVALID				10					//登陆用户名无效
#define DVS_LOGIN_USER_EXIST				11					//该用户已登陆
#define DVS_ADD_USER_EXIST					12					//添加用户名已存在
#define DVS_ADD_USER_FULL					13					//增加用户已满
#define DVS_DEL_USER_NOTEXIST				14					//删除的用户名并不存在
#define DVS_EDIT_USER_NOTEXIST				15					//修改用户的用户名不存在
#define DVS_CUR_STREAMCHANNEL_OPENED		16					//当前实时流通道已被打开
#define DVS_CUR_STREAMCHANNEL_NOTEXIST		17					//当前实时流通道不存在
#define DVS_GET_FILEINDEX_ERROR				18					//获取播放文件索引失败
#define DVS_OPEN_FILE_ERROR					19					//打开文件失败
#define DVS_REAL_ALREADY_SAVING				20					//实时数据已经处于保存状态
#define DVS_SOCKETINIT_ERROR				21					//socket库初始化出错
#define DVS_SEND_PARAM_FAILED				22					//发送参数失败
#define DVS_RECV_PARAM_FAILED				23					//接收参数失败
#define	DVS_VERSION_NOT_MATCH				101					//DVR版本不匹配

typedef enum{  // CIF:1, HD1:2, D1:4
	CIF_ONLY = 1,
	CIF_HD1 = 3,
	D1_ONLY = 4,
	CIF_D1 = 5,
	CIF_HD1_D1 = 7
}RESOLUTION_TYPE;

//设备信息//对应NET_VIEW_INFO
typedef struct
{
	UNS8	SysName[DVS_MAX_SYSTEM_NAME_LEN];	//系统名称
	UNS8	PTZName[DVS_MAX_SOLO_CHANNEL_16][DVS_MAX_PTZ_NAME_LEN];	//云台的名称
	UNS32	PTZModel[DVS_MAX_SOLO_CHANNEL_16]; //云台型号 PTZ_MODEL_NULL=无效
	UNS8	RecResolution[DVS_MAX_SOLO_CHANNEL_16]; //D1=0;CIF=1
	UNS8	NetResolution[DVS_MAX_SOLO_CHANNEL_16]; //
	UNS8	AudioChannel[DVS_MAX_SOLO_CHANNEL_16]; /*每个视频通道对应的音频通道号(1~16)不是按bit的*/
	UNS8	DevTypeName[DVS_MAX_DEVICE_TYPE_NAME_LEN]; /* 如"F"、"L" */
	RESOLUTION_TYPE  ResType;     //所支持的分辨率
	UNS16	Total_RecFrameLimit;       //主码流总帧数
	UNS16	Total_NetFrameLimit;       //次码流总帧数
	UNS8	VideoType; // 0---NTSC, 1---PAL
	UNS8	VideoInNum;   /*视频输入通道*/
	UNS8	AudioInNum;	 /*音频输入通道数*/
	UNS8	SensorInNum;	 /*报警输入通道数*/
	UNS8	SensorOutNum;	 /*报警输出通道数*/
	UNS8	HardDiskNum;      /*内置SATA硬盘数量*/
	UNS8	SpotOutNum;       /* SPOT输出通道数*/
	UNS8	DevType;
	UNS8	SysMAC[6];	//系统MAC地址
	UNS16	res;
	UNS32	langSupport;
}DVS_DEV_INFO,*LPDVS_DEV_INFO;

typedef struct
{
	UNS32	dwYear;
	UNS32	dwMonth;
	UNS32	dwDay;
	UNS32	dwHour;
	UNS32	dwMinute;
	UNS32	dwSecond;
}DVS_TIME,*LPDVS_TIME;

//录像文件信息
typedef struct
{
	UNS32		dwSize;
	UNS8		sFileName[DVS_FILE_NAME_LEN];          //录像文件名
	DVS_TIME	dtStartTime;                           //录像文件起始时间
	DVS_TIME	dtEndTime;                             //录像文件结束时间
	UNS32		dwFileSize;                            //录像文件大小,此处以1M为单位
	S32			type;                         
}DVS_RECORDFILE_INFO,*LPDVS_RECORDFILE_INFO;

typedef struct
{
	UNS32				dwSize;
	UNS32				dwRecordfileListSize;                  //该表能保存录像文件的最大数目
	UNS32				dwRecordfileCount;                     //该表实际保存录像文件数目
    DVS_RECORDFILE_INFO	*pRecordfileList;                 
}DVS_RECORDFILE_LIST,*LPDVS_RECORDFILE_LIST;

//播放控制命令宏定义
#define	DVS_PLAYCTRL_BACKWARD			1                          //快退
#define	DVS_PLAYCTRL_BACKPLAY			2                          //后退
#define DVS_PLAYCTRL_PLAY				3                          //前进
#define	DVS_PLAYCTRL_FORWARD			4                          //快进
#define	DVS_PLAYCTRL_BACKSHIFT			5                          //单帧后退
#define	DVS_PLAYCTRL_SHIFT				6                          //单帧前进
#define	DVS_PLAYCTRL_PAUSE				7                          //当前播放位置暂停
#define	DVS_PLAYCTRL_STOP				8                          //停止，回到播放起始位置 


//云台控制命令定义
typedef enum
{
	DVS_PTZ_CMD_NULL = 0,
	DVS_PTZ_CTRL_STOP,                                             //停止当前正在进行的云台操作
	DVS_PTZ_CTRL_UP,                                               //上
	DVS_PTZ_CTRL_DOWN,                                             //下
	DVS_PTZ_CTRL_LEFT,                                             //左
	DVS_PTZ_CTRL_RIGHT,                                            //右
	DVS_PTZ_CTRL_ZOOM_IN,                                          //焦距变大
	DVS_PTZ_CTRL_ZOOM_OUT,                                         //焦距变小
	DVS_PTZ_CTRL_FOCUS_NEAR,                                       //焦点前调
	DVS_PTZ_CTRL_FOCUS_FAR,                                        //焦点后调
	DVS_PTZ_CTRL_PRESET_SET,                                       //设置预设点，预设点的设置数与云台的设置能力有关
	DVS_PTZ_CTRL_PRESET_GOTO,                                      //调用预设点
	DVS_PTZ_CTRL_CLEARPRESET,                                      //清楚预设点 
	DVS_PTZ_CTRL_IRIS_OPEN,                                        //光圈扩大
	DVS_PTZ_CTRL_IRIS_CLOSE,                                       //光圈缩小
	DVS_PTZ_CTRL_RESETCAMERA,
	DVS_PTZ_CTRL_AUTOPAN,                                          //自动巡航
	DVS_PTZ_CTRL_UPLEFT,
	DVS_PTZ_CTRL_UPRIGHT,
	DVS_PTZ_CTRL_DOWNLEFT,
	DVS_PTZ_CTRL_DOWNRIGHT,
	DVS_PTZ_CTRL_SETZOOMSPEED,
	DVS_PTZ_CTRL_SETFOCUSSPEED,
	DVS_PTZ_CTRL_OSDMENU,                                           //菜单功能       
	DVS_PTZ_CTRL_MENUENTER,
	DVS_PTZ_CTRL_SETPATTERNSTART,
	DVS_PTZ_CTRL_SETPATTERNSTOP,
	DVS_PTZ_CTRL_RUNPATTERN,
	DVS_PTZ_CTRL_STOPPATTERN,										//停止轨迹巡航
	DVS_PTZ_CTRL_MAX_PTZ_CMD,
	DVS_PTZ_CTRL_WRITE_CHAR,

	/*added by zhusy 2012.07.05 start*/
	PTZ_CMD_CRUISE_SET,      //set cruise line
	PTZ_CMD_CRUISE_CLR,      //clear cruise line
	PTZ_CMD_CRUISE_START,    //start cruise
	PTZ_CMD_CRUISE_STOP = 35, //stop cruise
	PTZ_CMD_PRESET_CLEAR = 36 //stop cruise
	/*added by zhusy 2012.07.05 end*/

}DVS_PTZ_CTRL_MODE;

//报警消息定义
typedef struct
{
	UNS32	dwSize;
	UNS32	dwAlarmType;	//报警消息类型,0-外部输入报警，1-动态侦测报警，2-磁盘错误，3-视频丢失，4-密码错误
	UNS32	dwAlarmData;	//dwAlarmType=0,1,3时表示通道号，dwAlarmType=2时表示磁盘号，dwAlarmType=4时该项无效
	UNS32	dwValue;		//dwAlarmType=0时，dwValue=1表示外部输入报警存在，dwValue=0表示外部输入报警取消
							//dwAlarmType=1时，dwValue=1表示有动态侦测报警，dwValue=0表示动态侦测报警取消
							//dwAlarmType=3时，dwValue=1表示有视频丢失，dwValue=0表示dwAlarmData通道视频由无到有
							//dwAlarmType=2,4时，该值无意义
}DVS_ALARM_INFO;

//播放画面信息设置
typedef struct
{
	UNS32	dwSize;
	UNS8	byDateFormat;			//日期格式，0为2009-11-22，1为22-11-2009，2为11-12-2009
	UNS8	byDateCaption;			//日期标题显示位置，0-不显示，1-左上角，2-正上方，3-右上角，4-左下角，5-正下方，6-右下角
	UNS8	byTimeCaption;			//时间标题显示位置，0-不显示，1-左上角，2-正上方，3-右上角，4-左下角，5-正下方，6-右下角
	UNS8	byChannelNameCaption;	//通道名显示位置，0-不显示，1-左上角，2-正上方，3-右上角，4-左下角，5-正下方，6-右下角
	UNS8	bySysNameCaption;		//系统名显示位置，0-不显示，1-左上角，2-正上方，3-右上角，4-左下角，5-正下方，6-右下角    
	UNS8	byReserved[31];
}DVS_ImageInfo,*LPDVS_ImageInfo;

//定义消息回调函数
typedef void (CALLBACK *fMessCallBack)(DWORD dwCommand, HANDLE hDvs, char *pBuf, DWORD dwBufLen, char *pchDeviceIP, WORD wDevicePort, DWORD dwUser);

//返回错误码
DVS_API DWORD  __stdcall DVS_GetLastError(void);

//SDK库的初始化和注销
DVS_API BOOL  __stdcall DVS_Init(void);
DVS_API void  __stdcall DVS_Cleanup(void);

//获取SDK库版本号
DVS_API DWORD __stdcall DVS_GetSDKVersion(void);

//设置连接超时时间和连接次数，目前第二个参数连接次数暂不使用，填NULL
DVS_API void   __stdcall DVS_SetConnectTime(DWORD dwWaitTime, DWORD dwTryTimes);

//登录和注销
DVS_API HANDLE __stdcall DVS_Login(char *pchDeviceIP, WORD wDevicePort, char *pchUserName, char *pchPwd);
DVS_API BOOL   __stdcall DVS_Logout(HANDLE hDvs);

//DVR设备消息获取，包括报警等消息
//设置设备消息回调函数
DVS_API void   __stdcall DVS_SetDVRMessCallBack(fMessCallBack cbMessFunc, DWORD dwUser);
DVS_API BOOL   __stdcall DVS_StartListen(HANDLE hDvs);
DVS_API BOOL   __stdcall DVS_StopListen(HANDLE hDvs);

//获取设备信息
DVS_API BOOL   __stdcall DVS_GetDeviceInfo(HANDLE hDvs, LPDVS_DEV_INFO lpDeviceInfo);

DVS_API BOOL   __stdcall DVS_SpeechStart(HANDLE hDvs);
DVS_API void   __stdcall DVS_SpeechStop(HANDLE hDvs);
DVS_API BOOL   __stdcall DVS_IsOnSpeech(HANDLE hDvs);

//实时流预览函数
DVS_API BOOL   __stdcall DVS_SetStreamType(HANDLE hDvs, int type); // 0=主码流, 1= 子码流, 2=音频流
DVS_API BOOL   __stdcall DVS_OpenRealStream(HANDLE hDvs, char *pchHostIP, WORD wHostPort, DWORD dwChannel, HWND hWnd, HANDLE &hRealHandle);
DVS_API BOOL   __stdcall DVS_CloseRealStream(HANDLE hRealHandle);
DVS_API BOOL   __stdcall DVS_PlayRealStream(HANDLE hRealHandle, CString VideoLoss = NULL);
DVS_API BOOL   __stdcall DVS_StopRealStream(HANDLE hRealHandle);
DVS_API BOOL   __stdcall DVS_PlayRealAudio(HANDLE hDvs, HANDLE hRealHandle, DWORD dwChannel);
DVS_API BOOL   __stdcall DVS_StopRealAudio(HANDLE hRealHandle);
DVS_API BOOL   __stdcall DVS_GetRealBiAudio(HANDLE hRealHandle, unsigned char &biAudio);
DVS_API BOOL   __stdcall DVS_OpenAudioStream(HANDLE hDvs, char *pchHostIP, WORD wHostPort, HANDLE &hRealHandle);
DVS_API BOOL   __stdcall DVS_CloseAudioStream(HANDLE hRealHandle);
DVS_API int    __stdcall DVS_GetRealChnnl(HANDLE hRealHandle);


DVS_API void   __stdcall SetVideoLoss(HANDLE hRealHandle,CString VideoLoss = _T(" ")); //2012.9.3   BOOL IsVideoLoss 默认FALSE


//保存实时流数据文件
DVS_API BOOL   __stdcall DVS_SaveRealDataStart(HANDLE hRealHandle, char *sFileName);
//停止保存实时流数据文件
DVS_API BOOL   __stdcall DVS_SaveRealDataStop(HANDLE hRealHandle);
DVS_API BOOL   __stdcall DVS_IsRecording(HANDLE hRealHandle);
DVS_API BOOL   __stdcall DVS_RealCapBmp(HANDLE hRealHandle, const char* pathname);

//云台控制函数
DVS_API BOOL   __stdcall DVS_PTZControl(HANDLE hDvs, DWORD dwChannel, DWORD dwPTZCommand, DWORD dwParam = NULL);
DVS_API BOOL   __stdcall DVS_PTZCruise(HANDLE hDvs,  LPDVX_PTZCRUISE hPTZCruise);  //2012.06.26

//录像回放与下载
DVS_API BOOL   __stdcall DVS_QueryRecordFile(HANDLE hDvs, DVS_TIME dtStartTime, DVS_TIME dtEndTime, int type, LPDVS_RECORDFILE_LIST lpRecordfileList);
DVS_API UNS32  __stdcall DVS_GetRemoteFileInfo(HANDLE hDvs, char *pchRemoteFileName);
DVS_API BOOL   __stdcall DVS_OpenRemotePlay(HANDLE hDvs, char *pchRemoteFileName, HWND *pHwndList, DWORD dwHwndCount, HANDLE &hPlayHandle);
DVS_API BOOL   __stdcall DVS_CloseRemotePlay(HANDLE hPlayHandle);
DVS_API BOOL   __stdcall DVS_SetRemotePlayChannel(HANDLE hPlayHandle, DWORD dwBitMaskChn);
DVS_API BOOL   __stdcall DVS_RemotePlayControl(HANDLE hPlayHandle, DWORD dwControlCode);
DVS_API BOOL   __stdcall DVS_GetRemotePlayTime(HANDLE hPlayHandle, LPDVS_TIME lpCurPlayTime);
DVS_API BOOL   __stdcall DVS_StartRemotePlayAudio(HANDLE hPlayHandle, DWORD dwChannel);
DVS_API BOOL   __stdcall DVS_StopRemotePlayAudio(HANDLE hPlayHandle, DWORD dwChannel);
DVS_API BOOL   __stdcall DVS_SeekRemotePlay(HANDLE hPlayHandle, DWORD dwType, DWORD64 dwArg);

DVS_API BOOL   __stdcall DVS_DumpOpen(HANDLE hDvs, char *pDumpFile, char *pSaveAs, UNS32 startTime, UNS32 endTime, UNS32 chnnlMask = 0xFFFF, int dumpType = 0, BOOL isOcx = FALSE);
DVS_API void   __stdcall DVS_DumpClose(HANDLE hDvs);
DVS_API int    __stdcall DVS_DumpProgress(HANDLE hDvs);

//本地文件回放
DVS_API BOOL   __stdcall DVS_OpenLocalPlay(char *pchLocalFileName, HWND *pHwndList, DWORD dwHwndCount, HANDLE &hPlayHandle);
DVS_API BOOL   __stdcall DVS_GetDuration(HANDLE hPlay, UINT32 &startTime, UINT32 &endTime);
DVS_API BOOL   __stdcall DVS_GetLocalPlayCurTime(HANDLE hPlayHandle, UINT32 &curTime);
DVS_API BOOL   __stdcall DVS_CloseLocalPlay(HANDLE hPlayHandle);
DVS_API BOOL   __stdcall DVS_SetLocalPlayChannel(HANDLE hPlayHandle, DWORD dwChannel);
DVS_API BOOL   __stdcall DVS_LocalPlayControl(HANDLE hPlayHandle, DWORD dwControlCode);
DVS_API BOOL   __stdcall DVS_StartLocalPlayAudio(HANDLE hPlayHandle, DWORD dwChannel);
DVS_API BOOL   __stdcall DVS_StopLocalPlayAudio(HANDLE hPlayHandle, DWORD dwChannel);
DVS_API BOOL   __stdcall DVS_SeekLocalPlay(HANDLE hPlayHandle, DWORD dwType,DWORD64 dwArg);

DVS_API BOOL   __stdcall DVS_PlayIsEnd(HANDLE hPlayHandle);//判断文件是否播放结束

//图像控制函数
DVS_API BOOL   __stdcall DVS_CapturePicture(HANDLE hPlayHandle, DWORD dwChannel, char *pchPicFileName);
DVS_API BOOL   __stdcall DVS_SetImageInfo(HANDLE hPlayHandle, DWORD dwChannel, LPDVS_ImageInfo lpImageInfo);


DVS_API BOOL   __stdcall DVS_IsOnline(HANDLE hDvs);//DVS在线状态
DVS_API BOOL   __stdcall DVS_GetUserNetRight(HANDLE hDvs, USER_NETRIGHT *pNetAccess);//获取用户权限
DVS_API DWORD  __stdcall DVS_GetDvrVersion(void);//获取DVR版本
DVS_API DWORD  __stdcall DVS_SetChName(HANDLE hRealHandle, char *cChName);//设置通道名称
DVS_API DWORD  __stdcall DVS_SetFluenceFirst(HANDLE hDvs);//设置流畅度优先
DVS_API DWORD  __stdcall DVS_GetLinkNum(HANDLE hDvs, NET_LINK_INFO *pNetLinkInfo);//获取网络资源连接数
DVS_API BOOL   __stdcall DVS_ChnnlNameChanged(HANDLE hDvs);//通道名称是否改变
DVS_API DWORD  __stdcall DVS_RequestEmailTest(HANDLE hDvs);//请求DVR发送测试邮件
DVS_API DWORD  __stdcall DVS_SetAlarmIn(HANDLE hDvs, DWORD dwChannel, BOOL bSet);  //2012.03.15万盛平交接添加  // 报警输入
DVS_API DWORD  __stdcall DVS_SetAlarmOut(HANDLE hDvs, DWORD dwChannel, BOOL bSet); //2012.03.15万盛平交接添加  // 报警输出

DVS_API BOOL   __stdcall DVS_DVRControl(HANDLE hDvs, DWORD dwPTZCommand, DWORD dwParam = NULL);      //2012.04.06