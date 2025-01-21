/***************************************************************************
 * @file    Can.c
 * @brief   Định nghĩa các hàm điều khiển CAN
 * @details File này triển khai các hàm để điều khiển và sử dụng mạng CAN.
 *          Nó bao gồm các chức năng khởi tạo, gửi và nhận thông điệp qua
 *          mạng CAN.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Can.h"

/**************************************************************************
 * @brief   Khởi tạo CAN
 * @details Hàm này được gọi để khởi tạo CAN.
 * @param   None
 * @return 	None  
 **************************************************************************/
void Can_Init() {
    printf("CAN Initialized.\n");
}

/**************************************************************************
 * @brief   Gửi thông điệp CAN
 * @details Hàm này gửi một thông điệp CAN, bao gồm ID, dữ liệu và độ dài 
 *          của dữ liệu.
 * @param   message     Con trỏ đến thông điệp CAN cần gửi
 * @return 	None  
 **************************************************************************/
void Can_SendMessage(Can_MessageType* message) {
    // Gọi hàm delay để mô phỏng thời gian gửi CAN
    Can_Delay(200);  // Tạo độ trễ 200ms để mô phỏng

    // In ra thông tin thông điệp được gửi
    printf("CAN Message Sent:\n");
    printf("ID: %d, Data Length: %d, Data: [", message->id, message->length);
    for (int i = 0; i < message->length; i++) {
        printf("%d", message->data[i]);
        if (i < message->length - 1) printf(", ");
    }
    printf("]\n");
}

/**************************************************************************
 * @brief   Nhận thông điệp CAN
 * @details Hàm này nhận một thông điệp CAN (giả lập nhận ngẫu nhiên).
 * @param   None
 * @return 	Can_MessageType    Thông điệp CAN nhận được  
 **************************************************************************/
Can_MessageType Can_ReceiveMessage() {
    Can_MessageType message;

    // Gọi hàm delay để mô phỏng thời gian nhận CAN
    Can_Delay(300);  // Tạo độ trễ 300ms để mô phỏng

    // Giả lập dữ liệu ngẫu nhiên cho thông điệp CAN
    message.id = rand() % 2048;  // Giả lập ID ngẫu nhiên từ 0 đến 2047 (CAN Standard 11-bit)
    message.length = rand() % 9; // Giả lập độ dài dữ liệu (0 - 8 byte)
    for (int i = 0; i < message.length; i++) {
        message.data[i] = rand() % 256;  // Giả lập dữ liệu ngẫu nhiên từ 0 đến 255 (0 - 8 byte)
    }

    // In ra thông tin thông điệp nhận được
    printf("CAN Message Received:\n");
    printf("ID: %d, Data Length: %d, Data: [", message.id, message.length);
    for (int i = 0; i < message.length; i++) {
        printf("%d", message.data[i]);
        if (i < message.length - 1) printf(", ");
    }
    printf("]\n");

    return message;
}

/**************************************************************************
 * @brief   Tạo độ trễ (delay)
 * @details Hàm này dùng để tạo độ trễ mô phỏng (tính theo milliseconds).
 * @param   milliseconds    Thời gian độ trễ cần tạo (tính theo mili giây)
 * @return 	None  
 **************************************************************************/
void Can_Delay(uint32 milliseconds) {
    usleep(milliseconds * 1000); // Hàm usleep tính theo micro giây, nhân với 1000 để thành mili giây
}