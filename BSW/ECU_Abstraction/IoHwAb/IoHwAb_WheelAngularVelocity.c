/***************************************************************************
 * @file    IoHwAb_WheelAngularVelocity.c
 * @brief   Định nghĩa các hàm giao diện cảm biến vận tốc góc bánh xe
 * @details File này triển khai các hàm để tương tác với phần cứng cảm biến    
 *          vận tốc góc bánh xe. Nó chứa định nghĩa các hàm để khởi tạo và   
 *          đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IoHwAb_WheelAngularVelocity.h"
#include "Adc\Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
 * @brief Giả lập cấu hình của cảm biến vận tốc góc cho tất cả các bánh xe
 **************************************************************************/
static WheelAngularVel_ConfigType WheelAngularVel_CurrentConfig[WHEEL_NUMBERS];

/**************************************************************************
 * @brief 	Khởi tạo cảm biến vận tốc góc góc bánh xe
 * @details Hàm này được gọi để khởi tạo cảm biến vận tốc góc với cấu hình 
 *          được truyền vào.
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến vận tốc góc
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_WheelAngularVel_Init(const WheelAngularVel_ConfigType ConfigPtr[WHEEL_NUMBERS]) {
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer passed to IoHwAb_WheelAngularVel_Init.\n");
        return E_NOT_OK;
    }

    uint8 i;

    // Lưu cấu hình cảm biến vận tốc vào biến toàn cục
    for (i = 0; i < WHEEL_NUMBERS; i++) {
        WheelAngularVel_CurrentConfig[i].WheelAngularVel_Channel = ConfigPtr[i].WheelAngularVel_Channel;
        WheelAngularVel_CurrentConfig[i].WheelAngularVel_MaxValue = ConfigPtr[i].WheelAngularVel_MaxValue;
    }

    // Gọi API từ MCAL để khởi tạo ADC cho các cảm biến vận tốc góc
    Adc_ConfigType adcConfig[4];
    for (i = 0; i < WHEEL_NUMBERS; i++){
        adcConfig[i].Channel = ConfigPtr[i].WheelAngularVel_Channel;
        Adc_Init(&adcConfig[i]);
    }
    
    // In ra thông tin cấu hình cảm biến vận tốc góc
    printf("Wheel Angular Velocity Sensor Initialized with Configuration:\n");
    for (i = 0; i < WHEEL_NUMBERS; i++) {
        printf(" - ADC Channel: %d, Max Speed Value: %d rad/s\n", 
                WheelAngularVel_CurrentConfig[i].WheelAngularVel_Channel, 
                WheelAngularVel_CurrentConfig[i].WheelAngularVel_MaxValue);
    }
    
    return E_OK;
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến vận tốc góc
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến vận tốc góc.
 * @param   AngularVelocity Mảng lưu giá trị các vận tốc góc đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_WheelAngularVel_Read(float32 AngularVelocity[WHEEL_NUMBERS]) {
    uint8 i;

    // Đọc giá trị từ kênh ADC
    uint16 adcValue[WHEEL_NUMBERS] = {0};
    for (i = 0; i < WHEEL_NUMBERS; i++) {
        if (Adc_ReadChannel(WheelAngularVel_CurrentConfig[i].WheelAngularVel_Channel, &adcValue[i]) != E_OK) {
            printf("Error: Failed to read ADC value in channel %d.\n", 
                    WheelAngularVel_CurrentConfig[i].WheelAngularVel_Channel);
            return E_NOT_OK;
        }  
    }

    // Chuyển đổi giá trị ADC sang vận tốc góc (giả lập)
    for (i = 0; i < WHEEL_NUMBERS; i++) {
        AngularVelocity[i] = ((float32)adcValue[i] / 1023.0f) * WheelAngularVel_CurrentConfig->WheelAngularVel_MaxValue; 
    }

    // In ra giá trị vận tốc góc
    for (i = 0; i < WHEEL_NUMBERS; i++) {
        printf("Reading Angular Velocity Sensor (ADC Channel %d): Angular velocity = %.2f rad/s\n",
                WheelAngularVel_CurrentConfig[i].WheelAngularVel_Channel, AngularVelocity[i]);
    }
    
    return E_OK;   
}