#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAX 1000


typedef struct question {
    int order;
    char ques[300];
    char a[50];
    char b[50];
    char c[50];
    char d[50];
    char answer[50];
} Question;

void showTheRules();
void userInfo(int);

void randomTens(Question questions[], int shuffleOrder[]);
void storeQuestions(Question[]);
void askQuestion(Question x);
void shuffleInts(int shuffleOrder[]);
int checkList(int shuffleOrder[], int index, int rnd);


int main()
{
    Question questions[20];
    storeQuestions(questions);
    int shuffleOrder[10];
    
    puts("\tWelcome to the most exciting educational GAME!\n");
    
    int choice;
    while (1) {
        
        printf("\n\t***Who wants to be a millionaire***");
        printf("\n\t*                                             *");
        printf("\n\t*Enter(1)\tStart the game              *");
        printf("\n\t*                                             *");
        printf("\n\t*Enter(2)\tShow the rules              *");
        printf("\n\t*                                             *");
        printf("\n\t*Enter(3)\tExit                    *");
        printf("\n\t*                                             *");
        printf("\n\t* * * * * * * * * * * * * * * * * * * * * * * * ");
        puts("");
        
        printf("\nPlease, enter you choice: ");
        scanf("%d", &choice);
        
        if (choice == 1)
        {
            shuffleInts(shuffleOrder);
            randomTens(questions, shuffleOrder);
        }
        else if (choice == 2)
            showTheRules();
        else if (choice == 3)
            return 0;
        puts("\n");
    }
    
    
    return 0;
}


void storeQuestions(Question questions[])
{
    char line[20][MAX];
    
    FILE *fp = fopen("Questions.txt", "r");
    char *token[20];
    
    if (fp == NULL)
    {
        puts("File could not be opened.");
        exit(1); //to get rid of that
    }
    
    else
    {
        for (int i = 0; i < 20; i++)
        {
            fgets(line[i], sizeof(line[i]), fp);
        }
    }
    
    char *tokens[20];
    
    for (int i = 0; i < 20; i++)
    {
        
        tokens[i] = strtok(line[i], ";");
        questions[i].order = atoi(tokens[i]);
        
        //while (tokens[i] != NULL)
        for (int l = 0; l < 6; l++)
        {
            //printf("%s\n", tokens[i]);
            tokens[i] = strtok(NULL, ";");
            switch (l) {
                case 0:
                    strcpy(questions[i].ques, tokens[i]);                break;
                case 1:
                    strcpy(questions[i].a, tokens[i]);
                    break;
                case 2:
                    strcpy(questions[i].b, tokens[i]);                break;
                case 3:
                    strcpy(questions[i].c, tokens[i]);                break;
                case 4:
                    strcpy(questions[i].d, tokens[i]);                break;
                case 5:
                    strcpy(questions[i].answer, tokens[i]);                break;
            }
            
        }
    }
    fclose(fp);
}

void askQuestion(Question x)
{
    printf("%s\n%s\n%s\n%s\n%s\n", x.ques, x.a, x.b, x.c, x.d);
}

void shuffleInts(int shuffleOrder[])
{
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int rnd;
        do {
            rnd = rand() % 20;
        } while (checkList(shuffleOrder, i, rnd));
        
        shuffleOrder[i] = rnd;
    }
}

int checkList(int shuffleOrder[], int index, int rnd)
{
    for (int i = 0; i < index; i++)
    {
        if (shuffleOrder[i] == rnd)
            return 1;
    }
    
    return 0;
}

void randomTens(Question questions[], int shuffleOrder[])
{
    char userAnswer[2];
    
    for (int i = 0; i < 10; i++)
    {
        askQuestion(questions[shuffleOrder[i]]);
        scanf("%s", userAnswer); //needs attention
        if (userAnswer[0] == questions[shuffleOrder[i]].answer[0] || userAnswer[0] + 'a' - 'A' == questions[shuffleOrder[i]].answer[0])
            printf("Sukani bele SAXLA!\n\n");
        else
        {
            puts("Sorry, but 'En zeif bend Sizsiniz!'");
            userInfo(i);
            printf("You could get $%d\n\n", earnedAmount(i));
            break;
        }
        if (i == 9)
            printf("Congratulations! You became a MILLIONAIRE\n");
    }
}

void userInfo(int i)
{
    char name[30];
    printf("Enter your name: ");
    scanf("%s", &name); //be careful
    
    FILE *fp = fopen("Player Results.txt", "a");
    if (fp == NULL)
    {
        puts("Error opening the file!");
        exit(1); //needs attention
    }
    else
    {
        fprintf(fp, "%s        $%d\n", name, earnedAmount(i));
    }
    
    fclose(fp);
    
}

int earnedAmount(int i)
{
    int earnedAmount;
    
    switch (i)
    {
        case 0:
            earnedAmount = 0;
            break;
        case 1:
            earnedAmount = 4000;
            break;
        case 2:
            earnedAmount = 8000;
            break;
        case 3:
            earnedAmount = 16000;
            break;
        case 4:
            earnedAmount = 32000;
            break;
        case 5:
            earnedAmount = 64000;
            break;
        case 6:
            earnedAmount = 125000;
            break;
        case 7:
            earnedAmount = 250000;
            break;
        case 8:
            earnedAmount = 500000;
            break;
        case 9:
            earnedAmount = 1000000; //no need for break statement
    }
    
    return earnedAmount;
}

void showTheRules() {
    
    printf("\t########These are the rules of the game:#########");
    printf("\n\t#                                               #");
    printf("\n\t#Who wants to be a millionaire is a quiz compe- #");
    printf("\n\t#                                               #");
    printf("\n\t#tition where contestants have to correctly     #");
    printf("\n\t#                                               #");
    printf("\n\t#answer a series of multiple-choice questions   #");
    printf("\n\t#                                               #");
    printf("\n\t#in order to advance to the next level.         #");
    printf("\n\t#                                               #");
    printf("\n\t#There are 10 questions in total and each       #");
    printf("\n\t#                                               #");
    printf("\n\t#question is worth a specific amount  of money  #");
    printf("\n\t#                                               #");
    printf("\n\t#and no time limit is placed on contestants to  #");
    printf("\n\t#                                               #");
    printf("\n\t#come up with an answer                         #");
    printf("\n\t# # # # # # # # # # # # # # # # # # # # # # # # #");
    
}
