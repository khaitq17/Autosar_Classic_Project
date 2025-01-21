/***************************************************************************
 * @file    Pwm.h
 * @brief   Khai báo giao diện điều khiển PWM (Pulse Width Modulation)
 * @details File này cung cấp giao diện để điều khiển độ rộng xung PWM của
 *          vi điều khiển. Nó chứa các kiểu dữ liệu định nghĩa, cấu trúc 
 *          cấu hình và các hàm liên quan đến PWM.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef PWM_H
#define PWM_H

#include "Std_Types.h"

/**************************************************************************
 * @typedef Pwm_ChannelType
 * @brief 	Định nghĩa kiểu dữ liệu cho kênh PWM
 * @details Kiểu dữ liệu này được sử dụng cho tất cả các kênh PWM.
 **************************************************************************/
typedef uint8	Pwm_ChannelType;

/**************************************************************************
 * @typedef Pwm_PeriodType
 * @brief 	Định nghĩa kiểu dữ liệu cho chu kỳ PWM
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn chu kỳ của PWM.
 **************************************************************************/
typedef uint16	Pwm_PeriodType;

/**************************************************************************
 * @struct	Pwm_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho PWM
 * @details Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho PWM.
 **************************************************************************/
typedef struct {
    Pwm_ChannelType Pwm_Channel;    /* Kênh PWM */
    Pwm_PeriodType Pwm_Period;      /* Chu kỳ của PWM */
    uint16 Pwm_DutyCycle;           /* Tỷ lệ nhiệm vụ (duty cycle) của PWM */
} Pwm_ConfigType;

/**************************************************************************
 * @brief   Khởi tạo PWM
 * @param   ConfigPtr    Con trỏ trỏ đến cấu hình PWM
 * @return 	None  
 **************************************************************************/
void Pwm_Init(const Pwm_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief   Cài đặt tỷ lệ nhiệm vụ
 * @param   ChannelNumber   Kênh PWM
 * @param   DutyCycle       Tỷ lệ nhiệm vụ (duty cycle)
 * @return 	None  
 **************************************************************************/
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);

#endif /* PWM_H */