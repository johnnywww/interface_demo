#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <error.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/sockios.h>
#include "cmd_type.h"
#include "interface.h"
#include "ipnc.h"

#if 1
#define ETH_NAME "eth0"
#define HARDWARE_ID "caoyonghuaipc1"
#define MANUFACTURE_ID "Bravilliant"
#define MODEL_ID "ipc1"
//int g_iFw;
Av_cfg_t g_stAv_0_file;
Av_cfg_t g_stAv_1_file;
//Img_cfg_t g_stImg_file;
//Osd_cfg_t g_arrstOsd_file[REGION_NUM];
//Infrared_cfg_t g_stInfrad_file;
//Net_cfg_t g_stNet_file;
//Port_cfg_t g_stPort_file;
//Upnp_cfg_t g_stUpnp_file;
//DDNS_cfg_t g_stDDNS_file;
Wf_search g_stWf_search_file;
//Wf_cfg_t g_stwfcfg_file;
//Ptz_cfg_t g_stPtzcfg_file;
Ptz_ctrl_t g_stPtzctl_file;
//Md_cfg_t g_stMdcfg_file;
//Snaptimer_cfg_t g_stSnaptimercfg_file;
//User_file_t g_stUsr_file;
//Ft_cfg_t g_stFtcfg_file;
//Smtp_cfg_t g_stSmtpcfg_file;
//VidMask_cfg_t g_stVidMaskcfg_file;
//Time_cfg_t g_stTimecfg_file;
//Sys_cfg_t g_stSyscfg_file;

User_file_t g_stUsr_file = { 3, { { "admin", "admin", em_Usergroup_admin }, {
		"user", "user", em_Usergroup_user }, { "guest", "guest",
		em_Usergroup_guest } } };

int g_iFw = 50;

Img_cfg_t g_stImg_file = { 50, 50, 50, 50, 0, 50, 0, { 10, 30 },
		{ 128, 128, 128 } };

Osd_cfg_t g_arrstOsd_file[REGION_NUM] = { { TIMER_REGION, 0, 10, 10, 100, 1,
		"time region" }, { 1, 0, 1000, 10, 100, 1, "win1" }, { 2, 0, 1000, 30,
		100, 1, "win2" } };

Infrared_cfg_t g_stInfrad_file = { 0 };

Net_cfg_t g_stNet_file = { 0, "192.168.1.21", "255.255.255.0", "192.168.1.1", 0,
		"202.96.134.133", "202.96.134.133",
		{ 0x00, 0x50, 0x80, 0x11, 0x22, 0x33 }, 0 };

Port_cfg_t g_stPort_file = { 8001, 554 };

Upnp_cfg_t g_stUpnp_file = { 0 };

Wf_cfg_t g_stwfcfg_file = { 0, "linksys", 2, "1234567890", 0, 0 };

DDNS_cfg_t g_stDDNS_file = { 0, 1, "simple", "12345", "simple.3322.org" };

Ptz_cfg_t g_stPtzcfg_file = { 0, 0x01, 9600, 8, 1, 0 };

Md_cfg_t g_stMdcfg_file = { { { 0, 1, 0, 10, 10, 10, 10, 0 }, { 0, 1, 1, 20, 20,
		20, 20, 0 }, { 0, 1, 2, 30, 30, 30, 30, 0 }, { 0, 1, 3, 40, 40, 40, 40,
		0 } },

0, 0,

0, 0, 0, 0,

0, 10,

{ 0, 0, 0, { 0, 0 }, { 0, 0 }, { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
		{ 0, 0 }, { 0, 0 }, { 0, 0 } } } };

Snaptimer_cfg_t g_stSnaptimercfg_file = { 0, 60, 1, };

Ft_cfg_t g_stFtcfg_file =
		{ "192.168.1.2", 21, "aaronqiu", "123456", 1, "BR_pic" };

Smtp_cfg_t g_stSmtpcfg_file = { "smtp.brgq.com.cn", 25, 0, 1, "aaronqiu",
		"123456", "aaron@brgq.com.cn", "simple@brgq.com.cn", "pic", "snap pic" };

VidMask_cfg_t g_stVidMaskcfg_file = { 0, { { 0, 10, 10, 100, 100, 1 }, { 0, 100,
		100, 100, 100, 1 }, { 0, 200, 200, 100, 100, 1 } } };

Sys_cfg_t g_stSyscfg_file = { 0, "0", "1.0.0.0", "2.0.0.0", "ipcam",
		"2012-4-25 00:00:00", 0, 0, 0, 0 };

Time_cfg_t g_stTimecfg_file = { 480, //HK
		0, 0, "192.168.1.2", 60, "2011-03-14 04:05:06" };

void getDateTimeStr(char* info, const int len, const time_t dtValue) {
	struct tm* today = localtime(&dtValue);
	strftime(info, len, "%Y-%m-%d %H:%M:%S ", today);
}

void getCurrentDateTimeStr(char* info, const int len) {
	getDateTimeStr(info, len, time(NULL));
}


void logIntoFile(FILE* file, char* level, const char* fmt, va_list argptr) {
	char value[500] = { 0 };
	char dt[30];
	getCurrentDateTimeStr(dt, 30);
	vsnprintf(value, 500, fmt, argptr);
	fprintf(file, "%s %s: %s\n", dt, level, value);
}

void logInfo(const char* fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	logIntoFile(stdout, "NORMAL", fmt, argptr);
	va_end(argptr);
}

int getPCLocalIp(char* pIp) {
	int socket_fd;
	struct sockaddr_in *sin;
	struct ifreq ifr;
	struct ifconf conf;
	int num;
	int i;
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_fd == -1) {
		return -1;
	}
	strcpy(ifr.ifr_name, ETH_NAME);
	if (ioctl(socket_fd, SIOCGIFADDR, &ifr) < 0) {
		return -1;
	}
	else
	{
		sin = (struct sockaddr_in *)&(ifr.ifr_addr);
		strcpy(pIp, inet_ntoa(sin->sin_addr));
	}
	return 0;
}

void init_update_avbs_t(update_avbs_t* tmp)
{
    tmp->bit_rate = 2;
    tmp->enabled_roi = 1;
    tmp->enc_type = 0;
    tmp->frame_rate = 30;
    tmp->height = 720;
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
    tmp->width = 1280;
}

void init_Av_cfg_t(Av_cfg_t* tmp)
{
    tmp->denoise = 1;
    tmp->chn = 1;
    tmp->de_interlace = 10;
    tmp->input_system = 2;
    init_update_avbs_t(&tmp->ubs[0]);
    init_update_avbs_t(&tmp->ubs[1]);
}

void init() {
	init_Av_cfg_t(&g_stAv_0_file);
	init_Av_cfg_t(&g_stAv_1_file);
	init_Wf_search(&g_stWf_search_file);
	getPCLocalIp(g_stNet_file.ip);
}

