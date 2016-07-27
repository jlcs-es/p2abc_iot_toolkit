#ifndef __DEFS_TYPES_H
#define __DEFS_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char BYTE; //1byte
typedef signed char SBYTE;
typedef unsigned short WORD; //2bytes
typedef signed short SWORD;
//TODO: en la MOTA usar long, pero en PC usar int para 4 bytes
//typedef unsigned long DWORD; //4bytes
//typedef signed long SDWORD;
typedef unsigned int DWORD; //4bytes en PC
typedef signed int SDWORD;

typedef BYTE BOOL;




#ifdef __cplusplus
}
#endif

#endif // __DEFS_TYPES_H
