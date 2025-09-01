#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TRUE 1
	#define FALSE 0
	#define OK 1
	#define ERROR 0
	#define INFEASIBLE -1
	#define OVERFLOW -2

	typedef int status;
	typedef int KeyType; 
	typedef struct {
         KeyType  key;
         char others[20];
	} TElemType; //������������Ͷ���


    typedef struct BiTNode{  //����������Ķ���
	      TElemType  data;
	      struct BiTNode *lchild,*rchild;
	} BiTNode, *BiTree;

typedef struct {
    int pos;
    TElemType data;
} DEF;

typedef struct{
    struct{
        char name[30];
        BiTNode* T;
    } elem[10];
    int length;
    int size;
} TREES;

#include "tree_functions.h"

int main()
{
    int n;
    DEF definition[100];
    int i;
    BiTree T = NULL;
    KeyType key;
    TElemType value;
    char fileName[100];
    BiTNode* node;
    BiTNode* sibling;
    BiTNode* p1;    BiTNode* p2;  BiTNode* lca;
    int LR;
    KeyType e1, e2;
    TREES trees;
    trees.length=0;
    int treeIndex,flag,x;
    printf("\n      Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("1. CreateBiTree ����������\t\t2. DestroyBiTree ���ٶ�����\n");
    printf("3. ClearBiTree ��ն�����\t\t4. BiTreeEmpty �п�\n");
    printf("5. BiTreeDepth �����\t\t6. LocateNode ���ҽڵ�\n");
    printf("7. Assign �ڵ㸳ֵ\t\t8. GetSibling ��ȡ�ֵܽڵ�\n");
    printf("9. InsertNode ����ڵ�\t\t10. DeleteNode ɾ���ڵ�\n");
    printf("11. PreOrderTraverse ǰ�����\t12. InOrderTraverse �������\n");
    printf("13. PostOrderTraverse �������\t14. LevelOrderTraverse �������\n");
    printf("15. MaxPathSum ���·����\t16. LowestCommonAncestor �����������\n");
    printf("17. InvertTree ��ת������\t18. SaveBiTree �������ļ�\n");
    printf("19. LoadBiTree ���ļ���ȡ\t20. ��������\n");
    printf("0. Exit");
    printf("-------------------------------------------------\n");
    printf("    ��ѡ����Ĳ���[0~20]:");
    scanf("%d",&n);
    while(n)
    {
        switch(n)
        {
            case 1:
                // ����������
                printf("������������Ķ��壨��ʽ��λ�� �ؼ��� ������Ϣ����0��������\n");
                i=0;
                while (1) {
                    scanf("%d", &definition[i].pos);
                    if (definition[i].pos == 0) break;
                    scanf("%d %s", &definition[i].data.key, definition[i].data.others);
                    i++;
                }
                CreateBiTree(T, definition);
                printf("�����������ɹ���\n");
                break;
            case 2:
                // ���ٶ�����
                DestroyBiTree(T);
                printf("�����������١�\n");
                break;
            case 3:
                // ��ն�����
                ClearBiTree(T);
                printf("����������ա�\n");
                break;
            case 4:
                // �п�
                if (BiTreeEmpty(T)) {
                    printf("������Ϊ�ա�\n");
                } else {
                    printf("��������Ϊ�ա�\n");
                }
                break;
            case 5:
                // �����
                printf("�����������Ϊ��%d\n", BiTreeDepth(T));
                break;
            case 6:
                // ���ҽڵ�
                printf("������Ҫ���ҵĽڵ�ؼ��֣�");
                scanf("%d", &key);
                node = LocateNode(T, key);
                if (node != NULL) {
                    printf("�ҵ��ڵ㣺%d,%s\n", node->data.key, node->data.others);
                } else {
                    printf("δ�ҵ��ڵ㡣\n");
                }
                break;
            case 7:
                // �ڵ㸳ֵ
                printf("������Ҫ��ֵ�Ľڵ�ؼ��ֺ���ֵ��");
                scanf("%d %d %s", &key, &value.key, value.others);
                if (Assign(T, key, value) == OK) {
                    printf("�ڵ㸳ֵ�ɹ���\n");
                } else {
                    printf("�ڵ㸳ֵʧ�ܡ�\n");
                }
                break;
            case 8:
                // ��ȡ�ֵܽڵ�
                printf("������Ҫ�����ֵܽڵ�Ĺؼ��֣�");
                scanf("%d", &key);
                sibling = GetSibling(T, key);
                if (sibling != NULL) {
                    printf("�ֵܽڵ㣺%d,%s\n", sibling->data.key, sibling->data.others);
                } else {
                    printf("�ýڵ����ֵܽڵ㡣\n");
                }
                break;
            case 9:
                // ����ڵ�
                printf("������Ҫ����Ľڵ�ؼ��֡�λ�ã�0��1��-1�������½ڵ�ؼ��ֺ���Ϣ��");
                
                scanf("%d %d %d %s", &key, &LR, &value.key, value.others);
                if (InsertNode(T, key, LR, value) == OK) {
                    printf("�ڵ����ɹ���\n");
                } else {
                    printf("�ڵ����ʧ�ܡ�\n");
                }
                break;
            case 10:
                // ɾ���ڵ�
                printf("������Ҫɾ���Ľڵ�ؼ��֣�");
                scanf("%d", &key);
                if (DeleteNode(T, key) == OK) {
                    printf("�ڵ�ɾ���ɹ���\n");
                } else {
                    printf("�ڵ�ɾ��ʧ�ܡ�\n");
                }
                break;
            case 11:
                // ǰ�����
                printf("ǰ����������");
                PreOrderTraverse(T, Visit);
                printf("\n");
                break;
            case 12:
                // �������
                printf("������������");
                InOrderTraverse(T, Visit);
                printf("\n");
                break;
            case 13:
                // �������
                printf("������������");
                PostOrderTraverse(T, Visit);
                printf("\n");
                break;
            case 14:
                // �������
                printf("������������");
                LevelOrderTraverse(T, Visit);
                printf("\n");
                break;
            case 15:
                // ���·����
                printf("���·���ͣ�%d\n", MaxPathSum(T));
                break;
            case 16:
                // �����������
                printf("�����������ڵ�Ĺؼ��֣�");
                scanf("%d %d", &e1, &e2);
                p1=LocateNode(T,e1);
                p2=LocateNode(T,e2);
                if(p1==NULL || p2==NULL)
                {
                    printf("����û�и����Ľڵ�");
                    break;
                }
                lca = LowestCommonAncestor(T, p1, p2);
                if (lca != NULL) {
                    printf("����������ȣ�%d,%s\n", lca->data.key, lca->data.others);
                } else {
                    printf("δ�ҵ�����������ȡ�\n");
                }
                break;
            case 17:
                // ��ת������
                InvertTree(T);
                printf("�������ѷ�ת��\n");
                break;
            case 18:
                // �������ļ�
                printf("�������ļ�����");
                scanf("%s", fileName);
                if (SaveBiTree(T, fileName) == OK) {
                    printf("�������ѱ������ļ���\n");
                } else {
                    printf("����ʧ�ܡ�\n");
                }
                break;
            case 19:
                // ���ļ���ȡ
                printf("�������ļ�����");
                scanf("%s", fileName);
                if (LoadBiTree(T, fileName) == OK) {
                    printf("�������Ѵ��ļ����ء�\n");
                } else {
                    printf("����ʧ�ܡ�\n");
                }
                break;
            case 20:
                //��������
            printf("����������Ҫ�Ķ���������������1.�����ض����ƵĶ�����,��ഴ��10��\n2.ɾ���ض����ƵĶ�����\n3.��ĳ������������\n");
            printf("4.��ʾ���ж�����\n");
            scanf("%d",&x);
            switch(x)
            {
                case 1:
                    printf("��������Ҫ�����Ķ�����������\n");
                    char TreeName[30];
                    scanf("%29s",TreeName);
                    flag=AddList(trees,TreeName);
                    if(flag==OK)
                    {
                        printf("�����������ɹ�\n");
                    }
                    else if(flag==ERROR)
                    {
                        printf("����������ʧ��\n");
                    }
                    else if(flag==OVERFLOW)
                    {
                        printf("������������\n");
                    }
                    if (trees.length > 0 && trees.elem[trees.length - 1].T == NULL) 
                    {
                        trees.length--; // �ָ�����
                    }
                    break;
                case 2:
                    printf("����������ɾ���Ķ���������\n");
                    scanf("%s",TreeName);
                    flag=RemoveList(trees,TreeName);
                    if(flag==OK)
                    {
                        printf("ɾ���������ɹ�\n");
                    }
                    else printf("ɾ��������ʧ��\n");
                    break;
                
                case 3:
                    printf("����������Ҫ�����������������������Ķ���������\n");
                    scanf("%s",TreeName);
                    treeIndex = LocateList(trees, TreeName);
                    if (treeIndex == 0) 
                    {
                        printf("������δ�ҵ�\n");
                    } 
                    else 
                    {
                        T = trees.elem[treeIndex - 1].T;
                        printf("�ɹ�ѡ�ж����������ǵ�%d�������ɼ������жԸ����Ĳ���\n",treeIndex);
                    }
                    break;
                case 4:
                    bianli(trees);
                    break;
                default :
                    printf("��Ч����");
                    break;
            }
            break;
            case 0:
                // �˳�
                printf("�˳�����\n");
                return 0;
            default:
                printf("��Ч��ѡ�����������롣\n");
        }
        printf("\n      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("1. CreateBiTree ����������\t\t2. DestroyBiTree ���ٶ�����\n");
        printf("3. ClearBiTree ��ն�����\t\t4. BiTreeEmpty �п�\n");
        printf("5. BiTreeDepth �����\t\t6. LocateNode ���ҽڵ�\n");
        printf("7. Assign �ڵ㸳ֵ\t\t8. GetSibling ��ȡ�ֵܽڵ�\n");
        printf("9. InsertNode ����ڵ�\t\t10. DeleteNode ɾ���ڵ�\n");
        printf("11. PreOrderTraverse ǰ�����\t12. InOrderTraverse �������\n");
        printf("13. PostOrderTraverse �������\t14. LevelOrderTraverse �������\n");
        printf("15. MaxPathSum ���·����\t16. LowestCommonAncestor �����������\n");
        printf("17. InvertTree ��ת������\t18. SaveBiTree �������ļ�\n");
        printf("19. LoadBiTree ���ļ���ȡ\t20. ��������\n");
        printf("0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~20]:");
        scanf("%d",&n);
    }
}

