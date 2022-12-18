cmake_minimum_required(VERSION 3.21)
project(AssessmentPizza)

set(CMAKE_C_STANDARD 99)

include_directories(inc cfg)

set(ChainTable src/chain_table.c)
set(FileIO ${ChainTable} src/file_io.c)
set(Menu ${FileIO} src/menu.c)
set(Pizza ${FileIO} src/pizza.c)

add_executable(teamwork_week_1 ${FileIO}
                               src/password.c src/gen_ID.c inc/gen_ID.h)

add_executable(teamwork_week_2 src/chain_table.c test/chain_table_test.c)

add_executable(teamwork_week_3_pizza ${ChainTable} ${FileIO}
                                     src/pizza.c inc/pizza.h test/pizza_test.c)

add_executable(teamwork_week_3_yaml ${ChainTable}
                                    src/yaml_subset.c inc/pizza.h test/yaml_subset_test.c test/yaml_subset_test.c)

add_executable(teamwork_week_4_file ${ChainTable}
                                    src/file_io.c test/file_io_test.c)

add_executable(teamwork_week_4_menu ${ChainTable} ${FileIO}
                                    src/menu.c test/menu_test.c)

add_executable(teamwork_week_4_ui ${Menu} ${Pizza}
                                  src/user_interface_tools.c test/user_interface_test.c
                                  src/user_interface.c)
