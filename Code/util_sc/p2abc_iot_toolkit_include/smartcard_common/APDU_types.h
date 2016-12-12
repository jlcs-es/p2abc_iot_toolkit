#ifndef __APDU_TYPES_H
#define __APDU_TYPES_H

#include "defs_types.h"
#include "defs_consts.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * APDU structures
 ************************************************************************/

typedef struct
{
  BYTE pin[4];
  BYTE keyId;
} APDU_READ_AUTHENTICATION_KEY;

typedef struct
{
  BYTE group_id;
  BYTE comptype;
} APDU_SET_GROUP_COMPONENT;

typedef struct
{
  BYTE group_id;
  BYTE genId;
} APDU_SET_GENERATOR;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE group_id;
} APDU_READ_GROUP_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE group_id;
  BYTE comptype;
} APDU_READ_GROUP_COMPONENT_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE group_id;
  BYTE gen_id;
} APDU_READ_GENERATOR_IN;

typedef struct
{
  BYTE counter_id;
  BYTE key_id;
  BYTE index;
  BYTE threshold;
  BYTE cursor[CURSOR_SIZE];
} APDU_SET_COUNTER;

typedef struct
{
  BYTE key_id;
  BYTE sig[MAX_BIGINT_SIZE];
} APDU_INCREMENT_COUNTER;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE counter_id;
} APDU_READ_COUNTER_IN;

typedef struct
{
  BYTE issuer_id;
  BYTE group_id;
  BYTE gen_id_1;
  BYTE gen_id_2;
  BYTE numpres;
  BYTE counter_id;
} APDU_SET_ISSUER_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE issuer_id;
} APDU_READ_ISSUER_IN;

typedef struct
{
  BYTE prover_id;
  WORD ksize;
  WORD csize;
  BYTE cred_ids[NUM_CREDS];
} APDU_SET_PROVER_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE prover_id;
} APDU_READ_PROVER_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE prover_id;
} APDU_START_COMMITMENTS_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE prover_id;
  BYTE input[MAX_APDU_INPUT_DATA_SIZE-PIN_SIZE-1];
} APDU_START_RESPONSES_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE credential_id;
  BYTE issuer_id;
} APDU_SET_CREDENTIAL_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE credential_id;
} APDU_PIN_AND_CREDENTIAL_ID;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE scope[MAX_APDU_INPUT_DATA_SIZE-PIN_SIZE];
} APDU_GET_SCOPE_EXCLUSIVE_PSEUDONYM_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE scope[MAX_APDU_INPUT_DATA_SIZE-PIN_SIZE];
} APDU_GET_SCOPE_EXCLUSIVE_COMMITMENT_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE scope[MAX_APDU_INPUT_DATA_SIZE-PIN_SIZE];
} APDU_GET_SCOPE_EXCLUSIVE_RESPONSE_IN;

typedef struct
{
  BYTE datain[PIN_SIZE+MAX_URI_SIZE];
} APDU_BLOB_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE nread;
} APDU_LIST_BLOBS_IN;

typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE password[PASSWORD_SIZE];
} APDU_BACKUP_IN;

#ifdef SODER
typedef struct
{
  BYTE pin[PIN_SIZE];
  BYTE password[PASSWORD_SIZE];
  BYTE credential_id;
} APDU_BACKUP_CREDENTIAL_IN;
#endif

#ifdef __cplusplus
}
#endif

#endif // __APDU_TYPES_H
