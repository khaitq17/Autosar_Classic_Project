/***************************************************************************
 * @file    Dio.h
 * @brief   Khai báo giao diện điều khiển DIO (Digital Input/Output)
 * @details File này cung cấp giao diện để điều khiển và sử dụng DIO của
 *          của vi điều khiển. Nó chứa các kiểu dữ liệu định nghĩa, cấu trúc
 *          cấu hình và các hàm liên quan đến DIO.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef DIO_H
#define DIO_H

#include <stdio.h>
#include <stdlib.h>  // Thư viện hỗ trợ tạo giá trị ngẫu nhiên
#include <time.h>    // Thư viện hỗ trợ thời gian (sử dụng cho random)
#include <unistd.h>  // Thư viện hỗ trợ hàm sleep (sử dụng cho delay)
#include "Std_Types.h"

/**************************************************************************
 * @typedef Dio_ChannelType
 * @brief 	Định nghĩa kiểu dữ liệu cho kênh DIO
 * @details Kiểu dữ liệu này được sử dụng cho tất cả các kênh DIO.
 **************************************************************************/
typedef uint8   Dio_ChannelType;
#define DIO_CHANNEL_A0 		(Dio_ChannelType)0 		/* GPIOA Pin 0 */
#define DIO_CHANNEL_A1 		(Dio_ChannelType)1 		/* GPIOA Pin 1 */
#define DIO_CHANNEL_A2 		(Dio_ChannelType)2 		/* GPIOA Pin 2 */
#define DIO_CHANNEL_A3 		(Dio_ChannelType)3 		/* GPIOA Pin 3 */
#define DIO_CHANNEL_A4 		(Dio_ChannelType)4 		/* GPIOA Pin 4 */
#define DIO_CHANNEL_A5 		(Dio_ChannelType)5 		/* GPIOA Pin 5 */
#define DIO_CHANNEL_A6 		(Dio_ChannelType)6 		/* GPIOA Pin 6 */
#define DIO_CHANNEL_A7 		(Dio_ChannelType)7 		/* GPIOA Pin 7 */
#define DIO_CHANNEL_A8 		(Dio_ChannelType)8 		/* GPIOA Pin 8 */
#define DIO_CHANNEL_A9 		(Dio_ChannelType)9 		/* GPIOA Pin 9 */
#define DIO_CHANNEL_A10		(Dio_ChannelType)10		/* GPIOA Pin 10 */
#define DIO_CHANNEL_A11		(Dio_ChannelType)11		/* GPIOA Pin 11 */
#define DIO_CHANNEL_A12		(Dio_ChannelType)12		/* GPIOA Pin 12 */
#define DIO_CHANNEL_A13		(Dio_ChannelType)13		/* GPIOA Pin 13 */
#define DIO_CHANNEL_A14		(Dio_ChannelType)14		/* GPIOA Pin 14 */
#define DIO_CHANNEL_A15		(Dio_ChannelType)15		/* GPIOA Pin 15 */

#define DIO_CHANNEL_B0  	(Dio_ChannelType)16    	/* GPIOB Pin 0 */
#define DIO_CHANNEL_B1  	(Dio_ChannelType)17   	/* GPIOB Pin 1 */
#define DIO_CHANNEL_B2  	(Dio_ChannelType)18   	/* GPIOB Pin 2 */
#define DIO_CHANNEL_B3  	(Dio_ChannelType)19    	/* GPIOB Pin 3 */
#define DIO_CHANNEL_B4  	(Dio_ChannelType)20    	/* GPIOB Pin 4 */
#define DIO_CHANNEL_B5  	(Dio_ChannelType)21    	/* GPIOB Pin 5 */
#define DIO_CHANNEL_B6  	(Dio_ChannelType)22    	/* GPIOB Pin 6 */
#define DIO_CHANNEL_B7  	(Dio_ChannelType)23    	/* GPIOB Pin 7 */
#define DIO_CHANNEL_B8  	(Dio_ChannelType)24    	/* GPIOB Pin 8 */
#define DIO_CHANNEL_B9  	(Dio_ChannelType)25    	/* GPIOB Pin 9 */
#define DIO_CHANNEL_B10 	(Dio_ChannelType)26   	/* GPIOB Pin 10 */
#define DIO_CHANNEL_B11 	(Dio_ChannelType)27   	/* GPIOB Pin 11 */
#define DIO_CHANNEL_B12 	(Dio_ChannelType)28   	/* GPIOB Pin 12 */
#define DIO_CHANNEL_B13 	(Dio_ChannelType)29   	/* GPIOB Pin 13 */
#define DIO_CHANNEL_B14		(Dio_ChannelType)30   	/* GPIOB Pin 14 */
#define DIO_CHANNEL_B15 	(Dio_ChannelType)31   	/* GPIOB Pin 15 */
// Tương tự cho các chân DIO khác 

