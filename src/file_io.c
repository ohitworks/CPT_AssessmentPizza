/**
  **************************** AssessmentPizza: file_io.c ****************************
  * Created by oh-it-works on 2022/12/17.
  * @file
  * @author     oh it works
  * @date       2022-12-17
  * @brief      文件读写
  **************************** AssessmentPizza: file_io.c ****************************
 */

#include "file_io.h"
#include "file_io_cfg.h"

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


/**
 * @brief
 * @param path
 * @param manager  被写入的管理者, 应当未被初始化
 * @return         0  成功
 *                 -1 文件不存在或不可读
 *                 -2 字符串失败
 */
int read_ascii_file_lines(const char *path, ChainTableManager *manager) {
    int c, letter_counter;
    char buffer[16] = {0};
    bool file_not_end = true;
    FILE *fp;
    ChainTableManager *line;

    // 初始化
    chain_table_init(manager);

    // ---- 判断和打开文件 ----
    if (access(path, F_OK | R_OK) != 0) {
        // 文件不存在或不可读
        return -1;
    }
    fp = fopen(path, "r");

    // ---- 读取文件 ----
    while (file_not_end) {
        // 建一个新行, line 是一个 "字符串"
        chain_table_append(manager, sizeof(ChainTableManager), true);
        line = chain_table_get(manager, -1);
        chain_table_init(line);
        letter_counter = 0;
        while (true) {  // 读取一行
            c = getc(fp);
            // 检测是否结束
            if (c == EOF) {
                file_not_end = false;
                break;
            } else if (c == '\n') {
                // LF
                break;
            } else if (c == '\r') {
                // CR or CRLF
                if (getc(fp) != '\n') {
                    fp--;
                }
                break;
            }
            // 赋值
            buffer[letter_counter] = (char) c;
            letter_counter += 1;

            if (letter_counter >= 16) {
                if (string_extend(line, buffer, letter_counter, READ_LINE_NODE_LENGTH) != 0) {
                    return -2;
                }
                letter_counter = 0;
                memset(buffer, 0, sizeof(buffer));
            }
        }
        if (string_extend(line, buffer, letter_counter, READ_LINE_NODE_LENGTH) != 0) {
            return -2;
        }
    }

    // ---- 收尾 ----
    chain_table_append(manager, sizeof(ChainTableManager), true);
    line = chain_table_get(manager, -1);
    chain_table_init(line);
    if (string_extend(line, buffer, letter_counter, READ_LINE_NODE_LENGTH) != 0) {
        return -2;
    }
    fclose(fp);
    return 0;
}


/**
 * @brief               将字符串数组按照每个字符串一行, 写入文件
 * @param string_array
 * @param file_name
 * @return              0  成功
 *                      -1 文件写入失败
 */
int write_lines_to_file(const ChainTableManager *string_array, const char *file_name) {
    FILE *fp;
    char buffer[128];
    int line_number, read_start;
    ChainTableManager *string;

    fp = fopen(file_name, "w");
    if (fp == NULL) {
        return -1;
    }

    for (line_number = 0; line_number < string_array->length; line_number++) {
        // 迭代每一行的文本
        string = chain_table_get(string_array, line_number);
        read_start = 0;
        while (1) {
            // 循环将每行字符串的内容写入文件
            memset(buffer, 0, sizeof(buffer));
            string_read_with_start(string, buffer, 127, read_start);
            read_start += fputs(buffer, fp);
            if (buffer[126] == '\0') {
                // 循环结束, 写入换行符
                if (line_number != string_array->length - 1) {
                    fputs(WRITE_LINES_END_LINE_BREAK_CHARACTER, fp);
                }
                break;
            }
        }
    }
    return fclose(fp);
}


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

bool file_is_exist(char *file_name) {
    return access(file_name, F_OK) == 0;
}