char *ParseVars(char PostIn[], int *pParseIndex) {
	int out;
	int in;
	char hexch;
	char hexval[3];
	int start;
	char ch;

	in = *pParseIndex;

	hexval[2] = '\0';
	if ((in == 0) && (PostIn[0] == '$'))
		out = in = 1;
	else if (in == 0)
		out = 0;
	else if (in == -1)
		return NULL;
	else
		out = ++in;

	start = in;
	while (((ch = PostIn[in]) != '=') && (ch != '&') && (ch != '\0')
			&& (ch != '#')) {
		if (ch == '+')
			PostIn[out++] = ' ';
		else if (ch == '%') {
			hexval[0] = PostIn[++in];
			hexval[1] = PostIn[++in];
			hexch = (char) strtol(hexval, NULL, 16);
			PostIn[out++] = hexch;
		} else
			PostIn[out++] = ch;
		in++;
	}

	if ((ch == '\0') || (ch == '#'))
		in = -1;

	PostIn[out++] = '\0';

	*pParseIndex = in;

	return (&PostIn[start]);
}

int processMsg(void *buf, int len, void *rbuf) {
	int cmd_type = -1;
	char *pKey;
	int iKey;
	int iValue;
	float fValue;
	char *pValue;
	char *cmd_tmp;
	char *pInput = buf;
	int parseIndex = 0;
	int i = 0;

	char *pRet = rbuf;
	int ret = 0;
	int file_changed_flag = 0;
	void *p_tmp;
	p_tmp = (void*) &g_stAv_0_file;
	int channel = -1;
	int sub_channel = 0;
	int video_chn_num = 2;
	int ptz_preset_capacity = 128;
	int video_encode_profile = 0;
	int witch_file = 0;
	int osd_region = -1;
	int index = -1;
	int index1 = -1;
	int sharpness = 128;
	int wbMode = 0;
	int wbcrgain = 20;
	int wbcbgain = 20;
	int backlightcompMode = 0;
	int backlightcompLevel = 20;
	int wdrangeMode = 0;
	int wdrangeLevel = 20;
	int if_cfg = 0;
	int osd_cfg = 0;
	int ntpserver_cfg = 0;

	int fd_socket = -1;

	if (buf == NULL || rbuf == NULL) {
		return -1;
	}

	cmd_tmp = (char *) malloc(128 * sizeof(char));
	if (cmd_tmp == NULL) {
		return -2;
	}
	logInfo("receive cmd is %s\n", buf);
//fprintf(stdout, "enter process.\n");
	do {
		pKey = ParseVars(pInput, &parseIndex);
		pValue = ParseVars(pInput, &parseIndex);

		if (pKey == NULL || pValue == NULL) {
			break;
		}

		iKey = atoi(pKey);
		if (iKey < e_TYPE || iKey > e_END) {
			continue;
		}

		switch (iKey) {
		case e_TYPE:
			cmd_type = atoi(pValue);
			sprintf(cmd_tmp, "$%d=%d", e_TYPE, cmd_type);
			strcpy(pRet, cmd_tmp);
			logInfo("cmd type is %d", cmd_type);
			break;
		case e_Chn:
			channel = atoi(pValue);
			sprintf(cmd_tmp, "&%d=%d", e_Chn, channel);
			strcat(pRet, cmd_tmp);
			logInfo("channel is %d\n", channel);
			break;
		case e_Sub_Chn:
			sub_channel = atoi(pValue);
			sprintf(cmd_tmp, "&%d=%d", e_Sub_Chn, sub_channel);
			strcat(pRet, cmd_tmp);
			logInfo("sub channel is %d\n", sub_channel);
			break;
		case e_video_addr:
			if (cmd_type == T_Set) {
				logInfo("set e_video_addr %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=rtsp://%s:%d/day.264", e_video_addr,
						g_stNet_file.ip, 8554);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_video_addr rtsp://%s:%d\n", g_stNet_file.ip,
						g_stPort_file.rtspport + channel * 2);
			}
			break;
		case e_encode_profile:
			if (cmd_type == T_Set) {
				video_encode_profile = atoi(pValue);
				logInfo("set e_encode_profile %d\n", video_encode_profile);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_encode_profile,
						video_encode_profile);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_encode_profile %d\n", video_encode_profile);
			}
			break;
		case e_video_chn_num:
			if (cmd_type == T_Set) {
				video_chn_num = atoi(pValue);
				logInfo("set video channel counts %d\n", video_chn_num);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_video_chn_num, video_chn_num);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get video_chn_num %d\n", video_chn_num);
			}
			break;
		case e_FW:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set FW %d\n", iValue);
				/*if(g_iFw!=iValue){
				 g_iFw = iValue;
				 init_isp_pw_frequency(iValue);
				 SET_FILE_CHANGED(file_changed_flag, e_ENC_FW_FILE);
				 }*/
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_FW, g_iFw);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("set FW %d\n", g_iFw);
			}
			break;
		case e_denoise:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set denoise %d\n", iValue);
				/*if(((Av_cfg_t *)p_tmp)->denoise != iValue){
				 ((Av_cfg_t *)p_tmp)->denoise = iValue;
				 //............
				 SET_FILE_CHANGED(file_changed_flag, witch_file);
				 }*/
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_denoise,
						((Av_cfg_t *) p_tmp)->denoise);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get denoise %d\n", ((Av_cfg_t *) p_tmp)->denoise);
			}
			break;
		case e_input_system:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set input_system %d\n", iValue);

				/*if(((Av_cfg_t *)p_tmp)->input_system != iValue){
				 ((Av_cfg_t *)p_tmp)->input_system = iValue;
				 //............
				 SET_FILE_CHANGED(file_changed_flag, witch_file);
				 }*/
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_input_system,
						((Av_cfg_t *) p_tmp)->input_system);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get input_system %d\n",
						((Av_cfg_t *) p_tmp)->input_system);

			}
			break;
		case e_de_interlace:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set de_interlace %d\n", iValue);

				/*if(((Av_cfg_t *)p_tmp)->de_interlace != iValue){
				 ((Av_cfg_t *)p_tmp)->de_interlace = iValue;
				 //............
				 SET_FILE_CHANGED(file_changed_flag, witch_file);
				 }*/
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_de_interlace,
						((Av_cfg_t *) p_tmp)->de_interlace);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get de_interlace %d\n",
						((Av_cfg_t *) p_tmp)->de_interlace);
			}
			break;
		case e_Stream_enable:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set Stream_enable %d\n", iValue);

				/*if(((Av_cfg_t *)p_tmp)->ubs[sub_channel].stream_enable != iValue){
				 ((Av_cfg_t *)p_tmp)->ubs[sub_channel].stream_enable = iValue;
				 //............
				 SET_FILE_CHANGED(file_changed_flag, witch_file);
				 }*/
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_Stream_enable,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].stream_enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get Stream_enable %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].stream_enable);
			}
			break;
		case e_enc_type:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set enc_type %d\n", iValue);

				/*if(((Av_cfg_t *)p_tmp)->ubs[sub_channel].enc_type != iValue){
				 ((Av_cfg_t *)p_tmp)->ubs[sub_channel].enc_type = iValue;
				 //............
				 SET_FILE_CHANGED(file_changed_flag, witch_file);
				 }*/
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_enc_type,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].enc_type);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get enc_type %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].enc_type);
			}
			break;
		case e_frame_rate:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set frame_rate %d\n", iValue);

				/*if(((Av_cfg_t *)p_tmp)->ubs[sub_channel].frame_rate != iValue){
				 ((Av_cfg_t *)p_tmp)->ubs[sub_channel].frame_rate = iValue;
				 //............

				 set_fps(((Av_cfg_t *)p_tmp)->ubs[sub_channel].frame_rate);

				 SET_FILE_CHANGED(file_changed_flag, witch_file);
				 }*/
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_frame_rate,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].frame_rate);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get frame_rate %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].frame_rate);
			}
			break;
		case e_bit_rate:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set bit_rate %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_bit_rate,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].bit_rate );
				strcat(pRet, cmd_tmp);

