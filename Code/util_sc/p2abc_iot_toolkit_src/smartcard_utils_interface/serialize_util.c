#include <smartcard_utils_interface/serialize_util.h>

/********************************************************************/
/*            Serialization using JSON and Base64/HEX                   */
/********************************************************************/
#include <smartcard_common/global_vars.h>

#include <smartcard_external_utilities/base64.h>
#include <smartcard_external_utilities/cJSON.h>
#include <smartcard_common/abc4T_types.h>


char* serialize_smartcard_status(int * buf_len){
    // TODO: los array dobles decidir si como dim1*dim2 a base64 o como estructura json de arrays para dim1 y base64 para dim2
    char temp_hex_string[5];
    char * temp_base64;
    int temp_base64_len, i;
    cJSON *root = cJSON_CreateObject();

    // BLOB_STORE_ITEM  blob_store [MAX_NUMBER_OF_BLOBS]
    cJSON* blob_store_json_array = cJSON_CreateArray();
    for(i=0; i < MAX_NUMBER_OF_BLOBS; ++i){
        cJSON * blob_store_item_json = cJSON_CreateObject();
        {   // BYTE buffer[MAX_BLOB_SIZE]
            temp_base64 = base64(blob_store[i].buffer, MAX_BLOB_SIZE, &temp_base64_len);
            cJSON_AddStringToObject(blob_store_item_json, "buffer", temp_base64);
            free(temp_base64);
        }
        cJSON_AddItemToArray(blob_store_json_array, blob_store_item_json);
    }
    cJSON_AddItemToObject(root, "blob_store", blob_store_json_array);

    // BLOB_CATALOG_ITEM  blob_catalog [MAX_NUMBER_OF_BLOBS]
    cJSON* blob_catalog_json_array = cJSON_CreateArray();
    for(i=0; i < MAX_NUMBER_OF_BLOBS; ++i){
        cJSON * blob_catalog_item_json = cJSON_CreateObject();
        //BYTE exists
        sprintf(temp_hex_string, "%02X", blob_catalog[i].exists);
        cJSON_AddStringToObject(blob_catalog_item_json, "exists", temp_hex_string);
        {   //BYTE uri[MAX_URI_SIZE]
            temp_base64 = base64(blob_catalog[i].uri, MAX_URI_SIZE, &temp_base64_len);
            cJSON_AddStringToObject(blob_catalog_item_json, "uri", temp_base64);
            free(temp_base64);
        }
        //BYTE uri_size;
        sprintf(temp_hex_string, "%02X", blob_catalog[i].uri_size);
        cJSON_AddStringToObject(blob_catalog_item_json, "uri_size", temp_hex_string);
        //WORD buffer_size;
        sprintf(temp_hex_string, "%02X", blob_catalog[i].buffer_size);
        cJSON_AddStringToObject(blob_catalog_item_json, "buffer_size", temp_hex_string);

        cJSON_AddItemToArray(blob_catalog_json_array, blob_catalog_item_json);
    }
    cJSON_AddItemToObject(root, "blob_catalog", blob_catalog_json_array);

    // BYTE master_backup_key [MASTER_BACKUP_KEY_SIZE]
    temp_base64 = base64(master_backup_key, MASTER_BACKUP_KEY_SIZE, &temp_base64_len);  // To Base64, the function allocates memory
    cJSON_AddStringToObject(root, "master_backup_key", temp_base64);    // Add base64 string to JSON
    free(temp_base64);  // free the allocated memory in base64()

    // BYTE root_code[ACCESS_CODE_SIZE]
    temp_base64 = base64(root_code, ACCESS_CODE_SIZE, &temp_base64_len);
    cJSON_AddStringToObject(root, "root_code", temp_base64);
    free(temp_base64);

    // BYTE resurrection_key[RESURRECTION_KEY_SIZE]
    temp_base64 = base64(resurrection_key, RESURRECTION_KEY_SIZE, &temp_base64_len);
    cJSON_AddStringToObject(root, "resurrection_key", temp_base64);
    free(temp_base64);

    // BYTE pin_trials
    sprintf(temp_hex_string, "%02X", pin_trials);
    cJSON_AddStringToObject(root, "pin_trials", temp_hex_string);

    // BYTE puk_trials
    sprintf(temp_hex_string, "%02X", puk_trials);
    cJSON_AddStringToObject(root, "puk_trials", temp_hex_string);

    // BYTE device_id[ID_SIZE]
    temp_base64 = base64(device_id, ID_SIZE, &temp_base64_len);
    cJSON_AddStringToObject(root, "device_id", temp_base64);
    free(temp_base64);

    // WORD x_size
    sprintf(temp_hex_string, "%02X", x_size);
    cJSON_AddStringToObject(root, "x_size", temp_hex_string);

    // BYTE device_key[MAX_SMALLINT_SIZE]
    temp_base64 = base64(device_key, MAX_SMALLINT_SIZE, &temp_base64_len);
    cJSON_AddStringToObject(root, "device_key", temp_base64);
    free(temp_base64);

    // BYTE puk[PUK_SIZE]
    temp_base64 = base64(puk, PUK_SIZE, &temp_base64_len);
    cJSON_AddStringToObject(root, "puk", temp_base64);
    free(temp_base64);

    // BYTE pin[PIN_SIZE]
    temp_base64 = base64(pin, PIN_SIZE, &temp_base64_len);
    cJSON_AddStringToObject(root, "pin", temp_base64);
    free(temp_base64);

    // BYTE mode
    sprintf(temp_hex_string, "%02X", mode);
    cJSON_AddStringToObject(root, "mode", temp_hex_string);

    // BYTE auth_keys[NUM_AUTH_KEYS][MAX_BIGINT_SIZE]
    cJSON* auth_keys_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_AUTH_KEYS; ++i){
        temp_base64 = base64(auth_keys[i], MAX_BIGINT_SIZE, &temp_base64_len);
        cJSON_AddItemToArray(auth_keys_json_array, cJSON_CreateString(temp_base64));
        free(temp_base64);
    }
    cJSON_AddItemToObject(root, "auth_keys", auth_keys_json_array);

    // WORD auth_keys_sizes[NUM_AUTH_KEYS]
    temp_base64 = base64(auth_keys_sizes, NUM_AUTH_KEYS, &temp_base64_len);
    cJSON_AddStringToObject(root, "auth_keys_sizes", temp_base64);
    free(temp_base64);

    // BYTE buffer[BUFFER_MAX_SIZE]
    temp_base64 = base64(buffer, BUFFER_MAX_SIZE, &temp_base64_len);
    cJSON_AddStringToObject(root, "buffer", temp_base64);
    free(temp_base64);

    // WORD buffer_size
    sprintf(temp_hex_string, "%02X", buffer_size);
    cJSON_AddStringToObject(root, "buffer_size", temp_hex_string);

    // BYTE authData
    sprintf(temp_hex_string, "%02X", authData);
    cJSON_AddStringToObject(root, "authData", temp_hex_string);

    // GROUP groups[NUM_GROUPS]
    cJSON* groups_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_GROUPS; ++i){
        cJSON * groups_item_json = cJSON_CreateObject();
        // BYTE group_id
        sprintf(temp_hex_string, "%02X", groups[i].group_id);
        cJSON_AddStringToObject(groups_item_json, "group_id", temp_hex_string);
        // BYTE modulus[MAX_BIGINT_SIZE]
        temp_base64 = base64(groups[i].modulus, MAX_BIGINT_SIZE, &temp_base64_len);
        cJSON_AddStringToObject(groups_item_json, "modulus", temp_base64);
        free(temp_base64);
        // WORD modulus_size
        sprintf(temp_hex_string, "%02X", groups[i].modulus_size);
        cJSON_AddStringToObject(groups_item_json, "modulus_size", temp_hex_string);
        // BYTE q[MAX_SMALLINT_SIZE]
        temp_base64 = base64(groups[i].q, MAX_SMALLINT_SIZE, &temp_base64_len);
        cJSON_AddStringToObject(groups_item_json, "q", temp_base64);
        free(temp_base64);
        // WORD q_size
        sprintf(temp_hex_string, "%02X", groups[i].q_size);
        cJSON_AddStringToObject(groups_item_json, "q_size", temp_hex_string);
        // BYTE f[MAX_BIGINT_SIZE]
        temp_base64 = base64(groups[i].f, MAX_BIGINT_SIZE, &temp_base64_len);
        cJSON_AddStringToObject(groups_item_json, "f", temp_base64);
        free(temp_base64);
        // WORD f_size
        sprintf(temp_hex_string, "%02X", groups[i].f_size);
        cJSON_AddStringToObject(groups_item_json, "f_size", temp_hex_string);

        // BYTE g[NUM_GEN][MAX_BIGINT_SIZE]
        temp_base64 = base64(groups[i].g, NUM_GEN*MAX_BIGINT_SIZE, &temp_base64_len);       // NOTE: dimensión doble
        cJSON_AddStringToObject(groups_item_json, "g", temp_base64);
        free(temp_base64);

        // WORD g_size[NUM_GEN]
        temp_base64 = base64(groups[i].g_size, NUM_GEN, &temp_base64_len);
        cJSON_AddStringToObject(groups_item_json, "g_size", temp_base64);
        free(temp_base64);
        // BYTE num_generators
        sprintf(temp_hex_string, "%02X", groups[i].num_generators);
        cJSON_AddStringToObject(groups_item_json, "num_generators", temp_hex_string);

        cJSON_AddItemToArray(groups_json_array, groups_item_json);
    }
    cJSON_AddItemToObject(root, "groups", groups_json_array);

