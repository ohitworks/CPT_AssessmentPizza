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

int main (void) {
    Pizza pizza;
    PIZZA_NAME_TYPE name[16] = {0};

    pizza_init(&pizza, "name 1234", "type 0", 10);

    pizza_name_get(&pizza, name, 16);

    printf("name: %s\n", name);

    pizza_save(&pizza, "pizzas.cfg");

    pizza_free(&pizza);

    return 0;
}
