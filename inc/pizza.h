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
    ChainTableManager name;  // Name is a string-like chain table manager.
    char type[PIZZA_TYPE_NAME_MAX_LENGTH + 1];
    int size;
} Pizza;


int pizza_name_get(Pizza *pizza, char *dest, int max_length);

int pizza_init(Pizza *pizza, const ChainTableManager *pizza_name, const char *pizza_type, int pizza_size);

void pizza_free(Pizza * pizza);

int pizza_save(Pizza * pizza, const char * file_name);

int pizza_load_from_file(ChainTableManager * pizzas, const char * file_name);

int pizza_free_pizza_array(ChainTableManager *pizzas);

int pizza_remove_from_file(const Pizza * pizza, const char * file_name);

#endif //ASSESSMENT_PIZZA_PIZZA_H
