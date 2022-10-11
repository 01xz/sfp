#include "sfp.hh"
#include "utils.hh"

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
    return (LHIDE(LMASK(bits, es + 1), 1) == SFP_ZERO);
}

bool SFP::isNeg() const
{
    return ((SFP_STYPE)bits < 0);
}

int SFP::nBits() const
{
    return (1 + es + fs);
}

int SFP::bias() const
{
    return (POW2(es - 1));
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

// SFP SFP::add(const SFP& p) const
// {
//     if(isZero()) {
//         return p;
//     } else if (p.isZero()) {
//         return *this;
//     } else if (neg().eq(p)) {
//         return zero();
//     }
// }

float SFP::getFloat() const
{
    if (isZero()) {
        return 0.0;
    }

    uint32_t fsign;
    uint32_t fexp;
    uint32_t ffrac;

    fsign = LMASK(bits, 1) << 16;
    fexp = ((LHIDE(bits, 1) >> (SFP_WIDTH - (es + 1))) + 127 - bias()) << 23;
    ffrac = LHIDE(bits, es + 1) << (23 - (SFP_WIDTH - (es + 1)));

    union {
        float f;
        uint32_t u;
    } un;
    
    un.u = fsign | fexp | ffrac;
    return un.f;
}

void SFP::setBits(SFP_UTYPE b)
{
    bits = LSHIFT(b, SFP_WIDTH - nBits());
}

void SFP::print() const
{
    SFP p = abs();

    printf("sfp<%d,%d> ", es, fs);

    for (int i = SFP_WIDTH - 1; i >= SFP_WIDTH - nBits(); i--) {
        printf("%d", RSHIFT(bits, i) & 1);
    }

    printf(" -> ");
    printf(isNeg() ? "-" : "+");

    for (int i = SFP_WIDTH - 2; i >= SFP_WIDTH - nBits(); i--) {
        printf("%d", RSHIFT(p.bits, i) & 1);
        if (i != SFP_WIDTH - nBits() && (i == SFP_WIDTH - 1 - p.es)) {
            printf(" ");
        }
    }

    printf(" = %g", getFloat());
    // printf(" bias: %d", bias());
    printf("\n");
}
