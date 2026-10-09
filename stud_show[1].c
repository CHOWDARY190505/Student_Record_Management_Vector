#include "stud.h"

void stud_show(void)
{
    Student *current = head;

    if (current == NULL) {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n---------------------------------------------------------------\n");
    printf("%-10s %-30s %12s\n", "Roll No", "Name", "Percentage");
    printf("---------------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-10d %-30s %11.2f%%\n",
               current->roll, current->name, current->percentage);
        current = current->next;
    }

    printf("---------------------------------------------------------------\n");
}
