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

typedef struct ChainTableNode {
    void *ptr;
    size_t size;

    struct ChainTableNode *last;
    struct ChainTableNode *next;
} ChainTableNode;

typedef struct {
    uint16_t length;

    ChainTableNode * head;
    ChainTableNode * tail;
} ChainTableManager;

int chain_table_creat(ChainTableManager * ctm);

int chain_table_clear(ChainTableManager * ctm);

int chain_table_remove(ChainTableManager * ctm, int index);

int chain_table_node_get(ChainTableManager * ctm, int index, ChainTableNode ** node);

void * chain_table_get(ChainTableManager * ctm, int index);

int chain_table_append(ChainTableManager * ctm, size_t element_size);

int chain_table_insert(ChainTableManager * ctm, size_t element_size, int index);

#endif //ASSESSMENT_PIZZA_CHAIN_TABLE_H
