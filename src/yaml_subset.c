/**
  **************************** AssessmentPizza: yaml.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      实现 yaml 的子集读写
  **************************** AssessmentPizza: yaml.c ****************************
 */

#include "file_io.h"
#include "yaml_subset.h"
#include "yaml_subset_cfg.h"

#include <iso646.h>
#include <string.h>



static int read_static_yaml_struct(const ChainTableManager *string, Yaml *yaml, uint8_t retract_level);

static YAML_NODE_DATA_TYPE yaml_struct_check(const ChainTableManager *string, uint8_t retract_level);


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

static int read_static_yaml_struct(const ChainTableManager *string, Yaml *yaml, uint8_t retract_level) {
    char c;
    int index;
    ChainTableNode *node;

    index = retract_level * 4;
    c = string_char_get(string, index);
    if (c == '"') {
        // 文本类型
    } else if (48 <= c and c <= 57) {
        // 说明是数字
    } else if (c == '-') {
        c = string_char_get(string, index + 1);
        if (c == ' ') {
            // 列表
        } else if (48 <= c and c <= 57) {
            // 数字
        }
    }
    index += 1;


    return 0;
}


static YAML_NODE_DATA_TYPE yaml_struct_check(const ChainTableManager *string, uint8_t retract_level) {
    char c;
    retract_level *= 4;
    c = string_char_get(string, retract_level);
    if (c == '"') {
        // 文本类型
        return YAML_STRING;
    } else if (48 <= c and c <= 57) {
        // 说明是数字或小数
        return YAML_INT;
    } else if (c == '-') {
        c = string_char_get(string, retract_level + 1);
        if (c == ' ') {
            // 列表
            return YAML_LIST;
        } else if (48 <= c and c <= 57) {
            // 数字或小数
        }
    }
}

/**
 * @brief
 * @param path
 * @param yaml
 * @return      0  成功
 *              -1 文件读取失败 (基于 read_ascii_file_lines)
 */
int yaml_subset_read(const char *path, Yaml *yaml) {
    ChainTableManager lines;

    if (read_ascii_file_lines(path, &lines) != 0) {
        return -1;
    }

// TODO: Finish simple read.

    return 0;
}
