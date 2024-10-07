#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define map_length 4

int map[map_length][map_length] = {0};
int flag = 0;

int random_number(){    // 随机生成2或4
    srand(time(0));
    if (rand() % 10 == 0){  // 有10分之一的概率生成4
        return 4;
    }
    else{
        return 2;
    }
}

void creat_number(){    // 随机生成数字
    srand(time(0));
    while (1)
    {   
        int x = rand() % map_length;
        int y = rand() % map_length;
        if (map[x][y] == 0){    // 判断当前位置是否可以产生数字
            map[x][y] = random_number();
            break;
        }
    }
    
}

void map_show(){
    for (int i = 0;i < map_length;i++){
        for (int j = 0;j < map_length;j++){
            printf("%5d",map[i][j],"\n");
        }
        printf("\n");
    }
}

void move_up(){     // 向上移动
    for (int i = 0;i < map_length;i++){
        int temp = 0;
        for (int j = 1;j < map_length;j++){
            if (map[j][i] != 0){
                if (map[temp][i] == 0){     // 上一格为0
                    map[temp][i] = map[j][i];
                    map[j][i] = 0;
                }
                else if (map[temp][i] == map[j][i]){    // 上一格与这一格相同
                    map[temp][i] += map[j][i];
                    map[j][i] = 0;
                }
                else{
                    map[temp+1][i] = map[j][i]; // 不为0且数字不同 自身不变
                }
                temp++;
                flag = 1;
            }
        }
    }
}

void move_down(){
    for (int i = 0;i < map_length;i++){
        int temp = map_length-1;
        for (int j = map_length-2;j >=0;j--){
            if (map[j][i] != 0){
                if (map[temp][i] == 0){     // 下一格为0
                    map[temp][i] = map[j][i];
                    map[j][i] = 0;
                }
                else if (map[temp][i] == map[j][i]){    // 下一格与这一格相同
                    map[temp][i] += map[j][i];
                    map[j][i] = 0;
                }
                else{
                    map[temp-1][i] = map[j][i]; // 不为0且数字不同 自身不变
                }
                temp--;
            }
        }
    }
}

void move_left(){
    for (int i = 0;i < map_length;i++){
        int temp = 0;
        for (int j = 1;j < map_length;j++){
            if (map[i][j] != 0){
                if (map[i][temp] == 0){     // 上一格为0
                    map[i][temp] = map[i][j];
                    map[i][j] = 0;
                }
                else if (map[i][temp] == map[i][j]){    // 上一格与这一格相同
                    map[i][temp] += map[i][j];
                    map[i][j] = 0;
                }
                else{
                    map[i][temp+1] = map[i][j]; // 不为0且数字不同 自身不变
                }
                temp++;
                flag = 1;
            }
        }
    }
}

void move_right(){
    for (int i = 0;i < map_length;i++){
        int temp = map_length-1;
        for (int j = map_length-2;j >= 0;j--){
            if (map[i][j] != 0){
                if (map[i][temp] == 0){     // 上一格为0
                    map[i][temp] = map[i][j];
                    map[i][j] = 0;
                }
                else if (map[i][temp] == map[i][j]){    // 上一格与这一格相同
                    map[i][temp] += map[i][j];
                    map[i][j] = 0;
                }
                else{
                    map[i][temp-1] = map[i][j]; // 不为0且数字不同 自身不变
                }
                temp--;
                flag = 1;
            }
        }
    }
}

void Game_init(){
    printf("wsad分别控制上下左右,q保存并退出,r读取存档\n");
    creat_number();
    creat_number(); // 开局先生成两个数字
}

void legal_move(){
    if (flag){
        creat_number();
        flag = 0;
    }
}

void Game_save(){   // 保存文件
    FILE* save_fp = fopen("./save.txt","w");
        if (save_fp == NULL){
        perror("error:");
        return;
    }
    for (int i=0;i<map_length;i++){
        for (int j=0;j<map_length;j++){
            fprintf(save_fp,"%d ",map[i][j]);
        }
    }
    fclose(save_fp);
}

void Game_read(){    // 读取文件
    FILE* fp = fopen("./save.txt","r");
    if (fp == NULL){
        perror("error:");
    }
    for (int i = 0;i < map_length;i++){
        for (int j = 0;j < map_length;j++){
                fscanf(fp,"%d ",&map[i][j]);
        }
    }
    printf("读取成功\n");
    fclose(fp);
    map_show();
}

void Game_control(){
    char key = getchar();
    switch (key)
    {
    case 'a':
    case 'A':
        move_left();
        map_show();
        break;
    case 's':
    case 'S':
        move_down();
        map_show();
        break;
    case 'd':
    case 'D':
        move_right();
        map_show();
        break;
    case 'w':
    case 'W':
        move_up();
        map_show();
        break;
    case 'q':
    case 'Q':
        Game_save();
        exit(0);
        break;    
    case 'r':
    case 'R':
        Game_read();
        break;
    }

    
}



int main(){
    Game_init();
    map_show();
    while (1)
    {
        for (int i = 0;i < map_length;i++){
            for (int j = 0;j < map_length;j++){
                if (map[i][j] == 2048){
                    printf("游戏胜利！");
                    return 0;
                }
            }
        }
        Game_control();
        legal_move();
    }
    

    return 0;
}