/**
  **************************** AssessmentPizza: chain_table.c ****************************
  * Created by Juntong on 2022/12/2.
  * @file
  * @author     oh it works
  * @date       2022-12-02
  * @brief      实现了链表, 不考虑线程安全
  **************************** AssessmentPizza: chain_table.c ****************************
 */

#include "chain_table.h"

#include <stdlib.h>
#include <string.h>
#include <iso646.h>


#define string_extend_min(a, b) a < b ? a : b


int chain_table_node_create(ChainTableNode **node, size_t size, bool is_dynamic);


/**
 * @brief          初始化一个链表管理器
 * @param manager  链表管理器
 * @return         始终返回 0
 */
int chain_table_init(ChainTableManager *manager) {
    memset(manager, 0, sizeof(ChainTableManager));
    return 0;
}

/**
 * @brief          清空链表管理器的所有链表
 * @param manager  待清空的链表管理器
 * @return         0  顺利清空
 *                 -1 有动态节点导致未能清空
 */
int chain_table_clear(ChainTableManager *manager, ChainTableFreeModes mode) {

    int ret;
    ChainTableNode *ptr;
    ChainTableNode *to_del;

    if (manager->length == 0) {
        return 0;
    }

    // ---- Mode check ----
    if (mode == RETURN_IF_DYNAMIC) {
        // 只要有被标记为动态的节点, 就返回-1
        ptr = manager->head;
        while (ptr != manager->tail) {
            if (ptr->is_dynamic == true) {
                return -1;
            }
            ptr = ptr->next;
        }
        if (ptr->is_dynamic == true) {
            return -1;
        }
    } else if (mode == FREE_AS_MANAGER) {
        // 如果遇到动态节点, 检测其大小是否等于链表管理器, 若是则将其内容是为管理器执行释放, 不是则返回-1
        ptr = manager->head;
        while (ptr != NULL) {
            if (ptr->is_dynamic == true) {
                if (ptr->size == sizeof(ChainTableManager)) {
                    // 将 ptr 节点的值视作 管理器 , 尝试释放
                    ret = chain_table_clear((ChainTableManager *) ptr->ptr, FREE_AS_MANAGER);
                    if (ret != 0) {
                        return ret;
                    }
                } else {
                    return -1;
                }
            }
            ptr = ptr->next;
        }
    }

    // ---- Clear ----
    ptr = manager->tail->last;
    to_del = manager->tail;

    while (ptr != NULL) {
        free(to_del);
        to_del = ptr;
        ptr = ptr->last;
    }
    free(to_del);

    memset(manager, 0, sizeof(ChainTableManager));

    return 0;
}


/**
 * @brief          删除链表的 index 号节点
 * @param manager  链表管理器
 * @param index    index 号链表节点, 若获取失败也可能修改
 * @return         0 表示成功
 *                 -1 表示 index 不存在
 *                 -2 表示链表有问题
 *                 -3 有动态节点导致未执行
 *                 -4 清空时出错
 *                 -5 未知的模式
 */
int chain_table_remove(ChainTableManager *manager, ChainTableFreeModes mode, int index) {
    ChainTableNode *to_del = manager->tail;

    // ---- 判断索引 ----
    // 长度判断
    if (manager->length <= 0) {
        // 传入空链表
        return -1;
    }
    // 处理 index < 0 情况
    if (index < 0) {
        index += manager->length;
    }
    // 输入判断
    if (index >= manager->length or index < 0) {
        return -1;
    }

    // ---- 指定 to_del, 修改前后链表指针 ----
    if (index == 0) {
        // 删除第一个
        to_del = manager->head;
        // 根据mode判断是否可释放
        if (to_del->is_dynamic) {
            if (mode == RETURN_IF_DYNAMIC) {
                return -3;
            } else if (mode == FREE_AS_MANAGER) {
                if (to_del->size != sizeof(ChainTableManager)) {
                    return -3;
                }
                if (chain_table_clear((ChainTableManager *) to_del->ptr, mode) != 0) {
                    return -4;
                }
            } else {
                return -5;
            }
        }
        // 执行释放前准备
        manager->head = to_del->next;
        if (manager->tail == to_del) {
            manager->tail = NULL;
        }
    } else if (index == manager->length - 1) {
        // 删除末尾
        to_del = manager->tail;
        // 根据mode判断是否可释放
        if (to_del->is_dynamic) {
            if (mode == RETURN_IF_DYNAMIC) {
                return -3;
            } else if (mode == FREE_AS_MANAGER) {
                if (to_del->size != sizeof(ChainTableManager)) {
                    return -3;
                }
                if (chain_table_clear((ChainTableManager *) to_del->ptr, mode) != 0) {
                    return -4;
                }
            } else {
                return -5;
            }
        }
        // 执行释放前准备
        manager->tail = to_del->last;
        if (manager->head == to_del) {
            manager->head = NULL;
        }
    } else {
        // 获取值
        if (chain_table_node_get(manager, index, &to_del) != 0) {
            return -2;
        }
        // 根据mode判断是否可释放
        if (to_del->is_dynamic) {
            // 是动态节点, 需要考虑释放情况
            if (mode == RETURN_IF_DYNAMIC) {
                return -3;
            } else if (mode == FREE_AS_MANAGER) {
                if (to_del->size != sizeof(ChainTableManager)) {
                    return -3;
                }
                if (chain_table_clear((ChainTableManager *) to_del->ptr, mode) != 0) {
                    return -4;
                }
            } else {
                return -5;
            }
        }
        // 执行释放前准备
        to_del->last->next = to_del->next;
        to_del->next->last = to_del->last;
    }

    // 执行删除
    free(to_del);
    manager->length -= 1;
    return 0;
}

