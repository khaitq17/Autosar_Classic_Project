/***************************************************************************
 * @file    IoHwAb_InclinationSensor.h
 * @brief   Khai báo các hàm giao diện cảm biến góc nghiêng xe (so với mặt đất) 
 * @details File này cung cấp giao diện để tương tác với phần cứng cảm biến     
 *          góc nghiêng. Nó chứa cấu trúc cấu hình và các hàm để khởi tạo và
 *          đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_INCLINATION_H
#define IOHWAB_INCLINATION_H

#include "Std_Types.h"

/**************************************************************************
 * @struct  InclinationSensor_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho cảm biến góc nghiêng
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho 
 *          cảm biến góc nghiêng.
 **************************************************************************/
typedef struct {
    uint8 InclinationSensor_Channel;      /* Kênh ADC để đọc giá trị từ cảm biến góc nghiêng */
    uint16 InclinationSensor_MaxValue;    /* Giá trị góc nghiêng tối đa mà cảm biến có thể đọc */
} InclinationSensor_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến góc nghiêng
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến góc nghiêng
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_InclinationSensor_Init(const InclinationSensor_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến góc nghiêng
 * @param   InclinationValue    Con trỏ lưu giá trị góc nghiêng đọc được
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_InclinationSensor_Read(float32* InclinationValue);

#endif /* IOHWAB_INCLINATION_H */