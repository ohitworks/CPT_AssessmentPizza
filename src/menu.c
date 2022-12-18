/**
  **************************** AssessmentPizza: menu.c ****************************
  * Created by oh-it-works on 2022/12/17.
  * @file
  * @author     oh it works
  * @date       2022-12-17
  * @brief      菜单操作
  **************************** AssessmentPizza: menu.c ****************************
 */

#include "menu.h"
#include "file_io.h"
#include "chain_table.h"

#include <iso646.h>
#include <string.h>
#include <stdlib.h>


/**
 * @brief              从文件加载菜单数组
 * @param menu_pizzas  被视为未初始化的链表
 * @param file_name
 * @return
 */
int menu_load_from_file(ChainTableManager *menu_pizzas, const char *file_name) {
    ChainTableManager file;
    ChainTableManager *line;
    MenuPizza *menu_pizza;
    char *end_ptr;
    char buffer[PIZZA_TYPE_NAME_MAX_LENGTH * 2];

    chain_table_init(menu_pizzas);
    chain_table_init(&file);
    read_ascii_file_lines(file_name, &file);

    for (int index = 0; index < file.length; index++) {
        line = chain_table_get(&file, index);
        memset(buffer, 0, sizeof(buffer));
        string_read(line, buffer, PIZZA_TYPE_NAME_MAX_LENGTH * 2);
        if (memcmp(buffer, "[menu pizza]", 12) == 0) {
            // 添加菜单
            chain_table_append(menu_pizzas, sizeof(MenuPizza), false);
            menu_pizza = chain_table_get(menu_pizzas, -1);
            // 写入 pizza 类型
            index += 1;
            memset(buffer, 0, sizeof(buffer));
            line = chain_table_get(&file, index);
            string_read(line, buffer, PIZZA_TYPE_NAME_MAX_LENGTH * 2);
            memcpy(menu_pizza->pizza_type, buffer, PIZZA_TYPE_NAME_MAX_LENGTH);
            // 写入 pizza 类型
            index += 1;
            memset(buffer, 0, sizeof(buffer));
            line = chain_table_get(&file, index);
            string_read(line, buffer, PIZZA_TYPE_NAME_MAX_LENGTH * 2);
            menu_pizza->pizza_size = (int) strtol(buffer, &end_ptr, 10);
            // 写入 pizza 价格
            index += 1;
            memset(buffer, 0, sizeof(buffer));
            line = chain_table_get(&file, index);
            string_read(line, buffer, PIZZA_TYPE_NAME_MAX_LENGTH * 2);
            menu_pizza->pizza_price = (int) strtol(buffer, &end_ptr, 10);
        }
    }
    return 0;
}

int menu_save_to_file_no_update(const ChainTableManager *menu_pizzas, const char *file_name) {
    ChainTableManager file;
    ChainTableManager *string;
    MenuPizza *menu_pizza;
    char buffer[8];

    chain_table_init(&file);

    for (int index = 0; index < menu_pizzas->length; index++) {
        menu_pizza = chain_table_get(menu_pizzas, index);
        // 添加一个新的成员
        // 写入标头
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);
        string_extend(string, "[menu pizza]", 12, 12);
        // 写入类型
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);
        string_extend(string, menu_pizza->pizza_type, -1, 12);
        // 写入大小
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);
        memset(buffer, 0, sizeof(buffer));
        itoa(menu_pizza->pizza_size, buffer, 10);
        string_extend(string, buffer, -1, 8);
        // 写入价格
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);
        memset(buffer, 0, sizeof(buffer));
        itoa(menu_pizza->pizza_price, buffer, 10);
        string_extend(string, buffer, -1, 8);
    }

    return write_lines_to_file(&file, file_name);
}


int menu_get_pizza_price(const ChainTableManager *menu_pizzas, const Pizza * pizza) {
    MenuPizza *menu;
    for (int index=0; index < menu_pizzas->length; index++) {
        menu = chain_table_get(menu_pizzas, index);
        if (pizza->size == menu->pizza_size and
            memcmp(pizza->type, menu->pizza_type, PIZZA_TYPE_NAME_MAX_LENGTH + 1) == 0) {
            // 匹配到了
            return menu->pizza_price;
        }
    }
    return -1;
}


MenuPizza * menu_get_pizza_from_info(const ChainTableManager *menu_pizzas, const Pizza * pizza) {
    MenuPizza *menu;
    for (int index=0; index < menu_pizzas->length; index++) {
        menu = chain_table_get(menu_pizzas, index);
        if (pizza->size == menu->pizza_size and
            memcmp(pizza->type, menu->pizza_type, PIZZA_TYPE_NAME_MAX_LENGTH + 1) == 0) {
            // 匹配到了
            return menu;
        }
    }
    return NULL;
}
