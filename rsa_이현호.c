#include <stdio.h>
#include <string.h>
#include <openssl/bn.h>

#define true 1
#define false 0

typedef struct _b11rsa_st {
    BIGNUM *e;
    BIGNUM *d;
    BIGNUM *n;
}BOB11_RSA;

BOB11_RSA *BOB11_RSA_new();
int BOB11_RSA_free(BOB11_RSA *b11rsa);

int BOB11_RSA_KeyGen(BOB11_RSA *b11rsa, int nBits);
int BOB11_RSA_Enc(BIGNUM *c, BIGNUM *m, BOB11_RSA *b11rsa);
int BOB11_RSA_Dec(BIGNUM *m,BIGNUM *c, BOB11_RSA *b11rsa);

int mrPrimalityTest(BIGNUM *n, uint32_t k){ //n 판정하려는 수, k 테스트 횟수
    
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *A = BN_new();
    BIGNUM *r = BN_new();
    BIGNUM *range = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *l = BN_new();
    BN_dec2bn(&l , "1");

    BIGNUM *result = BN_new();

    
    BIGNUM *divisor = BN_new();
    BN_dec2bn(&A , "2");

    BIGNUM *compare = BN_new();
    BN_dec2bn(&compare , "1");
    BIGNUM *compare2 = BN_new();
    BN_dec2bn(&compare2 , "1");
    BIGNUM *compare3 = BN_new();
    BN_dec2bn(&compare3 , "1");
    BIGNUM *compare4 = BN_new();
    BN_dec2bn(&compare4 , "2");
    
    //2^l과 q 구하기, n은 이미 홀수로 뽑았기에 if문에 홀수일 (나머지가 1일 조건) 조건은 지움
    while(true){
        
        //printf("test...\n");
        BN_exp(divisor, A, l, ctx);
        BN_div(q, r, n, divisor, ctx);
        if(BN_cmp(n,divisor) == -1){
            break;
        }
        BN_add(l, l, compare);
        //printf("%s\n",BN_bn2dec(l));

    }
    //printf("%s\n",BN_bn2dec(compare));
    //compare = 1
    BIGNUM *RandNum = BN_new();
    
    
    //BN_dec2bn(&A , "1");
    BN_sub(range, n, compare);
   
    
    while(k--){
         
        while(true){
            //printf("test2\n");
            BN_rand_range(RandNum, range);
            //오류 후보 1 if문
            if(BN_is_one(RandNum) || BN_is_zero(RandNum)){
                continue;
            }
            break;
        }

        BN_gcd(A, RandNum, n, ctx );
        //printf("%s\n",BN_bn2dec(A));
        //오류 후보 2 if문
        if (BN_is_one(A) == 0){
            return false; // Composite number
        }
        BN_mod_exp(RandNum, RandNum, q, n, ctx);
        
        if (BN_is_one(RandNum))
            continue;

        BN_copy(compare, l);
        //printf("%s\n",BN_bn2dec(l));
        BIGNUM *compare5 = BN_new();
        BN_dec2bn(&compare5, "1");
        BN_sub(compare5, n, compare5);
        //printf("%s\n",BN_bn2dec(compare5));
        while(true){
            //printf("%s\n",BN_bn2dec(compare5));
            //printf("test3\n");
            //BN_mod_exp(result ,RandNum, compare, n, ctx);
            BN_sub(compare2, compare, compare3);
            //printf("%s\n",BN_bn2dec(compare2));
            if(!BN_cmp(RandNum, compare5)){
                continue;
            }
            if(BN_is_one(compare2)){
                break;
            }
            BN_mod_exp(RandNum, RandNum, compare4 ,n, ctx); 
        }
        if(!BN_cmp(RandNum,compare5)){
            continue;
        }
       
        return false; //composite number
        

    }
    BN_free(A);
    BN_free(q);
    BN_CTX_free(ctx);
    //printf("통과\n");
    return true;
}
int ExpMod(BIGNUM *r, const BIGNUM *a, const BIGNUM *e, BIGNUM *m)
{
        BN_CTX *ctx = BN_CTX_new();
        BIGNUM *A = BN_new();
        BN_copy(A, a);
	
	    //left 2 right algorithm

        for(int i = BN_num_bits(e)-2; i >= 0; i--)
        {
                BN_mod_mul(A, A, A, m, ctx);
                
                if(BN_is_bit_set(e, i))
                        BN_mod_mul(A, A, a, m, ctx);
        }

        BN_copy(r, A);
        BN_free(A);

        if(ctx != NULL)
                BN_CTX_free(ctx);
        return 1;
}
BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a,const BIGNUM *b)
{
	BIGNUM *q = BN_new();
	BIGNUM *r = BN_new();
	BIGNUM *t0 = BN_new();
	BIGNUM *t1 = BN_new();
	BIGNUM *u0 = BN_new();
	BIGNUM *v0 = BN_new();
	BIGNUM *u1 = BN_new();
	BIGNUM *v1 = BN_new();
	BIGNUM *u2 = BN_new();
	BIGNUM *v2 = BN_new();

	BIGNUM *compare = BN_new();

	BN_CTX *ctx = BN_CTX_new();
	
	BN_copy(t0, a);
	BN_copy(t1, b);
	
	BN_dec2bn(&u0 , "1");
	BN_dec2bn(&v0, "0");
	BN_dec2bn(&u1, "0");
	BN_dec2bn(&v1, "1");
	BN_dec2bn(&compare, "0");

	while(BN_cmp(t1, compare)){
			
		BN_div(q, r, t0, t1, ctx);
		BN_copy(t0, t1);
		BN_copy(t1, r);
		
		BN_mul(u2, q, u1, ctx);
		BN_sub(u2, u0, u2);
		BN_mul(v2, q, v1, ctx);
        BN_sub(v2, v0, v2);
	
		BN_copy(u0,u1);
		BN_copy(v0,v1);
		BN_copy(u1,u2);
		BN_copy(v1,v2);
	}
	BN_copy(x, u0);
	BN_copy(y, u0);
	return t0;

}
void PrintUsage()
{
    printf("usage: rsa [-k|-e e n plaintext|-d d n ciphertext]\n");
}

