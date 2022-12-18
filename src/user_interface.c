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
Pizza * ui_welcome_menu(ChainTableManager *pizzas) {
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
        printf("input the number of pizza, b for back:\n");

        // 写入
        memset(buffer, 0, sizeof(buffer));
        scanf("%[^\n]", buffer);

        index = (int) strtol(buffer, &ptr, 10) - 1;
        if (ptr - buffer > 2) {
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
 * @return       数量变更
 */
int ui_show_pizza(const ChainTableManager *menu, Pizza const *pizza) {
    char buffer[128] = {0};
    int price;

    price = menu_get_pizza_price(menu, pizza);

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
    printf("*                                       \n");
    printf("*  price: %d\n", price);
    printf("*                                 :)    \n");
    printf("****************************************\n");

    printf("input the number of pizza, b for back:\n");
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
