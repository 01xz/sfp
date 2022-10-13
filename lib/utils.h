#ifndef __SFP_UTILS_H
#define __SFP_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sfp_types.h"

#define LSHIFT(bits, shift) \
    ((shift) >= (int)(8 * sizeof(bits)) ? 0 : (bits) << (shift))

#define RSHIFT(bits, shift) \
    ((shift) >= (int)(8 * sizeof(bits)) ? 0 : (bits) >> (shift))

#define POW2(n) \
    (LSHIFT(1, (n)))

#define FLOORDIV(a, b) \
    ((a) / (b) - ((a) % (b) < 0))

#define MIN(a, b) \
    ((a) < (b) ? (a) : (b))

#define MAX(a, b) \
    ((a) > (b) ? (a) : (b))

#define LMASK(bits, size) \
    ((bits) & LSHIFT(SFP_MASK, SFP_WIDTH - (size)))

#define LHIDE(bits, size) \
    ((bits) & RSHIFT(SFP_MASK, size))

#define HIDDEN_BIT(frac) \
    (SFP_MSB | RSHIFT((frac), 1))

bool util_is_zero(SFP_UTYPE s, int es);
bool util_is_neg(SFP_UTYPE s);

SFP_UTYPE util_sfp_bias(int es);
int util_sfp_nbits(int es, int fs);

bool util_sfp_sign(SFP_UTYPE s);
SFP_STYPE util_sfp_exp(SFP_UTYPE s, int es, int fs);
SFP_UTYPE util_sfp_frac(SFP_UTYPE s, int es, int fs);

#ifdef __cplusplus
}
#endif

#endif
