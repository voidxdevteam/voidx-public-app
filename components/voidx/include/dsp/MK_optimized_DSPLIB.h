#ifndef MK_OPTIMIZED_DSPLIB_H_
#define MK_OPTIMIZED_DSPLIB_H_
#include "../../platform/platform.h"

#define S_FRAME_INV_F					(1.0f / (float)SIGNAL_FRAME)

void MK_blk_move_SFRAME(const float * src, float *restrict dst);
void MK_blk_move_SFRAME_UNROLLED(const float * src, float *restrict dst, unsigned int size);
void MK_mem_clean_SFRAME_UNROLLED(float * restrict mem, unsigned int size);
void MK_vecMul_SFRAME(const float * restrict x1, const float * restrict x2, float * y);
void MK_vecMul_SFRAME_UNROLLED(const float * restrict x1, const float * restrict x2, float * y, unsigned int size);
void MK_vecIncrement_SFRAME(float * restrict x1_y, const float * restrict x2);
void MK_vecOffset_SFRAME(float * restrict x, float offset);
void MK_w_vec_SFRAME(const float * x1, const float * x2, const float m, float *restrict y);
void MK_w_vec_SFRAME_UNROLLED(const float * x1, const float * x2, const float m, float *restrict y, unsigned int size);
void MK_biquad_SFRAME(float *restrict x, float *b, float *a, float * delay, float *restrict y);
void MK_vec_sum_SFRAME(float * restrict x1, const float * restrict x2, float * y);
void MK_vec_sum_SFRAME_UNROLLED(float * restrict x1, const float * restrict x2, float * y, unsigned int size);
float MK_vec_sum_square_SFRAME(const float * x);
float MK_vec_sum_elements_SFRAME(const float * x);
float MK_vec_sum_elm_SFRAME(const float * x);
void MK_vec_scale2_SFRAME(const float * x, float * restrict y, float scale_factor);
void MK_vec_scale_SFRAME(float * restrict x, float scale_factor);
void MK_iir4(float *restrict y1, const float * x, float *restrict y2, const float * hb, const float * ha);
float MK_L1_SFRAME(float *restrict x);
void MK_abs_SFRAME(const float * x, float * restrict y);
float MK_max_SFRAME(float *restrict x);
void MK_abs_SFRAME_UNROLLED(float *restrict x, float * restrict y, unsigned int size);
void MK_vec_cube_SFRAME_UNROLLED(float *restrict x, float * restrict y, unsigned int size);
float MK_DSPF_sp_lms(const float *x, float *restrict h, const float *y_i, float *restrict y_o, const float ar, float error, const int nh, const int ny);
void MK_vecrecip_SFRAME_UNROLLED(const float * x, float *restrict y, const int size);
float MK_dotprod_SFRAME_UNROLLED(const float * x, const float * y, const int size);
void MK_fircirc_SFRAME_UNROLLED(const float *x, float *h, float *restrict y, const int index, const int csize, const int nh, const int ny);
float modulations_get_fractional_index_value(float * array, float index);
float modulations_get_fractional_index_value_bounded(float * array, float index, unsigned int bound_value_and);
float MK_peak_SFRAME(const float * x);



#endif /* MK_OPTIMIZED_DSPLIB_H_ */
