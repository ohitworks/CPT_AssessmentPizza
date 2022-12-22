/**
  **************************** test: password.h ****************************
  * Created by oh-it-works on 2022/11/29.
  * @file
  * @author     oh it works
  * @date       2022-11-29
  * @brief      **BriefHere**
  **************************** test: password.h ****************************
 */

#ifndef TEST_PASSWORD_H
#define TEST_PASSWORD_H

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "account_cfg.h"
#include "chain_table.h"


int account_login(char *userid, char *password);

int account_register(USERNAME_TYPE *userid, char *password, const ChainTableManager *username, const char *tel);

int account_change_password(const char *userid, char *password);

int account_in(const ChainTableManager *file, const USERNAME_TYPE *userid);

int account_get_username(const USERNAME_TYPE *userid, ChainTableManager *username);

int account_rename(const char *userid, ChainTableManager *username);

int account_change_balance(const char *userid, int balance);

int account_remove(const char *userid);

int account_get_balance(const char *userid);

void gen_id(char *write_space);

#endif //TEST_PASSWORD_H
