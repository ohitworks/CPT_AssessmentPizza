#include "menu.h"
#include "pizza.h"
#include "file_io.h"
#include "customer.h"
#include "pizza_cfg.h"
#include "the_manager.h"
#include "main_config.h"
#include "account_cfg.h"
#include "order_logger.h"
#include "user_interface.h"
#include "user_interface_tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <string.h>


/**
 *
 * @param string
 * @return        string length
 */
int read_from_stdin(ChainTableManager *string) {
    char c;
    char buffer[22] = {0};
    int buffer_write;
    int length;

    length = 0;
    buffer_write = 0;
    chain_table_init(string);
    fflush(stdin);
    while (1) {
        c = (char) getchar();
        if (c != '\n') {
            length += 1;
            buffer[buffer_write++] = c;
        }
        if (buffer_write == 22) {
            buffer_write = 0;
            string_extend(string, buffer, 22, 22);
            memset(buffer, 0, sizeof(buffer));
        }
        if (c == '\n') {
            string_extend(string, buffer, 22, 22);
            break;
        }
    }

    return length;
}


/**
 * @brief   顾客下单用的菜单
 * @return  NULL 返回上一步
 */
Pizza *ui_order_one_menu(ChainTableManager *pizzas) {
    int index;
    char *ptr;
    char buffer[PIZZA_TYPE_NAME_MAX_LENGTH * 2];
    Pizza *pizza;

    printf("****************************************\n");
    printf("*                                       \n");
    printf("*                                       \n");

    for (index = 0; index < pizzas->length; index++) {
        pizza = chain_table_get(pizzas, index);
        memset(buffer, 0, sizeof(buffer));
        string_read(&pizza->name, buffer, PIZZA_TYPE_NAME_MAX_LENGTH * 2 - 1);
        printf("* %2d) %s\n*\n", index + 1, buffer);
    }
    printf("*                                 :)    \n");
    printf("****************************************\n");
    while (1) {
        printf("input the number of pizza, b for order: ");

        // 获取输入
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        index = (int) strtol(buffer, &ptr, 10) - 1;
        if (ptr == buffer or ptr - buffer > 2) {
            return NULL;
        }
        pizza = chain_table_get(pizzas, index);

        if (pizza == NULL) {
            printf("Error... Please input again...\n");
        }

        return pizza;
    }
}


/**
 *
 * @return
 */
int ui_customer_register(char *userid_write_space) {
    ChainTableManager username;
    char buffer[128] = {0};
    char tel[128] = {0};
    int length;

    printf("*****************************************\n");
    printf("*          Customer Register:           *\n");
    printf("*****************************************\n");
    printf("*                                       *\n");
    printf("*                                       *\n");

    while (1) {
        printf("input your username:");
        fflush(stdin);
        length = read_from_stdin(&username);
        if (length >= USERNAME_LENGTH_MIN) {
            break;
        }
        printf("Name too short ... Please input again...\n");
        chain_table_clear(&username, RETURN_IF_DYNAMIC);
    }
    while (1) {
        printf("\nInput password:");
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        length = (int) strlen(buffer);

        if (length <= PASSWORD_LENGTH_MAX and length >= PASSWORD_LENGTH_MIN) {
            break;
        }
        printf("Password too long or too short ... Please input again...\n");
    }

    printf("Input phone number:");
    memset(tel, 0, sizeof(tel));
    fflush(stdin);
    scanf("%[^\n]", tel);

    do {
        gen_id(userid_write_space);
    } while (account_register(userid_write_space, buffer, &username, tel) == -1);

    memset(buffer, 0, sizeof(buffer));
    length = string_read(&username, buffer, 128 - 1);
    printf("Register success! Hello %s", buffer);
    while (length == -1) {
        memset(buffer, 0, sizeof(buffer));
        length = string_read(&username, buffer, 128 - 1);
        printf("%s", buffer);
    }
    printf("\nYour ID is [%s] please remember this.\n", userid_write_space);

    return 0;
}


