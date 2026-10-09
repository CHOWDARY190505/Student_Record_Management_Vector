#include "stud.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

Student *head = NULL;

void read_line(const char *prompt, char *buffer, size_t size)
{
    size_t len;
    int ch;

    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* discard the rest of an overlong input line */
        }
    }
}

int read_int(const char *prompt)
{
    char line[128];
    char *end;
    long value;

    for (;;) {
        read_line(prompt, line, sizeof(line));
        errno = 0;
        value = strtol(line, &end, 10);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (line[0] != '\0' && *end == '\0' && errno == 0 &&
            value >= -2147483647L - 1L && value <= 2147483647L) {
            return (int)value;
        }
        printf("Invalid integer. Please try again.\n");
    }
}

float read_float(const char *prompt)
{
    char line[128];
    char *end;
    float value;

    for (;;) {
        read_line(prompt, line, sizeof(line));
        errno = 0;
        value = strtof(line, &end);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (line[0] != '\0' && *end == '\0' && errno == 0) {
            return value;
        }
        printf("Invalid number. Please try again.\n");
    }
}

char read_choice(const char *prompt)
{
    char line[32];
    read_line(prompt, line, sizeof(line));

    if (line[0] == '\0') {
        return '\0';
    }
    return (char)tolower((unsigned char)line[0]);
}

Student *find_by_roll(int roll)
{
    Student *current = head;
    while (current != NULL) {
        if (current->roll == roll) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int roll_exists(int roll)
{
    return find_by_roll(roll) != NULL;
}

int smallest_available_roll(void)
{
    int roll = 1;
    while (roll_exists(roll)) {
        roll++;
    }
    return roll;
}

void free_list(void)
{
    Student *current = head;
    while (current != NULL) {
        Student *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}
