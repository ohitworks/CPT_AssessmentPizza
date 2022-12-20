/**
  **************************** test: password.h ****************************
  * Created by Juntong on 2022/11/29.
  * @file
  * @author     Juntong
  * @date       2022-11-29
  * @brief      **BriefHere**
  **************************** test: password.h ****************************
 */

#ifndef TEST_PASSWORD_H
#define TEST_PASSWORD_H

#include "account_cfg.h"


int account_login(char *userid, char *password);

int account_register(USERNAME_TYPE *userid, char *password, const ChainTableManager *username);

int account_change_password(USERNAME_TYPE *userid, char *password);

int account_in(const ChainTableManager *file, USERNAME_TYPE *userid);


#endif //TEST_PASSWORD_H
