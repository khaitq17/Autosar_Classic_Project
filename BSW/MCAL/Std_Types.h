/***************************************************************************
 * @file    Std_Types.h
 * @brief   Định nghĩa các kiểu dữ liệu tiêu chuẩn cho AUTOSAR
 * @details File này chứa tất cả các kiểu dữ liệu và ký hiệu dành cho chuẩn 
 *          AUTOSAR. Các kiểu dữ liệu này được trừu tượng hóa để trở nên 
 *          độc lập với nền tảng và trình biên dịch.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>

/**************************************************************************
 * @brief   Định nghĩa các kiểu dữ liệu cơ bản cho Autosar
 * @details Định nghĩa các kiểu dữ liệu với dấu và kích thước của nó.
 **************************************************************************/
typedef unsigned          	char 	uint8;	    /* Số nguyên không dấu 8 bit */
typedef   signed          	char 	sint8;	    /* Số nguyên có dấu 8 bit */
typedef unsigned short     	 int 	uint16;	    /* Số nguyên không dấu 16 bit */
typedef   signed short     	 int 	sint16;	    /* Số nguyên có dấu 16 bit */
typedef unsigned             int 	uint32;	    /* Số nguyên không dấu 32 bit */
typedef   signed           	 int 	sint32;	    /* Số nguyên có dấu 32 bit */
typedef unsigned       long long 	uint64;	    /* Số nguyên không dấu 64 bit */
typedef   signed       long long 	sint64;	    /* Số nguyên có dấu 64 bit */

typedef float	float32;	/* Số thực 32 bit */
typedef	double	float64;	/* Số thực 64 bit */

/**************************************************************************
 * @typedef boolean
 * @brief	Định nghĩa kiểu dữ liệu boolean 
 * @details Kiểu dữ liệu này được sử dụng để định nghĩa giá trị True và False.
 **************************************************************************/
typedef uint8 boolean;
#ifndef TRUE
    #define TRUE    (boolean)1   /* Boolean True value */
#endif /* TRUE */

#ifndef FALSE
    #define FALSE   (boolean)0   /* Boolean False value */
#endif /* FALSE */

/**************************************************************************
 * @typedef Std_ReturnType
 * @brief 	Định ngĩa kiểu dữ liệu trả về chuẩn
 * @details Kiểu dữ liệu này được sử dụng để định nghĩa giá trị trả về chuẩn
 *          cho các hàm trong Autosar.
 **************************************************************************/
typedef uint8 Std_ReturnType;
#define E_OK        (Std_ReturnType)0x00U  /* Thao tác thành công */
#define E_NOT_OK    (Std_ReturnType)0x01U  /* Thao tác không thành công */

/**************************************************************************
 * @brief	Định nghĩa giá trị logic chuẩn
 * @details Kiểu dữ liệu này được sử dụng cho trạng thái đầu vào/đầu ra.
 **************************************************************************/
#define STD_LOW		0x00U 	/* Trạng thái điện áp 0V */
#define STD_HIGH 	0x01U	/* Trạng thái điện áp 5V or 3.3V */

/**************************************************************************
 * @brief 	Định nghĩa con trỏ NULL 
 **************************************************************************/
#ifndef NULL_PTR
    #define NULL_PTR    ((void*)0)    
#endif  /* NULL Pointer */

/**************************************************************************
 * @struct 	Std_VersionInfoType
 * @brief 	Cấu trúc lưu trữ thông tin phiên bản phần mềm
 * @details Cấu trúc này được sử dụng để lưu trữ thông tin chi tiết về phiên 
 *          bản của một mô-đun phần mềm, bao gồm ID nhà cung cấp, ID mô-đun 
 *          và các phiên bản phần mềm.
 **************************************************************************/
typedef struct {
    uint16 vendorID;          /* ID nhà cung cấp */
    uint16 moduleID;          /* ID mô-đun */
    uint8  sw_major_version;  /* Phiên bản chính của phần mềm */
    uint8  sw_minor_version;  /* Phiên bản phụ của phần mềm */
    uint8  sw_patch_version;  /* Phiên bản vá lỗi của phần mềm */
} Std_VersionInfoType;

#endif /* STD_TYPES_H */