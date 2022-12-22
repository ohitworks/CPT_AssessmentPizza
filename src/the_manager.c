/**
  **************************** AssessmentPizza: the_manager.c ****************************
  * Created by oh it works on 2022/12/21.
  * @file
  * @author     oh it works
  * @date       2022-12-21
  * @brief      The restaurant manager.
  **************************** AssessmentPizza: the_manager.c ****************************
 */

#include "customer.h"
#include "the_manager.h"
#include "chain_table.h"

/**
 *
 * @param password
 * @return          0 登陆成功
 */
int manager_login(char * password) {
    int ret;
    ChainTableManager name;

    ret = account_login("Superuser", password);

    if (ret == -1) {
        chain_table_init(&name);
        string_extend(&name, "su", -1, 12);
        account_register("Superuser", SUPERUSER_DEFINE_PASSWORD, &name);

        ret = account_login("Superuser", password);
    }
    return ret;
}

