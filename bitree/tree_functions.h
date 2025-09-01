void Visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

status CreateBiTree(BiTree &T, DEF definition[]) {
    int i = 0, j;
    static BiTNode *p[100];
    while (j = definition[i].pos) {
        p[j] = (BiTNode *)malloc(sizeof(BiTNode));
        p[j]->data = definition[i].data;
        p[j]->lchild = NULL;
        p[j]->rchild = NULL;
        if (j != 1)
            if (j % 2)
                p[j / 2]->rchild = p[j];
            else
                p[j / 2]->lchild = p[j];
        i++;
    }
    T = p[1];
    return OK;
}

status DestroyBiTree(BiTree &T) {
    if (T) {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T = NULL;
    }
    return OK;
}

status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL) {
    return OK; 
    }
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    
    T = NULL;
    return OK;

    /********** End **********/
}

status BiTreeEmpty(BiTree T) {
    return T == NULL ? TRUE : FALSE;
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return 0;
    int leftdepth=BiTreeDepth(T->lchild);
    int rightdepth=BiTreeDepth(T->rchild);
    return (leftdepth > rightdepth ? leftdepth :rightdepth)+1;

    /********** End **********/
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return NULL;
    if(T->data.key==e) return T;
    BiTNode* result = LocateNode(T->lchild, e); // 递归查找左子树
    if (result != NULL) {
        return result; // 如果在左子树中找到，返回结果
    }
    return LocateNode(T->rchild, e);

    /********** End **********/
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode* p=LocateNode(T,e);
    if(p==NULL) return ERROR;
    BiTNode* q=LocateNode(T,value.key);
    if(q!=NULL && p!=q) return ERROR;
    p->data=value;
    return OK;

    /********** End **********/
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    
    if(T==NULL) return NULL;
    if(T->lchild!=NULL && T->lchild->data.key==e)
    {
        return T->rchild;
    }
    if(T->rchild!=NULL && T->rchild->data.key==e)
    {
        return T->lchild;
    }
    BiTNode* result=GetSibling(T->lchild,e);
    if(result != NULL)
    {
        return result;
    }
    return GetSibling(T->rchild,e);

    /********** End **********/
}

BiTNode* GetParent(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    
    if(T==NULL) return NULL;
    if((T->lchild!=NULL && T->lchild->data.key==e) || (T->rchild!=NULL && T->rchild->data.key==e))
    {
        return T;
    }
    BiTNode* result=GetSibling(T->lchild,e);
    if(result != NULL)
    {
        return result;
    }
    return GetSibling(T->rchild,e);

    /********** End **********/
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode* p=(BiTNode*)malloc(sizeof(BiTNode));
    p->data=c;
    p->lchild=NULL;
    p->rchild=NULL;
    if(LR==-1)
    {
        p->rchild=T;
        T=p;
        return OK;
    }
    BiTNode* q=LocateNode(T,e);
    if(q==NULL || q->data.key==p->data.key) {free(p); return ERROR;}
    if(LR==0)
    {
        p->rchild=q->lchild;
        q->lchild=p;
    }
    else if(LR==1)
    {
        p->rchild=q->rchild;
        q->rchild=p;
    }
    return OK;

    /********** End **********/
}

