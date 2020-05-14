/* tb.h */

#include <systemc.h>

SC_MODULE(Testbench){
    sc_in<bool> clk{"clk"};

    void bench() {
        /* начальное состояние триггеров
         * уже было задано внутри счетчика */

        /* тестируем переключения */
        wait(30, SC_US);
        sc_stop();
    }
    SC_CTOR(Testbench){
        SC_THREAD(bench);
        sensitive << clk.neg();
    }
};
