#include "Pdu_Router.h"

/**************************************************************************
 * @brief   Khởi tạo hệ thống PDU Router
 * @details Hàm này được gọi để khởi tạo hệ thống PDU Router.
 * @param   None
 * @return 	None  
 **************************************************************************/
void PduR_Init() {
    printf("PDU Router Initialized.\n");
}

/**************************************************************************
 * @brief   Định tuyến PDU dựa trên giao thức
 * @details Hàm này sẽ định tuyến một PDU đến hàm xử lý tương ứng với giao 
 *          thức của PDU.
 * @param   pdu     Con trỏ đến PDU cần định tuyến
 * @return 	None  
 **************************************************************************/
void PduR_RoutePdu(Pdu_Type* pdu) {
    printf("Routing PDU: Protocol ID = 0x%x, Data = %s, Length = %d\n", pdu->protocol_id, pdu->data, pdu->length);

    switch (pdu->protocol_id) {
        case PROTOCOL_CAN:
            PduR_CanHandler(pdu);
            break;

        case PROTOCOL_LIN:
            PduR_LinHandler(pdu);
            break;

        case PROTOCOL_ETHERNET:
            PduR_EthernetHandler(pdu);
            break;

        default:
            printf("Unknown protocol ID: 0x%x\n", pdu->protocol_id);
            break;
    }
}

/**************************************************************************
 * @brief   Xử lý PDU cho giao thức CAN
 * @details Hàm này được gọi để xử lý PDU với giao thức CAN.
 * @param   pdu     Con trỏ đến PDU cần xử lý
 * @return 	None  
 **************************************************************************/
void PduR_CanHandler(Pdu_Type* pdu) {
    printf("Handling CAN PDU: Data = %s, Length = %d\n", pdu->data, pdu->length);
    // Xử lý dữ liệu theo giao thức CAN
}

/**************************************************************************
 * @brief   Xử lý PDU cho giao thức LIN
 * @details Hàm này được gọi để xử lý PDU với giao thức LIN.
 * @param   pdu     Con trỏ đến PDU cần xử lý
 * @return 	None  
 **************************************************************************/
void PduR_LinHandler(Pdu_Type* pdu) {
    printf("Handling LIN PDU: Data = %s, Length = %d\n", pdu->data, pdu->length);
    // Xử lý dữ liệu theo giao thức LIN
}

/**************************************************************************
 * @brief   Xử lý PDU cho giao thức Ethernet
 * @details Hàm này được gọi để xử lý PDU với giao thức Ethernet.
 * @param   pdu     Con trỏ đến PDU cần xử lý
 * @return 	None  
 **************************************************************************/
void PduR_EthernetHandler(Pdu_Type* pdu) {
    printf("Handling Ethernet PDU: Data = %s, Length = %d\n", pdu->data, pdu->length);
    // Xử lý dữ liệu theo giao thức Ethernet
}