BiTNode* LocateNodeWithParent(BiTree T,KeyType e, BiTNode** parent) 
//寻找节点及其父亲节点
{
    if (T == NULL) return NULL; // 空树，直接返回 NULL

    BiTNode* stack[100]; // 用于存储待处理的节点
    BiTNode* parentStack[100]; // 用于存储待处理的节点的父节点
    int top = 0;
    stack[top] = T; // 将根节点压入栈
    parentStack[top] = NULL; // 根节点的父节点为 NULL
    top++;

    while (top > 0) {
        top--;
        BiTNode* current = stack[top]; // 获取栈顶节点
        BiTNode* currentParent = parentStack[top]; // 获取栈顶节点的父节点

        if (current->data.key==e) {
            *parent = currentParent; // 保存父节点
            return current; // 找到目标节点，返回当前节点
        }

        // 将右子节点及其父节点压入栈（如果存在）
        if (current->rchild != NULL) {
            stack[top] = current->rchild;
            parentStack[top] = current;
            top++;
        }

        // 将左子节点及其父节点压入栈（如果存在）
        if (current->lchild != NULL) {
            stack[top] = current->lchild;
            parentStack[top] = current;
            top++;
        }
    }

    return NULL; // 未找到目标节点，返回 NULL
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode* parent;
    BiTNode* target = LocateNodeWithParent(T, e, &parent);

    if(target==NULL) return ERROR;
    if(target->lchild==NULL && target->rchild==NULL)
    {
        if(parent==NULL) T=NULL;
        else if(parent->lchild==target) parent->lchild=NULL;
        else if(parent->rchild==target) parent->rchild=NULL;
        free(target);
        return OK;
    }
    else if(target->lchild==NULL || target->rchild==NULL)
    {
        BiTNode* child = (target->lchild != NULL) ? target->lchild : target->rchild;
        if(parent==NULL) T=child;
        else if(parent->lchild==target) parent->lchild=child;
        else if(parent->rchild==target) parent->rchild=child;
        free(target);
        return OK; 
    }
    else if(target->lchild!=NULL && target->rchild!=NULL)
    {
        if(parent==NULL) T=target->lchild;
        else if(parent->lchild==target) parent->lchild=target->lchild;
        else if(parent->rchild==target) parent->rchild=target->lchild;
        BiTNode* p=target->lchild;
        while(p->rchild!=NULL)
        {
            p=p->rchild;
        }
        p->rchild=target->rchild;
        free(target);
        return OK;
    }
    return ERROR;

    /********** End **********/
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T（非递归）
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return OK;
    BiTNode* stack[100]; 
    int top = 0;
    stack[top++] = T;
    while(top>0)
    {
        top--;
        BiTNode* current=stack[top];
        visit(current);
        if(current->rchild!=NULL)
        {
            stack[top++]=current->rchild;
        }
        if(current->lchild!=NULL)
        {
            stack[top++]=current->lchild;
        }
    }
    return OK;

    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T（非递归）
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return OK;
    BiTNode* stack[100]; 
    int top = 0;
    BiTNode* current=T;
    while(top>0 || current!=NULL)
    {
        while(current!=NULL)
        {
            stack[top++]=current;
            current=current->lchild;
        }
        if(top>0)
        {
            current=stack[--top];
            visit(current);
            current=current->rchild;
        }
    }
    return OK;


    /********** End **********/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T（递归）
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL) return OK;
    PostOrderTraverse(T->lchild, visit); // 递归遍历左子树
    PostOrderTraverse(T->rchild, visit); // 递归遍历右子树
    visit(T); // 访问当前节点
    return OK;

    /********** End **********/
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return OK;
    BiTNode* queue[100];
    int head=0,tail=0;
    queue[tail++]=T;
    while(head<tail)
    {
        BiTNode* current=queue[head++];
        visit(current);
        if(current->lchild!=NULL)
        {
            queue[tail++]=current->lchild;
        }
        if(current->rchild!=NULL)
        {
            queue[tail++]=current->rchild;
        }
    }
    return OK;

    /********** End **********/
}

status SaveNode(BiTree node, FILE *fp) 
//递归保存文件
{
        if (node == NULL) {
            fprintf(fp, "NULL\n"); // 空节点，写入 NULL
            return OK;
        }
        fprintf(fp, "%d,%s\n", node->data.key, node->data.others); // 写入节点数据
        SaveNode(node->lchild, fp); // 递归保存左子树
        SaveNode(node->rchild, fp); // 递归保存右子树
        return OK;
}

status LoadNode(BiTree &node, FILE *fp) 
//递归读取文件
{
        char buffer[100];
        if (fscanf(fp, "%s", buffer) == EOF) return ERROR; // 文件读取结束

        if (strcmp(buffer, "NULL") == 0) {
            node = NULL; // 空节点
            return OK;
        }

        node = (BiTNode*)malloc(sizeof(BiTNode)); // 分配新节点
        if (node == NULL) return ERROR; // 内存分配失败
        sscanf(buffer, "%d,%[^,]", &node->data.key, node->data.others); // 读取节点数据
        LoadNode(node->lchild, fp); // 递归加载左子树
        LoadNode(node->rchild, fp); // 递归加载右子树
        return OK;
    }

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE *fp = fopen(FileName, "w"); // 打开文件用于写入
    if (fp == NULL) return ERROR; // 文件打开失败

    SaveNode(T, fp); // 从根节点开始保存
    fclose(fp); // 关闭文件
    return OK;

    /********** End 1 **********/
}

