/**
  **************************** AssessmentPizza: menu_test.c ****************************
  * Created by oh-it-works on 2022/12/17.
  * @file
  * @author     oh it works
  * @date       2022-12-17
  * @brief      测试菜单
  **************************** AssessmentPizza: menu_test.c ****************************
 */

#include "menu.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    MenuPizza mp1 = {"Type 1", 10, 100};
    MenuPizza mp2 = {"Type 1", 15, 140};

    ChainTableManager mps;
    MenuPizza *mp;

    // save
    chain_table_init(&mps);

    chain_table_append(&mps, sizeof(MenuPizza), false);
    memcpy(chain_table_get(&mps, -1), &mp1, sizeof(MenuPizza));

    chain_table_append(&mps, sizeof(MenuPizza), false);
    memcpy(chain_table_get(&mps, -1), &mp2, sizeof(MenuPizza));

    menu_save_to_file_no_update(&mps, "menu.cfg");

    // clear
    chain_table_clear(&mps, RETURN_IF_DYNAMIC);

    // load
    menu_load_from_file(&mps, "menu.cfg");
    for (int i=0; i < mps.length; i++) {
        mp = chain_table_get(&mps, i);
        printf("Menu [%2d]: type [%s], size [%d], price [%d]\n",
               i, mp->pizza_type, mp->pizza_size, mp->pizza_price);
    }


    chain_table_clear(&mps, RETURN_IF_DYNAMIC);
    return 0;
}
