#include <stdio.h>
#include <string.h>
#include <time.h> // For tracking time

void showInstructions()
{
    printf("Instructions:\n");
    printf("Type 'look' to see your surroundings.\n");
    printf("Type 'go [direction]' to move (north, south, east, west).\n");
    printf("Type 'take [item]' to pick up an item.\n");
    printf("Type 'exit' to quit the game.\n");
}

// Function for the puzzle guarding the key
int solvePuzzle()
{
    char answer[100];
    printf("\nAs you reach for the key, a mysterious voice echoes in the room...\n");
    printf("'To claim the key and be free, you must answer me this riddle: '\n");
    printf("'I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?'\n");
    printf("\nYour answer: ");

    fgets(answer, sizeof(answer), stdin);
    answer[strcspn(answer, "\n")] = 0; // Remove newline

    if (strcmp(answer, "echo") == 0)
    {
        printf("\nThe voice fades away and the key is now within your grasp.\n");
        return 1;
    }
    else
    {
        printf("\nThe voice booms: 'That is not the answer! The key remains out of reach.'\n");
        return 0;
    }
}

int main()
{
    char command[100];
    int hasKey = 0; // Item to be collected
    int gameWon = 0;
    char currentRoom[20] = "start"; // Track the player's current location
    time_t startTime, currentTime;
    int timeLimit = 120; // Time limit in seconds

    printf("Welcome to the Adventure Game!\n");
    showInstructions();

    // Start the timer
    time(&startTime);

    while (!gameWon)
    {
        // Check how much time has passed
        time(&currentTime);
        if (difftime(currentTime, startTime) > timeLimit)
        {
            printf("\nTime's up! You failed to escape in time. Game over!\n");
            break;
        }

        printf("\nYou have %.0f seconds left.\n", timeLimit - difftime(currentTime, startTime));
        printf("\nYou are in the %s room.\n", currentRoom);
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline

        if (strcmp(command, "look") == 0)
        {
            if (strcmp(currentRoom, "start") == 0)
            {
                printf("You are in a dark room. There is a door to the north.\n");
                printf("Other exits lead to the east, west, and south.\n");
            }
            else if (strcmp(currentRoom, "north") == 0)
            {
                if (!hasKey)
                {
                    printf("The door is locked. You need to find a key.\n");
                }
                else
                {
                    printf("The door is unlocked. You can go through it.\n");
                }
            }
            else if (strcmp(currentRoom, "east") == 0)
            {
                printf("You see a key on the ground, but it is guarded by something mysterious.\n");
            }
            else if (strcmp(currentRoom, "west") == 0)
            {
                printf("The room is empty, but you feel a strange presence.\n");
            }
            else if (strcmp(currentRoom, "south") == 0)
            {
                printf("The walls are covered in eerie messages, but none of them make sense.\n");
            }
        }
        else if (strncmp(command, "go ", 3) == 0)
        {
            if (strcmp(command + 3, "north") == 0)
            {
                if (strcmp(currentRoom, "start") == 0 || strcmp(currentRoom, "east") == 0 || strcmp(currentRoom, "west") == 0 || strcmp(currentRoom, "south") == 0)
                {
                    if (hasKey)
                    {
                        printf("You unlock the door and go through it. You win!\n");
                        gameWon = 1;
                    }
                    else
                    {
                        strcpy(currentRoom, "north");
                        printf("The door is locked. You need to find a key.\n");
                    }
                }
            }
            else if (strcmp(command + 3, "east") == 0)
            {
                strcpy(currentRoom, "east");
                printf("You enter the room to the east. You see a key.\n");
            }
            else if (strcmp(command + 3, "west") == 0)
            {
                strcpy(currentRoom, "west");
                printf("You enter the room to the west. It's empty and unsettling.\n");
            }
            else if (strcmp(command + 3, "south") == 0)
            {
                strcpy(currentRoom, "south");
                printf("You enter the room to the south. It's full of cryptic writings.\n");
            }
            else
            {
                printf("Unknown direction. Try 'go north', 'go east', 'go west', or 'go south'.\n");
            }
        }
        else if (strncmp(command, "take ", 5) == 0)
        {
            if (strcmp(command + 5, "key") == 0 && strcmp(currentRoom, "east") == 0 && !hasKey)
            {
                if (solvePuzzle())
                {
                    hasKey = 1;
                    printf("You took the key! Now you can go north to escape.\n");
                }
                else
                {
                    printf("The key remains unreachable. You must solve the puzzle to claim it.\n");
                }
            }
            else if (hasKey)
            {
                printf("You already have the key.\n");
            }
            else
            {
                printf("There is nothing to take here.\n");
            }
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Thanks for playing!\n");
            break;
        }
        else
        {
            printf("Unknown command. Try 'look', 'go [direction]', or 'take [item]'.\n");
        }
    }

    return 0;
}