status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE *fp = fopen(FileName, "r"); // 打开文件用于读取
    if (fp == NULL) return ERROR; // 文件打开失败

    LoadNode(T, fp); // 从根节点开始加载
    fclose(fp); // 关闭文件
    return OK;

    /********** End 2 **********/
}

int MaxPathSum(BiTree T) {
    if (T == NULL) return INFEASIBLE; // 如果树为空，返回INFEASIBLE

    // 如果当前节点是叶子节点，返回该节点的值
    if (T->lchild == NULL && T->rchild == NULL) return T->data.key;

    // 计算左子树和右子树的最大路径和
    int leftSum = MaxPathSum(T->lchild);
    int rightSum = MaxPathSum(T->rchild);

    // 如果左子树或右子树为空，只考虑非空子树的路径和
    if (T->lchild == NULL) return T->data.key + rightSum;
    if (T->rchild == NULL) return T->data.key + leftSum;

    // 返回当前节点值加上左右子树中较大的路径和
    return T->data.key + (leftSum > rightSum ? leftSum : rightSum);
}

BiTNode* LowestCommonAncestor(BiTree T,BiTNode*  e1,BiTNode* e2)
{
    if(T==NULL || T==e1 || T==e2) return T;
    /*if(e1->lchild==e2 || e1->rchild==e2) return e1;
    if(e2->lchild==e1 || e2->rchild==e1) return e2;
    BiTNode* result=LowestCommonAncestor(T,GetParent(T,e1->data.key),e2);
    if(result==T)
    {
        return LowestCommonAncestor(T,e1,GetParent(T,e2->data.key));
    }
    return result;*/
    BiTNode* left = LowestCommonAncestor(T->lchild, e1, e2);
    // 在右子树中查找e1和e2
    BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);

    // 如果左子树和右子树都找到了e1或e2，那么当前节点就是LCA
    if (left != NULL && right != NULL) return T;

    // 如果只在左子树中找到e1或e2，返回左子树的结果
    if (left != NULL) return left;

    // 如果只在右子树中找到e1或e2，返回右子树的结果
    return right;
}

BiTNode* InvertTree(BiTree &T)
{
    if(T==NULL) return NULL;
    BiTNode* temp=T->lchild;
    T->lchild=T->rchild;
    T->rchild=temp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
    return T;
}


status AddList(TREES &forest, char ListName[]) {
    if (forest.length >= 10) {
        return OVERFLOW; // 如果线性表数量已达上限，返回OVERFLOW
    }
    for (int i = 0; i < forest.length; i++) {
        if (strcmp(forest.elem[i].name, ListName) == 0) 
        {
            printf("已经有同名二叉树存在，可考虑更换一个名称重新创建\n");
            return ERROR;
        }
    }
    strcpy(forest.elem[forest.length].name, ListName);
    forest.elem[forest.length].T=(BiTNode*)malloc(sizeof(BiTNode));
    forest.elem[forest.length].T->lchild = NULL; 
    forest.elem[forest.length].T->rchild = NULL;
    forest.length++; // 递增长度
    return OK; // 添加成功
}

status RemoveList(TREES &forest, char ListName[]) {
    int location = -1;
    for (int i = 0; i < forest.length; i++) {
        if (strcmp(forest.elem[i].name, ListName) == 0) {
            location = i;
            break;
        }
    }
    if (location == -1) {
        return ERROR;
    }
    DestroyBiTree(forest.elem[location].T);
    for (int k = location; k < forest.length - 1; k++) {
        forest.elem[k].T = forest.elem[k + 1].T;
        strcpy(forest.elem[k].name, forest.elem[k + 1].name);
    }
    forest.length--;
    return OK;
}
 
int LocateList(TREES &forest, char ListName[]) {
    for (int i = 0; i < forest.length; i++) {
        if (strcmp(forest.elem[i].name, ListName) == 0) {
           return i + 1; // 返回逻辑序号（从1开始）
        }
    }
    return 0; // 如果未找到，返回0
}

void bianli(TREES forest)
{
    if (forest.length == 0) {
        printf("二叉树组为空。\n");
        return;
    }
    printf("现在多树管理系统中有%d个二叉树\n",forest.length);
    for(int i=0; i<forest.length; i++)
    {
        printf("第%d个二叉树:%s\n",i+1,forest.elem[i].name);
    }
    return ;
}

