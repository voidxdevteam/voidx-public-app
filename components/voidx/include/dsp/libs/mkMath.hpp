#ifndef MKMATH_H_
#define MKMATH_H_

#define MAX_UINT_F                      4294967295.0f
#define MAX_MATRIX_SIZE                 256

extern unsigned char brev[64];
extern float mk_ones[256];
extern float * mk_identity8[8];
extern float mk_zeros[2048];
//output *= input complesso
void complexMultiply(unsigned int N, float * input, float * output);
//normalizza ir
void scale_ir(float *ir, int n, float gain);
float max_vec_pos(float *vec, int n);
float get_norm_ir(float *ir, int n);
void hann(float * realArray, int N);
void normalize_ir(float *ir, int n);
//reverse ir
void time_reverse_ir(float *ir, int n);


void twiddle_gen (float *w, int n);
//modulo di vettore complesso, N = numero di elementi complessi, l'out ha N elementi reali
void complexAbsArray(unsigned int N, float * inputArray, float * outputArray);
void complexSquareArray(unsigned int N, float * inputArray, float * outputArray);
void complexDivision(unsigned int N, float * num, float * den, float * result);
//N pari = numero di elementi, prende un vettore reale e butta fuori un complesso (prealloca 2*N);
void hilbert(unsigned int N, float * inputArray, float * outputArray);
//estrai parte immaginaria da vettore complesso
void getMinusImag(unsigned int N, float * inputArray, float * outputArray);
//estrai parte reale da vettore complesso
void getReal(unsigned int N, float * inputArray, float * outputArray);
//estrai il log di un array
void logArray(unsigned int N, float * inputArray, float * outputArray);
//prende un modulo di dft, setta la fase e butta nell'array complesso outputArray
void setPhase(unsigned int N, float * absDft, float * phase, float * outputArray);
//da magnitude tira fuori IR a fase minima
void Magnitude2MinPhase(unsigned int N, float * absDft, float * mPhIr);

void real2Complex(unsigned int N, float * realArray, float * complexArray);
void complexRemoveImag(unsigned int N, float * cplxArray);
void real2ComplexLeftPad(unsigned int N, unsigned int pad, float * realArray, float * complexArray);
void real2ComplexRightPadReversed(unsigned int N, unsigned int pad, float * realArray, float * complexArray);
void real2ComplexRightPadReversedBlend(unsigned int N, unsigned int pad, float * realArray, float * complexArray, float on, float off);
float IRPower(float * ir, int n);

void LUPSolve(float **A, int *P, float *b, int N, float *x);
void LUPInvert(float **A, int *P, int N, float **IA);
int LUPDecompose(float **A, int N, float Tol, int *P);
float solveYWSystem(float * correlation, float * x, int N);

//dsp natural functions
float DSPF_sp_dotprod_natural(const float * x, const float * y, const int nx);
void DSPF_sp_w_vec_natural(const float *x1, const float *x2, const float m, float * y, const int n);
void DSPF_sp_blk_move_natural(const float * x, float * y, const int n);
void DSPF_sp_biquad_natural(float * x, float *b, float *a, float *delay, float * y, const int nx);
void DSPF_sp_fftSPxSP_natural(int N, float *ptr_x, float *ptr_w, float *ptr_y, unsigned char *brev, int n_min, int offset, int n_max);
void DSPF_sp_ifftSPxSP_natural (int N, float *ptr_x, float *ptr_w, float *ptr_y, unsigned char *brev, int n_min, int offset, int n_max);

#endif /* MKMATH_H_ */
