/**
  **************************** AssessmentPizza: chain_table_test.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      Test the chain table.
  **************************** AssessmentPizza: chain_table_test.c ****************************
 */

#include <stdio.h>
#include <string.h>

#include "chain_table.h"


int main(void) {
    ChainTableManager manager, string, string_2;
    ChainTableManager *sub;
    int c = 0;
    char buffer[128] = {0};
    char *ptr;

    chain_table_init(&manager);

    chain_table_append(&manager, sizeof(char) * 16, 0);
    chain_table_append(&manager, sizeof(char) * 16, 0);

    ptr = (char *) chain_table_get(&manager, 0);
    for (int i = 0; i < 13; i++, c++) {
        *(ptr + i) = (char) ('a' + c);
    }


    ptr = (char *) chain_table_get(&manager, 1);
    for (int i = 0; i < 13; i++, c++) {
        *(ptr + i) = (char) ('a' + c);
    }

    chain_table_insert(&manager, sizeof(char) * 11, 0, 1);
    ptr = (char *) chain_table_get(&manager, 1);
    c = 0;
    for (int i = 0; i < 10; i++, c++) {
        *(ptr + i) = (char) ('0' + c);
    }


    printf("numbers: %s\n",
           (char *) chain_table_get(&manager, 1));

    chain_table_remove(&manager, RETURN_IF_DYNAMIC, 1);

    printf("%s %s\n",
           (char *) chain_table_get(&manager, 0),
           (char *) chain_table_get(&manager, 1));

    chain_table_clear(&manager, FREE_AS_MANAGER);

//    while (true) {
//        printf("a        : add a string\n");
//        printf("b[a-z][.]: add the text letter on the string\n");
//        printf("c[a-z]   : add the text letter on the string\n");
//        switch (getchar()) {
//            case 'a':
//                // add a string
//                chain_table_append(&manager, sizeof(ChainTableManager), true);
//                sub = chain_table_get(&manager, 0);
//                chain_table_init(sub);
//                chain_table_append(sub, 16, false);
//                printf("string added\n");
//            case '\n':
//                continue;
//            case 'b':
//                sub = chain_table_get(&manager, 0);
//                if (sub == NULL) {
//                    printf("-- Index Error --\n");
//                    getchar();
//                    continue;
//                }
//                ptr = chain_table_get(sub, 0);
//                printf("%s\n", ptr);
//                if (strlen(ptr) < 16) {
//                    ptr[strlen(ptr)] = (char) getchar();
//                } else {
//                    getchar();
//                    printf("-- do nothing --\n");
//                }
//            case 'c':
//                sub = chain_table_get(&manager, getchar() - 'a');
//                if (sub == NULL) {
//                    printf("-- Index Error --\n");
//                    getchar();
//                    continue;
//                }
//                chain_table_append(sub, sizeof(ChainTableManager), false);
//                printf("added\n");
//            default:
//                break;
//            case 'q':
//                return 0;
//        }
//    }

    chain_table_clear(&manager, FREE_AS_MANAGER);

    // ---- string ----
    chain_table_init(&string);

    string_extend(&string, "Hello Ivy. Glad to meet you!", -1, 8);
    string_read(&string, buffer, 128);
    printf("%s\n", buffer);

    string_extend(&string, "\nLet's go dinner, will you?", -1, 20);
    string_read(&string, buffer, 128);
    printf("%s\n", buffer);

    // ---- test string_read_with_start ----
    memset(buffer, 0, 128);
    string_read_with_start(&string, buffer, 128, 29);
    printf("--\n%s\n--\n", buffer);

    // ---- string compare ----
    chain_table_init(&string_2);
    string_extend(&string_2, "Hello Ivy. Glad to meet you!\nLet's go dinner, will you?", -1, 8);
    memset(buffer, 0, 128);
    string_read_with_start(&string, buffer, 128, 0);
    printf("string_2: \n%s\n", buffer);

    printf("---\ncmp: %d\n---\n", string_equal(&string, &string_2));

    // ---- Test string_extend_string. ----
//    chain_table_clear(&string, RETURN_IF_DYNAMIC);
    chain_table_clear(&string_2, RETURN_IF_DYNAMIC);
    string_extend(&string_2, "String 2:", -1, 8);

    string_extend_string(&string_2, &string);

    memset(buffer, 0, 128);
    string_read_with_start(&string_2, buffer, 128, 0);
    printf("---\n%s\n---\n", buffer);

    // ---- Try clear. ----
    chain_table_append(&manager, sizeof(char) * 10, false);
    memcpy(chain_table_get(&manager, 0), "ABC", 3);

    chain_table_append(&manager, sizeof(ChainTableManager), true);
    memcpy(chain_table_get(&manager, 1), &string, sizeof(ChainTableManager));
//    printf("%d\n", chain_table_clear(&string, RETURN_IF_DYNAMIC));
    printf("Clear+FREE_AS_MANAGER: %d\n", chain_table_clear(&manager, FREE_AS_MANAGER));
    chain_table_init(&string);

    return 0;
}
