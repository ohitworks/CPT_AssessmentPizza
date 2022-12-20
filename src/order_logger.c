/**
  **************************** AssessmentPizza: order_logger.c ****************************
  * Created by oh it works on 2022/12/20.
  * @file
  * @author     oh it works
  * @date       2022-12-20
  * @brief      logger for order
  **************************** AssessmentPizza: order_logger.c ****************************
 */

#include "order_logger.h"
#include "menu.h"
#include "pizza.h"
#include "file_io.h"

#include <iso646.h>
#include <string.h>
#include <stdlib.h>


int write_log(const ChainTableManager *name, const ChainTableManager *menu_pizzas, const ChainTableManager *pizzas,
              const char *path) {
    ChainTableManager file_append;
    ChainTableManager *string;
    Pizza *pizza;
    MenuPizza *menu;
    char buffer[3];
    int ret = 0, is_empty = 1;

    chain_table_init(&file_append);

    chain_table_append(&file_append, sizeof(ChainTableManager), true);
    string = chain_table_get(&file_append, -1);
    chain_table_init(string);
    string_extend(string, "[", 1, 12);
    string_extend_string(string, name);
    string_extend(string, "]", 1, 2);

    for (int index = 0; index < pizzas->length; index++) {
        pizza = chain_table_get(pizzas, index);
        menu = menu_get_pizza_from_info(menu_pizzas, pizza);
        if (menu != NULL and menu->number > 0) {
            chain_table_append(&file_append, sizeof(ChainTableManager), true);
            string = chain_table_get(&file_append, -1);
            chain_table_init(string);
            string_extend_string(string, &pizza->name);

            memset(buffer, 0, sizeof(buffer));
            itoa(menu->number, buffer, 10);
            chain_table_append(&file_append, sizeof(ChainTableManager), true);
            string = chain_table_get(&file_append, -1);
            chain_table_init(string);
            string_extend(string, buffer, -1, 2);

            is_empty = 0;
        }
    }

    chain_table_append(&file_append, sizeof(ChainTableManager), true);
    string = chain_table_get(&file_append, -1);
    chain_table_init(string);
    string_extend(string, "\n", -1, 2);

    if (is_empty) {
        ret = write_lines_to_file_with_mode(&file_append, path, "a");
    }

    chain_table_clear(&file_append, FREE_AS_MANAGER);

    return ret;
}