/**
 * @brief          获取 index 号链表节点
 * @param manager  链表管理器
 * @param index    索引, 0 代表第一个, 随链表向后依次递增; -1代表最后一个, 随链表向前依次递减
 * @param node     index 号链表节点, 若获取失败也可能修改
 * @return         0 表示成功
 *                 -1 表示索引不合理
 *                 -2 表示迭代时出现异常
 * @note           无论输入索引为多少, 程序由前向后查找元素
 * @warning        不应在链表管理器之外调用
 */
int chain_table_node_get(const ChainTableManager *manager, int index, ChainTableNode **node) {
    // 处理 index < 0 情况
    if (index < 0) {
        index += manager->length;
    }
    // 输入判断
    if (index >= manager->length or index < 0) {
        return -1;
    }

    *node = manager->head;
    for (int i = 0; i < index; i++) {
        *node = (*node)->next;
        if ((*node) == NULL) {
            return -2;
        }
    }
    return 0;
}

/**
 * @brief          获取链表管理器 index 号元素对应内容的指针
 * @param manager  链表管理器
 * @param index    索引, 0 代表第一个, 随链表向后依次递增; -1代表最后一个, 随链表向前依次递减
 * @return         获取失败返回 NULL, 成功返回指定元素对应内容的指针
 * @warning        不要试图释放指针空间
 */
void *chain_table_get(ChainTableManager *manager, int index) {
    ChainTableNode *node = NULL;
    if (chain_table_node_get(manager, index, &node) != 0) {
        return NULL;
    }
    return node->ptr;
}

/**
 * @brief             创建一个节点
 * @param node        节点指针
 * @param size        节点对应的元素空间
 * @param is_dynamic
 * @return            0 表示成功
 *                    -1 获取内存失败
 * @note              事实上程序没有为节点的元素分配单独的空间, 而是在创建节点时一次性分配其所有空间,
 *                    有 node == ((ChainTableNode *) node->ptr) + 1
 */
int chain_table_node_create(ChainTableNode **node, size_t size, bool is_dynamic) {

    *node = malloc(size + sizeof(ChainTableNode));
    if (*node == NULL) {
        return -1;
    }
    memset(*node, 0, size + sizeof(ChainTableNode));

    (*node)->size = size;
    (*node)->is_dynamic = is_dynamic;
    (*node)->ptr = (*node) + 1;
    return 0;
}

/**
 *@brief                向链表后添加一个节点
 * @param manager       链表管理器
 * @param element_size  新节点的元素大小
 * @return              0 成功
 *                      -1 内存分配失败
 */
int chain_table_append(ChainTableManager *manager, size_t element_size, bool is_dynamic) {
    ChainTableNode *new_node = NULL;

    chain_table_node_create(&new_node, element_size, is_dynamic);
    if (new_node == NULL) {
        return -1;
    }

    if (manager->tail != NULL) {
        manager->tail->next = new_node;
    }
    new_node->last = manager->tail;
    manager->tail = new_node;
    if (manager->length == 0) {
        manager->head = new_node;
    }

    manager->length += 1;
    return 0;
}

/**
 *@brief                向链表插入一个节点, 新节点的索引为 index
 * @param manager       链表管理器
 * @param element_size  新节点的元素大小
 * @param index         新节点的索引; 0 代表第一个, 随链表向后依次递增; -1代表最后一个, 随链表向前依次递减
 * @return              0 成功
 *                      -1 内存分配失败
 *                      -2 索引错误
 *                      -3 意外错误
 */
int chain_table_insert(ChainTableManager *manager, size_t element_size, bool is_dynamic, int index) {
    ChainTableNode *new_node = NULL;
    ChainTableNode *old_node = NULL;

    // 处理 index < 0 情况
    if (index < 0) {
        index += manager->length;
    }
    // 输入判断
    if (index > manager->length or index < 0) {
        return -2;
    }

    // 创建并插入节点
    chain_table_node_create(&new_node, element_size, is_dynamic);
    if (new_node == NULL) {
        return -1;
    }
    if (index == manager->length) {
        if (manager->tail != NULL) {
            manager->tail->next = new_node;
        }
        new_node->last = manager->tail;
        manager->tail = new_node;
    } else if (index == 0) {
        if (manager->head != NULL) {
            manager->head->last = new_node;
        }
        new_node->next = manager->head;
        manager->head = new_node;
    } else {
        if (chain_table_node_get(manager, index, &old_node) != 0) {
            return -3;
        }

        // 修改节点联系
        new_node->last = old_node->last;
        new_node->next = old_node;

        old_node->last->next = new_node;

        old_node->last = new_node;
    }

    manager->length += 1;
    return 0;
}


