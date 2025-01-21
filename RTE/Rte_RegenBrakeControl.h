/***************************************************************************
 * @file    Rte_RegenBrakeControl.h
 * @brief   Khai báo các hàm giao diện để điều khiển phanh tái sinh (Regenerative
 *          Braking Control) thông qua tầng I/O Hardware Abstraction
 * @details File này cung cấp giao diện các hàm liên quan trong hệ thống 
 *          cho phép điều khiển phanh tái sinh và trao đổi dữ liệu giữa 
 *          các tầng.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef RTE_REGENBRAKECONTROL_H
#define RTE_REGENBRAKECONTROL_H

#include "IoHwAb_BrakeSensor.h"         // API IoHwAb để đọc cảm biến bàn đạp phanh
#include "IoHwAb_SpeedSensor.h"         // API IoHwAb để đọc cảm biến tốc độ
#include "IoHwAb_LoadSensor.h"          // API IoHwAb để đọc cảm biến tải trọng
#include "IoHwAb_BatterySOC.h"          // API IoHwAb để đọc trạng thái pin
#include "IoHwAb_InclinationSensor.h"   // API IoHwAb để đọc cảm biến góc nghiêng
#include "Std_Types.h"  

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tốc độ
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Call_RpSpeedSensor_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tải trọng
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Call_RpLoadSensor_Init(void);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tốc độ
 * @param   Speed           Con trỏ lưu giá trị tốc độ đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Read_RpSpeedSensor_Speed(float32* Speed);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tải trọng
 * @param   LoadWeight      Con trỏ lưu giá trị tải trọng đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Read_RpLoadSensor_LoadWeight(float32* LoadWeight);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp phanh
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpBrakeSensor_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến cho sử dụng cho trạng thái pin
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_Rp_BatterySOC_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến góc nghiêng
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_Rp_InclinationSensor_Init(void);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp phanh
 * @param   BrakePosition   Con trỏ lưu giá trị bàn đạp phanh đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpBrakeSensor_BrakePosition(float32* BrakePosition);

/**************************************************************************
 * @brief 	Đọc giá trị từ các cảm biến sử dụng cho trạng thái pin SOC
 * @param   BatterySOC      Con trỏ lưu giá trị SOC đọc được 
 * @param   BatteryTemp     Con trỏ lưu giá trị nhiệt độ pin đọc được      
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpBatterySOC_BatterySOC(uint16* BatterySOC, float32* BatteryTemp);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến góc nghiêng
 * @param   Inclination      Con trỏ lưu giá trị góc nghiêng đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpInclinationSensor_Inclination(float32* Inclination);

#endif /* RTE_REGENBRAKECONTROL_H */