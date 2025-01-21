/***************************************************************************
 * @file    IoHwAb_SpeedSensor.c
 * @brief   Định nghĩa các hàm giao diện cảm biến tốc độ
 * @details File này triển khai các hàm để tương tác với phần cứng cảm biến    
 *          tốc độ. Nó chứa định nghĩa các hàm để khởi tạo và đọc dữ liệu 
 *          cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IoHwAb_SpeedSensor.h"
#include "Adc\Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
 * @brief Giả lập cấu hình của cảm biến tốc độ
 **************************************************************************/
static SpeedSensor_ConfigType SpeedSensor_CurrentConfig;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tốc độ 
 * @details	Hàm này được gọi để khởi tạo cảm biến tốc độ với cấu hình 
 *          được truyền vào.
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến tốc độ
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_SpeedSensor_Init(const SpeedSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer passed to IoHwAb_SpeedSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến tốc độ vào biến toàn cục
    SpeedSensor_CurrentConfig.SpeedSensor_Channel = ConfigPtr->SpeedSensor_Channel;
    SpeedSensor_CurrentConfig.SpeedSensor_MaxValue = ConfigPtr->SpeedSensor_MaxValue;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Channel = ConfigPtr->SpeedSensor_Channel;
    Adc_Init(&adcConfig);

    // In ra thông tin cấu hình cảm biến tốc độ
    printf("Speed Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", SpeedSensor_CurrentConfig.SpeedSensor_Channel);
    printf(" - Max Speed Value: %d km/h\n", SpeedSensor_CurrentConfig.SpeedSensor_MaxValue);

    return E_OK;
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tốc độ
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến tốc độ.
 * @param   SpeedValue      Con trỏ lưu giá trị tốc độ đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_SpeedSensor_Read(float32* SpeedValue) {
    if (SpeedValue == NULL_PTR) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị từ kênh ADC
    uint16 adcValue = 0;
    if (Adc_ReadChannel(SpeedSensor_CurrentConfig.SpeedSensor_Channel, &adcValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang tốc độ (giả lập)
    *SpeedValue = ((float32)adcValue / 1023.0f) * SpeedSensor_CurrentConfig.SpeedSensor_MaxValue;

    // In ra giá trị tốc độ
    printf("Reading Speed Sensor (ADC Channel %d): Speed = %.2f km/h\n",
           SpeedSensor_CurrentConfig.SpeedSensor_Channel, *SpeedValue);

    return E_OK;
}