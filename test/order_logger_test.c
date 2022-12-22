/**
  **************************** AssessmentPizza: order_logger_test.c ****************************
  * Created by oh it works on 2022/12/20.
  * @file
  * @author     oh it works
  * @date       2022-12-20
  * @brief      Test order logger.
  **************************** AssessmentPizza: order_logger_test.c ****************************
 */

#include "order_logger.h"
#include "pizza.h"
#include "menu.h"
#include "user_interface.h"

Pizza pizza;
Pizza *pizza_ui;
ChainTableManager pizzas, menu_pizzas, name;

int main() {
//    pizza_load_from_file(&pizzas, "pizzas.cfg");
//    menu_load_from_file(&menu_pizzas, "pizzas.cfg");
//
    chain_table_init(&name);
    string_extend(&name, "UN", -1, 2);
//
//    while (1) {
//        pizza_ui = ui_order_one_menu(&pizzas);
//        if (pizza_ui == NULL) {
//            break;
//        }
//        ui_order_pizza(&menu_pizzas, pizza_ui);
//    }
//
//    write_log(&name, &menu_pizzas, &pizzas, "log.cfg");

    show_log(&name, "log.cfg");

    return 0;
}
