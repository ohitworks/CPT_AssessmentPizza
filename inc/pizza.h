/**
  **************************** AssessmentPizza: pizza.h ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      Pizza and it's operations.
  **************************** AssessmentPizza: pizza.h ****************************
 */

#ifndef ASSESSMENT_PIZZA_PIZZA_H
#define ASSESSMENT_PIZZA_PIZZA_H

#include "pizza_cfg.h"
#include "chain_table.h"

typedef struct {
    ChainTableManager name;
    char type[PIZZA_TYPE_NAME_MAX_LENGTH + 1];
    int size;
} Pizza;


int pizza_name_get(Pizza *pizza, char *dest, int max_length);

int pizza_init(Pizza *pizza, const char *pizza_name, const char *pizza_type, int pizza_size);

void pizza_free(Pizza * pizza);


#endif //ASSESSMENT_PIZZA_PIZZA_H
