#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define PATHLENGTH_MAX 70

#define PATHLENGTH_MIN 10

#define PATH_MULTIPLE 5

#define PATH_PERCENTAGE 0.75

#define LIVES_MIN 1

#define LIVES_MAX 10

struct PlayerInfo
{
    char symbol;
    int lives;
    int treasures;
    int history[PATHLENGTH_MAX];
};

struct GameInfo
{
    int maxMoves;
    int path;
    int bomb[PATHLENGTH_MAX];
    int treasures[PATHLENGTH_MAX];
};

int main(void)
{

    int validValue, gameOver, i, count, move; 

    struct PlayerInfo player1 = { 0 };

    struct GameInfo treasureHunt = { 0 };


    printf("================================\n");
    printf("         Treasure Hunt!\n");
    printf("================================\n\n");

    printf("PLAYER Configuration\n");
    printf("--------------------\n");

    do {

        validValue = 1;

        printf("Enter a single character to represent the player: ");
        scanf(" %c", &player1.symbol);

    } while (!validValue);

    do {

        validValue = 1;

        printf("Set the number of lives: ");
        scanf("%d", &player1.lives);

        if (player1.lives < LIVES_MIN || player1.lives > LIVES_MAX)
        {

            validValue = 0;

            printf("     Must be between %d and %d!\n", LIVES_MIN, LIVES_MAX);

        }

    } while (!validValue);

    for (i = 0; i < treasureHunt.path; i++)
    {
        player1.history[i] = 0;
    }

    printf("Player configuration set-up is complete\n\n");

    printf("GAME Configuration\n");
    printf("------------------\n");

    do {

        validValue = 1;

        printf("Set the path length (a multiple of %d between %d-%d): ", PATH_MULTIPLE,
            PATHLENGTH_MIN, PATHLENGTH_MAX);
        scanf("%d", &treasureHunt.path);

        if (treasureHunt.path > PATHLENGTH_MAX || treasureHunt.path < PATHLENGTH_MIN ||
            treasureHunt.path % PATH_MULTIPLE)
        {

            validValue = 0;

            printf("     Must be a multiple of %d and between %d-%d!!!\n", PATH_MULTIPLE,
                PATHLENGTH_MIN, PATHLENGTH_MAX);

        }

    } while (!validValue);

    do {

        validValue = 1;

        printf("Set the limit for number of moves allowed: ");
        scanf("%d", &treasureHunt.maxMoves);

        if (treasureHunt.maxMoves < player1.lives || treasureHunt.maxMoves >
            (int)(treasureHunt.path * PATH_PERCENTAGE))
        {

            validValue = 0;

            printf("    Value must be between %d and %d\n", player1.lives,
                (int)(treasureHunt.path * PATH_PERCENTAGE));

        }

    } while (!validValue);

    putchar('\n');
    printf("BOMB Placement\n");
    printf("--------------\n");
    printf("Enter the bomb positions in sets of %d where a value\n", PATH_MULTIPLE);
    printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", treasureHunt.path);

    i = 0;
    count = 0;
    for (i = 0; i < treasureHunt.path; i+=PATH_MULTIPLE)
    {

        printf("   Positions [%2d-%2d]: ", i+1, i+PATH_MULTIPLE);

        for (count = 0; count < PATH_MULTIPLE; count++)
        {
            scanf("%d", &treasureHunt.bomb[i+count]);
        }

    }

    printf("BOMB placement set\n\n");

    printf("TREASURE Placement\n");
    printf("------------------\n");
    printf("Enter the treasure placements in sets of %d where a value\n", PATH_MULTIPLE);
    printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", treasureHunt.path);

    i = 0;
    count = 0;
    for (i = 0; i < treasureHunt.path; i += PATH_MULTIPLE)
    {

        printf("   Positions [%2d-%2d]: ", i + 1, i + PATH_MULTIPLE);

        for (count = 0; count < PATH_MULTIPLE; count++)
        {
            scanf("%d", &treasureHunt.treasures[i+count]);
        }

    }

    printf("TREASURE placement set\n\n");

    printf("GAME configuration set-up is complete...\n\n");

    printf("------------------------------------\n");
    printf("TREASURE HUNT Configuration Settings\n");
    printf("------------------------------------\n");
    printf("Player:\n");
    printf("   Symbol     : %c\n", player1.symbol);
    printf("   Lives      : %d\n", player1.lives);
    printf("   Treasure   : [ready for gameplay]\n");
    printf("   History    : [ready for gameplay]\n\n");

    printf("Game:\n");
    printf("   Path Length: %d\n", treasureHunt.path);
    printf("   Bombs      : ");

    for (i = 0; i < treasureHunt.path; i++)
    {
        printf("%d", treasureHunt.bomb[i]);
    }

    putchar('\n');
    printf("   Treasure   : ");

    for (i = 0; i < treasureHunt.path; i++)
    {
        printf("%d", treasureHunt.treasures[i]);
    }

    printf("\n\n");
    printf("====================================\n");
    printf("~ Get ready to play TREASURE HUNT! ~\n");
    printf("====================================\n");

    gameOver = 0; 

    do
    { 
        putchar('\n');
        printf("  ");

        for (i = 0; i < treasureHunt.path; i++)
        {
            if (player1.history[i] != 0)
            {   

                if (treasureHunt.bomb[i] == 0 && treasureHunt.treasures[i] == 0)
                {
                    printf(".");
                }

                else if (treasureHunt.bomb[i] == 1 && treasureHunt.treasures[i] == 1)
                {
                    printf("&");
                }

                else if (treasureHunt.bomb[i] == 1 && treasureHunt.treasures[i] == 0)
                {
                    printf("!");
                }

                else
                {
                    printf("$");
                }


            }

            else
            {
                printf("-");
            }



        }

        putchar('\n');
        printf("  ");

        for (i = 0; i < treasureHunt.path; i++)
        {
            if ((i + 1) % 10)
            {
                printf("|");
            }

            else
            {
                printf("%d", (i + 1) / 10);
            }

        }

        putchar('\n');
        printf("  ");


        for (i = 0; i < treasureHunt.path; i++)
        {
            printf("%d", (i + 1) % 10);
        }

        putchar('\n');
        printf("+---------------------------------------------------+\n");
        printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n", player1.lives,
            player1.treasures, treasureHunt.maxMoves);
        printf("+---------------------------------------------------+\n");

        if ((player1.lives == 0) || (treasureHunt.maxMoves == 0))
        {
            gameOver = 1;
        }

        else
        {
            gameOver = 0; 
        }

        if (!gameOver)
        {
            validValue = 0;

            while (!validValue)
            {
                validValue = 1;

                printf("Next Move [1-%d]: ", treasureHunt.path);
                scanf("%d", &move);

                if (move < 1 || move > treasureHunt.path)
                {
                    printf("  Out of Range!!!\n");

                    validValue = 0;
                }

                else if (player1.history[move - 1] != 0)
                {
                    putchar('\n');

                    printf("===============> Dope! You've been here before!");

                    player1.history[move - 1] = 2;
                }

                else
                {
                    player1.history[move - 1] = 1;

                    treasureHunt.maxMoves -= 1;
                }

            }
            putchar('\n');

            if (player1.history[move - 1] == 1)
            {

                if (treasureHunt.bomb[move - 1] == 0 && treasureHunt.treasures[move - 1] == 0)
                {
                    printf("===============> [.] ...Nothing found here... [.]\n");
                }

                else if (treasureHunt.bomb[move - 1] == 1 && treasureHunt.treasures[move - 1] == 0)
                {
                    player1.lives -= 1;

                    printf("===============> [!] !!! BOOOOOM !!! [!]\n");
                }

                else
                {
                    player1.treasures += 1;

                    if (treasureHunt.bomb[move - 1] == 1)
                    {
                        player1.lives -= 1;

                        printf("===============> [&] !!! BOOOOOM !!! [&]\n");
                        printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n");
                    }

                    else
                    {
                        printf("===============> [$] $$$ Found Treasure! $$$ [$]\n");
                    }

                }

            }



            if (player1.lives == 0)
            {
                putchar('\n');
                printf("No more LIVES remaining!\n");
            }

            if (treasureHunt.maxMoves == 0)
            {
                putchar('\n');
                printf("No more MOVES remaining!\n");
            }

            putchar('\n');
            printf("  ");

            for (i = 0; i < move; i++)
            {
                if (i == move - 1)
                {
                    printf("%c", player1.symbol);
                }

                else
                {
                    printf(" ");
                }

            }

        }
           

    }while (!gameOver);

    putchar('\n');
    printf("##################\n");
    printf("#   Game over!   #\n");
    printf("##################\n\n");

    printf("You should play again and try to beat your score!\n\n");



    return 0;
}
