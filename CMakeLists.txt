cmake_minimum_required(VERSION 3.23)
project(AssessmentPizza)

set(CMAKE_C_STANDARD 99)

include_directories(inc cfg)

set(ChainTable src/chain_table.c)

add_executable(teamwork_week_1 src/password.c)
add_executable(teamwork_week_2 src/chain_table.c test/chain_table_test.c)
add_executable(teamwork_week_3_pizza ${ChainTable} src/pizza.c inc/pizza.h test/pizza_test.c)
