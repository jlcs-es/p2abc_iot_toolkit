#ifndef __SUBROUTINES_H
#define __SUBROUTINES_H

#import <defs_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

void getRandomBytes(BYTE* buffer, unsigned int size);
void checkPin(unsigned char* tested_pin);
void checkPuk(unsigned char* tested_puk);
unsigned int sizeDecode(unsigned char *s);
void sizeEncode(unsigned char *s, unsigned int size);
void getKey(BYTE *key, unsigned int *key_size, const BYTE key_id);
void publicKeyEncrypt(unsigned char* key, unsigned int key_size);
void encryption(BYTE* dst, unsigned int* dst_size, const BYTE *src, const unsigned int src_size, const BYTE *key, const unsigned int key_size);
void extract(const BYTE *key, const unsigned int key_size);
unsigned int extraction(const BYTE *n, const unsigned int n_size, BYTE *sig, unsigned int *sig_size, const BYTE *challenge, const unsigned int challenge_size);
void checkBufferPrefix(BYTE ins, BYTE *datain, unsigned int datain_size);
void checkBufferEqual(BYTE ins, BYTE *datain, unsigned int datain_size);
BYTE groupExists(BYTE group_id);
void getGroupComponent(BYTE group_id, BYTE comptype);
BYTE generatorExists(BYTE group_id, BYTE gen_id);
void getGenerator(BYTE group_id, BYTE gen_id);
BYTE accessCredential(BYTE *pin, BYTE credential_id);
void singleOrDoubleExpo(BYTE issuer_id, BYTE *e1, unsigned int e1_size, BYTE *e2, unsigned int e2_size);
void accessSession(BYTE credential_id);
void singleOrDoubleResponse(BYTE issuer_id, BYTE *c, unsigned int c_size, BYTE *x, unsigned int x_size, BYTE *kx, unsigned int kx_size, BYTE *v, unsigned int v_size, BYTE *kv, unsigned int kv_size);
void singleResponse(BYTE *k, unsigned int k_size, BYTE *c, unsigned int c_size, BYTE *u, unsigned int u_size, BYTE *q, unsigned int q_size, BYTE offset);
void scopeExclusiveGenerator(BYTE *scope, unsigned int scope_size, BYTE *m, unsigned int m_size, BYTE *f, unsigned int f_size);
BYTE* accessURI(BYTE *datain, unsigned int Lc);
void getBlobstoreInformations(unsigned int* first_available_index, unsigned int *blobcount, unsigned int *uri_index, unsigned char *uri, BYTE uri_size);
void encrypt(BYTE *password, BYTE label);
void decrypt(BYTE *device_id_prim, BYTE *password, BYTE label);
void print(void *s, unsigned int size);
void output_large_data(void);
void staticHighToSegment(void *low_addr, const void *high_addr, DWORD size);
void segmentToStaticHigh(void *high_addr, const void *low_addr, DWORD size);


#ifdef __cplusplus
}
#endif

#endif // __SUBROUTINES_H
