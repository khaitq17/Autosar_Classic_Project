#ifndef DCM_H
#define DCM_H

#include <stdio.h>
#include <string.h>
#include "Std_Types.h"

/**************************************************************************
 * @brief Định nghĩa các dịch vụ chẩn đoán (Diagnostic Services)
 **************************************************************************/
#define DIAGNOSTIC_SESSION_CONTROL 0x10
#define ECU_RESET 0x11
#define READ_DTC 0x19
#define CLEAR_DTC 0x14

/**************************************************************************
 * @struct  Dcm_MessageType
 * @brief   Cấu trúc mô phỏng một gói tin chẩn đoán
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn một gói tin chẩn đoán
 *          bao gồm mã dịch vụ và dữ liệu kèm theo.
 **************************************************************************/
typedef struct {
    uint16 service_id;     /* Mã dịch vụ chẩn đoán */
    char data[50];      /* Dữ liệu kèm theo */
} Dcm_MessageType;

/**************************************************************************
 * @brief   Khởi tạo hệ thống DCM
 * @param   None
 * @return 	None  
 **************************************************************************/
void Dcm_Init(void);

/**************************************************************************
 * @brief   Xử lý yêu cầu chẩn đoán từ thiết bị kiểm tra
 * @param   request     Con trỏ đến cấu trúc mô phỏng gói tin chẩn đoán
 * @return 	None  
 **************************************************************************/
void Dcm_ProcessRequest(Dcm_MessageType* request);

/**************************************************************************
 * @brief   Gửi phản hồi chẩn đoán đến thiết bị kiểm tra
 * @param   service_id  Mã dịch vụ chẩn đoán
 * @param   response    Chuỗi phản hồi
 * @return 	None  
 **************************************************************************/
void Dcm_SendResponse(uint16 service_id, const char* response);

#endif /* DCM_H */ 