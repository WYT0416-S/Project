4.17 int Replace(&S,T,V){
    while(Index(S,T,pos)){
        S[pos...Strlength(V)]=V[0...Strlength]
    }
    return 1;
}
4.21 
typedef struct Node {
    char ch;
    struct Node *next;
} Node;

typedef struct LString {
    Node *head; 
    int len;    
} LString;


void StrAssign(LString &S, char *chars) { 
    Node *p = S.head;
    while (*chars != '\0') {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->ch = *chars;
        newNode->next = NULL;
        p->next = newNode;
        p = newNode;
        S.len++;
        chars++;
    }
}
void StrCopy(LString &S, LString T) {   
    while (S.head->next != NULL) {
        Node *temp = S.head->next;
        S.head->next = temp->next;
        free(temp);
    }
    S.len = 0;
    Node *p = T.head->next;
    Node *tail = S.head;
    while (p != NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->ch = p->ch;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        S.len++;
        p = p->next;
    }
}


int StrCompare(LString S, LString T) {
    Node *p = S.head->next, *q = T.head->next;
    while (p != NULL && q != NULL) {
        if (p->ch != q->ch) {
            return p->ch - q->ch;
        }
        p = p->next;
        q = q->next;
    }
    return (S.len - T.len); 
}


int StrLength(LString S) {
    return S.len;
}


void Concat(LString &S, LString T) {
    Node *tail = S.head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    
    Node *p = T.head->next;
    while (p != NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->ch = p->ch;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        S.len++;
        p = p->next;
    }
}


bool SubString(LString &Sub, LString S, int pos, int len) {
    if (pos < 1 || pos > S.len || len < 0 || len > S.len - pos + 1) {
        return false; 
    
    
    while (Sub.head->next != NULL) {
        Node *temp = Sub.head->next;
        Sub.head->next = temp->next;
        free(temp);
    }
    Sub.len = 0;
    
    
    Node *p = S.head->next;
    for (int i = 1; i < pos; i++) {
        p = p->next;
    }
    
 
    Node *tail = Sub.head;
    while (len-- > 0 && p != NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->ch = p->ch;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        Sub.len++;
        p = p->next;
    }
    
    return true;
}
4.23
int IsSymmetric(LString s) {
    Block *head = s.head;
    Block *tail = s.tail;
    while (head != tail && head->next != tail) {
        for (int i = 0; i < 3; i++) {
            if (head->ch[i] != tail->ch[2 - i]) {
                return 0;
            }
        }
        Block *temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        head = head->next;
        tail = temp;
    }

    if (head == tail) {
        for (int i = 0; i < 3; i++) {
            if (head->ch[i] != '\0') {
                return 0;
            }
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (head->ch[i] != tail->ch[2 - i]) {
                return 0;
            }
        }
    }
    return 1;
}//复杂度位O（StrLength(S)）
//5.8
//当 j = i - 1时，在一维数组 B中的索引 k = 4(i - 1) - 1。

//当 j = i时，在一维数组 B中的索引 k = 4(i - 1)。

//当 j = i + 1时，在一维数组 B中的索引 k = 4(i - 1) + 1。
//5.26
// 定义十字链表结点结构
typedef struct OLNode {
    int row;            
    int col;            
    int value;         
    struct OLNode *right;  
    struct OLNode *down;   
} OLNode, *OLink;


typedef struct {
    int rows;           
    int cols;          
    OLink *rhead;       // 行头指针数组，rhead[i] 指向第 i 行的第一个非零元素
    OLink *chead;       // 列头指针数组，chead[j] 指向第 j 列的第一个非零元素
} CrossList;


void PrintTriple_CrossList(CrossList M) {
    if (M.rows <= 0 || M.cols <= 0) {
        return;  // 若矩阵行数或列数不合法，直接返回
    }

    // 遍历每一行
    for (int i = 1; i <= M.rows; i++) {
        OLink p = M.rhead[i];  // 获取第 i 行的第一个非零元素
        while (p != NULL) {
            // 输出三元组 (行下标, 列下标, 元素值)
            printf("(%d, %d, %d)\n", p->row, p->col, p->value);
            p = p->right;  // 移动到同一行的下一个非零元素
        }
    }
}






//5.30
// 广义表节点定义
typedef struct GLNode {
    int tag; // 0:原子，1:子表
    union {
        char atom; // 原子值（假设为char类型）
        struct {
            struct GLNode *hp; // 表头指针
            struct GLNode *tp; // 表尾指针
        } ptr;
    };
} GLNode, *GList;

int GlistDepth(GList L) {
    if (L == NULL) return 1; // 空表深度为1
    if (L->tag == 0) return 0; // 原子深度为0
    
    int max_depth = 0;
    GList p = L;
    while (p != NULL) { // 遍历所有表头元素
        int dep = GlistDepth(p->ptr.hp); // 递归计算子表深度
        if (dep > max_depth) max_depth = dep;
        p = p->ptr.tp; // 移动到下一个表头（表尾）
    }
    return max_depth + 1; // 子表最大深度加1
}
//5.32

bool GlistEqual(GList L, GList M) {
    // 均为空表
    if (L == NULL && M == NULL) return true;
    // 一个为空，另一个非空
    if (L == NULL || M == NULL) return false;
    
    if (L->tag == 0 && M->tag == 0) { // 均为原子
        return L->atom == M->atom;
    } else if (L->tag == 1 && M->tag == 1) { // 均为子表
        return GlistEqual(L->ptr.hp, M->ptr.hp) && // 比较表头
               GlistEqual(L->ptr.tp, M->ptr.tp);   // 比较表尾
    } else { // 类型不同（原子vs子表）
        return false;
    }
}