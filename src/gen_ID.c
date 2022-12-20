/**
  **************************** AssessmentPizza: gen_ID.c ****************************
  * Created by Miiiaao on 15/12/2022.
  *
  * @file       gen_ID.c
  * @brief      
  * @note       
  **************************** AssessmentPizza: gen_ID.c ****************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "gen_ID.h"
#include "chain_table.h"
#include "file_io.h"

char gen_id(char ID[ACCOUNT_LENGTH_MAX]){
    int success_gen_id = 0, i;
    ChainTableManager string_id, lines;
    ChainTableManager *sub_string_id, *string;
    char *str, *buffer;

    chain_table_init(&string_id);
    chain_table_append(&string_id, sizeof(char) * 16, 1);

    sub_string_id = chain_table_get(&string_id, 0);
    chain_table_init(&sub_string_id);
    chain_table_append(&sub_string_id, sizeof(char) *16, 0);

    read_ascii_file_lines(ACCOUNT_FILE_PATH, &lines);

    while (success_gen_id == 0){
        gen_random_string(str);

        for (i = 0; i < lines.length - 1; i++){
            memset(buffer, 0 , strlen(buffer));
            string = chain_table_get(&lines, i);
            string_read(string, buffer, );
            printf("line[%2d]: %s\n", i + 1, buffer);

            if (strcmp(buffer, str) == 0){
                continue;
            }
        }

        chain_table_node_get(&lines, 0, )

        write_lines_to_file(ACCOUNT_FILE_PATH, &lines);

        for (i = 0; i <= ACCOUNT_LENGTH_MAX; i++){
            ID[i] = str[i];
        }

//    printf("%s\n", ID);
        success_gen_id = 1;
    }


    return ID[ACCOUNT_LENGTH_MAX];
}

void gen_random_string(char * dest){
    const unsigned char allchar[63] = "0123456789abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int i, randNo;
    unsigned char str[ACCOUNT_LENGTH_MAX + 1] = { };

    srand((unsigned int)time(NULL));

    for (i = 0; i < ACCOUNT_LENGTH_MAX; i++){
        randNo = rand() % 62;
        *dest = allchar[randNo];
        dest++;
    }

    *dest = '\0';
}