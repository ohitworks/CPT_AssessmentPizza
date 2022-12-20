/**
  **************************** AssessmentPizza: customer_test.c ****************************
  * Created by oh it works on 2022/12/20.
  * @file
  * @author     oh it works
  * @date       2022-12-20
  * @brief      test functions in customer.c
  **************************** AssessmentPizza: customer_test.c ****************************
 */
#include "customer.h"

#include <stdio.h>


int main(void) {
    char buffer[PASSWORD_LENGTH_MAX +1] = {0};

    for (int i=0; i < 16; i++){
        gen_id(buffer);
        printf("[%2d]: %s\n", i+1, buffer);
    }
    return 0;
}
