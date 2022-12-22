/**
  **************************** AssessmentPizza: menu.h ****************************
  * Created by oh-it-works on 2022/12/17.
  * @file
  * @author     oh it works
  * @date       2022-12-17
  * @brief      菜单操作
  **************************** AssessmentPizza: menu.h ****************************
 */

#ifndef ASSESSMENT_PIZZA_MENU_H
#define ASSESSMENT_PIZZA_MENU_H

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "pizza.h"
#include "pizza_cfg.h"
#include "chain_table.h"

typedef struct {
    char pizza_type[PIZZA_TYPE_NAME_MAX_LENGTH + 1];
    int pizza_size;
    int pizza_price;
    int number;
} MenuPizza;

int menu_load_from_file(ChainTableManager *menu_pizzas, const char *file_name);

int menu_save_to_file_no_update(const ChainTableManager *menu_pizzas, const char *file_name);

int menu_save_to_file_remove_all_menu_data(const ChainTableManager *menu_pizzas, const char *file_name);

int menu_get_pizza_price(const ChainTableManager *menu_pizzas, const Pizza *pizza);

MenuPizza *menu_get_pizza_from_info(const ChainTableManager *menu_pizzas, const Pizza *pizza);

void menu_write_data_to_string_array(const ChainTableManager *menu_pizzas, ChainTableManager *string_array);

void menu_remove_menus_from_string_array(ChainTableManager *string_array);

int menu_get_charge(ChainTableManager *menus);

#endif //ASSESSMENT_PIZZA_MENU_H