/**************************************************************************
 * @typedef Dio_PortType
 * @brief 	Định nghĩa kiểu dữ liệu cho cổng DIO
 * @details Kiểu dữ liệu này được sử dụng cho tất cả các cổng DIO.
 **************************************************************************/
typedef uint16  Dio_PortType;
#define DIO_PORT_A		(Dio_PortType)0		/* GPIOA */
#define DIO_PORT_B		(Dio_PortType)1		/* GPIOB */
#define DIO_PORT_C		(Dio_PortType)2		/* GPIOC */
#define DIO_PORT_D		(Dio_PortType)3		/* GPIOD */
// Các cổng DIO khác (nếu có)

/**************************************************************************
 * @typedef Dio_LevelType
 * @brief 	Định nghĩa kiểu dữ liệu cho trạng thái của kênh DIO
 * @details Kiểu dữ liệu này để biểu diễn trạng thái của kênh DIO.
 **************************************************************************/
typedef uint8   Dio_LevelType;

/**************************************************************************
 * @typedef Dio_PortLevelType
 * @brief 	Định nghĩa kiểu dữ liệu cho trạng thái của cổng DIO
 * @details Kiểu dữ liệu này để biểu diễn trạng thái của cổng DIO.
 **************************************************************************/
typedef uint16  Dio_PortLevelType;

/**************************************************************************
 * @struct	Dio_ChannelGroupType
 * @brief 	Định nghĩa kiểu dữ liệu cho nhóm kênh DIO
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn một nhóm các kênh 
 *          DIO liền kề trong cùng một cổng.
 **************************************************************************/
typedef struct {
	Dio_PortType port;	    /* Cổng chứa nhóm kênh DIO */
	uint16 mask;			/* Mask xác định vị trí của nhóm kênh */
	uint8 offset;			/* Vị trí của nhóm kênh trong cổng, đếm từ LSB */
} Dio_ChannelGroupType;

/**************************************************************************
 * @typedef Dio_ModeType
 * @brief 	Định nghĩa kiểu dữ liệu cho chế độ của kênh DIO
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn chế độ của kênh DIO. 
 **************************************************************************/
typedef uint16 Dio_ModeType;
#define DIO_MODE_AIN			(Dio_ModeType)0		/* Chế độ Analog Input */
#define DIO_MODE_IN_FLOATING	(Dio_ModeType)1		/* Chế độ Input Floating */
#define DIO_MODE_IN_PD			(Dio_ModeType)2		/* Chế độ Input Pull Down */
#define DIO_MODE_IN_PU			(Dio_ModeType)3		/* Chế độ Input Pull Up */
#define DIO_MODE_OUT_OD			(Dio_ModeType)4		/* Chế độ Output Open Drain */
#define DIO_MODE_OUT_PP			(Dio_ModeType)5		/* Chế độ Output Push Pull */
#define DIO_MODE_AF_OD			(Dio_ModeType)6		/* Chế độ Alternate Function Open Drain */
#define DIO_MODE_AF_PP			(Dio_ModeType)7		/* Chế độ Alternate Function Push Pull */

/**************************************************************************
 * @brief   Khởi tạo DIO
 * @param   None
 * @return 	None  
 **************************************************************************/
void Dio_Init(void);

/**************************************************************************
 * @brief   Đọc giá trị từ chân DIO 
 * @param   ChannelId       ID của kênh DIO cần đọc
 * @return 	Dio_LevelType   Trả về STD_HIGH nếu giá trị đọc được là 1 
 *                                 STD_LOW nếu giá trị đọc được là 0
 **************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/**************************************************************************
 * @brief   Ghi giá trị cho chân DIO
 * @param   ChannelId   ID của kênh DIO cần ghi
 * @param   Level       Trạng thái cần ghi cho chân DIO
 * @return 	None  
 **************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/**************************************************************************
 * @brief   Tạo độ trễ (delay)
 * @param   milliseconds    Thời gian độ trễ cần tạo (tính theo mili giây)
 * @return 	None  
 **************************************************************************/
void Dio_Delay(uint32 milliseconds);

#endif /* DIO_H */ 