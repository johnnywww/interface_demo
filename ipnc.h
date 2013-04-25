/*
*
*/

#ifndef	_IPNC_NN_H
#define _IPNC_NN_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "dvr_enc_api.h"
//#include "dvr_common_api.h"


#define  FILE_ROOT		"/mnt/nfs/"		//"/mnt/mtd/"
//#define  FILE_ROOT		"/mnt/mtd/"

#define VERSION_FILE		FILE_ROOT"Version"
/*add by Aaron.qiu 2012.02.20*/
/*ϵͳļʽΪAv_cfg_t*/
#define ENC_0_FILE		FILE_ROOT"config/enc_0.dat"
#define ENC_1_FILE		FILE_ROOT"config/enc_1.dat"
#define ENC_2_FILE		FILE_ROOT"config/enc_2.dat"
#define ENC_3_FILE		FILE_ROOT"config/enc_3.dat"

#define ENC_FILE(x)		ENC_##x##_FILE
/*------------------------------------------*/

/*Ƶint*/
#define ENC_FW_FILE		FILE_ROOT"config/FW.dat"
/*--------------------------------------------*/

/*ͼļImg_cfg_t*/
#define IMAGE_ATTR_FILE		FILE_ROOT"config/imagecfg.dat"
/*--------------------------------------------------------*/

/*osdļOsd_cfg_t*/
#define TIMER_REGION		0
#define REGION_NUM			3
#define OVERLAY_CFG_FILE	FILE_ROOT"config/overlay.dat"
/*--------------------------------------------------------*/

/*ļInfrared_cfg_t*/
#define INFRARED_CFG_FILE	FILE_ROOT"config/infrared.dat"
/*-------------------------------------------------------*/

/*Net_cfg_t*/
#define NET_CFG_FILE		FILE_ROOT"config/net.dat"
/*-------------------------------------------------------*/

/*˿ļPort_cfg_t*/
#define PORT_CFG_FILE		FILE_ROOT"config/port.dat"
/*-------------------------------------------------------*/

/*UPNPUpnp_cfg_t*/
#define UPNP_CFG_FILE		FILE_ROOT"config/upnp.dat"
/*--------------------------------------------------------*/

/*Wf_cfg_t*/
#define WF_CFG_FILE			FILE_ROOT"config/wireless.dat"
/*--------------------------------------------------------*/

/*DDNSļDDNS_cfg_t*/
#define DDNS_CFG_FILE		FILE_ROOT"config/DDNS.dat"
/*--------------------------------------------------------*/

/*̨òļPtz_cfg_t*/
#define PTZCOM_CFG_FILE		FILE_ROOT"config/ptzcom.dat"
/*--------------------------------------------------------*/

/*ƶļMd_cfg_t*/
#define MD_CFG_FILE			FILE_ROOT"config/md.dat"
/*--------------------------------------------------------*/

/*ûϢļUser_file_t*/
#define USER_MAX			10
#define USER_FILE			FILE_ROOT"config/user.dat"
/*-------------------------------------------------------*/

/*ʱץļSnaptimer_cfg_t*/
#define SNAPTIMER_CFG_FILE	FILE_ROOT"config/snaptimer.dat"
/*--------------------------------------------------------*/

/*FTPļFt_cfg_t*/
#define FTP_CFG_FILE		FILE_ROOT"config/ftp.dat"
/*-------------------------------------------------------*/

/*SMTPļsmtp_cfg_data*/
#define SMTP_CFG_FILE		FILE_ROOT"config/smtp.dat"
/*-------------------------------------------------------*/

/*videoMaskļVidMask_cfg_t*/
#define MASK_AERA_NUM	3
#define VIDMASK_CFG_FILE	FILE_ROOT"config/vidmask.dat"
/*------------------------------------------------------*/


/*豸ϢļSys_cfg_t*/
#define SYS_CFG_FILE	FILE_ROOT"config/sys_cfg.dat"
/*------------------------------------------*/

