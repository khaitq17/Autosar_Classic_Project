/***************************************************************************
 * @file    IoHwAb_LoadSensor.h
 * @brief   Khai báo các hàm giao diện cảm biến tải trọng xe
 * @details File này cung cấp giao diện để tương tác với phần cứng cảm biến     
 *          tải trọng. Nó chứa cấu trúc cấu hình và các hàm để khởi tạo và 
 *          đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_LOADSENSOR_H
#define IOHWAB_LOADSENSOR_H

#include "Std_Types.h"

/**************************************************************************
 * @struct  LoadSensor_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho cảm biến tải trọng
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho 
 *          cảm biến tải trọng (Load Sensor).
 **************************************************************************/
typedef struct {
    uint8 LoadSensor_Channel;   /* Kênh ADC để đọc giá trị từ cảm biến */
    uint16 LoadSensor_MaxValue; /* Giá trị tải trọng tối đa mà cảm biến có thể đọc */
} LoadSensor_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tải trọng 
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến tải trọng
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_LoadSensor_Init(const LoadSensor_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tải trọng
 * @param   LoadValue       Con trỏ trỏ đến giá trị tải trọng đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_LoadSensor_Read(float32* LoadValue);

#endif /* IOHWAB_LOADSENSOR_H */