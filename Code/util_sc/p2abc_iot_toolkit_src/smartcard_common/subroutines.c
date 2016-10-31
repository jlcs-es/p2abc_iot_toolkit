/******************************************************************************/
/******************************************************************************/
/****************             Subroutines                **********************/
/******************************************************************************/
/******************************************************************************/

// TODO : la documentación ¿pasarla al .h?
// FIXME : el uso de unsigned int en vez de WORD / DWORD y la posibilidad que no quepa en los WORD del size usual de multosFuncion()
// según referencias de multos: "an integer is a machine word, which is 2 byte"
// "An integer is a machine word and, in the case of MULTOS, this is 2 bytes"
//

/////



#include <smartcard_common/subroutines.h>
#include <smartcard_common/m_adapted_API.h>
#include <smartcard_adaptor/system_funcs.h>
#include <smartcard_common/defs_consts.h>
#include <smartcard_common/defs_errs.h>
#include <smartcard_common/global_vars.h>


/************************************************************************************************************************************************
 * void getRandomBytes(BYTE* buffer, unsigned int size)
 *
 * Generate 's = 8*ceil(size/8)' random bytes and put them in
 * buffer[0],...,buffer[s-1].
 ************************************************************************************************************************************************/

void getRandomBytes(BYTE* buffer, unsigned int size) {

    unsigned int i;
    BYTE temp_buffer[8];

    for (i=8; i<=size; i += 8) {
        mGetRandomNumber(temp_buffer); // ** Adapted for util_sc ** //
        mBlockCopyFixedLength(8, temp_buffer, buffer + i - 8); // ** Adapted for util_sc ** //
    }

    if( 8-i+size < 8 ){ //unsigned size > 0

        mGetRandomNumber(temp_buffer); // ** Adapted for util_sc ** //
        mBlockCopyFixedLength(8-i+size, temp_buffer, buffer + i - 8); // ** Adapted for util_sc ** //

    }

}


/************************************************************************************************************************************************
 * void checkPin(BYTE* tested_pin)
 *
 * If tested_pin == pin, this routine returns to the
 * caller. Otherwise, it sends a SW != 0x9000. This routine does NOT
 * check whether pin_trials > 0.
 ************************************************************************************************************************************************/

void checkPin(BYTE* tested_pin) {

    if (mem_cmp(tested_pin, pin, PIN_SIZE) == 0) {  // ** Adapted for util_sc ** //
        pin_trials = MAX_PIN_TRIALS;
        return;
    }

    // if this point is reached, the pin is incorrect. We eventually
    // exit.

    pin_trials -= 1;

    if (pin_trials == 0) {
        mode = MODE_LOCKED;
        mExitSW(ERR_INCORRECT_PIN_AND_CARD_LOCKED); // ** Adapted for util_sc ** //
        return;
    }

    mExitSW(ERR_INCORRECT_PIN); // ** Adapted for util_sc ** //

}

/************************************************************************************************************************************************
 * void checkPuk(BYTE* tested_puk)
 *
 * If tested_puk == pin, this routine returns to the
 * caller. Otherwise, it sends a SW != 0x9000. This routine does NOT
 * check whether puk_trials > 0.
 ************************************************************************************************************************************************/

void checkPuk(BYTE* tested_puk) {

    if (mem_cmp(tested_puk, puk, PUK_SIZE) == 0) {  // ** Adapted for util_sc ** //
        puk_trials = MAX_PUK_TRIALS;
        return;
    }

    // if this point is reached, the puk is incorrect. We eventually
    // exit.

    puk_trials -= 1;

    if (puk_trials == 0) {
        mode = MODE_DEAD;
        mExitSW(ERR_INCORRECT_PUK_AND_CARD_DEAD); // ** Adapted for util_sc ** //
        return;
    }

    mExitSW(ERR_INCORRECT_PUK); // ** Adapted for util_sc ** //

}




/************************************************************************************************************************************************
 * unsigned int sizeDecode(BYTE *s)
 *
 * Take a n-byte table of BYTEs and returns
 * 2^8 * s[0] + s[1]. This assumes that SIZE_SIZE == 2.
 ************************************************************************************************************************************************/

unsigned int sizeDecode(BYTE *s) {

    return (unsigned int)( (((WORD)(s[0]))<<8) + s[1]);

}

/************************************************************************************************************************************************
 * void sizeEncode(BYTE *s, unsigned int size) {
 *
 * This is the inverse of sizeDecode
 ************************************************************************************************************************************************/

void sizeEncode(BYTE *s, unsigned int size) {

    s[1] = size & 0xFF;
    s[0] = (size >> 8) & 0xFF;

}

/************************************************************************************************************************************************
 * void getKey(BYTE *key, key_id)
 *
 ************************************************************************************************************************************************/

void getKey(BYTE *key, unsigned int *key_size, const BYTE key_id) {

    if (key_id > NUM_ISSUERS)
        mExitSW(ERR_KEY_ID_OUTSIDE_RANGE); // ** Adapted for util_sc ** //

    if (!auth_keys_sizes[key_id])
        mExitSW(ERR_AUTHENTICATION_KEY_DOES_NOT_EXIST); // ** Adapted for util_sc ** //

    *key_size = auth_keys_sizes[key_id];
    mem_cpy(key, auth_keys[key_id], auth_keys_sizes[key_id]);   // ** Adapted for util_sc ** //

}

/************************************************************************************************************************************************
 * void publicKeyEncrypt(BYTE* key, unsigned int key_size)
 *
 * Overwrites : temp_buffer, temp_buffer_size ???
 ************************************************************************************************************************************************/

void publicKeyEncrypt(BYTE* key, unsigned int key_size) {

    if (temp_buffer_size > key_size - 43)
        mExitSW(ERR_AUTHENTICATION_KEY_TOO_SHORT); // ** Adapted for util_sc ** //

    encryption(temp_buffer, &temp_buffer_size, temp_buffer, temp_buffer_size, key, key_size);

}

/************************************************************************************************************************************************
 * void encryption(BYTE* dst, unsigned int* dst_size, const BYTE *src, unsigned int src_size, BYTE *key, unsigned int key_size)
 *
 * Overwrites : pad, temp_rand_size,
 ************************************************************************************************************************************************/
