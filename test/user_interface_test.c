/**
  **************************** AssessmentPizza: user_interface_test.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      UI tools tested here.
  **************************** AssessmentPizza: user_interface_test.c ****************************
 */

#include "pizza.h"
#include "password.h"
#include "user_interface.h"
#include "user_interface_tools.h"

#include <stdio.h>


int main() {

    ChainTableManager menu;
    ChainTableManager pizzas;

    Pizza *pizza;

    account_register("Hello return -1.", "1234567809");
    account_change_password("Hello return -1.", "password 123");
    account_register("Hello return -2.", "password 123");

    menu_load_from_file(&menu, "menu.cfg");
    pizza_load_from_file(&pizzas, "pizzas.cfg");

    while (1) {
        pizza = ui_welcome_menu(&pizzas);
        if (pizza == NULL) {
            break;
        }
        printf("---\nupdate %d\n---\n", ui_show_pizza(&menu, pizza));
    }

    return 0;
}
