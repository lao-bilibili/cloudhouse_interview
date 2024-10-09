#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENT 100

typedef struct Student
{    
    char Name[20];  // 姓名
    int ID;     // 学号
    int Age;    // 年龄
    int Class;  // 班级
    int Score;  // 分数
}Student;

Student student[MAX_STUDENT]; // 学生列表储存在这
int num_student = 0;    // 目前学生数据总数

void save_student(){    // 保存学生数据
    FILE *fp = fopen("./save.dat","wb");
    if (fp == NULL){
        printf("文件打开错误！");
        return;
    }

    fwrite(student,sizeof(Student),num_student,fp);
    fclose(fp);
}

void load_student(){    // 读取学生数据
    FILE *fp = fopen("./save.dat", "rb");
    if (fp == NULL){
        printf("文件打开错误！");
        return;
    }

    while (fread(&student[num_student],sizeof(Student), 1, fp))
    {
        num_student++;
    }
    printf("文件读取成功！\n");

    fclose(fp);
}

void print_student(){   // 打印所有学生
    printf("学生名单如下\n");
    for (int i = 0;i < num_student;i++){
        printf("学号: %d, 姓名: %s, 年龄: %d, 班级: %d, 分数: %d\n",student[i].ID, student[i].Name, student[i].Age, student[i].Class, student[i].Score);
    }
}

void add_student(){     // 添加学生数据
    Student *p = &student[num_student];     // 判断列表是否填满溢出
    if (num_student >= MAX_STUDENT){
        printf("无法再添加更多学生！");
        return;
    }
    printf("请输入学号：");
    scanf("%d",&p->ID);
    printf("请输入姓名：");
    scanf("%s",&p->Name);
    printf("请输入年龄：");
    scanf("%d",&p->Age);
    printf("请输入班级：");
    scanf("%d",&p->Class);
    printf("请输入分数：");
    scanf("%d",&p->Score);
    num_student++;
    save_student();
    printf("添加成功！\n");
}

void delete_student(){  // 删除学生数据
    int id;
    int found = -1;
    printf("请输入学号以删除数据");
    scanf("%d",&id);
    for (int i = 0;i < num_student;i++){
        if (student[i].ID == id){
            found = i;
            break;
        }
    }
    if (found != -1){
        for (int i = found;i < num_student;i++){
            student[i] = student[i+1];
        }        
        num_student--;
        save_student();
        printf("删除成功！\n");
    }
    else{
        printf("找不到该学生！\n");
        return;
    }

}

void update_student(){  // 修改学生数据
    int id;
    printf("请输入学号以修改学生数据");
    scanf("%d",&id);
    
    for (int i = 0;i < num_student;i++){
        if (student[i].ID == id){
            Student *p = &student[i];
            printf("请输入学号：");
            scanf("%d",&p->ID);
            printf("请输入姓名：");
            scanf("%s",&p->Name);
            printf("请输入年龄：");
            scanf("%d",&p->Age);
            printf("请输入班级：");
            scanf("%d",&p->Class);
            printf("请输入分数：");
            scanf("%d",&p->Score);
            save_student();
            return;
        }
    }
}

void query_student(){   // 查找学生数据
    printf("输入1 按姓名查找\n输入2 按照学号查找");  
    int key;    
    scanf("%d",&key);        
    char name[20];
    int id;
 
    switch (key)
    {
    case 1:
        printf("请输入学生姓名：");
        scanf("%s",&name);
        for (int i = 0;i < num_student;i++){
            if (strcmp(student[i].Name, name) == 0){
                printf("查询成功\n");
                printf("ID: %d, Name: %s, Age: %d, Class: %d, Score: %d\n",
                student[i].ID, student[i].Name, student[i].Age, student[i].Class, student[i].Score);
                return;
            }
        }
        printf("查询失败：没有符合该条件的学生");
        return;
        break;
    case 2:
        printf("请输入学号：");
        scanf("%d",&id);
        for (int i = 0;i < num_student;i++){
            if (student[i].ID == id){
                printf("查询成功\n");
                printf("ID: %d, Name: %s, Age: %d, Class: %d, Score: %d\n",
                student[i].ID, student[i].Name, student[i].Age, student[i].Class, student[i].Score);
                return;
            }
        }
        printf("查询失败：没有符合该条件的学生");
        return;
        break;
    }
}

void sort_student(){    // 排序学生数据
    printf("输入1 按照成绩排序\n输入2 按照年龄排序\n输入3 按照学号排序\n");
    int key;
    scanf("%d",&key);
    switch (key)
    {
    case 1:     // 均使用冒泡排序 成绩
        for (int i = 0;i < num_student - 1;i++){
            for (int j = 0; j < num_student - 1 - i; j++){   
                if (student[j].Score > student[j+1].Score){
                    Student temp = student[j];
                    student[j] = student[j+1];
                    student[j+1] = temp;
                }
            }
        }
        save_student();
        print_student();
        break;
    
    case 2:     // 年龄
        for (int i = 0;i < num_student - 1;i++){
                for (int j = 0;j < num_student - 1 - i;j++){
                    if (student[j].Age > student[j+1].Age){
                    Student temp = student[j];
                    student[j] = student[j+1];
                    student[j+1] = temp;
                }
            }
        }
        save_student();
        print_student();
        break;
    
    case 3:     // 学号
        for (int i = 0;i < num_student - 1;i++){
                for (int j = 0;j < num_student - 1 - i;j++){
                    if (student[j].ID > student[j+1].ID){
                    Student temp = student[j];
                    student[j] = student[j+1];
                    student[j+1] = temp;
                }
            }
        }
        save_student();
        print_student();
        break;
    }
}

void control(){
    int key;
    scanf("%d",&key);
    switch (key)
    {
    case 1:
        print_student();
        break;
    case 2:
        add_student();
        break;
    case 3:
        delete_student();
        break;
    case 4:
        update_student();
        break;
    case 5:
        query_student();
        break;
    case 6:
        sort_student();
        break;
    case 7:
        load_student();
        break;
    case 8:
        save_student();
        break;
    case 9:
        exit(0);
        break;
    }
}

int main(){
    printf( "输入1 打印所有学生\n"
            "输入2 添加学生数据\n"
            "输入3 删除学生数据\n"
            "输入4 修改学生数据\n"
            "输入5 查找学生数据\n"
            "输入6 排序学生数据\n"
            "输入7 加载学生数据\n"
            "输入8 保存学生数据\n"
            "输入9 退出\n");    
    while (1)
    {
        control();
    }
    
    return 0;
}