/**
 * @brief             获取字符串链表的内容, 将其写入 disk 中
 * @param string      字符串链表管理器, 即所有节点存储数据类型为字符串数组的链表
 * @param dest        名称写入此
 * @param max_length  disk 的最大长度
 * @return            >0 : 名称长度
 *                    -1 : max_length < 名称长度
 *                    -2 : 获取节点失败
 */
int string_read(ChainTableManager *string, char *dest, int max_length) {
    int length = 0, letter_count = 0, index = 0;
    char *ptr;
    ChainTableNode *node;

    if (chain_table_node_get(string, index++, &node) != 0) {
        return -2;
    }
    ptr = node->ptr;

    while (length < max_length) {
        // dest 未写满
        if (letter_count++ < node->size / sizeof(char)) {
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
            if (chain_table_node_get(string, index++, &node) != 0) {
                *(dest + length) = '\0';
                return length;
            } else {
                ptr = node->ptr;
                continue;
            }
        }
    }
    return -1;
}


/**
 * @brief                向字符串后添加文本
 * @param string         字符串链表管理器
 * @param source         待添加的文本
 * @param source_length  文本长度, 若传入值小于 0, 使用 strlen 函数自动判断长度
 * @param node_length    若需要自动添加节点, 添加的节点长度
 * @return               0  成功
 *                       -1 空间申请失败
 *                       -2 获取节点失败
 *                       -3 长度过大
 */
int string_extend(ChainTableManager *string, const char *source, int64_t source_length, uint16_t node_length) {
    char *ptr = NULL;
    uint16_t letter_count, write_length;
    ChainTableNode *node;

    // 判断值
    if (source_length < 0) {
        // 自动填充字符长度
        source_length = (int64_t) strlen(source);
    }
    if (source_length == 0) {
        // 无需填充
        return 0;
    } else if (source_length < 0) {
        // 说明长度超标
        return -3;
    }

    // ---- 特殊处理 节点不为零的情况, 此时可以填入最后一个节点 ----
    if (string->length > 0) {
        // 节点不为 0, 取最后一个节点, 尝试写入
        if (chain_table_node_get(string, -1, &node) != 0) {
            return -2;
        }
        uint16_t this_node_length = node->size / sizeof(char);
        ptr = (char *) node->ptr;
        if (ptr[this_node_length - 1] == '\0') {
            // 说明未装满, 可以填入此节点
            // NOTE: 因为不写入 \0 故装满时不能用 string 库函数判断长度
            letter_count = strlen(ptr);  // letter_count 是已填入的长度
            write_length = string_extend_min(this_node_length - letter_count, source_length);
            memcpy(ptr + letter_count, source, write_length);

            source += write_length;
            source_length -= write_length;
        } else {
            // 最后一个节点已装满
        }
    }

    while (source_length > 0) {
        if (chain_table_append(string, node_length * sizeof(char), false) != 0) {
            return -1;
        }
        ptr = chain_table_get(string, -1);
//        if (ptr == NULL) {
//            // 想了想, 似乎没必要判断
//            return -2;
//        }
        write_length = string_extend_min(node_length, source_length);
        memcpy(ptr, source, write_length);

        source += write_length;
        source_length -= write_length;
    }

    return 0;
}

/**
 * @brief         返回字符串长度
 * @param string  被处理的字符串
 * @return        > 0 字符串长度
 */
int string_length(const ChainTableManager *string) {
    ChainTableNode *node;
    char *ptr;
    int node_length;
    int total_length = 0;

    for (int i = 0; i < string->length; i++) {
        chain_table_node_get(string, i, &node);
        node_length = (int) (node->size / sizeof(char));
        ptr = node->ptr;
        if (ptr[node_length - 1] != '\0') {
            // 一个满节点
            total_length += node_length;
        } else {
            total_length += (int) strlen(ptr);
        }
    }

    return total_length;
}

/**
 * @brief         获取字符串中指定位置的字符
 * @param string
 * @param index
 * @return        当获取失败时, 返回 \0
 */
char string_char_get(const ChainTableManager *string, int index) {

    int length;
    ChainTableNode *node;

    if (index >= 0) {
        // index 为正, 正序循环
        for (int node_index = 0; node_index < string->length; node_index++) {
            chain_table_node_get(string, node_index, &node);
            if (node == NULL) {
                return '\0';
            }
            length = (int) (node->size / sizeof(char));

            if (index < length) {
                // 找到了节点
                return ((char *) node->ptr)[index];
            } else {
                index -= length;
            }
        }
    } else {
        // index < 0, 反向循环
        node = string->tail;
        while (node != string->head) {
            length = (int) (node->size / sizeof(char));
            index += length;
            if (index >= 0) {
                // 找到了节点
                return ((char *) node->ptr)[index];
            }
            node = node->last;
        }
        length = (int) (node->size / sizeof(char));
        index += length;
        if (index >= 0) {
            // 找到了节点
            return ((char *) node->ptr)[index];
        }
    }
    return '\0';
}

