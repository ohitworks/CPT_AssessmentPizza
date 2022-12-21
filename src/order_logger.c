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

#include <stdio.h>
#include <iso646.h>
#include <string.h>
#include <stdlib.h>

#ifndef itoa
#define itoa _itoa
#endif


int write_log(const ChainTableManager *username, const ChainTableManager *menu_pizzas, const ChainTableManager *pizzas,
              const char *path) {
    ChainTableManager file_append;
    ChainTableManager *string;
    Pizza *pizza;
    MenuPizza *menu;
    char buffer[3];
    int ret = 0, is_not_empty = 0;

    chain_table_init(&file_append);

    chain_table_append(&file_append, sizeof(ChainTableManager), true);
    string = chain_table_get(&file_append, -1);
    chain_table_init(string);
    string_extend(string, "[", 1, 12);
    string_extend_string(string, username);
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

            is_not_empty = 1;
        }
    }

    chain_table_append(&file_append, sizeof(ChainTableManager), true);
    string = chain_table_get(&file_append, -1);
    chain_table_init(string);
    string_extend(string, "\n", -1, 2);

    if (is_not_empty) {
        ret = write_lines_to_file_with_mode(&file_append, path, "a");
    }

    chain_table_clear(&file_append, FREE_AS_MANAGER);

    return ret;
}


int show_log(const ChainTableManager *username, const char *log_path) {
    ChainTableManager file, name_key;
    ChainTableManager *string;

    chain_table_init(&name_key);
    string_extend(&name_key, "[", 1, 10);
    string_extend_string(&name_key, username);
    string_extend(&name_key, "]", 1, 1);

    read_ascii_file_lines(log_path, &file);

    for (int index = 0; index < file.length; index++) {
        string = chain_table_get(&file, index);
        if (string_equal(string, &name_key)) {
            do {
                string_print(string);
                printf("\n");
                index += 1;
                string = chain_table_get(&file, index);
            } while (string->length > 0);
        }
    }

    return 0;
}
