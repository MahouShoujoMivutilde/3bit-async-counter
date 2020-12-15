/* counter.h */

#include <systemc.h>
#include "jk.h"

SC_MODULE(Counter){
    sc_in<bool> clk{"clk_count_in"};

    JK jk1, jk2, jk3;

    sc_signal<bool> VP1{"VP1"}, VP2{"VP2"},
                    VP3{"VP3"};

    sc_signal<bool> JKs{"JKs"};

    SC_CTOR(Counter): jk1("JK1"), jk2("JK2"),
                      jk3("JK3")
    {

        jk1.J(JKs);
        jk1.K(JKs);

        jk2.J(JKs);
        jk2.K(JKs);

        jk3.J(JKs);
        jk3.K(JKs);

        /* -P */
        jk1.set(JKs);
        jk2.set(JKs);
        jk3.set(JKs);

        /* соединение триггеров между собой */
        jk1.clk(clk);
        jk1.Q(VP1);

        jk2.clk(VP1);
        jk2.Q(VP2);

        jk3.clk(VP2);
        jk3.Q(VP3);

        /* начальное состояние */
        VP2.write(true);
        VP3.write(true);
        JKs.write(true);
    }
};
