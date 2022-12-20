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

#include "chain_table.h"

int write_log(const ChainTableManager * name, const ChainTableManager * menu_pizzas, const ChainTableManager * pizzas, const char * path);


#endif //ASSESSMENT_PIZZA_ORDER_LOGGER_H
