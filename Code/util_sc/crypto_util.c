/*************************** HEADER FILES ***************************/
#include <crypto_util.h>
#include <string.h>
// #include <memory.h>


/********************************************************************/
/******************************SHA256********************************/
/********************************************************************/

// MACROS
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

// VARIABLES
static const DWORD k[64] = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
        0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
        0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
        0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
        0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

// FUNCTION DEFINITIONS
void sha256_transform(SHA256_CTX *ctx, const BYTE data[])
{
    DWORD a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    for ( ; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (i = 0; i < 64; ++i) {
        t1 = h + EP1(e) + CH(e,f,g) + k[i] + m[i];
        t2 = EP0(a) + MAJ(a,b,c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

void sha256_init(SHA256_CTX *ctx)
{
    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

void sha256_update(SHA256_CTX *ctx, const BYTE data[], WORD len)
{
    DWORD i;

    for (i = 0; i < len; ++i) {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == 64) {
            sha256_transform(ctx, ctx->data);
            ctx->bitlen += 512;
            ctx->datalen = 0;
        }
    }
}

void sha256_final(SHA256_CTX *ctx, BYTE hash[])
{
    DWORD i;

    i = ctx->datalen;

    // Pad whatever data is left in the buffer.
    if (ctx->datalen < 56) {
        ctx->data[i++] = 0x80;
        while (i < 56)
            ctx->data[i++] = 0x00;
    }
    else {
        ctx->data[i++] = 0x80;
        while (i < 64)
            ctx->data[i++] = 0x00;
        sha256_transform(ctx, ctx->data);
        memset(ctx->data, 0, 56);
    }

    // Append to the padding the total message's length in bits and transform.
    ctx->bitlen += ctx->datalen * 8;
    ctx->data[63] = ctx->bitlen;
    ctx->data[62] = ctx->bitlen >> 8;
    ctx->data[61] = ctx->bitlen >> 16;
    ctx->data[60] = ctx->bitlen >> 24;
    ctx->data[59] = ctx->bitlen >> 32;
    ctx->data[58] = ctx->bitlen >> 40;
    ctx->data[57] = ctx->bitlen >> 48;
    ctx->data[56] = ctx->bitlen >> 56;
    sha256_transform(ctx, ctx->data);

    // Since this implementation uses little endian byte ordering and SHA uses big endian,
    // reverse all the bytes when copying the final state to the output hash.
    for (i = 0; i < 4; ++i) {
        hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
    }
}





/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/

void shift_right(BYTE *arr, WORD length)
{

    WORD i;
    for (i = length-1;  i > 0;  --i)
    {
        arr[i] = (arr[i] >> 1) | ((arr[i-1] << 7) & 128);
    }
    arr[0] = arr[0] >> 1;

}


BOOL isZero(BYTE *arr, WORD length)
{
    int i;
    for(i=0; i<length; i++)
    {
        if(arr[i]!=0)
            return 0;
    }
    return 1;
}

void fillZeros(BYTE *arr, WORD length)
{
    int i;
    for(i=0; i<length; i++)
    {
        arr[i]=0;
    }
}


BOOL isEqual(BYTE *arr1, BYTE *arr2, WORD length)
{
    int i;
    for(i=0; i<length; i++)
    {
        if(arr1[i]!=arr2[i])
            return 0;
    }
    return 1;
}

void copyFromTo(BYTE *src, BYTE *dst, WORD lenght)
{
    for(WORD i=0; i<lenght; ++i){
        dst[i] = src[i];
    }
}


void module(BYTE *base, BYTE *modulus, WORD modulusLength)
{
    //TODO
}


void modular_add(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length)
{
    // Apply modulo to the operands
    module(arr1, modulus, length);
    module(arr2, modulus, length);

    WORD carry = 0;
    for(WORD i=length - 1; i>=0; --i){      // Big Endian
        carry = arr1[i] + arr2[i] + carry;
        result[i] = carry & 0xFF;
        carry >> 8;
    }
    //  if carry is != 0 after the loop, it means that result can't store the addition initialy and the module will fail
    if(carry!=0){
        BYTE auxArr[length+1];
        copyFromTo(result, auxArr+1, length); //copy result to the last positions of auxArr
        auxArr[0] = carry & 0xFF;
        module(auxArr, modulus, length+1);
        copyFromTo(auxArr+1, result, length);
    }
    else {
        module(result, modulus, length);
    }
}


/**
 * Stores in result the value of (arr1*arr2) mod modulus
 * Initialy the buffers must not supperpose
 * @param arr1
 * @param arr2
 * @param modulus
 * @param length
 */
void modular_product(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length)
{

}

// TODO: tener en cuenta si las operaciones permiten usar el mismo array de parámetro y salida
// TODO: usar arrays auxiliares para la solución, que no sobrescriban parámetros dados.
// TODO: Una vez funcionen las operaciones, intentar que puedan superponerse los arrays, y entonces
// TODO: sólo habrá que cambiar modular_exp que lo usa, poniendo como buffer de salida uno de los
// TODO: buffers de operador, que es mejor de cara a dar la opción a cómo usarlo y a que sea óptimo cuando pueda.


void modular_exponentiation(WORD exponentLength, WORD modulusLength,
                            BYTE *exponent, BYTE *modulus,
                            BYTE *base, BYTE *result)
{
    fillZeros(result, modulusLength);
    if(isZero(modulus, modulusLength))
    {
        return;     // if modulus = 1 then return 0
    }

    result[modulusLength-1]=1; // result := 1   // Multos is big endian

    module(base, modulus, modulusLength);  // base := base mod modulus

    BYTE aux[modulusLength];


    while(!isZero(exponent, exponentLength))    // while exponent > 0
    {
        if((exponent[exponentLength-1] & 1) == 1)   // if (exponent mod 2 == 1):
        {
            modular_product(aux, base, result, modulus, modulusLength);  // result := (result * base) mod modulus
            //todo asign aux to ..
        }

        shift_right(exponent, exponentLength);  // exponent := exponent >> 1

        modular_product(aux, base, base, modulus, modulusLength);    // base := (base * base) mod modulus
        //todo asign aux to ..

    }

    // return result

}


// TODO revisar de la implementación de BigInteger que dice esto:

//    Even more time consuming are exponentiations combined with modulus.
// Following method is not really optimal in speed but illustrates pretty
// well how exponentiation can be combined with the modulus:
//
//    INPUT: Base b, Exponent exp and Modulus m
//            OUTPUT: Result C = b ^ exp (mod m)
//    C = 1
//
//    while exp != 0 do
//    begin
//    if (exp & 0x01) then C = b * C (mod m)
//
//    b = b * b (mod m)
//
//    exp = exp >> 1
//    end
//
//            Using the Montgomery Exponentiation Algorithm we can speed up the proceeding. A good description is given in Handbook of Applied Cryptography. The Montgomery Multiplication is explained by algorithm 14.36 and can be done as follows:
//
//    INPUT: Base b, Exponent exp and Modulus m
//            OUTPUT: Result C = b ^ exp (mod m)
//





/********************************************************************/
/*********************crxModularExponentiation***********************/
/********************************************************************/



// multos.h

//    #ifdef __FUNCTION_PROTOTYPES
//    void multosModularExponentiation (WORD exponentLength, WORD modulusLength,
//                                      BYTE *exponent, BYTE *modulus, BYTE *input,
//                                      BYTE *output);
//    #else
//    #define multosModularExponentiation(exponentLength, modulusLength, exponent, modulus, input, output) \
//    do \
//    { \
//        __push (__typechk(WORD, exponentLength)); \
//        __push (__typechk(WORD, modulusLength)); \
//        __push (__typechk(BYTE *, exponent)); \
//        __push (__typechk(BYTE *, modulus)); \
//        __push (__typechk(BYTE *, input)); \
//        __push (__typechk(BYTE *, output)); \
//        __code (__PRIM, __PRIM_MODULAR_EXPONENTIATION); \
//    } while (0)
//    #endif


//  #define __PRIM_MODULAR_EXPONENTIATION               0xC8


// main.h

//    #define crxModularExponentiation(exponentLength, modulusLength, exponent, modulus, input, output) \
//      if (exponentLength > modulusLength) exitSW(0x9F30); \
//      multosModularExponentiation(exponentLength, modulusLength, exponent, modulus, input, output)


// MDRM

//    Modular Exponentiation / RSA Sign
//    This primitive performs a modular exponentiation operation, the basis of the RSA algorithm. This version of the primitive will execute with full countermeasures to protect the algorithm.
//      Page 200
//      [...]



// CAPI


//    4.79 multosModularExponentiation
//    void multosModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output)
//    The parameters are:
//     WORD exponentLength: the length of the exponent used
//     WORD modulusLength: the length of the modulus
//     BYTE *exponent: address of the exponent
//     BYTE *modulus: address of the modulus
//     BYTE *input: address of the input value
//     BYTE *output: address of where to write the result of the operation
//    This function performs a modular exponentiation. Note that the values held at modulus, input and output are all considered to be of size modulusLength.
//    This is an interface to the primitive Modular Exponentiation.
//



// WIKIPEDIA

//    https://en.wikipedia.org/wiki/Modular_exponentiation#Right-to-left_binary_method

