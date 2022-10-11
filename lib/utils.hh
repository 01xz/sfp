#ifndef __SFP_UTILS_HH
#define __SFP_UTILS_HH

#ifdef __cplusplus
extern "C" {
#endif

#include "sfp_types.hh"

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

#define HIDDEN_BIT(frac) \
    (SFP_MSB | RSHIFT((frac), 1))

#ifdef __cplusplus
}
#endif

#endif
