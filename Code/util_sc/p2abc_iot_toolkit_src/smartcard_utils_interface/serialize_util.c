#include <smartcard_utils_interface/serialize_util.h>

/********************************************************************/
/*            Serialization using JSON and Base64/HEX                   */
/********************************************************************/
#include <smartcard_common/global_vars.h>

#include <smartcard_external_utilities/base64.h>
#include <smartcard_external_utilities/cJSON.h>



char* serialize_smartcard_status(int * buf_len){

    char temp_hex_string[3];
    cJSON *root = cJSON_CreateObject();

    // BLOB_STORE_ITEM  blob_store []
    // BLOB_CATALOG_ITEM  blob_catalog [MAX_NUMBER_OF_BLOBS]
    // BYTE master_backup_key [MASTER_BACKUP_KEY_SIZE]
    // BYTE root_code[ACCESS_CODE_SIZE]
    // BYTE resurrection_key[RESURRECTION_KEY_SIZE]

    // BYTE pin_trials
    sprintf(temp_hex_string, "%02X", pin_trials);
    cJSON_AddStringToObject(root, "pin_trials", temp_hex_string);

    // BYTE puk_trials
    // BYTE device_id[ID_SIZE]
    // WORD x_size
    // BYTE device_key[MAX_SMALLINT_SIZE]
    // BYTE puk[PUK_SIZE]
    // BYTE pin[PIN_SIZE]
    // BYTE mode = MODE_VIRGIN
    // BYTE auth_keys[NUM_AUTH_KEYS][MAX_BIGINT_SIZE]
    // WORD auth_keys_sizes[NUM_AUTH_KEYS]
    // BYTE buffer[BUFFER_MAX_SIZE]
    // WORD buffer_size
    // BYTE authData
    // GROUP groups[NUM_GROUPS]
// #if NUM_COUNTERS > 0
    // COUNTER counters[NUM_COUNTERS]
// #endif
    // ISSUER issuers[NUM_ISSUERS]
    // PROVER provers[NUM_PROVERS]
    // BYTE current_prover_id
    // CREDENTIAL credentials[NUM_CREDS]
    // BYTE temp_key[MAX_BIGINT_SIZE]

}

void deserialize_smartcard_status(const char * ascii, int length);

char* serialize_APDU_response(int * buf_len);

void deserialize_APDU_command(const char * ascii, int length);
