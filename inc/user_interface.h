//
// Created by wlf on 2022/12/9.
//

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "menu.h"


Pizza * ui_welcome_menu(ChainTableManager *pizzas);

int ui_show_pizza(const ChainTableManager *menu, Pizza const *pizza);

#endif //USER_INTERFACE_H