/*ʱļTime_cfg_t*/
#define  SYS_TIMER_FILE  FILE_ROOT"config/timer_cfg.dat"
/*-------------------------------------------*/


#define IPNC_DEBUG

#ifdef IPNC_DEBUG
#define DBG_ERR(x...)		perror(x)
#define DBG(x...)			printf(x)
#else
#define DBG_ERR(x...)
#define DBG(x...)
#endif


#define MAX_WIFI_SEARCH_NUM		10

#define FW_50HZ		50
#define FW_60HZ		60

#define MAIN_STREAM_CHN		0
#define SUB_STREAM_CHN		1

#define MAX_UPDATE_SUB_CHN		2		//4
typedef struct st_update_bs {
        int stream_enable;  ///< 0:disable, 1:enable
        int enc_type;	    ///< 0:ENC_TYPE_H264, 1:ENC_TYPE_MPEG, 2:ENC_TYPE_MJPEG
        int frame_rate;     ///< frame rate per second
        int bit_rate;       ///< Bitrate per second
        int ip_interval;    ///< The I-P interval frames
        int width;          ///< width
        int height;         ///< hieght
        int rate_ctl_type;	// 0:cbr, 1:vbr, 2:ecbr, 3:evbr
        int target_rate_max;
        int reaction_delay_max;
        int init_quant;     ///< The initial quant value
        int max_quant;      ///< The max quant value
        int min_quant;      ///< The min quant value
        int mjpeg_quality;
        int enabled_roi;    //1: enabled, 0: disabled, not ready
        int roi_x;          ///< roi x position
        int roi_y;          ///< roi y position
        int roi_w;          ///< roi width
        int roi_h;          ///< roi height
} update_avbs_t;

void init_update_avbs_t(update_avbs_t* tmp)
{
    tmp->bit_rate = 2;
    tmp->enabled_roi = 1;
    tmp->enc_type = 1;
    tmp->frame_rate = 10;
    tmp->height = 100;
    tmp->init_quant = 20;
    tmp->ip_interval = 10;
    tmp->max_quant = tmp->mjpeg_quality = 20;
    tmp->min_quant = 10;
    tmp->rate_ctl_type = 1;
    tmp->reaction_delay_max = 20;
    tmp->roi_h = tmp->roi_w = 100;
    tmp->roi_x = tmp->roi_y = 0;
    tmp->stream_enable = 1;
    tmp->target_rate_max = 10;
    tmp->width = 100;
}

typedef struct _tagAv_cfg{
        /* per channel data */
        int						denoise;  /* 3D-denoise */
        int						de_interlace;  /* 3d-deInterlace  */
        int						input_system;

//	int						iFW;
        int						chn;	//MAIN_STREAM_CHN:	SUB_STREAM_CHN
        update_avbs_t			ubs[MAX_UPDATE_SUB_CHN];
}Av_cfg_t;
void init_Av_cfg_t(Av_cfg_t* tmp)
{
    tmp->denoise = 1;
    tmp->chn = 1;
    tmp->de_interlace = 10;
    tmp->input_system = 2;
    init_update_avbs_t(&tmp->ubs[0]);
    init_update_avbs_t(&tmp->ubs[1]);
}

typedef struct _tagImg_cfg{
        int		brightness;	//
        int		saturation; //Ͷ
        int		contrast;	//Աȶ
        int		hue;		//ɫ
        int		scene;		//ƽģʽ 0Զ1 2
        int		flip;		//ͼת 1: 0ر
        int		mirror;		//ͼ񿪹 1 0ر

        int		imgctow[2];	//תֵimgctow[0]ת   imgctow[1]ת   imgctow[0]<imgctow[1]
        int		wb[3];//r:g:b ƽɫ
}Img_cfg_t;

void init_Img_cfg_t(Img_cfg_t* tmp)
{
    tmp->brightness = 10;
    tmp->contrast = 10;
    tmp->flip = 10;
    tmp->hue = 20;
    tmp->imgctow[0] = tmp->imgctow[1] = 30;
    tmp->mirror = 3;
    tmp->saturation = 10;
    tmp->scene = 2;
    tmp->wb[0] = tmp->wb[1] = tmp->wb[2] = 100;
}

