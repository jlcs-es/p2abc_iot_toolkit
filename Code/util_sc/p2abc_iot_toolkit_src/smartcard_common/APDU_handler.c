#include <smartcard_common/APDU_handler.h>
#include <smartcard_common/defs_errs.h>
#include <smartcard_common/global_vars.h>
#include <smartcard_common/m_adapted_API.h>
#include <smartcard_adaptor/system_funcs.h>
#include <smartcard_common/subroutines.h>
#include <smartcard_common/defs_ins.h>


void handle_APDU() {

    /* Check class in APDU. */
    if (CLA != ABC_CLA && INS != INS_GET_RESPONSE)
        mExitSW(ERR_BAD_CLA);

    /* Decode instruction. */
    switch (INS)
    {
        #ifdef TEST_PATRAS_MODE       //TODO: remove if not necessary
        case INS_GET_KX_AND_DEVICE_KEY:
            handle_INS_GET_KX_AND_DEVICE_KEY();
            break;
        case INS_TEST:
            handle_INS_TEST();
            break;
        #endif
        case INS_GET_MODE:
            handle_INS_GET_MODE();
            break;
        case INS_SET_ROOT_MODE:
            handle_INS_SET_ROOT_MODE();
            break;
        case INS_SET_WORKING_MODE:
            handle_INS_SET_WORKING_MODE();
            break;
        case INS_SET_VIRGIN_MODE:
            handle_INS_SET_VIRGIN_MODE();
            break;
        case INS_SET_FAST_VIRGIN_MODE:
            handle_INS_SET_FAST_VIRGIN_MODE();
            break;
        case INS_PIN_TRIALS_LEFT:
            handle_INS_PIN_TRIALS_LEFT();
            break;
        case INS_PUK_TRIALS_LEFT:
            handle_INS_PUK_TRIALS_LEFT();
            break;
        case INS_CHANGE_PIN:
            handle_INS_CHANGE_PIN();
            break;
        case INS_RESET_PIN:
            handle_INS_RESET_PIN();
            break;
        case INS_INITIALIZE_DEVICE:
            handle_INS_INITIALIZE_DEVICE();
            break;
        case INS_GET_DEVICE_ID:
            handle_INS_GET_DEVICE_ID();
            break;
        case INS_GET_VERSION:
            handle_INS_GET_VERSION();
            break;
        case INS_PUT_DATA:
            handle_INS_PUT_DATA();
            break;
        case INS_GET_CHALLENGE:
            handle_INS_GET_CHALLENGE();
            break;
        case INS_AUTHENTICATE_DATA:
            handle_INS_AUTHENTICATE_DATA();
            break;
        case INS_SET_AUTHENTICATION_KEY:
            handle_INS_SET_AUTHENTICATION_KEY();
            break;
        case INS_LIST_AUTHENTICATION_KEYS:
            handle_INS_LIST_AUTHENTICATION_KEYS();
            break;
        case INS_READ_AUTHENTICATION_KEY:
            handle_INS_READ_AUTHENTICATION_KEY();
            break;
        case INS_REMOVE_AUTHENTICATION_KEY:
            handle_INS_REMOVE_AUTHENTICATION_KEY();
            break;
        case INS_SET_GROUP_COMPONENT:
            handle_INS_SET_GROUP_COMPONENT();
            break;
        case INS_SET_GENERATOR:
            handle_INS_SET_GENERATOR();
            break;
        case INS_LIST_GROUPS:
            handle_INS_LIST_GROUPS();
            break;
        case INS_READ_GROUP:
            handle_INS_READ_GROUP();
            break;
        case INS_READ_GROUP_COMPONENT:
            handle_INS_READ_GROUP_COMPONENT();
            break;
        case INS_READ_GENERATOR:
            handle_INS_READ_GENERATOR();
            break;
        case INS_REMOVE_GROUP:
            handle_INS_REMOVE_GROUP();
            break;
        case INS_SET_COUNTER:
            handle_INS_SET_COUNTER();
            break;
        case INS_INCREMENT_COUNTER:
            handle_INS_INCREMENT_COUNTER();
            break;
        case INS_LIST_COUNTERS:
            handle_INS_LIST_COUNTERS();
            break;
        case INS_READ_COUNTER:
            handle_INS_READ_COUNTER();
            break;
        case INS_REMOVE_COUNTER:
            handle_INS_REMOVE_COUNTER();
            break;
        case INS_SET_ISSUER:
            handle_INS_SET_ISSUER();
            break;
        case INS_LIST_ISSUERS:
            handle_INS_LIST_ISSUERS();
            break;
        case INS_READ_ISSUER:
            handle_INS_READ_ISSUER();
            break;
        case INS_REMOVE_ISSUER:
            handle_INS_REMOVE_ISSUER();
            break;
        case INS_SET_PROVER:
            handle_INS_SET_PROVER();
            break;
        case INS_READ_PROVER:
            handle_INS_READ_PROVER();
            break;
        case INS_REMOVE_PROVER:
            handle_INS_REMOVE_PROVER();
            break;
        case INS_START_COMMITMENTS:
            handle_INS_START_COMMITMENTS();
            break;
        case INS_START_RESPONSES:
            handle_INS_START_RESPONSES();
            break;
        case INS_SET_CREDENTIAL:
            handle_INS_SET_CREDENTIAL();
            break;
        case INS_LIST_CREDENTIALS:
            handle_INS_LIST_CREDENTIALS();
            break;
        case INS_READ_CREDENTIAL:
            handle_INS_READ_CREDENTIAL();
            break;
        case INS_REMOVE_CREDENTIAL:
            handle_INS_REMOVE_CREDENTIAL();
            break;
        case INS_GET_CREDENTIAL_PUBLIC_KEY:
            handle_INS_GET_CREDENTIAL_PUBLIC_KEY();
            break;
        case INS_GET_ISSUANCE_COMMITMENT:
            handle_INS_GET_ISSUANCE_COMMITMENT();
            break;
        case INS_GET_ISSUANCE_RESPONSE:
            handle_INS_GET_ISSUANCE_RESPONSE();
            break;
        case INS_GET_PRESENTATION_COMMITMENT:
            handle_INS_GET_PRESENTATION_COMMITMENT();
            break;
        case INS_GET_PRESENTATION_RESPONSE:
            handle_INS_GET_PRESENTATION_RESPONSE();
            break;
        case INS_GET_DEVICE_PUBLIC_KEY:
            handle_INS_GET_DEVICE_PUBLIC_KEY();
            break;
        case INS_GET_DEVICE_COMMITMENT:
            handle_INS_GET_DEVICE_COMMITMENT();
            break;
        case INS_GET_DEVICE_RESPONSE:
            handle_INS_GET_DEVICE_RESPONSE();
            break;
        case INS_GET_SCOPE_EXCLUSIVE_PSEUDONYM:
            handle_INS_GET_SCOPE_EXCLUSIVE_PSEUDONYM();
            break;
        case INS_GET_SCOPE_EXCLUSIVE_COMMITMENT:
            handle_INS_GET_SCOPE_EXCLUSIVE_COMMITMENT();
            break;
        case INS_GET_SCOPE_EXCLUSIVE_RESPONSE:
            handle_INS_GET_SCOPE_EXCLUSIVE_RESPONSE();
            break;
        case INS_STORE_BLOB:
            handle_INS_STORE_BLOB();
            break;
        case INS_LIST_BLOBS:
            handle_INS_LIST_BLOBS();
            break;
        case INS_READ_BLOB:
            handle_INS_READ_BLOB();
            break;
        case INS_REMOVE_BLOB:
            handle_INS_REMOVE_BLOB();
            break;
        case INS_BACKUP_DEVICE:
            handle_INS_BACKUP_DEVICE();
            break;
        case INS_RESTORE_DEVICE:
            handle_INS_RESTORE_DEVICE();
            break;
        case INS_BACKUP_COUNTERS:
            handle_INS_BACKUP_COUNTERS();
            break;
        case INS_RESTORE_COUNTERS:
            handle_INS_RESTORE_COUNTERS();
            break;
        #ifdef SODER //TODO: remove if not necessary
        case INS_BACKUP_CREDENTIAL:
            handle_INS_BACKUP_CREDENTIAL();
            break;
        case INS_RESTORE_CREDENTIAL:
            handle_INS_RESTORE_CREDENTIAL();
            break;
        #endif
        case INS_GET_INFO:
            handle_INS_GET_INFO();
            break;
        case INS_NOTHING:
            handle_INS_NOTHING();
            break;
        case INS_GET_RESPONSE:
            handle_INS_GET_RESPONSE();
            break;

        default:
            mExitSW(ERR_BAD_INS);
    }
    mExit();
}


#ifdef TEST_PATRAS_MODE

void handle_INS_GET_KX_AND_DEVICE_KEY(void){
    if (!mCheckCase(2))
        mExitSW(ERR_BAD_ISO);

    if (current_prover_id < 1 || current_prover_id > NUM_PROVERS)
        mExitSW(ERR_PROVERID_OUTSIDE_OF_RANGE);

    temp_size = 0;

    mem_cpy(temp_buffer+temp_size, &(provers[current_prover_id-1].ksize), 2);
    temp_size += 2;

    mem_cpy(temp_buffer+temp_size, provers[current_prover_id-1].kx + MAX_SMALLINT_SIZE - provers[current_prover_id-1].ksize, provers[current_prover_id-1].ksize);
    temp_size += provers[current_prover_id-1].ksize;

    mem_cpy(temp_buffer+temp_size, &x_size, 2);
    temp_size += 2;

    mem_cpy(temp_buffer+temp_size, device_key+MAX_SMALLINT_SIZE-x_size, x_size);
    temp_size += x_size;

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }

}