void encryption(BYTE* dst, unsigned int* dst_size, const BYTE *src, const unsigned int src_size, const BYTE *key, const unsigned int key_size) {

    BYTE exponent[1] = {3};

    temp_rand_size = key_size - 35 - src_size; // should be 83

#ifdef TEST_MODE
    memset(mem_session.pad+3+src_size, 0xbc, temp_rand_size);
#else
    getRandomBytes(mem_session.pad+3+src_size, temp_rand_size);
#endif

    mem_session.pad[0] = 0x00;
    sizeEncode(mem_session.pad+1, src_size);
    mem_cpy(mem_session.pad+3, src, src_size);  // ** Adapted for util_sc ** //
    pad_size = key_size-32; // should be 96

    //Deprecated: SHA256(mem_session.pad+pad_size, pad_size, mem_session.pad); // compute (pad || h)
    mSecureHash(pad_size, 32, mem_session.pad+pad_size, mem_session.pad); // SHA256 compute (pad || h) // ** Adapted for util_sc ** //

    mModularExponentiation(1, key_size, exponent, (BYTE*)key, mem_session.pad, dst); // ** Adapted for util_sc ** //

    *dst_size = key_size;

    temp_rand_size = 0;

}

/************************************************************************************************************************************************
 * void extract(const BYTE *key, const unsigned int key_size)
 ************************************************************************************************************************************************/

void extract(const BYTE *key, const unsigned int key_size) {

    extraction(key, key_size, buffer, &buffer_size, mem_session.challenge, challenge_size);

    mem_set(mem_session.challenge, 0, CHALLENGE_MAX_SIZE);  // ** Adapted for util_sc ** //

    if (buffer_size == 0)
        mExitSW(ERR_DATA_AUTHENTICATION_FAILURE); // ** Adapted for util_sc ** //

}

/************************************************************************************************************************************************
 * void extraction(const BYTE *n, const unsigned int n_size, BYTE *sig, unsigned int sig_size, const BYTE *challenge)
 *
 * In case of success, the extraction is put back into sig.
 ************************************************************************************************************************************************/

unsigned int extraction(const BYTE *n, const unsigned int n_size, BYTE *sig, unsigned int *sig_size, const BYTE *challenge, const unsigned int challenge_size) {

    BYTE exponent[1] = {3};
    BYTE hash_[HASH_SIZE]; // only used in the 'else' below
    BYTE hash_prime[HASH_SIZE];
    unsigned int pad_size;
    BYTE b;
    unsigned int L;
    BYTE *blob, *pad, *challenge_and_pad, *sigma, *m1, *m2, *hash;
    unsigned int m1_size, m2_size;

    if (challenge_size < 16 || *sig_size < n_size)
        mExitSW(ERR_DATA_AUTHENTICATION_FAILURE);  // ** Adapted for util_sc ** //

    if (n_size == *sig_size) {

        mem_cpy(temp_buffer, challenge, challenge_size);    // ** Adapted for util_sc ** //
        mModularExponentiation(1, n_size, exponent, (BYTE*)n, buffer, temp_buffer+challenge_size);  // ** Adapted for util_sc ** //
        temp_buffer_size = challenge_size + n_size;

        // temp_buffer contains challenge||pad||h

        pad_size          = n_size - 32;
        challenge_and_pad = temp_buffer;
        pad               = temp_buffer + challenge_size;
        hash              = temp_buffer + challenge_size + pad_size;

        // ** Adapted for util_sc ** // SHA256(hash_prime, challenge_size + pad_size, challenge_and_pad);
        mSecureHash(challenge_size + pad_size, 32, hash_prime, challenge_and_pad);  // ** Adapted for util_sc ** //


        b    = pad[0];
        L    = sizeDecode(pad + 1);
        blob = pad + 3;

        if (b != 0 || L < 1 || L > n_size - 35 || mem_cmp(hash_prime, hash, HASH_SIZE)) // ** Adapted for util_sc ** //
            mExitSW(ERR_DATA_AUTHENTICATION_FAILURE);   // ** Adapted for util_sc ** //

        mem_cpy(sig, blob, L);  // ** Adapted for util_sc ** //
        *sig_size = L;

    } else {

        sigma = sig;
        m2    = sig + n_size;

        mem_cpy(temp_buffer, challenge, challenge_size);    // ** Adapted for util_sc ** //
        mModularExponentiation(1, n_size, exponent, (BYTE *)n, sigma, temp_buffer+challenge_size);  // ** Adapted for util_sc ** //
        temp_buffer_size = challenge_size + n_size;

        // temp_buffer contains challenge||pad||h.

        pad_size          = n_size - 32;
        challenge_and_pad = temp_buffer;
        pad               = temp_buffer + challenge_size;
        mem_cpy(hash_, temp_buffer + challenge_size + pad_size, HASH_SIZE);     // ** Adapted for util_sc ** //


        // We want temp_buffer to contain challenge||pad||m2

        m2_size = *sig_size - n_size;
        mem_cpy(temp_buffer + challenge_size + pad_size, m2, m2_size);  // ** Adapted for util_sc ** //
        temp_buffer_size = challenge_size + pad_size + m2_size;

        // we hash

        // ** Adapted for util_sc ** // SHA256(hash_prime, temp_buffer_size, temp_buffer);
        mSecureHash(temp_buffer_size, 32, hash_prime, temp_buffer); // ** Adapted for util_sc ** //

        b       = pad[0];
        L       = sizeDecode(pad + 1);
        m1      = pad + 3;
        m1_size = pad_size - 3;

        if (b != 0 || L != n_size - 35 + m2_size || mem_cmp(hash_prime, hash_, HASH_SIZE))  // ** Adapted for util_sc ** //
            mExitSW(ERR_DATA_AUTHENTICATION_FAILURE);   // ** Adapted for util_sc ** //

        mem_cpy(sig        , m1, m1_size);  // ** Adapted for util_sc ** //
        mem_cpy(sig+m1_size, m2, m2_size);  // ** Adapted for util_sc ** //
        *sig_size = m1_size + m2_size;

    }

}

/************************************************************************************************************************************************
 * void checkBufferPrefix(BYTE ins, BYTE *datain, unsigned int datain_size)
 ************************************************************************************************************************************************/