typedef	struct _tagOsd_cfg{
        short		region;
        short		enable;
        short		x;
        short		y;
        short		w;
        short		h;
        char		name[16];
}Osd_cfg_t;
void init_Osd_cfg_t(Osd_cfg_t* tmp)
{
    tmp->enable = 1;
    tmp->h = 300;
    memset(tmp->name,0x00,16);
    memcpy(tmp->name,"hello",5);
    tmp->region = 10;
    tmp->w = 100;
    tmp->x = tmp->y = 10;
}

typedef struct _tagInfrared_cfg{
        int		stat;	//0:Զ 1:ǿƿ 2:ǿƹ
}Infrared_cfg_t;

void init_Infrared_cfg_t(Infrared_cfg_t* tmp)
{
    tmp->stat = 1;
}

typedef struct _tagNet_cfg{
        int			dhcpflag;
        char		ip[16];
        char		netmask[16];
        char		gateway[16];
        int			dnsstat;//0:ֶ 1:Զ
        char		fdnsip[16];
        char		sdnsip[16];
        char		macaddr[6];
        short		nettype;	//0: LAN| 1:Wifi
}Net_cfg_t;
void init_Net_cfg_t(Net_cfg_t* tmp)
{
    tmp->dhcpflag = 1;
    tmp->dnsstat = 1;
    tmp->nettype = 1;
    memcpy(tmp->fdnsip,"5.5.5.5",strlen("5.5.5.5"));
    memcpy(tmp->netmask,"5.5.5.5",strlen("5.5.5.5"));
    memcpy(tmp->gateway,"5.5.5.5",strlen("5.5.5.5"));
    memcpy(tmp->sdnsip,"5.5.5.5",strlen("5.5.5.5"));
    memcpy(tmp->macaddr,"5.5.5.5",strlen("5.5.5.5"));
    memcpy(tmp->ip,"5.5.5.5",strlen("5.5.5.5"));
}

typedef struct _tagPort_cfg{
        int			httpport;
        int			rtspport;
}Port_cfg_t;
void init_Port_cfg_t(Port_cfg_t* tmp)
{
   tmp->httpport = 80;
   tmp->rtspport = 20;
}

typedef struct _tagUpnp_cfg{
        int			upm_enable;
}Upnp_cfg_t;


typedef struct _tagDDNS_cfg{
        short		d3th_enable;	//ǷDDNS
        short		d3th_service;	//ѡ
        char		d3th_uname[16];		//û
        char		d3th_passwd[32];	//
        char		d3th_domain[64];	//
}DDNS_cfg_t;

typedef struct _tagWf_searchParam{
        int			wchannel;//ͨ
        int			wrssi;	//źǿ
        char		wessid[32]; //SSID
        int			wenc;		//
        int			wauth;		//֤ʽ
        int			wnet;		//ģʽ
}Wf_searchParam_t;
void init_Wf_searchParam_t(Wf_searchParam_t* tmp)
{
    tmp->wauth = 2;
    tmp->wchannel = 10;
    tmp->wenc = 10;
    tmp->wnet =1;
    tmp->wauth = 4;
    memcpy(tmp->wessid,"hello",5);
}

typedef struct _tagWf_search{
        int					waccess_points;	//
        Wf_searchParam_t	search_Param[MAX_WIFI_SEARCH_NUM];	//Ĳ
}Wf_search;
void init_Wf_search(Wf_search* tmp)
{
    tmp->waccess_points = 3;
    int i=0;
    for(i=0;i<MAX_WIFI_SEARCH_NUM;i++)
        init_Wf_searchParam_t(&tmp->search_Param[i]);
}

typedef struct _tagWf_cfg{
        int			wf_enable;
        char		wf_ssid[32];
        int			wf_auth;
        char		wf_key[32];	//Կ
        int			wf_enc;//
        int			wf_mode; //ӷʽ
}Wf_cfg_t;

