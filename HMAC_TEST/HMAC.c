/**
* HMAC TEST with OpenSSL 1.1.1
* 
* Reference
* 
* https://www.openssl.org/docs/man1.1.1/man3/EVP_sha256.html
* https://www.openssl.org/docs/man1.1.1/man3/HMAC.html
* 
* TEST VECTOR
* https://datatracker.ietf.org/doc/html/rfc4231#section-4
*
* Example
* https://github.com/Akagi201/hmac-sha1
* https://stackoverflow.com/questions/7591967/c-openssl-hmacsha1-works-but-not-how-i-want-it-to
* 
*/
//gcc -o HMAC HMAC.c -lcrypto

#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    
    unsigned char *key = "Jefe";
    unsigned char *Data = "what do ya want for nothing?";
    unsigned char output[256] = {0,};
    int len = sizeof(output);

    //HMAC_CTX_new() creates a new HMAC_CTX in heap memory.
    HMAC_CTX *ctx = HMAC_CTX_new();
    const EVP_MD *hash = EVP_sha256();
    //const EVP_MD *EVP_sha256(void);
    
    if(!HMAC(hash, key, strlen(key), Data, strlen(Data), output, &len))
    {
        fprintf(stderr,"HMAC function error\n");
        return 1;
    }

    HMAC_CTX_free(ctx);
    //fprintf(stdout,"%s\n", output);
    for(int i = 0; i < len; i++){
        fprintf(stdout, "%02x", output[i]);
    }
    fprintf(stdout,"\n");
    return 0;
}