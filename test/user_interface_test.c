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
#include "customer.h"
#include "order_logger.h"
#include "user_interface.h"
#include "user_interface_tools.h"

#include <stdio.h>


int main() {

    ChainTableManager menu;
    ChainTableManager pizzas;
    ChainTableManager username;
    Pizza *pizza;

    char user_id[PASSWORD_LENGTH_MAX * 2];
    char buffer[128] = {0};

    chain_table_init(&username);
    string_extend(&username, "user", -1, 6);
    account_register("Hello return -1.", "1234567809", &username);

    string_extend(&username, "++", -1, 6);
    account_register("Hello return -2.", "password 123", &username);
//    account_change_password("Hello return -2.", "1234567809");

    menu_load_from_file(&menu, "pizzas.cfg");
    pizza_load_from_file(&pizzas, "pizzas.cfg");

    switch (ui_choose_role()) {
        case 0:
        default:
            return 0;
        case 1:
            screen_clear();
            user_id[PASSWORD_LENGTH_MAX] = '\0';
            ui_customer_register(user_id);
            break;
        case 2:
            screen_clear();
            if (ui_login_page(user_id) != 0){
                return 0;
            }
            break;
        case 3:
            // TODO
    }

    while (1) {
        pizza = ui_welcome_menu(&pizzas);
        if (pizza == NULL) {
            break;
        }
        printf("---\n update %d\n---\n", ui_show_pizza(&menu, pizza));
    }

    read_from_stdin(&username);

    string_read(&username, buffer, 128);

    printf("%s\n", buffer);

    chain_table_clear(&username, RETURN_IF_DYNAMIC);
    account_get_username(user_id, &username);
    write_log(&username, &menu, &pizzas, "log.cfg");
    chain_table_clear(&username, RETURN_IF_DYNAMIC);

    return 0;
}
