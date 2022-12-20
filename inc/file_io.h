/**
  **************************** AssessmentPizza: file_io.h ****************************
  * Created by oh-it-works on 2022/12/17.
  * @file
  * @author     oh it works
  * @date       2022-12-17
  * @brief      文件读写
  **************************** AssessmentPizza: file_io.h ****************************
 */

#ifndef ASSESSMENT_PIZZA_FILE_IO_H
#define ASSESSMENT_PIZZA_FILE_IO_H

#include "chain_table.h"

int read_ascii_file_lines(const char *path, ChainTableManager *string_array);

int write_lines_to_file(const ChainTableManager *string_array, const char *file_name);

int write_bin(char *file_path, const void *obj, size_t obj_size);

int read_bin(char *file_path, void *obj, size_t obj_size);

bool file_is_exist(char * file_name);

int write_lines_to_file_with_mode(const ChainTableManager *string_array, const char *file_name, const char *mode);

#endif //ASSESSMENT_PIZZA_FILE_IO_H
