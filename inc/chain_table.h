/**
  **************************** AssessmentPizza: chain_table.h ****************************
  * Created by Juntong on 2022/12/2.
  * @file
  * @author     oh it works
  * @date       2022-12-02
  * @brief      **BriefHere**
  **************************** AssessmentPizza: chain_table.h ****************************
 */

#ifndef ASSESSMENT_PIZZA_CHAIN_TABLE_H
#define ASSESSMENT_PIZZA_CHAIN_TABLE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef enum {
    RETURN_IF_DYNAMIC,     // 如果动态则直接返回错误码
    FREE_AS_MANAGER,  // 如果其大小等于 sizeof(ChainTableManager) 将其当作链表管理器释放
} ChainTableFreeModes;

typedef struct ChainTableNode {
    void *ptr;
    size_t size;
    bool is_dynamic;

    struct ChainTableNode *last;
    struct ChainTableNode *next;
} ChainTableNode;

typedef struct {
    uint16_t length;

    ChainTableNode *head;
    ChainTableNode *tail;
} ChainTableManager;

int chain_table_init(ChainTableManager *manager);

int chain_table_clear(ChainTableManager *manager, ChainTableFreeModes mode);

int chain_table_remove(ChainTableManager *manager, ChainTableFreeModes mode, int index);

int chain_table_node_get(const ChainTableManager *manager, int index, ChainTableNode **node);

void *chain_table_get(const ChainTableManager *manager, int index);

int chain_table_append(ChainTableManager *manager, size_t element_size, bool is_dynamic);

int chain_table_insert(ChainTableManager *manager, size_t element_size, bool is_dynamic, int index);

int string_read(const ChainTableManager *string, char *dest, int max_length);

int string_read_with_start(const ChainTableManager *string, char *dest, int max_length, int read_start);

int string_extend(ChainTableManager *string, const char *source, int64_t source_length, uint16_t node_length);

int string_extend_string(ChainTableManager *string, const ChainTableManager *source);

int string_char_get_with_error_code(const ChainTableManager *string, char * c, int index);

char string_char_get(const ChainTableManager *string, int index);

int string_length(const ChainTableManager *string);

bool string_equal(const ChainTableManager *a, const ChainTableManager *b);

#endif //ASSESSMENT_PIZZA_CHAIN_TABLE_H