/**
 *
 * @return  0 退出程序
 *          1 顾客注册
 *          2 顾客登录
 *          3 管理员登录
 */
int ui_choose_role(void) {
    char buffer[128] = {0};

    printf("*****************************************\n");
    printf("*          Choose your role.            *\n");
    printf("*****************************************\n");
    printf("*                                       *\n");
    printf("*                                       *\n");
    printf("* 1)  Customer Register                 *\n");
    printf("*                                       *\n");
    printf("* 2)  Customer Login                    *\n");
    printf("*                                       *\n");
    printf("* 3)  Manager Login                     *\n");
    printf("*                                       *\n");
    printf("*                                 :)    *\n");
    printf("*****************************************\n");

    while (1) {
        printf("input the number to choose, b for exit:");
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        if (buffer[1] == '\0') {
            if (buffer[0] == '1' or buffer[0] == '2' or buffer[0] == '3') {
                break;
            } else {
                return 0;
            }
        }
        printf("Error ... Please input again...\n");
    }

    return (int) buffer[0] - 48;
}


int ui_manager_main(void) {
    char buffer[128] = {0};

    printf("****************************************\n");
    printf("*                Manager               *\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*                                      *\n");
    printf("* 1) Show orders log                   *\n");
    printf("*                                      *\n");
    printf("* 2) Add new pizza                     *\n");
    printf("*                                      *\n");
    printf("* 3) Remove exist pizza                *\n");
    printf("*                                      *\n");
    printf("* 4) Add new menu                      *\n");
    printf("*                                      *\n");
    printf("* 5) Remove exist menu                 *\n");
    printf("*                                      *\n");
    printf("* 6) Show all customers                *\n");
    printf("*                                      *\n");
    printf("* 7) Edit customer                     *\n");
    printf("*                                      *\n");
    printf("* 8) Add customer                      *\n");
    printf("*                                      *\n");
    printf("* 9) Delete customer                   *\n");
    printf("*                                      *\n");
    printf("*                                 :)   *\n");
    printf("****************************************\n");

    while (1) {
        printf("Input the number to choose, b for exit:");
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        if (buffer[1] == '\0') {
            if ('1' <= buffer[0] and buffer[0] <= '9') {
                break;
            } else {
                return 0;
            }
        }
        printf("Error ... Please input again...\n");
    }

    return (int) (buffer[0] - '0');
}


int ui_customer_functions(int key, const char *userid) {
    ChainTableManager username;

    screen_clear();
    if (key == 1) {
        // order
        ui_order_menu(userid);
    } else if (key == 2) {
        // See history.
        chain_table_init(&username);
        account_get_username(userid, &username);
        show_log(&username, LOG_SAVE_PATH);
    } else if (key == 3) {
        // Recharge.
        ui_recharge(userid);
    }

    return 0;
}


int ui_order_menu(const char *userid) {
    ChainTableManager pizzas, menu, username;
    Pizza *pizza;

    pizza_load_from_file(&pizzas, PIZZA_SAVE_PATH);
    menu_load_from_file(&menu, MENU_SAVE_PATH);

    while (1) {
        pizza = ui_order_one_menu(&pizzas);
        if (pizza == NULL) {
            break;
        }
        ui_order_pizza(&menu, pizza);
    }

    chain_table_init(&username);
    account_get_username(userid, &username);
    write_log(&username, &menu, &pizzas, LOG_SAVE_PATH);

    pizza_free_pizza_array(&pizzas);
    chain_table_clear(&menu, FREE_AS_MANAGER);
    chain_table_clear(&username, FREE_AS_MANAGER);
    return 0;
}


