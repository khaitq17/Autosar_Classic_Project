/***************************************************************************
 * @file    IoHwAb_BatterySOC.h
 * @brief   Khai báo các hàm giao diện cảm biến cho trạng thái pin
 * @details File này cung cấp giao diện để tương tác với phần cứng cảm biến     
 *          trạng thái pin (SOC) và nhiệt độ pin. Nó chứa cấu trúc cấu hình 
 *          và các hàm để khởi tạo và đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_BATTERYSOC_H
#define IOHWAB_BATTERYSOC_H

#include "Std_Types.h"

/**************************************************************************
 * @struct  BatterySOC_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho trạng thái pin SOC
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho 
 *          trạng thái pin SOC (State of Charge).
 **************************************************************************/
typedef struct {
    uint8 BatterySOC_Channel;       /* Kênh ADC để đọc giá trị từ cảm biến SOC */
    uint8 BatteryTemp_Channel;      /* Kênh ADC để đọc giá trị từ cảm biến nhiệt độ */
    uint16 BatteryTemp_MaxValue;    /* Giá trị nhiệt độ tối đa mà cảm biến có thể đọc */
} BatterySOC_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến trạng thái pin SOC
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến trạng thái pin
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_BatterySOC_Init(const BatterySOC_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến trạng thái pin SOC
 * @param   BatterySOCValue     Con trỏ lưu giá trị SOC đọc được   
 * @param   BatteryTempValue    Con trỏ lưu giá trị nhiệt độ pin đọc được
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_BatterySOC_Read(uint16* BatterySOCValue, float32* BatteryTempValue);

#endif /* IOHWAB_BATTERYSOC_H */