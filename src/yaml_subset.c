/**
  **************************** AssessmentPizza: yaml.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      实现 yaml 的子集读写
  **************************** AssessmentPizza: yaml.c ****************************
 */

#include "yaml_subset.h"
#include "yaml_subset_cfg.h"

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
 * @return         0 成功
 */
int read_ascii_file_lines(char *path, ChainTableManager *manager) {
    int c, letter_counter;
    char *ptr_in_line;
    bool not_end = true;
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
    while (not_end) {
        // 建一个新行
        chain_table_append(manager, sizeof(ChainTableManager), true);
        line = chain_table_get(manager, -1);
        chain_table_init(line);
        // 在行内添加字符
        chain_table_append(line, sizeof(char) * READ_LINE_NODE_LENGTH, false);
        ptr_in_line = chain_table_get(line, -1);
        letter_counter = READ_LINE_NODE_LENGTH;
        while (true) {
            c = getc(fp);
            // 检测是否结束
            if (c == EOF) {
                not_end = false;
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

            // 判断是否需要添加节点
            if (letter_counter == READ_LINE_NODE_LENGTH) {
                chain_table_append(line, sizeof(char) * READ_LINE_NODE_LENGTH, false);
                ptr_in_line = chain_table_get(line, -1);
                letter_counter = 0;
            }

            // 赋值
            ptr_in_line[letter_counter] = (char) c;
            letter_counter += 1;
        }
    }

    // ---- 收尾 ----
    fclose(fp);
    return 0;
}


/**
 * @brief       清空一个yaml
 * @param yaml  将被操作的yaml
 */
void yaml_subset_free(Yaml *yaml) {
    switch (yaml->data_type) {
        case YAML_NULL:
            // The yaml has been free, just return.
            return;
        case YAML_INT:
        case YAML_DOUBLE:
            // Nothing needed, just set the yaml to 0.
            break;
        case YAML_STRING:
            // Free the chain table.
            chain_table_clear((ChainTableManager *) yaml->data, FREE_AS_MANAGER);
            break;
        case YAML_LIST:
            for (int i = 0; i < ((ChainTableManager *) yaml->data)->length; i++) {
                yaml_subset_free((Yaml *) chain_table_get((ChainTableManager *) yaml->data, i));
            }
            chain_table_clear((ChainTableManager *) yaml->data, FREE_AS_MANAGER);
            memcpy(yaml, (Yaml *) yaml->data2, sizeof(Yaml));
            break;
    }
    memset(yaml, 0, sizeof(Yaml));
}

/**
 * @brief
 * @param path
 * @param yaml
 * @return      0  成功
 *              -1 文件不存在或不可读
 */
int yaml_subset_read(const char *path, Yaml *yaml) {
    FILE *fp;
    char c;

    // ---- 判断和打开文件 ----
    if (access(path, F_OK | R_OK) != 0) {
        // 文件不存在或不可读
        return -1;
    }

    fp = fopen(path, "r");

    // ---- 读文件 ----
    do {
        c = (char) getc(fp);


    } while (c != EOF);

    return 0;
}