int ui_customer_main(const char *userid) {
    char buffer[128] = {0};

//    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);

    ui_show_customer_info(userid);

    printf("****************************************\n");
    printf("*                Hello                 *\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("* 1) Order                             *\n");
    printf("*                                      *\n");
    printf("* 2) See history                       *\n");
    printf("*                                      *\n");
    printf("* 3) Recharge                          *\n");
    printf("*                                      *\n");
    printf("*                                 :)   *\n");
    printf("****************************************\n");

    while (1) {
        printf("Input the number to choose, b for exit:");
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        if (buffer[1] == '\0') {
            if ('1' <= buffer[0] and buffer[0] <= '3') {
                break;
            } else {
                return 0;
            }
        }
        printf("Error ... Please input again...\n");
    }

    return (int) (buffer[0] - '0');
}


int ui_manage_functions(int key) {
    ChainTableManager chain_table;
    ChainTableManager *string;
    char userid[32];
    int length;

    screen_clear();
    if (key == 1) {
        // 打印历史记录
        read_ascii_file_lines(LOG_SAVE_PATH, &chain_table);

        for (int i = 0; i < chain_table.length - 1; i++) {
            string = chain_table_get(&chain_table, i);
            printf("line[%2d]: ", i + 1);
            string_print(string);
            printf("\n");
        }
        chain_table_clear(&chain_table, FREE_AS_MANAGER);
    } else if (key == 2) {
        // 添加新 pizza
        ui_add_pizza();
    } else if (key == 3) {
        // 删除 pizza
        ui_remove_pizza();
    } else if (key == 4) {
        // 添加 菜单
        pizza_load_from_file(&chain_table, PIZZA_SAVE_PATH);
        ui_add_menu(&chain_table);
        pizza_free_pizza_array(&chain_table);
    } else if (key == 5) {
        // 删除 菜单
        ui_remove_menu();
    } else if (key == 6) {
        ui_show_all_customers();
    } else if (key == 7) {
        // Edit customers
        while (1) {
            printf("* User ID, q for exit:  ");
            memset(userid, 0, PASSWORD_LENGTH_MAX * 2);
            fflush(stdin);
            scanf("%[^\n]", userid);
            length = (int) strlen(userid);
            if (length == PASSWORD_LENGTH_MAX) {
                break;
            } else if (length == 1 and userid[0] == 'q') {
                return -1;
            }
            printf("Unexpect length, need %d, get %d.\n", PASSWORD_LENGTH_MAX, length);
            printf("Input user ID again...\n");
        }
        ui_edit_customers(userid);
    } else if (key == 8) {
        // add customer
        ui_customer_register(userid);
    } else if (key == 9) {
        // add customer
        while (1) {
            printf("* User ID, q for exit:  ");
            memset(userid, 0, PASSWORD_LENGTH_MAX * 2);
            fflush(stdin);
            scanf("%[^\n]", userid);
            length = (int) strlen(userid);
            if (length == PASSWORD_LENGTH_MAX) {
                break;
            } else if (length == 1 and userid[0] == 'q') {
                return -1;
            }
            printf("Unexpect length, need %d, get %d.\n", PASSWORD_LENGTH_MAX, length);
            printf("Input user ID again...\n");
        }
        ui_customer_register(userid);
    }
    return 0;
}


int ui_rename_customer(const char *userid) {
    ChainTableManager username;

    printf("Input new name:");
    read_from_stdin(&username);

    account_rename(userid, &username);

    chain_table_clear(&username, FREE_AS_MANAGER);
    return 0;
}

int ui_show_all_customers(void) {
    ChainTableManager file, superuser_id;
    ChainTableManager *string;
    char buffer[32];

    chain_table_init(&superuser_id);
    string_extend(&superuser_id, "Superuser", -1, 16);

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);
    for (int index = 0; index < file.length; index += 6) {
        string = chain_table_get(&file, index);
        if (string_equal(string, &superuser_id)) {
            continue;
        }

        memset(buffer, 0, sizeof(buffer));
        string_read(string, buffer, 32);
        ui_show_customer_info(buffer);
    }

    chain_table_clear(&file, FREE_AS_MANAGER);
    chain_table_clear(&superuser_id, FREE_AS_MANAGER);

    return 0;
}

