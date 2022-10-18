#include <stdio.h>
#include <openssl/rand.h>

//GCC 컴파일시 OpenSSL 컴파일 옵션
//-> gcc test_random.c -lcrypto
int main(){
    unsigned char seed[30] = {0,};
    RAND_bytes(seed, 10);
    for(int i=0; i<30; i++)
        printf("%02x ",seed[i]);

    return 0;

}