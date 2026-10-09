#include "stud.h"
#include <string.h>

static void show_matches_by_name(const char *name)
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
        printf("No matching name found.\n");
    }
}

static void show_matches_by_percentage(float percentage)
{
    Student *current = head;
    int found = 0;

    while (current != NULL) {
        if (current->percentage == percentage) {
            printf("Roll: %d | Name: %s | Percentage: %.2f\n",
                   current->roll, current->name, current->percentage);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("No matching percentage found.\n");
    }
}

void stud_mod(void)
{
    char search_choice;
    char field_choice;
    char name[NAME_LEN];
    int roll;
    float percentage;
    Student *student = NULL;

    if (head == NULL) {
        printf("No records to modify.\n");
        return;
    }

    printf("\nSearch Record:\n");
    printf("R/r : Roll Number\n");
    printf("N/n : Name\n");
    printf("P/p : Percentage\n");
    search_choice = read_choice("Enter your choice: ");

    if (search_choice == 'r') {
        roll = read_int("Enter roll number: ");
        student = find_by_roll(roll);
        if (student == NULL) {
            printf("Roll number not found.\n");
            return;
        }
    } else if (search_choice == 'n') {
        read_line("Enter exact student name: ", name, sizeof(name));
        show_matches_by_name(name);
        roll = read_int("Enter roll number of the record to modify (0 to cancel): ");
        if (roll == 0) {
            printf("Modification cancelled.\n");
            return;
        }
        student = find_by_roll(roll);
        if (student == NULL || strcmp(student->name, name) != 0) {
            printf("That roll number does not match the searched name.\n");
            return;
        }
    } else if (search_choice == 'p') {
        percentage = read_float("Enter exact percentage: ");
        show_matches_by_percentage(percentage);
        roll = read_int("Enter roll number of the record to modify (0 to cancel): ");
        if (roll == 0) {
            printf("Modification cancelled.\n");
            return;
        }
        student = find_by_roll(roll);
        if (student == NULL || student->percentage != percentage) {
            printf("That roll number does not match the searched percentage.\n");
            return;
        }
    } else {
        printf("Invalid search choice.\n");
        return;
    }

    printf("\nModify Field:\n");
    printf("N/n : Name\n");
    printf("P/p : Percentage\n");
    field_choice = read_choice("Enter your choice: ");

    if (field_choice == 'n') {
        size_t i;
        read_line("Enter new name: ", name, sizeof(name));
        if (name[0] == '\0') {
            printf("Name cannot be empty. No changes made.\n");
            return;
        }
        for (i = 0; name[i] != '\0'; i++) {
            if (name[i] == '|') {
                printf("The character '|' is not allowed in a name. No changes made.\n");
                return;
            }
        }
        strcpy(student->name, name);
        printf("Name updated successfully.\n");
    } else if (field_choice == 'p') {
        do {
            percentage = read_float("Enter new percentage (0 to 100): ");
            if (percentage < 0.0f || percentage > 100.0f) {
                printf("Percentage must be between 0 and 100.\n");
            }
        } while (percentage < 0.0f || percentage > 100.0f);

        student->percentage = percentage;
        printf("Percentage updated successfully.\n");
    } else {
        printf("Invalid field choice. No changes made.\n");
    }
}
