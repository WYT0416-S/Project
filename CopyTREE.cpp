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

typedef struct BiTNode{
    ElemType data ;
    struct BiTNode *lchild,*rchild;//递归定义
}BiTNode,*BiTree;

int leaf_count = 0;

Status InitBiTree(BiTree &T);
Status CreateBiTree(BiTree &T);
void ClearBiTree(BiTree &T);
bool BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
void DestroyBiTree(BiTree &T);
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
void DeleteBiTree(BiTree &T);
void DeleteXTree(BiTree &T, ElemType x);

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
Status InitBiTree(BiTree &T){
    T=NULL;
    return OK;
}
// 按先序序列创建二叉树
Status CreateBiTree(BiTree &T){
    char ch;
    scanf("%c",&ch);
    if(ch==' '||ch=='\n'){
        T=NULL;
    }
    else {
        T=(BiTree)malloc(sizeof(BiTNode));
        if(!T){
            exit(OVERFLOW);
        }
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

void ClearBiTree(BiTree &T){
    if(T!=NULL){
        ClearBiTree(&T->lchild);
        ClearBiTree(&T->rchild);
        free(T);
        T=NULL;
    }
}
bool BiTreeEmpty(BiTree T){
    return T==NULL;
}

int BiTreeDepth(BiTree T){
    if(T==NULL){
        return 0;
    }
    else {
        int leftDepth =BiTreeDepth(T->lchild);
        int rightDepth =BiTreeDepth(T->rchild);
        return (leftDepth>rightDepth?leftDepth:rightDepth)+1
    }
}
void DestroyBiTree(BiTree &T){
    ClearBiTree(T);
}
Status Assign(BiTree T, ElemType e,ElemType value){
    BiTree node=FindNode(T,e);
    if(node！=NULL){
        return node->rchild;
    }
    
}//