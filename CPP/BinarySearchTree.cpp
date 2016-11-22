#include <iostream>

using namespace std;

int sum = 0;

struct node
{
    int data;
    node *left;
    node *right;
};

struct node *NewNode(int data)
{
    struct node *temp = new node;

    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
};

struct node *Insert(struct node *node, int key)
{
    if (node == NULL) return NewNode(key);

    if (key < node->data)
        node->left  = Insert(node->left, key);
    else if (key > node->data)
        node->right = Insert(node->right, key);

    return node;
}

struct node *SearchTree(struct node *root, int key)
{
    if(!root)
        return NULL;

    while(root)
    {
        if(root->data == key)
            return root;
        else if(key < root->data)
            root = root->left;
        else if(key > root->data)
            root = root->right;
    }

    return NULL;
}

void LevToInorder(int arr[], int start, int end)
{
    if(start > end)
        return;

    LevToInorder(arr,2*start+1,end);
    cout<<arr[start]<<" ";
    LevToInorder(arr,2*start+2,end);
}

struct node *ContructTreeFromIN(int in[],int s, int e)
{
    int mid;

    if(s>e)
        return NULL;

    if((e-s)%2==0)
        mid = (s+e)/2;
    else
        mid = (s+e)/2 + 1;

    struct node *tNode = NewNode(in[mid]);

    tNode->left = ContructTreeFromIN(in,s,mid-1);
    tNode->right = ContructTreeFromIN(in,mid+1,e);

    return tNode;
}

struct node *MinValue(struct node *node)
{
    struct node *current = node;

    while(current->left)
        current = current->left;

    return node;
}

struct node *MaxValue(struct node *node)
{
    while(node->right)
        node = node->right;

    return node;
}
/*
Alternative Method - Time Compexity = O(n), where n = No. of nodes in Tree

    1-Perform Inorder Traversal and store the result in an Array
    2-While performing Inorder Traversal, store the index of Node 'n' in a global variable.
    3-Successor = Array[index+1];
    4-Predecessor = Array[index-1];
*/

//Time Complexity - O(h) where h = height of Tree
struct node *InSucc(struct node *root, struct node *n)
{
    if(n->right)
        return MinValue(n->right);

    struct node *successor = NULL;

    while(root)
    {
        if(n->data < root->data)
        {
            successor = root;
            root = root->left;
        }
        else if(n->data > root->data)
            root = root->right;
        else
            break;
    }

    return successor;
}

//Time Complexity - O(h) where h = height of Tree
struct node *InPred(struct node *root, struct node *n)
{
    if(n->left)
        return MaxValue(n->left);

    struct node *predecessor = NULL;

    while(root)
    {
        if(n->data < root->data)
            root = root->left;
        else if(n->data > root->data)
        {
            predecessor = root;
            root = root->right;
        }
        else
            break;
    }

    return predecessor;
}

int isBST(int a[], int b[], int size1,int size2)
{
    if(size1 == size2 && size1 == 0)
        return 1;

    if(size1 != size2)
        return 0;

    int l1[size1],l2[size1],l3[size1],l4[size1];

    if(size1 == 1)
    {
        if(a[0] == b[0])
            return 1;
        else
            return 0;
    }

    int c1,c2,c3,c4;
    c1=c2=c3=c4=0;

    if(a[0] == b[0])
    {
        for(int i=1;i<size1;++i)
        {
            if(a[i]<a[0])
            {
                l1[c1] = a[i];
                c1++;
            }
            else
            {
                l3[c3] = a[i];
                c3++;
            }
        }

        for(int i=1;i<size2;++i)
        {
            if(b[i]<b[0])
            {
                l2[c2] = b[i];
                c2++;
            }
            else
            {
                l4[c4] = b[i];
                c4++;
            }
        }

        int left = isBST(l1,l2,c1,c2);
        int right = isBST(l3,l4,c3,c4);

        return (left && right);
    }
    else
        return 0;
}

void Inorder(struct node *root)
{
    if(root == NULL)
        return;

    Inorder(root->left);
    cout<<root->data<<" ";
    Inorder(root->right);
}

//Using Reverse Inorder Traversal
void ModifyBST(struct node *root)
{
    if(!root)
        return;

    ModifyBST(root->right);

    sum += root->data;
    root->data = sum;

    ModifyBST(root->left);

}

void CeilandFloor(struct node *root, int input)
{
    if(root == NULL)
        return;

    struct node *ceilNode;
    struct node *floorNode;

    while(root)
    {
        if(input == root->data)
        {
            ceilNode = floorNode = root;
            break;
        }
        else if(input < root->data)
        {
            ceilNode = root;
            root = root->left;
        }
        else if(input > root->data)
        {
            floorNode = root;
            root = root->right;
        }
    }

    cout<<"Ceil: "<<ceilNode->data<<"\n";
    cout<<"Floor: "<<floorNode->data<<"\n";
}

