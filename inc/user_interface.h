//
// Created by wlf on 2022/12/9.
//

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "menu.h"


Pizza * ui_welcome_menu(ChainTableManager *pizzas);

int ui_show_pizza(ChainTableManager *menu, Pizza const *pizza);

int ui_login_page(char * user_id);

int ui_choose_role(void);

int read_from_stdin(ChainTableManager *string);

int ui_customer_register(char *userid_write_space);

int ui_add_pizza(void);

int ui_add_menu(ChainTableManager * pizzas);

int ui_remove_menu(void);

int ui_remove_pizza(void);

#endif //USER_INTERFACE_H
