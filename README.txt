STUDENT RECORD MANAGEMENT SYSTEM
================================

Files:
  main.c          Main menu and program flow
  stud.h          Structure and function declarations
  stud_common.c   Shared input and linked-list helpers
  stud_add.c      Add a student record
  stud_del.c      Delete by roll number or name
  stud_show.c     Display all records
  stud_mod.c      Search and modify a record
  stud_save.c     Save to and load from student.dat
  stud_sort.c     Sort by name or percentage

Compile with GCC:
  gcc -std=c99 -Wall -Wextra -pedantic main.c stud_common.c stud_add.c stud_del.c stud_show.c stud_mod.c stud_save.c stud_sort.c -o student

Run:
  ./student

On Windows with MinGW:
  student.exe

The file student.dat is created in the program's current working directory.
It stores one record per line in this format:
  roll|percentage|name

Example:
  1|85.50|Arun Kumar
  2|91.00|Priya

Notes:
- Roll numbers are assigned as the smallest currently unused positive integer.
- Name matching is exact and case-sensitive.
- Sorting is ascending.
- Percentage is limited to 0 through 100.
- Selecting Exit Without Saving discards unsaved changes made since the last save.
- Keep all .c files and stud.h in the same folder when compiling.
