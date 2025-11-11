#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

// 栈结构定义
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// 栈操作函数声明
void initStack(Stack *s);
bool isEmpty(Stack *s);
bool isFull(Stack *s);
bool push(Stack *s, char element);
char pop(Stack *s);
char peek(Stack *s);

// 括号匹配检查函数
bool isMatchingPair(char left, char right);
int getPriority(char bracket);
bool checkBracketPriority(Stack *s, char current);
bool checkBracketMatching(char *expression);

int main() {
    char expression[100];
    int choice;
    
    printf("========== 括号配对检验程序 ==========\n");
    
    do {
        printf("\n请输入要检验的表达式: ");
        scanf("%s", expression);
        
        if (checkBracketMatching(expression)) {
            printf("? 括号匹配正确！\n");
        } else {
            printf("? 括号匹配错误！\n");
        }
        
        printf("\n是否继续检验？(1-继续, 0-退出): ");
        scanf("%d", &choice);
    } while (choice != 0);
    
    printf("程序结束，谢谢使用！\n");
    return 0;
}

// 初始化栈
void initStack(Stack *s) {
    s->top = -1;
}

// 检查栈是否为空
bool isEmpty(Stack *s) {
    return s->top == -1;
}

// 检查栈是否已满
bool isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// 入栈操作
bool push(Stack *s, char element) {
    if (isFull(s)) {
        printf("栈已满，无法入栈！\n");
        return false;
    }
    s->data[++(s->top)] = element;
    return true;
}

// 出栈操作
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("栈为空，无法出栈！\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

// 获取栈顶元素（不弹出）
char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

// 检查左右括号是否匹配
bool isMatchingPair(char left, char right) {
    if (left == '(' && right == ')') return true;
    if (left == '[' && right == ']') return true;
    if (left == '{' && right == '}') return true;
    return false;
}

// 获取括号的优先级（数值越大优先级越高）
int getPriority(char bracket) {
    switch (bracket) {
        case '(': case ')': return 1;
        case '[': case ']': return 2;
        case '{': case '}': return 3;
        default: return 0;
    }
}

// 检查括号优先级（高优先级括号不能嵌套在低优先级括号内）
bool checkBracketPriority(Stack *s, char current) {
    if (isEmpty(s)) return true;
    
    char top = peek(s);
    // 如果是左括号，检查优先级：当前括号优先级不能高于栈顶括号优先级
    if (current == '(' || current == '[' || current == '{') {
        if (getPriority(current) > getPriority(top)) {
            printf("优先级错误：'%c' 不能嵌套在 '%c' 内部\n", current, top);
            return false;
        }
    }
    return true;
}

// 检查括号匹配的主函数
bool checkBracketMatching(char *expression) {
    Stack s;
    initStack(&s);
    int length = strlen(expression);
    
    for (int i = 0; i < length; i++) {
        char current = expression[i];
        
        // 如果是左括号，检查优先级后入栈
        if (current == '(' || current == '[' || current == '{') {
            if (!checkBracketPriority(&s, current)) {
                return false;
            }
            push(&s, current);
        }
        // 如果是右括号
        else if (current == ')' || current == ']' || current == '}') {
            if (isEmpty(&s)) {
                printf("错误：右括号 '%c' 没有匹配的左括号\n", current);
                return false;
            }
            
            char top = pop(&s);
            if (!isMatchingPair(top, current)) {
                printf("错误：括号不匹配，'%c' 与 '%c'\n", top, current);
                return false;
            }
        }
    }
    
    // 检查栈中是否还有未匹配的左括号
    if (!isEmpty(&s)) {
        printf("错误：有未匹配的左括号\n");
        return false;
    }
    
    return true;
}