/***************************************************************************
 * @file    IoHwAb_LoadSensor.c
 * @brief   Định nghĩa các hàm giao diện cảm biến tải trọng
 * @details File này triển khai các hàm để tương tác với phần cứng cảm biến    
 *          tải trọng. Nó chứa định nghĩa các hàm để khởi tạo và đọc dữ liệu 
 *          cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IoHwAb_LoadSensor.h"
#include "Adc\Adc.h"    // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>

/**************************************************************************
 * @brief Giả lập cấu hình của cảm biến tải trọng
 **************************************************************************/
static LoadSensor_ConfigType LoadSensor_CurrentConfig;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tải trọng 
 * @details	Hàm này được gọi để khởi tạo cảm biến tải trọng với cấu hình 
 *          được truyền vào.
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến tải trọng
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_LoadSensor_Init(const LoadSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer passed to IoHwAb_LoadSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến tải trọng vào biến toàn cục
    LoadSensor_CurrentConfig.LoadSensor_Channel = ConfigPtr->LoadSensor_Channel;
    LoadSensor_CurrentConfig.LoadSensor_MaxValue = ConfigPtr->LoadSensor_MaxValue;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Channel = ConfigPtr->LoadSensor_Channel;
    Adc_Init(&adcConfig);

    // In ra thông tin cấu hình cảm biến tải trọng
    printf("Load Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", LoadSensor_CurrentConfig.LoadSensor_Channel);
    printf(" - Max Load Value: %d kg\n", LoadSensor_CurrentConfig.LoadSensor_MaxValue);
    return E_OK;
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tải trọng
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến tải trọng.
 * @param   LoadValue       Con trỏ lưu giá trị tải trọng đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_LoadSensor_Read(float32* LoadValue) {
    if (LoadValue == NULL_PTR) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị ADC từ MCAL
    uint16 adcValue = 0;
    if (Adc_ReadChannel(LoadSensor_CurrentConfig.LoadSensor_Channel, &adcValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang giá trị tải trọng (kg)
    *LoadValue = ((float32)adcValue / 1023.0f) * LoadSensor_CurrentConfig.LoadSensor_MaxValue;

    // In ra giá trị tải trọng
    printf("Load Sensor (ADC Channel %d): Load = %.2f kg\n",
            LoadSensor_CurrentConfig.LoadSensor_Channel, *LoadValue);

    return E_OK;
}