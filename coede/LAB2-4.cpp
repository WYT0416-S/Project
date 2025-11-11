#include <stdio.h>
#include <stdlib.h>

// 客户节点结构
typedef struct CustNode {
    int arrtime;      // 到达时间
    int durtime;      // 业务处理时间
    int amount;       // 业务金额（正：存款，负：取款）
    struct CustNode *next;
    int id;           // 客户ID
    int starttime;    // 开始办理时间
} CustNode;

// 队列结构
typedef struct {
    CustNode *front;
    CustNode *rear;
    int length;
} Queue;

// 全局变量
int total;           // 银行资金总额
int closetime;       // 营业时间
int N;               // 客户总数
int *stay_times;     // 存储每个客户的逗留时间
int current_time;    // 当前模拟时间
CustNode *serving_customer = NULL; // 当前正在服务的客户
int serving_end_time = -1; // 当前服务结束时间
int last_deposit_amount; // 上一个存款客户的存款前资金

// 函数声明
void initQueue(Queue *q);
int isEmptyQueue(Queue *q);
void enqueue(Queue *q, CustNode *cust);
CustNode *dequeue(Queue *q);
void freeQueue(Queue *q);
CustNode *createCustomer(int arrtime, int amount, int id);
void processCustomer(Queue *q1, Queue *q2);
void checkQueue2(Queue *q2, int original_total);

int main() {
    // 读取第一行输入
    printf("请输入客户总数、银行初始资金总额和营业时间: ");
    scanf("%d %d %d", &N, &total, &closetime);
    
    // 分配存储逗留时间的数组
    stay_times = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        stay_times[i] = 0;
    }
    
    // 初始化队列
    Queue queue1, queue2;
    initQueue(&queue1);
    initQueue(&queue2);
    
    // 读取客户数据
    printf("请输入%d个客户的业务金额和到达时间:\n", N);
    CustNode **customers = (CustNode **)malloc(N * sizeof(CustNode *));
    for (int i = 0; i < N; i++) {
        int amount, arrtime;
        scanf("%d %d", &amount, &arrtime);
        customers[i] = createCustomer(arrtime, amount, i);
    }
    
    // 初始化变量
    current_time = 0;
    last_deposit_amount = total;
    
    // 模拟循环
    for (current_time = 0; current_time <= closetime; current_time++) {
        // 检查是否有客户到达
        for (int i = 0; i < N; i++) {
            if (customers[i]->arrtime == current_time) {
                enqueue(&queue1, customers[i]);
            }
        }
        
        // 检查当前服务是否结束
        if (serving_customer != NULL && current_time == serving_end_time) {
            // 更新银行资金
            total += serving_customer->amount;
            
            // 如果是存款业务，检查队列2
            if (serving_customer->amount > 0) {
                last_deposit_amount = total - serving_customer->amount; // 存款前的资金
                checkQueue2(&queue2, last_deposit_amount);
            }
            
            serving_customer = NULL;
            serving_end_time = -1;
        }
        
        // 如果当前没有客户在服务，尝试从队列1中取客户
        if (serving_customer == NULL && !isEmptyQueue(&queue1)) {
            processCustomer(&queue1, &queue2);
        }
    }
    
    // 处理营业结束时仍在队列中的客户
    while (!isEmptyQueue(&queue1)) {
        CustNode *cust = dequeue(&queue1);
        stay_times[cust->id] = closetime - cust->arrtime;
    }
    
    while (!isEmptyQueue(&queue2)) {
        CustNode *cust = dequeue(&queue2);
        stay_times[cust->id] = closetime - cust->arrtime;
    }
    
    // 输出每个客户的逗留时间
    printf("\n客户逗留时间:\n");
    for (int i = 0; i < N; i++) {
        printf("%d\n", stay_times[i]);
    }
    
    // 计算并输出平均逗留时间
    int total_stay_time = 0;
    for (int i = 0; i < N; i++) {
        total_stay_time += stay_times[i];
    }
    if (N > 0) {
        printf("\n平均逗留时间: %d\n", total_stay_time / N);
    } else {
        printf("\n平均逗留时间: 0\n");
    }
    
    // 释放内存
    free(stay_times);
    free(customers);
    freeQueue(&queue1);
    freeQueue(&queue2);
    
    return 0;
}

// 队列操作函数
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
    q->length = 0;
}

int isEmptyQueue(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, CustNode *cust) {
    cust->next = NULL;
    if (isEmptyQueue(q)) {
        q->front = q->rear = cust;
    } else {
        q->rear->next = cust;
        q->rear = cust;
    }
    q->length++;
}

CustNode *dequeue(Queue *q) {
    if (isEmptyQueue(q)) {
        return NULL;
    }
    CustNode *cust = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    q->length--;
    cust->next = NULL;
    return cust;
}

void freeQueue(Queue *q) {
    while (!isEmptyQueue(q)) {
        CustNode *cust = dequeue(q);
        free(cust);
    }
}

// 客户操作函数
CustNode *createCustomer(int arrtime, int amount, int id) {
    CustNode *cust = (CustNode *)malloc(sizeof(CustNode));
    cust->arrtime = arrtime;
    cust->durtime = 10; // 固定业务处理时间
    cust->amount = amount;
    cust->next = NULL;
    cust->id = id;
    cust->starttime = -1; // 初始化为-1，表示尚未开始办理
    return cust;
}

void processCustomer(Queue *q1, Queue *q2) {
    if (isEmptyQueue(q1)) {
        return;
    }
    
    CustNode *cust = q1->front;
    
    if (cust->amount > 0) { // 存款业务
        // 直接处理
        dequeue(q1);
        serving_customer = cust;
        serving_end_time = current_time + cust->durtime;
        cust->starttime = current_time;
        // 逗留时间 = 开始办理时间 - 到达时间（只计算等待时间）
        stay_times[cust->id] = current_time - cust->arrtime;
    } else { // 取款业务
        if (total >= -cust->amount) { // 资金足够
            // 直接处理
            dequeue(q1);
            serving_customer = cust;
            serving_end_time = current_time + cust->durtime;
            cust->starttime = current_time;
            // 逗留时间 = 开始办理时间 - 到达时间（只计算等待时间）
            stay_times[cust->id] = current_time - cust->arrtime;
        } else { // 资金不足，排入队列2
            dequeue(q1);
            enqueue(q2, cust);
        }
    }
}

void checkQueue2(Queue *q2, int original_total) {
    int checked_count = 0;
    int queue_length = q2->length;
    
    while (checked_count < queue_length && total > original_total) {
        CustNode *cust = dequeue(q2);
        
        if (total >= -cust->amount) { // 可以满足
            // 立即处理这个客户
            serving_customer = cust;
            serving_end_time = current_time + cust->durtime;
            cust->starttime = current_time;
            // 逗留时间 = 开始办理时间 - 到达时间（只计算等待时间）
            stay_times[cust->id] = current_time - cust->arrtime;
            break; // 只处理一个客户，然后返回
        } else { // 仍不满足，重新排入队尾
            enqueue(q2, cust);
        }
        
        checked_count++;
    }
}