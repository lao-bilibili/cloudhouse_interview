#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct Stack{
    char text[MAX_SIZE]; // 记录文本
    int top;    // 记录栈顶
} Stack;

void initializeStack(Stack *s) {    // 初始化栈
    s->top = -1;
}

int isFull(Stack *s) {      // 判断栈是否为满
    return s->top == MAX_SIZE - 1;
}

int isEmpty(Stack *s) {     // 判断栈是否为空
    return s->top == -1;
}

void push(Stack *s, char value) {   // 向栈顶加入元素
    if (!isFull(s)) {
        s->text[++s->top] = value;
    } else {
        printf("栈已满\n");
    }
}

char pop(Stack *s) {    // 删除栈顶元素
    if (!isEmpty(s)) {
        return s->text[s->top--];
    } else {
        printf("栈为空\n");
        return '\0';
    }
}


void undo(Stack *textStack, Stack *undoStack) {     // 撤销
    if (!isEmpty(undoStack)) {
        char op = pop(undoStack);
        if (op == 'i') {    // 判断进行插入操作
            pop(textStack);     // 将其删除(与插入操作相反)
        } else if (op == 'd') { // 判断进行删除操作
            char ch = pop(textStack);
            push(textStack, ch); // 同上
        }
    } else {
        printf("没有可以撤销的步骤！\n");
    }
}

void insertChar(Stack *textStack, Stack *undoStack, char ch) {      // 插入文字
    push(textStack, ch);
    push(undoStack, 'i');           // 撤销标识
}

void deleteChar(Stack *textStack, Stack *undoStack) {
    if (!isEmpty(textStack)) {
        push(undoStack, 'd');       // 撤销标识
        pop(textStack);
    } else {
        printf("无法在空文本中删除！\n");
    }
}

void printText(Stack *textStack) {      // 打印文本
    int i = 0;
    while (i <= textStack->top) {
        printf("%c", textStack->text[i++]);
    }
    printf("\n");
}

int main() {
    Stack textStack, undoStack;
    initializeStack(&textStack);
    initializeStack(&undoStack);
    
    insertChar(&textStack, &undoStack, 'a');
    insertChar(&textStack, &undoStack, 'b');
    insertChar(&textStack, &undoStack, 'c');

    deleteChar(&textStack, &undoStack);

    undo(&textStack, &undoStack);
    
    printText(&textStack);

    return 0;
}