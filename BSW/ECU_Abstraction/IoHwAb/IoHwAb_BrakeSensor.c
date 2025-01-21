/***************************************************************************
 * @file    IoHwAb_BrakeSensor.c
 * @brief   Định nghĩa các hàm giao diện cảm biến trạng thái bàn đạp phanh
 * @details File này triển khai các hàm để tương tác với phần cứng cảm biến    
 *          trạng thái bàn đạp phanh. Nó chứa định nghĩa các hàm để khởi tạo
 *          và đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IoHwAb_BrakeSensor.h"
#include "Adc\Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
 * @brief Định nghĩa phạm vi giá trị của cảm biến bàn đạp phanh (giá trị thô)
 **************************************************************************/
#define BRAKE_SENSOR_MIN_RAW_VALUE 0    /* Giá trị ADC tối thiểu */ 
#define BRAKE_SENSOR_MAX_RAW_VALUE 1023 /* Giá trị ADC tối đa */

/**************************************************************************
 * @brief Định nghĩa phạm vi giá trị của bàn đạp phanh sau khi chuyển đổi
 **************************************************************************/
#define BRAKE_POSITION_MIN 0.0f  /* Bàn đạp phanh hoàn toàn thả */
#define BRAKE_POSITION_MAX 1.0f  /* Bàn đạp phanh hoàn toàn nhấn */

/**************************************************************************
 * @brief Giả lập cấu hình của cảm biến bàn đạp ga
 **************************************************************************/
static BrakeSensor_ConfigType BrakeSensor_CurrentConfig;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp phanh 
 * @details	Hàm này được gọi để khởi tạo cảm biến bàn đạp phanh với cấu hình 
 *          được truyền vào.
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến bàn đạp phanh
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_BrakeSensor_Init(const BrakeSensor_ConfigType *ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer passed to IoHwAb_BrakeSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cảm biến cấu bàn đạp phanh vào biến toàn cục
    BrakeSensor_CurrentConfig.BrakeSensor_Channel = ConfigPtr->BrakeSensor_Channel;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Channel = BrakeSensor_CurrentConfig.BrakeSensor_Channel;

    Adc_Init(&adcConfig);

    // Gọi API từ MCAL để khởi tạo DIO nếu cần
    //Dio_Init();

    // In ra thông tin cấu hình của cảm biến bàn đạp ga
    printf("Brake Sensor Initialized with ADC Channel %d\n", BrakeSensor_CurrentConfig.BrakeSensor_Channel);

    return E_OK;
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp phanh
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến bàn đạp phanh.
 * @param   BrakePosition    Con trỏ lưu giá trị bàn đạp phanh đọc được
 * @return 	Std_ReturnType   Trả về E_OK nếu đọc giá trị thành công,
 *                                  E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_BrakeSensor_Read(float32 *BrakePosition) {
    if (BrakePosition == NULL_PTR) {
        return E_NOT_OK;
    }

    // Đọc giá trị ADC từ cảm biến bàn đạp phanh
    uint16 raw_adc_value = 0;
    if (Adc_ReadChannel(BrakeSensor_CurrentConfig.BrakeSensor_Channel, &raw_adc_value) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị thô của ADC từ 0.0 đến 1.0
    *BrakePosition = ((float32)(raw_adc_value - BRAKE_SENSOR_MIN_RAW_VALUE) / 
                    (BRAKE_SENSOR_MAX_RAW_VALUE - BRAKE_SENSOR_MIN_RAW_VALUE));

    // Đảm bảo giá trị nằm trong phạm vi từ 0.0 đến 1.0
    if (*BrakePosition < BRAKE_POSITION_MIN) {
        *BrakePosition = BRAKE_POSITION_MIN;
    } else if (*BrakePosition > BRAKE_POSITION_MAX) {
        *BrakePosition = BRAKE_POSITION_MAX;
    }

    // In ra giá trị bàn đạp phanh sau khi chuyển đổi
    printf("Reading Brake Sensor (ADC Channel %d): Brake Position = %.2f\n",
            BrakeSensor_CurrentConfig.BrakeSensor_Channel, *BrakePosition);

    return E_OK;
}