/**
**************************** test: Assessment3_password.c ****************************
* @file
* @author     ohitworks
* @date       2022-11-28
**************************** test: Assessment3_password.c ****************************
*/

#include "file_io.h"
#include "customer.h"
#include "chain_table.h"

#include <string.h>
#include <stdlib.h>
#include <process.h>
#include <Windows.h>

#ifndef itoa
#define itoa _itoa
#endif

#ifndef getpid
#define getpid _getpid
#endif


void password_hash(const char *password, char disk[]) {
    int hash = 0;

    for (int i = 0; i < PASSWORD_LENGTH_MAX; i++) {
        hash = 33 * hash + (int) password[i];
        if (hash >= (INT_MAX - 256) / 33) {
            itoa(hash, disk + strlen(disk), 16);
            hash = 0;
        }
    }
}


/**
 *
 * @param file
 * @param userid
 * @return        用户名对应的密码所在索引
 */
int account_in(const ChainTableManager *file, const USERNAME_TYPE *userid) {
    ChainTableManager *string;
    int ret = 0;
    char buffer[PASSWORD_LENGTH_MAX];

    for (int index = 0; index < file->length; index += 5) {
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
int account_register(USERNAME_TYPE *userid, char *password, const ChainTableManager *username) {
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

    // 写入用户名
    chain_table_append(&file, sizeof(ChainTableManager), true);
    string = chain_table_get(&file, -1);
    chain_table_init(string);
    string_extend_string(string, username);

    // 写入用户余额
    chain_table_append(&file, sizeof(ChainTableManager), true);
    string = chain_table_get(&file, -1);
    chain_table_init(string);
    string_extend(string, "0", 1, 1);

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


/**
 * @brief           修改密码
 * @param userid    用户 ID
 * @param username  用户名写入位置, 将被视为未初始化节点
 * @return          成功返回 0
 *                  用户不存在返回 -1
 */
int account_get_username(const USERNAME_TYPE *userid, ChainTableManager *username) {
    ChainTableManager file;
    int password_index;

    chain_table_init(username);

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);
    password_index = account_in(&file, userid);
    if (password_index == 0) {
        // 用户不存在
        return -1;
    }

    string_extend_string(username, chain_table_get(&file, password_index + 1));

    chain_table_clear(&file, FREE_AS_MANAGER);

    return 0;
}


int account_get_balance(const char *userid) {
    ChainTableManager file;
    ChainTableManager *string;
    int password_index, balance;
    char buffer[32];
    char *c;

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);
    password_index = account_in(&file, userid);
    if (password_index == 0) {
        // 用户不存在
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));
    string = chain_table_get(&file, password_index + 1);
    string_read(string, buffer, 128);
    balance = (int) strtol(buffer, &c, 10);

    chain_table_clear(&file, FREE_AS_MANAGER);

    return balance;
}


int account_change_balance(const char *userid, int balance) {
    ChainTableManager file;
    ChainTableManager *string;
    int index;
    char buffer[32] = {0};

    read_ascii_file_lines(ACCOUNT_INFO_FILE_PATH, &file);
    index = account_in(&file, userid);
    if (index == 0) {
        // 用户不存在
        return -1;
    }
    index += 1;

    chain_table_remove(&file, FREE_AS_MANAGER, index);

    itoa(balance, buffer, 10);
    chain_table_insert(&file, sizeof(ChainTableManager), true, index);
    string = chain_table_get(&file, index);
    chain_table_init(string);
    string_extend(string, buffer, -1, 1);

    write_lines_to_file(&file, ACCOUNT_INFO_FILE_PATH);

    chain_table_clear(&file, FREE_AS_MANAGER);

    return balance;
}


void gen_id(char *write_space) {
    char buffer[PASSWORD_LENGTH_MAX] = {0};
    volatile int length, write_length, keeper;  // 哪个变量招谁惹谁了?! 神奇的原因解决问题!
    // 我猜解决原因是 volatile 关键字减慢了程序运行速度, 因此运行成功
    // 猜测问题原因是 MinGW-gcc 的 getpid 函数有问题, NOTE: 建立pid变量后, 在写入buffer前打印, 不能解决问题
    // 在 Visual Studio 上不加关键字没问题
    SYSTEMTIME sys_time;
    uint32_t mul = 1;

    memset(write_space, 0, PASSWORD_LENGTH_MAX);

    GetSystemTime(&sys_time);
    itoa(sys_time.wMonth * 32 + sys_time.wDay, write_space, 32);
    length = (int) strlen(write_space);
    itoa(sys_time.wSecond * 1000 + sys_time.wMilliseconds, write_space + length, 16);
    length = (int) strlen(write_space);

    if (length >= PASSWORD_LENGTH_MAX) {
        return;
    }

    itoa(getpid(), buffer, 10);
    write_length = PASSWORD_LENGTH_MAX - length;
    if (write_length <= 9) {
        keeper = 1;
        for (int i = 0; i < write_length; i++) {}
        keeper *= 10;
    } else {
        keeper = INT32_MAX;
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (i % 10) {
            Sleep(100);
        }
        if (i % 5 == 0) {
            // FIXME: vs 上无法获取毫秒级时间戳
            GetSystemTime(&sys_time);
//            printf("%d-%d\n", sys_time.wSecond, sys_time.wMilliseconds);
        }
        mul = (mul * 313 + buffer[i] + (sys_time.wMilliseconds + i) % 10);
        mul %= keeper;
    }
    memset(buffer, 'A', sizeof(buffer));
    itoa((int) mul, buffer, 10);
    buffer[strlen(buffer)] = buffer[0];

    memcpy(write_space + length, buffer, write_length);

}