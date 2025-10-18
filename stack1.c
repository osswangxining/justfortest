#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define size 30

// 全局栈（避免使用指针）
char stack_data[size], ch;
char ch;
int stack_top = 0; // 栈顶索引，-1 表示空栈

// 初始化栈
void initStack()
{
    stack_top = 0;
}

// 入栈
bool push(char ch)
{
    if (stack_top >= size - 1)
    {
        return false; // 栈满
    }

    stack_data[stack_top] = ch;
    stack_top++;
    return true;
}

// 出栈
char pop()
{
    if (stack_top <= 0)
    {
        return '\0'; // 空栈返回空字符
    }
    stack_top--;
    char top_char = stack_data[stack_top];
    return top_char;
}

void check(char x, char y)
{
    if (x == '\0' || x == '#')
    {
        printf("错误：右括号多！");
        exit(0);
    }
    else
    {
        if (x != y)
        {
            printf("错误：括号不匹配！");
            exit(0);
        }
    }
}

// 主函数：读取表达式并检查括号
int main()
{
    char ch, out;
    initStack(); // 初始化全局栈
    push('#');

    printf("请输入算术表达式（以 # 结束）：\n");

    // 读取输入直到 '#'
    ch = getchar();

    while (ch != '#')
    {
        switch (ch)
        {
        case '(':
        case '[':
        case '{':
            push(ch);
            break;
        case ')':
            out = pop();
            check(out, '(');
            break;
        case ']':
            out = pop();
            check(out, '[');
            break;
        case '}':
            out = pop();
            check(out, '{');
            break;

        default:
            break;
        }

        ch = getchar();
    }
    out = pop();
    if (out == '#')
    {
        printf("括号配对正确且不交叉。\n");
    } else {
        printf("错误：左括号多\n");
    }

    return 0;
}
