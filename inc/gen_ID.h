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

#define ACCOUNT_LENGTH_MAX 15
#define ACCOUNT_FILE_PATH "gen_account.txt"

char gen_id(char ID[ACCOUNT_LENGTH_MAX]);

void gen_random_string(char * dest);

#endif //ASSESSMENTPIZZA_GEN_ID_H
