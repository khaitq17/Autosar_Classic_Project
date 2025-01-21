/***************************************************************************
 * @file    Can.h
 * @brief   Khai báo giao diện điều khiển CAN (Controller Area Network)
 * @details File này cung cấp giao diện để điều khiển và sử dụng mạng CAN. 
 *          Nó chứa các kiểu dữ liệu định nghĩa, cấu trúc cấu hình và các hàm  
 *          liên quan đến CAN.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef CAN_H
#define CAN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Thư viện hỗ trợ hàm sleep (sử dụng cho delay)
#include "Std_Types.h"

/**************************************************************************
 * @typedef Can_IdType
 * @brief 	Định nghĩa kiểu dữ liệu cho ID của CAN message
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn ID của CAN message.
 *          Với CAN Standard 11-bit, ID có giá trị từ 0 đến 0x400007FF.
 *          Với CAN Extended 29-bit, ID có giá trị từ 0 đến 0xDFFFFFFF.
 **************************************************************************/
typedef uint32  Can_IdType;	

/**************************************************************************
 * @struct  Can_MessageType
 * @brief 	Định nghĩa cấu trúc mô phỏng một CAN message
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết cho một CAN message.
 **************************************************************************/
typedef struct {
    Can_IdType id;      /* ID của thông điệp CAN */ 
    uint8 data[8];      /* Dữ liệu CAN (tối đa 8 byte) */
    uint8 length;       /* Độ dài dữ liệu (tối đa 8 byte) */
} Can_MessageType;

/**************************************************************************
 * @brief   Khởi tạo CAN
 * @param   None
 * @return 	None  
 **************************************************************************/
void Can_Init(void);

/**************************************************************************
 * @brief   Gửi thông điệp CAN
 * @param   message     Con trỏ đến thông điệp CAN cần gửi
 * @return 	None  
 **************************************************************************/
void Can_SendMessage(Can_MessageType* message);

/**************************************************************************
 * @brief   Nhận thông điệp CAN
 * @details Hàm này nhận một thông điệp CAN (giả lập nhận ngẫu nhiên).
 * @param   None
 * @return 	Can_MessageType    Thông điệp CAN nhận được  
 **************************************************************************/
Can_MessageType Can_ReceiveMessage(void);

/**************************************************************************
 * @brief   Tạo độ trễ (delay)
 * @param   milliseconds    Thời gian độ trễ cần tạo (tính theo mili giây)
 * @return 	None  
 **************************************************************************/
void Can_Delay(uint32 milliseconds);

#endif /* CAN_H */ 