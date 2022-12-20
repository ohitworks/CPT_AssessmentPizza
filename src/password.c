/**
**************************** test: Assessment3_password.c ****************************
* @file
* @author     ohitworks
* @date       2022-11-28
**************************** test: Assessment3_password.c ****************************
*/

#include "file_io.h"
#include "password.h"
#include "chain_table.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void password_hash(const char *password, char disk[]) {
    int hash = 0;

    for (int i = 0; i < PASSWORD_LENGTH_MAX; i++) {
        hash = 33 * hash + (int) password[i];
        if (hash >= (INT_MAX - 256) / 33) {
            itoa(hash, disk + strlen(disk), 16);
            hash = 0;
            printf("%llu\n", strlen(disk));
        }
    }
}


/**
 *
 * @param file
 * @param userid
 * @return        用户名对应的密码所在索引
 */
int account_in(const ChainTableManager *file, USERNAME_TYPE *userid) {
    ChainTableManager *string;
    int ret = 0;
    char buffer[PASSWORD_LENGTH_MAX];

    for (int index = 0; index < file->length; index += 2) {
        string = chain_table_get(file, index);

        memset(buffer, 0, PASSWORD_LENGTH_MAX);
        string_read(string, buffer, PASSWORD_LENGTH_MAX);

        if (memcmp(buffer, userid, PASSWORD_LENGTH_MAX) == 0) {
            ret = index + 1;
            break;
        }
    }

    return ret;
}


/**
 * @brief           注册账号
 * @param userid    用户名
 * @param password  密码
 * @return          注册成功返回 0
 *                  用户已存在返回 -1
 */
int account_register(USERNAME_TYPE *userid, char *password) {
    ChainTableManager file;
    ChainTableManager *string;
    char password_char[22] = {0};

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);

    if (account_in(&file, userid) != 0) {
        // 用户已存在
        return -1;
    }

    // 写入 id
    chain_table_append(&file, sizeof(ChainTableManager), true);
    string = chain_table_get(&file, -1);
    chain_table_init(string);
    string_extend(string, userid, PASSWORD_LENGTH_MAX, PASSWORD_LENGTH_MAX);

    // 写入密码
    chain_table_append(&file, sizeof(ChainTableManager), true);
    string = chain_table_get(&file, -1);
    chain_table_init(string);
    password_hash(password, password_char);
    string_extend(string, password_char, -1, 22);

    // 写入空节点, 用于换行
    chain_table_append(&file, sizeof(ChainTableManager), true);
    string = chain_table_get(&file, -1);
    chain_table_init(string);

    write_lines_to_file(&file, ACCOUNT_INFO_FILE_PATH);

    chain_table_clear(&file, FREE_AS_MANAGER);

    return 0;
}

/**
 * @brief           登录用户
 * @param userid    待登录的用户名
 * @param password  密码
 * @return          登录成功返回 0
 *                  用户不存在返回 -1
 *                  密码错误返回 -2
 */
int account_login(USERNAME_TYPE *userid, char *password) {
    ChainTableManager file;
    ChainTableManager *string;
    int password_index;
    char password_hashed[22] = {0};
    char password_read[22] = {0};

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);
    password_index = account_in(&file, userid);
    if (password_index == 0) {
        // 用户不存在
        return -1;
    }

    password_hash(password, password_hashed);

    string = chain_table_get(&file, password_index);
    string_read(string, password_read, 22);

    if (strcmp(password_hashed, password_read) == 0) {
        return -2;
    }

    // 登录成功
    return 0;
}

/**
 * @brief           修改密码
 * @param userid    用户名
 * @param password  新密码
 * @return          修改成功返回 0
 *                  用户不存在返回 -1
 */
int account_change_password(USERNAME_TYPE *userid, char *password) {
    ChainTableManager file;
    ChainTableManager *string;
    int password_index;
    char password_hashed[22] = {0};

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);
    password_index = account_in(&file, userid);
    if (password_index == 0) {
        // 用户不存在
        return -1;
    }

    password_hash(password, password_hashed);

    // 更新密码
    string = chain_table_get(&file, password_index);
    chain_table_clear(string, FREE_AS_MANAGER);
    chain_table_init(string);
    string_extend(string, password_hashed, -1, 22);

    write_lines_to_file(&file, ACCOUNT_INFO_FILE_PATH);
    chain_table_clear(&file, FREE_AS_MANAGER);

    return 0;
}

char *gen_id() {
    int count;
    char ID;

}