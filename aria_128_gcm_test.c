#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
/****
 * =======build command on ubuntu linux======
 *
 *        gcc -o aria_128_gcm aria_128_gcm_test.c -lcrypto -g
 */

int main(int argv, char *argc[])
{
    //https://www.openssl.org/docs/man1.1.1/man3/EVP_aria_192_ecb.html
    //https://www.openssl.org/docs/man1.1.1/man3/EVP_EncryptInit.html
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    unsigned char *key = "Jefe";
    unsigned char *iv = "1234";
    unsigned char *in = "kookmin banking1234";
    EVP_EncryptInit_ex(ctx, EVP_aria_128_gcm(), NULL, key, iv);
    
    unsigned char out[256] = {0,};
    unsigned char out2[256] = {0,};
    int len = sizeof(out);
    
    EVP_EncryptUpdate(ctx, out, &len, in, strlen(in));
    printf("ciphertext length: %d\n",len);
    printf("ciphertext: %s\n\n", out);
    // EVP_EncryptFinal_ex(ctx, out, &len);
    // printf("%d\n",len);
    // printf("%s\n", out);

    EVP_DecryptInit_ex(ctx, EVP_aria_128_gcm(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, out2, &len, out, strlen(out));
    printf("plaintext length: %d\n",len);
    printf("plaintext:%s\n", out2);
    
    EVP_CIPHER_CTX_free(ctx);
    
}
/*
https://github.com/openssl/openssl/blob/master/include/crypto/evp.h
    290 줄 struct evp_cipher_st 정의 -> EVP_CIPHER
    const EVP_CIPHER * cipher = EVP_aria_128_cbc();

https://github.com/openssl/openssl/blob/master/crypto/evp/e_aria.c

# define BLOCK_CIPHER_generic(nid,keylen,blocksize,ivlen,nmode,mode,MODE,flags) \
static const EVP_CIPHER aria_##keylen##_##mode = { \
        nid##_##keylen##_##nmode,blocksize,keylen/8,ivlen, \
        flags|EVP_CIPH_##MODE##_MODE,   \
        EVP_ORIG_GLOBAL,                \
        aria_init_key,                  \
        aria_##mode##_cipher,           \
        NULL,                           \
        sizeof(EVP_ARIA_KEY),           \
        NULL,NULL,NULL,NULL };          \
const EVP_CIPHER *EVP_aria_##keylen##_##mode(void) \
{ return &aria_##keylen##_##mode; }


#define BLOCK_CIPHER_aead(keylen,mode,MODE)        \
static const EVP_CIPHER aria_##keylen##_##mode = { \
        NID_aria_##keylen##_##mode,                \
        1, keylen/8, 12,                           \
        ARIA_AUTH_FLAGS|EVP_CIPH_##MODE##_MODE,    \
        EVP_ORIG_GLOBAL,                           \
        aria_##mode##_init_key,                    \
        aria_##mode##_cipher,                      \
        aria_##mode##_cleanup,                     \
        sizeof(EVP_ARIA_##MODE##_CTX),             \
        NULL,NULL,aria_##mode##_ctrl,NULL };       \
const EVP_CIPHER *EVP_aria_##keylen##_##mode(void) \
{ return (EVP_CIPHER*)&aria_##keylen##_##mode; }
*/

/*
## 연산자

 

 그럼 ## 연산자의 역할은 무엇일까요?



##은 두 개의 토큰을 이어준다. 혹은 붙여준다. 의 의미로 생각하시면 됩니다. 


===============================
#define INT_i(n)    int i##n;
===============================


위와 같은 매크로가 있고, 함수내에서 INT_i(0) 이라는 매크로를 사용했다고 가정합시다.



그렇다면 위의 매크로는 받아온 n이라는 변수를 i##n 와 같이 i하고 붙여준 int형 변수를 선언하게 됩니다. 





즉 위의 매크로와 같은 표현은 



int i0;



입니다. i와 0을 붙여서 하나의 변수로 만들어진것입니다.
*/