int ui_edit_customers(const char *userid) {
    ChainTableManager file;
    ChainTableManager *string;
    int index, choose;

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);
    index = account_in(&file, userid);

    string = chain_table_get(&file, index + 1);

    printf("*****************************************\n");
    printf("*  >>>     Hello~");
    string_print(string);
    printf("\n");
    ui_show_customer_info(userid);
    printf("*****************************************\n");
    printf("*                                       *\n");
    printf("*                                       *\n");
    printf("* 1)  Rename                            *\n");
    printf("*                                       *\n");
    printf("* 2)  Reset password                    *\n");
    printf("*                                       *\n");
    printf("* 3)  Recharge                          *\n");
    printf("*                                       *\n");
    printf("*                                 :)    *\n");
    printf("*****************************************\n");

    printf("input the number to choose, b for exit:");
    choose = ui_multiple_choice("123b", 3, 1);

    if (choose == 0) {
        ui_rename_customer(userid);
    } else if (choose == 1) {
        // Reset password.
        ui_reset_password(userid);
    } else if (choose == 2) {
        // Recharge
        ui_recharge(userid);
    }

    chain_table_clear(&file, FREE_AS_MANAGER);
    return 0;
}


int ui_show_customer_info(const char *userid) {
    ChainTableManager file;
    ChainTableManager *string;
    int index;

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);

    index = account_in(&file, userid);
    if (index > 0) {
        string = chain_table_get(&file, index - 1);
        printf("User ID :");
        string_print(string);
        printf("\n");

        string = chain_table_get(&file, index);
        printf("User hashed password :");
        string_print(string);
        printf("\n");

        string = chain_table_get(&file, index + 1);
        printf("User name :");
        string_print(string);
        printf("\n");

        string = chain_table_get(&file, index + 2);
        printf("User balance :");
        string_print(string);
        printf("\n");

        string = chain_table_get(&file, index + 3);
        printf("User phone number :");
        string_print(string);
        printf("\n");
    }

    chain_table_clear(&file, FREE_AS_MANAGER);

    return 0;
}


int ui_manager_login(void) {
    int length;
    char password[PASSWORD_LENGTH_MAX * 2];

    printf("*****************************************\n");
    printf("*             Manager in                *\n");
    printf("*****************************************\n");
    printf("*                                       *\n");
    printf("*                                       *\n");

    while (1) {
        while (1) {
            printf("Input password: ");
            memset(password, 0, PASSWORD_LENGTH_MAX * 2);
            fflush(stdin);
            scanf("%[^\n]", password);
            length = (int) strlen(password);
            if (length <= PASSWORD_LENGTH_MAX and length >= PASSWORD_LENGTH_MIN) {
                break;
            }
            printf("Unexpect length, get %d.\n", length);
            printf("Input password again...\n");
        }

        if (manager_login(password) == 0) {
            break;
        }
        printf("Password not matched.\n");
    }

    return 0;
}


/**
 * @brief
 * @param pizza
 * @return       数量变更, 将修改 menu 上对应的节点
 * @warning      程序不检查输入
 */
