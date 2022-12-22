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
    char userid_1[PASSWORD_LENGTH_MAX +1] = {0};
    char userid_2[PASSWORD_LENGTH_MAX +1] = {0};
    ChainTableManager username;

    for (int i=0; i < 2; i++){
        gen_id(buffer);
        printf("[%2d]: %s\n", i+1, buffer);
    }

    chain_table_init(&username);

    gen_id(userid_1);
    printf("userid 1  %s\n", userid_1);
    string_extend(&username, "user", 4, 6);
    account_register(userid_1, "1234567809", &username, NULL);
    string_extend(&username, "++", 2, 4);
    gen_id(userid_2);
    printf("userid 2  %s\n", userid_2);
    account_register(userid_2, "1234567809", &username, NULL);

    account_change_balance(userid_1, 10);
    printf("Balance: %d\n", account_get_balance(userid_1));

    account_remove(userid_2);

    account_change_balance(userid_1, 20);
    printf("Balance: %d\n", account_get_balance(userid_1));

    chain_table_clear(&username, FREE_AS_MANAGER);

    return 0;
}