//				logInfo("=======to get bit_rate:%d.\n", ((Av_cfg_t *)p_tmp)->ubs[sub_channel].bit_rate/1000);

				ret++;
				logInfo("get bit_rate %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].bit_rate );
			}
			break;
		case e_ip_interval:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ip_interval %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ip_interval,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].ip_interval);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ip_interval %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].ip_interval);
			}
			break;
		case e_width:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {

				iValue = atoi(pValue);
				logInfo("set e_width %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_width,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].width);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_width %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].width);
			}
			break;
		case e_height:
			/*if(channel==MAIN_STREAM_CHN){
			 p_tmp = (void *)&g_stAv_0_file;
			 witch_file = e_ENC_0_FILE;
			 }else{
			 p_tmp = (void *)&g_stAv_1_file;
			 witch_file = e_ENC_1_FILE;
			 }*/
			if (cmd_type == T_Set) {

				iValue = atoi(pValue);
				logInfo("set e_height %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_height,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].height);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_height %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].height);
			}
			break;
		case e_rate_ctl_type:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_rate_ctl_type %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_rate_ctl_type,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].rate_ctl_type);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_rate_ctl_type %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].rate_ctl_type);
			}
			break;
		case e_target_rate_max:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_target_rate_max %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_target_rate_max,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].target_rate_max);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_target_rate_max %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].target_rate_max);
			}
			break;
		case e_reaction_delay_max:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_reaction_delay_max %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(
						cmd_tmp,
						"&%d=%d",
						e_reaction_delay_max,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].reaction_delay_max);
				strcat(pRet, cmd_tmp);
				ret++;
				printf(
						"get e_reaction_delay_max %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].reaction_delay_max);

			}
			break;
		case e_init_quant:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_init_quant %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_init_quant,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].init_quant);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_init_quant %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].init_quant);
			}
			break;
		case e_max_quant:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_max_quant %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_max_quant,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].max_quant);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_max_quant %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].max_quant);
			}
			break;
		case e_min_quant:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_min_quant %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_min_quant,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].min_quant);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_min_quant %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].min_quant);
			}
			break;
		case e_mjpeg_quality:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_mjpeg_quality %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_mjpeg_quality,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].mjpeg_quality);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_mjpeg_quality %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].mjpeg_quality);
			}
			break;
		case e_enable_roi:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_enable_roi %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_enable_roi,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].enabled_roi);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_enable_roi %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].enabled_roi);
			}
			break;
		case e_roi_x:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_roi_x %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_roi_x,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].roi_x);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_roi_x %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].roi_x);
			}
			break;
		case e_roi_y:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_roi_y %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_roi_y,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].roi_y);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_roi_y %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].roi_y);
			}
			break;
		case e_roi_w:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_roi_w %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_roi_w,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].roi_w);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_roi_w %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].roi_w);
			}
			break;
		case e_roi_h:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_roi_h %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_roi_h,
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].roi_h);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_roi_h %d\n",
						((Av_cfg_t *) p_tmp)->ubs[sub_channel].roi_h);

			}
			break;
		case e_brightness:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_brightness %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_brightness,
						g_stImg_file.brightness);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_brightness %d\n", g_stImg_file.brightness);
			}
			break;
		case e_saturation:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_saturation %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_saturation,
						g_stImg_file.saturation);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_saturation %d\n", g_stImg_file.saturation);
			}
			break;
		case e_contrast:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_contrast %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_contrast, g_stImg_file.contrast);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_contrast %d\n", g_stImg_file.contrast);
			}
			break;
		case e_sharpness:
			if (cmd_type == T_Set) {
				sharpness = atoi(pValue);
				logInfo("set e_sharpness %d\n", sharpness);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_sharpness, sharpness);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sharpness %d\n", sharpness);
			}
			break;
		case e_hue:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_hue %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_hue, g_stImg_file.hue);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_hue %d\n", g_stImg_file.hue);
			}
			break;
		case e_scene:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_scene %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_scene, g_stImg_file.scene);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_scene %d\n", g_stImg_file.scene);
			}
			break;
		case e_flip: //޸Ϊֵ
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_flip %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_flip, g_stImg_file.flip);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_flip %d\n", g_stImg_file.flip);
			}
			break;
		case e_mirror:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_mirror %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_mirror, g_stImg_file.mirror);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_mirror %d\n", g_stImg_file.mirror);
			}
			break;
		case e_imgctow:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_imgctow %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_imgctow, g_stImg_file.imgctow[0]);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_imgctow %d\n", g_stImg_file.imgctow[0]);

			}
			break;
		case e_imgwtoc:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_imgwtoc %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_imgwtoc, g_stImg_file.imgctow[1]);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_imgwtoc %d\n", g_stImg_file.imgctow[1]);
			}
			break;
		case e_wb_r:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_wb_r %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wb_r, g_stImg_file.wb[0]);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wb_r %d\n", g_stImg_file.wb[0]);
			}
			break;
		case e_wb_g:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_wb_g %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wb_g, g_stImg_file.wb[1]);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wb_g %d\n", g_stImg_file.wb[1]);
			}
			break;
		case e_wb_b:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_wb_b %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wb_b, g_stImg_file.wb[2]);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wb_b %d\n", g_stImg_file.wb[2]);
			}
			break;
		case e_wb_mode:
			if (cmd_type == T_Set) {
				wbMode = atoi(pValue);
				logInfo("set e_wb_mode %d\n", wbMode);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wb_mode, wbMode);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wb_mode %d\n", wbMode);
			}
			break;
		case e_wb_crgain:
			if (cmd_type == T_Set) {
				wbcrgain = atoi(pValue);
				logInfo("set e_wb_crgain %d\n", wbcrgain);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wb_crgain, wbcrgain);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wb_crgain %d\n", wbcrgain);
			}
			break;
		case e_wb_cbgain:
			if (cmd_type == T_Set) {
				wbcbgain = atoi(pValue);
				logInfo("set e_wb_cbgain %d\n", wbcbgain);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wb_cbgain, wbcbgain);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wb_cbgain %d\n", wbcbgain);
			}
			break;
		case e_backlightcomp_mode:
			if (cmd_type == T_Set) {
				backlightcompMode = atoi(pValue);
				logInfo("set e_backlightcomp_mode %d\n", backlightcompMode);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_backlightcomp_mode,
						backlightcompMode);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_backlightcomp_mode %d\n", backlightcompMode);
			}
			break;
		case e_backlightcomp_level:
			if (cmd_type == T_Set) {
				backlightcompLevel = atoi(pValue);
				logInfo("set e_backlightcomp_level %d\n", backlightcompLevel);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_backlightcomp_level,
						backlightcompLevel);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_backlightcomp_level %d\n", backlightcompLevel);
			}
			break;
		case e_wdrange_mode:
			if (cmd_type == T_Set) {
				wdrangeMode = atoi(pValue);
				logInfo("set e_wdrange_mode %d\n", wdrangeMode);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wdrange_mode, wdrangeMode);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wdrange_mode %d\n", wdrangeMode);
			}
			break;
		case e_wdrange_level:
			if (cmd_type == T_Set) {
				wdrangeLevel = atoi(pValue);
				logInfo("set e_wdrange_level %d\n", wdrangeLevel);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wdrange_level, wdrangeLevel);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wdrange_level %d\n", wdrangeLevel);
			}
			break;
		case e_osd_region:
			osd_region = atoi(pValue);
			sprintf(cmd_tmp, "&%d=%d", e_osd_region, osd_region);
			strcat(pRet, cmd_tmp);
			logInfo("e_osd_region:%d\n", osd_region);
			break;
		case e_osd_region_name:

			if (cmd_type == T_Set) {
				logInfo("set e_osd_region_name %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_osd_region_name,
						g_arrstOsd_file[osd_region].name);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_osd_region_name %s\n",
						g_arrstOsd_file[osd_region].name);
			}
			break;
		case e_osd_enable:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_osd_enable %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_osd_enable,
						g_arrstOsd_file[osd_region].enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_osd_enable %d\n",
						g_arrstOsd_file[osd_region].enable);
			}
			break;
		case e_osd_x:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_osd_x %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_osd_x,
						g_arrstOsd_file[osd_region].x);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_osd_x %d\n", g_arrstOsd_file[osd_region].x);
			}
			break;
		case e_osd_y:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_osd_y %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_osd_y,
						g_arrstOsd_file[osd_region].y);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_osd_y %d\n", g_arrstOsd_file[osd_region].y);
			}
			break;
		case e_osd_w:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_osd_w %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_osd_w,
						g_arrstOsd_file[osd_region].w);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_osd_w %d\n", g_arrstOsd_file[osd_region].w);
			}
			break;
		case e_osd_h:

			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_osd_h %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_osd_h,
						g_arrstOsd_file[osd_region].h);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_osd_h %d\n", g_arrstOsd_file[osd_region].h);
			}
			break;
		case e_infrad_stat:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_infrad_stat %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_infrad_stat, g_stInfrad_file.stat);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_infrad_stat %d\n", g_stInfrad_file.stat);
			}
			break;
		case e_net_dhcpflag:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_net_dhcpflag %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_net_dhcpflag,
						g_stInfrad_file.stat);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_dhcpflag %d\n", g_stInfrad_file.stat);
			}
			break;
		case e_net_ip:
			if (cmd_type == T_Set) {
				logInfo("set e_net_ip %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_net_ip, g_stNet_file.ip);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_ip %s\n", g_stNet_file.ip);
			}
			break;
		case e_net_netmask:
			if (cmd_type == T_Set) {
				logInfo("set e_net_netmask %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_net_netmask, g_stNet_file.netmask);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_netmask %s\n", g_stNet_file.netmask);
			}
			break;
		case e_net_gateway:
			if (cmd_type == T_Set) {
				logInfo("set e_net_gateway %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_net_gateway, g_stNet_file.gateway);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_gateway %s\n", g_stNet_file.gateway);
			}
			break;
		case e_net_dnsstat:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_net_dnsstat %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_net_dnsstat, g_stNet_file.dnsstat);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_dnsstat %d\n", g_stNet_file.dnsstat);
			}
			break;
		case e_net_fdnsip:
			if (cmd_type == T_Set) {
				logInfo("set e_net_fdnsip %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_net_fdnsip, g_stNet_file.fdnsip);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_fdnsip %s\n", g_stNet_file.fdnsip);
			}
			break;
		case e_net_sdnsip:
			if (cmd_type == T_Set) {
				logInfo("set e_net_sdnsip %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_net_sdnsip, g_stNet_file.sdnsip);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_sdnsip %s\n", g_stNet_file.sdnsip);
			}
			break;
		case e_net_macaddr:
			if (cmd_type == T_Set) {
				logInfo("set e_net_macaddr %s\n", pValue);

			} else if (cmd_type == T_Get) {
				//net_get_hwaddr("eth0", g_stNet_file.macaddr);

				sprintf(cmd_tmp, "&%d=%02x-%02x-%02x-%02x-%02x-%02x",
						e_net_macaddr, g_stNet_file.macaddr[0],
						g_stNet_file.macaddr[1], g_stNet_file.macaddr[2],
						g_stNet_file.macaddr[3], g_stNet_file.macaddr[4],
						g_stNet_file.macaddr[5]);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_macaddr %s\n", cmd_tmp);
			}
			break;
		case e_net_nettype:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_net_nettype %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_net_nettype, g_stNet_file.dnsstat);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_net_nettype %d\n", g_stNet_file.dnsstat);
			}
			break;
		case e_port_httpport:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_port_httpport %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_port_httpport,
						g_stPort_file.httpport);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_port_httpport %d\n", g_stPort_file.httpport);
			}
			break;
		case e_port_rtspport:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_port_rtspport %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_port_rtspport,
						g_stPort_file.rtspport);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_port_rtspport %d\n", g_stPort_file.rtspport);
			}
			break;
		case e_upnp_upmenable:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_upnp_upmenable %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_upnp_upmenable,
						g_stUpnp_file.upm_enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_upnp_upmenable %d\n", g_stUpnp_file.upm_enable);
			}
			break;
		case e_ddns_d3thenable:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ddns_d3thenable %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ddns_d3thenable,
						g_stDDNS_file.d3th_enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ddns_d3thenable %d\n", g_stDDNS_file.d3th_enable);
			}
			break;
		case e_ddns_d3thservice:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ddns_d3thservice %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ddns_d3thservice,
						g_stDDNS_file.d3th_service);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ddns_d3thservice %d\n",
						g_stDDNS_file.d3th_service);
			}
			break;
		case e_ddns_d3thuname:
			if (cmd_type == T_Set) {
				logInfo("set e_ddns_d3thuname %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_ddns_d3thuname,
						g_stDDNS_file.d3th_uname);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ddns_d3thuname %s\n", g_stDDNS_file.d3th_uname);
			}
			break;
		case e_ddns_d3thpasswd:
			if (cmd_type == T_Set) {
				logInfo("set e_ddns_d3thpasswd %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_ddns_d3thpasswd,
						g_stDDNS_file.d3th_passwd);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ddns_d3thpasswd %s\n", g_stDDNS_file.d3th_passwd);
			}
			break;
		case e_ddns_domain:
			if (cmd_type == T_Set) {
				logInfo("set e_ddns_domain %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_ddns_domain,
						g_stDDNS_file.d3th_domain);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ddns_domain %s\n", g_stDDNS_file.d3th_domain);
			}
			break;
		case e_wf_enable:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_wf_enable %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wf_enable,
						g_stwfcfg_file.wf_enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wf_enable %d\n", g_stwfcfg_file.wf_enable);
			}
			break;
		case e_wf_ssid:
			if (cmd_type == T_Set) {
				logInfo("set e_wf_ssid %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_wf_ssid, g_stwfcfg_file.wf_ssid);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wf_ssid %s\n", g_stwfcfg_file.wf_ssid);
			}
			break;
		case e_wf_auth:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_wf_auth %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wf_auth, g_stwfcfg_file.wf_auth);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wf_auth %d\n", g_stwfcfg_file.wf_auth);
			}
			break;
		case e_wf_key:
			if (cmd_type == T_Set) {
				logInfo("set e_wf_key %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_wf_key, g_stwfcfg_file.wf_key);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wf_key %s\n", g_stwfcfg_file.wf_key);
			}
			break;
		case e_wf_enc:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_wf_enc %d\n", iValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wf_enc, g_stwfcfg_file.wf_enc);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wf_enc %d\n", g_stwfcfg_file.wf_enc);
			}
			break;
		case e_wf_mode:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_wf_mode %d\n", iValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wf_mode, g_stwfcfg_file.wf_mode);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wf_mode %d\n", g_stwfcfg_file.wf_mode);
			}
			break;
		case e_wfsearch_accesspoints:
			if (cmd_type == T_Get) {
				iValue = atoi(pValue);
				if (iValue >= g_stWf_search_file.waccess_points)
					break;
				index = iValue;
				sprintf(cmd_tmp, "&%d=%d", e_wfsearch_accesspoints, index);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wfsearch_accesspoints %d\n", index);
			}
			break;
		case e_wfsearch_channel:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wfsearch_channel,
						g_stWf_search_file.search_Param[index].wchannel);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wfsearch_channel %d\n",
						g_stWf_search_file.search_Param[index].wchannel);
			}
			break;
		case e_wfsearch_rssi:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wfsearch_rssi,
						g_stWf_search_file.search_Param[index].wrssi);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wfsearch_rssi %d\n",
						g_stWf_search_file.search_Param[index].wrssi);
			}
			break;
		case e_wfsearch_essid:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_wfsearch_essid,
						g_stWf_search_file.search_Param[index].wessid);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wfsearch_essid %d\n",
						g_stWf_search_file.search_Param[index].wessid);
			}
			break;
		case e_wfsearch_enc:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wfsearch_enc,
						g_stWf_search_file.search_Param[index].wenc);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wfsearch_enc %d\n",
						g_stWf_search_file.search_Param[index].wenc);
			}
			break;
		case e_wfsearch_auth:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wfsearch_auth,
						g_stWf_search_file.search_Param[index].wauth);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wfsearch_auth %d\n",
						g_stWf_search_file.search_Param[index].wauth);
			}
			break;
		case e_wfsearch_net:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_wfsearch_net,
						g_stWf_search_file.search_Param[index].wnet);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_wfsearch_net %d\n",
						g_stWf_search_file.search_Param[index].wnet);
			}
			break;
		case e_ptz_protocal:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ptz_protocal %d\n", iValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ptz_protocal,
						g_stPtzcfg_file.protocal);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ptz_protocal %d\n", g_stPtzcfg_file.protocal);
			}
			break;
		case e_ptz_address:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ptz_address %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ptz_address,
						g_stPtzcfg_file.address);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ptz_address %d\n", g_stPtzcfg_file.address);
			}
			break;
		case e_ptz_baud:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ptz_baud %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ptz_baud, g_stPtzcfg_file.baud);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ptz_baud %d\n", g_stPtzcfg_file.baud);
			}
			break;
		case e_ptz_databit:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ptz_databit %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ptz_databit,
						g_stPtzcfg_file.databit);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ptz_databit %d\n", g_stPtzcfg_file.databit);
			}
			break;
		case e_ptz_stopbit:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ptz_stopbit %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ptz_stopbit,
						g_stPtzcfg_file.stopbit);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ptz_stopbit %d\n", g_stPtzcfg_file.stopbit);
			}
			break;
		case e_ptz_check:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ptz_check %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ptz_check, g_stPtzcfg_file.check);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ptz_check %d\n", g_stPtzcfg_file.check);
			}
			break;
		case e_md_io_alarm_enable:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_io_alarm_enable %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_io_alarm_enable,
						g_stMdcfg_file.io_alarm_enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_io_alarm_enable %d\n",
						g_stMdcfg_file.io_alarm_enable);
			}
			break;
		case e_md_io_alarm_flag:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_io_alarm_flag %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_io_alarm_flag,
						g_stMdcfg_file.io_alarm_flag);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_io_alarm_flag %d\n",
						g_stMdcfg_file.io_alarm_flag);
			}
			break;
		case e_md_email_switch:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_email_switch %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_email_switch,
						g_stMdcfg_file.email_switch);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_email_switch %d\n",
						g_stMdcfg_file.email_switch);
			}
			break;
		case e_md_snap_switch:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_snap_switch %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_snap_switch,
						g_stMdcfg_file.snap_switch);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_snap_switch %d\n", g_stMdcfg_file.snap_switch);
			}
			break;
		case e_md_record_switch:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_record_switch %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_record_switch,
						g_stMdcfg_file.record_switch);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_record_switch %d\n",
						g_stMdcfg_file.record_switch);
			}
			break;
		case e_md_ftp_switch:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_ftp_switch %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_ftp_switch,
						g_stMdcfg_file.ftp_switch);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_ftp_switch %d\n", g_stMdcfg_file.ftp_switch);
			}
			break;
		case e_md_relay_switch:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_relay_switch %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_relay_switch,
						g_stMdcfg_file.relay_switch);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_relay_switch %d\n",
						g_stMdcfg_file.relay_switch);
			}
			break;
		case e_md_relay_time:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_relay_time %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_relay_time,
						g_stMdcfg_file.relay_time);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_relay_time %d\n", g_stMdcfg_file.relay_time);
			}
			break;
		case e_md_schedule_type:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_type %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_type,
						g_stMdcfg_file.schedule.type);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_type %d\n",
						g_stMdcfg_file.schedule.type);
			}
			break;
		case e_md_schedule_ename:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_ename %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_ename,
						g_stMdcfg_file.schedule.ename);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_ename %d\n",
						g_stMdcfg_file.schedule.ename);
			}
			break;
		case e_md_schedule_etm:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_etm %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_etm,
						g_stMdcfg_file.schedule.etm);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_etm %d\n",
						g_stMdcfg_file.schedule.etm);
			}
			break;
		case e_md_schedule_workday_Tend:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_workday_Tend %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_workday_Tend,
						g_stMdcfg_file.schedule.stWorkday.t_end);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_workday_Tend %d\n",
						g_stMdcfg_file.schedule.stWorkday.t_end);
			}
			break;
		case e_md_schedule_workday_Tstart:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_workday_Tstart %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_workday_Tstart,
						g_stMdcfg_file.schedule.stWorkday.t_start);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_workday_Tstart %d\n",
						g_stMdcfg_file.schedule.stWorkday.t_start);
			}
			break;
		case e_md_schedule_workend_Tstart:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_workend_Tstart %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_workend_Tstart,
						g_stMdcfg_file.schedule.stWeekend.t_start);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_workend_Tstart %d\n",
						g_stMdcfg_file.schedule.stWeekend.t_start);
			}
			break;
		case e_md_schedule_workend_Tend:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_workend_Tend %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_workend_Tend,
						g_stMdcfg_file.schedule.stWeekend.t_end);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_workend_Tend %d\n",
						g_stMdcfg_file.schedule.stWeekend.t_end);
			}
			break;
		case e_md_schedule_week_Tstart:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_week_Tstart %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_week_Tstart,
						g_stMdcfg_file.schedule.astWeek[0].t_start);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_week_Tstart %d\n",
						g_stMdcfg_file.schedule.astWeek[0].t_start);
			}
			break;
		case e_md_schedule_week_Tend:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_schedule_week_Tend %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_schedule_week_Tend,
						g_stMdcfg_file.schedule.astWeek[0].t_end);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_schedule_week_Tend %d\n",
						g_stMdcfg_file.schedule.astWeek[0].t_end);
			}
			break;
		case e_md_area:
			iValue = atoi(pValue);
			index = iValue;
			if (index >= 4)
				break;
			sprintf(cmd_tmp, "&%d=%d", e_md_area, index);
			strcat(pRet, cmd_tmp);
			ret++;
			logInfo("e_md_area:%d\n", index);
			break;
		case e_md_area_eable:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_area_eable %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_area_eable,
						g_stMdcfg_file.area_param[index].enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_area_eable %d\n",
						g_stMdcfg_file.area_param[index].enable);
			}
			break;
		case e_md_area_s:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_area_s %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_area_eable,
						g_stMdcfg_file.area_param[index].s);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_area_s %d\n",
						g_stMdcfg_file.area_param[index].s);
			}
			break;
		case e_md_area_method:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_area_method %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_area_method,
						g_stMdcfg_file.area_param[index].method);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_area_method %d\n",
						g_stMdcfg_file.area_param[index].method);
			}
			break;
		case e_md_area_x:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_area_x %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_area_x,
						g_stMdcfg_file.area_param[index].x);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_area_x %d\n",
						g_stMdcfg_file.area_param[index].x);
			}
			break;
		case e_md_area_y:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_area_y %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_area_y,
						g_stMdcfg_file.area_param[index].y);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_area_y %d\n",
						g_stMdcfg_file.area_param[index].y);
			}
			break;
		case e_md_area_w:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_area_w %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_area_y,
						g_stMdcfg_file.area_param[index].w);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_area_w %d\n",
						g_stMdcfg_file.area_param[index].w);
			}
			break;
		case e_md_area_h:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_md_area_h %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_md_area_y,
						g_stMdcfg_file.area_param[index].h);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_md_area_h %d\n",
						g_stMdcfg_file.area_param[index].h);
			}
			break;
		case e_snapT_enable:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_snapT_enable %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_snapT_enable,
						g_stSnaptimercfg_file.as_enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_snapT_enable %d\n",
						g_stSnaptimercfg_file.as_enable);
			}
			break;
		case e_snapT_interval:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_snapT_interval %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_snapT_interval,
						g_stSnaptimercfg_file.as_interval);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_snapT_interval %d\n",
						g_stSnaptimercfg_file.as_interval);
			}
			break;
		case e_snapT_type:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_snapT_type %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_snapT_type,
						g_stSnaptimercfg_file.as_type);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_snapT_type %d\n", g_stSnaptimercfg_file.as_type);
			}
			break;
		case e_user_number:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_user_number,
						g_stUsr_file.user_num);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_user_number %d\n", g_stUsr_file.user_num);
			}
			break;
		case e_user_opt_type:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_user_opt_type %d\n", iValue);
				if (iValue < 0 || iValue > MODIFY_USER
				)
					break;
				index = iValue;
			}
			break;
		case e_user_name:
			if (cmd_type == T_Set) {
				switch (index) {
				case ADD_USER:
					logInfo("set e_user_name:add user\n");
					break;
				case DEL_USER:
					logInfo("set e_user_name:delete user\n");
					break;
				case MODIFY_USER:
					logInfo("set e_user_name:modify user\n");
					break;
				}
			} else if (cmd_type == T_Get) {
				logInfo("get user name \n");
			}
			index1 = i;
			sprintf(cmd_tmp, "&%d=%s", e_user_name,
					g_stUsr_file.stUser[index1].username);
			strcat(pRet, cmd_tmp);
			ret++;
			break;
		case e_user_password:
			if (cmd_type == T_Set) {
				logInfo("set e_user_password %s\n", pValue);

			} else if (cmd_type == T_Get) {

			}
			break;
		case e_user_group:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_user_group %d\n", iValue);
			} else if (cmd_type == T_Get) {

			}
			break;
		case e_ft_serverip:
			if (cmd_type == T_Set) {
				logInfo("set e_ft_serverip %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_ft_serverip,
						g_stFtcfg_file.serverip);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ft_serverip %s\n", g_stFtcfg_file.serverip);
			}
			break;
		case e_ft_port:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ft_port %d\n", iValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ft_port, g_stFtcfg_file.port);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ft_port %d\n", g_stFtcfg_file.port);
			}
			break;
		case e_ft_username:
			if (cmd_type == T_Set) {
				logInfo("set e_ft_username %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_ft_username,
						g_stFtcfg_file.username);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ft_username %s\n", g_stFtcfg_file.username);
			}
			break;
		case e_ft_password:
			if (cmd_type == T_Set) {
				logInfo("set e_ft_password %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_ft_password,
						g_stFtcfg_file.password);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ft_password %s\n", g_stFtcfg_file.password);
			}
			break;
		case e_ft_mode:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_ft_mode %d\n", iValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ft_mode, g_stFtcfg_file.mode);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ft_mode %d\n", g_stFtcfg_file.mode);
			}
			break;
		case e_ft_dirname:
			if (cmd_type == T_Set) {
				logInfo("set e_ft_dirname %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_ft_dirname,
						g_stFtcfg_file.dirname);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ft_dirname %s\n", g_stFtcfg_file.dirname);
			}
			break;
		case e_smtp_serverip:
			if (cmd_type == T_Set) {
				logInfo("set e_smtp_serverip %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_smtp_serverip,
						g_stSmtpcfg_file.serverip);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_serverip %s\n", g_stSmtpcfg_file.serverip);
			}
			break;
		case e_smtp_port:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_smtp_port %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_smtp_port, g_stSmtpcfg_file.port);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_port %d\n", g_stSmtpcfg_file.port);
			}
			break;
		case e_smtp_sslflag:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_smtp_sslflag %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_smtp_sslflag,
						g_stSmtpcfg_file.ssl_flag);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_sslflag %d\n", g_stSmtpcfg_file.ssl_flag);
			}
			break;
		case e_smtp_logintype:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_smtp_logintype %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_smtp_logintype,
						g_stSmtpcfg_file.logintype);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_logintype %d\n", g_stSmtpcfg_file.logintype);
			}
			break;
		case e_smtp_username:
			if (cmd_type == T_Set) {
				logInfo("set e_smtp_username %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_smtp_username,
						g_stSmtpcfg_file.username);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_username %s\n", g_stSmtpcfg_file.username);
			}
			break;
		case e_smtp_password:
			if (cmd_type == T_Set) {
				logInfo("set e_smtp_password %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_smtp_password,
						g_stSmtpcfg_file.password);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_password %s\n", g_stSmtpcfg_file.password);
			}
			break;
		case e_smtp_from:
			if (cmd_type == T_Set) {
				logInfo("set e_smtp_from %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_smtp_from, g_stSmtpcfg_file.from);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_from %s\n", g_stSmtpcfg_file.from);
			}
			break;
		case e_smtp_to:
			if (cmd_type == T_Set) {
				logInfo("set e_smtp_to %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_smtp_to, g_stSmtpcfg_file.to);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_to %s\n", g_stSmtpcfg_file.to);
			}
			break;
		case e_smtp_subject:
			if (cmd_type == T_Set) {
				logInfo("set e_smtp_subject %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_smtp_subject,
						g_stSmtpcfg_file.subject);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_subject %s\n", g_stSmtpcfg_file.subject);
			}
			break;
		case e_smtp_text:
			if (cmd_type == T_Set) {
				logInfo("set e_smtp_text %s\n", pValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_smtp_text, g_stSmtpcfg_file.text);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_smtp_text %s\n", g_stSmtpcfg_file.text);
			}
			break;
		case e_vdmask_number:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_vdmask_number,
						g_stVidMaskcfg_file.aeraNum);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_vdmask_number %d\n", g_stVidMaskcfg_file.aeraNum);
			}
			break;
		case e_vdmask_NO:
