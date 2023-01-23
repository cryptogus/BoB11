#include "galois_operation.h"

// little endian, GF(2^128)상에서의 곱셈 연산 -> 128bits galois multiplication
// ============= reference =============
// https://committee.tta.or.kr/data/reportDown.jsp?news_num=4712 -> 47p
void galois_operation(uint8_t *input1, uint8_t *input2, uint8_t *output)
{
    uint8_t input1_1[16] = {0,};
    memcpy(input1_1, input1, 16);
    //strcpy(dest, src)
    //memcpy(dest, src, strlen(src)+1);
    uint8_t cbit[16] = {0,};

    for (int i = 0; i < 128; i++)
    {
        if ( ((input2[i / 8] >> (i % 8)) & 0x01) == 1)
        {
            for (int j = 0; j < 16; j++)
            {
                output[j] ^= input1_1[j];

            }
        }

        if ( (input1_1[15] & 0x80) == 0 )
        {
            
            for (int j = 0; j < 16; j++)
            {
                if (input1_1[j] & 0x80)
                {
                    input1_1[j] <<= 1;
                    cbit[j] = 1;
                }else
                {
                    input1_1[j] <<= 1;
                }
            }
            for (int k = 0; k < 15; k++)
            {
                input1_1[k + 1] |= cbit[k];
            }
            
        }
        else
        {
            for (int j = 0; j < 16; j++)
            {
                if (input1_1[j] & 0x80)
                {
                    input1_1[j] <<= 1;
                    cbit[j] = 1;
                }else
                {
                    input1_1[j] <<= 1;
                }
            }
            for (int k = 0; k < 15; k++)
            {
                input1_1[k + 1] |= cbit[k];
            }
            input1_1[0] ^= 0b11100001;
        }
        memset(cbit, 0, 16);
    }
}