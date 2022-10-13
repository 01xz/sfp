#ifndef __SFP_PACK_H
#define __SFP_PACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sfp_types.h"

typedef struct {
    bool sign;
    SFP_STYPE exp;
    SFP_UTYPE frac;
} unpacked_t;

SFP_UTYPE pack_sfp(unpacked_t us, int es, int fs);

unpacked_t unpack_sfp(SFP_UTYPE s, int es, int fs);

#ifdef __cplusplus
}
#endif

#endif
