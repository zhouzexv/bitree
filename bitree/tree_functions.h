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
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
    // �������ﲹ����룬��ɱ�������
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
//�������T�����
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T==NULL) return 0;
    int leftdepth=BiTreeDepth(T->lchild);
    int rightdepth=BiTreeDepth(T->rchild);
    return (leftdepth > rightdepth ? leftdepth :rightdepth)+1;

    /********** End **********/
}

BiTNode* LocateNode(BiTree T,KeyType e)
//���ҽ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(T==NULL) return NULL;
    if(T->data.key==e) return T;
    BiTNode* result = LocateNode(T->lchild, e); // �ݹ����������
    if (result != NULL) {
        return result; // ��������������ҵ������ؽ��
    }
    return LocateNode(T->rchild, e);

    /********** End **********/
}

status Assign(BiTree &T,KeyType e,TElemType value)
//ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
{
    // �������ﲹ����룬��ɱ�������
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
//ʵ�ֻ���ֵܽ��
{
    // �������ﲹ����룬��ɱ�������
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
//ʵ�ֻ���ֵܽ��
{
    // �������ﲹ����룬��ɱ�������
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
//�����㡣��������ͨ������������������ʵ�ֱ�������
{
    // �������ﲹ����룬��ɱ�������
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
//Ѱ�ҽڵ㼰�丸�׽ڵ�
{
    if (T == NULL) return NULL; // ������ֱ�ӷ��� NULL

    BiTNode* stack[100]; // ���ڴ洢������Ľڵ�
    BiTNode* parentStack[100]; // ���ڴ洢������Ľڵ�ĸ��ڵ�
    int top = 0;
    stack[top] = T; // �����ڵ�ѹ��ջ
    parentStack[top] = NULL; // ���ڵ�ĸ��ڵ�Ϊ NULL
    top++;

    while (top > 0) {
        top--;
        BiTNode* current = stack[top]; // ��ȡջ���ڵ�
        BiTNode* currentParent = parentStack[top]; // ��ȡջ���ڵ�ĸ��ڵ�

        if (current->data.key==e) {
            *parent = currentParent; // ���游�ڵ�
            return current; // �ҵ�Ŀ��ڵ㣬���ص�ǰ�ڵ�
        }

        // �����ӽڵ㼰�丸�ڵ�ѹ��ջ��������ڣ�
        if (current->rchild != NULL) {
            stack[top] = current->rchild;
            parentStack[top] = current;
            top++;
        }

        // �����ӽڵ㼰�丸�ڵ�ѹ��ջ��������ڣ�
        if (current->lchild != NULL) {
            stack[top] = current->lchild;
            parentStack[top] = current;
            top++;
        }
    }

    return NULL; // δ�ҵ�Ŀ��ڵ㣬���� NULL
}

status DeleteNode(BiTree &T,KeyType e)
//ɾ����㡣��������ͨ������������������ʵ�ֱ�������
{
    // �������ﲹ����룬��ɱ�������
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
//�������������T���ǵݹ飩
{
    // �������ﲹ����룬��ɱ�������
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
//�������������T���ǵݹ飩
{
    // �������ﲹ����룬��ɱ�������
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
//�������������T���ݹ飩
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (T == NULL) return OK;
    PostOrderTraverse(T->lchild, visit); // �ݹ����������
    PostOrderTraverse(T->rchild, visit); // �ݹ����������
    visit(T); // ���ʵ�ǰ�ڵ�
    return OK;

    /********** End **********/
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    // �������ﲹ����룬��ɱ�������
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
//�ݹ鱣���ļ�
{
        if (node == NULL) {
            fprintf(fp, "NULL\n"); // �սڵ㣬д�� NULL
            return OK;
        }
        fprintf(fp, "%d,%s\n", node->data.key, node->data.others); // д��ڵ�����
        SaveNode(node->lchild, fp); // �ݹ鱣��������
        SaveNode(node->rchild, fp); // �ݹ鱣��������
        return OK;
}

status LoadNode(BiTree &node, FILE *fp) 
//�ݹ��ȡ�ļ�
{
        char buffer[100];
        if (fscanf(fp, "%s", buffer) == EOF) return ERROR; // �ļ���ȡ����

        if (strcmp(buffer, "NULL") == 0) {
            node = NULL; // �սڵ�
            return OK;
        }

        node = (BiTNode*)malloc(sizeof(BiTNode)); // �����½ڵ�
        if (node == NULL) return ERROR; // �ڴ����ʧ��
        sscanf(buffer, "%d,%[^,]", &node->data.key, node->data.others); // ��ȡ�ڵ�����
        LoadNode(node->lchild, fp); // �ݹ����������
        LoadNode(node->rchild, fp); // �ݹ����������
        return OK;
    }

status SaveBiTree(BiTree T, char FileName[])
//���������Ľ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
    FILE *fp = fopen(FileName, "w"); // ���ļ�����д��
    if (fp == NULL) return ERROR; // �ļ���ʧ��

    SaveNode(T, fp); // �Ӹ��ڵ㿪ʼ����
    fclose(fp); // �ر��ļ�
    return OK;

    /********** End 1 **********/
}

status LoadBiTree(BiTree &T,  char FileName[])
//�����ļ�FileName�Ľ�����ݣ�����������
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    FILE *fp = fopen(FileName, "r"); // ���ļ����ڶ�ȡ
    if (fp == NULL) return ERROR; // �ļ���ʧ��

    LoadNode(T, fp); // �Ӹ��ڵ㿪ʼ����
    fclose(fp); // �ر��ļ�
    return OK;

    /********** End 2 **********/
}

int MaxPathSum(BiTree T) {
    if (T == NULL) return INFEASIBLE; // �����Ϊ�գ�����INFEASIBLE

    // �����ǰ�ڵ���Ҷ�ӽڵ㣬���ظýڵ��ֵ
    if (T->lchild == NULL && T->rchild == NULL) return T->data.key;

    // �����������������������·����
    int leftSum = MaxPathSum(T->lchild);
    int rightSum = MaxPathSum(T->rchild);

    // �����������������Ϊ�գ�ֻ���Ƿǿ�������·����
    if (T->lchild == NULL) return T->data.key + rightSum;
    if (T->rchild == NULL) return T->data.key + leftSum;

    // ���ص�ǰ�ڵ�ֵ�������������нϴ��·����
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
    // ���������в���e1��e2
    BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);

    // ��������������������ҵ���e1��e2����ô��ǰ�ڵ����LCA
    if (left != NULL && right != NULL) return T;

    // ���ֻ�����������ҵ�e1��e2�������������Ľ��
    if (left != NULL) return left;

    // ���ֻ�����������ҵ�e1��e2�������������Ľ��
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
        return OVERFLOW; // ������Ա������Ѵ����ޣ�����OVERFLOW
    }
    for (int i = 0; i < forest.length; i++) {
        if (strcmp(forest.elem[i].name, ListName) == 0) 
        {
            printf("�Ѿ���ͬ�����������ڣ��ɿ��Ǹ���һ���������´���\n");
            return ERROR;
        }
    }
    strcpy(forest.elem[forest.length].name, ListName);
    forest.elem[forest.length].T=(BiTNode*)malloc(sizeof(BiTNode));
    forest.elem[forest.length].T->lchild = NULL; 
    forest.elem[forest.length].T->rchild = NULL;
    forest.length++; // ��������
    return OK; // ��ӳɹ�
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
           return i + 1; // �����߼���ţ���1��ʼ��
        }
    }
    return 0; // ���δ�ҵ�������0
}

void bianli(TREES forest)
{
    if (forest.length == 0) {
        printf("��������Ϊ�ա�\n");
        return;
    }
    printf("���ڶ�������ϵͳ����%d��������\n",forest.length);
    for(int i=0; i<forest.length; i++)
    {
        printf("��%d��������:%s\n",i+1,forest.elem[i].name);
    }
    return ;
}