void handle_INS_TEST(void){
      // do whatever you like here...
}

#endif

void handle_INS_GET_MODE(){

    if (!mCheckCase(2))
        mExitSW(ERR_BAD_ISO);

    apdu_data.mode = mode;
    mExitLa(1);

}


void handle_INS_SET_ROOT_MODE(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_VIRGIN)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != ACCESS_CODE_SIZE)
        mExitSW((ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ ACCESS_CODE_SIZE));

    if (mem_cmp(apdu_data.access_code, root_code, ACCESS_CODE_SIZE) != 0)
        mExitSW(ERR_FAILED_ACCESS_PRIVILEGED_MODE);

    mode = MODE_ROOT;

}


void handle_INS_SET_WORKING_MODE(){

    if (!mCheckCase(1))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT)
        mExitSW(ERR_BAD_MODE ^ mode);

    mode = MODE_WORKING;

}


void handle_INS_SET_VIRGIN_MODE(){

    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (Lc != MAC_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ MAC_SIZE);

    if (challenge_size < 16)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_RAND ^ 16);

    mem_cpy(temp_buffer, resurrection_key, RESURRECTION_KEY_SIZE);
    mem_cpy(temp_buffer+RESURRECTION_KEY_SIZE, mem_session.challenge, challenge_size);
    buffer_ptr = temp_buffer + RESURRECTION_KEY_SIZE + challenge_size;
    mSecureHash(RESURRECTION_KEY_SIZE + challenge_size, 32, buffer_ptr, temp_buffer);

    mem_set(mem_session.challenge, 0, CHALLENGE_MAX_SIZE);
    challenge_size = 0;

    if (mem_cmp(apdu_data.mac, buffer_ptr, MAC_SIZE) != 0)
        mExitSW(ERR_FAILED_ACCESS_PRIVILEGED_MODE);

    // Erase the entire contents of the static memory and reset some of the variables to their original value

    pin_trials = MAX_PIN_TRIALS;
    puk_trials = MAX_PUK_TRIALS;
    mem_set(device_id, 0, ID_SIZE);
    x_size = 0;
    mem_set(device_key, 0, MAX_SMALLINT_SIZE);
    mem_set(puk, 0, PUK_SIZE);
    mem_set(pin, 0, PIN_SIZE);
    mem_set(auth_keys, 0, NUM_AUTH_KEYS*MAX_BIGINT_SIZE);
    mem_set(auth_keys_sizes, 0, sizeof(WORD)*NUM_AUTH_KEYS);
    mem_set(buffer, 0, BUFFER_MAX_SIZE);
    buffer_size = 0;
    authData = 0;
    mem_set(groups, 0, sizeof(GROUP)*NUM_GROUPS);
#if NUM_COUNTERS > 0
    mem_set(counters, 0, sizeof(COUNTER)*NUM_COUNTERS);
#endif
    mem_set(issuers, 0, sizeof(ISSUER)*NUM_ISSUERS);
    mem_set(provers, 0, sizeof(PROVER)*NUM_PROVERS);
    current_prover_id = 0;
    mem_set(credentials, 0, sizeof(CREDENTIAL)*NUM_CREDS);
    //setStaticHigh(blob_store, 0x00, sizeof(BLOB_STORE_ITEM)*MAX_NUMBER_OF_BLOBS); // TODO !!!
    mem_set(blob_catalog, 0x00, sizeof(BLOB_CATALOG_ITEM)*MAX_NUMBER_OF_BLOBS);
    mem_set(temp_key, 0, MAX_BIGINT_SIZE);

    mode = MODE_VIRGIN;
}


void handle_INS_SET_FAST_VIRGIN_MODE(){
    // TODO
}


void handle_INS_PIN_TRIALS_LEFT(){
    if (!mCheckCase(2))
        mExitSW(ERR_BAD_ISO);

    if (mode == MODE_VIRGIN)
        mExitSW(ERR_BAD_MODE);

    apdu_data.pin_trials = pin_trials;
    mExitLa(1);
}


void handle_INS_PUK_TRIALS_LEFT(){
    if (!mCheckCase(2))
        mExitSW(ERR_BAD_ISO);

    if (mode == MODE_VIRGIN)
        mExitSW(ERR_BAD_MODE);

    apdu_data.puk_trials = puk_trials;
    mExitLa(1);

}


void handle_INS_CHANGE_PIN(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != (PIN_SIZE<<1))
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE<<1));

    checkPin(apdu_data.old_pin_and_new_pin);

    mem_cpy(pin, apdu_data.old_pin_and_new_pin + PIN_SIZE, PIN_SIZE);

    pin_trials = MAX_PIN_TRIALS;
}


void handle_INS_RESET_PIN(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING && mode != MODE_LOCKED)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PUK_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + PUK_SIZE));

    checkPuk(apdu_data.puk_and_pin);

    mem_cpy(pin, apdu_data.puk_and_pin + PUK_SIZE, PIN_SIZE);

    pin_trials = MAX_PIN_TRIALS;

    mode = MODE_WORKING;
}


void handle_INS_INITIALIZE_DEVICE(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != ID_SIZE + SIZE_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (ID_SIZE + SIZE_SIZE));

    mem_cpy(device_id, apdu_data.id_and_size, ID_SIZE);

    temp_size = sizeDecode(apdu_data.id_and_size + ID_SIZE);

    if (temp_size < MIN_X_SIZE)
        mExitSW(ERR_DEVICE_KEY_SHORTER_THAN_MIN_X_SIZE);

    if (temp_size > MAX_SMALLINT_SIZE)
        mExitSW(ERR_INTEGER_EXCEEDS_MAXINTSIZE);

    x_size = temp_size;

#ifdef TEST_MODE
    mem_cpy(device_key+MAX_SMALLINT_SIZE-temp_size, test_device_key, temp_size);
      mem_cpy(pin, test_pin, PIN_SIZE);
      mem_cpy(puk, test_puk, PUK_SIZE);
#else
    getRandomBytes(device_key+MAX_SMALLINT_SIZE-temp_size, temp_size);
    getRandomBytes(temp_buffer, PIN_SIZE+PUK_SIZE);
    for (i = 0; i < PUK_SIZE; i++) {
        puk[i] = 0x30 + (temp_buffer[i] % 10);
    }
    for (i = 0; i < PIN_SIZE; i++) {
        pin[i] = 0x30 + (temp_buffer[i+PUK_SIZE] % 10);
    }
#endif

    getKey(temp_key, &temp_key_size, 0);

    mem_cpy(temp_buffer         , pin, PIN_SIZE);
    mem_cpy(temp_buffer+PIN_SIZE, puk, PUK_SIZE);
    temp_buffer_size = PIN_SIZE + PUK_SIZE;

    publicKeyEncrypt(temp_key, temp_key_size);

    mem_set(&temp_key, 0, MAX_BIGINT_SIZE);

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_DEVICE_ID(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    mem_cpy(apdu_data.device_id, device_id, ID_SIZE);

    mExitLa(ID_SIZE);
}


void handle_INS_GET_VERSION(){
    if (!mCheckCase(2))
        mExitSW(ERR_BAD_ISO);

    mem_cpy(apdu_data.version, version, 64);

    mExitLa(64);

}


void handle_INS_PUT_DATA(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc == 0)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA ^ 0x01);

    if (Lc > BUFFER_MAX_SIZE)
        buffer_size = BUFFER_MAX_SIZE;
    else
        buffer_size = Lc;

    mem_cpy(buffer, apdu_data.buffer, buffer_size);

}


void handle_INS_GET_CHALLENGE(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (Lc != 1)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ 1);

    challenge_size = (unsigned int)apdu_data.challenge_size;

    if (!challenge_size)
        challenge_size = CHALLENGE_MAX_SIZE;

#ifdef TEST_MODE
    mem_set(mem_session.challenge, 0xaa, challenge_size);
#else
    getRandomBytes(mem_session.challenge, challenge_size);
#endif

    if (challenge_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.challenge, mem_session.challenge, challenge_size);
        mExitLa(challenge_size);
    } else {
        remaining_position = mem_session.challenge;
        remaining_size = challenge_size;
        output_large_data();
    }

}


void handle_INS_AUTHENTICATE_DATA(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != 1)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ 1);

    getKey(temp_key, &temp_key_size, apdu_data.keyId);

    authData = 0;

    extract(temp_key, temp_key_size);

    authData = 1;

    authKeyId = apdu_data.keyId;

    mem_set(&temp_key, 0, MAX_BIGINT_SIZE);

}


void handle_INS_SET_AUTHENTICATION_KEY(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != 1)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ 1);

    if (apdu_data.keyId >= NUM_AUTH_KEYS)
        mExitSW(ERR_KEY_ID_OUTSIDE_RANGE);

    if (mode == MODE_WORKING)
        checkBufferPrefix(INS_SET_AUTHENTICATION_KEY, &apdu_data.keyId, 1);

    if (buffer_size < 55)
        mExitSW(ERR_AUTHENTICATION_KEY_TOO_SHORT);

    if (buffer_size > MAX_BIGINT_SIZE)
        mExitSW(ERR_INTEGER_EXCEEDS_MAXINTSIZE);

    mem_cpy(auth_keys[apdu_data.keyId], buffer, buffer_size);
    auth_keys_sizes[apdu_data.keyId] = buffer_size;

    buffer_size = 0;

}


