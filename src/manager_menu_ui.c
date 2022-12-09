//
// Created by chen yuzhuo on 2022/12/9.
//
/**
  **************************** AssessmentUI: manager_ui.c ****************************
  * Created by thomas on 2022/12/9.
  * @file
  * @author     Thomas
  * @date       2022-12-09
  * @brief      The UI for manager
  **************************** AssessmentUI: manager_ui.c ****************************
 */

#include <stdio.h>
#include <synchapi.h>
#include "manager_menu_ui.h"

/**
 * @brief 菜单1：如果有额外登陆通道的话
 */
void manager_menu_login()
{
    int menu_flag = 0;
    printf("\t1. Login\n\n");
    printf("\t2. Register\n\n");
    printf("\t3. Exit\n\n");
    scanf("%d",&menu_flag);
    switch (menu_flag) {
        case 1:
            ////登录
            manager_menu_function();
                    ;break;
        case 2:
        ////注册
        manager_menu_login();
            ;break;
        case 3:
            printf("Exit successfully");
            ;break;
    }
    ////如果登录分员工通道和客户通道
    ////TODO:1.登录和注册的后续程序 2.位置 or 边框可能需调整统一 3.输入控制
}

//根据题目需求，设计交互界面，需要写出大体上的字符串样式，各个选项文本和对应功能，最好有设计报告。
//经理编辑菜单以及用户信息界面.
/**
 * @brief 菜单2：各种功能
 */
void manager_menu_function()
{
    int menu_flag = 0;
    printf("\t1.Edit the pizza menu.\n\n");
    printf("\t2.Check or edit the customer's information.\n\n");
    printf("\t3.Check the sales of each pizza.\n\n");
    scanf("%d",&menu_flag);
    switch (menu_flag){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
    ////TODO: 1.输入控制 2.各功能接口
}

//下方是功能UI有待考虑
/**
 * @brief 菜单3：修改菜单
 */
/*void manager_menu_pizza()
{
    int menu_flag = 0;
    printf("\tHere are different kinds of pizza\n\n");
    printf("\t1.Edit the pizza's name.\n\n");
    printf("\t2.Edit the pizza's price.\n\n");
    printf("\t3.Return to upper level.\n\n");
    scanf("%d",&menu_flag);
    switch (menu_flag){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
    ////TODO: 1.输入控制 2.各功能接口
}*/


