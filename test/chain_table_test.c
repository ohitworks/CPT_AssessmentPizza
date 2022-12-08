/**
  **************************** AssessmentPizza: chain_table_test.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      Test the chain table.
  **************************** AssessmentPizza: chain_table_test.c ****************************
 */

#include <stdio.h>

#include "chain_table.h"


int main(void) {
    ChainTableManager ctm;
    int c = 0;
    char *ptr;

    chain_table_init(&ctm);

    chain_table_append(&ctm, sizeof(char) * 14);
    chain_table_append(&ctm, sizeof(char) * 14);

    ptr = (char *) chain_table_get(&ctm, 0);
    for (int i = 0; i < 13; i++, c++) {
        *ptr = (char) ('a' + c);
    }
    ptr = (char *) chain_table_get(&ctm, 1);
    for (int i = 0; i < 13; i++, c++) {
        *ptr = (char) ('a' + c);
    }

    printf("%s\n", (char *) chain_table_get(&ctm, 0));
    printf("%s\n", (char *) chain_table_get(&ctm, 1));

    chain_table_clear(&ctm);

    return 0;
}
