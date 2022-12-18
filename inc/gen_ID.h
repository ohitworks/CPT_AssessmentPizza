/**
  **************************** AssessmentPizza: gen_ID.h ****************************
  * Created by Miiiaao on 18/12/2022.
  *
  * @file       gen_ID.h
  * @brief      
  * @note       
  **************************** AssessmentPizza: gen_ID.h ****************************
 */

#ifndef ASSESSMENTPIZZA_GEN_ID_H
#define ASSESSMENTPIZZA_GEN_ID_H

#include "time.h"

int count = 0;

char *gen_id();
char int_to_char(int object);

struct Type{
    char ID_mon;
    char ID_day;
    char ID_hour;
    char ID_min;
    char ID_sec;
};
#endif //ASSESSMENTPIZZA_GEN_ID_H