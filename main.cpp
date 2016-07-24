#include <iostream>
#include<stack>
#include<queue>

using namespace std;

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *NewNode(int data)
{
    struct node *node1 = new node;

    node1->data = data;
    node1->left = NULL;
    node1->right = NULL;

    return node1;
};

/*
Algorithm for Inorder Using Stack
    1-Create an Empty Stack
    2-Current Node = Root Node
    3-If Current != NULL push the current node to Stack and set current = current->left
    4-If Current = NULL and stack is not empty,
        -Pop The Top Element from Stack
        -Print the item and set current = poppedItem->right
        -Go to 3
    5-If Current = NULL and Stack is Empty, Exit.
*/
void InorderIter(struct node *root)
{
    if(root == NULL)
        return;

    stack<node*> inorderStack;

    node *curr = root;

    while(curr!=NULL || !(inorderStack.empty()))
    {
        if(curr != NULL)
        {
            inorderStack.push(curr);
            curr = curr->left;
        }
        else if(curr == NULL && !(inorderStack.empty()))
        {
            node *temp = inorderStack.top();
            cout<<temp->data<<" ";
            inorderStack.pop();
            curr = temp->right;
        }
    }
}

/*
Algorithm
    1-Create an Empty Stack
    2-Push the Root Node onto the Stack.
    3-While Stack is not Empty
        -Pop the top element and print its value
        -Push the right node on to the stack
        -Push the left node on to the stack
*/
void PreOrderIter(struct node *root1)
{
    if(root1 == NULL)
        return;

    stack<node*> preorderStack;
    preorderStack.push(root1);

    while(!preorderStack.empty())
    {
        struct node *temp = preorderStack.top();
        cout<<temp->data<<" ";
        preorderStack.pop();

        if(temp->right)
            preorderStack.push(temp->right);
        if(temp->left)
            preorderStack.push(temp->left);
    }
}

/*
Algorithm
    - Create 2 Stacks - StackOne and StackTwo
    - Push root to StackOne
    - While StackOne is not Empty
        - Pop the top Node from StackOne
        - Push the node to StackTwo
        - Push the left and right nodes of popped node to StackOne
    - When StackOne is Empty, print the values of StackTwo.
*/
void postOrderTwoStack(struct node *root)
{
    stack<node*> StackOne;
    stack<node*> StackTwo;

    StackOne.push(root);

    while(!StackOne.empty())
    {
        struct node *top = StackOne.top();
        StackOne.pop();

        StackTwo.push(top);

        if(top->left)
            StackOne.push(top->left);
        if(top->right)
            StackOne.push(top->right);
    }

    while(!StackTwo.empty())
    {
        struct node *top = StackTwo.top();
        cout<<top->data<<" ";
        StackTwo.pop();
    }
}

/*
Algorithm
    - Create a Stack
    - Do the following while Stack is not Empty
        - While root is not NULL
            - If root has right child, push right child on to stack
            - Then, push root to stack
            - Set root = root->left
        - Pop a node from Stack. Let root be popped node.
        - If popped item's right child is on top of stack
            - Pop the node from Stack
            - Push root to Stack
            - Set root = root->right
        - Else, Print the Value of Node at top and set root = NULL
*/
void postOrderOneStack(struct node *root)
{
    if(root == NULL)
        return;

    stack<node*> postOrderStack;

    do
    {
        while(root)
        {
            if(root->right)
                postOrderStack.push(root->right);
            postOrderStack.push(root);
            root = root->left;
        }

        root = postOrderStack.top();
        postOrderStack.pop();

        if(root->right && !postOrderStack.empty() && postOrderStack.top() == root->right)
        {
            struct node *top = postOrderStack.top();
            postOrderStack.pop();
            postOrderStack.push(root);
            root = root->right;
        }
        else{
            cout<<root->data<<" ";
            root = NULL;
        }
    }while(!postOrderStack.empty());
}

void LevelOrderIterative(struct node *root)
{
    if(root == NULL)
        return;

    queue<node*> LevelQueue;

    LevelQueue.push(root);


    while(!LevelQueue.empty())
    {
        //int qSize = LevelQueue.size();
        //int _left = 0, _right = 0;

        //while(qSize>0)
        //{
            struct node *top = LevelQueue.front();
            cout<<top->data<<" ";
            LevelQueue.pop();

            if(top->left){
                LevelQueue.push(top->left);
                //_left = top->left->data;
            }
            if(top->right){
                LevelQueue.push(top->right);
                //_right = top->right->data;
            }
/*
            if(top->left && top->right && !(_left + _right == top->data))
            {
                cout<<"Noooooooooooooooo\n";
                return 0;
            }
*/
            //qSize--;
        //}
        //cout<<"\n";
    }
    cout<<"\n";
    //return 1;

}

void BottomView(struct node *root)
{
    bool right1 = true;
    bool print;

    if(root == NULL)
        return;

    if(root->left == NULL && root->right == NULL)
    {
        cout<<root->data<<" ";
        return;
    }

    if(root->left)
    {
        if(!root->left->right)
        {
            right1 = true;
            print = true;
        }
        else
        {
            right1 = false;
            print = false;
        }
    }
    if(root->right && right1)
    {
        if(root->right->left)
            print = false;
    }

    if(print)
        cout<<root->data<<" ";

    BottomView(root->left);
    BottomView(root->right);
}

int main()
{
    int inp,level;
/*
    struct node *root = NewNode(20);
    root->left = NewNode(8);
    root->right = NewNode(22);0
    //root->right->left = NewNode(4);
    root->left->left = NewNode(5);
    root->right->right = NewNode(25);
    root->left->right = NewNode(3);
    root->left->right->left = NewNode(10);
    root->left->right->right = NewNode(14);
    //root->right->right->left = NewNode(7);
*/

    struct node *root = NewNode(6);
    root->left = NewNode(4);
    root->right = NewNode(2);
    root->left->left = NewNode(1);
    root->left->right = NewNode(3);
    root->right->left = NewNode(2);

    cout <<"1. Inorder\n2. PreOrder\n3. PostOrder - Using Two Stacks\n4. PostOrder - Using One Stack\n5. Level Order Traversal - Iterative Method\n6. Bottom View\n";
    do{
        cout<<"\nEnter choice:\n";
        cin>>inp;
        switch(inp)
        {
        case 0:
            cout<<"\nExiting...\n";
            break;
        case 1:
            cout<<"\nInorder Traversal\n";
            InorderIter(root);
            cout<<"\n";
            break;
        case 2:
            cout<<"\nPreOrder Traversal\n";
            PreOrderIter(root);
            cout<<"\n";
            break;
        case 3:
            cout<<"Post Order Traversal Using Two Stacks\n";
            postOrderTwoStack(root);
            cout<<"\n";
            break;
        case 4:
            cout<<"\nPostOrder Traversal Using One Stack\n";
            postOrderOneStack(root);
            break;
        case 5:
            cout<<"\nLevel Order Traversal - Iterative Method\n";
            LevelOrderIterative(root);
            //cout<<level;
            cout<<"\n";
            break;
        case 6:
            cout<<"Bottom View of Tree\n";
            BottomView(root);
            cout<<"\n";
            break;
        default:
            cout<<"\nInvalid Number. Please Try Again\n";
            break;
        }
    }while(inp>0);
    return 0;
}
