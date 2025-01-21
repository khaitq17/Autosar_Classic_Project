/***************************************************************************
 * @file    IoHwAb_MotorDriver.c
 * @brief   Định nghĩa các hàm giao diện cho mô-tơ
 * @details File này triển khai các hàm để tương tác với phần cứng mô-tơ.  
 *          Nó chứa định nghĩa các hàm để khởi tạo và đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IoHwAb_MotorDriver.h"
#include "Pwm.h"  // Gọi API PWM từ MCAL
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
 * @brief Giả lập cấu hình của mô-tơ
 **************************************************************************/
static MotorDriver_ConfigType MotorDriver_CurrentConfig;

/**************************************************************************
 * @brief 	Khởi tạo mô-tơ
 * @details	Hàm này được gọi để khởi tạo mô-tơ với cấu hình được truyền vào.
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình mô-tơ
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_MotorDriver_Init(const MotorDriver_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer passed to IoHwAb_MotorDriver_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình MotorDriver
    MotorDriver_CurrentConfig.Motor_Channel = ConfigPtr->Motor_Channel;
    MotorDriver_CurrentConfig.Motor_MaxTorque = ConfigPtr->Motor_MaxTorque;

    // Gọi API từ MCAL để khởi tạo PWM
    Pwm_ConfigType pwmConfig = {
        .Pwm_Channel = MotorDriver_CurrentConfig.Motor_Channel,
        .Pwm_Period = 1000, // 1 giây (1000ms)
        .Pwm_DutyCycle = 0  // Khởi tạo với duty cycle = 0%
    };
    Pwm_Init(&pwmConfig);

    // In ra thông tin cấu hình MotorDriver
    printf("Motor Driver Initialized with Configuration:\n");
    printf(" - Motor Channel: %d\n", MotorDriver_CurrentConfig.Motor_Channel);
    printf(" - Max Torque: %d Nm\n", MotorDriver_CurrentConfig.Motor_MaxTorque);

    return E_OK;
}

/**************************************************************************
 * @brief 	Điều chỉnh mô-men xoắn của mô-tơ
 * @details	Hàm này được gọi để điều chỉnh mô-men xoắn của mô-tơ.
 * @param   TorqueValue     Giá trị mô-men xoắn muốn điều chỉnh (Nm)
 * @return 	Std_ReturnType  Trả về E_OK nếu điều chỉnh thành công,
 *                                 E_NOT_OK nếu điều chỉnh không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_MotorDriver_SetTorque(float32 TorqueValue) {
    // Kiểm tra giá trị mô-men xoắn hợp lệ
    if (TorqueValue < 0.0f || TorqueValue > MotorDriver_CurrentConfig.Motor_MaxTorque) {
        printf("Error: Torque value %.2f Nm out of range (Max: %d Nm).\n", TorqueValue, MotorDriver_CurrentConfig.Motor_MaxTorque);
        return E_NOT_OK;
    }

    // Tính toán tỷ lệ nhiệm vụ (duty cycle) dựa trên mô-men xoắn
    uint16 dutyCycle = (uint16)((TorqueValue / MotorDriver_CurrentConfig.Motor_MaxTorque) * 100);

    // Gọi API từ MCAL để cài đặt duty cycle của PWM
    Pwm_SetDutyCycle(MotorDriver_CurrentConfig.Motor_Channel, dutyCycle);

    // In ra giá trị mô-men xoắn đã đặt
    printf("Setting Motor Torque to %.2f Nm on Channel %d\n", TorqueValue, MotorDriver_CurrentConfig.Motor_Channel);

    return E_OK;
}