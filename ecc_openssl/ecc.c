#include <stdio.h>
#include <openssl/obj_mac.h>
#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/err.h>

EC_GROUP *create_curve(void)
{
    EC_GROUP *curve;

    /* https://wiki.openssl.org/index.php/Elliptic_Curve_Cryptography */

    /* Create the curve */
    if (NULL == (curve = EC_GROUP_new_by_curve_name(NID_secp256k1)))
    {
        fprintf(stderr, "curve is not created!\n");
        return NULL;
    }

    return curve;
}
EC_POINT *create_generator(EC_GROUP *curve)
{
    /* Create generator from curve*/
    EC_POINT *generator = EC_POINT_new(curve); // 그냥 이대로  사용하면 point at infinity로 초기화

    if (generator == NULL)
    {
        fprintf(stderr, "Error creating generator!\n");
        EC_GROUP_free(curve); // Cleanup
        return NULL;
    }

    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    if (BN_hex2bn(&x, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798") &&
        BN_hex2bn(&y, "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"))
    {

        if (EC_POINT_set_affine_coordinates(curve, generator, x, y, NULL) == 1)
        {
            printf("Generator is set.\n");
        }
        else
        {
            fprintf(stderr, "Error setting generator coordinates.\n");
        }
    }
    else
    {
        fprintf(stderr, "Error setting BN values for Gx, Gy.\n");
    }
    
    if (EC_POINT_is_at_infinity(curve, generator) == 1)
    {
        printf("Generator is point at infinity.\n");
    }
    BN_free(x);
    BN_free(y);
    BN_CTX_free(ctx);

    return generator;
}

void generate_random_point(EC_GROUP *curve)
{

    EC_POINT *point = EC_POINT_new(curve);
    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    if (EC_POINT_is_on_curve(curve, point, ctx) != 1)
        fprintf(stderr, "Error: point is not on curve!\n");

    // point가 무한원점인지 확인
    if (EC_POINT_is_at_infinity(curve, point) == 1)
    {
        printf("Point is at infinity.\n");
    }
    BN_dec2bn(&x, "100");
    BN_dec2bn(&y, "123213123");
    if (point != NULL && x != NULL && y != NULL && ctx != NULL)
    {
        if (EC_POINT_set_affine_coordinates(curve, point, x, y, ctx) == 1)
        {

            printf("Generated Point (x, y):\n");
            printf("x: %s\n", BN_bn2hex(x));
            printf("y: %s\n", BN_bn2hex(y));
        }
        else
        {
            fprintf(stderr, "Error getting point coordinates!\n");
        }
        BN_free(x);
        BN_free(y);
        BN_CTX_free(ctx); // BN_CTX 해제
        EC_POINT_free(point);
    }
}

int main(void)
{

    EC_GROUP *curve = create_curve();
    EC_POINT *generator = create_generator(curve);
    if (curve != NULL)
    {
        generate_random_point(curve);

        // Clean up
        EC_GROUP_free(curve); // Free curve
    }
    // 에러 정보 출력
    ERR_print_errors_fp(stderr);

    return 0;
}