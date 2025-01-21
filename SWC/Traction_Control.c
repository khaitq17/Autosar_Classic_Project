/***************************************************************************
 * @file    Traction_Control.c
 * @brief   Định nghĩa các hàm giao diện để điều khiển lực kéo thông qua 
 *          tầng RTE
 * @details File này triển khai các hàm trong hệ thống cho phép điều khiển 
 *          lực kéo. Nó bao gồm các chức năng khởi tạo và cập nhật hệ thống
 *          điều khiển lực kéo với các module phần mềm liên quan.
 * @version 1.0
 * @date    2025-01-11
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Rte_TractionControl.h"   // Bao gồm interface của RTE cho Traction Control
#include "Traction_Control.h"
#include <stdio.h>
#include <math.h>

extern float32 throttle_input;      // Trạng thái bàn đạp ga
extern float32 brake_input;         // Trạng thái bàn đạp phanh
extern float32 current_speed;       // Tốc độ xe hiện tại (km/h)
float32 wheel_angular_vel[WHEEL_NUMBERS] = {0.0f};  // Vận tốc góc các bánh xe (rad/s)

/**************************************************************************
 * @brief 	Khởi tạo hệ thống điều khiển lực kéo
 * @details	Hàm này được gọi để khởi tạo hệ thống điều khiển lực kéo thông
 *          qua việc gọi các API từ RTE. 
 * @param   None
 * @return 	None
 **************************************************************************/
void TractionControl_Init() {
    Std_ReturnType status;

    printf("Initializing Traction Control system...\n");

    // // Khởi tạo cảm biến bàn đạp ga (nếu chưa khởi tạo)
    // status = Rte_Call_RpThrottleSensor_Init();
    // if (status == E_OK) {
    //     printf("Throttle sensor has been initialized successfully.\n");
    // } else {
    //     printf("Error initializing throttle sensor.\n");
    //     return;
    // }

    // // Khởi tạo cảm biến bàn đạp phanh (nếu chưa khởi tạo)
    // status = Rte_Call_RpBrakeSensor_Init();
    // if (status == E_OK) {
    //     printf("Brake sensor has been initialized successfully.\n");
    // } else {
    //     printf("Error initializing brake sensor.\n");
    //     return;
    // }

    // // Khởi tạo cảm biến tốc độ (nếu chưa khởi tạo)
    // status = Rte_Call_RpSpeedSensor_Init();
    // if (status == E_OK) {
    //     printf("Speed sensor has been initialized successfully.\n");
    // } else {
    //     printf("Error initializing speed sensor.\n");
    //     return;
    // }

    // Khởi tạo cảm biến vận tốc góc
    status = Rte_Call_RpWheelAngularVelSensor_Init();
    if (status == E_OK) {
        printf("Wheel angular velocity sensor has been initialized successfully.\n");
    } else {
        printf("Error initializing wheel angular velocity sensor.\n");
        return;
    }

    printf("The Traction Control system is ready.\n");
}

/**************************************************************************
 * @brief 	Cập nhật hệ thống điều khiển lực kéo
 * @details	Hàm này được gọi để cập nhật hệ thống điều khiển lực kéo thông
 *          qua việc gọi các API từ RTE. 
 * @param   None
 * @return 	None
 **************************************************************************/
