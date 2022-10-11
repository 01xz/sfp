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
    return (bits == SFP_ZERO);
}

bool SFP::isNeg() const
{
    return ((SFP_STYPE)bits < 0);
}

int SFP::nBits() const
{
    return (1 + es + fs);
}

SFP SFP::zero() const
{
    return SFP(SFP_ZERO, es, fs);
}

SFP SFP::neg() const
{
    return SFP(bits ^ SFP_MSB, es, fs);
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

void SFP::setBits(SFP_UTYPE b)
{
    bits = LSHIFT(b, SFP_WIDTH - nBits());
}

void SFP::print() const
{
    SFP p = (isNeg() ? neg() : *this);

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

    // printf(" = %lg", getDouble());

    printf("\n");
}