void checkBufferPrefix(BYTE ins, BYTE *datain, unsigned int datain_size) { // prefix = ins || datain

    unsigned int i, prefix_size;

    prefix_size = datain_size + 1;

    if (buffer_size < prefix_size)
        mExitSW(ERR_NEED_PRIOR_DATA_AUTHENTICATION_WRT_ROOT_KEY);   // ** Adapted for util_sc ** //

    if (authData == 0)
        mExitSW(ERR_NEED_PRIOR_DATA_AUTHENTICATION_WRT_ROOT_KEY);   // ** Adapted for util_sc ** //

    if (authKeyId != 0)
        mExitSW(ERR_DATA_AUTHENTICATED_WRT_NON_ROOT_KEY);   // ** Adapted for util_sc ** //

    authData = 0;

    if (buffer[0] != ins || mem_cmp(datain, buffer+1, datain_size)) // prefix = ins || datain   // ** Adapted for util_sc ** //
        mExitSW(ERR_CMD_PARAMETERS_FAILED_ROOT_AUTHENTICATION); // ** Adapted for util_sc ** //

    if (buffer_size > prefix_size) {
        for (i=0; i<buffer_size; i++)
            buffer[i] = buffer[i+prefix_size];
    }

    buffer_size = buffer_size-prefix_size;

}

/************************************************************************************************************************************************
 * void checkBufferEqual(BYTE ins, BYTE *datain, unsigned int datain_size) // content = ins || datain
 ************************************************************************************************************************************************/

void checkBufferEqual(BYTE ins, BYTE *datain, unsigned int datain_size) {

    checkBufferPrefix(ins, datain, datain_size);
    if (buffer_size != 0)
        mExitSW(ERR_DATA_AUTHENTICATION_FAILURE);   // ** Adapted for util_sc ** //

}

/************************************************************************************************************************************************
 * BYTE groupExists(BYTE group_id)
 ************************************************************************************************************************************************/

BYTE groupExists(BYTE group_id) {
    if (groups[group_id].modulus_size > 0)
        return 1;
    return 0;
}

/************************************************************************************************************************************************
 * BYTE generatorExists(BYTE group_id, BYTE gen_id)
 ************************************************************************************************************************************************/

BYTE generatorExists(BYTE group_id, BYTE gen_id) {
    if (groups[group_id].g_size[gen_id-1] > 0)
        return 1;
    return 0;
}

/************************************************************************************************************************************************
 * void getGroupComponent(BYTE group_id, BYTE comptype)
 ************************************************************************************************************************************************/

void getGroupComponent(BYTE group_id, BYTE comptype) {

    switch(comptype) {
        case 0:
            mem_cpy(buffer, groups[group_id].modulus + (MAX_BIGINT_SIZE-groups[group_id].modulus_size), groups[group_id].modulus_size); // ** Adapted for util_sc ** //
            buffer_size = groups[group_id].modulus_size;
            break;
        case 1:
            mem_cpy(buffer, groups[group_id].q + (MAX_SMALLINT_SIZE-groups[group_id].q_size), groups[group_id].q_size); // ** Adapted for util_sc ** //
            buffer_size = groups[group_id].q_size;
            break;
        case 2:
            mem_cpy(buffer, groups[group_id].f + (MAX_BIGINT_SIZE-groups[group_id].f_size), groups[group_id].f_size);   // ** Adapted for util_sc ** //
            buffer_size = groups[group_id].f_size;
            break;
        default:
            buffer[0] = groups[group_id].num_generators;
            buffer_size = 1;
            break;
    }

}

/************************************************************************************************************************************************
 * void getGenerator(BYTE group_id, BYTE gen_id)
 *
 * Put the generator in a MAX_BIGINT_SIZEd buffer. The significant length
 * of the generator is put in buffer_size.
 ************************************************************************************************************************************************/

void getGenerator(BYTE group_id, BYTE gen_id) {

    if (gen_id == 0 || gen_id > NUM_GEN)
        mExitSW(ERR_ID_OF_GROUP_GENERATOR_OUTSIDE_OF_RANGE);    // ** Adapted for util_sc ** //

    if (!generatorExists(group_id, gen_id))
        mExitSW(ERR_GENERATOR_DOES_NOT_EXIST);  // ** Adapted for util_sc ** //

    mem_cpy(buffer, groups[group_id].g[gen_id-1], MAX_BIGINT_SIZE); // ** Adapted for util_sc ** //
    buffer_size = groups[group_id].g_size[gen_id-1];

}

/************************************************************************************************************************************************
 * BYTE accessCredential(BYTE pin[PIN_SIZE], BYTE credential_id)
 ************************************************************************************************************************************************/

BYTE accessCredential(BYTE *pin, BYTE credential_id) {

    if (mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);   // ** Adapted for util_sc ** //

    if (Lc != 5)
        mExitSW(ERR_INCORRECT_SIZE_OF_INCOMMING_DATA  ^ 5); // ** Adapted for util_sc ** //

    checkPin(pin);

    if (credential_id < 1 || credential_id > NUM_CREDS)
        mExitSW(ERR_CREDENTIALID_OUTSIDE_OF_RANGE); // ** Adapted for util_sc ** //

    if (!credentials[credential_id-1].exists)
        mExitSW(ERR_CREDENTIAL_DOES_NOT_EXIST); // ** Adapted for util_sc ** //

    return credential_id;


}

/************************************************************************************************************************************************
 * void singleOrDoubleExpo(BYTE issuer_id, BYTE *e1, unsigned int e1_size, BYTE *e2, unsigned int e2_size)
 *
 * We assume that both e1 and e2 are buffer of size MAX_SMALLINT_SIZE and
 * that the significant bytes are right-shifted. The number of
 * significant bytes are given by e1_size and e2_size
 * respectively.
 *
 * The least significant byte of the computation is stored in
 * buffer[MAX_BIGINT_SIZE-1]. The real size (number of significant bytes)
 * is stored in buffer_size.
 ************************************************************************************************************************************************/

