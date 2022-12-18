/**
  **************************** AssessmentPizza: gen_ID.c ****************************
  * Created by Miiiaao on 18/12/2022.
  *
  * @file       gen_ID.c
  * @brief      
  * @note       
  **************************** AssessmentPizza: gen_ID.c ****************************
 */

#include "gen_ID.h"

#include <iso646.h>

char *gen_ID(){
    count++;
    char ID = ' ';
    time_t tmpcal_ptr;
    struct  tm *tmp_ptr = NULL;
    struct  Type *ID_type = NULL;

    time(&tmpcal_ptr);

    tmp_ptr = localtime(&tmpcal_ptr);

    ID_type->ID_mon = int_to_char(tmp_ptr->tm_mon);
    ID_type->ID_day = int_to_char(tmp_ptr->tm_mday);
    ID_type->ID_hour = int_to_char(tmp_ptr->tm_hour);
    ID_type->ID_min = int_to_char(tmp_ptr->tm_min);
    ID_type->ID_sec = int_to_char(tmp_ptr->tm_sec);

    ID = 'P' + (char)(1900 + tmp_ptr->tm_year) + ID_type->ID_mon + ID_type->ID_day + ID_type->ID_hour + ID_type->ID_min
            + ID_type->ID_sec;
    return ID;
}

char int_to_char(int object){
    char target = ' ';
    if (10 <= object and object <= 99){
        target = (char)object;
    }else{
        target = '0' + (char)object;
    }
    return target;
}