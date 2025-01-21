/***************************************************************************
 * @file    IoHwAb_BrakeSensor.h
 * @brief   Khai báo các hàm giao diện cảm biến trạng thái bàn đạp phanh
 * @details File này cung cấp giao diện để tương tác với phần cứng cảm biến     
 *          trạng thái bàn đạp phanh. Nó chứa cấu trúc cấu hình và các hàm 
 *          để khởi tạo và đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_BRAKESENSOR_H
#define IOHWAB_BRAKESENSOR_H

#include "Std_Types.h"

/**************************************************************************
 * @struct  BrakeSensor_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho cảm biến phanh
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho 
 *          cảm biến phanh (Brake Sensor).
 **************************************************************************/
typedef struct {
    uint8 BrakeSensor_Channel;   /* Kênh ADC để đọc giá trị từ cảm biến phanh */
} BrakeSensor_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp phanh
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến bàn đạp phanh
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_BrakeSensor_Init(const BrakeSensor_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp phanh
 * @param   BrakePosition    Con trỏ lưu giá trị bàn đạp phanh đọc được
 * @return 	Std_ReturnType   Trả về E_OK nếu đọc giá trị thành công,
 *                                  E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_BrakeSensor_Read(float32* BrakePosition);

#endif /* IOHWAB_BRAKESENSOR_H */