int ui_order_pizza(ChainTableManager *menu, Pizza const *pizza) {
    char *ptr;
    char buffer[128] = {0};
    int number_update;
    MenuPizza *menu_pizza;

    menu_pizza = menu_get_pizza_from_info(menu, pizza);

    string_read(&pizza->name, buffer, 128);

    printf("****************************************\n");
    printf("*                                       \n");
    printf("*                                       \n");
    printf("*  name:  %s\n", buffer);
    printf("*                                       \n");
    printf("*  type:  %s\n", pizza->type);
    printf("*                                       \n");
    printf("*  size:  %d\n", pizza->size);
    printf("*                                       \n");
    printf("*  price: %d\n", menu_pizza->pizza_price);
    printf("*                   ----                \n");
    printf("*  Your order number: %2d               \n", menu_pizza->number);
    printf("*                   ----                \n");
    printf("*                                  :)   \n");
    printf("****************************************\n");

    while (1) {
        printf("input the number of pizza, b for back:");
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        number_update = strtol(buffer, &ptr, 10);
        if (ptr != buffer) {
            if (number_update + menu_pizza->number < 0) {
                // NOTE: Pizza check here!
                printf("Wrong value...\n");
                continue;
            }
            menu_pizza->number += number_update;
            return number_update;
        } else if (*ptr == 'b') {
            return 0;
        }
        printf("Error ... Please input again...\n");
    }
}

int ui_reset_password(const char *userid) {
    char buffer[PASSWORD_LENGTH_MAX * 2];
    int length;

    while (1) {
        printf("\nInput password:");
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        length = (int) strlen(buffer);

        if (length <= PASSWORD_LENGTH_MAX and length >= PASSWORD_LENGTH_MIN) {
            break;
        }
        printf("Password too long or too short ... Please input again...\n");
    }

    account_change_password(userid, buffer);

    return 0;
}


int ui_recharge(const char *userid) {
    char buffer[16];
    char *c;
    int change, new;

    printf("Enter the amount change:");
    // 获取输入
    memset(buffer, 0, sizeof(buffer));
    fflush(stdin);
    scanf("%[^\n]", buffer);

    change = (int) strtol(buffer, &c, 10) - 1;

    new = account_get_balance(userid) + change;
    account_change_balance(userid, new);

    return 0;
}


/**
 *
 * @param userid  待写入的字符串数组, 长度应当为 (PASSWORD_LENGTH_MAX * 2), 执行完成后写入登录的用户ID
 * @return         0  登录成功
 *                 -1 用户取消登录
 */
int ui_login_page(char *userid) {
    int length, login;
    char password[PASSWORD_LENGTH_MAX * 2];

    printf("*****************************************\n");
    printf("*                Log in                 *\n");
    printf("*****************************************\n");
    printf("*                                       *\n");
    printf("*                                       *\n");

    while (1) {

        while (1) {
            printf("* User ID, q for exit:  ");
            memset(userid, 0, PASSWORD_LENGTH_MAX * 2);
            fflush(stdin);
            scanf("%[^\n]", userid);
            length = (int) strlen(userid);
            if (length == PASSWORD_LENGTH_MAX) {
                break;
            } else if (length == 1 and userid[0] == 'q') {
                return -1;
            }
            printf("Unexpect length, need %d, get %d.\n", PASSWORD_LENGTH_MAX, length);
            printf("Input user ID again...\n");
        }

        while (1) {
            printf("Input password: ");
            memset(password, 0, PASSWORD_LENGTH_MAX * 2);
            fflush(stdin);
            scanf("%[^\n]", password);
            length = (int) strlen(password);
            if (length <= PASSWORD_LENGTH_MAX and length >= PASSWORD_LENGTH_MIN) {
                break;
            }
            printf("Unexpect length, get %d.\n", length);
            printf("Input password again...\n");
        }

        login = account_login(userid, password);
        if (login == 0) {
            printf("Login success! Hello~\n");
            return 0;
        }

        printf("Wrong ID or password.\n");
    }
}


