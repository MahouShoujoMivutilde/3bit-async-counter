/* nand.h */

#include <systemc.h>

SC_MODULE(NAND){
    sc_in<bool> A{"A"}, B{"B"};
    sc_out<bool> F{"F"};

    void inner_logic() {
        F.write( !(A.read() && B.read()) );
    }

    SC_CTOR(NAND){
        SC_METHOD(inner_logic);

        /* чувствителен к изменениям A и B */
        sensitive << A << B;
    }
};
