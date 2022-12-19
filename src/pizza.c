/**
  **************************** AssessmentPizza: pizza.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      Pizza and it's operations.
  **************************** AssessmentPizza: pizza.c ****************************
 */

#include "pizza.h"
#include "file_io.h"

#include <string.h>
#include <stdlib.h>


/**
 * @brief             获取 pizza 的名称, 将其写入 disk 中
 * @param pizza       待处理的 Pizza
 * @param dest        名称写入此
 * @param max_length  disk 的最大长度
 * @return            >0 : 名称长度
 *                    -1 : max_length < 名称长度
 */
int pizza_name_get(Pizza *pizza, PIZZA_NAME_TYPE *dest, int max_length) {
    return string_read(&pizza->name, dest, max_length);
}


/**
 * @brief             使用参数初始化 pizza
 * @param pizza       待处理的实例
 * @param pizza_name  披萨的名称, 注意应当有 '\0' 结束符
 * @param pizza_type  披萨的类型
 * @param pizza_size  披萨的尺寸
 * @return            0 成功
 *                    -1 内存获取失败
 *                    -2 名称太长
 */
int pizza_init(Pizza *pizza, const char *pizza_name, const char *pizza_type, int pizza_size) {

    memset(pizza, 0, sizeof(Pizza));
    chain_table_init(&pizza->name);

    // ---- 写入类型和尺寸 ----
    if (strlen(pizza_type) > PIZZA_TYPE_NAME_MAX_LENGTH) {
        return -2;
    }
    strcpy(pizza->type, pizza_type);
    pizza->size = pizza_size;

    // ---- 写入名称 ----
    string_extend(&pizza->name, pizza_name, -1, PIZZA_NAME_NODE_SIZE);

    return 0;
}


/**
 * @brief        释放 pizza 空间, 并将其置为0
 * @param pizza  待处理的实例
 */
void pizza_free(Pizza *pizza) {
    chain_table_clear(&pizza->name, RETURN_IF_DYNAMIC);
    memset(pizza, 0, sizeof(Pizza));
}


/**
 * @brief            写入或更新 pizza 配置文件
 * @param pizza
 * @param file_name
 * @return           0  成功
 *                   -1 文件读写失败
 */
int pizza_save(Pizza *pizza, const char *file_name) {
    ChainTableManager file;
    ChainTableManager *string;
    int i;
    int read_return, pizza_index = -1;
    char buffer[PIZZA_TYPE_NAME_MAX_LENGTH * 2];


    read_return = read_ascii_file_lines(file_name, &file);

    if (read_return == 0) {
        // 文件存在, 读取顺利
        for (i = 0; i < file.length; i++) {
            string = chain_table_get(&file, i);
            memset(buffer, 0, sizeof(buffer));
            string_read(string, buffer, PIZZA_TYPE_NAME_MAX_LENGTH * 2);
            if (strcmp(buffer, "[pizza]") == 0) {
                // pizza name here
                if (string_equal(&pizza->name, chain_table_get(&file, i + 1))) {
                    pizza_index = i;
                    break;
                }
                // pizza 有三个成员, 因此向下三行可以跳到成员末尾
                i += 3;
            }
        }
    }
    if (pizza_index != -1) {
        // 修改参数
        // 写入类型
        string = chain_table_get(&file, pizza_index + 2);
        chain_table_clear(string, RETURN_IF_DYNAMIC);
        string_extend(string, pizza->type, -1, 8);
        // 写入大小
        string = chain_table_get(&file, pizza_index + 3);
        memset(buffer, 0, sizeof(buffer));
        itoa(pizza->size, buffer, 10);
        chain_table_clear(string, RETURN_IF_DYNAMIC);
        string_extend(string, buffer, -1, 8);
    } else {
        // 文件读取失败, 或 向文末添加文本
        // 添加标头
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);
        string_extend(string, "[pizza]", 7, 7);
        // 添加名称
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);
        string_extend_string(string, &pizza->name);
        // 添加类型
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);
        string_extend(string, pizza->type, -1, 8);
        // 添加大小
        chain_table_append(&file, sizeof(ChainTableManager), true);
        string = chain_table_get(&file, -1);
        chain_table_init(string);
        memset(buffer, 0, sizeof(buffer));
        itoa(pizza->size, buffer, 10);
        string_extend(string, buffer, -1, 8);
    }
    read_return = write_lines_to_file(&file, file_name);

    chain_table_clear(&file, FREE_AS_MANAGER);

    return read_return;
}

/**
 * @brief            从文件加载 pizza 列表
 * @param pizzas     待写入的链表, 被视为未初始化的链表管理器, 将添加 Pizza 类型的成员
 * @param file_name  配置文件名
 * @return           0  成功
 *                   -1 文件读取失败
 */
int pizza_load_from_file(ChainTableManager *pizzas, const char *file_name) {
    ChainTableManager file;
    ChainTableManager *string;
    Pizza *pizza;
    char *ptr;
    char buffer[128];

    chain_table_init(pizzas);

    if(read_ascii_file_lines(file_name, &file) != 0) {
        return -1;
    }

    for (int i = 0; i < file.length; i++) {
        string = chain_table_get(&file, i);
        memset(buffer, 0, sizeof(buffer));
        string_read(string, buffer, 128);
        if (strcmp(buffer, "[pizza]") == 0) {
            // 找到了一个 pizza 成员
            // 新建
            chain_table_append(pizzas, sizeof(Pizza), true);
            pizza = chain_table_get(pizzas, -1);
            // 写入名称
            i += 1;
            string = chain_table_get(&file, i);
            string_extend_string(&pizza->name, string);
            // 写入类型
            i += 1;
            string = chain_table_get(&file, i);
            memset(buffer, 0, sizeof(buffer));
            string_read(string, buffer, PIZZA_TYPE_NAME_MAX_LENGTH);
            memcpy(pizza->type, buffer, PIZZA_TYPE_NAME_MAX_LENGTH);
            // 写入大小
            i += 1;
            string = chain_table_get(&file, i);
            memset(buffer, 0, sizeof(buffer));
            string_read(string, buffer, PIZZA_TYPE_NAME_MAX_LENGTH);
            pizza->size = (int) strtol(buffer, &ptr, 10);
        }
    }

    chain_table_clear(&file, FREE_AS_MANAGER);

    return 0;
}

int pizza_free_pizza_array(ChainTableManager *pizzas) {
    Pizza * pizza;
    ChainTableNode *node;
    int index;

    for (index = 0; index < pizzas->length; index++) {
        chain_table_node_get(pizzas, index, &node);
        pizza = node->ptr;
        pizza_free(pizza);
    }
    chain_table_clear_directly(pizzas);
    return 0;
}
