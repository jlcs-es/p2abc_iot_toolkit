#ifndef __GLOBAL_VARS_H
#define __GLOBAL_VARS_H

#include <defs_types.h>
#include <defs_consts.h>
#include <APDU_types.h>
#include <abc4T_types.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Internal system variables. */
extern BYTE ProtocolFlags;
extern BYTE ProtocolType;
extern BYTE GetResponseCLA;
extern BYTE GetResponseSW1;
extern BYTE CLA;
extern BYTE INS;
extern BYTE P1;
extern BYTE P2;
extern BYTE P3;
extern WORD P1P2;               /* P1 in MSB, P2 in LSB. */
extern WORD Lc;
extern WORD Le;
extern WORD La;
extern BYTE SW1;
extern BYTE SW2;
extern WORD SW12;               /* SW1 in MSB, SW2 in LSB. */








/************************************************************************
 * Session data for the application (in RAM, but not public. Together
 * with the stack, limited to 960 bytes on ML2 cards)
 ************************************************************************/

extern unsigned int temp_size; // not used in subroutines

extern unsigned int challenge_size;

extern unsigned int pad_size;
extern BYTE authKeyId;
extern BYTE temp_group_id;
extern BYTE temp_gen_id;
extern BYTE temp_key_id;
extern BYTE temp_counter_id;
extern BYTE temp_issuer_id;
extern BYTE temp_prover_id;
extern BYTE temp_credential_id;
extern BYTE temp_gen_id_1;
extern BYTE temp_gen_id_2;
extern unsigned int temp_gen_1_size;
extern unsigned int temp_gen_2_size;
extern BYTE temp_status;
extern BYTE *temp_modulus;
extern unsigned int temp_modulus_size;
extern BYTE d;
//extern BYTE mExit;
// NOTE: redifined from "exit"
// TODO: RENOMBRAR exit EN EL CÓDIGO IMPORTADO
// NOTE: en main.c solo lo usa en #ifdef SODER y comentado indicando que ya no se usa.
// NOTE: en su lugar usa ExitSW
extern unsigned int temp_blob_index;
extern unsigned int temp_blobcount;
extern unsigned int temp_uri_index;
extern BYTE temp_nread;
extern BYTE prev_nread;

extern unsigned int temp_buffer_size;
extern WORD temp_rand_size;

extern BYTE *uri;

extern unsigned int i, j;

extern BYTE device_id_prim[ID_SIZE];
extern unsigned int temp_key_size;

// the following variables are used in GET RESPONSE and allow to output more than 255 bytes
extern WORD remaining_size;
extern BYTE *remaining_position;

extern BYTE *buffer_ptr;

typedef union
{
    BYTE small_buffer[SMALL_BUFFER_MAX_SIZE];
    BYTE pad[MAX_BIGINT_SIZE-32];
    BYTE challenge[CHALLENGE_MAX_SIZE];
} MEM_SESSION;
extern MEM_SESSION mem_session;

/************************************************************************
 * Public data for the application (first data is placed at PB[0])
 ************************************************************************/

extern BYTE temp_buffer[2*MAX_BIGINT_SIZE]; // size max can be reached in the singleResponse subroutine, cannot be less than 512 bytes

