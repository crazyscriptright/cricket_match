#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_OVERS 20
#define BALLS_PER_OVER 6
#define MAX_INPUT_LENGTH 3
#define MAX_PLAYERS 11
#define NAME_LENGTH 20
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

int i, j, numberOfOvers, k;

typedef struct
{
    char name[NAME_LENGTH];
    int runs;
    int balls;
} Player;

void inputScores(int runs[MAX_OVERS][BALLS_PER_OVER], Player team[MAX_PLAYERS], int *totalScore, int *wickets, int *ballsBowled, int *targetScore, int inning)
{
    int strikerIndex = 0, nonStrikerIndex = 1, totalBallsBowled, currentRunrate, requiredRunrate, remainingBalls, run;
    *totalScore = 0;
    *wickets = 0;
    *ballsBowled = 0;
    printf("\n\033[7;5;31mEnter runs or 'W' for wicket" RESET "\n");
    for (i = 0; i < numberOfOvers; i++)
    {
        printf("" BLUE "Over %d:" RESET " \n", i + 1);
        for (j = 0; j < BALLS_PER_OVER; j++)
        {
            char input[MAX_INPUT_LENGTH];
            printf(MAGENTA "  Ball %d:  " GREEN "", j + 1);
            scanf("%s", input);
            if (strlen(input) > 1)
            {
                printf("\t" RED "Invalid Runs\n" RESET);
                j--;
                continue;
            }

            if (isdigit(input[0]))
            {
                run = atoi(input);
                if (run > 6 || run < 0 || run == 5)
                {
                    printf(RED "\tINVALID RUNS\n" RESET);
                    j--;
                    continue;
                }
                runs[i][j] = run;
                if (runs[i][j] == 0)
                {
                    runs[i][j] = -2;
                }
                *totalScore += run;
                team[strikerIndex].runs += run;
                team[strikerIndex].balls += 1;
                if (inning == 2 && *totalScore > *targetScore)
                {
                    (*ballsBowled)++;
                    return;
                }

                if (run % 2 == 1)
                {
                    int temp = strikerIndex;
                    strikerIndex = nonStrikerIndex;
                    nonStrikerIndex = temp;
                }
            }
            else if (toupper(input[0]) == 'W')
            {
                printf("\033[1;31m\tPlayer \033[1;6;31m%s OUT" RESET " \033[1;31mwith %d runs\n" RESET, team[strikerIndex].name, team[strikerIndex].runs);
                runs[i][j] = -1;
                team[strikerIndex].balls += 1;
                (*wickets)++;
                if (*wickets < MAX_PLAYERS - 1)
                {
                    strikerIndex = *wickets + 1;
                }
                else
                {
                    return;
                }
            }
            else
            {
                printf("\t" RED "Invalid input. Please enter a valid number or 'W' for wicket.\n" RESET);
                j--;
                continue;
            }

            (*ballsBowled)++;
            totalBallsBowled = (i * 6) + j + 1;
            float currentRunrate = (*totalScore) * 6 / totalBallsBowled;
            remainingBalls = ((numberOfOvers * 6) - totalBallsBowled);

            if (inning == 1)
            {
                printf("\t" YELLOW "Current Runrate: %.2f \t Current Score: %d" RESET "\n", currentRunrate, *totalScore);
            }
            if (inning == 2)
            {
                float requiredRunrate = ((*targetScore + 1 - *totalScore) * 6.0) / remainingBalls;
                if (remainingBalls != 0)
                {
                    printf("\t" CYAN "Needed %d runs in %d balls", (*targetScore + 1) - (*totalScore), remainingBalls);
                    printf("\tCurrent Runrate: %.2f\t Required Runrate: %.2f \tCurrent Score:%d" RESET "\n", currentRunrate, requiredRunrate, *totalScore);
                }
            }
        }
        int temp = strikerIndex;
        strikerIndex = nonStrikerIndex;
        nonStrikerIndex = temp;
    }
}

void displayScores(int runs[MAX_OVERS][BALLS_PER_OVER], int numberOfOvers)
{
    for (i = 0; i < numberOfOvers; i++)
    {
        printf("Over %d: ", i + 1);
        for (j = 0; j < BALLS_PER_OVER; j++)
        {
            if (runs[i][j] == -1)
            {
                printf("W ");
            }
            else if (runs[i][j] == '\0')
            {
                printf("\n");
                return;
            }
            else if (runs[i][j] == -2)
            {
                printf("0 ");
            }
            else
            {
                printf("%d ", runs[i][j]);
            }
        }
        printf("\n");
    }
}
void playerDispay(Player team[MAX_PLAYERS])
{
    printf("\nPlayer Scores:\n");
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        printf("%s: %d runs, %d balls\n", team[i].name, team[i].runs, team[i].balls);
    }
}