//			if(cmd_type==T_Set){
			iValue = atoi(pValue);
			index = iValue;
			logInfo("e_vdmask_NO:%d\n", index);
//			}
			break;
		case e_vdmask_enable:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_vdmask_enable %d\n", iValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_vdmask_enable,
						g_stVidMaskcfg_file.aera[index].enable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_vdmask_enable %d\n",
						g_stVidMaskcfg_file.aera[index].enable);
			}
			break;
		case e_vdmask_x:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_vdmask_x %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_vdmask_x,
						g_stVidMaskcfg_file.aera[index].x);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_vdmask_x %d\n",
						g_stVidMaskcfg_file.aera[index].x);
			}
			break;
		case e_vdmask_y:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_vdmask_y %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_vdmask_y,
						g_stVidMaskcfg_file.aera[index].y);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_vdmask_y %d\n",
						g_stVidMaskcfg_file.aera[index].y);
			}
			break;
		case e_vdmask_w:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_vdmask_w %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_vdmask_w,
						g_stVidMaskcfg_file.aera[index].w);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_vdmask_w %d\n",
						g_stVidMaskcfg_file.aera[index].w);
			}
			break;
		case e_vdmask_h:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_vdmask_h %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_vdmask_h,
						g_stVidMaskcfg_file.aera[index].h);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_vdmask_h %d\n",
						g_stVidMaskcfg_file.aera[index].h);
			}
			break;
		case e_vdmask_color:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_vdmask_color %d\n", iValue);
			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_vdmask_color,
						g_stVidMaskcfg_file.aera[index].color);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_vdmask_color %d\n",
						g_stVidMaskcfg_file.aera[index].color);
			}
			break;
		case e_time_Zone:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_time_Zone %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_time_Zone,
						g_stTimecfg_file.timeZone);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_time_Zone %d\n", g_stTimecfg_file.timeZone);
			}
			break;
		case e_time_dstmode:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_time_dstmode %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_time_dstmode,
						g_stTimecfg_file.dstmode);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_time_dstmode %d\n", g_stTimecfg_file.dstmode);
			}
			break;
		case e_time_ntpenable:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_time_ntpenable %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_time_ntpenable,
						g_stTimecfg_file.ntpenable);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_time_ntpenable %d\n", g_stTimecfg_file.ntpenable);
			}
			break;
		case e_time_ntpserver:
			if (cmd_type == T_Set) {
				logInfo("set e_time_ntpserver %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_time_ntpserver,
						g_stTimecfg_file.ntpserver);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_time_ntpserver %s\n", g_stTimecfg_file.ntpserver);
			}
			break;
		case e_time_ntpinterval:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_time_ntpinterval %d\n", iValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_time_ntpinterval,
						g_stTimecfg_file.ntpinterval);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_time_ntpinterval %d\n",
						g_stTimecfg_file.ntpinterval);
			}
			break;
		case e_time_systime:
			if (cmd_type == T_Set) {
				logInfo("set e_time_systime %s\n", pValue);

			} else if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_time_systime,
						g_stTimecfg_file.sys_time);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_time_systime %s\n", g_stTimecfg_file.sys_time);
			}
			break;
		case e_sys_devtype:
			if (cmd_type == T_Get) {
				if (g_stAv_0_file.ubs[0].width == 1920) {
					g_stSyscfg_file.devtype = 1;
				} else {
					g_stSyscfg_file.devtype = 0;
				}
				sprintf(cmd_tmp, "&%d=%d", e_sys_devtype,
						g_stSyscfg_file.devtype); //0:720p 1:1080p
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_devtype %d\n", g_stSyscfg_file.devtype);
			}
			break;
		case e_sys_model:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_model, g_stSyscfg_file.model);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_model %s\n", g_stSyscfg_file.model);
			}
			break;
		case e_sys_hdversion:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_hdversion,
						g_stSyscfg_file.hardVersion);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_hdversion %s\n", g_stSyscfg_file.hardVersion);
			}
			break;
		case e_sys_swversion:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_swversion,
						g_stSyscfg_file.softVersion);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_swversion %s\n", g_stSyscfg_file.softVersion);
			}
			break;
		case e_sys_hardwareId:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_hardwareId,
						HARDWARE_ID);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_hardwareId %s\n", HARDWARE_ID);
			}
			break;
		case e_sys_manufacturer:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_manufacturer,
						MANUFACTURE_ID);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_manufacturer %s\n", MANUFACTURE_ID);
			}
			break;
		case e_sys_Model:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_Model, MODEL_ID);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_Model %s\n", MODEL_ID);
			}
			break;
		case e_sys_serialNumber:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_serialNumber, g_stSyscfg_file.model);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_serialNumber %s\n", g_stSyscfg_file.model);
			}
			break;
		case e_sys_devname:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_devname, g_stSyscfg_file.name);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_devname %s\n", g_stSyscfg_file.name);
			}
			break;
		case e_sys_startdate:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_sys_startdate,
						g_stSyscfg_file.startdate);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_startdate %s\n", g_stSyscfg_file.startdate);
			}
			break;
		case e_sys_runtimes:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_sys_runtimes,
						g_stSyscfg_file.runtimes);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_runtimes %s\n", g_stSyscfg_file.runtimes);
			}
			break;
		case e_sys_sdstatus:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_sys_sdstatus,
						g_stSyscfg_file.sdstatus);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_sdstatus %d\n", g_stSyscfg_file.sdstatus);
			}
			break;
		case e_sys_sdfreespace:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_sys_sdfreespace,
						g_stSyscfg_file.sdfreespace);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_sdfreespace %d\n",
						g_stSyscfg_file.sdfreespace);
			}
			break;
		case e_sys_sdtotalspace:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_sys_sdtotalspace,
						g_stSyscfg_file.sdtotalspace);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_sys_sdtotalspace %d\n",
						g_stSyscfg_file.sdtotalspace);
			}
			break;
		case e_nvr_opt:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set e_nvr_opt %d\n", iValue);
			}
			break;
		case e_nvr_forIDR:
			if (cmd_type == T_Set) {
				//set_IDR_BR(channel, sub_channel);
				logInfo("set e_nvr_forIDR\n");
			}
			break;
		case e_nvr_clientID:
			if (cmd_type == T_Get) {
				iValue = atoi(pValue);
				sprintf(cmd_tmp, "&%d=%d", e_nvr_clientID, iValue);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_nvr_clientID %d\n", iValue);
			}
			break;
		case e_enc_resolution:
			if (cmd_type == T_Get) {
				if (g_stAv_0_file.ubs[0].width == 1920) {
					iValue = 1;
				} else {
					iValue = 0;
				}

				sprintf(cmd_tmp, "&%d=%d", e_enc_resolution, iValue);
				strcat(pRet, cmd_tmp);

//				logInfo("==============to get resolution: %d.\n", iValue);

				ret++;
				logInfo("get e_enc_resolution %d\n", iValue);
			} else {
				iValue = atoi(pValue);
				logInfo("set e_enc_resolution %d\n", iValue);
			}
			break;

		case e_reset:
			if (cmd_type == T_Set) {
				logInfo("set e_reset \n");
			}
			break;
		case e_ptz_continue_move_vx:
			if (cmd_type == T_Set) {
				fValue = atof(pValue);
				logInfo("set ptz continous move pan %f", fValue);
			}
			break;
		case e_ptz_continue_move_vy:
			if (cmd_type == T_Set) {
				fValue = atof(pValue);
				logInfo("set ptz continous move tilt %f", fValue);
			}
			break;
		case e_ptz_continue_move_vzoom:
			if (cmd_type == T_Set) {
				fValue = atof(pValue);
				logInfo("set ptz continous move zoom %f", fValue);
			}
			break;
		case e_ptz_continue_move_timeout:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set ptz stop timeout %d", iValue);
			}
			break;
		case e_ptz_continue_move_default_timeout:
			if (cmd_type == T_Get) {
				iValue = 15;
				sprintf(cmd_tmp, "&%d=%d", e_ptz_continue_move_default_timeout,
								iValue);
				logInfo("get ptz default timeout %d", iValue);
			}
			break;
		case e_ptz_stop_pt:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set ptz stop pan/tilt %d", iValue);
			}
			break;
		case e_ptz_stop_zoom:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set ptz stop zoom %d", iValue);
			}
			break;
		case e_ptz_presets_capacity:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%d", e_ptz_presets_capacity,
						ptz_preset_capacity);
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ptz_presets_capacity %d\n",
						ptz_preset_capacity);
			}
			break;
		case e_ptz_allpresets:
			if (cmd_type == T_Get) {
				sprintf(cmd_tmp, "&%d=%s", e_ptz_allpresets,
						"1/64");
				strcat(pRet, cmd_tmp);
				ret++;
				logInfo("get e_ptz_allpresets %s\n",
						"1/64");
			}
			break;
		case e_ptz_preset:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set ptz preset %d", iValue);
			}
			break;
		case e_ptz_goto_preset:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set ptz goto preset %d", iValue);
			}
			break;
		case e_ptz_deletepreset:
			if (cmd_type == T_Set) {
				iValue = atoi(pValue);
				logInfo("set ptz delete preset %d", iValue);
			}
			break;
		default:
			break;
		}

	} while (parseIndex != -1);

	strcat(pRet, "#");

	return ret;
}
#endif

