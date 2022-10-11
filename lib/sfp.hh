#ifndef __SFP_HH
#define __SFP_HH

#include "sfp_types.hh"

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

    SFP zero() const;

    SFP neg() const;

    SFP add(const SFP& p) const;        // x + p
    SFP sub(const SFP& p) const;        // x - p
    SFP mul(const SFP& p) const;        // x * p
    SFP div(const SFP& p) const;        // x / p

    bool eq(const SFP& p) const;        // x == p
    bool gt(const SFP& p) const;        // x > p
    bool ge(const SFP& p) const;        // x >= p
    bool lt(const SFP& p) const;        // x < p
    bool le(const SFP& p) const;        // x <= p

    void set(SFP p);                    // x = p
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