void singleOrDoubleExpo(BYTE issuer_id, BYTE *e1, unsigned int e1_size, BYTE *e2, unsigned int e2_size) {

    if (issuer_id < 1 || issuer_id > NUM_ISSUERS)
        mExitSW(ERR_ISSUERID_OUTSIDE_OF_RANGE); // ** Adapted for util_sc ** //

    if (!issuers[issuer_id-1].exists)
        mExitSW(ERR_ISSUER_DOES_NOT_EXIST); // ** Adapted for util_sc ** //

    temp_group_id = issuers[issuer_id-1].group_id;
    temp_gen_id_1 = issuers[issuer_id-1].gen_id_1;
    temp_gen_id_2 = issuers[issuer_id-1].gen_id_2;

    if (temp_group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);  // ** Adapted for util_sc ** //

    if (!groupExists(temp_group_id))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);  // ** Adapted for util_sc ** //

    temp_modulus      = groups[temp_group_id].modulus;
    temp_modulus_size = groups[temp_group_id].modulus_size;

    getGenerator(temp_group_id, temp_gen_id_1); // put the generator in a buffer of MAX_BIGINT_SIZE bytes, the real size being stored in temp_gen_1_size
    temp_gen_1_size = buffer_size;

    // 8. call ModExp(e1,m)

    if (temp_gen_1_size >= temp_modulus_size) {
        // reduce the buffer modulo m
        // void multosModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
        mModularReduction(temp_gen_1_size, temp_modulus_size, buffer+MAX_BIGINT_SIZE-temp_gen_1_size, temp_modulus+MAX_BIGINT_SIZE-temp_modulus_size); // ** Adapted for util_sc ** //
        temp_gen_1_size = temp_modulus_size;
    }

    // At this point we have temp_modulus_size >= temp_gen_1_size

    // void crxModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output);
    mModularExponentiation(e1_size, temp_modulus_size, e1+MAX_SMALLINT_SIZE-e1_size, temp_modulus+MAX_BIGINT_SIZE-temp_modulus_size, buffer+MAX_BIGINT_SIZE-temp_modulus_size, buffer+MAX_BIGINT_SIZE-temp_modulus_size);   // ** Adapted for util_sc ** //
    buffer_size = temp_modulus_size;

    // buffer now holds g1**e1 mod m and is of size buffer_size = temp_modulus_size

    // 9. if gen != 0 ...
    if (temp_gen_id_2 != 0) {

        mem_cpy(temp_buffer, buffer, MAX_BIGINT_SIZE);  // ** Adapted for util_sc ** //
        temp_buffer_size = buffer_size; // = temp_modulus_size

        getGenerator(temp_group_id, temp_gen_id_2);
        temp_gen_2_size = buffer_size;

        if (temp_gen_2_size >= temp_modulus_size) {
            // reduce the buffer modulo m
            mModularReduction(temp_gen_2_size, temp_modulus_size, buffer+MAX_BIGINT_SIZE-temp_gen_2_size, temp_modulus+MAX_BIGINT_SIZE-temp_modulus_size);  // ** Adapted for util_sc ** //
            temp_gen_2_size = temp_modulus_size;
        }

        mModularExponentiation(e2_size, temp_modulus_size, e2+MAX_SMALLINT_SIZE-e2_size, temp_modulus+MAX_BIGINT_SIZE-temp_modulus_size, buffer+MAX_BIGINT_SIZE-temp_modulus_size, buffer+MAX_BIGINT_SIZE-temp_modulus_size);   // ** Adapted for util_sc ** //
        buffer_size = temp_modulus_size;

        // ** Adapted for util_sc ** //
            // void multosModularMultiplication (WORD modulusLength, BYTE *modulus, BYTE *block1, BYTE *block2);
            // We set the first bytes of buffer and temp_buffer to 0. This is
            // necessary for the crxModularMultiplication routine. We expect
            // temp_modulus to already have zero's on the left-most bytes.
        mem_set(buffer, 0, MAX_BIGINT_SIZE-temp_modulus_size);  // ** Adapted for util_sc ** // // could be deleted with the use of mModularMultiplication, but for safety, is kept
        mem_set(temp_buffer, 0, MAX_BIGINT_SIZE-temp_modulus_size); // ** Adapted for util_sc ** //
        // ** Adapted for util_sc ** //
            // crxModularMultiplication(temp_modulus_size,   /* modulus size */
            //                         temp_modulus,        /* modulus */
            //                         buffer,              /* buffer */
            //                         temp_buffer);        /* temp   */  // this overwrites buffer
        // ** Adapted for util_sc ** //
        mModularMultiplication (temp_modulus_size, temp_modulus+MAX_BIGINT_SIZE-temp_modulus_size, buffer+MAX_BIGINT_SIZE-temp_modulus_size, temp_buffer+MAX_BIGINT_SIZE-temp_modulus_size); // this overwrites buffer  // ** Adapted for util_sc ** //
        // NOTE : la implementación de crxModularMultiplication hay que estudiarla por si no hace una mult. mod. solo
    }

}

/************************************************************************************************************************************************
 * void accessSession(BYTE credential_id)
 ************************************************************************************************************************************************/

void accessSession(BYTE credential_id) {

    if (current_prover_id < 1 || current_prover_id > NUM_PROVERS)
        mExitSW(ERR_PROVERID_OUTSIDE_OF_RANGE); // ** Adapted for util_sc ** //

    if (!provers[current_prover_id-1].exists)
        mExitSW(ERR_PROVER_DOES_NOT_EXIST); // ** Adapted for util_sc ** //

}

/************************************************************************************************************************************************
 * void singleOrDoubleResponse(BYTE issuer_id, BYTE *c, unsigned int c_size, BYTE *x, unsigned int x_size, BYTE *kx, unsigned int kx_size, BYTE *v, unsigned int v_size, BYTE *kv, unsigned int kv_size)
 *
 * The result is stored in the left-most bytes of buffer, the size of the result is stored in buffer_size.
 ************************************************************************************************************************************************/

void singleOrDoubleResponse(BYTE issuer_id, BYTE *c, unsigned int c_size, BYTE *x, unsigned int x_size, BYTE *kx, unsigned int kx_size, BYTE *v, unsigned int v_size, BYTE *kv, unsigned int kv_size) {

    if (issuer_id < 1 || issuer_id > NUM_ISSUERS)
        mExitSW(ERR_ISSUERID_OUTSIDE_OF_RANGE); // ** Adapted for util_sc ** //

    if (!issuers[issuer_id-1].exists)
        mExitSW(ERR_ISSUER_DOES_NOT_EXIST); // ** Adapted for util_sc ** //

    temp_group_id = issuers[issuer_id-1].group_id;
    temp_gen_id_2 = issuers[issuer_id-1].gen_id_2;

    if (temp_group_id >= NUM_GROUPS)
        mExitSW(ERR_GROUPID_OUTSIDE_OF_RANGE);  // ** Adapted for util_sc ** //

    if (!groupExists(temp_group_id))
        mExitSW(ERR_GROUP_DOES_NOT_EXIST);  // ** Adapted for util_sc ** //

    // fetch q = groups[temp_group_id].q;

    singleResponse(kx, kx_size, c, c_size, x, x_size, groups[temp_group_id].q, groups[temp_group_id].q_size, 0); // the result is stored in the right-most bytes of buffer[0 ... MAX_BIGINT_SIZE-1], there are buffer_size significant bytes

    if (temp_gen_id_2 != 0) {

        singleResponse(kv, kv_size, c, c_size, v, v_size, groups[temp_group_id].q, groups[temp_group_id].q_size, buffer_size);

    }

}

