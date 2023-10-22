#ifndef MK_OPTIMIZED_MATHLIB_H_
#define MK_OPTIMIZED_MATHLIB_H_

#include "libs.hpp"

inline float cossp_i(float a){
    float   Zero   =  0.0; 
    float   MAX    =  1048576.0;
    float   MIN    =  2.4414062e-4;
    float   Sign   =  1;
    float   InvPI  =  0.318309886183791;
    float	  HalfPI =  1.5707963268;
    float   s4     =  2.601903036e-6;
    float   s3     = -1.980741872e-4;
    float   s2     =  8.333025139e-3;
    float   s1     = -1.666665668e-1;
    float   C1     =  3.140625;
    float   C2     =  9.67653589793e-4;
    float   X, Y, Z, F, G, R;
    int     N;

    Y = _fabsf(a) + HalfPI;

    if (Y > MAX) {
        Y = HalfPI;
    }

    X = Y * InvPI;            /* X = Y * (1/PI)         */
    N = (int)(X);            /* N = integer part of X  */
    Z = N;                    /* Z = float (N)          */
    
    if ((N&1) != 0) {
        Sign = -Sign;           /* quad. 3 or 4   */
    }

    F = (Y - (Z*C1)) - (Z*C2);      
    R = F;
    
    if (F < Zero) {
        R = -R;
    }

    if (R < MIN) {
        return (R*Sign); 
    }
    
    G = F*F;
    R = (((s4*G+s3)*G+s2)*G+s1)*G;      
    
    return ((F + F*R)*Sign);
}

inline float sinsp_i(float a){
    float InvPI =  0.318309886183791;
    float One   =  1.0;
    float MAX   =  1048576.0;
    float Zero  =  0.0;
    float s1    = -1.666665668e-1;
    float s2    =  8.333025139e-3; 
    float s3    = -1.980741872e-4;
    float s4    =  2.601903036e-6; 
    float C1    =  3.140625;
    float C2    =  9.67653589793e-4;
    float Sign, X, Y, Z, F, G, R;
    int   N;

    Sign = One;
    Y    = a;

    if (_fabsf(Y) > MAX) {
        Y = Zero;
    }

    X = Y * InvPI;            /* X = Y * (1/PI)  */
    N = (int)(X);            /* N = integer part of X  */
    Z = (float) N;                         
    
    if ((N & 1) != 0.0f) {
        Sign = -Sign;           /* Quadrant 3 or 4 */
    }

    F = (Y - Z*C1) - Z*C2;      
    G = F * F;
    R = (((s4*G + s3)*G + s2)*G + s1)*G;
            
    return ((F + F*R) * Sign);
}

inline float atan2f_sr1i_atan2spi (float g1, float pih, int s, int bn, int an){
	float coef;
	float	g2;
	float	g4;
	float	g6;
	float	g8;
	float	g10;
	float	g12;
	float	pol;
	float	tmp1;
	float	tmp2;
	float	c1 =  0.00230158202f;
	float	c2 = -0.01394551000f;
	float	c3 =  0.03937087815f;
	float	c4 = -0.07235669163f;
	float	c5 =  0.10521499322f;
	float	c6 = -0.14175076797f;
	float	c7 =  0.19989300877f;
	float	c8 = -0.33332930041f;
	int 	ns_nbn;
	
        /* get coef based on the flags */
        coef = pih;
    if (!s) {
        coef = 3.1415927f;
    }
    
    ns_nbn = s | bn;
    
    if (!ns_nbn) {
        coef = 0;
    }
    if (an) {
        coef = -coef;
    }
 
	/* calculate polynomial */
	g2  = g1*g1;
	g4  = g2*g2;
	g6  = g2*g4;
	g8  = g4*g4;
	g10 = g6*g4;
	g12 = g8*g4;

	tmp1 = ((c5 * g8) + (c6 * g6)) + ((c7 * g4) + (c8 * g2));
	tmp2 = (((c1 * g4 + c2 * g2) + c3) * g12) + (c4 * g10);

	pol = tmp1  + tmp2;
	pol = pol*g1 + g1;

	return (s ? (coef - pol) : (coef + pol));
}

inline float atan2sp_i (float a, float b){
    float   g, x, y;
    float   res;
    float   temp;
    float   pih = 1.570796327f;
    float   pi  = 3.141592741f;
    float   Max = 3.402823466E+38F;
    int     an;
    int     bn;
    int     s = 0;

    x  = a;
    y  = b;
    an = (a < 0);   /* flag for a negative */
    bn = (b < 0);   /* flag for b negative */

    /* swap a and b before calling division sub routine if a > b */
    if (_fabsf(a) > _fabsf(b)) {
        temp = b;
        b    = a;
        a    = temp;
        s    = 1;             /* swap flag */
    }

    g = a/b;
    
    /* do polynomial estimation */
    res = atan2f_sr1i_atan2spi (g, pih, s, bn, an);

    //switch the returns so that the answer is equivalent
    if (x == 0.0f) {
        res = (y >= 0.0f ? 0 : pi);
    }
    if (g > Max) {
        res = pih;
    }
    if (g < -Max) {
        res = -pih;
    }

    return (res);
}

static unsigned char brev_data[64] = {
    0x0, 0x20, 0x10, 0x30, 0x8, 0x28, 0x18, 0x38,
    0x4, 0x24, 0x14, 0x34, 0xc, 0x2c, 0x1c, 0x3c,
    0x2, 0x22, 0x12, 0x32, 0xa, 0x2a, 0x1a, 0x3a,
    0x6, 0x26, 0x16, 0x36, 0xe, 0x2e, 0x1e, 0x3e,
    0x1, 0x21, 0x11, 0x31, 0x9, 0x29, 0x19, 0x39,
    0x5, 0x25, 0x15, 0x35, 0xd, 0x2d, 0x1d, 0x3d,
    0x3, 0x23, 0x13, 0x33, 0xb, 0x2b, 0x1b, 0x3b,
    0x7, 0x27, 0x17, 0x37, 0xf, 0x2f, 0x1f, 0x3f
};

void twiddle_gen (float *w, int n);
void DSPF_sp_fftSPxSP_natural(int N, float *ptr_x, float *ptr_w, float *ptr_y, unsigned char *brev, int n_min, int offset, int n_max);

#endif /* MK_OPTIMIZED_MATHLIB_H_ */
