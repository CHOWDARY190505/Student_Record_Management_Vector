#include "stud.h"
#include <stdlib.h>
#include <string.h>

void stud_add(void)
{
    Student *node;
    Student *current;
    char name[NAME_LEN];
    float percentage;
    size_t i;

    read_line("Enter student name: ", name, sizeof(name));

    if (name[0] == '\0') {
        printf("Name cannot be empty. Record not added.\n");
        return;
    }

    /* The file format uses | as a separator, so do not allow it in names. */
    for (i = 0; name[i] != '\0'; i++) {
        if (name[i] == '|') {
            printf("The character '|' is not allowed in a name.\n");
            return;
        }
    }

    do {
        percentage = read_float("Enter percentage (0 to 100): ");
        if (percentage < 0.0f || percentage > 100.0f) {
            printf("Percentage must be between 0 and 100.\n");
        }
    } while (percentage < 0.0f || percentage > 100.0f);

    node = (Student *)malloc(sizeof(Student));
    if (node == NULL) {
        printf("Memory allocation failed. Record not added.\n");
        return;
    }

    node->roll = smallest_available_roll();
    strcpy(node->name, name);
    node->percentage = percentage;
    node->next = NULL;

    if (head == NULL) {
        head = node;
    } else {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }

    printf("Record added successfully. Assigned roll number: %d\n", node->roll);
}
