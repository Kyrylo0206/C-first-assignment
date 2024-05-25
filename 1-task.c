#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BufferSize 1024
#define start true

char **text;
int capacity = 10;
int totalLines = 0;
int size = 128;

// Function Declarations
void appendText(char *newText);
void newLine();
void saveToFile(const char *filename);
void loadFromFile(const char *filename);
void printText();
void insertText(int line, int index, char *str);
void searchText(char *str, int *line, int *index);
void clearConsole();
void initializeTextStorage();
void ensureCapacity();
void Free_Text_storage();

int main(void) {
    int user_input;
    char inputBuffer[BufferSize];
    int line, index;
    char filename[144];

    initializeTextStorage();

    while (start) {
        printf("\nChoose the command from 1 to 9:\n ");
        scanf("%d", &user_input);
        getchar();

        if (user_input == 1) {
            printf("1. Enter text to append\n");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);
            inputBuffer[strcspn(inputBuffer, "\n")] = 0;
            appendText(inputBuffer);
        } else if (user_input == 2) {
            printf("2. Start new line\n");
            newLine();
        } else if (user_input == 3) {
            printf("3. Enter the file name for saving:\n ");
            scanf("%s", filename);
            saveToFile(filename);
        } else if (user_input == 4) {
            printf("4. Enter the file name for loading:\n ");
            scanf("%s", filename);
            loadFromFile(filename);
        } else if (user_input == 5) {
            printf("You are printing the current text\n");
            printText();
        } else if (user_input == 6) {
            printf("6. Choose line and index:\n ");
            scanf("%d %d", &line, &index);
            getchar();
            printf("Enter text to insert: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);
            inputBuffer[strcspn(inputBuffer, "\n")] = 0;
            insertText(line, index, inputBuffer);
        } else if (user_input == 7) {
            printf("7. Search text position\n");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);
            inputBuffer[strcspn(inputBuffer, "\n")] = 0;
            searchText(inputBuffer, &line, &index);
            if (line == -1) {
                printf("Text not found.\n");
            } else {
                printf("Text found at line %d, index %d.\n", line, index);
            }
        } else if (user_input == 8) {
            clearConsole();
        } else if (user_input == 9) {
            Free_Text_storage();
            return 0;
        }
    }
    return 0;
}

void initializeTextStorage() {
    text = malloc(capacity * sizeof(char*));
    for (int i = 0; i < capacity; i++) {
        text[i] = malloc(BufferSize * sizeof(char));
        text[i][0] = '\0';
    }
}

void ensureCapacity() {
    if (totalLines >= capacity) {
        int newCapacity = capacity + size;
        char **newText = realloc(text, newCapacity * sizeof(char*));
        if (newText == NULL) {
            printf("Failed to allocate more memory.\n");
            return;
        }
        for (int i = capacity; i < newCapacity; i++) {
            newText[i] = malloc(BufferSize * sizeof(char));
            newText[i][0] = '\0';
        }
        text = newText;
        capacity = newCapacity;
    }
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void appendText(char *newText) {
    ensureCapacity();
    if (newText != NULL) {
        strcpy(text[totalLines], newText);
        totalLines++;
    }
}

void newLine() {
    ensureCapacity();
    text[totalLines][0] = '\0';
    totalLines+ 1;
}

void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }
    for (int i = 0; i < totalLines; i++) {
        fprintf(file, "%s\n", text[i]);
    }
    fclose(file);
}

void loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[BufferSize];
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    while (fgets(line, BufferSize, file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        appendText(line);
    }
    fclose(file);
}

void printText() {
    for (int i = 0; i < totalLines; i++) {
        printf("%s\n", text[i]);
    }
}

void insertText(int line, int index, char *str) {
    if (line < 0 || line >= totalLines) {
        printf("Invalid line number.\n");
        return;
    }
    if (index < 0 || index > strlen(text[line])) {
        printf("Invalid index.\n");
        return;
    }
    char buffer[BufferSize];
    strncpy(buffer, text[line], index);
    buffer[index] = '\0';
    strcat(buffer, str);
    strcat(buffer, &text[line][index]);
    strcpy(text[line], buffer);
}

void searchText(char *str, int *line, int *index) {
    *line = -1;
    *index = -1;

    for (int i = 0; i < totalLines; i++) {
        char *position = strstr(text[i], str);
        if (position != NULL) {
            *line = i;
            *index = position - text[i];
            return;
        }
    }
}

void Free_Text_storage() {
    for (int i = 0; i < capacity; i++) {
        free(text[i]);
    }
    free(text);
}
