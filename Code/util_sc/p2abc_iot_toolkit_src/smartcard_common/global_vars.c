#include <smartcard_common/global_vars.h>


static char version[64] = "ABC4Trust Card Lite - Jose Luis Canovas 2016 - IoT Toolkit v1   "; // 64 bytes

/* Internal system variables. */
BYTE ProtocolFlags;
BYTE ProtocolType;
BYTE GetResponseCLA;
BYTE GetResponseSW1;
BYTE CLA;
BYTE INS;
BYTE P1;
BYTE P2;
BYTE P3;
WORD P1P2;
WORD Lc;
WORD Le;
WORD La;
BYTE SW1;
BYTE SW2;
WORD SW12;

///TODO: estas variables globales se nombran para diferentes funciones (session, public, static) -> ¿dejar aquí o mover?
///TODO: si es viable para las motas (tamaño del programa, etc), pasar de variables globales a funciones -> mejor diseño


/************************************************************************
 * Session data for the application (in RAM, but not public. Together
 * with the stack, limited to 960 bytes on ML2 cards)
 ************************************************************************/

unsigned int temp_size; // not used in subroutines

unsigned int challenge_size = 0;

unsigned int pad_size;
BYTE authKeyId;
BYTE temp_group_id;
BYTE temp_gen_id;
BYTE temp_key_id;
BYTE temp_counter_id;
BYTE temp_issuer_id;
BYTE temp_prover_id;
BYTE temp_credential_id;
BYTE temp_gen_id_1;
BYTE temp_gen_id_2;
unsigned int temp_gen_1_size;
unsigned int temp_gen_2_size;
BYTE temp_status;
BYTE *temp_modulus;
unsigned int temp_modulus_size;
BYTE d;
//BYTE mExit; //NOTE: redifined from "exit" for type errors
unsigned int temp_blob_index;
unsigned int temp_blobcount;
unsigned int temp_uri_index;
BYTE temp_nread;
BYTE prev_nread;

unsigned int temp_buffer_size;
WORD temp_rand_size;

BYTE *uri;

unsigned int i, j;

BYTE device_id_prim[ID_SIZE];
unsigned int temp_key_size;

// the following variables are used in GET RESPONSE and allow to output more than 255 bytes
WORD remaining_size;
BYTE *remaining_position;

BYTE *buffer_ptr;

MEM_SESSION mem_session;

/************************************************************************
 * Public data for the application (first data is placed at PB[0])
 ************************************************************************/

BYTE temp_buffer[2*MAX_BIGINT_SIZE]; // size max can be reached in the singleResponse subroutine, cannot be less than 512 bytes

APDU_DATA apdu_data;



/************************************************************************
 * Static data for the application
 ************************************************************************/

BLOB_STORE_ITEM   blob_store[MAX_NUMBER_OF_BLOBS]; // do not declare anything above 'blob_store': anything declared above blobs could be located in higher (not directly accessible) part of the e2 memory.
BLOB_CATALOG_ITEM blob_catalog[MAX_NUMBER_OF_BLOBS];


BYTE master_backup_key[MASTER_BACKUP_KEY_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


BYTE root_code[ACCESS_CODE_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


BYTE resurrection_key[RESURRECTION_KEY_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

BYTE pin_trials = MAX_PIN_TRIALS;
BYTE puk_trials = MAX_PUK_TRIALS;
BYTE device_id[ID_SIZE];
unsigned int x_size;
BYTE device_key[MAX_SMALLINT_SIZE];
BYTE puk[PUK_SIZE];
BYTE pin[PIN_SIZE];
BYTE mode = MODE_VIRGIN;
BYTE auth_keys[NUM_AUTH_KEYS][MAX_BIGINT_SIZE];
unsigned int auth_keys_sizes[NUM_AUTH_KEYS]; // auth_keys_exist[key_id] > 0 iff the key exists, 0 otherwise
BYTE buffer[BUFFER_MAX_SIZE];
unsigned int buffer_size = 0;
BYTE authData = 0;
GROUP groups[NUM_GROUPS];
#if NUM_COUNTERS > 0
COUNTER counters[NUM_COUNTERS];
#endif
ISSUER issuers[NUM_ISSUERS];
PROVER provers[NUM_PROVERS];
BYTE current_prover_id;
CREDENTIAL credentials[NUM_CREDS];

BYTE temp_key[MAX_BIGINT_SIZE];



// TODO: por la linea 800 de main.c SET VIRGIN MODE inicializa la gran parte de las variables.

