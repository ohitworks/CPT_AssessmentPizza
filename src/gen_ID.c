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

char gen_ID(){
    count++;
    char *str_id = "Account generation error\n";
    time_t tmpcal_ptr;
    struct  tm *tmp_ptr = NULL;
    struct  Type *ID_type = NULL;

    time(&tmpcal_ptr);

    tmp_ptr = localtime(&tmpcal_ptr);

    ID_type->ID_year = int_to_string(tmp_ptr->tm_year);
    ID_type->ID_mon = int_to_string(tmp_ptr->tm_mon);
    ID_type->ID_day = int_to_string(tmp_ptr->tm_mday);
    ID_type->ID_hour = int_to_string(tmp_ptr->tm_hour);
    ID_type->ID_min = int_to_string(tmp_ptr->tm_min);
    ID_type->ID_sec = int_to_string(tmp_ptr->tm_sec);

    strcpy(str_id, ID_type->ID_year);
    strcpy(str_id, ID_type->ID_mon);
    strcpy(str_id, ID_type->ID_day);
    strcpy(str_id, ID_type->ID_hour);
    strcpy(str_id, ID_type->ID_min);
    strcpy(str_id, ID_type->ID_sec);

    return *str_id;
}

char *int_to_string(int object){
    char *target, *media_1, *media_2 = "0";
    if (10 <= object <= 99){
        itoa(object, target,10);
    }else if(0 < object <= 9){
        itoa(object, media_1,10);
        strcat(target, media_2);
        strcat(target, media_1);
    }else{
        itoa(object, target,10);
    }

    return *target;
}
