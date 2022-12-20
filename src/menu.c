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


#ifndef itoa
#define itoa _itoa
#endif


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

    chain_table_clear(&file, FREE_AS_MANAGER);

    return 0;
}

void menu_write_data_to_string_array(const ChainTableManager *menu_pizzas, ChainTableManager *string_array) {
    char buffer[8];
    MenuPizza *menu_pizza;
    ChainTableManager *string;

    chain_table_init(string_array);

    for (int index = 0; index < menu_pizzas->length; index++) {
        menu_pizza = chain_table_get(menu_pizzas, index);
        // 添加一个新的成员
        // 写入标头
        chain_table_append(string_array, sizeof(ChainTableManager), true);
        string = chain_table_get(string_array, -1);
        chain_table_init(string);
        string_extend(string, "[menu pizza]", 12, 12);
        // 写入类型
        chain_table_append(string_array, sizeof(ChainTableManager), true);
        string = chain_table_get(string_array, -1);
        chain_table_init(string);
        string_extend(string, menu_pizza->pizza_type, -1, 12);
        // 写入大小
        chain_table_append(string_array, sizeof(ChainTableManager), true);
        string = chain_table_get(string_array, -1);
        chain_table_init(string);
        memset(buffer, 0, sizeof(buffer));
        itoa(menu_pizza->pizza_size, buffer, 10);
        string_extend(string, buffer, -1, 8);
        // 写入价格
        chain_table_append(string_array, sizeof(ChainTableManager), true);
        string = chain_table_get(string_array, -1);
        chain_table_init(string);
        memset(buffer, 0, sizeof(buffer));
        itoa(menu_pizza->pizza_price, buffer, 10);
        string_extend(string, buffer, -1, 8);
    }
}

int menu_save_to_file_no_update(const ChainTableManager *menu_pizzas, const char *file_name) {
    ChainTableManager file;
    int ret;

    chain_table_init(&file);
    menu_write_data_to_string_array(menu_pizzas, &file);
    ret = write_lines_to_file(&file, file_name);

    chain_table_clear(&file, FREE_AS_MANAGER);

    return ret;
}


int menu_get_pizza_price(const ChainTableManager *menu_pizzas, const Pizza *pizza) {
    MenuPizza *menu;
    menu = menu_get_pizza_from_info(menu_pizzas, pizza);
    if (menu == NULL) {
        return -1;
    } else {
        return menu->pizza_size;
    }
}

/**
 * @brief              删除文件中所有菜单数据后, 向后写入菜单信息
 * @param menu_pizzas
 * @param file_name
 * @return             0  成功
 *                     -1 文件写入失败
 */
int menu_save_to_file_remove_all_menu_data(const ChainTableManager *menu_pizzas, const char *file_name) {
    ChainTableManager file, menu_data;
    ChainTableManager *string;

    int ret;

    chain_table_init(&file);
    read_ascii_file_lines(file_name, &file);

    menu_remove_menus_from_string_array(&file);
    menu_write_data_to_string_array(menu_pizzas, &menu_data);

    for (int index = 0; index < menu_data.length; index++) {
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);

        string_extend_string(string, chain_table_get(&menu_data, index));
    }

    ret = write_lines_to_file(&file, file_name);

    chain_table_clear(&file, FREE_AS_MANAGER);
    chain_table_clear(&menu_data, FREE_AS_MANAGER);

    if (ret != 0) {
        ret = -1;
    }

    return ret;
}


MenuPizza *menu_get_pizza_from_info(const ChainTableManager *menu_pizzas, const Pizza *pizza) {
    MenuPizza *menu;
    for (int index = 0; index < menu_pizzas->length; index++) {
        menu = chain_table_get(menu_pizzas, index);
        if (pizza->size == menu->pizza_size and
            memcmp(pizza->type, menu->pizza_type, PIZZA_TYPE_NAME_MAX_LENGTH + 1) == 0) {
            // 匹配到了
            return menu;
        }
    }
    return NULL;
}


void menu_remove_menus_from_string_array(ChainTableManager *string_array) {
    ChainTableManager *string;
    char buffer[12];
    int i;

    for (int index = 0; index < string_array->length; index++) {
        string = chain_table_get(string_array, index);
        memset(buffer, 0, sizeof(buffer));
        string_read(string, buffer, 12);
        if (memcmp(buffer, "[menu pizza]", 12) == 0) {
            for (i = 0; i < 4; i++) {
                chain_table_remove(string_array, FREE_AS_MANAGER, index);
            }
            index -= 1;
        }
    }
}
