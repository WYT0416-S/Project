#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 定义数据类型和状态码
typedef char ElemType;
typedef int Status;
#define OK 1
#define ERROR 0
#define OVERFLOW -1

// 二叉树结点定义
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 全局变量用于叶子计数
int leaf_count = 0;

// 函数声明
Status InitBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);
void ClearBiTree(BiTree *T);
bool BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
void DestroyBiTree(BiTree *T);
Status Assign(BiTree T, ElemType e, ElemType value);
BiTree Root(BiTree T);
ElemType Value(BiTree T, ElemType e);
BiTree Parent(BiTree T, ElemType e);
BiTree LeftChild(BiTree T, ElemType e);
BiTree RightChild(BiTree T, ElemType e);
BiTree LeftSibling(BiTree T, ElemType e);
BiTree RightSibling(BiTree T, ElemType e);
Status InsertChild(BiTree T, BiTree p, int LR, BiTree c);
Status DeleteChild(BiTree T, BiTree p, int LR);

void PreOrderTraverse(BiTree T);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);
void LevelOrderTraverse(BiTree T);

int CountNodes(BiTree T);
int TreeHeight(BiTree T);
void CountLeaves_Global(BiTree T);
int CountLeaves_Return(BiTree T);
void DeleteBiTree(BiTree *T);
void DeleteXTree(BiTree *T, ElemType x);

// 辅助函数
BiTree FindNode(BiTree T, ElemType e);

int main() {
    BiTree T = NULL;
    int choice;
    ElemType value, target;
    
    printf("========== 二叉树操作演示程序 ==========\n");
    
    do {
        printf("\n请选择操作:\n");
        printf("1. 创建二叉树\n");
        printf("2. 前序遍历\n");
        printf("3. 中序遍历\n");
        printf("4. 后序遍历\n");
        printf("5. 层次遍历\n");
        printf("6. 统计结点个数\n");
        printf("7. 计算树高度\n");
        printf("8. 统计叶子结点数\n");
        printf("9. 删除指定值的子树\n");
        printf("10. 销毁二叉树\n");
        printf("0. 退出\n");
        printf("请输入选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("按先序序列输入二叉树结点值（空格表示空结点）:\n");
                printf("示例: AB D  CE  表示 A 为根，B 为左子树，D 为 B 的右子树，C 为 A 的右子树，E 为 C 的左子树\n");
                getchar(); // 清除缓冲区
                if (CreateBiTree(&T) == OK) {
                    printf("二叉树创建成功！\n");
                } else {
                    printf("二叉树创建失败！\n");
                }
                break;
                
            case 2:
                printf("前序遍历结果: ");
                PreOrderTraverse(T);
                printf("\n");
                break;
                
            case 3:
                printf("中序遍历结果: ");
                InOrderTraverse(T);
                printf("\n");
                break;
                
            case 4:
                printf("后序遍历结果: ");
                PostOrderTraverse(T);
                printf("\n");
                break;
                
            case 5:
                printf("层次遍历结果: ");
                LevelOrderTraverse(T);
                printf("\n");
                break;
                
            case 6:
                printf("二叉树结点个数: %d\n", CountNodes(T));
                break;
                
            case 7:
                printf("二叉树高度: %d\n", TreeHeight(T));
                break;
                
            case 8:
                leaf_count = 0;
                CountLeaves_Global(T);
                printf("方法1（全局变量）叶子结点数: %d\n", leaf_count);
                printf("方法2（返回值）叶子结点数: %d\n", CountLeaves_Return(T));
                break;
                
            case 9:
                printf("请输入要删除的结点值: ");
                getchar();
                scanf("%c", &target);
                DeleteXTree(&T, target);
                printf("删除完成\n");
                break;
                
            case 10:
                DestroyBiTree(&T);
                printf("二叉树已销毁\n");
                break;
                
            case 0:
                printf("程序结束\n");
                break;
                
            default:
                printf("无效选择！\n");
        }
    } while (choice != 0);
    
    // 清理内存
    if (T != NULL) {
        DestroyBiTree(&T);
    }
    
    return 0;
}

// 初始化二叉树
Status InitBiTree(BiTree *T) {
    *T = NULL;
    return OK;
}

// 按先序序列创建二叉树
Status CreateBiTree(BiTree *T) {
    char ch;
    scanf("%c", &ch);
    
    if (ch == ' ' || ch == '\n') {
        *T = NULL;
    } else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T) {
            exit(OVERFLOW);
        }
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
    return OK;
}

// 清空二叉树
void ClearBiTree(BiTree *T) {
    if (*T != NULL) {
        ClearBiTree(&(*T)->lchild);
        ClearBiTree(&(*T)->rchild);
        free(*T);
        *T = NULL;
    }
}

// 判断二叉树是否为空
bool BiTreeEmpty(BiTree T) {
    return T == NULL;
}

// 计算二叉树深度
int BiTreeDepth(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        int leftDepth = BiTreeDepth(T->lchild);
        int rightDepth = BiTreeDepth(T->rchild);
        return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
    }
}

// 销毁二叉树
void DestroyBiTree(BiTree *T) {
    ClearBiTree(T);
}

// 给指定结点赋值
Status Assign(BiTree T, ElemType e, ElemType value) {
    BiTree node = FindNode(T, e);
    if (node != NULL) {
        node->data = value;
        return OK;
    }
    return ERROR;
}

