#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;
int nlines;
char **lines;


int get_nlines(void);

char **get_lines(int nlines);

void sort_lines(char **lines, int nlines);

void print_lines(char **lines, int nlines);

void free_lines(char **lines, int nlines);

void swapLines(int i, int j, char **lines);

int compareLines(int i, int j, char **lines);


int main(int argv, char **argc) {
    if (argv != 2) {
        printf("Wrong number of args");
        return -1;
    }

    char *fileName = argc[1];
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Input error\n");
        exit(EXIT_FAILURE);
    }

    nlines = get_nlines();
    if (nlines < 0) {
        printf("Invalid input\n");
        return -1;
    }
    lines = get_lines(nlines);
    print_lines(lines, nlines);
    sort_lines(lines, nlines);
    printf("\nSorted\n");
    print_lines(lines, nlines);
    free_lines(lines, nlines);

    fclose(file);

    return 0;
}

int get_nlines(void) {
    char buf[255], c;
    int i = 0;
    while ((c = (char) fgetc(file)) != '\n')
        buf[i++] = c;
    sscanf(buf, "%d", &i);
    return i;

}

char **get_lines(int nlines) {
    char **lines = (char **) calloc(nlines, 255);
    for (int i = 0; i < nlines; i++)
        lines[i] = (char *) calloc(255, 1);
    char buf[255], c;
    int i = 0;
    int line = 0;
    while ((c = (char) fgetc(file)) != EOF) {
        if (c == '\n') {
            line++;
            i = 0;
        } else {
            lines[line][i++] = c;
        }
    }
    return lines;
}

void sort_lines(char **lines, int nlines) {
    for (int i = 0; i < nlines; i++) {
        int minLineIndex = i;
        for (int j = i + 1; j < nlines; j++) {
            if (compareLines(minLineIndex, j, lines) == 1)
                minLineIndex = j;
        }
        swapLines(i, minLineIndex, lines);
    }
}


void print_lines(char **lines, int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lines[i]);
}

void free_lines(char **lines, int nlines) {
    for (int i = 0; i < nlines; i++)
        free(lines[i]);
    free(lines);
}

void swapLines(int i, int j, char **lines) {
    char *buf = lines[i];
    lines[i] = lines[j];
    lines[j] = buf;
}

int compareLines(int i, int j, char **lines) {
    int length1 = (int) strlen(lines[i]);
    int length2 = (int) strlen(lines[j]);

    int index = 0;
    while (index < length1 && index < length2) {
        char c1 = lines[i][index];
        char c2 = lines[j][index];
        if (c1 > c2)
            return 1;
        else if (c1 < c2)
            return -1;
        else
            index++;
    }

    if (length1 == length2)
        return 0;
    else if (length1 > length2)
        return 1;
    else
        return -1;
}

