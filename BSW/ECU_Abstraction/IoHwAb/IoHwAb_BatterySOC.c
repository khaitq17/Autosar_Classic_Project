/***************************************************************************
 * @file    IoHwAb_BatterySOC.c
 * @brief   Định nghĩa các hàm giao diện cảm biến cho trạng thái pin
 * @details File này triển khai các hàm để tương tác với phần cứng cảm biến    
 *          trạng thái pin (SOC) và cảm biến nhiệt độ pin. Nó chứa định nghĩa 
 *          các hàm để khởi tạo và đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IoHwAb_BatterySOC.h"
#include "Adc\Adc.h"   // Gọi API từ MCAL để đọc giá trị từ ADC
#include "Dio.h"   // Gọi API từ MCAL để kiểm tra trạng thái DIO nếu cần
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
 * @brief Định nghĩa phạm vi giá trị của cảm biến đọc từ ADC (giá trị thô)
 **************************************************************************/
#define BATTERY_SENSOR_MIN_RAW_VALUE 0      /* Giá trị ADC tối thiểu */ 
#define BATTERY_SENSOR_MAX_RAW_VALUE 1023   /* Giá trị ADC tối đa */

/**************************************************************************
 * @brief Định nghĩa phạm vi giá trị SOC sau khi chuyển đổi
 **************************************************************************/
#define SOC_VALUE_MIN 0      /* Trạng thái hết pin */
#define SOC_VALUE_MAX 100    /* Trạng thái đầy pin */

/**************************************************************************
 * @brief Giả lập cấu hình của cảm biến trạng thái pin SOC
 **************************************************************************/
static BatterySOC_ConfigType BatterySOC_CurrentConfig;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến trạng thái pin SOC
 * @details	Hàm này được gọi để khởi tạo cảm biến trạng thái pin với cấu hình 
 *          được truyền vào.
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến trạng thái pin
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_BatterySOC_Init(const BatterySOC_ConfigType *ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer passed to IoHwAb_BatterySOC_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến trạng thái pin vào biến toàn cục
    BatterySOC_CurrentConfig.BatterySOC_Channel = ConfigPtr->BatterySOC_Channel;
    BatterySOC_CurrentConfig.BatteryTemp_Channel = ConfigPtr->BatteryTemp_Channel;
    BatterySOC_CurrentConfig.BatteryTemp_MaxValue = ConfigPtr->BatteryTemp_MaxValue;

    // Gọi API từ MCAL để khởi tạo 2 kênh ADC cho SOC và nhiệt độ
    Adc_ConfigType adcSOC_Config;
    adcSOC_Config.Channel = BatterySOC_CurrentConfig.BatterySOC_Channel;
    Adc_Init(&adcSOC_Config);

    Adc_ConfigType adcTemp_Config;
    adcTemp_Config.Channel = BatterySOC_CurrentConfig.BatteryTemp_Channel;
    Adc_Init(&adcTemp_Config);
    
    // In ra thông tin cấu hình của cảm biến trạng thái pin SOC
    printf("Battery SOC Sensor Initialized with ADC Channel %d\n", BatterySOC_CurrentConfig.BatterySOC_Channel);
    printf("Battery Temperature Sensor Initialized with ADC Channel %d\n", BatterySOC_CurrentConfig.BatteryTemp_Channel);
    printf("Battery Temperature Max Value: %d\u00b0C\n", BatterySOC_CurrentConfig.BatteryTemp_MaxValue);

    return E_OK;
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến trạng thái pin SOC
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến trạng thái pin SOC, 
 *          bao gồm giá trị SOC và nhiệt độ pin.
 * @param   BatterySOCValue     Con trỏ lưu giá trị SOC đọc được   
 * @param   BatteryTempValue    Con trỏ lưu giá trị nhiệt độ pin đọc được
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_BatterySOC_Read(uint16 *BatterySOCValue, float32 *BatteryTempValue) {
    if (BatterySOCValue == NULL_PTR || BatteryTempValue == NULL_PTR) {
        printf("Error: Null pointer passed to IoHwAb_BatterySOC_Read.\n");
        return E_NOT_OK;
    }

    // Đọc giá trị từ cảm biến trạng thái pin SOC
    uint16 batterySOC_adc_value;
    if (Adc_ReadChannel(BatterySOC_CurrentConfig.BatterySOC_Channel, &batterySOC_adc_value) == E_NOT_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang giá trị SOC
    *BatterySOCValue = ((uint16)batterySOC_adc_value - BATTERY_SENSOR_MIN_RAW_VALUE) / 
                        (BATTERY_SENSOR_MAX_RAW_VALUE - BATTERY_SENSOR_MIN_RAW_VALUE) * (SOC_VALUE_MAX - SOC_VALUE_MIN);

    // Đảm bảo giá trị SOC nằm trong phạm vi từ 0.0f đến 100.0f
    if (*BatterySOCValue < SOC_VALUE_MIN) {
        *BatterySOCValue = SOC_VALUE_MIN;
    } else if (*BatterySOCValue > SOC_VALUE_MAX) {
        *BatterySOCValue = SOC_VALUE_MAX;
    }

    // In ra giá trị SOC sau khi chuyển đổi
    printf("Reading Battery SOC Sensor (ADC Channel %d): SOC = %d%%\n",
            BatterySOC_CurrentConfig.BatterySOC_Channel, *BatterySOCValue);

    // Đọc giá trị từ cảm biến nhiệt độ
    uint16 batteryTemp_adc_value;
    if (Adc_ReadChannel(BatterySOC_CurrentConfig.BatteryTemp_Channel, &batteryTemp_adc_value) == E_NOT_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang giá trị nhiệt độ
    *BatteryTempValue = ((float32)batteryTemp_adc_value / BATTERY_SENSOR_MAX_RAW_VALUE) * 
                        BatterySOC_CurrentConfig.BatteryTemp_MaxValue;

    float32 Celsius_To_Fahrenheit = (*BatteryTempValue * 9.0f / 5.0f) + 32.0f;

    // In ra giá trị nhiệt độ sau khi chuyển đổi
    printf("Reading Battery Temperature Sensor (ADC Channel %d): Temperature = %.2f\u00b0C (%.2f\u00b0F)\n",
            BatterySOC_CurrentConfig.BatteryTemp_Channel, *BatteryTempValue, Celsius_To_Fahrenheit);

    return E_OK;
}