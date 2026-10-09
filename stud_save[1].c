#include "stud.h"
#include <stdlib.h>
#include <string.h>

void stud_save(void)
{
    FILE *fp = fopen(DATA_FILE, "w");
    Student *current = head;

    if (fp == NULL) {
        perror("Could not open student.dat for saving");
        return;
    }

    while (current != NULL) {
        if (fprintf(fp, "%d|%.2f|%s\n",
                    current->roll, current->percentage, current->name) < 0) {
            printf("An error occurred while writing records.\n");
            fclose(fp);
            return;
        }
        current = current->next;
    }

    if (fclose(fp) == 0) {
        printf("Records saved to %s successfully.\n", DATA_FILE);
    } else {
        perror("Error closing data file");
    }
}

void stud_load(void)
{
    FILE *fp = fopen(DATA_FILE, "r");
    int roll;
    float percentage;
    char name[NAME_LEN];
    char line[256];
    int loaded = 0;

    if (fp == NULL) {
        /* It is normal for the file not to exist on the first run. */
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *first = strchr(line, '|');
        char *second;
        char *newline;
        char *end;
        long parsed_roll;
        float parsed_percentage;
        Student *node;
        Student *tail;

        if (first == NULL) {
            continue;
        }
        *first = '\0';
        second = strchr(first + 1, '|');
        if (second == NULL) {
            continue;
        }
        *second = '\0';

        parsed_roll = strtol(line, &end, 10);
        if (*line == '\0' || *end != '\0' || parsed_roll <= 0 ||
            parsed_roll > 2147483647L) {
            continue;
        }

        parsed_percentage = strtof(first + 1, &end);
        if (*(first + 1) == '\0' || *end != '\0' ||
            parsed_percentage < 0.0f || parsed_percentage > 100.0f) {
            continue;
        }

        strncpy(name, second + 1, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        newline = strchr(name, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        newline = strchr(name, '\r');
        if (newline != NULL) {
            *newline = '\0';
        }
        if (name[0] == '\0' || roll_exists((int)parsed_roll)) {
            continue;
        }

        roll = (int)parsed_roll;
        percentage = parsed_percentage;

        node = (Student *)malloc(sizeof(Student));
        if (node == NULL) {
            printf("Not enough memory to load all records.\n");
            break;
        }
        node->roll = roll;
        node->percentage = percentage;
        strcpy(node->name, name);
        node->next = NULL;

        if (head == NULL) {
            head = node;
        } else {
            tail = head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = node;
        }
        loaded++;
    }

    fclose(fp);
    if (loaded > 0) {
        printf("%d record(s) loaded from %s.\n", loaded, DATA_FILE);
    }
}
