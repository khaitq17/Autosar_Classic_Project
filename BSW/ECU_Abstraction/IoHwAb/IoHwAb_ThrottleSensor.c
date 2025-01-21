/***************************************************************************
 * @file    IoHwAb_ThrottleSensor.c
 * @brief   Định nghĩa các hàm giao diện cảm biến bàn đạp ga
 * @details File này triển khai các hàm để tương tác với phần cứng cảm biến    
 *          bàn đạp ga. Nó chứa định nghĩa các hàm để khởi tạo và đọc dữ liệu 
 *          cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IoHwAb_ThrottleSensor.h"
#include "Adc\Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
 * @brief Định nghĩa phạm vi giá trị của cảm biến bàn đạp ga (giá trị thô)
 **************************************************************************/
#define THROTTLE_SENSOR_MIN_RAW_VALUE 0    /* Giá trị ADC tối thiểu */ 
#define THROTTLE_SENSOR_MAX_RAW_VALUE 1023 /* Giá trị ADC tối đa */

/**************************************************************************
 * @brief Định nghĩa phạm vi giá trị của bàn đạp ga sau khi chuyển đổi
 **************************************************************************/
#define THROTTLE_POSITION_MIN 0.0f  /* Bàn đạp ga hoàn toàn thả */
#define THROTTLE_POSITION_MAX 1.0f  /* Bàn đạp ga hoàn toàn nhấn */

/**************************************************************************
 * @brief Giả lập cấu hình của cảm biến bàn đạp ga
 **************************************************************************/
static ThrottleSensor_ConfigType ThrottleSensor_CurrentConfig;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp ga 
 * @details	Hàm này được gọi để khởi tạo cảm biến bàn đạp ga với cấu hình 
 *          được truyền vào.
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến bàn đạp ga
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_ThrottleSensor_Init(const ThrottleSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer passed to IoHwAb_ThrottleSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến bàn đạp ga vào biến toàn cục
    ThrottleSensor_CurrentConfig.ThrottleSensor_Channel = ConfigPtr->ThrottleSensor_Channel;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Channel = ThrottleSensor_CurrentConfig.ThrottleSensor_Channel;
   
    Adc_Init(&adcConfig);

    // Gọi API từ MCAL để khởi tạo DIO nếu cần
    //Dio_Init();

    // In ra thông tin cấu hình của cảm biến bàn đạp ga
    printf("Throttle Sensor Initialized with ADC Channel %d\n", ThrottleSensor_CurrentConfig.ThrottleSensor_Channel);

    return E_OK;
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp ga
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến bàn đạp ga.
 * @param   ThrottlePosition    Con trỏ lưu giá trị bàn đạp ga đọc được
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_ThrottleSensor_Read(float32* ThrottlePosition) {
    if (ThrottlePosition == NULL_PTR) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị ADC từ kênh cảm biến bàn đạp ga
    uint16 raw_adc_value = 0;
    if (Adc_ReadChannel(ThrottleSensor_CurrentConfig.ThrottleSensor_Channel, &raw_adc_value) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị thô của ADC sang phạm vi từ 0.0 đến 1.0
    *ThrottlePosition = ((float32)(raw_adc_value - THROTTLE_SENSOR_MIN_RAW_VALUE) / 
                        (THROTTLE_SENSOR_MAX_RAW_VALUE - THROTTLE_SENSOR_MIN_RAW_VALUE));

    // Đảm bảo giá trị nằm trong phạm vi từ 0.0 đến 1.0
    if (*ThrottlePosition < THROTTLE_POSITION_MIN) {
        *ThrottlePosition = THROTTLE_POSITION_MIN;
    } else if (*ThrottlePosition > THROTTLE_POSITION_MAX) {
        *ThrottlePosition = THROTTLE_POSITION_MAX;
    }

    // In ra giá trị bàn đạp ga sau khi chuyển đổi
    printf("Reading Throttle Sensor (ADC Channel %d): Throttle Position = %.2f\n",
           ThrottleSensor_CurrentConfig.ThrottleSensor_Channel, *ThrottlePosition);

    return E_OK;
}