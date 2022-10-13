#include "pack.h"
#include "utils.h"

SFP_UTYPE pack_sfp(unpacked_t us, int es, int fs)
{
    SFP_UTYPE sign = us.sign ? SFP_MSB : SFP_ZERO;
    SFP_UTYPE exp = LHIDE(LSHIFT(us.exp + util_sfp_bias(es), SFP_WIDTH - (1 + es)), 1);
    SFP_UTYPE frac = LMASK(RSHIFT(us.frac, 1 + es), (1 + es + fs));

    return (sign | exp | frac);
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
