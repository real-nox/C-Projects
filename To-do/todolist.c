#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define LINE_SIZE 256

FILE *ListFileA;
FILE *ListFileR;

char listner[50];

int idfinder(int ID);
int addlist();
void removelist(int ID);
void listoflists();

int main()
{
    int opt;
    int id;
    do
    {
        printf("Welcome to the TO DO LIST !\n\nYou may choose one of the following options bellow :\n1 : Add to do list\n2 : Remove specific to do list\n3 : Show to do list\n\n0 : Exit\n\n");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            addlist();
            break;
        case 2:
            printf("Enter ID of the task : ");
            scanf("%d", &id);
            removelist(id);
            break;
        case 3:
            listoflists();
            break;
        default:
            continue;
        }
    } while (opt != 0);
    return 0;
}

int idfinder(int ID) {

    char listner[LINE_SIZE];
    char lines[MAX_LINES][LINE_SIZE];

    int CurrentID;
    int found, MaxID, lineCount = {0, 0, 0};

    if (ID == 0) {
        ListFileR = fopen("TODOLIST.txt", "r");
        if (ListFileR == NULL) {
            return 1;
        }

        while (fgets(listner, sizeof(listner), ListFileR) != NULL) {
            if (sscanf(listner, "%d", &CurrentID) == 1) {
                printf("IDDDD %d\n", CurrentID);
                if (CurrentID > MaxID) {
                    MaxID = CurrentID;
                }
            }
        }
        fclose(ListFileR);
        printf("%d\n", MaxID + 1);
        return MaxID + 1;
    } else {
        ListFileR = fopen("TODOLIST.txt", "r");
        if (ListFileR == NULL) {
            return 1;
        }

        while (lineCount < MAX_LINES && fgets(lines[lineCount], LINE_SIZE, ListFileR) != NULL) {
            lines[lineCount][strcspn(lines[lineCount], "\n")] = 0;
            if (sscanf(lines[lineCount], "%d", &CurrentID) == 1 && CurrentID == ID) {
                printf("Found Task: %s\n", lines[lineCount]);
                printf("Removing line..\n");
                found = 1;
                continue;
            }
            lineCount++;
        }
        fclose(ListFileR);

        if (!found) {
            printf("No task found with ID %d.\n", ID);
            return 1;
        }

        ListFileA = fopen("TODOLIST.txt", "w");
        if (ListFileA == NULL) {
            return 1;
        }
        for (int i = 0; i < lineCount; i++) {
            fprintf(ListFileA, "%s\n", lines[i]); 
        }
        fclose(ListFileA);
        return 0;
    }
}

int addlist()
{
    ListFileA = fopen("TODOLIST.txt", "a");

    if (ListFileA == NULL)
        return 1;

    int ID = idfinder(0);
    fprintf(ListFileA, "%d Sup dude\n", ID);
    fclose(ListFileA);
}

void removelist(int ID) {
    idfinder(ID);
}
void listoflists() {}