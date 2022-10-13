#ifndef __SFP_HH
#define __SFP_HH

#include "sfp_types.h"

class SFP
{
private:
    SFP_UTYPE bits;
    int es;
    int fs;

public:
    SFP(SFP_UTYPE bits, int es,int fs);
    SFP(int es, int fs);

    bool isZero() const;
    bool isNeg() const;

    int nBits() const;
    int bias() const;
    bool sign() const;
    SFP_STYPE exp() const;
    SFP_UTYPE frac() const;

    SFP zero() const;
    SFP absMax() const;
    SFP absMin() const;
    SFP max() const;
    SFP min() const;

    SFP neg() const;
    SFP abs() const;

    SFP add(const SFP& s) const;        // x + s
    SFP sub(const SFP& s) const;        // x - s
    SFP mul(const SFP& s) const;        // x * s
    SFP div(const SFP& s) const;        // x / s

    bool eq(const SFP& s) const;        // x == s
    bool gt(const SFP& s) const;        // x > s
    bool ge(const SFP& s) const;        // x >= s
    bool lt(const SFP& s) const;        // x < s
    bool le(const SFP& s) const;        // x <= s

    void set(SFP s);                    // x = s
    void set(float n);                  // x = n
    void set(double n);                 // x = n

    float getFloat() const;             // n = x
    double getDouble() const;           // n = x

    // debug
    void setBits(SFP_UTYPE bits);
    SFP_UTYPE getBits() const;
    void print() const;
};

class SFP33: public SFP
{
public:
    SFP33();
    SFP33(SFP v);
    SFP33(float v);
    SFP33(double v);
};

#endif
