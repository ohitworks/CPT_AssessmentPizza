#include "menu.h"
#include "pizza.h"
#include "pizza_cfg.h"
#include "user_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <string.h>


/**
 * @brief   顾客下单用的菜单
 * @return  NULL 返回上一步
 */
Pizza *ui_welcome_menu(ChainTableManager *pizzas) {
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
        printf("input the number of pizza, b for back: ");

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
 * @brief
 * @param pizza
 * @return       数量变更, 将修改 menu 上对应的节点
 * @warning      程序不检查输入
 */
int ui_show_pizza(ChainTableManager *menu, Pizza const *pizza) {
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
    printf("*  Your order number: %2d                \n", menu_pizza->number);
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
