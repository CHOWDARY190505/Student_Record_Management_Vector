#include "stud.h"
#include <string.h>
#include <stdlib.h>

static void print_matches_by_name(const char *name)
{
    Student *current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Roll: %d | Name: %s | Percentage: %.2f\n",
                   current->roll, current->name, current->percentage);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No record found with that name.\n");
    }
}

static int delete_roll(int roll)
{
    Student *current = head;
    Student *previous = NULL;

    while (current != NULL) {
        if (current->roll == roll) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Record with roll number %d deleted.\n", roll);
            return 1;
        }
        previous = current;
        current = current->next;
    }

    printf("Roll number %d not found.\n", roll);
    return 0;
}

void stud_del(void)
{
    char choice;
    char name[NAME_LEN];
    int roll;

    if (head == NULL) {
        printf("No records to delete.\n");
        return;
    }

    printf("\nR/r : Delete using Roll Number\n");
    printf("N/n : Delete using Name\n");
    choice = read_choice("Enter your choice: ");

    if (choice == 'r') {
        roll = read_int("Enter roll number to delete: ");
        delete_roll(roll);
    } else if (choice == 'n') {
        read_line("Enter exact student name: ", name, sizeof(name));
        print_matches_by_name(name);

        if (strcmp(name, "") != 0) {
            roll = read_int("Enter the roll number to delete (0 to cancel): ");
            if (roll != 0) {
                delete_roll(roll);
            } else {
                printf("Deletion cancelled.\n");
            }
        }
    } else {
        printf("Invalid choice.\n");
    }
}
