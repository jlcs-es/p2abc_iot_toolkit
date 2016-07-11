#ifndef __ABC4T_TYPES_H
#define __ABC4T_TYPES_H

#include "defs_types.h"
#include "defs_consts.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * Various structures for ABC4Trust specific types
 ************************************************************************/


typedef struct
{
  BYTE group_id;
  BYTE modulus[MAX_BIGINT_SIZE];
  unsigned int modulus_size;
  BYTE q[MAX_SMALLINT_SIZE];          // group order, do not change the size for something larger than MAX_SMALLINT_SIZE
  unsigned int q_size;
  BYTE f[MAX_BIGINT_SIZE];          // cofactor
  unsigned int f_size;
  BYTE g[NUM_GEN][MAX_BIGINT_SIZE]; // generators
  unsigned int g_size[NUM_GEN];
  BYTE num_generators;           // number of generators
} GROUP;

typedef struct
{
  BYTE counter_id;
  BYTE key_id;
  BYTE index;
  BYTE threshold;
  BYTE cursor[CURSOR_SIZE];
  BYTE exists;
} COUNTER;

typedef struct
{
  BYTE issuer_id;
  BYTE group_id;
  BYTE gen_id_1;
  BYTE gen_id_2;
  BYTE numpres;
  BYTE counter_id;
  BYTE exists;
} ISSUER;

typedef struct
{
  BYTE prover_id;
  unsigned int ksize;
  unsigned int csize;
  BYTE kx[MAX_SMALLINT_SIZE];
  BYTE c[HASH_SIZE];
  BYTE proofsession[PROOFSESSION_SIZE];
  BYTE proofstatus;
  BYTE cred_ids[NUM_CREDS];
  BYTE cred_ids_size; // also called 't' in the documentation
  BYTE exists;
} PROVER;

typedef struct
{
  BYTE credential_id;
  BYTE issuer_id;
  BYTE v[MAX_SMALLINT_SIZE]; // private key
  BYTE kv[MAX_SMALLINT_SIZE];
  BYTE status;
  BYTE prescount;
  unsigned int v_size;
  unsigned int kv_size;
  BYTE exists;
} CREDENTIAL; /* do NOT change the order of the structure elements */

typedef struct
{
  BYTE exists;
  BYTE uri[MAX_URI_SIZE];
  BYTE uri_size;
  WORD buffer_size;
} BLOB_CATALOG_ITEM;

typedef struct
{
  BYTE buffer[MAX_BLOB_SIZE];
} BLOB_STORE_ITEM;

#ifdef __cplusplus
}
#endif

#endif // __ABC4T_TYPES_H