void handle_INS_LIST_AUTHENTICATION_KEYS(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    temp_size = 0; // size of temp_buffer
    for (authKeyId=0; authKeyId < NUM_ISSUERS; authKeyId++) {
        if (auth_keys_sizes[authKeyId]) {
            mem_cpy(temp_buffer + temp_size, &authKeyId, 1);
            mem_cpy(temp_buffer + temp_size + 1, &(auth_keys_sizes[authKeyId]), 2);
            temp_size = temp_size + 3;
        }
    }

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }

}


void handle_INS_READ_AUTHENTICATION_KEY(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + KEY_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + KEY_ID_SIZE));

    checkPin(apdu_data.read_authentication_key.pin);

    getKey(temp_buffer, &temp_size, apdu_data.read_authentication_key.keyId);

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.auth_key, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }

}


void handle_INS_REMOVE_AUTHENTICATION_KEY(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != KEY_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ KEY_ID_SIZE);

    if (apdu_data.keyId >= NUM_AUTH_KEYS)
        mExitSW(ERR_KEY_ID_OUTSIDE_RANGE);

    if (!auth_keys_sizes[apdu_data.keyId])
        mExitSW(ERR_AUTHENTICATION_KEY_DOES_NOT_EXIST);

    if (mode == MODE_WORKING)
        checkBufferEqual(INS_REMOVE_AUTHENTICATION_KEY, &(apdu_data.keyId), KEY_ID_SIZE);

    mem_set(auth_keys[apdu_data.keyId], 0x00, auth_keys_sizes[apdu_data.keyId]);
    auth_keys_sizes[apdu_data.keyId] = 0;

}


void handle_INS_SET_GROUP_COMPONENT(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != GROUP_ID_SIZE + COMPTYPE_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (GROUP_ID_SIZE + COMPTYPE_SIZE));

    if (apdu_data.set_group_component.group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);

    if (apdu_data.set_group_component.comptype > 2)
        mExitSW(ERR_COMPONENT_TYPE_OUTSIDE_OF_RANGE);

    if (mode == MODE_WORKING)
        checkBufferPrefix(INS_SET_GROUP_COMPONENT, &apdu_data.set_group_component.group_id, 2); // trick to get group_id || comptype

    if (buffer_size > MAX_BIGINT_SIZE)
        mExitSW(ERR_INTEGER_EXCEEDS_MAXINTSIZE);

    switch(apdu_data.set_group_component.comptype) {
        case 0:
            mem_set(groups[apdu_data.set_group_component.group_id].modulus, 0, MAX_BIGINT_SIZE-buffer_size);
            mem_cpy(groups[apdu_data.set_group_component.group_id].modulus+(MAX_BIGINT_SIZE-buffer_size), buffer, buffer_size); // put the buffer data on the right-most bytes of modulus
            groups[apdu_data.set_group_component.group_id].modulus_size = buffer_size;
            break;
        case 1:
            if (buffer_size > MAX_SMALLINT_SIZE)
                mExitSW(ERR_INTEGER_EXCEEDS_MAXINTSIZE);
            mem_cpy(groups[apdu_data.set_group_component.group_id].q+(MAX_SMALLINT_SIZE-buffer_size), buffer, buffer_size);
            groups[apdu_data.set_group_component.group_id].q_size = buffer_size;
            break;
        case 2:
            mem_cpy(groups[apdu_data.set_group_component.group_id].f+(MAX_BIGINT_SIZE-buffer_size), buffer, buffer_size);
            groups[apdu_data.set_group_component.group_id].f_size = buffer_size;
            break;
        default:
            break;
    }

}


void handle_INS_SET_GENERATOR(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != GROUP_ID_SIZE + GEN_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (GROUP_ID_SIZE + GEN_ID_SIZE));

    temp_group_id = apdu_data.set_generator.group_id;
    temp_gen_id   = apdu_data.set_generator.genId;

    if (temp_group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);

    if (temp_gen_id == 0 || temp_gen_id > NUM_GEN)
        mExitSW(ERR_ID_OF_GROUP_GENERATOR_OUTSIDE_OF_RANGE);

    if (mode == 2)
        checkBufferPrefix(INS_SET_GENERATOR, &apdu_data.set_generator.group_id, 2); // trick to get group_id || genId

    if (buffer_size > MAX_BIGINT_SIZE)
        mExitSW(ERR_INTEGER_EXCEEDS_MAXINTSIZE);

    mem_cpy(groups[temp_group_id].g[temp_gen_id-1]+(MAX_BIGINT_SIZE-buffer_size), buffer, buffer_size); // align the buffer data to the right-most bytes of g[]
    if (groups[temp_group_id].g_size[temp_gen_id-1] == 0) {
        groups[temp_group_id].num_generators += 1;
    }
    groups[temp_group_id].g_size[temp_gen_id-1] = buffer_size;

}


void handle_INS_LIST_GROUPS(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    temp_size = 0; // size of dataout
    for (temp_group_id = 0; temp_group_id < NUM_GROUPS; temp_group_id++)
        if (groupExists(temp_group_id)) {
            mem_cpy(temp_buffer + temp_size, &temp_group_id, 1);
            temp_size++;
        }

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }

}


void handle_INS_READ_GROUP(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + GROUP_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + GROUP_ID_SIZE));

    checkPin(apdu_data.read_group_in.pin);

    temp_group_id = apdu_data.read_group_in.group_id;

    if (temp_group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);

    if (!groupExists(temp_group_id))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    temp_size = 0;

    getGroupComponent(temp_group_id, 0x00);
    mem_cpy(temp_buffer+temp_size, &buffer_size, SIZE_SIZE);
    temp_size += SIZE_SIZE;

    getGroupComponent(temp_group_id, 0x01);
    mem_cpy(temp_buffer+temp_size, &buffer_size, SIZE_SIZE);
    temp_size += SIZE_SIZE;

    getGroupComponent(temp_group_id, 0x02);
    mem_cpy(temp_buffer+temp_size, &buffer_size, SIZE_SIZE);
    temp_size += SIZE_SIZE;

    getGroupComponent(temp_group_id, 0x03);
    mem_cpy(temp_buffer+temp_size, buffer, buffer_size);
    temp_size += 1;

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }

}


void handle_INS_READ_GROUP_COMPONENT(){

    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + GROUP_ID_SIZE + COMPTYPE_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + GROUP_ID_SIZE + COMPTYPE_SIZE));

    checkPin(apdu_data.read_group_component_in.pin);

    if (apdu_data.read_group_component_in.group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);

    if (!groupExists(apdu_data.read_group_component_in.group_id))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    if (apdu_data.read_group_component_in.comptype > 3)
        mExitSW(ERR_COMPONENT_TYPE_OUTSIDE_OF_RANGE);

    getGroupComponent(apdu_data.read_group_component_in.group_id, apdu_data.read_group_component_in.comptype);

    if (buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, buffer, buffer_size);
        mExitLa(buffer_size);
    } else {
        remaining_position = buffer;
        remaining_size = buffer_size;
        output_large_data();
    }


}


void handle_INS_READ_GENERATOR(){

    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + GROUP_ID_SIZE + GEN_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + GROUP_ID_SIZE + GEN_ID_SIZE));

    checkPin(apdu_data.read_generator_in.pin);

    if (apdu_data.read_generator_in.group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);

    if (!groupExists(apdu_data.read_generator_in.group_id))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    getGenerator(apdu_data.read_generator_in.group_id, apdu_data.read_generator_in.gen_id); // temp_size holds the true size of the generator
    temp_size = buffer_size;

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, buffer+MAX_BIGINT_SIZE-temp_size, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = buffer+MAX_BIGINT_SIZE-temp_size;
        remaining_size = temp_size;
        output_large_data();
    }

}


void handle_INS_REMOVE_GROUP(){

    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != GROUP_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ GROUP_ID_SIZE);

    if (apdu_data.group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);

    if (!groupExists(apdu_data.group_id))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    if (mode == MODE_WORKING)
        checkBufferPrefix(INS_REMOVE_GROUP, &apdu_data.group_id, GROUP_ID_SIZE);

    groups[apdu_data.group_id].modulus_size = 0;
    groups[apdu_data.group_id].q_size = 0;
    groups[apdu_data.group_id].f_size = 0;
    for (i=0; i<NUM_GEN; i++)
        groups[apdu_data.group_id].g_size[i] = 0;
    groups[apdu_data.group_id].num_generators = 0;

}


void handle_INS_SET_COUNTER(){
#if NUM_COUNTERS > 0

    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != 4 + CURSOR_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (4 + CURSOR_SIZE));

    if ( (apdu_data.set_counter.counter_id < 1) || (apdu_data.set_counter.counter_id > NUM_COUNTERS) )
        mExitSW(ERR_COUNTER_ID_OUTSIDE_OF_RANGE);

    if (apdu_data.set_counter.key_id > NUM_ISSUERS)
        mExitSW(ERR_KEY_ID_OUTSIDE_RANGE);

    if (mode == MODE_WORKING)
        checkBufferEqual(INS_SET_COUNTER, &(apdu_data.set_counter.counter_id), 4+CURSOR_SIZE); // trick to get counter_id||key_id||...

    temp_counter_id = apdu_data.set_counter.counter_id;

    mem_cpy(&(counters[temp_counter_id-1]), &(apdu_data.set_counter.counter_id), 4 + CURSOR_SIZE); // this sets counter_id, key_id, index, threshold,cursor, all at once
    counters[temp_counter_id-1].exists = 1;

#endif
}


