//
// Created by wlf on 2022/12/9.
//

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "menu.h"


Pizza * ui_welcome_menu(ChainTableManager *pizzas);

int ui_show_pizza(ChainTableManager *menu, Pizza const *pizza);

int ui_login_page(char * userid);

int ui_choose_role(void);

int read_from_stdin(ChainTableManager *string);

int ui_customer_register(char *userid_write_space);

int ui_add_pizza(void);

int ui_add_menu(ChainTableManager * pizzas);

int ui_remove_menu(void);

int ui_remove_pizza(void);

int ui_manager_login(void);

int ui_manager_main(void);

int ui_manage_functions(int key);

int ui_rename_customer(const char * userid);

int ui_show_customer_info(const char * userid);

int ui_show_all_customers(void);

int ui_edit_customers(const char * userid);

int ui_recharge(const char *userid);

int ui_reset_password(const char *userid);

#endif //USER_INTERFACE_H
