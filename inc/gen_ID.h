/**
  **************************** AssessmentPizza: gen_ID.h ****************************
  * Created by Miiiaao on 15/12/2022.
  *
  * @file       gen_ID.h
  * @brief      
  * @note       
  **************************** AssessmentPizza: gen_ID.h ****************************
 */

#ifndef ASSESSMENTPIZZA_GEN_ID_H
#define ASSESSMENTPIZZA_GEN_ID_H

#include "time.h"

#define PASSWORD_LENGTH_MAX 15 //


void gen_id_init();

char gen_id(char ID[PASSWORD_LENGTH_MAX]);

void gen_random_string(char * dest);



struct Type{
    char ID_mon;
    char ID_day;
    char ID_hour;
    char ID_min;
    char ID_sec;
};
#endif //ASSESSMENTPIZZA_GEN_ID_H
