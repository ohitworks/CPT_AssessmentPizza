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

int menu_get_pizza_price(const ChainTableManager *menu_pizzas, const Pizza *pizza);

MenuPizza * menu_get_pizza_from_info(const ChainTableManager *menu_pizzas, const Pizza * pizza);

#endif //ASSESSMENT_PIZZA_MENU_H
