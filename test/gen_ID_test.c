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
    char ID[PASSWORD_LENGTH_MAX] = { };

    //init
    gen_id_init();
    //generate an ID
    gen_id(ID);
    printf("%s\n",ID); //测试 获得一个随机的账户名

    //验证是否唯一



    return 0;
}