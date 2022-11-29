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

typedef struct {
    USERNAME_TYPE username[USERNAME_LENGTH_MAX + 1];
    USERNAME_TYPE password[PASSWORD_LENGTH_MAX + 1];
}AccountUsernamePassword;

typedef struct {

} AccountUsernames;

int account_login(char *username, char *password);

int account_register(USERNAME_TYPE *username, char *password);

int account_change_password(USERNAME_TYPE *username, char *password);

AccountUsernames account_get_all_username();

#endif //TEST_PASSWORD_H
