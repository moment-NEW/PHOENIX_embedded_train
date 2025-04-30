#ifndef __PID_H_
#define __PID_H_

#include "main.h"
#include "can.h"
#include "stm32f4xx.h"
#include "dvc_dji_gm6020.h"


typedef struct
{   
    float P;//�趨�ٶ�
    float I;//�趨�Ƕ�
	  float D;

}PID;


float position_PID(float target, float current);
float velocity_PID(float target, float current);
#endif
