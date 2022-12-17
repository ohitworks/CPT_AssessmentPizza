/**
  **************************** AssessmentPizza: yaml_subset_test.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      测试 yaml 子集的读写
  **************************** AssessmentPizza: yaml_subset_test.c ****************************
 */

#include "file_io.h"
#include "yaml_subset.h"

#include <stdio.h>
#include <string.h>


int main(void) {
    ChainTableManager lines;
    ChainTableManager *string;
    char buffer[128];

    read_ascii_file_lines("import this.txt", &lines);

    for (int i = 0; i < lines.length - 1; i++) {
        memset(buffer, 0, sizeof(buffer));
        string = chain_table_get(&lines, i);
        string_read(string, buffer, 128);
        printf("line[%2d]: %s\n", i + 1, buffer);
    }

    for (int i = 1; i < 10; i++) {
        printf("%d: %c\n", i-1, string_char_get(string, i-1));
        printf("%d: %c\n", -i, string_char_get(string, -i));
    }

    printf("%d: %c\n", 63, string_char_get(string, 63));

//    printf("%llu\n", strlen("12345"));
//    printf("%d\n", (int) UINT32_MAX);
    chain_table_clear(&lines, FREE_AS_MANAGER);
    return 0;
}