typedef union
{
    // structures and variables used for output
    BYTE mode;
    BYTE pin_trials;
    BYTE puk_trials;
    BYTE challenge[CHALLENGE_MAX_SIZE];
    BYTE device_id[ID_SIZE];
    BYTE version[64];
    BYTE memspace[2];
    BYTE dataout[MAX_APDU_OUTPUT_DATA_SIZE];
    BYTE access_code[ACCESS_CODE_SIZE];
    BYTE mac[MAC_SIZE];
    APDU_READ_AUTHENTICATION_KEY read_authentication_key;
    APDU_SET_GROUP_COMPONENT set_group_component;
    APDU_SET_GENERATOR set_generator;
    BYTE proofsession[PROOFSESSION_SIZE];
    // structures and variables used for input
    BYTE challenge_size;
    BYTE old_pin_and_new_pin[PIN_SIZE << 1];
    BYTE puk_and_pin[PUK_SIZE + PIN_SIZE];
    BYTE id_and_size[ID_SIZE + SIZE_SIZE];
    BYTE small_buffer[SMALL_BUFFER_MAX_SIZE];
    BYTE pin[PIN_SIZE];
    BYTE buffer[BUFFER_MAX_SIZE];
    BYTE keyId;
    BYTE auth_key[MAX_BIGINT_SIZE];
    APDU_READ_GROUP_IN read_group_in;
    APDU_READ_GROUP_COMPONENT_IN read_group_component_in;
    APDU_READ_GENERATOR_IN read_generator_in;
    BYTE group_id;
    APDU_SET_COUNTER set_counter;
    APDU_INCREMENT_COUNTER increment_counter;
    APDU_READ_COUNTER_IN read_counter_in;
    BYTE counter_id;
    APDU_SET_ISSUER_IN set_issuer_in;
    APDU_READ_ISSUER_IN read_issuer_in;
    BYTE issuer_id;
    APDU_SET_PROVER_IN set_prover_in;
    APDU_READ_PROVER_IN read_prover_in;
    BYTE prover_id;
    APDU_START_COMMITMENTS_IN start_commitments_in;
    APDU_START_RESPONSES_IN start_responses_in;
    APDU_SET_CREDENTIAL_IN set_credential_in;
    APDU_PIN_AND_CREDENTIAL_ID pin_and_credential_id;
    APDU_GET_SCOPE_EXCLUSIVE_PSEUDONYM_IN get_scope_exclusive_pseudonym_in;
    APDU_GET_SCOPE_EXCLUSIVE_COMMITMENT_IN get_scope_exclusive_commitment_in;
    APDU_GET_SCOPE_EXCLUSIVE_RESPONSE_IN get_scope_exclusive_response_in;
    APDU_BLOB_IN blob_in;
    APDU_LIST_BLOBS_IN list_blobs_in;
    APDU_BACKUP_IN backup_in;
#ifdef SODER
    APDU_BACKUP_CREDENTIAL_IN backup_credential_in;
#endif
} APDU_DATA;

extern APDU_DATA apdu_data;

///TODO: mover a APDU_types.h, cuando todo funcione



/************************************************************************
 * Static data for the application
 ************************************************************************/

extern BLOB_STORE_ITEM   blob_store[MAX_NUMBER_OF_BLOBS]; // do not declare anything above 'blob_store': anything declared above blobs could be located in higher (not directly accessible) part of the e2 memory.
extern BLOB_CATALOG_ITEM blob_catalog[MAX_NUMBER_OF_BLOBS];



extern BYTE master_backup_key[MASTER_BACKUP_KEY_SIZE];


extern BYTE root_code[ACCESS_CODE_SIZE];


extern BYTE resurrection_key[RESURRECTION_KEY_SIZE];

extern BYTE pin_trials;
extern BYTE puk_trials;
extern BYTE device_id[ID_SIZE];
extern unsigned int x_size;
extern BYTE device_key[MAX_SMALLINT_SIZE];
extern BYTE puk[PUK_SIZE];
extern BYTE pin[PIN_SIZE];
extern BYTE mode;
extern BYTE auth_keys[NUM_AUTH_KEYS][MAX_BIGINT_SIZE];
extern unsigned int auth_keys_sizes[NUM_AUTH_KEYS]; // auth_keys_exist[key_id] > 0 iff the key exists, 0 otherwise
extern BYTE buffer[BUFFER_MAX_SIZE];
extern unsigned int buffer_size;
extern BYTE authData;
extern GROUP groups[NUM_GROUPS];
#if NUM_COUNTERS > 0
extern COUNTER counters[NUM_COUNTERS];
#endif
extern ISSUER issuers[NUM_ISSUERS];
extern PROVER provers[NUM_PROVERS];
extern BYTE current_prover_id;
extern CREDENTIAL credentials[NUM_CREDS];

extern BYTE temp_key[MAX_BIGINT_SIZE];

















#ifdef __cplusplus
}
#endif

#endif //__GLOBAL_VARS_H
