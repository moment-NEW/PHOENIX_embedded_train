#include "GM6020.h"

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
        case 0x202://�������ı�ʶ��
        {
            GM6020.rotor_angle    = ((rx_data[0] << 8) | rx_data[1]);//���ջ�е�Ƕȣ�16bit��
            GM6020.rotor_speed    = ((rx_data[2] << 8) | rx_data[3]);//����ת�٣�16bit��
            GM6020.torque_current = ((rx_data[4] << 8) | rx_data[5]);//����ʵ��ת��
            GM6020.temp           =   rx_data[6];//���յ���¶ȣ�8bit��
            break;
        }
    }
}

void Set_GM6020_Gimbal_Voltage(CAN_HandleTypeDef* hcan,Moto_GM6020_t GM6020)
{
    CAN_TxHeaderTypeDef tx_header;
    uint8_t             CAN1_tx_data[8] = {0};
    
    tx_header.StdId = 0X200;//��ʶ�������ֲ�P6��
    tx_header.IDE   = CAN_ID_STD;//��׼ID
    tx_header.RTR   = CAN_RTR_DATA;//����֡
    tx_header.DLC   = 8;//�ֽڳ���
    CAN1_tx_data[2] = ((int16_t)GM6020.Speed_PID.output>>8)&0xff;
    CAN1_tx_data[3] = ((int16_t)GM6020.Speed_PID.output)&0xff;
    HAL_CAN_AddTxMessage(&hcan1, &tx_header, CAN1_tx_data,(uint32_t*)CAN_TX_MAILBOX0);
}