void handle_INS_INCREMENT_COUNTER(){
#if NUM_COUNTERS > 0

    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc < 56)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA ^ 0x38);

    temp_key_id = apdu_data.increment_counter.key_id;

    mem_cpy(buffer, apdu_data.increment_counter.sig, Lc-1);
    buffer_size = Lc-1;

    getKey(temp_key, &temp_key_size, temp_key_id);

    extract(temp_key, temp_key_size);

    if (buffer_size != 5)
        mExitSW(ERR_DATA_AUTHENTICATION_FAILURE);

    temp_counter_id = buffer[0];
    mem_cpy(mem_session.small_buffer, buffer+1, CURSOR_SIZE);

    if (temp_counter_id < 1 || temp_counter_id > NUM_COUNTERS)
        mExitSW(ERR_COUNTER_ID_OUTSIDE_OF_RANGE);

    if (!counters[temp_counter_id-1].exists)
        mExitSW(ERR_COUNTER_DOES_NOT_EXIST);

    if (temp_key_id != counters[temp_counter_id-1].key_id)
        mExitSW(ERR_DATA_AUTHENTICATION_FAILURE);

    if (mem_cmp(mem_session.small_buffer,counters[temp_counter_id-1].cursor, CURSOR_SIZE) > 0) {
        mem_cpy(counters[temp_counter_id-1].cursor, mem_session.small_buffer, CURSOR_SIZE);
        counters[temp_counter_id-1].index += 1;
    }

    mem_set(&temp_key, 0, MAX_BIGINT_SIZE);

#endif
}


void handle_INS_LIST_COUNTERS(){
#if NUM_COUNTERS > 0

    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    temp_size = 0;

    for (temp_counter_id = 1; temp_counter_id <= NUM_COUNTERS; temp_counter_id++) {
        if (counters[temp_counter_id-1].exists) {
            temp_buffer[temp_size] = temp_counter_id;
            temp_size++;
        }
    }

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }

#endif
}


void handle_INS_READ_COUNTER(){
#if NUM_COUNTERS > 0

    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + COUNTER_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + COUNTER_ID_SIZE));

    checkPin(apdu_data.read_counter_in.pin);

    temp_counter_id = apdu_data.read_counter_in.counter_id;

    if (temp_counter_id < 1 || temp_counter_id > NUM_COUNTERS)
        mExitSW(ERR_COUNTER_ID_OUTSIDE_OF_RANGE);

    if (!counters[temp_counter_id-1].exists)
        mExitSW(ERR_COUNTER_DOES_NOT_EXIST);

    mem_cpy(apdu_data.dataout, &(counters[temp_counter_id-1].key_id), 3 + CURSOR_SIZE); // get key_id || index || ...

    mExitLa(3 + CURSOR_SIZE);

#endif
}


void handle_INS_REMOVE_COUNTER(){
#if NUM_COUNTERS > 0
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != COUNTER_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ COUNTER_ID_SIZE);

    temp_counter_id = apdu_data.counter_id;

    if (temp_counter_id < 1 || temp_counter_id > NUM_COUNTERS)
        mExitSW(ERR_COUNTER_ID_OUTSIDE_OF_RANGE);

    if (!counters[temp_counter_id-1].exists)
        mExitSW(ERR_COUNTER_DOES_NOT_EXIST);

    if (mode == MODE_WORKING)
        checkBufferEqual(INS_REMOVE_COUNTER, &temp_counter_id, COUNTER_ID_SIZE);

    mem_set(&(counters[temp_counter_id-1].counter_id), 0, 5+CURSOR_SIZE); // also set 'exists' to 0

#endif
}


void handle_INS_SET_ISSUER(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != 6)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ 6);

    temp_issuer_id = apdu_data.set_issuer_in.issuer_id;

    if (temp_issuer_id < 1 || temp_issuer_id > NUM_ISSUERS)
        mExitSW(ERR_ISSUERID_OUTSIDE_OF_RANGE);

    if (apdu_data.set_issuer_in.group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);

    if (apdu_data.set_issuer_in.gen_id_1 < 1 || apdu_data.set_issuer_in.gen_id_1 > NUM_GEN || apdu_data.set_issuer_in.gen_id_2 > NUM_GEN)
        mExitSW(ERR_ID_OF_GROUP_GENERATOR_OUTSIDE_OF_RANGE);

    if (apdu_data.set_issuer_in.counter_id > NUM_COUNTERS)
        mExitSW(ERR_COUNTER_ID_OUTSIDE_OF_RANGE);

    if (mode == MODE_WORKING)
        checkBufferEqual(INS_SET_ISSUER, &(temp_issuer_id), 6); // get issuer_id||group_id||...

    mem_cpy(&(issuers[temp_issuer_id-1].issuer_id), &(apdu_data.set_issuer_in.issuer_id), 6);
    issuers[temp_issuer_id-1].exists = 1;

}


void handle_INS_LIST_ISSUERS(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    temp_size = 0;

    for (temp_issuer_id = 1; temp_issuer_id <= NUM_ISSUERS; temp_issuer_id++)
        if (issuers[temp_issuer_id-1].exists) {
            mem_cpy(temp_buffer + temp_size, &temp_issuer_id, 1);
            temp_size++;
        }

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }


}


void handle_INS_READ_ISSUER(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE+1)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE+1));

    checkPin(apdu_data.read_issuer_in.pin);

    temp_issuer_id = apdu_data.read_issuer_in.issuer_id;

    if (temp_issuer_id < 1 || temp_issuer_id > NUM_ISSUERS)
        mExitSW(ERR_ISSUERID_OUTSIDE_OF_RANGE);

    if (!issuers[temp_issuer_id-1].exists)
        mExitSW(ERR_ISSUER_DOES_NOT_EXIST);

    mem_cpy(apdu_data.dataout, &(issuers[temp_issuer_id-1].group_id), 5);

    mExitLa(5);

}


void handle_INS_REMOVE_ISSUER(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != 1)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ 1);

    temp_issuer_id = apdu_data.issuer_id;

    if (temp_issuer_id < 1 || temp_issuer_id > NUM_ISSUERS)
        mExitSW(ERR_ISSUERID_OUTSIDE_OF_RANGE);

    if (!issuers[temp_issuer_id-1].exists)
        mExitSW(ERR_ISSUER_DOES_NOT_EXIST);

    if (mode == MODE_WORKING)
        checkBufferEqual(INS_REMOVE_ISSUER, &temp_issuer_id, 1);

    mem_set(&(issuers[temp_issuer_id-1]), 0, 7); // also set 'exists' to 0

}


void handle_INS_SET_PROVER(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc < 5)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA  ^ 5);

    temp_prover_id = apdu_data.set_prover_in.prover_id;

    if (temp_prover_id < 1 || temp_prover_id > NUM_PROVERS)
        mExitSW(ERR_PROVERID_OUTSIDE_OF_RANGE);

    for (i=0; i < Lc-5; i++)
        if (apdu_data.set_prover_in.cred_ids[i] > NUM_CREDS)
            mExitSW(ERR_ONE_ID_OF_CREDIDS_IS_OUTSIDE_OF_RANGE);

    if (mode == MODE_WORKING)
        checkBufferEqual(INS_SET_PROVER, &(apdu_data.set_prover_in.prover_id), Lc);

    mem_cpy(&(provers[temp_prover_id-1].prover_id), &(apdu_data.set_prover_in.prover_id), 5); // under the hood, this also initializes ksize and csize
    mem_set(&(provers[temp_prover_id-1].kx), 0, MAX_SMALLINT_SIZE);
    mem_set(&(provers[temp_prover_id-1].c), 0, HASH_SIZE);
    mem_set(&(provers[temp_prover_id-1].proofsession), 0, PROOFSESSION_SIZE);
    provers[temp_prover_id-1].proofstatus = 0;
    provers[temp_prover_id-1].cred_ids_size = Lc-5;
    mem_cpy(provers[temp_prover_id-1].cred_ids, apdu_data.set_prover_in.cred_ids, Lc-5);
    provers[temp_prover_id-1].exists = 1;

}


void handle_INS_READ_PROVER(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PROVER_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ (PIN_SIZE + PROVER_ID_SIZE));

    checkPin(apdu_data.read_prover_in.pin);

    temp_prover_id = apdu_data.read_prover_in.prover_id;

    if (temp_prover_id < 1 || temp_prover_id > NUM_PROVERS)
        mExitSW(ERR_PROVERID_OUTSIDE_OF_RANGE);

    if (!provers[temp_prover_id-1].exists)
        mExitSW(ERR_PROVER_DOES_NOT_EXIST);

    mem_cpy(temp_buffer, &(provers[temp_prover_id-1].ksize), 4); // copy ksize || csize
    mem_cpy(temp_buffer+4, &(provers[temp_prover_id-1].proofsession), PROOFSESSION_SIZE + 1 + provers[temp_prover_id-1].cred_ids_size); // proofsession || proofstatus || cred_ids

    temp_size = 5 + PROOFSESSION_SIZE + provers[temp_prover_id-1].cred_ids_size;

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }


}


void handle_INS_REMOVE_PROVER(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PROVER_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ PROVER_ID_SIZE);

    temp_prover_id = apdu_data.prover_id;

    if (temp_prover_id < 1 || temp_prover_id > NUM_PROVERS)
        mExitSW(ERR_PROVERID_OUTSIDE_OF_RANGE);

    if (!provers[temp_prover_id-1].exists)
        mExitSW(ERR_PROVER_DOES_NOT_EXIST);

    if (mode == 2)
        checkBufferEqual(INS_REMOVE_PROVER, &(temp_prover_id), 1);

    mem_set(&(provers[temp_prover_id-1]), 0, sizeof(PROVER));

}