#if NUM_COUNTERS > 0
    // COUNTER counters[NUM_COUNTERS]
    cJSON* counters_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_COUNTERS; ++i){
        cJSON * counters_item_json = cJSON_CreateObject();
        // BYTE counter_id
        sprintf(temp_hex_string, "%02X", counters[i].counter_id);
        cJSON_AddStringToObject(counters_item_json, "counter_id", temp_hex_string);
        // BYTE key_id
        sprintf(temp_hex_string, "%02X", counters[i].key_id);
        cJSON_AddStringToObject(counters_item_json, "key_id", temp_hex_string);
        // BYTE index
        sprintf(temp_hex_string, "%02X", counters[i].index);
        cJSON_AddStringToObject(counters_item_json, "index", temp_hex_string);
        // BYTE threshold
        sprintf(temp_hex_string, "%02X", counters[i].threshold);
        cJSON_AddStringToObject(counters_item_json, "threshold", temp_hex_string);
        // BYTE cursor[CURSOR_SIZE]
        temp_base64 = base64(counters[i].cursor, CURSOR_SIZE, &temp_base64_len);
        cJSON_AddStringToObject(counters_item_json, "cursor", temp_base64);
        free(temp_base64);
        // BYTE exists
        sprintf(temp_hex_string, "%02X", counters[i].exists);
        cJSON_AddStringToObject(counters_item_json, "exists", temp_hex_string);

        cJSON_AddItemToArray(counters_json_array, counters_item_json);
    }
    cJSON_AddItemToObject(root, "counters", counters_json_array);