/************************************************************************************************************************************************
 * void singleResponse(BYTE *k, unsigned int k_size, BYTE *c,
 *                     unsigned int c_size, BYTE *u, unsigned int u_size,
 *                     BYTE *q, unsigned int q_size)
 *
 * We assume that all the tables are of size MAX_SMALLINT_SIZE, except for
 * c which we assume to be made of HASH_SIZE bytes. The sizes given as
 * parameters are the number of significant bytes.
 *
 * The result of the computation is stored in buffer, the most
 * significat byte being stored in buffer[offset]. The number of
 * significant bytes and offset bytes is stored in buffer_size.
 ************************************************************************************************************************************************/

void singleResponse(BYTE *k, unsigned int k_size, BYTE *c, unsigned int c_size, BYTE *u, unsigned int u_size, BYTE *q, unsigned int q_size, BYTE offset) {

    BYTE blockLength;

    // put both c and u in temp_buffer

    mem_set(temp_buffer, 0, 2*MAX_SMALLINT_SIZE);   // ** Adapted for util_sc ** //
    mem_cpy(temp_buffer+MAX_SMALLINT_SIZE-c_size, c, c_size);   // ** Adapted for util_sc ** //
    mem_cpy(temp_buffer+MAX_SMALLINT_SIZE, u, MAX_SMALLINT_SIZE);   // ** Adapted for util_sc ** //

    if (q_size != 0) {

        // compute (k - c*u) mod q

        // reduce c and u mod q and compute c*u mod q and put the result in temp_buffer
        // void multosModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
        if (c_size >= q_size)
            mModularReduction (c_size, q_size, temp_buffer+MAX_SMALLINT_SIZE-c_size, q+MAX_SMALLINT_SIZE-q_size);   // ** Adapted for util_sc ** //
        if (u_size >= q_size)
            mModularReduction (u_size, q_size, temp_buffer+2*MAX_SMALLINT_SIZE-u_size, q+MAX_SMALLINT_SIZE-q_size); // ** Adapted for util_sc ** //

        // compute c * u mod q
        // Due to the fact that multosModularMultiplication stores the MSB
        // of the result on block1[0] (which is *not* how things should be
        // done), we replace this instruction with a simple
        // multiplication, followed by a modular reduction.

        // void multosBlockMultiply (const BYTE blockLength, BYTE *block1, BYTE *block2, BYTE *result)
        // ** Adapted for util_sc ** //     crxBlockMultiply127orLess (MAX_SMALLINT_SIZE-1, temp_buffer+1, temp_buffer+MAX_SMALLINT_SIZE+1, temp_buffer+2); // this puts the result in the right-most bytes of temp_buffer[0 ... 2*MAX_SMALLINT_SIZE-1]
        mBlockMultiply(MAX_SMALLINT_SIZE-1, temp_buffer+1, temp_buffer+MAX_SMALLINT_SIZE+1, temp_buffer+2); // this puts the result in the right-most bytes of temp_buffer[0 ... 2*MAX_SMALLINT_SIZE-1]     // ** Adapted for util_sc ** //
        // FIXME : check comment vs function call


        // void multosModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
        if (c_size + u_size >= q_size)
            mModularReduction (c_size + u_size, q_size, temp_buffer + 2*MAX_SMALLINT_SIZE - c_size - u_size, q + MAX_SMALLINT_SIZE - q_size);   // ** Adapted for util_sc ** //

        //temp_buffer_size = q_size; // the least significant byte of c*u mod q is in temp_buffer_size[2*MAX_SMALLINT_SIZE-1] and there are at most q_size significant bytes

        // put k in buffer. If necessary, reduce it modulo q

        mem_cpy(temp_buffer, k, MAX_SMALLINT_SIZE); // ** Adapted for util_sc ** //
        if (k_size >= q_size)
            mModularReduction (k_size,
                               q_size,
                               temp_buffer + MAX_SMALLINT_SIZE - k_size, /* k */
                               q           + MAX_SMALLINT_SIZE - q_size  /* q */
            );  // ** Adapted for util_sc ** //

        // we want to compute k - cu mod q, we already have k mod q in temp_buffer[0..MAX_SMALLINT_SIZE-1] and cu mod q in temp_buffer[MAX_SMALLINT_SIZE..2*MAX_SMALLINT_SIZE-1]

        /* if k mod q < cu mod q, replace k by k + q */
        if(mem_cmp(temp_buffer, temp_buffer+MAX_SMALLINT_SIZE, MAX_SMALLINT_SIZE) < 0) {    // ** Adapted for util_sc ** //
            // we have that (k mod q) < (c*u mod q)
            // void multosBlockAdd (const BYTE blockLength, BYTE *block1, BYTE *block2, const BYTE *result);
            mBlockAdd(MAX_SMALLINT_SIZE, temp_buffer, q, temp_buffer);      // ** Adapted for util_sc ** //
        }

        // void multosBlockSubract (const BYTE blockLength, BYTE *block1, BYTE *block2, const BYTE *result);
        //multosBlockSubract (q_size, buffer+MAX_SMALLINT_SIZE-q_size, temp_buffer+MAX_SMALLINT_SIZE-q_size, buffer+MAX_SMALLINT_SIZE-q_size);
        mBlockSubtract (MAX_SMALLINT_SIZE,
                        temp_buffer+MAX_SMALLINT_SIZE,
                        temp_buffer,
                        temp_buffer);   // block2-block1   // ** Adapted for util_sc ** //

        mem_cpy(buffer+offset, temp_buffer+MAX_SMALLINT_SIZE-q_size, q_size);   // ** Adapted for util_sc ** //
        buffer_size = q_size+offset;

    } else {

        // compute k - c*u over the integers

        // make sure that c*u fits a big integer

        if (c_size + u_size > MAX_SMALLINT_SIZE)
            mExitSW(ERR_INTEGER_EXCEEDS_MAXINTSIZE);    // ** Adapted for util_sc ** //

        // compute c*u, put it in temp_buffer[0 ... MAX_SMALLINT_SIZE-1]
        // void multosBlockMultiply (const BYTE blockLength, BYTE *block1, BYTE *block2, BYTE *result);
        // ** Adapted for util_sc ** //     crxBlockMultiply127orLess (MAX_SMALLINT_SIZE-1, temp_buffer+1, temp_buffer+MAX_SMALLINT_SIZE+1, temp_buffer+2); // this puts the result in the right-most bytes of temp_buffer[0 ... 2*MAX_SMALLINT_SIZE-1]
        mBlockMultiply(MAX_SMALLINT_SIZE-1, temp_buffer+1, temp_buffer+MAX_SMALLINT_SIZE+1, temp_buffer+2);     // this puts the result in the right-most bytes of temp_buffer[0 ... 2*MAX_SMALLINT_SIZE-1]   // ** Adapted for util_sc ** //
        // FIXME : check comment vs function call

        // since c_size + u_size <= MAX_SMALLINT_SIZE, we can put the result back in the MAX_SMALLINT_SIZE first bytes of temp_buffer

        mem_cpy(temp_buffer, temp_buffer+MAX_SMALLINT_SIZE, MAX_SMALLINT_SIZE); // ** Adapted for util_sc ** //

        // put k

        mem_cpy(temp_buffer+MAX_SMALLINT_SIZE, k, MAX_SMALLINT_SIZE);   // ** Adapted for util_sc ** //

        // compute (temp_buffer+MAX_SMALLINT_SIZE) - temp_buffer (i.e., k - cu), both buffers being made of MAX_INT_BYTES bytes

        mBlockSubtract(MAX_SMALLINT_SIZE, temp_buffer, temp_buffer+MAX_SMALLINT_SIZE, temp_buffer); // block2-block1    // ** Adapted for util_sc ** //

        buffer_size = k_size+offset;
        mem_cpy(buffer+offset, temp_buffer+MAX_SMALLINT_SIZE-k_size, k_size);   // ** Adapted for util_sc ** //

    }

}

