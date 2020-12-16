/* main.cpp */

#include <systemc.h>
#include "tb.h"
#include "counter.h"

int sc_main(int argc, char* argv[]){
    Testbench tb1("tb1");
    Counter counter("counter");

    sc_clock Clock("Clock", 1, SC_US, 0.5, 0, SC_US, false);

    counter.clk(Clock);
    tb1.clk(Clock);

    cout << "*** Starting simulation ***" << endl;

    sc_trace_file* tf = sc_create_vcd_trace_file("trace");
    sc_trace(tf, counter.VP1, "VP1");
    sc_trace(tf, counter.VP2, "VP2");
    sc_trace(tf, counter.VP3, "VP3");

    sc_start();

    return 0;
}