void manOfMatch(Player team1[MAX_PLAYERS], Player team2[MAX_PLAYERS])
{
    int high = 0, ball = 0, teamname;
    char playername[NAME_LENGTH];
    for (j = 0; j < 2; j++)
    {
        Player *team = (j == 0) ? team1 : team2;
        for (i = 0; i < MAX_PLAYERS; i++)
        {
            if (high < team[i].runs)
            {
                high = team[i].runs;
                strcpy(playername, team[i].name);
                teamname = j + 1;
                ball = team[i].balls;
            }
            else if (high <= team[i].runs && ball > team[i].balls)
            {
                high = team[i].runs;
                strcpy(playername, team[i].name);
                teamname = j + 1;
                ball = team[i].balls;
            }
        }
    }
    printf(GREEN "\nMan of the match award goes to %s from Team%d with %d runs in %d balls" RESET "\n", playername, teamname, high, ball);
}

void colorAnimation(int startColor, int endColor)
{
    int i = 0, j = 0;
    do
    {
        system("cls");
        printf("\033[%d;%d;%dm", i, j, 31 + startColor);
        printf(" \n"
               "  ______           __          __                 __          ______                                      	      \n"
               " /      \\         |  \\        |  \\               |  \\        /      \\                                                \n"
               "|  $$$$$$\\ ______  \\$$ _______| $$   __  ______ _| $$_      |  $$$$$$\\ _______  ______   ______   ______            \n"
               "| $$   \\$$/      \\|  \\/       | $$  /  \\/      |   $$ \\     | $$___\\$$/       \\/      \\ /      \\ /      \\         \n"
               "| $$     |  $$$$$$| $|  $$$$$$| $$_/  $|  $$$$$$\\$$$$$$      \\$$    \\|  $$$$$$|  $$$$$$|  $$$$$$|  $$$$$$\\       \n"
               "| $$   __| $$   \\$| $| $$     | $$   $$| $$    $$| $$ __     _\\$$$$$$| $$     | $$  | $| $$   \\$| $$    $$      \n"
               "| $$__/  | $$     | $| $$_____| $$$$$$\\| $$$$$$$$| $$|  \\   |  \\__| $| $$_____| $$__/ $| $$     | $$$$$$$$\\     \n"
               " \\$$    $| $$     | $$\\$$     | $$  \\$$\\\\$$     \\ \\$$  $$    \\$$    $$\\$$     \\\\$$    $| $$      \\$$     \\    \n"
               "  \\$$$$$$ \\$$      \\$$ \\$$$$$$$\\$$   \\$$ \\$$$$$$$  \\$$$$      \\$$$$$$  \\$$$$$$$ \\$$$$$$ \\$$       \\$$$$$$$     \n");
        Sleep(800);
        startColor++;
        if (startColor == 6)
            startColor = 0;
        if (endColor == startColor + 1)
        {
            i = 5;
            j = 6;
        }
    } while (startColor != endColor);
    printf("\n" RESET);
}

void players(Player team[MAX_PLAYERS], int i)
{
    char choice[2], playerName[20];
    while (1)
    {
        printf(RESET "\nDo you want to continue with default player names for Team%d (y/n): " GREEN, i);
        scanf(" %s", choice);
        if (strlen(choice) > 1)
        {
            printf("\t" RED "Invalid choice\n" RESET);
            continue;
        }
        if (choice[0] == 'n' || choice[0] == 'N')
        {
            printf(RESET "\nEnter the player names for team%d:\n", i);
            for (j = 0; j < MAX_PLAYERS; j++)
            {
                while (1)
                {
                    int valid = 1;
                    printf(RESET "Player %d: " GREEN, j + 1);
                    scanf("%s", playerName);

                    for (k = 0; k < strlen(playerName); k++)
                    {
                        if (!isalpha(playerName[k]))
                        {
                            printf(RED "\tEnter valid Name\n" RESET);
                            valid = 0;
                            break;
                        }
                    }

                    if (valid)
                    {
                        strcpy(team[j].name, playerName);
                        break;
                    }
                }
            }
            printf(RESET "\n");
            break;
        }
        else if (choice[0] == 'y' || choice[0] == 'Y')
        {
            for (j = 0; j < MAX_PLAYERS; j++)
            {
                snprintf(team[j].name, NAME_LENGTH, "T%dP%d", i, j + 1);
            }
            break;
        }
        else
        {
            printf(RED "\tInvalid choice, please try again.\n" RESET);
        }
    }
}

