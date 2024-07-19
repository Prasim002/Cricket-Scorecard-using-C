#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<unistd.h>

// Function to display ball details
void ballss(int o, char r[10], int wr) {
	int k;
    for(k=0; k<o; k++) {
        switch(r[k]) {
            case 'o':
                printf("(W)");
                break;
            case 'w':
                printf("(WD%d)", wr);
                break;
            case 'n':
                printf("(NB%d)", wr);
                break;
            default:
                printf("(%c)", r[k]);
        }
    }
}

// Function to handle the toss and choose batting/fielding
int toss(char team1[10], char team2[10]) {
    char tosswin[10], tc;
    printf("Who won the toss? ");
    scanf("%s", tosswin);
    printf("Enter B for batting and F for fielding: ");
    scanf(" %c", &tc);

    if(strcmp(team1, tosswin) == 0) {
        if(tc == 'b' || tc == 'B') {
            printf("%s chose to bat\n", team1);
            sleep(1);
            return 1;
        } else {
            printf("%s chose to field\n", team1);
            sleep(1);
            return 2;
        }
    } else {
        if(tc == 'b' || tc == 'B') {
            printf("%s chose to bat\n", team2);
            sleep(1);
            return 2;
        } else {
            printf("%s chose to field\n", team2);
            sleep(1);
            return 1;
        }
    }
}

// Function to open file for innings
FILE* openFileForInnings(char* teamName) {
    char filename[20];
    sprintf(filename, "%s.txt", teamName);
    FILE* fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("Error in creating team file\n");
    }
    return fp;
}

// Function to display match banner
void displayMatchBanner(char* team1, char* team2) {
    int len1 = strlen(team1);
    int len2 = strlen(team2);
    int total_len = len1 + len2 + 4; // Including spaces and "VS"
    int padding = (29 - total_len) / 2;

    printf("\t\t\t\t+-----------------------------+\n");
    printf("\t\t\t\t|       Cricket Match         |\n");
    printf("\t\t\t\t|%*s%s VS %s%*s|\n", padding, "", team1, team2, padding, "");
    printf("\t\t\t\t+-----------------------------+\n");
    sleep(4);
}

// Function to display ready message
void displayReadyMessage() {
    printf("Are ");
    sleep(1);
    printf("You ");
    sleep(1);
    printf("Ready?\n");
    sleep(2);
    printf("Press any key to continue");
    getch();
}

// Function to display match status
void displayMatchStatus(char* battingTeam, int runs, int wickets, int over, int ball) {
    printf("\t\t\t+---------------------------------------------------------------------------------------+\n");
    printf("\t\t\t|  %s  Batting  |\t\t\t%d-%d\t\t\t|\tovers %d.%d\t|\n", battingTeam, runs, wickets, over, ball);
    printf("\t\t\t+---------------------------------------------------------------------------------------+\n");
}

