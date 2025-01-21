/***************************************************************************
 * @file    Rte_TractionControl.c
 * @brief   Định nghĩa các hàm giao diện để điều khiển lực kéo
 * @details File này triển khai các hàm trong hệ thống cho phép điều khiển 
 *          lực kéo. Nó bao gồm các chức năng khởi tạo, đọc và ghi dữ liệu
 *          cho các module phần mềm như bàn đạp ga, bàn đạp phanh, tóc độ xe
 *          và tốc độ góc bánh xe.
 * @version 1.0
 * @date    2025-01-11
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Rte_TractionControl.h"

/**************************************************************************
 * @brief 	Khởi tạo cảm biến vận tốc góc
 * @details Hàm này được gọi để khởi tạo cảm biến vận tốc góc, thông qua  
 *          việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpWheelAngularVelSensor_Init() {
    // Cấu hình cho cảm biến vận tốc góc
    WheelAngularVel_ConfigType wheelAngularVelConfig[WHEEL_NUMBERS] = {
        {.WheelAngularVel_Channel = 8, .WheelAngularVel_MaxValue = 150}, // Bánh xe trước bên phải
        {.WheelAngularVel_Channel = 9, .WheelAngularVel_MaxValue = 150}, // Bánh xe trước bên trái
        {.WheelAngularVel_Channel = 10, .WheelAngularVel_MaxValue = 150}, // Bánh xe sau bên phải
        {.WheelAngularVel_Channel = 11, .WheelAngularVel_MaxValue = 150}, // Bánh xe sau bên trái
    };
    return IoHwAb_WheelAngularVel_Init(&wheelAngularVelConfig[0]);  // Gọi API từ IoHwAb để khởi tạo cảm biến vận tốc góc
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến vận tốc góc
 * @details Hàm này được gọi để đọc giá trị từ cảm biến vận tốc góc, thông 
 *          qua việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   AngularVel      Mảng lưu giá trị các cảm biến vận tốc góc       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpWheelAngularVelSensor_AngularVel(float32 AngularVel[WHEEL_NUMBERS]) {
    return IoHwAb_WheelAngularVel_Read(AngularVel); // Gọi API từ IoHwAb để đọc giá trị từ cảm biến vận tốc góc
}