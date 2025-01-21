/***************************************************************************
 * @file    Main.c
 * @brief   Chương trình chính
 * @details File này chứa hàm chạy chương trình chính, nó sẽ khởi tạo hệ 
 *          điều hành và các task, in thông tin ra màn hình console.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Os.h"
#include "Torque_Control.h"
#include "Regen_Brake_Control.h"
#include "Traction_Control.h"
#include <stdio.h>

/**************************************************************************
 * @brief   Biến mutex để bảo vệ việc truy cập tài nguyên chia sẻ
 * @details Mutex được sử dụng để đồng bộ hóa việc truy cập vào tài nguyên 
 *          chia sẻ, đảm bảo các task không gây ra xung đột khi truy cập
 *          các phần dữ liệu chung hoặc khi in ra màn hình console.
 *          Mutex sẽ được khóa khi một task cần truy cập tài nguyên và sẽ 
 *          mở khóa khi không còn cần sử dụng tài nguyên nữa.
 **************************************************************************/
pthread_mutex_t mtx;

/**************************************************************************
 * @brief Các hàm task được sử dụng để khởi tạo và liên tục cập nhật các 
 *        hệ thống điều khiển.
 **************************************************************************/
void* Task_TorqueControl(); // Điều khiển mô-men xoắn
void* Task_RegenBrakeControl(); // Điều khiển phanh tái sinh
void* Task_TractionControl(); // Điều khiển lực kéo

/**************************************************************************
 * @brief   Hàm chạy chương trình chính
 * @details Trong chương trình chính sẽ khởi tạo hệ điều hành và các task,
 *          các task sẽ khởi tạo và cập nhật liên tục thông tin của các 
 *          hệ thống và in ra màn hình console.
 **************************************************************************/
int main() {
    /* Khởi tạo hệ điều hành */ 
    Os_Init();
    
    // Khởi tạo mutex
    pthread_mutex_init(&mtx, NULL_PTR);

    /* Tạo các task */  
    // Điều khiển mô-men xoắn
    Os_CreateTask(Task_TorqueControl, "Torque Control"); 

    // Điều khiển phanh tái sinh
    Os_CreateTask(Task_RegenBrakeControl, "Regenerative Braking Control"); 

    // Điều khiển lực kéo
    Os_CreateTask(Task_TractionControl, "Traction Control"); 

    /* Chờ các task hoàn thành */
    Os_Shutdown();
    
    // Hủy mutex khi không sử dụng nữa 
    pthread_mutex_destroy(&mtx);

    return 0;
}

/**************************************************************************
 * @brief   Task hệ thống điều khiển mô-men xoắn  
 * @details Hàm này sẽ khởi tạo và liên tục cập nhật các thông số cho hệ thống 
 *          điều khiển mô-men xoắn như trạng thái bàn đạp ga, tốc độ xe,
 *          tải trọng xe, mô-men xoắn của mô-tơ.  
 **************************************************************************/
void* Task_TorqueControl() {
    // Khóa mutex trước khi gọi hàm khởi tạo
    pthread_mutex_lock(&mtx);

    // Gọi hàm khởi tạo Torque Control
    TorqueControl_Init();

    // Mở khóa mutex sau khi khởi tạo xong
    pthread_mutex_unlock(&mtx);

    // Liên tục cập nhật hệ thống điều khiển mô-men xoắn
    while (1) {
        // Khóa mutex trước khi cập nhật
        pthread_mutex_lock(&mtx);

        TorqueControl_Update();

        // Mở khóa mutex trước sau cập nhật
        pthread_mutex_unlock(&mtx);

        // Tạm dừng 1 giây trước khi cập nhật tiếp
        Os_Delay(1000);
    }

    return NULL_PTR;
}

/**************************************************************************
 * @brief   Task hệ thống điều khiển phanh tái sinh 
 * @details Hàm này sẽ khởi tạo và liên tục cập nhật các thông số cho hệ thống 
 *          điều khiển phanh tái sinh như trạng thái bàn đạp phanh, tốc độ xe,
 *          tải trọng xe, góc nghiêng của xe so với mặt đất, trạng thái pin.
 **************************************************************************/
void* Task_RegenBrakeControl() {
    // Khóa mutex trước khi gọi hàm khởi tạo
    pthread_mutex_lock(&mtx);

    // Gọi hàm khởi tạo Regenerative Braking Control
    RegenBrakeControl_Init();

    // Mở khóa mutex sau khi khởi tạo xong
    pthread_mutex_unlock(&mtx);

    // Liên tục cập nhật hệ thống điều khiển phanh tái sinh
    while (1) {
        // Khóa mutex trước khi cập nhật
        pthread_mutex_lock(&mtx);

        RegenBrakeControl_Update();

        // Mở khóa mutex trước sau cập nhật
        pthread_mutex_unlock(&mtx);

        // Tạm dừng 1 giây trước khi cập nhật tiếp
        Os_Delay(1000);
    }

    return NULL_PTR;    
}

/**************************************************************************
 * @brief   Task hệ thống điều khiển phanh tái sinh 
 * @details Hàm này sẽ khởi tạo và liên tục cập nhật các thông số cho hệ thống 
 *          điều khiển phanh tái sinh như trạng thái bàn đạp ga, bàn đạp phanh, 
 *          tốc độ xe, vận tốc góc các bánh xe.
 **************************************************************************/
void* Task_TractionControl() {
    // Khóa mutex trước khi gọi hàm khởi tạo
    pthread_mutex_lock(&mtx);

    // Gọi hàm khởi tạo Traction Control
    TractionControl_Init();

    // Mở khóa mutex sau khi khởi tạo xong
    pthread_mutex_unlock(&mtx);

    // Liên tục cập nhật hệ thống điều khiển lực kéo
    while (1) {
        // Khóa mutex trước khi cập nhật
        pthread_mutex_lock(&mtx);

        TractionControl_Update();

        // Mở khóa mutex trước sau cập nhật
        pthread_mutex_unlock(&mtx);

        // Tạm dừng 1 giây trước khi cập nhật tiếp
        Os_Delay(1000);
    }

    return NULL_PTR;
}