/************************************************************************************************************************************************
 * void scopeExclusiveGenerator()
 *
 * Put the result in the right-most bytes of buffer[0 ... MAX_BIGINT_SIZE-1].
 * The significant length of the result is stored in buffer_size.
 ************************************************************************************************************************************************/

void scopeExclusiveGenerator(BYTE *scope, unsigned int scope_size, BYTE *m, unsigned int m_size, BYTE *f, unsigned int f_size) {

    mem_set(buffer, 0, MAX_BIGINT_SIZE); // alloc for buffer: MAX_APDU_INPUT_DATA_SIZE bytes    // ** Adapted for util_sc ** //
    // ** Adapted for util_sc ** // SHA256(buffer+MAX_BIGINT_SIZE-HASH_SIZE, scope_size, scope);
    mSecureHash(scope_size, 32, buffer+MAX_BIGINT_SIZE-HASH_SIZE, scope);   // ** Adapted for util_sc ** //
    buffer_size = HASH_SIZE;

    if (f_size != 0) {

        // void multosModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
        if (buffer_size >= m_size) {
            mModularReduction (buffer_size, m_size, buffer+MAX_BIGINT_SIZE-buffer_size, m+MAX_BIGINT_SIZE-m_size);  // ** Adapted for util_sc ** //
            buffer_size = m_size;
        }

        // void crxModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output);
        mModularExponentiation(f_size, m_size, f+MAX_BIGINT_SIZE-f_size, m+MAX_BIGINT_SIZE-m_size, buffer+MAX_BIGINT_SIZE-m_size, buffer+MAX_BIGINT_SIZE-m_size);   // ** Adapted for util_sc ** //
        buffer_size = m_size;

    }

}


/************************************************************************************************************************************************
 * BYTE* accessURI(BYTE *datain, unsigned int Lc)
 ************************************************************************************************************************************************/

BYTE* accessURI(BYTE *datain, unsigned int Lc) {

    BYTE *uri;
    BYTE uri_size;

    if (mode != MODE_ROOT && mode != MODE_WORKING)
        mExitSW(ERR_BAD_MODE ^ mode);   // ** Adapted for util_sc ** //

    if (Lc < 5)
        mExitSW(ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA ^ 5);  // ** Adapted for util_sc ** //

    checkPin(datain);

    uri = datain + PIN_SIZE;
    uri_size = Lc - PIN_SIZE;

    if (uri_size > MAX_URI_SIZE)
        mExitSW(ERR_URI_TOO_LARGE); // ** Adapted for util_sc ** //

    return uri;

}

/************************************************************************************************************************************************
 * void getBlobstoreInformations(unsigned int* first_available_index, unsigned int *blobcount, unsigned int *uri_index, unsigned char *uri, BYTE uri_size)
 *
 * first_available_index will point to the first free blob
 * location. If there is no more space available, then
 * first_available_index = MAX_NUMBER_OF_BLOBS.
 *
 * When uri != null (in which case, uri_size must be specified),
 * uri_index will be initialized to the index of the blob with this
 * uri. If no such uri exists, then uri_index = MAX_NUMBER_OF_BLOBS.
 ************************************************************************************************************************************************/

void getBlobstoreInformations(unsigned int* first_available_index, unsigned int *blobcount, unsigned int *uri_index, unsigned char *uri, BYTE uri_size) {

    unsigned int i;

    *first_available_index = MAX_NUMBER_OF_BLOBS;
    *blobcount = 0;
    *uri_index = MAX_NUMBER_OF_BLOBS;

    for (i = 0; i < MAX_NUMBER_OF_BLOBS; i++) {
        if (blob_catalog[i].exists) {

            (*blobcount)++;

            if (uri != NULL && uri_size == blob_catalog[i].uri_size && mem_cmp(uri, blob_catalog[i].uri, uri_size) == 0) {  // ** Adapted for util_sc ** //
                *uri_index = i;
            }

        } else {

            if (*first_available_index == MAX_NUMBER_OF_BLOBS)
                *first_available_index = i;

        }
    }

}

