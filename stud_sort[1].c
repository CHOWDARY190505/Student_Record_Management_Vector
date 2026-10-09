#include "stud.h"
#include <string.h>

static void swap_data(Student *a, Student *b)
{
    int roll_temp = a->roll;
    float percentage_temp = a->percentage;
    char name_temp[NAME_LEN];

    strcpy(name_temp, a->name);

    a->roll = b->roll;
    a->percentage = b->percentage;
    strcpy(a->name, b->name);

    b->roll = roll_temp;
    b->percentage = percentage_temp;
    strcpy(b->name, name_temp);
}

void stud_sort(void)
{
    char choice;
    Student *i;
    Student *j;

    if (head == NULL || head->next == NULL) {
        printf("Not enough records to sort.\n");
        return;
    }

    printf("\nN/n : Sort by Name\n");
    printf("P/p : Sort by Percentage\n");
    choice = read_choice("Enter your choice: ");

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            int should_swap = 0;

            if (choice == 'n' && strcmp(i->name, j->name) > 0) {
                should_swap = 1;
            } else if (choice == 'p' && i->percentage > j->percentage) {
                should_swap = 1;
            }

            if (should_swap) {
                swap_data(i, j);
            }
        }
    }

    if (choice == 'n') {
        printf("Records sorted by name in ascending order.\n");
    } else if (choice == 'p') {
        printf("Records sorted by percentage in ascending order.\n");
    } else {
        printf("Invalid sorting choice.\n");
    }
}