int main (int argc, char *argv[])
{
    BOB11_RSA *b11rsa = BOB11_RSA_new();
    BIGNUM *in = BN_new();
    BIGNUM *out = BN_new();

    if(argc == 2){
        if(strncmp(argv[1],"-k",2)){
            PrintUsage();
            return -1;
        }
        BOB11_RSA_KeyGen(b11rsa,1024);
        BN_print_fp(stdout,b11rsa->n);
        printf(" ");
        BN_print_fp(stdout,b11rsa->e);
        printf(" ");
        BN_print_fp(stdout,b11rsa->d);
    }else if(argc == 5){
        if(strncmp(argv[1],"-e",2) && strncmp(argv[1],"-d",2)){
            PrintUsage();
            return -1;
        }
        BN_hex2bn(&b11rsa->n, argv[3]);
        BN_hex2bn(&in, argv[4]); //단 평문을 16진수로 입력해야함
        if(!strncmp(argv[1],"-e",2)){
            BN_hex2bn(&b11rsa->e, argv[2]);
            BOB11_RSA_Enc(out,in, b11rsa);
        }else if(!strncmp(argv[1],"-d",2)){
            BN_hex2bn(&b11rsa->d, argv[2]);
            BOB11_RSA_Dec(out,in, b11rsa);
        }else{
            PrintUsage();
            return -1;
        }
        BN_print_fp(stdout,out);
    }else{
        PrintUsage();
        return -1;
    }

    if(in != NULL) BN_free(in);
    if(out != NULL) BN_free(out);
    if(b11rsa!= NULL) BOB11_RSA_free(b11rsa);

    return 0;
}

BOB11_RSA *BOB11_RSA_new()
{
    BOB11_RSA* RSA_struct = (BOB11_RSA*)malloc(sizeof(BOB11_RSA));
    RSA_struct->e = BN_new();
    RSA_struct->n = BN_new();
    RSA_struct->d = BN_new();
    return RSA_struct;
}

