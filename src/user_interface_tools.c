/**
  **************************** AssessmentPizza: user_interface_tools.c ****************************
  * Created by oh-it-works on 2022/12/18.
  * @file
  * @author     oh it works
  * @date       2022-12-18
  * @brief      图形界面操作 Graphical interface Operation
  **************************** AssessmentPizza: user_interface_tools.c ****************************
 */

#include "user_interface_tools.h"

#include <stdio.h>
#include <stdlib.h>

/**
* @brief           Ask the user for choose from parameter `chooses`.
* @param chooses   Char array for choose.
* @param size      Size of param `chooses`.
* @param mode      0 for only ask once time, return -1 if user input an not exist value.
*                  1 for ask until user input an exist value.
* @return          Return the index for the selected chooses.
*                  -1 will be returned if user input an not exist value.
*                  -2 will be returned if unexpect mode got.
*/
int ui_multiple_choice(char *chooses, size_t size, int mode) {
    int i;
    char input_char;

    while (1) {
        // Working loo.

        // ------  Print options.  ------
        printf("[");
        for (i = 0; i < size - 1; i++) {
            printf("%c | ", chooses[i]);
        }
        printf("%c] :", chooses[i]);

        // ------  Get input.  ------
        scanf("\n%c", &input_char);

        // ------ check input  ------
        for (i = 0; i < size; i++) {
            if (chooses[i] == input_char) {
                return i;
            }
        }
        // Unexpected input got.
        if (mode == 0) {
            // Return error code.
            return -1;
        }
        else if (mode == 1) {
            // Print notice and keep ask.
            printf("Unexpected input :%c\n", input_char);
        }
        else {
            // Unexpected mode. Return error code.
            return -2;
        }
    }
}


/**
* @brief  Clear the screen.
*/
void screen_clear(void) {
    system("cls");
    fflush(stdin);
}
