#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 4

// 队列存储
int queue_data[MAX_SIZE];
int front = 0;      // 队头索引
int rear = 0;       // 队尾索引
int count = 0;      // 元素个数

// 全局变量：用于 dequeue 返回值（避免指针）
int global_dequeued_value = 0;

// 初始化队列
void initQueue() {
    front = 0;
    rear = 0;
    count = 0;
}

// 判断队列是否为空
bool isEmpty() {
    return count == 0;
}

// 判断队列是否已满
bool isFull() {
    return count == MAX_SIZE;
}

// 入队
bool enqueue(int value) {
    if (isFull()) {
        printf("【警告】队列已满，无法入队 %d！\n", value);
        return false;
    }
    queue_data[rear] = value;
    rear = (rear + 1) % MAX_SIZE;
    count++;
    return true;
}

// 出队（通过全局变量返回值）
bool dequeue() {
    if (isEmpty()) {
        printf("【警告】队列为空，无法出队！\n");
        return false;
    }
    global_dequeued_value = queue_data[front];
    front = (front + 1) % MAX_SIZE;
    count--;
    return true;
}

// 获取最后一次出队的值
int getLastDequeuedValue() {
    return global_dequeued_value;
}

// 打印队列内容 + 内部状态 (front, rear, count)
void printQueue() {
    printf("  队列数据: [");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (i > 0) printf(", ");
        printf("%d", queue_data[i]);
    }
    printf("]\n");
    
    if (isEmpty()) {
        printf("  队列状态: 空\n");
    } else {
        printf("  队列状态: [");
        int i = front;
        for (int j = 0; j < count; j++) {
            printf("%d", queue_data[i]);
            if (j < count - 1) printf(", ");
            i = (i + 1) % MAX_SIZE;
        }
        printf("] (队头→队尾)\n");
    }
    printf("  front=%d, rear=%d, count=%d\n", front, rear, count);
}

// 主函数：演示先进先出（FIFO）
int main() {
    initQueue();

    printf("=== 队列 FIFO 演示（显示 front/rear/count）===\n");
    printf("队列容量: %d\n\n", MAX_SIZE);

    // 入队 5, 7, 9
    printf("▶ 入队 5\n");
    enqueue(5);
    printQueue();

    printf("\n▶ 入队 7\n");
    enqueue(7);
    printQueue();

    printf("\n▶ 入队 9\n");
    enqueue(9);
    printQueue();

    // 出队
    printf("\n▶ 出队\n");
    if (dequeue()) {
        printf("  出队元素: %d\n", getLastDequeuedValue());
        printQueue();
    }

    printf("\n▶ 出队\n");
    if (dequeue()) {
        printf("  出队元素: %d\n", getLastDequeuedValue());
        printQueue();
    }

    // 入队 6
    printf("\n▶ 入队 6\n");
    enqueue(6);
    printQueue();

    // 出队
    printf("\n▶ 出队\n");
    if (dequeue()) {
        printf("  出队元素: %d\n", getLastDequeuedValue());
        printQueue();
    }

    // 入队 8
    printf("\n▶ 入队 8\n");
    enqueue(8);
    printQueue();

    // 连续出队
    printf("\n▶ 出队\n");
    if (dequeue()) {
        printf("  出队元素: %d\n", getLastDequeuedValue());
        printQueue();
    }

    printf("\n▶ 出队\n");
    if (dequeue()) {
        printf("  出队元素: %d\n", getLastDequeuedValue());
        printQueue();
    }

    // 最后入队 5
    printf("\n▶ 入队 5\n");
    enqueue(5);
    printQueue();

    return 0;
}
