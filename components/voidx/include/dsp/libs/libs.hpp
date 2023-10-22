#pragma once

#include "../../codec/CodecInterface.hpp"

#define SIGNAL_FRAME (SAMPLING_FRAME)
#define SAMPLE_FREQ  (SAMPLING_FREQ)
#define DATA_ALIGN(x)

#define _nassert(x)
#define _amemd8(x) (*((double *)(x)))
#define _amemd8_const(x) (*((const double *)(x)))
#define _rcpsp(x) (1.0f/(x))
#define _hif2(x) (((float *)(&x))[1])
#define _lof2(x) (((float *)(&x))[0])
#define _hi(x) (((float *)(&x))[1])
#define _lo(x) (((float *)(&x))[0])
#define _itof(x) (*((float *)(&x)))
#define _fabsf(x) ((x)<0 ? (-x) : (x))
#define _fabs(x) ((x)<0 ? (-x) : (x))
#define _rcpsp(x) (1.0f/(x))

#include "mkMath.hpp"
#include "eq_utils.hpp"
#include "MK_optimized_MATHLIB.hpp"
#include "MK_optimized_DSPLIB.hpp"
