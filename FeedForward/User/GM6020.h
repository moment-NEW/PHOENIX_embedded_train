#ifndef __GM6020_H__
#define __GM6020_H__

#include "main.h"
#include "can.h"
#include "stm32f4xx.h"
#include "PID.h"


typedef struct
{
    uint16_t can_id;//���ID
    int16_t  set_voltage;//�趨�ĵ�ѹֵ
    uint16_t rotor_angle;//����Ƕ�
    int16_t  rotor_speed;//����ٶ�
    int16_t  torque_current;//���Ť��
    uint8_t  temp;//�¶�
    float Set_Speed;//�趨�ٶ�
    float Set_Angle;//�趨�Ƕ�
    PID_struct_t Speed_PID;    
    PID_struct_t Angle_PID;
}Moto_GM6020_t;

void Set_GM6020_Gimbal_Voltage(CAN_HandleTypeDef* hcan,Moto_GM6020_t GM6020);
void Get_GM6020_Motor_Message(uint32_t StdId,uint8_t rx_data[8]);

#endif
