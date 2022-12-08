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

#include <string.h>


/**
 * @brief             获取 pizza 的名称, 将其写入 disk 中
 * @param pizza       待处理的 Pizza
 * @param dest        名称写入此
 * @param max_length  disk 的最大长度
 * @return            >0 : 名称长度
 *                    -1 : max_length < 名称长度
 */
int pizza_name_get(Pizza *pizza, PIZZA_NAME_TYPE *dest, int max_length) {
    int length = 0, letter_count = 0, index = 0;
    PIZZA_NAME_TYPE *ptr = chain_table_get(&pizza->name, 0);

    while (length < max_length) {
        // dest 未写满
        if (letter_count++ < PIZZA_NAME_NODE_SIZE) {
            // 不需要切换名称链表指针

            // 将内容写入 disk
            *(dest + length) = *ptr;
            if (*ptr == '\0') {
                return length;
            }

            ptr++;
            length += 1;
        } else {
            // 需要切换链表指针
            letter_count = 0;
            ptr = chain_table_get(&pizza->name, ++index);
            if (ptr == NULL) {
                *(dest + length) = '\0';
                return length;
            } else {
                continue;
            }
        }
    }
    return -1;
}


/**
 * @brief             使用参数初始化 pizza
 * @param pizza       待处理的实例
 * @param pizza_name  披萨的名称, 注意应当有 '\0' 结束符
 * @param pizza_type  披萨的类型
 * @param pizza_size  披萨的尺寸
 * @return            0 成功
 *                    -1 内存获取失败
 */
int pizza_init(Pizza *pizza, const char *pizza_name, const char *pizza_type, int pizza_size) {
    PIZZA_NAME_TYPE *name;
    int letter_count = 0;

    memset(pizza, 0, sizeof(Pizza));
    chain_table_init(&pizza->name);

    // ---- 写入名称 ----
    // 添加节点
    if (chain_table_append(&pizza->name, sizeof(PIZZA_NAME_TYPE) * PIZZA_NAME_NODE_SIZE) != 0) {
        return -1;
    }
    name = chain_table_get(&pizza->name, -1);
    // 循环写入名称
    while (*pizza_name != '\0') {
        // 名称未结束
        if (letter_count < PIZZA_NAME_NODE_SIZE) {
            name[letter_count] = *pizza_name;
            letter_count += 1;
        } else {
            // 需要添加节点
            if (chain_table_append(&pizza->name, sizeof(PIZZA_NAME_TYPE) * PIZZA_NAME_NODE_SIZE) != 0) {
                // 节点添加失败
                chain_table_clear(&pizza->name);  // 清空已分配的内存
                return -1;
            }
            name = chain_table_get(&pizza->name, -1);
        }
        pizza_name++;
    }
    // ---- 写入类型和尺寸 ----
    strcpy(pizza->type, pizza_type);
    pizza->size = pizza_size;
    return 0;
}