void handle_INS_START_COMMITMENTS(){

#ifdef SODER
    if (!mCheckCase(4))
	    mExitSW(ERR_BAD_ISO);
#else
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);
#endif

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PROVER_ID_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ (PIN_SIZE + PROVER_ID_SIZE));

    checkPin(apdu_data.start_commitments_in.pin);

    temp_prover_id = apdu_data.start_commitments_in.prover_id;

    if (temp_prover_id < 1 || temp_prover_id > NUM_PROVERS)
        mExitSW(ERR_PROVERID_OUTSIDE_OF_RANGE);

    if (!provers[temp_prover_id-1].exists)
        mExitSW(ERR_PROVER_DOES_NOT_EXIST);

    mem_set(provers[temp_prover_id-1].kx, 0, MAX_SMALLINT_SIZE - provers[temp_prover_id-1].ksize); // put 0x00's on the left of kx

#ifdef TEST_MODE
    mem_set(provers[temp_prover_id-1].kx + MAX_SMALLINT_SIZE - provers[temp_prover_id-1].ksize, 0xaa, provers[temp_prover_id-1].ksize);
    mem_set(provers[temp_prover_id-1].proofsession, 0xaa, PROOFSESSION_SIZE);
#else
    getRandomBytes(provers[temp_prover_id-1].kx + MAX_SMALLINT_SIZE - provers[temp_prover_id-1].ksize, provers[temp_prover_id-1].ksize);
    getRandomBytes(provers[temp_prover_id-1].proofsession, PROOFSESSION_SIZE);
#endif
    provers[temp_prover_id-1].proofstatus = 1;

    current_prover_id = temp_prover_id;

    // For Patras 2, we do not use the proofsession

#ifdef SODER
    mem_cpy(apdu_data.proofsession, provers[temp_prover_id-1].proofsession, PROOFSESSION_SIZE);
    mExitLa(PROOFSESSION_SIZE);
#endif

}


void handle_INS_START_RESPONSES(){

#ifdef SODER

    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc < 6)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA  ^ 6);

    checkPin(apdu_data.start_responses_in.pin);

    temp_prover_id = apdu_data.start_responses_in.prover_id;

    if (temp_prover_id < 1 || temp_prover_id > NUM_PROVERS)
        mExitSW(ERR_PROVERID_OUTSIDE_OF_RANGE);

    if (!provers[temp_prover_id-1].exists)
        mExitSW(ERR_PROVER_DOES_NOT_EXIST);

    if (current_prover_id != temp_prover_id)
        mExitSW(ERR_PROOF_SESSION_CANNOT_START);

    if (provers[temp_prover_id-1].proofstatus != 1)
        mExitSW(ERR_PROOF_SESSION_CANNOT_START);

    d = apdu_data.start_responses_in.input[0];

    if(Lc-6 < (d * 16))
        mExitSW(ERR_MALICIOUS_INPUT_RESPONSE_STAGE);

    BOOL exit = 1;
    for (i=0; i<d; i++) {
        if (mem_cmp(provers[temp_prover_id-1].proofsession, &(apdu_data.start_responses_in.input[1]) + (16*i), PROOFSESSION_SIZE) == 0) {
            exit = 0;
            break;
        }
    }
    if (exit)
        mExitSW(ERR_MALICIOUS_INPUT_RESPONSE_STAGE);

    if (P1 == 0x00) {

        // for idemix
        mSecureHash(Lc-PIN_SIZE-1, 32, temp_buffer, apdu_data.start_responses_in.input);

    } else {

        // for uprove

        temp_size = 0;
        mem_cpy(temp_buffer, &temp_size, 2);                                                   // tem_buffer = 0x00 || 0x00
        temp_size = 1+16*d;
        mem_cpy(temp_buffer+2, &temp_size, 2);                                                 // tem_buffer = 0x00 || 0x00 || 1+16d over 2 bytes
        mem_cpy(temp_buffer+4, apdu_data.start_responses_in.input, 1+16*d);                    // tem_buffer = 0x00 || 0x00 || 1+16d over 2 bytes || d || ps_1 || ... || ps_d
        temp_size = 0;
        mem_cpy(temp_buffer+4+1+16*d, &temp_size, 2);                                          // tem_buffer = 0x00 || 0x00 || 1+16d over 2 bytes || d || ps_1 || ... || ps_d || 0x00 || 0x00
        temp_size = (Lc-5)-(1+16*d); // temp_size = size(h)
        mem_cpy(temp_buffer+6+1+16*d, &temp_size, 2);                                          // tem_buffer = 0x00 || 0x00 || 1+16d over 2 bytes || d || ps_1 || ... || ps_d || 0x00 || 0x00 || size(h) over 2 bytes
        mem_cpy(temp_buffer+8+1+16*d, apdu_data.start_responses_in.input+(1+16*d), temp_size); // tem_buffer = 0x00 || 0x00 || 1+16d over 2 bytes || d || ps_1 || ... || ps_d || 0x00 || 0x00 || size(h) over 2 bytes || h

        mSecureHash(8+1+16*d+temp_size, 32, temp_buffer, temp_buffer);

    }
    mem_set(provers[temp_prover_id-1].c, 0, HASH_SIZE);
    mem_cpy(provers[temp_prover_id-1].c+HASH_SIZE-provers[temp_prover_id-1].csize, temp_buffer, provers[temp_prover_id-1].csize);

    provers[temp_prover_id-1].proofstatus = 2;

#else

    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc < 6)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA ^ 6);

    checkPin(apdu_data.start_responses_in.pin);

    temp_prover_id = apdu_data.start_responses_in.prover_id;

    if (temp_prover_id < 1 || temp_prover_id > NUM_PROVERS)
        mExitSW(ERR_PROVERID_OUTSIDE_OF_RANGE);

    if (!provers[temp_prover_id-1].exists)
        mExitSW(ERR_PROVER_DOES_NOT_EXIST);

    if (current_prover_id != temp_prover_id)
        mExitSW(ERR_PROOF_SESSION_CANNOT_START);

    if (provers[temp_prover_id-1].proofstatus != 1)
        mExitSW(ERR_PROOF_SESSION_CANNOT_START);

    if((Lc-PIN_SIZE-1) != provers[temp_prover_id-1].csize)
        mExitSW(ERR_MALICIOUS_INPUT_RESPONSE_STAGE);

    mem_cpy(temp_buffer, apdu_data.start_responses_in.input, provers[temp_prover_id-1].csize);

    mem_set(provers[temp_prover_id-1].c, 0, HASH_SIZE);
    mem_cpy(provers[temp_prover_id-1].c+HASH_SIZE-provers[temp_prover_id-1].csize, temp_buffer, provers[temp_prover_id-1].csize);

    provers[temp_prover_id-1].proofstatus = 2;

#endif

}


void handle_INS_SET_CREDENTIAL(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + 2)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ (PIN_SIZE + 2));

    checkPin(apdu_data.set_credential_in.pin);

    temp_credential_id = apdu_data.set_credential_in.credential_id;

    if (temp_credential_id < 1 || temp_credential_id > NUM_CREDS)
        mExitSW(ERR_CREDENTIALID_OUTSIDE_OF_RANGE);

    temp_issuer_id = apdu_data.set_credential_in.issuer_id;

    if (temp_issuer_id < 1 || temp_issuer_id > NUM_ISSUERS)
        mExitSW(ERR_ISSUERID_OUTSIDE_OF_RANGE);

    if (!issuers[temp_issuer_id-1].exists)
        mExitSW(ERR_ISSUER_DOES_NOT_EXIST);

    credentials[temp_credential_id-1].credential_id = temp_credential_id;
    credentials[temp_credential_id-1].issuer_id = temp_issuer_id;
    mem_set(credentials[temp_credential_id-1].v, 0, MAX_SMALLINT_SIZE-x_size);
#ifdef TEST_MODE
    mem_set(credentials[temp_credential_id-1].v+MAX_SMALLINT_SIZE-x_size, 0xaa, x_size);
#else
    getRandomBytes(credentials[temp_credential_id-1].v+MAX_SMALLINT_SIZE-x_size, x_size);
#endif
    credentials[temp_credential_id-1].v_size = x_size;

    mem_set(credentials[temp_credential_id-1].kv, 0, MAX_SMALLINT_SIZE);
    credentials[temp_credential_id-1].kv_size = 0;
    credentials[temp_credential_id-1].status = 0;
    credentials[temp_credential_id-1].prescount = 0;
    credentials[temp_credential_id-1].exists = 1;

}


void handle_INS_LIST_CREDENTIALS(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    temp_size = 0;

    for (temp_credential_id = 1; temp_credential_id < NUM_CREDS; temp_credential_id++)
        if (credentials[temp_credential_id-1].exists) {
            temp_buffer[temp_size] = temp_credential_id;
            temp_size++;
        }

    if (temp_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_size);
        mExitLa(temp_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_size;
        output_large_data();
    }

}


void handle_INS_READ_CREDENTIAL(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    temp_credential_id = accessCredential(apdu_data.pin_and_credential_id.pin, apdu_data.pin_and_credential_id.credential_id);

    apdu_data.dataout[0] = credentials[temp_credential_id-1].issuer_id;
    mem_cpy(apdu_data.dataout+1, &(credentials[temp_credential_id-1].v_size), 2);
    mem_cpy(apdu_data.dataout+3, &(credentials[temp_credential_id-1].kv_size), 2);
    mem_cpy(apdu_data.dataout+5, &(credentials[temp_credential_id-1].status), 2); // status || prescount

    mExitLa(7);

}