int ui_add_menu(ChainTableManager *pizzas) {
    Pizza *pizza;
    MenuPizza menu_pizza;
    ChainTableManager menu_pizzas, names_for_edit;
    ChainTableManager *string;
    int index;
    char buffer[128];
    char *c;

    chain_table_init(&names_for_edit);
    menu_load_from_file(&menu_pizzas, MENU_SAVE_PATH);

    // 获取待添加的名称
    for (int i = 0; i < pizzas->length; i++) {
        pizza = chain_table_get(pizzas, i);
        if (menu_get_pizza_from_info(&menu_pizzas, pizza) == NULL) {
            // 找到一个没有写入菜单的 pizza
            chain_table_append(&names_for_edit, sizeof(ChainTableManager), true);
            string = chain_table_get(&names_for_edit, -1);
            string_extend_string(string, &pizza->name);
        }
    }

    if (names_for_edit.length == 0) {
        // Nothing to do.
        return 0;
    }

    // 打印所有可添加的名称
    printf("Choose the pizza's name to add:\n");
    for (int i = 0; i < names_for_edit.length; i++) {
        string = chain_table_get(&names_for_edit, i);
        printf("* %2d  )", i + 1);
        string_print(string);
        printf("\n");
    }

    // 获取输入
    printf("Input name index:");
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        index = (int) strtol(buffer, &c, 10);
        if (*c == '\0' and index > 0 and index <= names_for_edit.length) {
            break;
        }
        printf("Input again please:");
    }

    string = chain_table_get(&names_for_edit, index - 1);
    for (index = 0; index < pizzas->length; index++) {
        pizza = chain_table_get(pizzas, index);
        if (string_equal(&pizza->name, string)) {
            break;
        }
    }

    // 获取定价
    printf("Input price:");
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        index = (int) strtol(buffer, &c, 10);
        if (*c == '\0' and index > 0) {
            break;
        }
        printf("Input again please:");
    }

    memset(&menu_pizza, 0, sizeof(menu_pizza));
    menu_pizza.pizza_price = index;
    menu_pizza.pizza_size = pizza->size;
    memcpy(menu_pizza.pizza_type, pizza->type, PIZZA_TYPE_NAME_MAX_LENGTH);

    chain_table_append(&menu_pizzas, sizeof(MenuPizza), false);
    memcpy((MenuPizza *) chain_table_get(&menu_pizzas, -1), &menu_pizza, sizeof(MenuPizza));

    menu_save_to_file_remove_all_menu_data(&menu_pizzas, MENU_SAVE_PATH);

    chain_table_clear(&menu_pizzas, FREE_AS_MANAGER);
    chain_table_clear(&names_for_edit, FREE_AS_MANAGER);

    return 0;
}

int ui_remove_menu(void) {
    ChainTableManager menu_pizzas;
    MenuPizza *menu_pizza;
    int index;
    char buffer[PIZZA_TYPE_NAME_MAX_LENGTH + 1];
    char *c;

    menu_load_from_file(&menu_pizzas, MENU_SAVE_PATH);
    for (index = 0; index < menu_pizzas.length; index++) {
        menu_pizza = chain_table_get(&menu_pizzas, index);
        memset(buffer, 0, sizeof(buffer));
        memcpy(buffer, menu_pizza->pizza_type, PIZZA_TYPE_NAME_MAX_LENGTH);
        printf("* * * *  menu %d  * * * *\n", index + 1);
        printf("Type %s\n", buffer);
        printf("Size %d\n", menu_pizza->pizza_size);
        printf("Price %d\n", menu_pizza->pizza_price);
    }

    // 获取输入
    printf("Input name index:");
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        index = (int) strtol(buffer, &c, 10);
        if (*c == '\0' and index > 0 and index <= menu_pizzas.length) {
            break;
        }
        printf("Input again please:");
    }

    chain_table_remove(&menu_pizzas, FREE_AS_MANAGER, index - 1);
    menu_save_to_file_remove_all_menu_data(&menu_pizzas, MENU_SAVE_PATH);

    chain_table_clear(&menu_pizzas, FREE_AS_MANAGER);

    return 0;
}

