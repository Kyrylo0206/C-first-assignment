#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define BufferSize 1024
#define start true

char text[100][BufferSize];
int totalLines = 0;

//Function Declarations need to declarate and then in any part of code write it
void appendText(char *text);
void newLine();
void saveToFile(const char *filename);
void loadFromFile(const char *filename);
void printText();
void insertText(int line, int index, char *str);
int searchText(char *str);
void clearConsole() ;

int main(void){
    int user_input;
    char inputBuffer[BufferSize];
    int line, index;
    char filename[100];

    while (start){
        printf("\nChoose the command:\n ");
        scanf("%d",  user_input);
        if (user_input == 1){
            printf("%s","1. Enter text to append\n");
            fgets(inputBuffer, BufferSize, stdin);
            inputBuffer[strcspn(inputBuffer, "\n")] = 0; // Remove newline character
            appendText(inputBuffer);
            break;
        }
        else if (user_input == 2){
            printf("%s","2. Start new line\n");
            newLine();
            break;
        }
        else if (user_input == 3){
            printf("%s","3. Enter the file name for saving:\n ");
            scanf("%s", filename);
            saveToFile(filename);
        }
        else if (user_input == 4){
            printf("%s","4. Enter the file name for loading:\n ");
            scanf("%s", filename);
            loadFromFile(filename);
        }
        else if (user_input == 5){
            printf("%s", "You are printing the current text");
            printText();
        }
        else if (user_input == 6){
            printf("%s","6. Choose line and index:\n ");
            scanf("%d %d", &line, &index);
            getchar();
            printf("Enter text to insert: ");
            fgets(inputBuffer, BufferSize, stdin);
            inputBuffer[strcspn(inputBuffer, "\n")] = 0; // Remove newline character
            insertText(line, index, inputBuffer);
        }
        else if (user_input == 7){
            printf("%s","7. Search text position");
            fgets(inputBuffer, BufferSize, stdin);
            inputBuffer[strcspn(inputBuffer, "\n")] = 0; // Remove newline character
            if (searchText(inputBuffer) == 0) {
                printf("Text not found.\n");
            } else {
                printf("Text found at position %d.\n", searchText(inputBuffer));
            }
        }
        else if (user_input == 8) {
            printf("%s","8. Clear the console");
            clearConsole(); // Clear the console
        } else if (user_input == 9) {
            return 0;
        }
    }
    return 0;
}
void clearConsole() {
#ifdef _WIN64
    system("cls");
#else
    system("clear");
#endif
}