void handle_INS_REMOVE_CREDENTIAL(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    temp_credential_id = accessCredential(apdu_data.pin_and_credential_id.pin, apdu_data.pin_and_credential_id.credential_id);

    mem_set(&(credentials[temp_credential_id-1].credential_id), 0, sizeof(CREDENTIAL));

}


void handle_INS_GET_CREDENTIAL_PUBLIC_KEY(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    temp_credential_id = accessCredential(apdu_data.pin_and_credential_id.pin, apdu_data.pin_and_credential_id.credential_id);

    temp_issuer_id = credentials[temp_credential_id-1].issuer_id;

    singleOrDoubleExpo(temp_issuer_id, device_key, x_size, credentials[temp_credential_id-1].v, credentials[temp_credential_id-1].v_size);

    if (buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, buffer+MAX_BIGINT_SIZE-buffer_size, buffer_size);
        mExitLa(buffer_size);
    } else {
        remaining_position = buffer+MAX_BIGINT_SIZE-buffer_size;
        remaining_size = buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_ISSUANCE_COMMITMENT(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    temp_credential_id = accessCredential(apdu_data.pin_and_credential_id.pin, apdu_data.pin_and_credential_id.credential_id);

    temp_issuer_id = credentials[temp_credential_id-1].issuer_id;
    temp_status = credentials[temp_credential_id-1].status;

    if (temp_status != 0)
        mExitSW(ERR_CREDENTIAL_INAP_STATE);

    accessSession(temp_credential_id);

    if (provers[current_prover_id-1].proofstatus != 1)
        mExitSW(ERR_CURRENT_PROOF_SESSION_INAP_STAGE);

    mem_set(temp_key, 0, MAX_BIGINT_SIZE-provers[current_prover_id-1].ksize);
#ifdef TEST_MODE
    mem_set(temp_key + MAX_BIGINT_SIZE-provers[current_prover_id-1].ksize, 0xbb, provers[current_prover_id-1].ksize);
#else
    getRandomBytes(temp_key + MAX_BIGINT_SIZE-provers[current_prover_id-1].ksize, provers[current_prover_id-1].ksize);
#endif
    temp_key_size = provers[current_prover_id-1].ksize;

    singleOrDoubleExpo(temp_issuer_id, provers[current_prover_id-1].kx, provers[current_prover_id-1].ksize, temp_key+MAX_BIGINT_SIZE-MAX_SMALLINT_SIZE, provers[current_prover_id-1].ksize);

    credentials[temp_credential_id-1].status = 1;
    mem_cpy(credentials[temp_credential_id-1].kv, temp_key+MAX_BIGINT_SIZE-MAX_SMALLINT_SIZE, MAX_SMALLINT_SIZE);
    credentials[temp_credential_id-1].kv_size = temp_key_size;

    mem_set(&temp_key, 0, MAX_BIGINT_SIZE);


    if (buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, buffer+MAX_BIGINT_SIZE-buffer_size, buffer_size);
        mExitLa(buffer_size);
    } else {
        remaining_position = buffer+MAX_BIGINT_SIZE-buffer_size;
        remaining_size = buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_ISSUANCE_RESPONSE(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    temp_credential_id = accessCredential(apdu_data.pin_and_credential_id.pin, apdu_data.pin_and_credential_id.credential_id);

    temp_issuer_id = credentials[temp_credential_id-1].issuer_id;
    temp_status = credentials[temp_credential_id-1].status;

    if (temp_status != 1)
        mExitSW(ERR_CREDENTIAL_INAP_STATE);

    accessSession(temp_credential_id);

    if (provers[current_prover_id-1].proofstatus != 2)
        mExitSW(ERR_CURRENT_PROOF_SESSION_INAP_STAGE);

    singleOrDoubleResponse(temp_issuer_id,
                           provers[current_prover_id-1].c, provers[current_prover_id-1].csize,
                           device_key, x_size,
                           provers[current_prover_id-1].kx, provers[current_prover_id-1].ksize,
                           credentials[temp_credential_id-1].v, credentials[temp_credential_id-1].v_size,
                           credentials[temp_credential_id-1].kv, provers[current_prover_id-1].ksize);

    credentials[temp_credential_id-1].status = 2;

    if (buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, buffer, buffer_size);
        mExitLa(buffer_size);
    } else {
        remaining_position = buffer;
        remaining_size = buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_PRESENTATION_COMMITMENT(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    temp_credential_id = accessCredential(apdu_data.pin_and_credential_id.pin, apdu_data.pin_and_credential_id.credential_id);

    temp_issuer_id = credentials[temp_credential_id-1].issuer_id;
    temp_status = credentials[temp_credential_id-1].status;

    if (temp_status != 2)
        mExitSW(ERR_CREDENTIAL_INAP_STATE);

    accessSession(temp_credential_id);

    if (provers[current_prover_id-1].proofstatus != 1)
        mExitSW(ERR_CURRENT_PROOF_SESSION_INAP_STAGE);

    if (temp_issuer_id < 1 || temp_issuer_id > NUM_ISSUERS)
        mExitSW(ERR_ISSUERID_OUTSIDE_OF_RANGE);

    if (!issuers[temp_issuer_id-1].exists)
        mExitSW(ERR_ISSUER_DOES_NOT_EXIST);

#if NUM_COUNTERS > 0
    temp_counter_id = issuers[temp_issuer_id-1].counter_id;

    if (temp_counter_id != 0) {

        if (temp_counter_id < 1 || temp_counter_id > NUM_COUNTERS)
            mExitSW(ERR_COUNTER_ID_OUTSIDE_OF_RANGE);

        if (!counters[temp_counter_id-1].exists)
            mExitSW(ERR_COUNTER_DOES_NOT_EXIST);

        if (counters[temp_counter_id-1].index < counters[temp_counter_id-1].threshold)
            mExitSW(ERR_PRESENTATION_CRED_RESTRICTED_BY_IMM_COUNTER);

    }
#endif

    mem_set(temp_key, 0, MAX_BIGINT_SIZE-provers[current_prover_id-1].ksize);
#ifdef TEST_MODE
    mem_set(temp_key + MAX_BIGINT_SIZE-provers[current_prover_id-1].ksize, 0xaa, provers[current_prover_id-1].ksize);
#else
    getRandomBytes(temp_key + MAX_BIGINT_SIZE-provers[current_prover_id-1].ksize, provers[current_prover_id-1].ksize);
#endif

    singleOrDoubleExpo(temp_issuer_id, provers[current_prover_id-1].kx, provers[current_prover_id-1].ksize, temp_key+MAX_BIGINT_SIZE-MAX_SMALLINT_SIZE, provers[current_prover_id-1].ksize);

    mem_cpy(credentials[temp_credential_id-1].kv, temp_key+MAX_BIGINT_SIZE-MAX_SMALLINT_SIZE, MAX_SMALLINT_SIZE);
    credentials[temp_credential_id-1].status = 3;

    mem_set(&temp_key, 0, MAX_BIGINT_SIZE);

    if (buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, buffer+MAX_BIGINT_SIZE-buffer_size, buffer_size);
        mExitLa(buffer_size);
    } else {
        remaining_position = buffer+MAX_BIGINT_SIZE-buffer_size;
        remaining_size = buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_PRESENTATION_RESPONSE(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    temp_credential_id = accessCredential(apdu_data.pin_and_credential_id.pin, apdu_data.pin_and_credential_id.credential_id);

    temp_issuer_id = credentials[temp_credential_id-1].issuer_id;
    temp_status = credentials[temp_credential_id-1].status;

    if (temp_status != 3)
        mExitSW(ERR_CREDENTIAL_INAP_STATE);

    accessSession(temp_credential_id);

    if (provers[current_prover_id-1].proofstatus != 2)
        mExitSW(ERR_CURRENT_PROOF_SESSION_INAP_STAGE);

    singleOrDoubleResponse(temp_issuer_id,
                           provers[current_prover_id-1].c, provers[current_prover_id-1].csize,
                           device_key, x_size,
                           provers[current_prover_id-1].kx, provers[current_prover_id-1].ksize,
                           credentials[temp_credential_id-1].v, credentials[temp_credential_id-1].v_size,
                           credentials[temp_credential_id-1].kv, provers[current_prover_id-1].ksize);

    credentials[temp_credential_id-1].prescount += 1;

    if (issuers[temp_issuer_id-1].numpres == 0 || credentials[temp_credential_id-1].prescount < issuers[temp_issuer_id-1].numpres)
        credentials[temp_credential_id-1].status = 2;
    else
        credentials[temp_credential_id-1].status = 4;

    if (buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, buffer, buffer_size);
        mExitLa(buffer_size);
    } else {
        remaining_position = buffer;
        remaining_size = buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_DEVICE_PUBLIC_KEY(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    if (!groupExists(0))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    getGenerator(0, 1);
    temp_gen_1_size = buffer_size;

    // void multosModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
    if (temp_gen_1_size >= groups[0].modulus_size)
        mModularReduction (temp_gen_1_size, groups[0].modulus_size, buffer+MAX_BIGINT_SIZE-temp_gen_1_size, groups[0].modulus+MAX_BIGINT_SIZE-groups[0].modulus_size);

    // We have that temp_gen_1_size <= modulus_size
    // void crxModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output);
    mModularExponentiation (x_size,
                            groups[0].modulus_size,
                            device_key+MAX_SMALLINT_SIZE-x_size,
                            groups[0].modulus+MAX_BIGINT_SIZE-groups[0].modulus_size,
                            buffer+MAX_BIGINT_SIZE-groups[0].modulus_size, // ON POURRAIT METTRE buffer+MAX_BIGINT_SIZE-temp_gen_1_size ????? Bog, la fonction considere que tout est de taille du modulus
                            temp_buffer);
    temp_buffer_size = groups[0].modulus_size;

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_DEVICE_COMMITMENT(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc < PIN_SIZE)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA  ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    accessSession(0);

    // fetch provers[current_prover_id-1].kx, provers[current_prover_id-1].proofstatus

    if (provers[current_prover_id-1].proofstatus != 1)
        mExitSW(ERR_CURRENT_PROOF_SESSION_INAP_STAGE);

    if (!groupExists(0))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    // fetch groups[0].modulus

    getGenerator(0, 1);

    // void multosModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
    if (buffer_size >= groups[0].modulus_size) {
        mModularReduction (buffer_size, groups[0].modulus_size, buffer+MAX_BIGINT_SIZE-buffer_size, groups[0].modulus+MAX_BIGINT_SIZE-groups[0].modulus_size);
        buffer_size = groups[0].modulus_size;
    }

    // void crxModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output);
    mModularExponentiation (provers[current_prover_id-1].ksize,
                              groups[0].modulus_size,
                              provers[current_prover_id-1].kx+MAX_SMALLINT_SIZE-provers[current_prover_id-1].ksize,
                              groups[0].modulus+MAX_BIGINT_SIZE-groups[0].modulus_size,
                              buffer+MAX_BIGINT_SIZE-groups[0].modulus_size,
                              temp_buffer);
    temp_buffer_size = groups[0].modulus_size;

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_DEVICE_RESPONSE(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ PIN_SIZE);

    checkPin(apdu_data.pin);

    accessSession(0);

    // fetch provers[current_prover_id-1].kx, provers[current_prover_id-1].c, provers[current_prover_id-1].proofstatus

    if (provers[current_prover_id-1].proofstatus != 2)
        mExitSW(ERR_CURRENT_PROOF_SESSION_INAP_STAGE);

    if (!groupExists(0))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    // fetch groups[0].q

    singleResponse(provers[current_prover_id-1].kx, provers[current_prover_id-1].ksize,
                   provers[current_prover_id-1].c, provers[current_prover_id-1].csize,
                   device_key, x_size,
                   groups[0].q, groups[0].q_size, 0);

    if (buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, buffer, buffer_size);
        mExitLa(buffer_size);
    } else {
        remaining_position = buffer;
        remaining_size = buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_SCOPE_EXCLUSIVE_PSEUDONYM(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc < PIN_SIZE + 1)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA  ^ (PIN_SIZE + 1));

    checkPin(apdu_data.get_scope_exclusive_pseudonym_in.pin);

    if (!groupExists(0))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    // fetch groups[0].modulus, groups[0].f

    scopeExclusiveGenerator(apdu_data.get_scope_exclusive_pseudonym_in.scope, Lc-PIN_SIZE, groups[0].modulus, groups[0].modulus_size, groups[0].f, groups[0].f_size);

    if (buffer_size >= groups[0].modulus_size) {
        // void multosModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
        mModularReduction (buffer_size, groups[0].modulus_size, buffer+MAX_BIGINT_SIZE-buffer_size, groups[0].modulus+MAX_BIGINT_SIZE-groups[0].modulus_size);
        buffer_size = groups[0].modulus_size;
    }

    // void crxModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output);
    mModularExponentiation(x_size, groups[0].modulus_size, device_key+MAX_SMALLINT_SIZE-x_size, groups[0].modulus+MAX_BIGINT_SIZE-groups[0].modulus_size, buffer+MAX_BIGINT_SIZE-groups[0].modulus_size, temp_buffer);
    temp_buffer_size = groups[0].modulus_size;

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_SCOPE_EXCLUSIVE_COMMITMENT(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc < PIN_SIZE + 1)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA  ^ (PIN_SIZE + 1));

    checkPin(apdu_data.get_scope_exclusive_commitment_in.pin);

    accessSession(0);

    // fetch provers[current_prover_id-1].kx, provers[current_prover_id-1].proofstatus

    if (provers[current_prover_id-1].proofstatus != 1)
        mExitSW(ERR_CURRENT_PROOF_SESSION_INAP_STAGE);

    if (!groupExists(0))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    // fetch groups[0].modulus, groups[0].f

    scopeExclusiveGenerator(apdu_data.get_scope_exclusive_commitment_in.scope, Lc - PIN_SIZE, groups[0].modulus, groups[0].modulus_size, groups[0].f, groups[0].f_size);

    // void multosModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
    if (buffer_size >= groups[0].modulus_size) {
        mModularReduction (buffer_size, groups[0].modulus_size, buffer+MAX_BIGINT_SIZE-buffer_size, groups[0].modulus+MAX_BIGINT_SIZE-groups[0].modulus_size);
        buffer_size = groups[0].modulus_size;
    }

    // void crxModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output);
    mModularExponentiation (provers[current_prover_id-1].ksize,
                              groups[0].modulus_size,
                              provers[current_prover_id-1].kx+MAX_SMALLINT_SIZE-provers[current_prover_id-1].ksize,
                              groups[0].modulus+MAX_BIGINT_SIZE-groups[0].modulus_size,
                              buffer+MAX_BIGINT_SIZE-groups[0].modulus_size,
                              temp_buffer);
    temp_buffer_size = groups[0].modulus_size;

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}


void handle_INS_GET_SCOPE_EXCLUSIVE_RESPONSE(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc < PIN_SIZE + 1)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA  ^ (PIN_SIZE + 1));

    checkPin(apdu_data.get_scope_exclusive_response_in.pin);

    accessSession(0);

    // fetch provers[current_prover_id-1].kx, provers[current_prover_id-1].c, provers[current_prover_id-1].proofstatus

    if (provers[current_prover_id-1].proofstatus != 2)
        mExitSW(ERR_CURRENT_PROOF_SESSION_INAP_STAGE);

    if (!groupExists(0))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);

    // fetch groups[0].q

    singleResponse(provers[current_prover_id-1].kx, provers[current_prover_id-1].ksize, provers[current_prover_id-1].c , provers[current_prover_id-1].csize, device_key, x_size, groups[0].q, groups[0].q_size, 0);

    mem_cpy(temp_buffer, buffer, buffer_size);
    temp_buffer_size = buffer_size;

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}


