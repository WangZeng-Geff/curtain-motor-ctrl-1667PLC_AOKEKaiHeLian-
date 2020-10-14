

#ifndef _SETTINGS_H_
#define _SETTINGS_H_
#include <types.h>
#define FLASH_SECTOR_SIZE		(1024u)
#define FLASH_SECTOR_MASK		(FLASH_SECTOR_SIZE - 1)
#define SETTING_MAGIC			(0x55AAu)
#define SETTING_FROM			(70 * 1024u)
#define SETTING_SIZE			(2 * 1024u)
#define SETTING_INVALID_ADDR	(SETTING_FROM + SETTING_SIZE)

//#define MAX_LOW_TEMP_PROTECT 80//���±����¶�  5~8��	ʹ���� ���»ز��¶����
//#define MIN_LOW_TEMP_PROTECT 50//���±����¶�  5~8��
#define SAVE_TIME				600 /*��Ϣ����ʱ�� S*/
#define B_KEEP_TIME 			5  /*�������ʱ�� S*/
#define LCD_BLINK_TM			5 /*LCD��˸��ͼ�걣������ʱ�� *100ms  ����500ms*/
#define LCD_DATA_TM 			30 /*LCD��˸��ͼ�걣������ʱ�� *100ms  ����3s*/

//--------------------------------------------------------------------------
//�̵�������
#define H_OPEN					0x03 
#define M_OPEN					0x05
#define L_OPEN					0x09
#define H_CLOSE 				0x02
#define M_CLOSE 				0x04
#define L_CLOSE 				0x08
#define N_CLOSE 				0x00	

//--------------------------------------------------------------------------
typedef struct sensor
{
int16_t 		temp;								//�¶� ��ʮ��ʵ���¶� ����1λС��
int16_t 		humi;								//ʪ�� ͬ��
uint8_t 		poweron 		: 1;				//��ʱһ��ʱ���ٽ��м̵�����������ֹ�ϵ���¶�δ����ʱ�̵�������
uint8_t 		breakdown;							//����������  1Ϊ���� 0Ϊ����  ��ԭ����Ϊ���ʾ �����ϱ�ʱ��Ҫȡ�ֽڵ�ַ��
} sensor_status_t;


/*���޸İ���˳�� �޸�����˳�򼴿�*/
enum key_list
{
KEY_SWITCH = 0, 
KEY_DEC, 
KEY_ADD, 
KEY_MODE, 
KEY_SPEED, 
KEY_LOCK,											/*����ʵ�ʰ�����ʵ�����������ĳ���ִ��*/
};


enum act_flag
{
LOWTEMP = 0,										/*���±���*/
EN_ACT, 

//	EN_AUTO,/*�����Զ�*/	
EN_TIME,											/*ʱ�ο��Ʊ�־*/
EN_MAN, 											/*ʱ������Ϊ������־*/
EN_PLC, 
EN_PLC_RUN, 
};


//---------------------------------------------------
//ˢ����ʾ������
enum 
{
DIS_OTHER, 
DIS_CLOCK, 
};


/*��ö��˳�򲻿ɶ�	��winspeed���Ӧ*/
enum wind_speed
{
WIN_LOW, 
WIN_MIDDLE, 
WIN_HIGH, 
WIN_AUTO, 
};


/*��ö��˳�򲻿ɶ�	��mode���Ӧ*/
enum 
{
MODE_COOL = 0, 
MODE_HEAT, 
MODE_VENTILATE, 
};

typedef struct rgb_str
{
uint8_t 		r;
uint8_t 		g;
uint8_t 		b;
} rgb_t;

#ifdef configUSING_LOCALTIME


enum dev_time_list
{
_YY, 
_MM, 
_DD, 
_WW, 
_H, 
_M, 
_S, 
};


typedef struct dev_time
{
uint8_t 		time[7];							/*��������ʱ����*/
uint8_t 		date_flag_set	: 1;				/*ƽ̨�·�����*/
uint8_t 		time_flag_set	: 1;				/*ƽ̨�·�ʱ��*/
uint8_t 		date_flag_ok	: 1;				/*��ȡ���ڳɹ�*/
uint8_t 		time_flag_ok	: 1;				/*��ȡʱ��ɹ�*/
} dev_time_t;


#endif

typedef struct special_fun
{
uint8_t 		flag;								//2 3 ��־ͬʱ������־
uint8_t 		cnt0;								/*ʱ�� 2 3ʱ����*/
uint8_t 		num;								/*����*/
uint8_t 		cnt1;								/*��ʱ�䲻���Զ��˳�*/
} dev_special_fun_t;


