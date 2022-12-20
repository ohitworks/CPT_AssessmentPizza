/**
  **************************** AssessmentPizza: gen_ID.c ****************************
  * Created by Miiiaao on 15/12/2022.
  *
  * @file       gen_ID.c
  * @brief      
  * @note       
  **************************** AssessmentPizza: gen_ID.c ****************************
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "gen_ID.h"
#include "chain_table.h"

void gen_id_init (){
    ChainTableManager string_id;

    chain_table_init(&string_id);

    chain_table_append(&string_id, sizeof(char) * 16, 1);

    return;
}

char gen_id(char ID[PASSWORD_LENGTH_MAX]){
//    char ID[PASSWORD_LENGTH_MAX] = {0};
    ChainTableManager *sub_string_id;
    char *str;

    chain_table_init(&sub_string_id);

    chain_table_append(&sub_string_id, sizeof(char) *16, 0);

    gen_random_string(str);

    int i;
    for (i = 0; i <= PASSWORD_LENGTH_MAX; i++){
        ID[i] = str[i];
    }


    printf("%s\n", ID);

    return ID[PASSWORD_LENGTH_MAX];
}

void gen_random_string(char * dest){
    const unsigned char allchar[63] = "0123456789abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int i, randNo;
    unsigned char str[PASSWORD_LENGTH_MAX + 1] = { };

    srand((unsigned int)time(NULL));

    for (i = 0; i < PASSWORD_LENGTH_MAX; i++){
        randNo = rand() % 62;
        *dest = allchar[randNo];
        dest++;
    }

    *dest = '\0';
}