int main()
{
    char Overs[10];
    Player team1Players[MAX_PLAYERS] = {0};
    Player team2Players[MAX_PLAYERS] = {0};
    int runsTeam1[MAX_OVERS][BALLS_PER_OVER] = {0};
    int runsTeam2[MAX_OVERS][BALLS_PER_OVER] = {0};
    int totalScoreTeam1, totalScoreTeam2, valid;
    int wicketsTeam1, wicketsTeam2;
    int ballsBowledTeam1, ballsBowledTeam2;

    colorAnimation(5, 4);
    while (1)
    {
        printf("\n" RESET "Enter the number of overs (maximum %d): " GREEN, MAX_OVERS);
        scanf("%s", Overs);
        valid = 1;
        for (i = 0; i < strlen(Overs); i++)
        {
            if (!isdigit(Overs[i]))
            {
                printf("\t" RED "Invalid Input\n" RESET "");
                valid = 0;
                break;
            }
        }
        if (!valid)
        {
            continue;
        }
        numberOfOvers = atoi(Overs);
        if (numberOfOvers > MAX_OVERS || numberOfOvers <= 0)
        {
            printf(RED "Invalid number of overs. Please enter a number between 1 and %d.\n" RESET, MAX_OVERS);
            continue;
        }
        else
        {
            break;
        }
    }
    for (i = 0; i < numberOfOvers; i++)
    {
        for (j = 0; j < BALLS_PER_OVER; j++)
        {
            runsTeam1[i][j] = '\0';
            runsTeam2[i][j] = '\0';
        }
    }
    players(team1Players, 1);
    players(team2Players, 2);

    printf(RESET "\n\033[0;4;38mInput scores for Team1:\n" RESET);
    inputScores(runsTeam1, team1Players, &totalScoreTeam1, &wicketsTeam1, &ballsBowledTeam1, &totalScoreTeam1, 1);

    printf("\n****" GREEN "Team2 needs %d runs in %d balls" RESET "****\n", totalScoreTeam1 + 1, 6 * numberOfOvers);
    printf("\n  ****" GREEN "Required Runrate: %.2f" RESET "****\n\n", (float)(totalScoreTeam1 + 1) / numberOfOvers);

    printf("\n" RESET "\033[0;4;38mInput scores for Team2:\n" RESET);
    inputScores(runsTeam2, team2Players, &totalScoreTeam2, &wicketsTeam2, &ballsBowledTeam2, &totalScoreTeam1, 2);

    for (i = 0; i < 2; i++)
    {
        if (totalScoreTeam1 > totalScoreTeam2)
        {
            printf("\n\t\t" YELLOW "\033[4mTeam1 won by %d runs!" RESET "\n\n", totalScoreTeam1 - totalScoreTeam2);
        }
        else if (totalScoreTeam2 > totalScoreTeam1)
        {
            printf("\n\t\t" YELLOW "\033[4mTeam2 won by %d wickets!" RESET "\n\n", 10 - wicketsTeam2);
        }
        else
        {
            printf("\n\t\t" YELLOW "\033[4mThe match is a tie!" RESET "\n\n");
        }
        Sleep(1000);
    }
    getch();
    printf("\n" RESET "Scores for Team1:\n" RED);
    displayScores(runsTeam1, numberOfOvers);
    int completedOversTeam1 = ballsBowledTeam1 / BALLS_PER_OVER;
    int remainingBallsTeam1 = ballsBowledTeam1 % BALLS_PER_OVER;
    printf("Total Score: %d\n", totalScoreTeam1);
    printf("Wickets: %d\n", wicketsTeam1);
    printf("Overs: %d.%d" CYAN "\n", completedOversTeam1, remainingBallsTeam1);
    playerDispay(team1Players);
    getch();

    printf("\n" RESET "Scores for Team2:\n" YELLOW);
    displayScores(runsTeam2, numberOfOvers);
    int completedOversTeam2 = ballsBowledTeam2 / BALLS_PER_OVER;
    int remainingBallsTeam2 = ballsBowledTeam2 % BALLS_PER_OVER;
    printf(YELLOW "Total Score: %d\n", totalScoreTeam2);
    printf("Wickets: %d\n", wicketsTeam2);
    printf("Overs: %d.%d\n" BLUE, completedOversTeam2, remainingBallsTeam2);
    playerDispay(team2Players);
    manOfMatch(team1Players, team2Players);
    getch();
    return 0;
}
