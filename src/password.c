/**
**************************** test: Assessment3_password.c ****************************
* @file
* @author     ohitworks
* @date       2022-11-28
**************************** test: Assessment3_password.c ****************************
*/

#include "password.h"
#include "file_io.h"

#include <string.h>


/**
 * @brief           注册账号
 * @param username  用户名
 * @param password  密码
 * @return          注册成功返回 0
 *                  用户已存在返回 -1
 */
int account_register(USERNAME_TYPE *username, char *password) {
    AccountUsernamePassword account;

    if (file_is_exist(username)) {
        // 文件已存在，说明不能注册
        return -1;
    }

    memcpy(account.username, username, USERNAME_LENGTH_MAX * sizeof(USERNAME_TYPE));
    memcpy(account.username, password, PASSWORD_LENGTH_MAX * sizeof(char));

    write_bin(username, &account, sizeof(account));

    return 0;
}

/**
 * @brief           登录用户
 * @param username  待登录的用户名
 * @param password  密码
 * @return          注册成功返回 0
 *                  用户不存在返回 -1
 *                  密码错误返回 -2
 */
int account_login(USERNAME_TYPE *username, char *password){
    AccountUsernamePassword account;

    if (!file_is_exist(username)) {
        // 文件不存在，说明用户不存在
        return -1;
    }

    read_bin(username, &account, sizeof(account));

    if (memcmp(password, account.password, PASSWORD_LENGTH_MAX * sizeof(USERNAME_TYPE)) == 0) {
        // 两个数组内容相同
        return 0;
    } else {
        return -2;
    }
}

/**
 * @brief           修改密码
 * @param username  用户名
 * @param password  新密码
 * @return          修改成功返回 0
 *                  用户不存在返回 -1
 */
int account_change_password(USERNAME_TYPE *username, char *password){
    AccountUsernamePassword account;

    if (!file_is_exist(username)) {
        // 文件不存在，说明用户不存在
        return -1;
    }

    memcpy(account.username, username, USERNAME_LENGTH_MAX * sizeof(USERNAME_TYPE));
    memcpy(account.username, password, PASSWORD_LENGTH_MAX * sizeof(char));

    write_bin(username, &account, sizeof(account));

    return 0;
}
