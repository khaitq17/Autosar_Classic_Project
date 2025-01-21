/***************************************************************************
 * @file    Pwm.c
 * @brief   Định nghĩa các hàm điều khiển PWM
 * @details File này triển khai các hàm để điều khiển độ rộng xung PWM của 
 *          vi điều khiển. Nó bao gồm các chức năng khởi tạo và thiết lập
 *          ty lệ nhiệm vụ cho PWM.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Pwm.h"
#include <stdio.h>

/**************************************************************************
 * @brief   Khởi tạo PWM
 * @details Hàm này khởi tạo PWM với cấu hình được truyền vào.
 * @param   ConfigPtr    Con trỏ trỏ đến cấu hình PWM
 * @return 	None  
 **************************************************************************/
void Pwm_Init(const Pwm_ConfigType* ConfigPtr) {
    printf("PWM Initialized for Channel %d with Period %d ms and Duty Cycle %d%%\n", 
           ConfigPtr->Pwm_Channel, ConfigPtr->Pwm_Period, ConfigPtr->Pwm_DutyCycle);
}

/**************************************************************************
 * @brief   Cài đặt tỷ lệ nhiệm vụ
 * @details Hàm này cài đặt tỷ lệ nhiệm vụ (duty cycle) cho kênh PWM.
 * @param   ChannelNumber   Kênh PWM
 * @param   DutyCycle       Tỷ lệ nhiệm vụ (duty cycle)
 * @return 	None  
 **************************************************************************/
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle) {
    printf("PWM Channel %d set to Duty Cycle: %d%%\n", ChannelNumber, DutyCycle);
}