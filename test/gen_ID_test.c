/**
  **************************** AssessmentPizza: gen_ID.h ****************************
  * Created by Miiiaao on 15/12/2022.
  *
  * @file       gen_ID.h
  * @brief
  * @note
  **************************** AssessmentPizza: gen_ID.h ****************************
 */

#include <stdio.h>

#include "gen_ID.h"

int main(void){
    char ID[ACCOUNT_LENGTH_MAX + 1] = { };

    //generate an ID
    gen_id(ID);
    printf("%s\n", ID); //Win！！！ 获得一个唯一且定长的账户名





    return 0;
}