void handle_INS_STORE_BLOB(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    uri = accessURI(apdu_data.blob_in.datain, Lc);

    getBlobstoreInformations(&temp_blob_index, &temp_blobcount, &temp_uri_index, uri, Lc-PIN_SIZE);

    if (temp_blobcount == MAX_NUMBER_OF_BLOBS)
        mExitSW(ERR_MAX_NBR_BLOB_REACHED);

    if (temp_uri_index != MAX_NUMBER_OF_BLOBS) {
        temp_blob_index = temp_uri_index; // there already exists a blob with this uri, overwrite it
    }

    if (buffer_size > MAX_BLOB_SIZE)
        mExitSW(ERR_BLOB_TOO_LARGE);

    blob_catalog[temp_blob_index].exists = 1;
    mem_cpy(blob_catalog[temp_blob_index].uri, uri, Lc-PIN_SIZE);
    blob_catalog[temp_blob_index].uri_size = Lc-PIN_SIZE;
    blob_catalog[temp_blob_index].buffer_size = buffer_size;

    segmentToStaticHigh(blob_store[temp_blob_index].buffer, buffer, buffer_size);

}


void handle_INS_LIST_BLOBS(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + 1)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + 1));

    checkPin(apdu_data.list_blobs_in.pin);

    getBlobstoreInformations(&temp_blob_index, &temp_blobcount, &temp_uri_index, NULL, NULL);

    buffer_size = 0;

    temp_nread = apdu_data.list_blobs_in.nread;
    prev_nread = temp_nread;

    // if prev_nread > temp_blobcount, the reader is asking for more
    // blobs although they do not exist. Exit with  "blobcount on 1 byte" 00 90 00.
    if (prev_nread >= temp_blobcount) {
        apdu_data.dataout[0] = temp_blobcount & 0xFF;
        apdu_data.dataout[1] = 0x00;
        mExitLa(2);
    }

    temp_size = 0;

    i = 0;
    while(i < MAX_NUMBER_OF_BLOBS && (temp_nread < temp_blobcount) && !(temp_size + blob_catalog[temp_nread].uri_size + 1 > MAX_APDU_OUTPUT_DATA_SIZE - 2)) {

        if(blob_catalog[i].exists) {

            if(prev_nread) {

                prev_nread--;

            } else {

                mem_cpy(apdu_data.dataout+temp_size, &(blob_catalog[i].uri_size), 1);
                temp_size += 1;
                mem_cpy(apdu_data.dataout+temp_size, blob_catalog[i].uri, blob_catalog[i].uri_size);
                temp_size += blob_catalog[i].uri_size;

                temp_nread++;

            }

        }

        i++;
    }

    mem_cpy(apdu_data.dataout+temp_size, &temp_nread, 1);
    temp_size += 1;
    temp_nread = temp_blobcount - temp_nread;
    mem_cpy(apdu_data.dataout+temp_size, &temp_nread, 1);
    temp_size += 1;

    mExitLa(temp_size); // in this particular case, we know that no more than 255 will ever be sent out

}


void handle_INS_READ_BLOB(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    uri = accessURI(apdu_data.blob_in.datain, Lc);

    getBlobstoreInformations(&temp_blob_index, &temp_blobcount, &temp_uri_index, uri, Lc-PIN_SIZE);

    if (temp_uri_index == MAX_NUMBER_OF_BLOBS)
        mExitSW(ERR_NO_BLOB_WITH_GIVEN_URI);

    temp_buffer_size = blob_catalog[temp_uri_index].buffer_size;
    staticHighToSegment(temp_buffer, blob_store[temp_uri_index].buffer, temp_buffer_size);

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}


