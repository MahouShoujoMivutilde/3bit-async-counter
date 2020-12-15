/* jk.h */

#include <systemc.h>

SC_MODULE(JK){
    sc_in<bool> J{"J"}, K{"K"};
    sc_in<bool> clk{"clk"};
    sc_in<bool> reset{"reset"};

    sc_out<bool> Q{"Q"};

    void inner_logic() {
        if (!clk.read()) {
            if (J.read() == true && K.read() == true) {
                bool q = Q.read();
                cout << "@" << sc_time_stamp() << " " << name();
                cout << ": Q next = " << !q << endl;
                Q.write(!q);
            } else if (J.read() == true && K.read() == false) {
                Q.write(true);
            } else if (J.read() == false && K.read() == true) {
                Q.write(false);
            }
        }
        if (!reset.read()) {
            cout << "@" << sc_time_stamp() << " " << name();
            cout << ": reset" << endl;
            Q.write(false);
        }
    }

    SC_CTOR(JK){
        SC_METHOD(inner_logic);

        /* чувствителен к падениям clk и сбросу,
         * а также изменениям J и K */
        sensitive << clk.neg();
        sensitive << reset.neg();
        sensitive << J << K;
    }
};
