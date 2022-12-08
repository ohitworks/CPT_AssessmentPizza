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


int chain_table_node_create(ChainTableNode **node, size_t size);

int chain_table_node_free(ChainTableNode *ctn);


/**
 * @brief       释放一个节点指向的空间
 * @param node  节点指针
 * @return      0 表示成功
 *              -1 获取内存失败
 *              -2 表示节点已被释放, 不做修改
 */
int chain_table_node_free(ChainTableNode *ctn) {
    ChainTableNode *next, *last;

    if (ctn->ptr == NULL) {
        return -2;
    }

    next = ctn->next;
    last = ctn->last;

    free(ctn->ptr);
    ctn->ptr = NULL;

    if (next != NULL) {
        next->last = last;
    }

    if (last != NULL) {
        last->next = next;
    }

    return 0;
}


/**
 * @brief      初始化一个链表管理器
 * @param ctm  链表管理器
 * @return     始终返回 0
 */
int chain_table_init(ChainTableManager *ctm) {
    memset(ctm, 0, sizeof(ChainTableManager));
    return 0;
}

/**
 * @brief      清空链表管理器的所有链表
 * @param ctm  待清空的链表管理器
 * @return     始终返回 0
 */
int chain_table_clear(ChainTableManager *ctm) {
    int ret = 0;

    ChainTableNode *ptr = ctm->tail->last;
    ChainTableNode *to_del = ctm->tail;

    while (ptr != NULL) {
        free(to_del);
        ptr = ptr->last;
        to_del = ptr;
    }
    free(to_del);

    memset(ctm, 0, sizeof(ChainTableManager));

    return ret;
}


/**
 * @brief        删除链表的 index 号节点
 * @param ctm    链表管理器
 * @param index  index 号链表节点, 若获取失败也可能修改
 * @return       0 表示成功
 *               -1 表示 index 不存在
 *               -2 表示链表有问题
 */
int chain_table_remove(ChainTableManager *ctm, int index) {
    ChainTableNode *to_del = ctm->tail;

    // 长度判断
    if (ctm->length <= 0) {
        // 传入空链表
        return -1;
    }
    // 处理 index < 0 情况
    if (index < 0) {
        index += ctm->length;
    }
    // 输入判断
    if (index >= ctm->length or index < 0) {
        return -1;
    }

    // 指定 to_del, 修改前后链表指针
    if (index == 0) {
        // 删除第一个
        to_del = ctm->head;
        ctm->head = to_del->next;
        if (ctm->tail == to_del) {
            ctm->tail = NULL;
        }
    } else if (index == ctm->length - 1) {
        // 删除末尾
        to_del = ctm->tail;
        ctm->tail = to_del->last;
        if (ctm->head == to_del) {
            ctm->head = NULL;
        }
    } else {
        if (chain_table_node_get(ctm, index, &to_del) != 0) {
            return -2;
        }
        to_del->last->next = to_del->next;
        to_del->next->last = to_del->last;
    }

    // 执行删除
    free(to_del);
    ctm->length -= 1;
    return 0;
}

/**
 * @brief        获取 index 号链表节点
 * @param ctm    链表管理器
 * @param index  索引, 0 代表第一个, 随链表向后依次递增; -1代表最后一个, 随链表向前依次递减
 * @param node   index 号链表节点, 若获取失败也可能修改
 * @return       0 表示成功
 *               -1 表示索引不合理
 *               -2 表示迭代时出现异常
 * @note         无论输入索引为多少, 程序由前向后查找元素
 * @warning      不应在链表管理器之外调用
 */
int chain_table_node_get(ChainTableManager *ctm, int index, ChainTableNode **node) {
    // 处理 index < 0 情况
    if (index < 0) {
        index += ctm->length;
    }
    // 输入判断
    if (index >= ctm->length or index < 0) {
        return -1;
    }

    *node = ctm->head;
    for (int i = 0; i < index; i++) {
        *node = (*node)->next;
        if ((*node) == NULL) {
            return -2;
        }
    }
    return 0;
}

/**
 * @brief        获取链表管理器 index 号元素对应内容的指针
 * @param ctm    链表管理器
 * @param index  索引, 0 代表第一个, 随链表向后依次递增; -1代表最后一个, 随链表向前依次递减
 * @return       获取失败返回 NULL, 成功返回指定元素对应内容的指针
 * @warning      不要试图释放指针空间
 */
void *chain_table_get(ChainTableManager *ctm, int index) {
    ChainTableNode *node = NULL;
    if (chain_table_node_get(ctm, index, &node) != 0) {
        return NULL;
    }
    return node->ptr;
}

/**
 * @brief       创建一个节点
 * @param node  节点指针
 * @param size  节点对应的元素空间
 * @return      0 表示成功
 *              -1 获取内存失败
 * @note        事实上程序没有为节点的元素分配单独的空间, 而是在创建节点时一次性分配其所有空间,
 *              有 node == node->ptr + sizeof(ChainTableNode)
 */
int chain_table_node_create(ChainTableNode **node, size_t size) {

    *node = malloc(size + sizeof(ChainTableNode));
    if (*node == NULL) {
        return -1;
    }
    memset(*node, 0, size + sizeof(ChainTableNode));

    (*node)->size = size;
    (*node)->ptr = (*node) + 1;
    return 0;
}

/**
 *@brief                向链表后添加一个节点
 * @param ctm           链表管理器
 * @param element_size  新节点的元素大小
 * @return              0 成功
 *                      -1 内存分配失败
 */
int chain_table_append(ChainTableManager *ctm, size_t element_size) {
    ChainTableNode *new_node = NULL;

    chain_table_node_create(&new_node, element_size);
    if (new_node == NULL) {
        return -1;
    }

    if (ctm->tail != NULL) {
        ctm->tail->next = new_node;
    }
    new_node->last = ctm->tail;
    ctm->tail = new_node;
    if (ctm->length == 0) {
        ctm->head = new_node;
    }

    ctm->length += 1;
    return 0;
}

/**
 *@brief                向链表插入一个节点, 新节点的索引为 index
 * @param ctm           链表管理器
 * @param element_size  新节点的元素大小
 * @param index         新节点的索引; 0 代表第一个, 随链表向后依次递增; -1代表最后一个, 随链表向前依次递减
 * @return              0 成功
 *                      -1 内存分配失败
 *                      -2 索引错误
 *                      -3 意外错误
 */
int chain_table_insert(ChainTableManager *ctm, size_t element_size, int index) {
    ChainTableNode *new_node = NULL;
    ChainTableNode *old_node = NULL;

    // 处理 index < 0 情况
    if (index < 0) {
        index += ctm->length;
    }
    // 输入判断
    if (index > ctm->length or index < 0) {
        return -2;
    }

    // 创建并插入节点
    chain_table_node_create(&new_node, element_size);
    if (new_node == NULL) {
        return -1;
    }
    if (index == ctm->length) {
        if (ctm->tail != NULL) {
            ctm->tail->next = new_node;
        }
        new_node->last = ctm->tail;
        ctm->tail = new_node;
    } else if (index == 0) {
        if (ctm->head != NULL) {
            ctm->head->last = new_node;
        }
        new_node->next = ctm->head;
        ctm->head = new_node;
    } else {
        if (chain_table_node_get(ctm, index, &old_node) != 0) {
            return -3;
        }

        // 修改节点联系
        new_node->last = old_node->last;
        new_node->next = old_node;

        old_node->last->next = new_node;

        old_node->last = new_node;
    }

    ctm->length += 1;
    return 0;
}