int BOB11_RSA_free(BOB11_RSA *b11rsa)
{
    BN_free(b11rsa->d);
    BN_free(b11rsa->e);
    BN_free(b11rsa->n);
    free(b11rsa);
    return 0;
}

int BOB11_RSA_KeyGen(BOB11_RSA *b11rsa, int nBits){
    
    BN_CTX *ctx = BN_CTX_new();
    int PrimeBits = nBits/2;
    
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    //BN_hex2bn(&p,"17" );
    //BN_hex2bn(&q,"13");
    //printf("p = %s\n",BN_bn2hex(p));
    //printf("q = %s\n",BN_bn2hex(q));
    // BN_hex2bn(&p,"C485F491D12EA7E6FEB95794E9FE0A819168AAC9D545C9E2AE0C561622F265FEB965754C875E049B19F3F945F2574D57FA6A2FC0A0B99A2328F107DD16ADA2A" );
    // BN_hex2bn(&q,"F9A91C5F20FBBCCC4114FEBABFE9D6806A52AECDF5C9BAC9E72A07B0AE162B4540C62C52DF8A8181ABCC1A9E982DEB84DE500B27E902CD8FDED6B545C067CE4F");
    //두 서로다른 n/2 비트 소수 생성
    //BIGNUM *p = BN_new();
    //BIGNUM *q = BN_new();
    while(true){
        //두 랜덤한 홀수 뽑기
        BN_priv_rand(p, PrimeBits, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ODD);
        BN_priv_rand(q, PrimeBits, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ODD);
        if(mrPrimalityTest(p,30) && mrPrimalityTest(q, 30) ){ //30 회 테스트
            
            break;
            
        }
    }
    
    
    BIGNUM *N = BN_new();

    BN_mul(N, p, q, ctx);
    BN_copy(b11rsa->n, N);
    
    //오일러 파이함수 생성
    BIGNUM *phi = BN_new();
    BIGNUM *p1 = BN_new();
    BIGNUM *q1= BN_new();
    BIGNUM *c = BN_new();
    BN_dec2bn(&c , "1");
    // printf("c = %s\n",BN_bn2hex(c));
    // printf("N = %s\n",BN_bn2hex(N));
    BN_sub(p1, p, c);
    //printf("p1 = %s\n",BN_bn2dec(p1));
    
    BN_sub(q1, q, c);
    //printf("q1 = %s\n",BN_bn2dec(q1));
    BN_mul(phi, p1, q1, ctx);
    //printf("phi = %s\n",BN_bn2dec(phi));
    //공개키 선택 b11rsa->e 단 gcd(e, 오일러파이함수) = 1  int BN_gcd(BIGNUM *r, BIGNUM *a, BIGNUM *b, BN_CTX *ctx);
    
    while(true){
        BN_rand_range(b11rsa->e, phi);
        BN_gcd(p1, b11rsa->e, phi, ctx);
        //printf("p1 = %s\n",BN_bn2hex(p1));
        if(BN_is_one(p1) == 0)
            continue;
        break;
    }
    
    //printf("e = %s\n",BN_bn2dec(b11rsa->e));
    //비밀키 d 생성
    XEuclid( b11rsa->d, q1, b11rsa->e ,phi);
    BN_mod_exp(b11rsa->d, b11rsa->d, c, phi, ctx);
    //printf("q1 = %s\n",BN_bn2hex(q1));
    //printf("d = %s\n",BN_bn2hex(b11rsa->d));
}

int BOB11_RSA_Enc(BIGNUM *c, BIGNUM *m, BOB11_RSA *b11rsa){
    
    ExpMod(c ,m ,b11rsa->e, b11rsa->n);
    //printf("%s\n\n",BN_bn2hex(b11rsa->n));
    //printf("%s\n\n",BN_bn2hex(b11rsa->e));
    // printf("%s\n",BN_bn2hex(m));
    // printf("%s\n",BN_bn2hex(c));
    return 1;

}
int BOB11_RSA_Dec(BIGNUM *m,BIGNUM *c, BOB11_RSA *b11rsa){

    ExpMod(m ,c ,b11rsa->d, b11rsa->n);

    return 1;
}