/************************************************************************************************************************************************
 * void encrypt(BYTE *password, BYTE label)
 *
 * Encrypt the buffer of size buffer_size under the given
 * password. Store the result at the begining of buffer.
 ************************************************************************************************************************************************/

void encrypt(BYTE *password, BYTE label) {

    temp_buffer_size = 0;
    mem_cpy(temp_buffer+temp_buffer_size, master_backup_key, MASTER_BACKUP_KEY_SIZE);   // ** Adapted for util_sc ** //
    temp_buffer_size += MASTER_BACKUP_KEY_SIZE;
    mem_cpy(temp_buffer+temp_buffer_size, password, PASSWORD_SIZE); // ** Adapted for util_sc ** //
    temp_buffer_size += PASSWORD_SIZE;
    mem_cpy(temp_buffer+temp_buffer_size, &label, 1);   // ** Adapted for util_sc ** //
    temp_buffer_size += 1;

    // ** Adapted for util_sc ** // SHA256(temp_buffer, temp_buffer_size, temp_buffer);
    mSecureHash(temp_buffer_size, 32, temp_buffer, temp_buffer);    // ** Adapted for util_sc ** //
    temp_buffer_size = 16;

    // temp_buffer contains K (16 bytes)

    // encryption of buffer under key = temp_buffer (first 16 bytes), with this device id

    // create pad, make it start at temp_buffer+16
    pad_size = 0;

    mem_set(temp_buffer+16+pad_size, 0, 4); // ** Adapted for util_sc ** //
    pad_size += 4;

    mem_cpy(temp_buffer+16+pad_size, &buffer_size, 2);  // ** Adapted for util_sc ** //
    pad_size += 2;

    mem_cpy(temp_buffer+16+pad_size, &device_id, ID_SIZE);  // ** Adapted for util_sc ** //
    pad_size += ID_SIZE;

#ifdef TEST_MODE
    memset(temp_buffer+16+pad_size, 0xaa, 8);
#else
    getRandomBytes(temp_buffer+16+pad_size, 8);
#endif
    pad_size += 8;

    // temp_buffer contains K (16 bytes) || pad (16 bytes)

    // encrypt with AES128
    // void multosAESECBEncipher (BYTE *plainText, BYTE *cipherText, BYTE keyLength, BYTE *key);
    mAESECBEncipher(temp_buffer+16, temp_buffer+32, 16, temp_buffer);  // ** Adapted for util_sc ** //

    // temp_buffer contains K (16 bytes) || pad (16 bytes) || t (16 bytes)

    // SHA256(digest, plaintext_length, plaintext)
    // ** Adapted for util_sc ** // SHA256(temp_buffer+48, 32, temp_buffer);
    mSecureHash(32, 32, temp_buffer+48, temp_buffer);   // ** Adapted for util_sc ** //

    // temp_buffer contains K (16 bytes) || pad (16 bytes) || t (16 bytes) || k (16 bytes) || c0 (16 bytes) (ok !)

    // right-pad buffer with 0x00 bytes until its size is a multiple of 16
    if ((buffer_size & 0xf) != 0) {  // mod 16
        mem_set(buffer+buffer_size, 0, 16-(buffer_size & 0xf)); // ** Adapted for util_sc ** //
        buffer_size += (16-(buffer_size & 0xf));
    }

    d = buffer_size / 16;

    // buffer = buffer1 || ... || buffer_d where size(buffer_i) = 16 bytes

    // crxAESEncryptCBC(BYTE *ciphertext, const BYTE *iv, const BYTE *plaintext, WORD plaintext_size, const BYTE *key)
    crxAESEncryptCBC(temp_buffer+80, temp_buffer+64, buffer, buffer_size, temp_buffer+48);

    // temp_buffer contains K (16 bytes) || pad (16 bytes) || t (16 bytes) || k (16 bytes) || c0 (16 bytes) || c_1 (16 bytes) || ... || c_d (16 bytes)

    buffer_size = 0;
    mem_cpy(buffer + buffer_size, temp_buffer+32, 16); // copy 't'  // ** Adapted for util_sc ** //
    buffer_size += 16;
    mem_cpy(buffer + buffer_size, temp_buffer+80, 16*d); // copy c_1 || ... || c_d  // ** Adapted for util_sc ** //
    buffer_size += (16*d);

}

/************************************************************************************************************************************************
 * void decrypt(BYTE *device_id_prim, BYTE *password, BYTE label)
 *
 * Decrypt the buffer of size buffer_size under the given
 * password. Store the result at the begining of buffer.
 *
 * Set device_id_prim to the value found during the decryption
 * process.
 ************************************************************************************************************************************************/

