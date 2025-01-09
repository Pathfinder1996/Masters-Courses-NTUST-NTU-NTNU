#include <stdio.h>
#include <string.h>

int main() {
    int x, y;
    scanf("%d %d", &x, &y);

    int init_x, init_y;
    char init_dir;
    char instruction[101];
    char directions[4] = {'N', 'E', 'S', 'W'};
    int x_move[4] = {0, 1, 0, -1}; // F x軸動東 西
    int y_move[4] = {1, 0, -1, 0}; // F y軸動北 南
    int record[51][51] = {0}; //記錄lost位置
    while(scanf("%d %d %c", &init_x, &init_y, &init_dir) != EOF) {
        scanf("%s", instruction);

        int current_dir_index = 0;
        int i;
        for (i = 0; i < 4; i++) {
            if (directions[i] == init_dir) {
                current_dir_index = i;
                // printf("%c", directions[current_dir_index]);
                break;
            }
        }

        int str_len = strlen(instruction);
        int robot_lost = 0;
        for (i = 0; i < str_len; i++) {
            // printf("%c", instruction[i]);
            if (instruction[i] == 'L') {
                current_dir_index = (current_dir_index + 3) % 4;
            }
            else if (instruction[i] == 'R') {
                current_dir_index = (current_dir_index + 1) % 4;
            }
            else if (instruction[i] == 'F') {
                int current_x = init_x + x_move[current_dir_index];
                int current_y = init_y + y_move[current_dir_index];

                if (current_x < 0 || current_y < 0 || current_x > x || current_y > y) {
                    if (record[init_x][init_y] == 0) {
                        record[init_x][init_y] = 1;
                        robot_lost = 1;
                        break;
                    }
                }
                else {
                    init_x = current_x;
                    init_y = current_y;
                }
            }
        }

        printf("%d %d %c", init_x, init_y, directions[current_dir_index]);
        if (robot_lost) {
            printf(" LOST");
        }
        printf("\n");
    }

    return 0;
}
