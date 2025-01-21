#ifndef PDU_ROUTER_H
#define PDU_ROUTER_H

#include <stdio.h>
#include <string.h>
#include "Std_Types.h"

/**************************************************************************
 * @brief Định nghĩa các giao thức truyền thông giả lập
 **************************************************************************/
#define PROTOCOL_CAN        0x01        /* Giao thức CAN */
#define PROTOCOL_LIN        0x02        /* Giao thức LIN */
#define PROTOCOL_ETHERNET   0x03        /* Giao thức Ethernet */

/**************************************************************************
 * @struct  Pdu_Type
 * @brief   Cấu trúc mô phỏng một PDU (Protocol Data Unit)
 * @details Kiểu dữ liệu này mô tả một PDU với các trường thông tin như
 *          giao thức truyền thông, dữ liệu và độ dài của dữ liệu.
 **************************************************************************/
typedef struct {
    uint8 protocol_id;  /* Giao thức của PDU (CAN, LIN, Ethernet, ...) */ 
    char data[50];    /* Dữ liệu của PDU */
    uint8 length;       /* Độ dài dữ liệu */
} Pdu_Type;

/**************************************************************************
 * @brief   Khởi tạo hệ thống PDU Router
 * @param   None
 * @return 	None  
 **************************************************************************/
void PduR_Init(void);

/**************************************************************************
 * @brief   Định tuyến PDU dựa trên giao thức
 * @param   pdu     Con trỏ đến PDU cần định tuyến
 * @return 	None  
 **************************************************************************/
void PduR_RoutePdu(Pdu_Type* pdu);

/**************************************************************************
 * @brief   Xử lý PDU cho giao thức CAN
 * @param   pdu     Con trỏ đến PDU cần xử lý
 * @return 	None  
 **************************************************************************/
void PduR_CanHandler(Pdu_Type* pdu);

/**************************************************************************
 * @brief   Xử lý PDU cho giao thức LIN
 * @details Hàm này được gọi để xử lý PDU với giao thức CAN.
 * @param   pdu     Con trỏ đến PDU cần xử lý
 * @return 	None  
 **************************************************************************/
void PduR_LinHandler(Pdu_Type* pdu);

/**************************************************************************
 * @brief   Xử lý PDU cho giao thức Ethernet
 * @param   pdu     Con trỏ đến PDU cần xử lý
 * @return 	None  
 **************************************************************************/
void PduR_EthernetHandler(Pdu_Type* pdu);

#endif /* PDU_ROUTER_H */ 