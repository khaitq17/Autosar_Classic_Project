/***************************************************************************
 * @file    IoHwAb_InclinationSensor.c
 * @brief   Định nghĩa các hàm giao diện cảm biến góc nghiêng
 * @details File này triển khai các hàm để tương tác với phần cứng cảm biến    
 *          góc nghiêng. Nó chứa định nghĩa các hàm để khởi tạo và đọc dữ liệu 
 *          cảm biến.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IoHwAb_InclinationSensor.h"
#include "Adc\Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
 * @brief Giả lập cấu hình của cảm biến góc nghiêng
 **************************************************************************/
static InclinationSensor_ConfigType InclinationSensor_CurrentConfig;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến góc nghiêng 
 * @details	Hàm này được gọi để khởi tạo cảm biến góc nghiêng với cấu hình 
 *          được truyền vào.
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến góc nghiêng
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_InclinationSensor_Init(const InclinationSensor_ConfigType *ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer passed to IoHwAb_Inclination_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến góc nghiêng vào biến toàn cục
    InclinationSensor_CurrentConfig.InclinationSensor_Channel = ConfigPtr->InclinationSensor_Channel;
    InclinationSensor_CurrentConfig.InclinationSensor_MaxValue = ConfigPtr->InclinationSensor_MaxValue;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Channel = InclinationSensor_CurrentConfig.InclinationSensor_Channel;

    Adc_Init(&adcConfig);

    // In ra thông tin cấu hình của cảm biến góc nghiêng
    printf("Inclination Sensor Initialized with ADC Channel %d\n", 
            InclinationSensor_CurrentConfig.InclinationSensor_Channel);

    return E_OK;
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến góc nghiêng
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến góc nghiêng.
 * @param   InclinationValue    Con trỏ lưu giá trị góc nghiêng đọc được
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_InclinationSensor_Read(float32 *InclinationValue) {
    if (InclinationValue == NULL_PTR) {
        return E_NOT_OK;
    }

    // Đọc giá trị ADC từ cảm biến góc nghiêng
    uint16 adcValue = 0;
    if (Adc_ReadChannel(InclinationSensor_CurrentConfig.InclinationSensor_Channel, &adcValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang giá trị góc nghiêng (độ)
    *InclinationValue = ((float32)adcValue / 1023.0f) * InclinationSensor_CurrentConfig.InclinationSensor_MaxValue;

    // In ra giá trị góc nghiêng đọc được
    printf("Inclination Sensor (ADC Channel %d): Inclination = %.2f\u00b0C\n",
            InclinationSensor_CurrentConfig.InclinationSensor_Channel, *InclinationValue);

    return E_OK;
}