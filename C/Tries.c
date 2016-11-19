#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

struct trie_node
{
    int data;
    struct trie_node *children[26];
};

struct trie_node *getNode()
{
    struct trie_node *pNode =(struct trie_node*)malloc(sizeof(struct trie_node));

    if(pNode)
    {
        int i;

        pNode->data = 0;

        for(i = 0;i < 26;++i)
        {
            pNode->children[i] = NULL;
        }
    }

    return pNode;
}

void insert(struct trie_node *_trie,char key[])
{
    int i,index,length;
    length = strlen(key);
    struct trie_node *node = _trie;

    for(i = 0;i < length;++i)
    {
        index = CHAR_TO_INDEX(key[i]);
        if(node->children[index] == NULL)
        {
            node->children[index] = getNode();
        }
        node = node->children[index];
        //printf("I: %d Ind: %d NV: %d\n",i,index,node->data);
    }

    node->data = i;
    //printf("----\n");
    //printf("\n%d\n",node->data);
}

int search(struct trie_node *_trie, char key[])
{
    int i,index;
    int length = strlen(key);
    struct trie_node *node = _trie;

    for(i = 0;i < length;++i)
    {
        index = CHAR_TO_INDEX(key[i]);
        if(!node->children[index])
        {
            return 0;
        }
        node = node->children[index];
    }

    return node->data;
}

void prefixString(struct trie_node *_trie,char key[])
{
    int i,index,count = 0,flag = 0;
    int length = strlen(key);
    //printf("\nLen: %d\n",length);
    struct trie_node *node = _trie;

    for(i = 0;i < length;++i)
    {
        index = CHAR_TO_INDEX(key[i]);
        if(!node->children[index])
        {
            break;
        }
        node = node->children[index];
        if(node->data > count)
            count = node->data;
        //printf("I: %d Ind: %d NV: %d\n",i,index,node->data);
    }
    //printf("\n%d\n",count);
    for(i = 0;i < count;i++)
    {
        printf("%c",key[i]);
    }
}

int isLeafNode(struct trie_node *node)
{
    return (node->data != 0);
}

int isFreeNode(struct trie_node *node)
{
    int i;

    for(i = 0;i < 26; ++i)
    {
        if(node->children[i])
            return 0;
    }

    return 1;
}

int delete(struct trie_node *pnode,char key[],int limit,int len)
{
    int index;

    if(pnode)
    {
        if(limit == len)
        {
            pnode->data = 0;

            if(isFreeNode(pnode))
            {
                return 1;
            }

            return 0;
        }
        else
        {
            index = CHAR_TO_INDEX(key[limit]);

            if(delete(pnode->children[index],key,limit+1,len))
            {
                free(pnode->children[index]);
                pnode->children[index] = NULL;

                return (!isLeafNode && isFreeNode(pnode));
            }
        }
    }

    return 1;
}

int main()
{
    int i,found;
    char keys[][8] = {"the","a","there","answer","any","by","bye","their"};

    struct trie_node *_trie = getNode();

    for(i = 0;i < 8; ++i)
    {
        insert(_trie,keys[i]);
    }
    //insert(_trie,"the");
    //insert(_trie,"there");
/*
    found = search(_trie,"ther");

    if(found)
        printf("\nFound\n");
    else
        printf("\nNot Found\n");
*/
    prefixString(_trie,"th");

    //delete(_trie,keys[0],0,3);

    return 0;
}