#endif

    // ISSUER issuers[NUM_ISSUERS]
    cJSON* issuers_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_ISSUERS; ++i){
        // TODO
        cJSON * issuers_item_json = cJSON_CreateObject();
        // BYTE issuer_id
        sprintf(temp_hex_string, "%02X", issuers[i].issuer_id);
        cJSON_AddStringToObject(issuers_item_json, "issuer_id", temp_hex_string);
        // BYTE group_id
        // BYTE gen_id_1
        // BYTE gen_id_2
        // BYTE numpres
        // BYTE counter_id
        // BYTE exists
        cJSON_AddItemToArray(issuers_json_array, issuers_item_json);
    }
    cJSON_AddItemToObject(root, "issuers", issuers_json_array);


    // PROVER provers[NUM_PROVERS]
    cJSON* provers_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_PROVERS; ++i){
        // TODO
        cJSON * provers_item_json = cJSON_CreateObject();
        // BYTE prover_id
        // WORD ksize
        // WORD csize
        // BYTE kx[MAX_SMALLINT_SIZE]
        // BYTE c[HASH_SIZE]
        // BYTE proofsession[PROOFSESSION_SIZE]
        // BYTE proofstatus
        // BYTE cred_ids[NUM_CREDS]
        // BYTE cred_ids_size
        // BYTE exists

        cJSON_AddItemToArray(provers_json_array, provers_item_json);
    }
    cJSON_AddItemToObject(root, "provers", provers_json_array);


    // BYTE current_prover_id
    sprintf(temp_hex_string, "%02X", current_prover_id);
    cJSON_AddStringToObject(root, "current_prover_id", temp_hex_string);

    // CREDENTIAL credentials[NUM_CREDS]
    cJSON* credentials_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_CREDS; ++i){
        // TODO
        cJSON * credentials_item_json = cJSON_CreateObject();
        // BYTE credential_id
        // BYTE issuer_id
        // BYTE v[MAX_SMALLINT_SIZE]
        // BYTE kv[MAX_SMALLINT_SIZE]
        // BYTE status
        // BYTE prescount
        // WORD v_size
        // WORD kv_size
        // BYTE exists

        cJSON_AddItemToArray(credentials_json_array, credentials_item_json);
    }
    cJSON_AddItemToObject(root, "credentials", credentials_json_array);

    // BYTE temp_key[MAX_BIGINT_SIZE]
    temp_base64 = base64(temp_key, MAX_BIGINT_SIZE, &temp_base64_len);
    cJSON_AddStringToObject(root, "temp_key", temp_base64);
    free(temp_base64);

}

void deserialize_smartcard_status(const char * ascii, int length);

char* serialize_APDU_response(int * buf_len);

void deserialize_APDU_command(const char * ascii, int length);