struct node *DeleteNode(struct node *root,int data)
{
    if(!root)
        return NULL;

    if(data < root->data)
        root->left = DeleteNode(root->left,data);
    else if(data > root->data)
        root->right = DeleteNode(root->right,data);
    else
    {
        //Case 1: Leaf Node
        if(!root->left && !root->right)
        {
            delete root;
            root = NULL;
        }
        //Case 2: Left Node is Null
        else if(root->left == NULL)
        {
            struct node *temp = root;
            root = root->right;
            delete temp;
        }
        //Case 3: Right Node is NULL
        else if(root->right == NULL)
        {
            struct node *temp = root;
            root = root->left;
            delete temp;
        }
        //Case 4: Node has two Children
        else
        {
            struct node *temp = MinValue(root->right);
            root->data = temp->data;
            root->right = DeleteNode(root->right,temp->data);
        }
    }

    return root;
}

int main()
{
    int inp,num,suc,pred,isBst,ceil;
    int bst1[] = {8,3,6,1,4,7,10,14,13};
    int bst2[] = {8,10,14,3,6,4,1,7,13};
    int arr[] = {6,4,9,3,5,7,11};
    int in[] = {3,4,5,6,7,9,11};
    struct node *tree,*found,*Del;
    struct node *iSucc1,*iSucc2;
    struct node *iPred1,*iPred2;

    struct node *root = NULL;
    root = Insert(root, 50);
    Insert(root, 30);
    Insert(root, 20);
    Insert(root, 40);
    Insert(root, 70);
    Insert(root, 60);
    Insert(root, 80);

    cout<<"1. Insert\n2. Search\n3. Delete\n4. Inorder Traversal\n5. Level Order Traversal to Inorder\n6. Construct BST from Inorder Traversal\n7. Inorder Successor\n8. Inorder Predecessor\n9. Check if 2 BST's are Identical\n10. Add All Values greater to every node in BST\n11. Ceil and Floor Value\n";
    do{
        cout<<"\nEnter choice:\n";
        cin>>inp;
        switch(inp)
        {
        case 0:
            cout<<"\nExiting...\n";
            break;
        case 1:
            cout<<"\nEnter number to insert:\n";
            cin>>num;
            Insert(root,num);
            break;
        case 2:
            cout<<"\nEnter number to search:\n";
            cin>>num;
            found = SearchTree(root,num);
            if(found)
                cout<<"\nFound the element in Tree\n";
            else
                cout<<"\nElement Not Found\n";
            break;
        case 3:
            cout<<"\nEnter number to delete:\n";
            cin>>num;
            Del = DeleteNode(root,num);
            Inorder(Del);
            cout<<"\n";
            break;
        case 4:
            cout<<"\nInorder Traversal\n";
            Inorder(root);
            cout<<"\n";
            break;
        case 5:
            cout<<"\nGiven: Array of Level Order Traversal\nOutput: Inorder Traversal i.e., Sorted Order of Array in O(n)\n\n";
            LevToInorder(arr,0,6);
            cout<<"\n";
            break;
        case 6:
            cout<<"\nGiven: Sorted Array i.e.e Inorder Traversal of BST\n";
            cout<<"Contructing Tree...\n";
            tree = ContructTreeFromIN(in,0,6);
            cout<<"\n";
            Inorder(tree);
            cout<<"\n";
            break;
        case 7:
            cout<<"\nEnter the num whose Inorder Successor Has to be Found.\n";
            cin>>suc;
            iSucc1 = SearchTree(root,suc);
            iSucc2 = InSucc(root,iSucc1);
            cout<<"\nInorder Successor of "<<suc<<" is "<<iSucc2->data;
            cout<<"\n";
            break;
        case 8:
            cout<<"\nEnter the num whose Inorder Predecessor Has to be Found.\n";
            cin>>pred;
            iPred1 = SearchTree(root,pred);
            iPred2 = InPred(root,iPred1);
            cout<<"\nInorder Predecessor of "<<pred<<" is "<<iPred2->data;
            cout<<"\n";
            break;
        case 9:
            isBst = isBST(bst1,bst2,9,9);
            (isBst)?cout<<"\nIdentical\n":cout<<"\nNot Identical\n";
            break;
        case 10:
            ModifyBST(root);
            break;
        case 11:
            cout<<"\nEnter a value:\n";
            cin>>num;
            CeilandFloor(root,num);
            break;
        default:
            cout<<"Invalid Choice.\n";
            break;
        }
    }while(inp>0);

    return 0;
}