typedef struct _tagPtz_cfg{
        int			protocal;	//Э
        int			address;	//ַ
        int			baud;		//
        int			databit;	//λ
        int			stopbit;	//ֹͣλ
        int			check;		//У
}Ptz_cfg_t;

typedef	struct _tagPtz_ctrl{
        int			step;	//ʽ
        int			act;	//  ptz_command
        int			speed;	//̨ٶ
}Ptz_ctrl_t;

typedef struct _tagMd_aera{
        int			enable;
        int			s;	//
        int			area;	//
        int			x;
        int			y;
        int			w;
        int			h;
        int			method;
}Md_aera_t;

typedef struct _tagSchedule_time{
        int			t_start;
        int			t_end;
}_Sche_time_t;

typedef struct _tagMD_schedule{
        int			type;	//1:event¼
        int			ename;	//1mdƶⱨ
        int			etm;	//0:ģʽ1:Ϣģʽ 2:ʱģʽ
        _Sche_time_t	stWorkday;//ղʱ
        _Sche_time_t	stWeekend;//Ϣղʱ
        _Sche_time_t	astWeek[7];//һղʱ
}_MD_schedule_t;

typedef struct _tagMd_cfg{
        Md_aera_t		area_param[4];

        int			io_alarm_enable;//ñ 0:ر 1:
        int			io_alarm_flag;//ñģʽ 0:ر 1:

        int			email_switch;//Ƿʼ
        int			snap_switch;//ץͼ
        int			record_switch;//Ƶ
        int			ftp_switch;//ftp

        int			relay_switch;//Ƿü̵
        int			relay_time;

        _MD_schedule_t	schedule;
}Md_cfg_t;

typedef	struct _tagSnaptimer_cfg{
        int			as_enable;
        int			as_interval;
        int			as_type;
}Snaptimer_cfg_t;

enum{
        em_Usergroup_admin = 0,
        em_Usergroup_user,
        em_Usergroup_guest,
        em_Usergroup_end,
        em_Usergroup_error
};

typedef struct _tagUsr_cfg{
        char		username[16];
        char		password[16];
        int			group;//0:admingroup 1:usergroup 2:guestgroup
}Usr_cfg_t;

typedef struct _tarUser_file{
        int			user_num;
        Usr_cfg_t	stUser[USER_MAX];
}User_file_t;

typedef struct _tagFt_cfg{
        char		serverip[16];
        int			port;
        char		username[16];
        char		password[16];
        int			mode;//ģʽ 0ر 1
        char		dirname[16];//·
}Ft_cfg_t;

typedef struct _tagSmtp_cfg{
        char		serverip[32];
        int			port;
        int			ssl_flag;//ǷSSL
        int			logintype;//Ƿ֤
        char		username[16];
        char		password[16];
        char		from[48];
        char		to[48];
        char		subject[32];
        char		text[32];
}Smtp_cfg_t;

typedef struct _tagVidMask_aera{
        int			enable;
        int			x;
        int			y;
        int			w;
        int			h;
        int			color;//1ɫ2ɫ3ɫ
}_VidMask_aera_t;

typedef struct _tagVidMask{
        int			aeraNum;
        _VidMask_aera_t	aera[MASK_AERA_NUM];
}VidMask_cfg_t;

typedef struct _tagTime_cfg{
        int			timeZone;		//ʱ
        char		dstmode;		//ǷʱԶʱ
        int			ntpenable;
        char		ntpserver[32];	//NTP
        int			ntpinterval;	//ͬʱ
        char		sys_time[32];	//ϵͳʱ
}Time_cfg_t;


