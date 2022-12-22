/**
  **************************** AssessmentPizza: order_logger.h ****************************
  * Created by oh it works on 2022/12/20.
  * @file
  * @author     oh it works
  * @date       2022-12-20
  * @brief      logger for order
  **************************** AssessmentPizza: order_logger.h ****************************
 */

#ifndef ASSESSMENT_PIZZA_ORDER_LOGGER_H
#define ASSESSMENT_PIZZA_ORDER_LOGGER_H

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "chain_table.h"

int write_log(const ChainTableManager *username, const ChainTableManager *menu_pizzas, const ChainTableManager *pizzas,
              const char *path);

int show_log(const ChainTableManager *username, const char *log_path);


#endif //ASSESSMENT_PIZZA_ORDER_LOGGER_H
