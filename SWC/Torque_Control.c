/***************************************************************************
 * @file    Torque_Control.c
 * @brief   Định nghĩa các hàm giao diện để điều khiển mô-men xoắn thông qua 
 *          tầng RTE
 * @details File này triển khai các hàm trong hệ thống cho phép điều khiển 
 *          mô-men xoắn. Nó bao gồm các chức năng khởi tạo và cập nhật hệ thống
 *          điều khiển mô-men xoắn với các module phần mềm liên quan.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Rte_TorqueControl.h"   // Bao gồm interface của RTE cho Torque Control
#include "Torque_Control.h"
#include <stdio.h>  

float32 throttle_input = 0.0f;  // Trạng thái bàn đạp ga
float32 current_speed = 0.0f;   // Tốc độ xe hiện tại (km/h)
float32 load_weight = 0.0f;     // Tải trọng của xe (kg)
float32 actual_torque = 0.0f;   // Mô-men xoắn thực tế (Nm)
float32 desired_torque = 0.0f;  // Mô-men xoắn yêu cầu (Nm)

/**************************************************************************
 * @brief 	Khởi tạo hệ thống điều khiển mô-men xoắn  
 * @details	Hàm này được gọi để khởi tạo hệ thống điều khiển mô-men xoắn,
 *          thông qua việc gọi các API từ RTE. 
 * @param   None
 * @return 	None
 **************************************************************************/
void TorqueControl_Init() {
    // Khởi tạo các cảm biến bàn đạp ga, tốc độ và tải trọng
    Std_ReturnType status;

    printf("Initializing Torque Control system...\n");

    // Khởi tạo cảm biến bàn đạp ga
    status = Rte_Call_RpThrottleSensor_Init();
    if (status == E_OK) {
        printf("Throttle sensor has been initialized successfully.\n");
    } else {
        printf("Error initializing throttle sensor.\n");
        throttle_input = -1.0f;
        return;
    }

    // Khởi tạo cảm biến tốc độ
    status = Rte_Call_RpSpeedSensor_Init();
    if (status == E_OK) {
        printf("Speed sensor has been initialized successfully.\n");
    } else {
        printf("Error initializing speed sensor.\n");
        current_speed = -1.0f;
        return;
    }

    // Khởi tạo cảm biến tải trọng
    status = Rte_Call_RpLoadSensor_Init();
    if (status == E_OK) {
        printf("Load sensor has been initialized successfully.\n");
    } else {
        printf("Error initializing load sensor.\n");
        load_weight = -1.0f;
        return;
    }

    // Khởi tạo cảm biến mô-men xoắn thực tế
    status = Rte_Call_RpTorqueSensor_Init();
    if (status == E_OK) {
        printf("Torque sensor has been initialized successfully.\n");
    } else {
        printf("Error initializing torque sensor.\n");
        return;
    }

    // Khởi tạo bộ điều khiển mô-men xoắn (có thể là PWM hoặc module điều khiển động cơ)
    status = Rte_Call_PpMotorDriver_Init();
    if (status == E_OK) {
        printf("Motor driver has been initialized successfully.\n");
    } else {
        printf("Error initializing motor driver.\n");
        return;
    }

    printf("The Torque Control system is ready.\n");
}

/**************************************************************************
 * @brief 	Cập nhật hệ thống điều khiển mô-men xoắn  
 * @details	Hàm này được gọi để cập nhật hệ thống điều khiển mô-men xoắn,
 *          thông qua việc gọi các API từ RTE. 
 * @param   None
 * @return 	None
 **************************************************************************/
void TorqueControl_Update() {
    // Đọc dữ liệu từ cảm biến bàn đạp ga
    if (Rte_Read_RpThrottleSensor_ThrottlePosition(&throttle_input) == E_OK) {
        printf("Throttle pedal value: %.2f%%\n", throttle_input * 100);
    } else {
        printf("Error reading throttle sensor!\n");
        throttle_input = -1.0f;
    }

    // Đọc dữ liệu từ cảm biến tốc độ
    if (Rte_Read_RpSpeedSensor_Speed(&current_speed) == E_OK) {
        printf("Current vehicle speed: %.2f km/h\n", current_speed);
    } else {
        printf("Error reading speed sensor!\n");
        current_speed = -1.0f;
    }

    // Đọc dữ liệu từ cảm biến tải trọng
    if (Rte_Read_RpLoadSensor_LoadWeight(&load_weight) == E_OK) {
        printf("Current load weight: %.2f kg\n", load_weight);
    } else {
        printf("Error reading load sensor!\n");
        load_weight = -1.0f;
    }

    // Tính toán mô-men xoắn yêu cầu
    desired_torque = throttle_input * MAX_TORQUE;
    if (current_speed > 50.0f) {
        desired_torque *= 0.8f;  // Giảm mô-men xoắn nếu tốc độ cao
    }
    if (load_weight > 500.0f) {
        desired_torque += 10.0f;  // Tăng mô-men xoắn nếu tải trọng lớn
    }

    // Giới hạn mô-men xoắn trong phạm vi an toàn
    if (desired_torque > MAX_TORQUE) {
        desired_torque = MAX_TORQUE;
    } else if (desired_torque < MIN_TORQUE) {
        desired_torque = MIN_TORQUE;
    }

    // In ra mô-men xoắn yêu cầu
    printf("Desired torque: %.2f Nm\n", desired_torque);

    // Ghi mô-men xoắn yêu cầu tới bộ điều khiển động cơ
    if (Rte_Write_PpMotorDriver_SetTorque(desired_torque) == E_OK) {
        printf("Desired torque has been sent to the motor.\n");
    } else {
        printf("Error sending torque to the motor!\n");
    }

    // Đọc mô-men xoắn thực tế để so sánh với mô-men xoắn yêu cầu
    if (Rte_Read_RpTorqueSensor_ActualTorque(&actual_torque) == E_OK) {
        printf("Actual torque: %.2f Nm\n", actual_torque);
    } else {
        printf("Error reading actual torque!\n");
    }

    // So sánh và điều chỉnh nếu có sự sai lệch giữa mô-men xoắn thực tế và yêu cầu
    if (actual_torque < desired_torque) {
        printf("Increase torque to reach the desired torque.\n");
    } else if (actual_torque > desired_torque) {
        printf("Decrease torque to reach the desired torque.\n");
    }

    // Hoàn tất quá trình cập nhật 
    printf("Torque control system update completed!\n");
}