#ifndef __SUBROUTINES_H
#define __SUBROUTINES_H

#include <smartcard_common/defs_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

void getRandomBytes(BYTE* buffer, WORD size);
BOOL checkPin(BYTE* tested_pin);
void checkPuk(BYTE* tested_puk);
WORD sizeDecode(BYTE *s);
void sizeEncode(BYTE *s, WORD size);
void getKey(BYTE *key, WORD *key_size, const BYTE key_id);
void publicKeyEncrypt(BYTE* key, WORD key_size);
void encryption(BYTE* dst, WORD* dst_size, const BYTE *src, const WORD src_size, const BYTE *key, const WORD key_size);
void extract(const BYTE *key, const WORD key_size);
WORD extraction(const BYTE *n, const WORD n_size, BYTE *sig, WORD *sig_size, const BYTE *challenge, const WORD challenge_size);
void checkBufferPrefix(BYTE ins, BYTE *datain, WORD datain_size);
void checkBufferEqual(BYTE ins, BYTE *datain, WORD datain_size);
BYTE groupExists(BYTE group_id);
void getGroupComponent(BYTE group_id, BYTE comptype);
BYTE generatorExists(BYTE group_id, BYTE gen_id);
void getGenerator(BYTE group_id, BYTE gen_id);
BYTE accessCredential(BYTE *pin, BYTE credential_id);
void singleOrDoubleExpo(BYTE issuer_id, BYTE *e1, WORD e1_size, BYTE *e2, WORD e2_size);
void accessSession(BYTE credential_id);
void singleOrDoubleResponse(BYTE issuer_id, BYTE *c, WORD c_size, BYTE *x, WORD x_size, BYTE *kx, WORD kx_size, BYTE *v, WORD v_size, BYTE *kv, WORD kv_size);
void singleResponse(BYTE *k, WORD k_size, BYTE *c, WORD c_size, BYTE *u, WORD u_size, BYTE *q, WORD q_size, BYTE offset);
void scopeExclusiveGenerator(BYTE *scope, WORD scope_size, BYTE *m, WORD m_size, BYTE *f, WORD f_size);
BYTE* accessURI(BYTE *datain, WORD Lc);
void getBlobstoreInformations(WORD* first_available_index, WORD *blobcount, WORD *uri_index, BYTE *uri, BYTE uri_size);
void encrypt(BYTE *password, BYTE label);
void decrypt(BYTE *device_id_prim, BYTE *password, BYTE label);
void print(void *s, WORD size);
void output_large_data(void);
void staticHighToSegment(void *low_addr, const void *high_addr, DWORD size);
void segmentToStaticHigh(void *high_addr, const void *low_addr, DWORD size);


#ifdef __cplusplus
}
#endif

#endif // __SUBROUTINES_H
