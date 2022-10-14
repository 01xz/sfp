#include "sfp.hh"
#include "utils.h"
#include "pack.h"
#include "op.h"

#include <cstdio>
#include <cmath>

using namespace std;

SFP::SFP(SFP_UTYPE bits, int es, int fs) :
    bits(bits),
    es(es),
    fs(fs)
{
}

SFP::SFP(int es, int fs) :
    SFP::SFP(SFP_ZERO, es, fs)
{
}

bool SFP::isZero() const
{
    return util_is_zero(bits, es);
}

bool SFP::isNeg() const
{
    return util_is_neg(bits);
}

int SFP::nBits() const
{
    return util_sfp_nbits(es, fs);
}

int SFP::bias() const
{
    return util_sfp_bias(es);
}

bool SFP::sign() const
{
    return util_sfp_sign(bits);
}

SFP_STYPE SFP::exp() const
{
    return util_sfp_exp(bits, es, fs);
}

SFP_UTYPE SFP::frac() const
{
    return util_sfp_frac(bits, es, fs);
}

SFP SFP::zero() const
{
    return SFP(SFP_ZERO, es, fs);
}

SFP SFP::absMax() const
{
    return SFP(LMASK(SFP_MAX, nBits()), es, fs);
}

SFP SFP::absMin() const
{
    return SFP(LSHIFT(SFP_MIN, SFP_WIDTH - (es + 1)), es, fs);
}

SFP SFP::max() const
{
    return absMax();
}

SFP SFP::min() const
{
    return absMax().neg();
}

SFP SFP::neg() const
{
    return SFP(bits ^ SFP_MSB, es, fs);
}

SFP SFP::abs() const
{
    return (isNeg() ? neg() : *this);
}

SFP SFP::add(const SFP& s) const
{
    if(isZero()) {
        return s;
    } else if (s.isZero()) {
        return *this;
    } else if (neg().eq(s)) {
        return zero();
    }

    unpacked_t ua = unpack_sfp(bits, es, fs);
    unpacked_t ub = unpack_sfp(s.bits, s.es, s.fs);
    unpacked_t ur = op_add(ua, ub);

    return SFP(pack_sfp(ur, es + 1, fs + 1), es + 1, fs + 1);
}

SFP SFP::sub(const SFP& s) const
{
    if(isZero()) {
        return s.neg();
    } else if (s.isZero()) {
        return *this;
    } else if (eq(s)) {
        return zero();
    }

    unpacked_t ua = unpack_sfp(bits, es, fs);
    unpacked_t ub = unpack_sfp(s.bits, s.es, s.fs);
    unpacked_t ur = op_sub(ua, ub);

    return SFP(pack_sfp(ur, es + 1, fs + 1), es + 1, fs + 1);
}

SFP SFP::mul(const SFP& s) const
{
    if (isZero() || s.isZero()) {
        return zero();
    }

    unpacked_t ua = unpack_sfp(bits, es, fs);
    unpacked_t ub = unpack_sfp(s.bits, s.es, s.fs);
    unpacked_t ur = op_mul(ua, ub);

    return SFP(pack_sfp(ur, es + 1, fs + 1), es + 1, fs + 1);
}

bool SFP::eq(const SFP& s) const
{
    if (isZero() && s.isZero()) {
        return true;
    }
    return (bits == s.bits);
}

float SFP::getFloat() const
{
    if (isZero()) {
        return 0.0;
    }

    return pack_float(unpack_sfp(bits, es, fs));
}

void SFP::setBits(SFP_UTYPE s)
{
    bits = LSHIFT(s, SFP_WIDTH - nBits());
}

SFP_UTYPE SFP::getBits() const
{
    return RSHIFT(bits, SFP_WIDTH - nBits());
}

void SFP::print() const
{
    SFP s = abs();

    printf("sfp<%d,%d> ", es, fs);

    for (int i = SFP_WIDTH - 1; i >= SFP_WIDTH - nBits(); i--) {
        printf("%d", RSHIFT(bits, i) & 1);
    }

    printf(" -> ");
    printf(isNeg() ? "-" : "+");

    for (int i = SFP_WIDTH - 2; i >= SFP_WIDTH - nBits(); i--) {
        printf("%d", RSHIFT(s.bits, i) & 1);
        if (i != SFP_WIDTH - nBits() && (i == SFP_WIDTH - 1 - s.es)) {
            printf(" ");
        }
    }

    printf(" = %g", getFloat());
    // printf(" (sign: %d, exp: %d, frac: %d(%x))", sign(), exp(), RSHIFT(frac(), SFP_WIDTH - fs), frac());
    printf("\n");
}

SFP operator+(const SFP& a, const SFP& b)
{
    return a.add(b);
}

SFP operator-(const SFP& a, const SFP& b)
{
    return a.sub(b);
}

SFP operator*(const SFP& a, const SFP& b)
{
    return a.mul(b);
}

SFP operator-(const SFP& a)
{
    return a.neg();
}
