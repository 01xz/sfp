#include "sfp.hh"

#include <cstdio>

int main(int argc, char *argv[])
{
    auto p = SFP(3, 3);

    for (unsigned i = 0; i < (unsigned)(1 << p.nBits()); i++) {
        p.setBits(i);
        p.print();
    }

    return 0;
}