void TractionControl_Update() {
    // Đọc dữ liệu từ cảm biến bàn đạp ga
    // if (Rte_Read_RpThrottleSensor_ThrottlePosition(&throttle_input) == E_OK) {
    //     printf("Throttle pedal value: %.2f%%\n", throttle_input * 100);
    // } else {
    //     printf("Error reading throttle sensor!\n");
    // }
    if (current_speed != -1.0f) {
        printf("Current vehicle speed: %.2f km/h\n", current_speed);
    } else {
        printf("Error reading speed sensor!\n");
    }

    // Đọc dữ liệu từ cảm biến bàn đạp phanh
    // if (Rte_Read_RpBrakeSensor_BrakePosition(&brake_input) == E_OK) {
    //     printf("Brake pedal value: %.2f%%\n", brake_input * 100);
    // } else {
    //     printf("Error reading throttle sensor!\n");
    // }
    if (brake_input != -1.0f) {
        printf("Brake pedal value: %.2f%%\n", brake_input * 100);
    } else {
        printf("Error reading throttle sensor!\n");
    }

    if (throttle_input > 0 && brake_input > 0) {
        printf("Warning: Accelerator and brake pedals pressed at the same time!\n");
    }

    // Đọc dữ liệu từ cảm biến tốc độ
    // if (Rte_Read_RpSpeedSensor_Speed(&current_speed) == E_OK) {
    //     printf("Current vehicle speed: %.2f km/h\n", current_speed);
    // } else {
    //     printf("Error reading speed sensor!\n");
    // }
    if (current_speed != -1.0f) {
        printf("Current vehicle speed: %.2f km/h\n", current_speed);
    } else {
        printf("Error reading speed sensor!\n");
    }

    // Đọc dữ liệu từ cảm biến vận tốc góc
    if (Rte_Read_RpWheelAngularVelSensor_AngularVel(wheel_angular_vel) == E_OK) {
        printf("Front right wheel angular velocity: %.2f rad/s\n", wheel_angular_vel[0]); // Bánh xe trước bên phải
        printf("Front left wheel angular velocity: %.2f rad/s\n", wheel_angular_vel[1]); // Bánh xe trước bên trái
        printf("Rear right wheel angular velocity: %.2f rad/s\n", wheel_angular_vel[2]); // Bánh xe sau bên phải
        printf("Rear left wheel angular velocity: %.2f rad/s\n", wheel_angular_vel[3]); // Bánh xe sau bên trái    
        // Thông tin các bánh xe khác nếu nhiều hơn 4 bánh xe    
    } else {
        printf("Error reading wheel angular velocity sensor!\n");
    }
    
    uint8 i;
    float32 slip_ratio = 0.0f;  // Độ trượt bánh xe
    float32 max_slip_ratio = 0.0f; // Độ trượt lớn nhất
    uint16 wheel_with_max_slip; // Bánh xe trượt nhiều nhất
    for (i = 0; i < WHEEL_NUMBERS; i++) {
        slip_ratio = (fabs((wheel_angular_vel[i] * (WHEEL_RADIUS)) - (current_speed / (3.6f)))) 
                    / (wheel_angular_vel[i] * (WHEEL_RADIUS));

        // Giới hạn độ trượt nằm trong phạm vi từ 0.0f đến 1.0f
        if (slip_ratio < 0) slip_ratio = 0.0f;
        if (slip_ratio > 1) slip_ratio = 1.0f;

        // Cập nhật độ trượt lớn nhất và bánh xe có độ trượt lớn nhất
        if (slip_ratio > max_slip_ratio) {
            max_slip_ratio = slip_ratio;
            wheel_with_max_slip = i;
        }
    }

    // Kiểm tra độ trượt và điều chỉnh  
    if (max_slip_ratio > BRAKE_THRESHOLD) {
        // Độ trượt quá lớn, tăng chân phanh
        brake_input *= 2.0f;  
        if (brake_input > 1.0f) brake_input = 1.0f;

        printf("High slip detected: %.2f, reducing throttle pedal to %.2f%%\n", 
                max_slip_ratio, brake_input * 100);

    } else if (max_slip_ratio > SLIP_THRESHOLD && max_slip_ratio < BRAKE_THRESHOLD) {
        // Giảm chân ga nếu độ trượt lớn
        throttle_input *= 0.5f;  
        printf("High slip detected: %.2f, reducing throttle pedal to %.2f%%\n", 
                max_slip_ratio, throttle_input * 100);
    }
    
    // Hoàn tất quá trình cập nhật 
    printf("Traction control system update completed!\n");                           
}