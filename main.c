#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure for soldiers with two integer data members
struct Soldier {
    int health;
    int strength;
};

// Structure for the stack data structure
struct Stack {
    struct Soldier *data;
    int size;
    int capacity;
};

// Function used to create a stack data structure
struct Stack *createStack(int capacity) {
    struct Stack *stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->size = 0;
    stack->data = (struct Soldier *) malloc(sizeof(struct Soldier) * capacity);
    return stack;
}

// Function to add a soldier to the stack
void push(struct Stack *stack, struct Soldier soldier) {
    if (stack->size < stack->capacity) {
        stack->data[stack->size] = soldier;
        stack->size++;
    } else {
        printf("Stack is full, soldier cannot be added.\n");
    }
}

// Function to remove a soldier from the stack
struct Soldier pop(struct Stack *stack) {
    if (stack->size > 0) {
        stack->size--;
        return stack->data[stack->size];
    } else {
        printf("Stack is empty, soldier cannot be removed.\n");
        struct Soldier emptySoldier = {0, 0};
        return emptySoldier;
    }
}

// Function to manage the battle between two sides
void battle(struct Stack *side1, struct Stack *side2, int *turn) {
    struct Soldier soldier1 = pop(side1);
    struct Soldier soldier2 = pop(side2);

    int damage = (soldier1.strength - soldier2.strength) * 0.05 + 50;
    printf("%d hit %d damage\n", *turn, damage);

    soldier2.health -= damage;

    if (soldier2.health <= 0) {
        printf("1 has a casualty\n");
    } else {
        push(side2, soldier2);
    }
}

int main() {
    // Seed the random number generator with the current time.
    srand(time(NULL));

    // Create two stacks for side 1 and side 2, each with a capacity of 10 soldiers.
    struct Stack *side1 = createStack(10);
    struct Stack *side2 = createStack(10);



    // Open the "commands.txt" file for reading.
    FILE *file = fopen("commands.txt", "r");
    if (file == NULL) {
        // Print an error message and exit if the file couldn't be opened.
        printf("File couldn't be opened.\n");
        return 1;
    }

    // Define a character array to store each line from the file.
    char line[256];
    int turn = 1;

    // Read each line from the file and process the commands.
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "A", 1) == 0) {
            int side;
            int result = sscanf(line, "A %d", &side);
            if (result != 1) {
                // Print an error message if the command format is invalid and continue to the next line.
                printf("Invalid command format.\n");
                continue;
            }

            // Print a message indicating soldiers are being added to the specified side.
            printf("add soldiers to side %d\n", side);

            // Extract soldier data from the line and add them to the corresponding side's stack.
            char *data = strchr(line, ';');
            if (data != NULL) {
                data++;
                char *token = strtok(data, ";");
                while (token != NULL) {
                    int h, s;
                    sscanf(token, "%d,%d", &h, &s);
                    struct Soldier newSoldier = {h, s};
                    push(side == 1 ? side1 : side2, newSoldier);
                    // Print the health and strength of each added soldier.
                    printf("S- H: %d S: %d\n", h, s);
                    token = strtok(NULL, ";");
                }
            }
        } else if (strncmp(line, "F", 1) == 0) {
            if (turn == 1) {
                battle(side1, side2, &turn);
            } else {
                battle(side2, side1, &turn);
            }
            turn = 3 - turn; // Switch turns between 1 and 2
        } else if (strncmp(line, "R", 1) == 0) {
            int side;
            int result = sscanf(line, "R %d", &side);
            if (result != 1) {
                // Print an error message if the command format is invalid and continue to the next line.
                printf("Invalid command format.\n");
                continue;
            }

            // Print a message indicating reinforcements are called to the specified side.
            printf("Called reinforcements to side %d\n", side);

            // Generate random properties for the new soldier and add them to the specified side's stack.
            int random_health = rand() % 101;    // Random health value between 0 and 100.
            int random_strength = rand() % 101;  // Random strength value between 0 and 100.
            struct Soldier newSoldier = {random_health, random_strength};
            push(side == 1 ? side1 : side2, newSoldier);

            // Print the health and strength of the added soldier.
            printf("S- H: %d S: %d\n", random_health, random_strength);
        } else if (strncmp(line, "C", 1) == 0) {
            printf("Critical shot\n");
            // Check which side to target and perform the critical hit.
            if (turn == 1) {
                if (side2->size > 0) {
                    pop(side2);
                    printf("1 has a casualty\n");
                } else {
                    printf("Critical hit failed. Target side is already empty.\n");
                }
            } else {
                if (side1->size > 0) {
                    pop(side1);
                    printf("2 has a casualty\n");
                } else {
                    printf("Critical hit failed. Target side is already empty.\n");
                }
            }
        }
    }

    // Close the file.
    fclose(file);

    // Free memory allocated for both stacks and their soldier data.
    free(side1->data);
    free(side1);
    free(side2->data);
    free(side2);

    return 0;
}