// 返回根结点
BiTree Root(BiTree T) {
    return T;
}

// 返回指定结点的值
ElemType Value(BiTree T, ElemType e) {
    BiTree node = FindNode(T, e);
    if (node != NULL) {
        return node->data;
    }
    return '\0';
}

// 查找指定结点的父结点
BiTree Parent(BiTree T, ElemType e) {
    if (T == NULL || T->data == e) {
        return NULL; // 根结点或无父结点
    }
    
    if ((T->lchild != NULL && T->lchild->data == e) ||
        (T->rchild != NULL && T->rchild->data == e)) {
        return T;
    }
    
    BiTree left = Parent(T->lchild, e);
    if (left != NULL) return left;
    
    return Parent(T->rchild, e);
}

// 返回左孩子
BiTree LeftChild(BiTree T, ElemType e) {
    BiTree node = FindNode(T, e);
    if (node != NULL) {
        return node->lchild;
    }
    return NULL;
}

// 返回右孩子
BiTree RightChild(BiTree T, ElemType e) {
    BiTree node = FindNode(T, e);
    if (node != NULL) {
        return node->rchild;
    }
    return NULL;
}

// 返回左兄弟
BiTree LeftSibling(BiTree T, ElemType e) {
    BiTree parent = Parent(T, e);
    if (parent != NULL && parent->rchild != NULL && parent->rchild->data == e) {
        return parent->lchild;
    }
    return NULL;
}

// 返回右兄弟
BiTree RightSibling(BiTree T, ElemType e) {
    BiTree parent = Parent(T, e);
    if (parent != NULL && parent->lchild != NULL && parent->lchild->data == e) {
        return parent->rchild;
    }
    return NULL;
}

// 插入子树
Status InsertChild(BiTree T, BiTree p, int LR, BiTree c) {
    if (T == NULL || p == NULL) {
        return ERROR;
    }
    
    if (LR == 0) { // 插入为左孩子
        if (p->lchild != NULL) {
            DeleteBiTree(&p->lchild);
        }
        p->lchild = c;
    } else { // 插入为右孩子
        if (p->rchild != NULL) {
            DeleteBiTree(&p->rchild);
        }
        p->rchild = c;
    }
    return OK;
}

// 删除子树
Status DeleteChild(BiTree T, BiTree p, int LR) {
    if (T == NULL || p == NULL) {
        return ERROR;
    }
    
    if (LR == 0) { // 删除左子树
        DeleteBiTree(&p->lchild);
    } else { // 删除右子树
        DeleteBiTree(&p->rchild);
    }
    return OK;
}

// 前序遍历
void PreOrderTraverse(BiTree T) {
    if (T) {
        printf("%c ", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

// 中序遍历
void InOrderTraverse(BiTree T) {
    if (T) {
        InOrderTraverse(T->lchild);
        printf("%c ", T->data);
        InOrderTraverse(T->rchild);
    }
}

// 后序遍历
void PostOrderTraverse(BiTree T) {
    if (T) {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c ", T->data);
    }
}

// 层次遍历
void LevelOrderTraverse(BiTree T) {
    if (T == NULL) return;
    
    BiTree queue[100];
    int front = 0, rear = 0;
    
    queue[rear++] = T;
    
    while (front < rear) {
        BiTree current = queue[front++];
        printf("%c ", current->data);
        
        if (current->lchild != NULL) {
            queue[rear++] = current->lchild;
        }
        if (current->rchild != NULL) {
            queue[rear++] = current->rchild;
        }
    }
}

// 计算结点个数
int CountNodes(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        return 1 + CountNodes(T->lchild) + CountNodes(T->rchild);
    }
}

// 计算树高度
int TreeHeight(BiTree T) {
    if (T == NULL) {
        return 0;
    } else {
        int m = TreeHeight(T->lchild);
        int n = TreeHeight(T->rchild);
        return (m > n) ? m + 1 : n + 1;
    }
}

// 统计叶子结点（全局变量方法）
void CountLeaves_Global(BiTree T) {
    if (T != NULL) {
        if (T->lchild == NULL && T->rchild == NULL) {
            leaf_count++;
        }
        CountLeaves_Global(T->lchild);
        CountLeaves_Global(T->rchild);
    }
}

// 统计叶子结点（返回值方法）
int CountLeaves_Return(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    if (T->lchild == NULL && T->rchild == NULL) {
        return 1;
    }
    return CountLeaves_Return(T->lchild) + CountLeaves_Return(T->rchild);
}

// 删除二叉树
void DeleteBiTree(BiTree *T) {
    if (*T != NULL) {
        DeleteBiTree(&(*T)->lchild);
        DeleteBiTree(&(*T)->rchild);
        free(*T);
        *T = NULL;
    }
}

// 删除指定值的子树
void DeleteXTree(BiTree *T, ElemType x) {
    if (*T != NULL) {
        DeleteXTree(&(*T)->lchild, x);
        
        if ((*T)->data == x) {
            DeleteBiTree(T);
        } else {
            DeleteXTree(&(*T)->rchild, x);
        }
    }
}

// 辅助函数：查找指定值的结点
BiTree FindNode(BiTree T, ElemType e) {
    if (T == NULL) {
        return NULL;
    }
    if (T->data == e) {
        return T;
    }
    
    BiTree left = FindNode(T->lchild, e);
    if (left != NULL) {
        return left;
    }
    
    return FindNode(T->rchild, e);
}