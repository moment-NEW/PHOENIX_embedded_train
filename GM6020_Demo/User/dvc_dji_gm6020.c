#include "dvc_dji_gm6020.h"

HAL_StatusTypeDef can_1;
extern Moto_GM6020_t GM6020;
/**
 * @file GM6020.c
 * @brief GM6020���ܷ������ĺ���
 * @param StdId ���ID
 * @param rx_data CANͨ���յ�������
 * @author HWX
 * @date 2024/10/20
 */
void Get_GM6020_Motor_Message(uint32_t StdId,uint8_t rx_data[8])
{
    switch(StdId)//����ָ�������������Ϣ
    {
        case 0x207://�������ı�ʶ��
        {
            GM6020.rotor_angle    = ((rx_data[0] << 8) | rx_data[1]);//���ջ�е�Ƕȣ�16bit��
            GM6020.rotor_speed    = ((rx_data[2] << 8) | rx_data[3]);//����ת�٣�16bit��
            GM6020.torque_current = ((rx_data[4] << 8) | rx_data[5]);//����ʵ��ת��
            GM6020.temp           =   rx_data[6];//���յ���¶ȣ�8bit��
            break;
        }
    }
}

