/**
  **************************** AssessmentPizza: yaml_subset.h ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      实现 yaml 的子集读写
  **************************** AssessmentPizza: yaml_subset.h ****************************
 */

#ifndef ASSESSMENT_PIZZA_YAML_SUBSET_H
#define ASSESSMENT_PIZZA_YAML_SUBSET_H

#include "chain_table.h"


typedef enum {
    YAML_NULL = 0,  // data -> NULL                    , data2 -> NULL
    YAML_INT,       // data -> int32                   , data2 -> Yaml or NULL
    YAML_DOUBLE,    // data -> double                  , data2 -> Yaml or NULL
    YAML_STRING,    // data -> ChainTableManager (char), data2 -> Yaml or NULL
    YAML_LIST,      // data -> ChainTableManager (Yaml), data2 -> Yaml or NULL
} YAML_NODE_DATA_TYPE;

typedef struct {
    void *data;
    void *data2;
    YAML_NODE_DATA_TYPE data_type;
} Yaml;


int read_ascii_file_lines(char *path, ChainTableManager *manager);

int yaml_subset_read(const char *path, Yaml *yaml);

void yaml_subset_free(Yaml *yaml);

#endif //ASSESSMENT_PIZZA_YAML_SUBSET_H
