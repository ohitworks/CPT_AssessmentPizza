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

#include "pizza_cfg.h"
#include "chain_table.h"

typedef struct {
    char pizza_type[PIZZA_TYPE_NAME_MAX_LENGTH];
    int pizza_size;
    int pizza_price;
} MenuPizza;

int menu_lead_from_file(ChainTableManager *menu_pizzas, const char *file_name);

int menu_save_to_file_no_update(const ChainTableManager *menu_pizzas, const char *file_name);

#endif //ASSESSMENT_PIZZA_MENU_H
