/**
  **************************** AssessmentPizza: yaml_subset_test.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      测试 yaml 子集的读写  **************************** AssessmentPizza: yaml_subset_test.c ****************************
 */

#include "yaml_subset.h"

#include <stdio.h>
#include <string.h>


int main(void) {
    ChainTableManager lines;
    ChainTableManager * string;
    char buffer[128];

    read_ascii_file_lines("hello.txt", &lines);


    for (int i=0; i<lines.length; i++) {
        memset(buffer, 0, sizeof(buffer));
        string = chain_table_get(&lines, i);
        string_read(string, buffer, 128);
        printf("line[%2d]: %s\n", i+1, buffer);
    }

    chain_table_clear(&lines, FREE_AS_MANAGER);

//    printf("%llu\n", strlen("12345"));
//    printf("%d\n", (int) UINT32_MAX);
}
