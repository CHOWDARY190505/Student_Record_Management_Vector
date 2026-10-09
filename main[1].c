#include "stud.h"
#include <stdio.h>

int main(void)
{
    char choice;

    stud_load();

    for (;;) {
        printf("\n**** STUDENT RECORD MENU ****\n");
        printf("A/a : Add New Record\n");
        printf("D/d : Delete a Record\n");
        printf("S/s : Show the List\n");
        printf("M/m : Modify a Record\n");
        printf("V/v : Save\n");
        printf("T/t : Sort the List\n");
        printf("E/e : Exit\n");

        choice = read_choice("Enter Your Choice: ");

        switch (choice) {
            case 'a':
                stud_add();
                break;
            case 'd':
                stud_del();
                break;
            case 's':
                stud_show();
                break;
            case 'm':
                stud_mod();
                break;
            case 'v':
                stud_save();
                break;
            case 't':
                stud_sort();
                break;
            case 'e': {
                char exit_choice;
                printf("\nS/s : Save and Exit\n");
                printf("E/e : Exit Without Saving\n");
                exit_choice = read_choice("Enter Your Choice: ");

                if (exit_choice == 's') {
                    stud_save();
                    free_list();
                    return 0;
                } else if (exit_choice == 'e') {
                    free_list();
                    printf("Exiting without saving current changes.\n");
                    return 0;
                } else {
                    printf("Invalid choice. Returning to main menu.\n");
                }
                break;
            }
            default:
                printf("Invalid choice. Please select A, D, S, M, V, T, or E.\n");
        }
    }
}
