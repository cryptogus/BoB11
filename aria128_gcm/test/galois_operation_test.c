#include "../galois_operation.h"
#include <stdio.h>

/***
 * ******** build command ********
 * gcc galois_operation_test.c ../galois_operation.c -o galois
 * 
 * ******** test vector ********
 * https://asecuritysite.com/gf/sage01
 * 5 * 35 = 175(0xaf)
 * 7 * 33 = 231(0xe7)
 * 0x80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 * 3(0b00000011) = 0x80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 e1
 * */

int main()
{
    uint8_t src[16] ={0,};
    src[15] = 0x80;
   
    uint8_t src2[16] ={0,};
    src2[0] = 0b00000011;
    
    uint8_t des[16] = {0,};
    galois_operation(src, src2, des);
    for (int i = 15; i >= 0; i--)
        printf("%02x ",des[i]);
    printf("\n");
}