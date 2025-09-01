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
	} TElemType; //二叉树结点类型定义


    typedef struct BiTNode{  //二叉链表结点的定义
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
    printf("1. CreateBiTree 创建二叉树\t\t2. DestroyBiTree 销毁二叉树\n");
    printf("3. ClearBiTree 清空二叉树\t\t4. BiTreeEmpty 判空\n");
    printf("5. BiTreeDepth 求深度\t\t6. LocateNode 查找节点\n");
    printf("7. Assign 节点赋值\t\t8. GetSibling 获取兄弟节点\n");
    printf("9. InsertNode 插入节点\t\t10. DeleteNode 删除节点\n");
    printf("11. PreOrderTraverse 前序遍历\t12. InOrderTraverse 中序遍历\n");
    printf("13. PostOrderTraverse 后序遍历\t14. LevelOrderTraverse 层序遍历\n");
    printf("15. MaxPathSum 最大路径和\t16. LowestCommonAncestor 最近公共祖先\n");
    printf("17. InvertTree 翻转二叉树\t18. SaveBiTree 保存至文件\n");
    printf("19. LoadBiTree 从文件读取\t20. 多树操作\n");
    printf("0. Exit");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~20]:");
    scanf("%d",&n);
    while(n)
    {
        switch(n)
        {
            case 1:
                // 创建二叉树
                printf("请输入二叉树的定义（格式：位置 关键字 其他信息，以0结束）：\n");
                i=0;
                while (1) {
                    scanf("%d", &definition[i].pos);
                    if (definition[i].pos == 0) break;
                    scanf("%d %s", &definition[i].data.key, definition[i].data.others);
                    i++;
                }
                CreateBiTree(T, definition);
                printf("二叉树创建成功。\n");
                break;
            case 2:
                // 销毁二叉树
                DestroyBiTree(T);
                printf("二叉树已销毁。\n");
                break;
            case 3:
                // 清空二叉树
                ClearBiTree(T);
                printf("二叉树已清空。\n");
                break;
            case 4:
                // 判空
                if (BiTreeEmpty(T)) {
                    printf("二叉树为空。\n");
                } else {
                    printf("二叉树不为空。\n");
                }
                break;
            case 5:
                // 求深度
                printf("二叉树的深度为：%d\n", BiTreeDepth(T));
                break;
            case 6:
                // 查找节点
                printf("请输入要查找的节点关键字：");
                scanf("%d", &key);
                node = LocateNode(T, key);
                if (node != NULL) {
                    printf("找到节点：%d,%s\n", node->data.key, node->data.others);
                } else {
                    printf("未找到节点。\n");
                }
                break;
            case 7:
                // 节点赋值
                printf("请输入要赋值的节点关键字和新值：");
                scanf("%d %d %s", &key, &value.key, value.others);
                if (Assign(T, key, value) == OK) {
                    printf("节点赋值成功。\n");
                } else {
                    printf("节点赋值失败。\n");
                }
                break;
            case 8:
                // 获取兄弟节点
                printf("请输入要查找兄弟节点的关键字：");
                scanf("%d", &key);
                sibling = GetSibling(T, key);
                if (sibling != NULL) {
                    printf("兄弟节点：%d,%s\n", sibling->data.key, sibling->data.others);
                } else {
                    printf("该节点无兄弟节点。\n");
                }
                break;
            case 9:
                // 插入节点
                printf("请输入要插入的节点关键字、位置（0左1右-1根）、新节点关键字和信息：");
                
                scanf("%d %d %d %s", &key, &LR, &value.key, value.others);
                if (InsertNode(T, key, LR, value) == OK) {
                    printf("节点插入成功。\n");
                } else {
                    printf("节点插入失败。\n");
                }
                break;
            case 10:
                // 删除节点
                printf("请输入要删除的节点关键字：");
                scanf("%d", &key);
                if (DeleteNode(T, key) == OK) {
                    printf("节点删除成功。\n");
                } else {
                    printf("节点删除失败。\n");
                }
                break;
            case 11:
                // 前序遍历
                printf("前序遍历结果：");
                PreOrderTraverse(T, Visit);
                printf("\n");
                break;
            case 12:
                // 中序遍历
                printf("中序遍历结果：");
                InOrderTraverse(T, Visit);
                printf("\n");
                break;
            case 13:
                // 后序遍历
                printf("后序遍历结果：");
                PostOrderTraverse(T, Visit);
                printf("\n");
                break;
            case 14:
                // 层序遍历
                printf("层序遍历结果：");
                LevelOrderTraverse(T, Visit);
                printf("\n");
                break;
            case 15:
                // 最大路径和
                printf("最大路径和：%d\n", MaxPathSum(T));
                break;
            case 16:
                // 最近公共祖先
                printf("请输入两个节点的关键字：");
                scanf("%d %d", &e1, &e2);
                p1=LocateNode(T,e1);
                p2=LocateNode(T,e2);
                if(p1==NULL || p2==NULL)
                {
                    printf("树中没有给出的节点");
                    break;
                }
                lca = LowestCommonAncestor(T, p1, p2);
                if (lca != NULL) {
                    printf("最近公共祖先：%d,%s\n", lca->data.key, lca->data.others);
                } else {
                    printf("未找到最近公共祖先。\n");
                }
                break;
            case 17:
                // 翻转二叉树
                InvertTree(T);
                printf("二叉树已翻转。\n");
                break;
            case 18:
                // 保存至文件
                printf("请输入文件名：");
                scanf("%s", fileName);
                if (SaveBiTree(T, fileName) == OK) {
                    printf("二叉树已保存至文件。\n");
                } else {
                    printf("保存失败。\n");
                }
                break;
            case 19:
                // 从文件读取
                printf("请输入文件名：");
                scanf("%s", fileName);
                if (LoadBiTree(T, fileName) == OK) {
                    printf("二叉树已从文件加载。\n");
                } else {
                    printf("加载失败。\n");
                }
                break;
            case 20:
                //多树操作
            printf("请输入你想要的多二叉树管理操作：1.创建特定名称的二叉树,最多创建10个\n2.删除特定名称的二叉树\n3.对某个二叉树操作\n");
            printf("4.显示已有二叉树\n");
            scanf("%d",&x);
            switch(x)
            {
                case 1:
                    printf("请输入想要创建的二叉树的名字\n");
                    char TreeName[30];
                    scanf("%29s",TreeName);
                    flag=AddList(trees,TreeName);
                    if(flag==OK)
                    {
                        printf("创建二叉树成功\n");
                    }
                    else if(flag==ERROR)
                    {
                        printf("创建二叉树失败\n");
                    }
                    else if(flag==OVERFLOW)
                    {
                        printf("二叉树组已满\n");
                    }
                    if (trees.length > 0 && trees.elem[trees.length - 1].T == NULL) 
                    {
                        trees.length--; // 恢复长度
                    }
                    break;
                case 2:
                    printf("请输入你想删除的二叉树名称\n");
                    scanf("%s",TreeName);
                    flag=RemoveList(trees,TreeName);
                    if(flag==OK)
                    {
                        printf("删除二叉树成功\n");
                    }
                    else printf("删除二叉树失败\n");
                    break;
                
                case 3:
                    printf("请输入你想要进行上述单个二叉树操作的二叉树名称\n");
                    scanf("%s",TreeName);
                    treeIndex = LocateList(trees, TreeName);
                    if (treeIndex == 0) 
                    {
                        printf("二叉树未找到\n");
                    } 
                    else 
                    {
                        T = trees.elem[treeIndex - 1].T;
                        printf("成功选中二叉树，这是第%d个树，可继续进行对该树的操作\n",treeIndex);
                    }
                    break;
                case 4:
                    bianli(trees);
                    break;
                default :
                    printf("无效输入");
                    break;
            }
            break;
            case 0:
                // 退出
                printf("退出程序。\n");
                return 0;
            default:
                printf("无效的选择，请重新输入。\n");
        }
        printf("\n      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("1. CreateBiTree 创建二叉树\t\t2. DestroyBiTree 销毁二叉树\n");
        printf("3. ClearBiTree 清空二叉树\t\t4. BiTreeEmpty 判空\n");
        printf("5. BiTreeDepth 求深度\t\t6. LocateNode 查找节点\n");
        printf("7. Assign 节点赋值\t\t8. GetSibling 获取兄弟节点\n");
        printf("9. InsertNode 插入节点\t\t10. DeleteNode 删除节点\n");
        printf("11. PreOrderTraverse 前序遍历\t12. InOrderTraverse 中序遍历\n");
        printf("13. PostOrderTraverse 后序遍历\t14. LevelOrderTraverse 层序遍历\n");
        printf("15. MaxPathSum 最大路径和\t16. LowestCommonAncestor 最近公共祖先\n");
        printf("17. InvertTree 翻转二叉树\t18. SaveBiTree 保存至文件\n");
        printf("19. LoadBiTree 从文件读取\t20. 多树操作\n");
        printf("0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        scanf("%d",&n);
    }
}

