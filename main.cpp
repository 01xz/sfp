#include "sfp.hh"

#include <cstdio>
#include <cassert>

int main(int argc, char *argv[])
{
    auto p = SFP(3, 3);
    auto q = SFP(3, 3);

    for (unsigned i = 0; i < (unsigned)(1 << p.nBits()); i++) {
        for (unsigned j = 0; j < (unsigned)(1 << p.nBits()); j++) {
            p.setBits(i);
            q.setBits(j);
            float pf = p.getFloat();
            float qf = q.getFloat();
            float r = pf * qf;
            auto sr = p.mul(q);
            // if ((r - sr.getFloat()) > 14.0) {
                printf("----------------------\n");
                p.print();
                q.print();
                printf("float: %g * %g = %g\n", pf, qf, r);
                sr.print();
            // }
        }
    }

    return 0;
}
