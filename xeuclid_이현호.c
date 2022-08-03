#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a)
{
        char *number_str = BN_bn2dec(a);
        printf("%s %s\n", msg, number_str);
        OPENSSL_free(number_str);
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
	BN_copy(y, v0);
	return t0;

}

int main(int argc, char *argv[])
{
	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *x = BN_new();
	BIGNUM *y = BN_new();
	BIGNUM *gcd;

	if(argc != 3){
		printf("usage: xeuclid num1 num2");
		return -1;
	}
	BN_dec2bn(&a, argv[1]);
	BN_dec2bn(&b, argv[2]);
	gcd = XEuclid(x, y, a, b);

	printBN("(a,b) = ", gcd);
	printBN("a = ", a);
	printBN("b = ", b);
	printBN("x = ", x);
	printBN("y = ", y);
	printf("%s*(%s) + %s*(%s) = %s\n", BN_bn2dec(a), BN_bn2dec(x), BN_bn2dec(b), BN_bn2dec(y), BN_bn2dec(gcd));

	if(a != NULL) BN_free(a);
	if(b != NULL) BN_free(b);
	if(x != NULL) BN_free(x);
	if(y != NULL) BN_free(y);
	if(gcd != NULL) BN_free(gcd);

	return 0;
}
