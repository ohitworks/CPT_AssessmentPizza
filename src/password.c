/**
**************************** test: Assessment3_password.c ****************************
* @file
* @author     ohitworks
* @date       2022-11-28
**************************** test: Assessment3_password.c ****************************
*/

#include "password.h"

#include <io.h>
#include <stdio.h>
#include <string.h>


#ifndef F_OK
#define F_OK 0
#endif

#ifndef W_OK
#define W_OK 2
#endif

#ifndef R_OK
#define R_OK 4
#endif

#ifndef access
#define access _access
#endif


int write_bin(char *file_path, const void *obj, size_t obj_size);

int read_bin(char *file_path, void *obj, size_t obj_size);


/**
* @brief            Write an object to file.
* @param file_path  The path of file.
* @param obj        The object to write.
* @param obj_size   The size of object.
* @return           The return of file close function.
*/
int write_bin(char *file_path, const void *obj, size_t obj_size) {
    FILE *fp = fopen(file_path, "wb");
    fwrite(obj, 1, obj_size, fp);
    return fclose(fp);
}

/**
* @brief            Read bin from file and write it to a struct.
* @param file_path  The path of file.
* @param obj        The object to write.
* @param obj_size   The size of object.
* @return           The return of file close function.
*/
int read_bin(char *file_path, void *obj, size_t obj_size) {
    FILE *fp = fopen(file_path, "rb");
    fread(obj, 1, obj_size, fp);
    return fclose(fp);
}

/**
 * @brief           注册账号
 * @param username  用户名
 * @param password  密码
 * @return          注册成功返回 0
 *                  用户已存在返回 -1
 */
int account_register(USERNAME_TYPE *username, char *password) {
    int file_exist;
    AccountUsernamePassword account;

    file_exist = access(username, F_OK);
    if (file_exist == 0) {
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
    int file_exist;
    AccountUsernamePassword account;

    file_exist = access(username, F_OK);
    if (file_exist != 0) {
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
    int file_exist;
    AccountUsernamePassword account;

    file_exist = access(username, F_OK);
    if (file_exist != 0) {
        // 文件不存在，说明用户不存在
        return -1;
    }

    memcpy(account.username, username, USERNAME_LENGTH_MAX * sizeof(USERNAME_TYPE));
    memcpy(account.username, password, PASSWORD_LENGTH_MAX * sizeof(char));

    write_bin(username, &account, sizeof(account));

    return 0;
}
