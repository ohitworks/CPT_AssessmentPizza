/**
  **************************** AssessmentPizza: pizza_test.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      Pizza test here.
  **************************** AssessmentPizza: pizza_test.c ****************************
 */

#include "pizza.h"

#include <stdio.h>
#include <string.h>

int main (void) {
    Pizza pizza;
    PIZZA_NAME_TYPE name[16] = {0};

    ChainTableManager pizzas;
    pizza_load_from_file(&pizzas, "pizzas.cfg");

    for (int i=0; i < pizzas.length; i++) {

        memset(name, 0, sizeof(name));
        pizza_name_get(chain_table_get(&pizzas, i), name, 16);

        printf("name: %s\n", name);
    }

    pizza_free(&pizza);

    return 0;
}