#define	UN_AVSERVER_DOMAIN	"/tmp/avserver.domain"
int main(int argc, char *argv[]) {
	int ch_num, stream, i;
	int server_fd, client_fd;
	int max_socket_fd = -1;
	struct sockaddr_un client_addr;
	int readlen = -1;
	int ret = -1;
	char *pMsg_buf;
	char *pRet_buf;
	fd_set readfset;
	int len = 0;

	init();
	server_fd = create_server(UN_AVSERVER_DOMAIN);
	if (server_fd < 0) {
		logInfo("interface_demo: error create server_fd.\n");
		return 1;
	}

	pMsg_buf = (char *) malloc(MAX_CMD_LEN * sizeof(char));
	if (NULL == pMsg_buf) {
		return 1;
	}
	pRet_buf = (char *) malloc(MAX_CMD_LEN * sizeof(char));
	if (NULL == pRet_buf) {
		free(pMsg_buf);
		return 1;
	}

	if (listen(server_fd, 1) < 0) {
		goto error_avserver;
	}
	client_fd = -1;

	//arrClient_fd[0] = server_fd;

	sleep(1);

	logInfo("start...\n");
	while (1) {
		FD_ZERO(&readfset);
		FD_SET(server_fd, &readfset);
		max_socket_fd = server_fd;

		if (client_fd > 0) {
			FD_SET(client_fd, &readfset);
			max_socket_fd =
					(max_socket_fd < client_fd) ? (client_fd) : (max_socket_fd);
		}

		logInfo("select start...max_socket_fd=%d\n", max_socket_fd);

		ret = select(max_socket_fd + 1, &readfset, NULL, NULL, NULL);
		if (ret <= 0) {
			continue;
		}
		if (FD_ISSET(server_fd, &readfset)) {
			logInfo("client comming.\n");
			len = sizeof(client_addr);
			client_fd = accept(server_fd, (struct sockaddr*) &client_addr,
					&len);
			if (client_fd < 0) {
				continue;
			}
			continue;
		}
		{
			if (FD_ISSET(client_fd, &readfset)) {

//				readlen = read(client_fd, (void *)pMsg_buf, sizeof(Pack_Msg));
				readlen = read(client_fd, (void *) pMsg_buf, MAX_CMD_LEN);
				if (readlen <= 3) {
					FD_CLR(client_fd, &readfset);
					close(client_fd);
					client_fd = -1;
					continue;
				}

				fprintf(stdout, "get len is %d, data: %s.\n", readlen,
						pMsg_buf);
				memset(pRet_buf, 0, MAX_CMD_LEN * sizeof(char));
				len = processMsg(pMsg_buf, strlen(pMsg_buf), pRet_buf);
				fprintf(stdout, "return len: %d.\n", len);
				if (len == 0)
					continue;
				fprintf(stdout, "return data: %s.\n", pRet_buf);
				if (write(client_fd, pRet_buf, /*strlen(pRet_buf)*/MAX_CMD_LEN)
						< 0) {
					fprintf(stdout, "write error.\n");
					if (errno == EBADF) {
						FD_CLR(client_fd, &readfset);
						close(client_fd);
						client_fd = -1;
					}
				}
			}
		}
	}

	error_avserver: if (pMsg_buf != NULL)
		free(pMsg_buf);
	if (pRet_buf != NULL)
		free(pRet_buf);

	if (server_fd > 0) {
		close(server_fd);
	}

	return 0;
}
