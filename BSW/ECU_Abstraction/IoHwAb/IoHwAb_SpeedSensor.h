/***************************************************************************
 * @file    IoHwAb_SpeedSensor.h
 * @brief   Khai báo các hàm giao diện cảm biến tốc độ xe
 * @details File này cung cấp giao diện để tương tác với phần cứng cảm biến     
 *          tốc độ. Nó chứa cấu trúc cấu hình và các hàm để khởi tạo và đọc
 *          dữ liệu cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_SPEEDSENSOR_H
#define IOHWAB_SPEEDSENSOR_H

#include "Std_Types.h"

/**************************************************************************
 * @struct  SpeedSensor_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho cảm biến tốc độ
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho
 *          cảm biến tốc độ (Speed Sensor).
 **************************************************************************/
typedef struct {
    uint8 SpeedSensor_Channel;   /* Kênh ADC để đọc giá trị từ cảm biến tốc độ */
    uint16 SpeedSensor_MaxValue; /* Giá trị tốc độ tối đa mà cảm biến có thể đọc (km/h) */
} SpeedSensor_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tốc độ
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến tốc độ
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_SpeedSensor_Init(const SpeedSensor_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tốc độ
 * @param   SpeedValue      Con trỏ trỏ đến giá trị tốc độ đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_SpeedSensor_Read(float32* SpeedValue);

#endif /* IOHWAB_SPEEDSENSOR_H */