#ifndef __ERROR_CODES_H
#define __ERROR_CODES_H

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_CANT_MALLOC                       101
#define ERROR_SOCKET                            201
#define ERROR_CANT_OPEN_FILE                    401
#define ERROR_CANT_READ_FILE                    402
#define ERROR_BAD_JSON_VALUE_LENGTH             501
#define ERROR_BAD_JSON_ARRAY_LENGTH             502
#define ERROR_APDU_TOO_SHORT                    601
#define ERROR_APDU_TOO_LONG                     602
#define ERROR_OPENSSL                           701

#ifdef __cplusplus
}
#endif

#endif // __ERROR_CODES_H
