#ifndef STUD_H
#define STUD_H

#include <stdio.h>

#define NAME_LEN 100
#define DATA_FILE "student.dat"

typedef struct Student {
    int roll;
    char name[NAME_LEN];
    float percentage;
    struct Student *next;
} Student;

extern Student *head;

/* Shared helpers */
void read_line(const char *prompt, char *buffer, size_t size);
int read_int(const char *prompt);
float read_float(const char *prompt);
char read_choice(const char *prompt);
Student *find_by_roll(int roll);
int roll_exists(int roll);
int smallest_available_roll(void);
void free_list(void);

/* Required project functions */
void stud_add(void);
void stud_del(void);
void stud_show(void);
void stud_mod(void);
void stud_save(void);
void stud_load(void);
void stud_sort(void);

#endif
