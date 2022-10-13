#include "op.h"

unpacked_t add(unpacked_t a, unpacked_t b, bool sign)
{

}

unpacked_t sub(unpacked_t a, unpacked_t b, bool sign)
{

}

unpacked_t op_add(unpacked_t a, unpacked_t b)
{
    if (a.sign == b.sign) {
        return add(a, b, a.sign);
    } else {
        return sub(a, b, a.sign);
    }
}

unpacked_t op_eadd(unpacked_t a, unpacked_t b)
{
    if (a.sign == b.sign) {
        return add(a, b, a.sign);
    } else {
        return sub(a, b, a.sign);
    }
}

unpacked_t op_mul(unpacked_t a, unpacked_t b)
{
    unpacked_t r;

    SFP_LUTYPE afrac = HIDDEN_BIT(a.frac);
    SFP_LUTYPE bfrac = HIDDEN_BIT(b.frac);
    SFP_UTYPE frac = RSHIFT(afrac * bfrac, SFP_WIDTH);
    SFP_STYPE exp = a.exp + b.exp + 1;

    if ((frac & SFP_MSB) == 0) {
        exp--;
        frac = LSHIFT(frac, 1);
    }

    r.sign = a.sign ^ b.sign;
    r.exp = exp;
    r.frac = LSHIFT(frac, 1);

    return r;
}
