/**
  **************************** AssessmentPizza: user_interface_test.c ****************************
  * Created by oh-it-works on 2022/12/8.
  * @file
  * @author     oh it works
  * @date       2022-12-08
  * @brief      UI tools tested here.
  **************************** AssessmentPizza: user_interface_test.c ****************************
 */

#include "customer.h"
#include "user_interface.h"
#include "user_interface_tools.h"


int main() {
    char userid[PASSWORD_LENGTH_MAX * 2];
    int key;


    switch (ui_choose_role()) {
        case 0:
        default:
            return 0;
        case 1:
            screen_clear();
            userid[PASSWORD_LENGTH_MAX] = '\0';
            ui_customer_register(userid);
            break;
        case 2:
            screen_clear();
            if (ui_login_page(userid) != 0) {
                return 0;
            }
            break;
        case 3:
            ui_manager_login();
            do {
                key = ui_manager_main();
                ui_manage_functions(key);
            } while (key);
            return 0;
    }

    do {
        key = ui_customer_main(userid);
        ui_customer_functions(key, userid);
    } while (key);


    return 0;
}