void decrypt(BYTE *device_id_prim, BYTE *password, BYTE label) {

    unsigned int L;

    temp_buffer_size = 0;
    mem_cpy(temp_buffer+temp_buffer_size, master_backup_key, MASTER_BACKUP_KEY_SIZE);   // ** Adapted for util_sc ** //
    temp_buffer_size += MASTER_BACKUP_KEY_SIZE;
    mem_cpy(temp_buffer+temp_buffer_size, password, PASSWORD_SIZE); // ** Adapted for util_sc ** //
    temp_buffer_size += PASSWORD_SIZE;
    mem_cpy(temp_buffer+temp_buffer_size, &label, 1);   // ** Adapted for util_sc ** //
    temp_buffer_size += 1;

    // ** Adapted for util_sc ** // SHA256(temp_buffer, temp_buffer_size, temp_buffer);
    mSecureHash(temp_buffer_size, 32, temp_buffer, temp_buffer);    // ** Adapted for util_sc ** //
    temp_buffer_size = 16;

    // temp_buffer contains : K (16 bytes)

    if ((buffer_size & 0xf) != 0)
        mExitSW(ERR_INVALID_BACKUP_ARCHIVE);    // ** Adapted for util_sc ** //

    d = (buffer_size - 16)/16;

    // buffer contains : t (16 bytes) || c_1 (16 bytes) || ... || c_d (16 bytes)

    mem_cpy(temp_buffer+32, buffer, 16);    // ** Adapted for util_sc ** //

    // temp_buffer contains : K (16 bytes) || nothing (16 bytes) || t (16 bytes)

    // void multosAESECBDecipher (BYTE *cipherText, BYTE *plainText, BYTE keyLength, BYTE *key);
    mAESECBDecipher (temp_buffer+32, temp_buffer+16, 16, temp_buffer);     // ** Adapted for util_sc ** //

    // temp_buffer should contain : K (16 bytes) || pad (16 bytes) || t (16 bytes)
    // where pad = 0x00 0x00 0x00 0x00 || L (2 bytes) || deviceId' (2 bytes) || z (8 bytes)

    mem_cpy(device_id_prim, temp_buffer+22, 2); // ** Adapted for util_sc ** //

    mem_set(mem_session.small_buffer, 0, 4);    // ** Adapted for util_sc ** //
    if (mem_cmp(temp_buffer+16, mem_session.small_buffer, 4) != 0)  // ** Adapted for util_sc ** //
        mExitSW(ERR_INVALID_BACKUP_ARCHIVE);    // ** Adapted for util_sc ** //

    mem_cpy(&L, temp_buffer+20, 2); // ** Adapted for util_sc ** //

    if (L < 16*(d-1)+1 || L > 16*d)
        mExitSW(ERR_INVALID_BACKUP_ARCHIVE);    // ** Adapted for util_sc ** //

    // SHA256(digest, plaintext_length, plaintext)
    // ** Adapted for util_sc ** // SHA256(temp_buffer+48, 32, temp_buffer);
    mSecureHash(32, 32, temp_buffer+48, temp_buffer);   // ** Adapted for util_sc ** //

    // temp_buffer contains : K (16 bytes) || pad (16 bytes) || t (16 bytes) || k (16 bytes) || c_0 (16 bytes)

    mem_cpy(temp_buffer+80, buffer+16, 16*d);   // ** Adapted for util_sc ** //

    // temp_buffer contains : K (16 bytes) || pad (16 bytes) || t (16 bytes) || k (16 bytes) || c_0 (16 bytes) || c_1 (16 bytes) || ... || c_d (16 bytes)

    // crxAESDecryptCBC(BYTE *plaintext, const BYTE *iv, const BYTE *ciphertext, WORD ciphertext_size, const BYTE *key)
    crxAESDecryptCBC(buffer, temp_buffer+64, temp_buffer+80, 16*d, temp_buffer+48);

    // buffer contains : data_1 (16 bytes) || ... || data_d (16 bytes)

    mem_set(mem_session.small_buffer, 0, 16*d - L); // ** Adapted for util_sc ** //
    if (mem_cmp(buffer+L, mem_session.small_buffer, 16*d - L) != 0) // ** Adapted for util_sc ** //
        mExitSW(ERR_INVALID_BACKUP_ARCHIVE);    // ** Adapted for util_sc ** //

    buffer_size = L;

}

/************************************************************************************************************************************************
 * void print(BYTE *s, unsigned int size)
 *
 ************************************************************************************************************************************************/

void print(void *s, unsigned int size) {

    mem_cpy(apdu_data.dataout, (BYTE *)s, size);    // ** Adapted for util_sc ** //

    exitLa(size);

}

/************************************************************************
 * void output_large_data()
 *
 * This routine expects the global variable *remaining_position to
 * point at the begining of the data to be sent. The global variable
 * remaining_size should specify the total length of the data to be
 * sent (which can be larger than 255).
 ************************************************************************/

void output_large_data(void) {

    WORD output_size = 0;

    if (remaining_size == 0) {
        multosExit();
    }

    output_size = MIN(remaining_size, MAX_APDU_OUTPUT_DATA_SIZE);

    mem_cpy(apdu_data.dataout, remaining_position, output_size);    // ** Adapted for util_sc ** //

    remaining_position = remaining_position + output_size;
    remaining_size -= output_size;

    if(remaining_size == 0){
        exitLa(output_size);
    }
    else if(remaining_size >= 0xff) {
        exitSWLa(0x61ff, 0xFF);
    }
    else {
        exitSWLa(0x6100+remaining_size, 0xFF);
    }

}

/******************************************************************************
 * void segmentToStaticHigh(void *high_addr, const void *low_addr, size_t size)
 *
 * This routine copies the content of the buffer located in the normal
 * address space (ram of e2), starting at address low_addr, to the the
 * buffer (possibly) located in the higher part of the static memory,
 * starting at address high_addr. If high_addr+size < 0x8000, then
 * this routine can be replace by a memcpy.
 ******************************************************************************/

/**
 // TODO :
 * Estos dos se usan solo una vez cada uno en el main para leer y escribir blobs
 * por lo que una copia de arrays debería bastar.
 *
 */


void segmentToStaticHigh(void *high_addr, const void *low_addr, DWORD size)    // ** Adapted for util_sc ** //
{

    BYTE high_addr_32bits[4] = {0x00, 0x00, 0x00, 0x00};

    // compute high_addr_32bits
    mem_cpy(high_addr_32bits+2, &high_addr, 2); // ** Adapted for util_sc ** //

    // call MEMORY COPY ADDITION STATIC (non atomic)
    __push ((__typechk(WORD, size))); // size of the data to copy
    __push (__BLOCKCAST(4)(__typechk(BYTE *, high_addr_32bits))); // push the static offset
    __push ((__typechk(WORD, (WORD)(low_addr)))); // address of the data in the low memory
    __code (__PRIM, 0xDD, 0x80);

}

/******************************************************************************
 * void staticHighToSegment(void *low_addr, const void *high_addr, size_t size)
 *
 * This routine copies the content of the buffer (possibly) located in
 * the high address space, starting at address high_addr, to the the
 * buffer located in the lower part of the memory (ram of e2),
 * starting at address low_addr.
 ******************************************************************************/

void staticHighToSegment(void *low_addr, const void *high_addr, DWORD size)    // ** Adapted for util_sc ** //
{

    BYTE high_addr_32bits[4] = {0x00, 0x00, 0x00, 0x00};

    // compute high_addr_32bits
    mem_cpy(high_addr_32bits+2, &high_addr, 2); // ** Adapted for util_sc ** //

    // call MEMORY COPY ADDITION STATIC (non atomic)
    __push ((__typechk(WORD, size))); // size of the data to copy
    __push ((__typechk(WORD, (WORD)(low_addr)))); // address of the data in the low memory
    __push (__BLOCKCAST(4)(__typechk(BYTE *, high_addr_32bits))); // push the static offset
    __code (__PRIM, 0xDD, 0x81);

}