#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// 数字栈（操作数栈）
int num_stack[MAX_SIZE];
int num_top = -1;

// 运算符栈
char op_stack[MAX_SIZE];
int op_top = -1;

// 初始化栈
void initStacks() {
    num_top = -1;
    op_top = -1;
}

// 数字栈操作
bool pushNum(int n) {
    if (num_top >= MAX_SIZE - 1) return false;
    num_top++;
    num_stack[num_top] = n;
    return true;
}

int popNum() {
    if (num_top == -1) return 0;
    int val = num_stack[num_top];
    num_top--;
    return val;
}

bool isNumStackEmpty() {
    return num_top == -1;
}

// 运算符栈操作
bool pushOp(char op) {
    if (op_top >= MAX_SIZE - 1) return false;
    op_top++;
    op_stack[op_top] = op;
    return true;
}

char popOp() {
    if (op_top == -1) return '\0';
    char op = op_stack[op_top];
    op_top--;
    return op;
}

bool isOpStackEmpty() {
    return op_top == -1;
}

// 计算 a op b
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;      // 整数除法
        case '^': {
            int result = 1;
            for (int i = 0; i < b; i++) {
                result *= a;
            }
            return result;
        }
        default: return 0;
    }
}

// 获取运算符优先级（数字越大优先级越高）
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0; // 括号等
}

// 处理栈中运算符直到遇到 '(' 或栈空
void processOperators() {
    while (!isOpStackEmpty()) {
        char op = op_stack[op_top];
        if (op == '(') break;
        // 弹出两个操作数和一个运算符进行计算
        int b = popNum();
        int a = popNum();
        char op_char = popOp();
        int result = applyOp(a, b, op_char);
        pushNum(result);
    }
}

// 主函数
int main() {
    initStacks();
    char ch;
    printf("请输入算术表达式（以 # 结束，操作数为一位数字）：\n");

    ch = getchar();
    while (ch != '#') {
        if (ch >= '0' && ch <= '9') {
            // 数字直接入数字栈
            pushNum(ch - '0');
        }
        else if (ch == '(') {
            // 左括号直接入运算符栈
            pushOp(ch);
        }
        else if (ch == ')') {
            // 遇到右括号，计算直到左括号
            while (!isOpStackEmpty() && op_stack[op_top] != '(') {
                int b = popNum();
                int a = popNum();
                char op = popOp();
                int res = applyOp(a, b, op);
                pushNum(res);
            }
            // 弹出左括号
            if (!isOpStackEmpty()) {
                popOp(); // 弹出 '('
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            // 处理运算符优先级
            while (!isOpStackEmpty() && op_stack[op_top] != '(' &&
                   getPrecedence(op_stack[op_top]) >= getPrecedence(ch)) {
                int b = popNum();
                int a = popNum();
                char op = popOp();
                int res = applyOp(a, b, op);
                pushNum(res);
            }
            pushOp(ch);
        }
        // 忽略其他字符（本题无空格，可不处理）
        ch = getchar();
    }

    // 处理剩余运算符
    while (!isOpStackEmpty()) {
        int b = popNum();
        int a = popNum();
        char op = popOp();
        int res = applyOp(a, b, op);
        pushNum(res);
    }

    // 最终结果在数字栈顶
    int result = popNum();
    printf("表达式结果: %d\n", result);

    return 0;
}
