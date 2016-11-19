#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *NewNode(int data)
{
    struct node *node = (struct node*)malloc(sizeof(struct node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
};

void Inorder(struct node *node)
{
    if(node == NULL)
        return;

    Inorder(node->left);
    printf("%d ",node->data);
    Inorder(node->right);
}

void PreOrder(struct node *node)
{
    if(node == NULL)
        return;

    printf("%d ",node->data);
    PreOrder(node->left);
    PreOrder(node->right);
}

void PostOrder(struct node *node)
{
    if(node == NULL)
        return;

    PostOrder(node->left);
    PostOrder(node->right);
    printf("%d ",node->data);
}

//Size of Tree is the number of nodes in the tree......
int SizeOfTree(struct node *node)
{
    if(node == NULL)
        return 0;
    else
        return(SizeOfTree(node->left) + 1 + SizeOfTree(node->right));
}

//Height of a tree is the number of nodes in the longest path of a  tree.....
//Height of a tree is also called Maximum Depth..
int DepthOrHeight(struct node *node)
{
    if(node == NULL)
        return 0;
    else{
        int lHeight = DepthOrHeight(node->left);
        int rHeight = DepthOrHeight(node->right);

        if(lHeight > rHeight)
            return (lHeight + 1);
        else
            return (rHeight + 1);
    }
}

//A Mirror Tree is a tree with interchanged left and right nodes of original Tree.....
void Mirror(struct node *node)
{
    if(node == NULL || (node->left == NULL && node->right == NULL))
        return;
    else{
        struct node *temp;

        Mirror(node->left);
        Mirror(node->right);

        temp = node->left;
        node->left = node->right;
        node->right = temp;
    }

}

//Print All Paths in the tree.....
void printPaths(struct node *node)
{
    int path[1000];
    printPathRec(node,path,0);
}

void printPathRec(struct node *node,int path[],int pathLen)
{
    if(node == NULL)
        return;

    path[pathLen] = node->data;
    pathLen++;

    if(node->left == NULL && node->right == NULL)
        printPathArray(path,pathLen);
    else{
        printPathRec(node->left,path,pathLen);
        printPathRec(node->right,path,pathLen);
    }
}

void printPathArray(int p[],int pLen)
{
    int i;
    for(i=0;i<pLen;++i)
        printf("%d ",p[i]);

    printf("\n");
}

//Prints Node Values of Each Level starting from Top Level i.e., Root Node.........
void LevelOrder(struct node *node)
{
    int h = DepthOrHeight(node);
    int i;

    for(i=1;i<=h;++i){
        printGivenLevel(node,i);
        printf("\n");
    }
}

void printGivenLevel(struct node *node,int level)
{
    if(node == NULL)
        return;

    if(level == 1)
        printf("%d ",node->data);
    else if(level > 1){
        printGivenLevel(node->left,level-1);
        printGivenLevel(node->right,level-1);
    }
}

//Children Sum Property is satisfied when the values of sum of left and right child nodes id equal to the value of parent node...
int isChildrenSumProperty(struct node *node)
{
    int leftData = 0, rightData = 0;

    if(node == NULL || (node->left == NULL && node->right == NULL))
        return 1;
    else{
        if(node->left != NULL)
            leftData = node->left->data;

        if(node->right != NULL)
            rightData = node->right->data;

        if(node->data = leftData+rightData && isChildrenSumProperty(node->left) && isChildrenSumProperty(node->right))
            return 1;
        else
            return 0;
    }
}

//Convert a tree to satisfy Children Sum Property
void convertTree(struct node *node)
{
    int leftData = 0, rightData = 0, diff;

    if(node == NULL || (node->left == NULL && node->right == NULL))
        return;
    else{
        convertTree(node->left);
        convertTree(node->right);

        if(node != NULL)
            leftData = node->left->data;

        if(node != NULL)
            rightData = node->right->data;

        diff = leftData + rightData - node->data;

        if(diff > 0)
            node->data = node->data + diff;
        else if(diff < 0)
            increment(node,-diff);

    }
}

void increment(struct node *node,int diff)
{
    if(node->left != NULL){
        node->left->data = node->left->data +diff;
        increment(node->left,diff);
    }
    else if(node->right != NULL){
        node->right->data = node->right->data + diff;
        increment(node->right,diff);
    }
}

void DoubleTree(struct node *node)
{
    struct node *temp;

    if(node == NULL)
        return;

    temp = NewNode(node->data);
    temp->left = node->left;
    node->left = temp;

    DoubleTree(temp->left);
    DoubleTree(node->right);
}

//Returns the level of a particular Node...
int getLevel(struct node *root,int data, int level)
{
    if(root == NULL)
        return;

    if(root->data == data)
        return level;

    int corrLevel = getLevel(root->left,data,level+1);
    if(corrLevel!=0)
        return corrLevel;

    corrLevel = getLevel(root->right,data,level+1);
    return corrLevel;
}

struct node *BuildTree(int in[],int pre[],int start,int end)
{
    static int preindex = 0;
    int inIndex;

    if(start>end)
        return NULL;

    struct node *tNode = NewNode(pre[preindex++]);

    if(start == end)
        return tNode;

    inIndex = SearchArr(in,start,end,tNode->data);

    tNode->left = BuildTree(in,pre,start,inIndex-1);
    tNode->right = BuildTree(in,pre,inIndex+1,end);

    return tNode;

}

int SearchArr(int in[],int start,int end,int x)
{
    int i;

    for(i=start;i<=end;++i){
        if(in[i] == x)
            return i;
    }
}

int max(int a,int b)
{
    return (a>b)?a:b;
}

int DiameterOfTree(struct node *node)
{
    if(node == NULL)
        return 0;

    int lheight = DepthOrHeight(node->left);
    int rheight = DepthOrHeight(node->right);

    int ldia = DiameterOfTree(node->left);
    int rdia = DiameterOfTree(node->right);

    return max(lheight + rheight + 1,max(ldia,rdia));
}

int main()
{
    int input,size,height,lev,diameter;
    int in[] = {4,2,5,1,6,3};
    int pre[] = {1,2,4,5,3,6};
    int len = sizeof(in)/sizeof(in[0]);

    struct node *root = NewNode(6);
    root->left = NewNode(3);
    root->right = NewNode(8);
    root->left->left = NewNode(1);
    root->left->right = NewNode(5);
    //root->right->left = NewNode(7);
    //root->right->right = NewNode(9);

    printf("1. Inorder - Recursion\n2. PostOrder - Recursion\n3. PreOrder - Recursion\n4. Level Order - Recursion\n5. Size of a Tree\n6. Depth or Height\n7. Mirror Tree\n8. Print All Paths-Recursion\n9. Children Sum Property\n10. Convert to Children Sum Property\n");
    printf("11. Double Tree\n12. Get Level of a Node\n13. Build Tree - Inorder and PreOrder Given\n14. Diameter of Tree\n");
    do{
        printf("\nEnter Choice\n");
        scanf("%d",&input);
        //printf("\n");
        switch(input)
        {
        case 0:
            printf("\nExiting...\n");
            break;
        case 1:
            printf("\nInorder Traversal.\n");
            Inorder(root);
            printf("\n");
            break;
        case 2:
            printf("\nPostOrder Traversal\n");
            PostOrder(root);
            printf("\n");
            break;
        case 3:
            printf("\nPreOrder Traversal\n");
            PreOrder(root);
            printf("\n");
            break;
        case 4:
            printf("\nLevel Order Traversal\n");
            LevelOrder(root);
            printf("\n");
            break;
        case 5:
            size = SizeOfTree(root);
            printf("\nSize: %d\n",size);
            break;
        case 6:
            height = DepthOrHeight(root);
            printf("\nHeight: %d ",height);
            break;
        case 7:
            Mirror(root);
            break;
        case 8:
            printPaths(root);
            printf("\n");
            break;
        case 9:
            if(isChildrenSumProperty(root))
                printf("The tree satisfies Children Sum Property\n");
            else
                printf("The tree does not satisfy Children Sum Property\n");
            break;
        case 10:
            printf("Converting...");
            convertTree(root);
            printf("\n");
            break;
        case 11:
            printf("Converting to Double Tree...");
            DoubleTree(root);
            printf("\n");
            break;
        case 12:
            printf("Level of a Node...\n");
            lev = getLevel(root,5,1);
            printf("Level is: %d",lev);
            break;
        case 13:
            printf("Building Tree from Inorder and Preorder Traversals...\n");
            struct node *tr = BuildTree(in,pre,0,len-1);
            printf("\nInorder\n");
            Inorder(tr);
            printf("\nLevelOrder\n");
            LevelOrder(tr);
            break;
        case 14:
            printf("\nDiameter of Tree\n");
            diameter = DiameterOfTree(root);
            printf("%d\n",diameter);
            break;
        default:
            printf("\nInvalid Number\n");
            break;
        }
    }while(input>0);

    return 0;
}
