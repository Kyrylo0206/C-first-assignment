#include <stdio.h>
#include <stdbool.h>

//Function Declarations
void appendText(char *text);
void newLine();
void saveToFile(const char *filename);
void loadFromFile(const char *filename);
void printText();
void insertText(int line, int index, char *str);
int searchText(char *str);

int main(void){
    int choice;
    //char inputBuffer[BUFFER_SIZE];
    int line, index;
    char filename[100];

    while (true){
        int user_input;
        printf("\nChoose the command:\n ");
        scanf("%d",  user_input);
        if (user_input == 1){
            printf("%s","1. Enter text to append\n");
        }
        else if (user_input == 2){
            printf("%s","2. Start new line\n");
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
        }
        else if (user_input == 7){
            printf("%s","7. Search text position");
        }
        else{
            printf("%s", "Invalid choice. Please try again.\n");
        }

    }
    return 0;
}