typedef struct DevStateInfo
{
uint8_t 		state;								/*�̵���״̬*/
uint8_t 		state_bak;
int16_t 		set_temp;
uint8_t 		air_coner_switch;
uint8_t 		relay_num;
uint8_t 		need_act;
uint8_t 		act_chn;
uint8_t 		param_save;
uint8_t 		need_restore;
sensor_status_t sensor; 							/*������״̬*/
uint16_t		act_flag;							/*ͨ��ö��EN_ ����λʹ��*/
uint8_t 		low_protect_act;					/*���±���������־*/
uint8_t 		check_online_cnt;					/*������߼���*/
uint16_t		power_delay_cnt;					/*����ϵ���ʱ����*/
uint8_t 		lcd_on_cnt; 						/*LCD�ϵ�ȫ��ʱ��*/
uint16_t		run_save_cnt;						/*����״̬��Ϣ�洢����*/
uint8_t 		plc_run_cnt;						/*PLCͨ����˸����*/

#ifdef configUSING_LOCALTIME
dev_time_t		dev_time;
uint8_t 		get_time_cnt;
uint8_t 		power_report;
#endif
rgb_t           rgb_data;

uint8_t 		period_invaild_num; 				/*��Чʱ���*/
dev_special_fun_t special_fun;
} dev_state_info_t;


extern dev_state_info_t dev_state;

typedef struct period_ctrl /*ʱ�ο���*/
{
uint8_t 		mode;								/*ʱ�ο���ģʽ0����ʹ�� 1������ 2��5���2��*/
uint8_t 		week[2];							/*��Чʱ�� bit0-bit6 ��1-����+*/
uint8_t 		num[2]; 							/*ʱ����*/
uint16_t		start[2][6];						/*��ʼʱ�����*/
uint16_t		end[2][6];							/*��ֹʱ�����*/
uint8_t 		onoff[2][6];
int16_t 		set_temp[2][6];
} period_ctrl_t;

typedef struct setting_hdr
{
uint16_t		magic;
uint16_t		crc;
} setting_hdr_t;


typedef struct 
{
uint8_t 		sn[12];
uint8_t 		dkey[8];
uint8_t 		id[4];
uint8_t 		pwd[2];
} encode_t;


typedef struct 
{
uint8_t 		gid[4];
uint8_t 		panid[2];
uint8_t 		sid[2];
} para_t;


typedef struct CtrlInfo
{
uint8_t 		idx;
uint8_t 		aid[4];
uint8_t 		chn;
} ctrl_info_t;


typedef struct DevInfo
{
#if 0
uint32_t		opt_cnt[2]; 						/*����ͳ�� 0Ϊ���Ŵ��� 1Ϊ���ش���*/

uint32_t		time_cnt[5]; /*�̵�������ʱ�� 0 1 2 3 4	�ֱ�Ϊ���� �� �� �� ��
	��*/
period_ctrl_t	period_ctrl;						/*ʱ�ο���*/
uint8_t 		report;
uint16_t		temp_report_freq;
uint16_t		temp_report_step;
uint16_t		humi_report_freq;
uint16_t		humi_report_step;
uint8_t 		mode;								/*ģʽ  0cool 1heat 2*/
uint8_t 		win_speed;							/*����*/
int16_t 		set_temp;							/*���������¶� ���ܻ�����ʱ�ο����޸�*/
uint8_t 		air_coner_switch;					/*�յ�����*/
uint16_t		return_diff_temp;					/*�ز��¶� Ĭ��1��*/
uint16_t		power_delay;						/*�ϵ紫������ʱʱ��*/
uint8_t 		panel_lock; 						/*�������*/
uint8_t 		backlight_enable;					//����
uint8_t 		auto_disable;						/*�Զ���ģʽ�� �ﵽ�趨�¶Ⱥ��Ƿ����ͨ��*/
uint16_t		low_deadband;						/*���»ز��¶� Ĭ��*/
uint8_t 		low_temp_switch;					/*���±�������*/
uint16_t		low_protect_temp;					//���±����¶�
uint16_t		max_set_temp;						//��������¶�
uint16_t		min_set_temp;						//��С�����¶�
uint16_t		max_heat_temp;						//��������¶�
uint16_t		min_heat_temp;						//��С�����¶�
uint16_t		max_cool_temp;						//��������¶�
uint16_t		min_cool_temp;						//��С�����¶� 
int16_t 		humi_compensation;					//ʪ�Ȳ���
int16_t 		temp_compensation;					//�¶Ȳ���
#endif
uint8_t           actuation_time;                                    //�̵���������
} dev_info_t;


typedef struct 
{
setting_hdr_t	hdr;

/* device */
encode_t		encode;

/* para */
para_t			para;

/* ctrl */
ctrl_info_t 	ctrl[4];

/* dev */
dev_info_t		dev_infor;
} __attribute__((aligned(4)))

setting_t;


#define SETTING_HDR_SIZE		(sizeof(setting_hdr_t))
#define SETTING_DAT_SIZE		(sizeof(setting)-sizeof(setting_hdr_t))
#define setting_addr(s) 		((uint8_t*)&s + SETTING_HDR_SIZE)
extern setting_t setting;
int disk_erase(uint32_t start, uint32_t size);
int disk_write(uint32_t start, const void * data, uint32_t size);
int disk_read(uint32_t start, void * data, uint32_t size);
void setting_save(void);
void setting_load(void);
void dev_restore_factory(void);

#endif

