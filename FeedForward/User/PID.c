#include "PID.h"

/**************************����PID���˹��㱣����û���κ�����**********************************/
/********************************************************************************************
*�ǶȻ�-KI��0
*�ٶȻ�-KD��0
*�ȵ��ٶȻ������ٶȻ���ʵ����������ٵ��Ƕȡ�
********************************************************************************************/

float Limit_Min_Max(float value,float min,float max);

/**
 * @brief PID�����ʼ��
 * @param PID PID����
 * @param kp 
 * @param ki 
 * @param kd 
 * @param i_max 
 * @param out_max 
 */
void PID_init(PID_struct_t *PID,
              float kp,
              float ki,
              float kd,
              float kf,
              float i_max,
              float out_max)//PID��ʼ������
{
  PID->kp      = kp;
  PID->ki      = ki;
  PID->kd      = kd;
  PID->kf      = kf;
  PID->i_max   = i_max;//�����޷�
  PID->out_max = out_max;//����޷�
}

/**
 * @brief PID���㱣��
 * @param pid PID�ṹ��
 * @param angle_max �Ƕ�����
 */
void PID_Protect(PID_struct_t *pid,float angle_max)
{
  float half_angle = angle_max/2;
	if(pid->ref[0] - pid->fdb > half_angle)
	{
		pid->fdb+=angle_max;
	}
	else if(pid->ref[0] - pid->fdb < -half_angle)
	{
		pid->fdb-=angle_max;
	}
}

/**
 * @brief PID�ǶȻ����㺯��
 * @param PID PID�ṹ��
 * @param ref �趨ֵ
 * @param fdb ʵ��ֵ
 * @param angle_max �Ƕ�����
 * @param i_out ���ַ��������Ϊ0ʱ��Ч��
 * @return PID������
 */
float PID_Calc_Angle(PID_struct_t *PID, float ref, float fdb,float angle_max,float i_out)//PID���㺯����Ŀ�꣬ʵ�ʣ�
{
  PID->ref[0] = ref;
  PID->fdb = fdb;
  PID->f_out = PID->kf * (PID->ref[0] - PID->ref[1]);
	PID_Protect(PID,angle_max);//���㱣��

  PID->err[0] = PID->ref[0] - PID->fdb;

  PID->p_out  = PID->kp * PID->err[0];
  PID->i_out += PID->ki * PID->err[0];
  PID->d_out  = PID->kd * (PID->err[0] - PID->err[1]);
  PID->i_out=Limit_Min_Max(PID->i_out, -PID->i_max, PID->i_max);
  
  PID->output = PID->p_out + PID->i_out + PID->d_out + PID->f_out;
  PID->output=Limit_Min_Max(PID->output, -PID->out_max, PID->out_max);

  PID->err[1] = PID->err[0];
  PID->ref[1] = PID->ref[0];
  return PID->output;
}

/**
 * @brief �ٶȻ�PID
 * @param PID PID�ṹ��
 * @param ref �趨ֵ
 * @param fdb ʵ��ֵ
 * @return PID������
 */
float PID_Calc_Speed(PID_struct_t *PID, float ref, float fdb)
{
  PID->ref[0] = ref;
  PID->fdb = fdb;

  PID->f_out = PID->kf * (PID->ref[0] - PID->ref[1]);

  PID->err[0] = PID->f_out + PID->ref[0] - PID->fdb;

  PID->p_out  = PID->kp * PID->err[0];
  PID->i_out += PID->ki * PID->err[0];
  PID->d_out  = PID->kd * (PID->err[0] - PID->err[1]);
  PID->i_out=Limit_Min_Max(PID->i_out, -PID->i_max, PID->i_max);
  
  PID->output = PID->p_out + PID->i_out + PID->d_out;
  PID->output=Limit_Min_Max(PID->output, -PID->out_max, PID->out_max);

  PID->ref[1] = PID->ref[0];
  PID->err[1] = PID->err[0];

  return PID->output;
}

/**
 * @brief ����һ���������� value ��ָ������Сֵ min �����ֵ max ֮��
 * @param value ����ֵ
 * @param min ��Сֵ
 * @param max ���ֵ
 * @return 
 */
float Limit_Min_Max(float value,float min,float max)
{
	if(value<min)
		return min;
	else if(value>max)
		return max;
	else return value;
}