void handle_INS_REMOVE_BLOB(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    uri = accessURI(apdu_data.blob_in.datain, Lc);

    getBlobstoreInformations(&temp_blob_index, &temp_blobcount, &temp_uri_index, uri, Lc-PIN_SIZE);

    if (temp_uri_index == MAX_NUMBER_OF_BLOBS)
        mExitSW(ERR_NO_BLOB_WITH_GIVEN_URI);

    blob_catalog[temp_uri_index].exists = 0;
    mem_set(blob_catalog[temp_uri_index].uri, 0, MAX_URI_SIZE);
    blob_catalog[temp_uri_index].uri_size = 0;
    blob_catalog[temp_uri_index].buffer_size = 0;

}


void handle_INS_BACKUP_DEVICE(){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PASSWORD_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + PASSWORD_SIZE));

    checkPin(apdu_data.backup_in.pin);

    buffer_size = 0;
    mem_cpy(buffer+buffer_size, pin, PIN_SIZE);
    buffer_size += PIN_SIZE;
    mem_cpy(buffer+buffer_size, puk, PUK_SIZE);
    buffer_size += PUK_SIZE;
#ifdef SODER
    mem_cpy(buffer+buffer_size, device_key+MAX_SMALLINT_SIZE-x_size, x_size);
    buffer_size += x_size;
#endif

    encrypt(apdu_data.backup_in.password, 0x01);

    mem_cpy(temp_buffer, buffer, buffer_size);
    temp_buffer_size = buffer_size;

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}


void handle_INS_RESTORE_DEVICE(){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PASSWORD_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + PASSWORD_SIZE));

    checkPin(apdu_data.backup_in.pin);

    decrypt(device_id_prim, apdu_data.backup_in.password, 0x01);

    mem_cpy(pin, buffer, PIN_SIZE);
    mem_cpy(puk, buffer+PIN_SIZE, PUK_SIZE);

#ifdef SODER
    x_size = buffer_size - PIN_SIZE - PUK_SIZE;
    mem_set(device_key, 0, MAX_SMALLINT_SIZE);
    mem_cpy(device_key+MAX_SMALLINT_SIZE-x_size, buffer+PIN_SIZE+PUK_SIZE, x_size);
#endif

}


void handle_INS_BACKUP_COUNTERS(){

#if NUM_COUNTERS > 0
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PASSWORD_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + PASSWORD_SIZE));

    checkPin(apdu_data.backup_in.pin);

    buffer_size = 0;

    for (temp_counter_id = 1; temp_counter_id <= NUM_COUNTERS; temp_counter_id++) {
        if (counters[temp_counter_id-1].exists) {
            mem_cpy(buffer+buffer_size, &(counters[temp_counter_id-1].counter_id), 1);
            buffer_size++;
            mem_cpy(buffer+buffer_size, &(counters[temp_counter_id-1].index), 1);
            buffer_size++;
            mem_cpy(buffer+buffer_size, counters[temp_counter_id-1].cursor, CURSOR_SIZE);
            buffer_size += CURSOR_SIZE;
        }
    }

    if (buffer_size == 0)
        mExitSW(ERR_NO_CONTENT_TO_BACKUP);

    encrypt(apdu_data.backup_in.password, 0x02);

    mem_cpy(temp_buffer, buffer, buffer_size);
    temp_buffer_size = buffer_size;

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

#endif

}


void handle_INS_RESTORE_COUNTERS(){

#if NUM_COUNTERS > 0
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PASSWORD_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + PASSWORD_SIZE));

    checkPin(apdu_data.backup_in.pin);

    decrypt(device_id_prim, apdu_data.backup_in.password, 0x02);

    if (buffer_size % 6 != 0)
        mExitSW(ERR_INVALID_BACKUP_ARCHIVE);

    d = buffer_size / 6;

    for (i = 0; i < d; i++) {
        mem_cpy(mem_session.small_buffer, buffer + 6*i, 6);
        // small_buffer contains counter_id (1 byte) || index (1 byte) || cursor (4 bytes)
        temp_counter_id = mem_session.small_buffer[0];
        if (!counters[temp_counter_id-1].exists)
            mExitSW(ERR_COUNTER_DOES_NOT_EXIST);
        counters[temp_counter_id-1].index = mem_session.small_buffer[1];
        mem_cpy(counters[temp_counter_id-1].cursor, mem_session.small_buffer+2, CURSOR_SIZE);
    }

#endif

}



#ifdef SODER    //TODO: remove if not necessary
void handle_INS_BACKUP_CREDENTIAL(void){
    if (!mCheckCase(4))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PASSWORD_SIZE + 1)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + PASSWORD_SIZE + 1));

    checkPin(apdu_data.backup_credential_in.pin);

    temp_credential_id = apdu_data.backup_credential_in.credential_id;

    if (temp_credential_id < 1 || temp_credential_id > NUM_CREDS)
        mExitSW(ERR_CREDENTIALID_OUTSIDE_OF_RANGE);

    if (!credentials[temp_credential_id - 1].exists)
        mExitSW(ERR_CREDENTIAL_DOES_NOT_EXIST);

    // fetch credentials[temp_credential_id - 1].issuer_id, credentials[temp_credential_id - 1].status, credentials[temp_credential_id - 1].prescount, credentials[temp_credential_id - 1].v

    if (credentials[temp_credential_id - 1].status != 2)
        mExitSW(ERR_NO_CONTENT_TO_BACKUP);

    buffer_size = 0;
    mem_cpy(buffer+buffer_size, &(credentials[temp_credential_id - 1].credential_id), 1);
    buffer_size += 1;
    mem_cpy(buffer+buffer_size, &(credentials[temp_credential_id - 1].issuer_id), 1);
    buffer_size += 1;
    mem_cpy(buffer+buffer_size, &(credentials[temp_credential_id - 1].status), 1);
    buffer_size += 1;
    mem_cpy(buffer+buffer_size, &(credentials[temp_credential_id - 1].prescount), 1);
    buffer_size += 1;
    mem_cpy(buffer+buffer_size, credentials[temp_credential_id - 1].v, credentials[temp_credential_id - 1].v_size);
    buffer_size += credentials[temp_credential_id - 1].v_size;

    encrypt(apdu_data.backup_credential_in.password, 0x03);

    mem_cpy(temp_buffer, buffer, buffer_size);
    temp_buffer_size = buffer_size;

    if (temp_buffer_size <= MAX_APDU_OUTPUT_DATA_SIZE) {
        mem_cpy(apdu_data.dataout, temp_buffer, temp_buffer_size);
        mExitLa(temp_buffer_size);
    } else {
        remaining_position = temp_buffer;
        remaining_size = temp_buffer_size;
        output_large_data();
    }

}

void handle_INS_RESTORE_CREDENTIAL(void){
    if (!mCheckCase(3))
        mExitSW(ERR_BAD_ISO);

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);

    if (Lc != PIN_SIZE + PASSWORD_SIZE)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA ^ (PIN_SIZE + PASSWORD_SIZE));

    checkPin(apdu_data.backup_in.pin);

    decrypt(device_id_prim, apdu_data.backup_in.password, 0x03);

    // buffer should contain credential_id || issuer_id || status || prescount || v

    if (buffer[2] != 2)
        mExitSW(ERR_INVALID_BACKUP_ARCHIVE);

    temp_credential_id = buffer[0];

    mem_cpy(&(credentials[temp_credential_id - 1].credential_id), buffer, 2); /* This sets credential_id AND issuer_id */
    /*       credentials[temp_credential_id - 1].credential_id = temp_credential_id; */
    /*       credentials[temp_credential_id - 1].issuer_id = buffer[1]; */
    mem_cpy(&(credentials[temp_credential_id - 1].status), buffer+2, 2); /* This sets status AND prescount */
    /*       credentials[temp_credential_id - 1].status    = buffer[2]; */
    /*       credentials[temp_credential_id - 1].prescount = buffer[3]; */
    mem_cpy(credentials[temp_credential_id - 1].v, buffer+4, buffer_size-4);
    credentials[temp_credential_id - 1].v_size = buffer_size-4;
    mem_set(credentials[temp_credential_id - 1].kv, 0, MAX_SMALLINT_SIZE);
    credentials[temp_credential_id - 1].kv_size = 0;
    credentials[temp_credential_id - 1].exists = 1;

}
#endif


void handle_INS_GET_INFO(void){
    if (!mCheckCase(2))
        mExitSW(ERR_BAD_ISO);

    temp_buffer_size = 0;

    temp_size = CHALLENGE_MAX_SIZE;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    temp_size = NUM_ISSUERS;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    temp_size = MAX_NUMBER_OF_BLOBS;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    temp_size = NUM_GROUPS;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    temp_size = NUM_COUNTERS;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    temp_size = NUM_AUTH_KEYS;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    temp_size = MAX_URI_SIZE;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    temp_size = MAX_BLOB_SIZE;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    temp_size = MAX_BIGINT_SIZE;
    mem_cpy(apdu_data.dataout+temp_buffer_size, &temp_size, 2);
    temp_buffer_size += 2;

    mExitLa(temp_buffer_size);


}


void handle_INS_NOTHING(void){
    // manyhue
}


void handle_INS_GET_RESPONSE(void){
    if (!mCheckCase(2))
        mExitSW(ERR_BAD_ISO);

    output_large_data();

}
