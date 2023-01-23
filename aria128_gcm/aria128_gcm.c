#include <openssl/evp.h>
/*************
 * https://stackoverflow.com/questions/12153009/openssl-c-example-of-aes-gcm-using-evp-interfaces
 * https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption#Authenticated_Encryption_using_GCM_mode
 *  
 */
int main()
{
    const EVP_CIPHER *cipher = NULL;
    cipher = EVP_aria_128_gcm();

}