// Function to play innings and update runs and wickets
void playInnings(char* battingTeam, int* runs, int* wickets, int overcon, FILE* fp) {
    char r[10], c;
    int wr, o, b, runs_scored, i, j;

    for(i=0; i<=overcon; i++) {
        o = 0;
        for(j=0; j<6; j++) {
            hello:
            b = j + 1;
            if(i < overcon) {
                fprintf(fp, "%d.%d\t", i, b);
            }
            system("cls");
            displayMatchStatus(battingTeam, *runs, *wickets, i, j);
            printf("\t\t\t   ");
            ballss(o, r, wr);
            printf("\n\t\t\t+---------------------------------------------------------------------------------------+\n");
            if(i == overcon || *wickets == 10) {
                goto end_innings;
            }
            printf("\nRuns:0 1 2 3 4 6 Wicket:o Wide:w No Ball:n\n");
            printf("Enter case: ");
            scanf(" %c", &c);
            r[o] = c;
            o++;
            switch(c) {
                case '0':
                    fprintf(fp, "0\t");
                    break;
                case '1':
                    fprintf(fp, "1\t");
                    (*runs) += 1;
                    break;
                case '2':
                    fprintf(fp, "2\t");
                    (*runs) += 2;
                    break;
                case '3':
                    fprintf(fp, "3\t");
                    (*runs) += 3;
                    break;
                case '4':
                    fprintf(fp, "4\t");
                    (*runs) += 4;
                    break;
                case '6':
                    fprintf(fp, "6\t");
                    (*runs) += 6;
                    break;
                case 'w':
                    printf("Enter wide runs: ");
                    scanf("%d", &wr);
                    (*runs) += wr;
                    fprintf(fp, "Wide %d\t", wr);
                    j--;
                    break;
                case 'o':
                    (*wickets)++;
                    printf("Enter runs if runout: ");
                    scanf("%d", &runs_scored);
                    (*runs) += runs_scored;
                    fprintf(fp, "Wicket %d\t", runs_scored);
                    break;
                case 'n':
                    printf("Enter no ball runs: ");
                    scanf("%d", &wr);
                    (*runs) += wr;
                    fprintf(fp, "No Ball %d\t", wr);
                    j--;
                    break;
                default:
                    printf("Choose a valid option\n");
                    goto hello;
            }
            fprintf(fp, "%d-%d\n", *runs, *wickets);
        }
    }
    end_innings:
    fclose(fp);
}

// Function to display match result
void displayResult(char* team1, char* team2, int runs1, int runs2, int wickets2, int tossResult) {
    system("cls");
    if(runs1 == runs2) {
        printf("Draw, move to the super overs\n");
    } else {
        if(tossResult == 2) {
            if(runs1 > runs2) {
                printf("%s won by %d runs\n", team2, runs1 - runs2);
            } else {
                printf("%s won by %d wickets\n", team1, 10 - wickets2);
            }
        } else {
            if(runs1 > runs2) {
                printf("%s won by %d runs\n", team1, runs1 - runs2);
            } else {
                printf("%s won by %d wickets\n", team2, 10 - wickets2);
            }
        }
    }
}

// Function to view match stats
void viewStats() {
    char teamname[10], filename[20], content[100];
    FILE* fp3;
    printf("Enter name of team: ");
    scanf("%s", teamname);
    sprintf(filename, "%s.txt", teamname);
    fp3 = fopen(filename, "r");
    if(fp3 == NULL) {
        printf("Error in opening team file\n");
        return;
    }
    while(fgets(content, sizeof(content), fp3) != NULL) {
        printf("%s", content);
    }
    fclose(fp3);
}

int main() {
    int runst1 = 0, runst2 = 0, overcon, wicketst1 = 0, wicketst2 = 0, choice, t;
    char team1[10], team2[10];

    // Get team names and overs
    printf("Enter Team 1: ");
    scanf("%s", team1);
    printf("Enter Team 2: ");
    scanf("%s", team2);
    printf("Enter number of overs: ");
    scanf("%d", &overcon);

    // Perform toss and determine first batting team
    t = toss(team1, team2);
    FILE* fp1 = openFileForInnings(t == 1 ? team1 : team2);

    // Display match banner and ready message
    displayMatchBanner(team1, team2);
    displayReadyMessage();

    // First innings
    playInnings(t == 1 ? team1 : team2, &runst1, &wicketst1, overcon, fp1);

    printf("Ready for the next half? Press any key to continue\n");
    getch();

    // Second innings
    FILE* fp2 = openFileForInnings(t == 1 ? team2 : team1);
    playInnings(t == 1 ? team2 : team1, &runst2, &wicketst2, overcon, fp2);

    // Display match result
    displayResult(team1, team2, runst1, runst2, wicketst2, t);

    // Loop to view stats or exit
    while(1) {
        printf("\n1. See stats\n2. Exit\n");
        scanf("%d", &choice);
        if(choice == 1) {
            viewStats();
        } else {
            exit(0);
        }
    }
    return 0;
}