#define DEVTYPE_ALL_NUM		2
typedef struct _tagSys_cfg{
        char		devtype;	//豸
        char		model[16];//豸к
        char		hardVersion[16];//Ӳ汾
        char		softVersion[16];//汾
        char		name[16];	//豸
        char		startdate[32];	//ϵͳʼʱ
        int			runtimes;	//ֶ
        int			sdstatus;	//SD״̬
        int			sdfreespace;	//SDʣÿռ䣬λKB
        int			sdtotalspace;	//SDλKB
}Sys_cfg_t;


//=================================================================
typedef enum _emSrc{
        Src_start = 0,
        http_server,
        mine_server,
        rtspd,
        Src_end
}Src_e;

typedef enum _emData_type{
        Data_type_start = 0,
        av_cfg_data,
        img_cfg_data,
        osd_cfg_data,
        infrared_cfg_data,
        net_cfg_data,
        port_cfg_data,
        upnp_cfg_data,
        DDNS_cfg_data,
        wf_cfg_data,
        ptz_cfg_data,
        ptz_ctrl_data,
        md_cfg_data,
        snaptimer_cfg_data,
        user_cfg_data,
        ft_cfg_data,
        smtp_cfg_data,
        vidmask_cfg_data,
        sys_cfg_data,
        timer_cfg_data,
        log_cfg_data,
        Data_type_end
}Data_type_e;

typedef enum emCommand{
        cmd_start = 0,
        cmd_av,
        cmd_enc,
        cmd_imgattr,
        cmd_overlay,
        cmd_mbsnapattr,
        cmd_aencattr,
        cmd_audioV,
        cmd_infrared,
        cmd_netattr,
        cmd_httpport,
        cmd_rtspport,
        cmd_upnpattr,
        cmd_wfattr,
        cmd_scwf,
        cmd_ckwf,
        cmd_ddnsattr,
        cmd_ptzattr,
        cmd_mdattr,
        cmd_ioattr,
        cmd_mdalarm,
        cmd_relayattr,
        cmd_schedule,
        cmd_userattr,
        cmd_snaptimer,
        cmd_ftpattr,
        cmd_smtpattr,
        cmd_vidmask,
        cmd_servertime,
        cmd_ntpattr,
        cmd_end
}Command_e;

typedef struct _tagCmd_compare{
        char		*cmd_string;
        Command_e	eCmd;
}Cmd_compare;

typedef struct _tagPack_head{
        Src_e			emSrc;			//Դ
        Data_type_e 	emData_type;	//
        int				data_len;
        Command_e		eCmd;			//
}Pack_head;

typedef struct _tagPack_Msg{
        Pack_head	head;
        union unPack_data{
                Av_cfg_t		av_data;
                Img_cfg_t		img_data;
                Osd_cfg_t		osd_data;
                Infrared_cfg_t	infrared_data;
                Net_cfg_t		net_data;
                Port_cfg_t		port_data;
                Upnp_cfg_t		upnp_data;
                DDNS_cfg_t		ddns_data;
                Wf_cfg_t		wf_data;
                Ptz_cfg_t		ptz_data;
                Ptz_ctrl_t		ptz_ctrl;
                Md_cfg_t		md_data;
                Snaptimer_cfg_t	snaptimer_data;
                Usr_cfg_t		user_data;
                Ft_cfg_t		ft_data;
                Smtp_cfg_t		smtp_data;
                VidMask_cfg_t	vidmask_data;
                Sys_cfg_t		sys_data;
                Time_cfg_t		time_data;
        }Pack_data;
}Pack_Msg;


typedef struct _tagTime_Zone{
        char		Zone[24];
        int			GMT;	//λ
}time_zone_t;

extern time_zone_t Time_Zone[];
extern char *ptz_command[];
extern char *devtype_strings[];
extern char *SDstatus[];
extern Cmd_compare cmd_compare_value[];


#define READ_CFG_FILE_OK		0
#define WRITE_CFG_FILE_OK		0
#define CFG_FILE_NOT_EXIST		-1
#define CFG_FILE_OPEN_ERROR		-2
#define CFG_FILE_READ_ERROR		-3
#define CFG_FILE_WRITE_ERROR	-4
#define PARAM_ERROR				-10



#endif








