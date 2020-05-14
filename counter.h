/* counter.h */

#include <systemc.h>
#include "jk.h"
#include "nand.h"

SC_MODULE(Counter){
    sc_in<bool> clk{"clk_count_in"};

    JK jk1, jk2, jk3, jk4;
    NAND nand;

    sc_signal<bool> VP1{"VP1"}, VP2{"VP2"},
                    VP3{"VP3"}, VP4{"VP4"},
                    VP5{"VP5"};

    sc_signal<bool> JKs{"JKs"};

    SC_CTOR(Counter): jk1("JK1"), jk2("JK2"),
                      jk3("JK3"), jk4("JK4"),
                      nand("nand")
    {

        jk1.J(JKs);
        jk1.K(JKs);

        jk2.J(JKs);
        jk2.K(JKs);

        jk3.J(JKs);
        jk3.K(JKs);

        jk4.J(JKs);
        jk4.K(JKs);

        jk1.reset(JKs);
        jk2.reset(JKs);

        /* соединение триггеров между собой */
        jk1.clk(clk);
        jk1.Q(VP1);

        jk2.clk(VP1);
        jk2.Q(VP2);

        jk3.clk(VP2);
        jk3.Q(VP3);

        jk4.clk(VP3);
        jk4.Q(VP4);

        /* подключение NAND */
        nand.A(VP3);
        nand.B(VP4);

        nand.F(VP5);

        jk3.reset(VP5);
        jk4.reset(VP5);

        /* начальное состояние */
        VP2.write(true);
        VP3.write(true);
        JKs.write(true);
    }
};
