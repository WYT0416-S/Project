// 假设二叉树结点结构   6.47
// typedef struct BiTNode {
//     ElemType data;
//     struct BiTNode *lchild, *rchild;
// } BiTNode, *BiTree;

void LevelOrderTraversal(BiTree root) {
    if (root == NULL) return; // 空树则直接返回

    InitQueue(Q); // 初始化一个队列Q
    BiTree p = root;
    EnQueue(Q, p); // 根结点入队

    while (!QueueEmpty(Q)) { // 当队列不为空时循环
        DeQueue(Q, p); // 队头元素出队，并用p指向它
        visit(p->data); // 访问当前结点（如打印）

        if (p->lchild != NULL) { // 若左孩子存在，则左孩子入队
            EnQueue(Q, p->lchild);
        }
        if (p->rchild != NULL) { // 若右孩子存在，则右孩子入队
            EnQueue(Q, p->rchild);
        }
    }
}

//6.48
// 结点结构同上

BiTree FindNearestCommonAncestor(BiTree root, BiTree p, BiTree q) {
    // 递归基
    if (root == NULL) {
        return NULL; // 当前子树为空，返回NULL
    }
    if (root == p || root == q) {
        return root; // 如果当前结点就是p或q，则返回当前结点
    }

    // 递归工作：在左右子树中寻找p和q
    BiTree left_ancestor = FindNearestCommonAncestor(root->lchild, p, q);
    BiTree right_ancestor = FindNearestCommonAncestor(root->rchild, p, q);

    // 对递归返回的结果进行判断
    if (left_ancestor != NULL && right_ancestor != NULL) {
        return root; // 情况1：p和q分别位于当前根结点的左右子树中，则当前根结点即为最近公共祖先
    }
    // 情况2：p和q都位于当前根结点的左子树或都位于右子树中
    else if (left_ancestor != NULL) {
        return left_ancestor; // 左子树中找到的祖先就是最终结果
    } else {
        return right_ancestor; // 右子树中找到的祖先就是最终结果
    }
}
//6.54
// 二叉树结点结构
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 顺序表结构
typedef struct {
    ElemType *elem;  // 存储空间基址，elem[0]不用
    int last;        // 最后一个结点位置
} SqList;

// 递归建立二叉链表
BiTree CreateBiTree(SqList sa, int i) {
    if (i > sa.last) return NULL;  // 超出范围返回空
    
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T->data = sa.elem[i];  // 创建当前结点
    
    // 递归建立左子树和右子树
    T->lchild = CreateBiTree(sa, 2*i);
    T->rchild = CreateBiTree(sa, 2*i + 1);
    
    return T;
}

// 主函数：建立二叉链表
BiTree SaToBiTree(SqList sa) {
    if (sa.last < 1) return NULL;  // 空树处理
    return CreateBiTree(sa, 1);    // 从根结点（下标1）开始建立
}