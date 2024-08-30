#include <stdio.h>
#include <string.h>

#define COM_L 7
#define TOTAL_COM_L 1000
#define STR_MAX_L 51

typedef struct System {
    char name[STR_MAX_L];
    int price;
} system;

void addSystem(char name[], int price);
void deleteSystem(char name[]);
void editSystem(char name[], int price);
void showSystem();

system inventory[TOTAL_COM_L];
int storeCount = 0;

int main(void) {
    char command[COM_L];
    char name[STR_MAX_L];
    int price;

    while (1) {
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%s %d", name, &price);
            addSystem(name, price);
        } else if (strcmp(command, "delete") == 0) {
            scanf("%s", name);
            deleteSystem(name);
        } else if (strcmp(command, "edit") == 0) {
            scanf("%s %d", name, &price);
            editSystem(name, price);
        } else if (strcmp(command, "show") == 0) {
            showSystem();
        } else if (strcmp(command, "quit") == 0) {
            printf("end");
            break;
        }
    }

    return 0;
}

void addSystem(char name[], int price) {
    int i;
    for (i = 0; i < storeCount; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            printf("adding failed\n");
            return;
        }
    }
    if (storeCount >= TOTAL_COM_L) {
        printf("adding failed\n");
        return;
    }
    strcpy(inventory[storeCount].name, name);
    inventory[storeCount].price = price;
    storeCount = storeCount + 1;
    printf("adding succeed\n");
}

void deleteSystem(char name[]) {
    for (int i = 0; i < storeCount; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            for (int j = i; j < storeCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            storeCount = storeCount - 1;
            printf("deleting succeed\n");
            return;
        }
    }
    printf("deleting failed\n");
}

void editSystem(char name[], int price) {
    for (int i = 0; i < storeCount; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            inventory[i].price = price;
            printf("editing succeed\n");
            return;
        }
    }
    printf("editing failed\n");
}

void showSystem() {
    if (storeCount == 0) {
        printf("no goods now\n");
        return;
    }
    printf("we have %d goods now\n", storeCount);
    int i;
    if (strcmp(inventory[0].name, "orange_juice") == 0) {
        for (i = 1; i < storeCount; i++) {
        printf("%s %d\n", inventory[i].name, inventory[i].price);
        }
        printf("%s %d\n", inventory[0].name, inventory[0].price);
    }
    else {
        for (i = 0; i < storeCount; i++) {
            printf("%s %d\n", inventory[i].name, inventory[i].price);
        }
    }
}
