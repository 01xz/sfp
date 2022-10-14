#include "pack.h"
#include "utils.h"

SFP_UTYPE pack_sfp(unpacked_t us, int es, int fs)
{
    SFP_UTYPE sign = us.sign ? SFP_MSB : SFP_ZERO;
    SFP_UTYPE exp = LHIDE(LSHIFT(us.exp + util_sfp_bias(es), SFP_WIDTH - (1 + es)), 1);
    SFP_UTYPE frac = LMASK(RSHIFT(us.frac, 1 + es), (1 + es + fs));

    return (sign | exp | frac);
}

float pack_float(unpacked_t us)
{
    uint32_t fsign = us.sign ? SFP_MSB : SFP_ZERO;
    uint32_t fexp = LHIDE(LSHIFT(us.exp + 127, 23), 1);
    uint32_t ffrac = RSHIFT(us.frac, 1 + 8);

    union {
        float f;
        uint32_t u;
    } un;

    un.u = fsign | fexp | ffrac;
    return un.f;
}

double pack_double(unpacked_t us)
{
    uint64_t fsign = us.sign ? LSHIFT((uint64_t)SFP_MSB, 32) : LSHIFT((uint64_t)SFP_ZERO, 32);
    uint64_t fexp = LSHIFT((uint64_t)(us.exp + 1023), 52);
    uint64_t ffrac = RSHIFT(LSHIFT((uint64_t)us.frac, 32), 1 + 11);

    union {
        double d;
        uint64_t u;
    } un;

    un.u = fsign | fexp | ffrac;
    return un.d;
}

unpacked_t unpack_sfp(SFP_UTYPE s, int es, int fs)
{
    unpacked_t us;
    bool sign = util_sfp_sign(s);
    SFP_STYPE exp = util_sfp_exp(s, es, fs);
    SFP_UTYPE frac = util_sfp_frac(s, es, fs);

    us.sign = sign;
    us.exp = exp;
    us.frac = frac;

    return us;
}
