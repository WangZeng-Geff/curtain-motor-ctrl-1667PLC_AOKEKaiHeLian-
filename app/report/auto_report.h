#ifndef _RREPORT_H_
#define _RREPORT_H_
#include <stdint.h>
#include <string.h>
//---------------------------------------------------------------------------------------------------------

#define TYPE_NUM				     	        3 /* support sensor or alarm or actor type number,please modify depend on your system */
#define SUBSCRIBER_NUM                          3 /* please modify depend on your system */

#define MAX_ACTOR_NUM				            6 /* please modify depend on your system *//*���� ���� ���±��� �����¶� ������� ģʽ*/
#if MAX_ACTOR_NUM
#define SOFT_ACTOR                              0 /* soft actor or not */
#define TAKER_DATA                              7 /* please don't modify this */
#endif

//#define MAX_ALARM_NUM                           2 /* please modify depend on your system */ //���ºʹ���������
#if MAX_ALARM_NUM
#define ALARM_REPORT_SB                         0 /* alarm data report subscriber or not */
#endif

//#define MAX_SENSOR_NUM                          2 /* please modify depend on your system */
#if MAX_SENSOR_NUM
#define SENSOR_REPORT_SB                        1  /* sensor data report subscriber or not */
#define  DIGITAL_WIN                            0  /* digital sensor window val */
#endif

#define MAX_TRY_CNT                             2
#define MAX_SUBSCRIBER_NUM                      (TYPE_NUM + SUBSCRIBER_NUM)
#define CHANNEL_COMMUNICATE_ABILITY             2/*assess the channel communicate ability,for example 2 means trans waits 2seconds for the ack*/
#define FIRST_RETRY_INTERVAL                    10//s
#define SECOND_RETRY_INTERVAL                   100//s
#define POWER_ON_COMPARE_DATA                   100  /* the data maybe diffrerent */

//---------------------------------------------------------------------------------------------------------
#ifndef STC
#define STC   0x7E
#endif

#ifndef ID_LEN
#define ID_LEN   0x04
#endif

#ifndef DID_LEN
#define DID_LEN 0X02
#endif

#ifndef NULL
#define NULL  0
#endif
typedef enum _data_type_t
{
	UNKNOWN = 0,
	VOLTAGE,
	CURRENT,
	TEMP,
	HUMI,
	BRIGHTNESS,
	SMOKE,
	GAS,
	CO,
	INFRARED,
	ACTOR,
	ILLUMINATION,
	POWER,
    BODY
    //add your sensor type
}data_type_t;

typedef enum _wait_channel_ability_t
{
	WAIT_CHANNEL_ABILITY = 1,
	WAIT_FOR_TIME
}wait_channel_ability_t;

typedef enum _report_ack_t
{
	NO_ACK,
	YES_ACK
}report_ack_t;

typedef enum _report_type_t
{
	POWER_ON = 1,
	REGISTER,
	STATE_CHANGE,
	FIXED_LENGTH,
	FREQUENCY,
	ALARM,	
	REPORT_NUM,
}report_type_t;

typedef enum _report_process_t
{
	IDLE,
	STOP,
	SETTING,
	WAITING
}report_process_t;

typedef enum _report_attribute_t
{
	UNRELIABLE = 0,
	RELIABLE
}report_attribute_t;

enum 
{
	REPORT_NO,
	REPORT_GW,
	REPORT_SB
};

typedef enum _state_change_mode_t
{
    FREE,
    P2P,
    BROADCAST,
    LOCAL
}state_change_mode_t;

typedef enum _flag_type_t
{
	UNFINISHED,
	FINISHED
}flag_type_t;

enum
{
    FALSE = 0,
    TRUE
};

typedef struct _report_para_t
{
	uint8_t state_flag;//״̬��־
	uint8_t ack_state;//ACK״̬
	report_type_t report_typ;//�ϱ�����
	uint8_t report_seq;//�ϱ�֡���
	uint8_t time_count;//ʱ�����
	uint8_t retry_count;//���Լ���
}report_para_t;

typedef struct _delay_data_t
{
	uint32_t invalid_time;//��Чʱ��
	uint32_t freq;//Ƶ��
	int32_t power_on_time_count;//�ϵ�ʱ�����
	int32_t register_time_count;//ע��ʱ�����
	int32_t relay_time_count;//�̵���ʱ�����
	int32_t sensor_time_count;//������ʱ�����
}delay_data_t;