int ui_add_pizza(void) {
    ChainTableManager pizza_name;
    Pizza pizza;
    int length, pizza_size;
    char buffer[128];
    char pizza_type[PIZZA_TYPE_NAME_MAX_LENGTH + 1];
    char *c;

    printf("Input pizza name:");
    fflush(stdin);
    read_from_stdin(&pizza_name);

    printf("Input pizza type:");
    while (1) {
        fflush(stdin);
        memset(pizza_type, 0, sizeof(pizza_type));
        scanf("%[^\n]", pizza_type);
        length = (int) strlen(pizza_type);
        if (length > 0 and length <= PIZZA_TYPE_NAME_MAX_LENGTH) {
            break;
        }
        printf("Input again please:");
    }

    printf("Input pizza size:");
    while (1) {
        fflush(stdin);
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        pizza_size = (int) strtol(buffer, &c, 10);
        if (*c == '\0') {
            break;
        }
        printf("Input again please:");
    }

    pizza_init(&pizza, &pizza_name, pizza_type, pizza_size);
    pizza_save(&pizza, PIZZA_SAVE_PATH);
    chain_table_clear(&pizza_name, FREE_AS_MANAGER);
    return 0;
}

int ui_remove_pizza(void) {
    ChainTableManager pizzas;
    Pizza *pizza;
    int index;
    char buffer[PIZZA_TYPE_NAME_MAX_LENGTH + 1];
    char *c;

    pizza_load_from_file(&pizzas, PIZZA_SAVE_PATH);

    for (int i = 0; i < pizzas.length; i++) {
        pizza = chain_table_get(&pizzas, i);
        printf("- %2d )", i + 1);
        string_print(&pizza->name);
        printf("\n");
    }

    // 获取输入
    printf("Input name index:");
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        fflush(stdin);
        scanf("%[^\n]", buffer);

        index = (int) strtol(buffer, &c, 10);
        if (*c == '\0' and index > 0 and index <= pizzas.length) {
            break;
        }
        printf("Input again please:");
    }

    pizza = chain_table_get(&pizzas, index - 1);
    pizza_remove_from_file(pizza, PIZZA_SAVE_PATH);

    pizza_free_pizza_array(&pizzas);
    return 0;
}

/**
 * @brief   顾客下单用的菜单
 * @return
 */
void menu_order_welcome() {
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*                                      *\n");
    printf("*  Welcome to the pizza order system   *\n");
    printf("*                                      *\n");
    printf("*                                 :)   *\n");
    printf("****************************************\n");
}

void menu_order_type() {
    printf("****************************************\n");
    printf("*             Pizza  Type              *\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*                                      *\n");
    printf("* 1) Hand Tossed                       *\n");
    printf("*                                      *\n");
    printf("* 2) Thin pancake base                 *\n");
    printf("*                                      *\n");
    printf("* 3) Pastry base                       *\n");
    printf("*                                      *\n");
    printf("* 4) Extra-thick                       *\n");
    printf("*                                      *\n");
    printf("*                                 :)   *\n");
    printf("****************************************\n");
}

void menu_order_size() {
    printf("****************************************\n");
    printf("*              Pizza  Size             *\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*                                      *\n");
    printf("* 1) 10 inches                         *\n");
    printf("*                                      *\n");
    printf("* 2) 12 inches                         *\n");
    printf("*                                      *\n");
    printf("* 3) 14 inches                         *\n");
    printf("*                                      *\n");
    printf("* 4) 16 inches                         *\n");
    printf("*                                      *\n");
    printf("*                                 :)   *\n");
    printf("****************************************\n");
}

void menu_order_topping() {
    printf("****************************************\n");
    printf("*            Pizza  Topping            *\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*                                      *\n");
    printf("* 1) Supreme                           *\n");
    printf("*                                      *\n");
    printf("* 2) Hawaiian                          *\n");
    printf("*                                      *\n");
    printf("* 3) Margherita                        *\n");
    printf("*                                      *\n");
    printf("* 4) BBQ Chicken                       *\n");
    printf("*                                      *\n");
    printf("*                                 :)   *\n");
    printf("****************************************\n");
}