typedef struct _flags_t
{
	uint8_t power_on_report;//�ϵ��ϱ�
	uint8_t register_report;//ע���ϱ�  TURE��ʼ  FALSE����
	uint8_t state_report_start;//��ʼ״̬�ϱ�
	uint8_t dev_state;//�豸״̬
	uint8_t sensor_fixed_length_reporting;//�����������ϱ�
	uint8_t sensor_fixed_length_report_start;//��������ʼ�����ϱ�
	uint8_t sensor_fixed_freq_report_start;//��������ʼ��Ƶ�ϱ�
	uint8_t alarm_report_start;//�澯�ϱ�
}flags_t;

typedef struct _sensor_data_t
{
	data_type_t sensor_type;//����������
	uint8_t fixed_len_reporting;//�����ϱ�
    int32_t sensor_cur;//����������ֵ
    uint16_t sensor_step;//����������
	uint16_t sensor_freq;//������Ƶ��
	int32_t last_report;//���һ���ϱ�
	int32_t sensor_base;//��������׼
	int32_t sensor_window;//����������
}sensor_data_t;

typedef struct _act8_data_t//8bits
{
	uint8_t *cur;
}act8_data_t;
typedef struct _act16_data_t//8bits
{
	int16_t *cur;
}act16_data_t;

typedef struct _judge_data_t
{
#if MAX_ACTOR_NUM
	uint8_t  taker_id[ID_LEN];
	uint8_t  last_id[ID_LEN];
	uint8_t  equipment_gid;
    uint8_t  find_myself;
#endif
#if SUBSCRIBER_NUM
	uint8_t subs_pos;
	uint8_t subs_id[ID_LEN * SUBSCRIBER_NUM];
#endif

	uint8_t * report_object;
	uint8_t  gw_id[ID_LEN];
	uint8_t  my_id[ID_LEN];
    uint8_t  default_report;
}judge_data_t;

typedef struct _sub_pos_t
{
#if MAX_ACTOR_NUM
	uint8_t state_change_pos;
#endif
#if MAX_SENSOR_NUM
	uint8_t fixed_length_pos;
	uint8_t fixed_freq_pos;
#endif
#if MAX_ALARM_NUM
	uint8_t alarm_pos;
#endif
}sub_pos_t;

#if MAX_ACTOR_NUM
extern act8_data_t act8_data[MAX_ACTOR_NUM];
extern uint8_t act8_data_bak[MAX_ACTOR_NUM];
extern act16_data_t act16_data[1];//u16�������� �����¶�
extern int16_t act16_data_bak[1];
extern void local_key_report(void);
#endif

#if MAX_ALARM_NUM
extern act8_data_t alarm_data[MAX_ALARM_NUM];
extern uint8_t alarm_data_bak[MAX_ALARM_NUM];
#endif

#if MAX_SENSOR_NUM
extern sensor_data_t sensor_data[MAX_SENSOR_NUM];
extern int8_t get_sensor_from_type(data_type_t data_type);
extern void reload_freq_infor(void);
#endif

extern judge_data_t judge_data;

void auto_report_sec_task(void);
extern void stop_report_para(uint8_t pos);
extern void report_frame_ack(uint8_t seq, uint8_t source_addr[], uint8_t *fbd);
extern void auto_report_init(uint32_t invalid_time, uint8_t gateway_id[], uint8_t my_id[], uint8_t sid[], uint8_t *report_object);
extern void register_report(uint8_t gateway_id[]);
extern void save_subscriber_infor(uint8_t cmd,uint8_t *said,uint8_t *taid);
extern void save_subscriber_infor_ready(void);

uint8_t get_1byte_bit1_number(uint8_t data, uint8_t pos);
extern int peek_chn(int chn, uint8_t buf[], int len);
extern int get_chn(int chn, uint8_t buf[], int len);
extern int put_chn(int chn, const void *in, int len);
extern void clear_chn(int chn);
void clear_equipment_gid_flag(void);//����豸GID��Ϣ
uint8_t is_nogateway_or_power_report_unfinish(void);

#endif
