#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memoryManager.c"

#define ENCODE_SIZE 51

struct node
{
    int feq;
    char data;
    struct node *left;
    struct node *right;
};

typedef struct StrNode
{
    char *str;
    struct StrNode *next;
} StrNode;

StrNode *createNodeForLinkedLIst(StrNode *start)
{
    StrNode *newNode = (StrNode *)MMalloc(sizeof(StrNode));
    newNode->next = NULL;

    newNode->str = (char *)MMalloc(sizeof(char) * ENCODE_SIZE);
    memset(newNode->str, 0, ENCODE_SIZE); // Initialize buffer to zeros

    if (start == NULL)
        start = newNode;
    else
    {
        StrNode *ptr = start;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
    return start;
}

// function to create a node and add to link list.
struct node *createNode(char alp, int feq)
{
    // printf("entered in create node\n");
    struct node *newnode = NULL;                           // creating two struct node type pointer newnode which is a new node of list, ptr which address of what root has which is null currently.
    newnode = (struct node *)MMalloc(sizeof(struct node)); // creating new node;
    newnode->data = alp;                                   // storing alphabate into new nodes's data.
    newnode->feq = feq;                                    // assigning frepuency to 1 because we storing the alphabat which means it occure one's.
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

struct node *joinNode(struct node *root, struct node *newNode)
{
    struct node *ptr = root;
    if (root == NULL) // root is null mens link list not exist.
    {
        root = newNode; // so assigning newnode to root.
    }
    else // if root is not null || linklist exist.
    {
        while (ptr->right != NULL) // traversing untile we reach to last node. if ptr at last node then loop will end.
        {
            ptr = ptr->right;
            // printf("entered in create node->else->while\n")
        }
        ptr->right = newNode; // adding new node at last position.
        newNode->left = ptr;
    }
    // printf("create node check\n");
    return root;
}

void inorderTraversal(struct node *root)
{

    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%c:%d,", root->data, root->feq);
        inorderTraversal(root->right);
    }
    return;
}

// traverse and print the link list.
void traverse(struct node *root)
{
    // printf("entered in traverse\n");
    struct node *ptr = root;
    while (ptr != NULL)
    {
        // printf("traverse->while\n");
        printf("%c: %d\n", ptr->data, ptr->feq);
        ptr = ptr->right;
    }
}

struct node *checkEle(char alp, struct node *root)
{
    // printf("entered on check element\n");
    struct node *newNode, *ptr = root;

    while (ptr != NULL)
    {
        if (ptr->data == alp)
            break;
        // printf("checkele->while\n");
        ptr = ptr->right;
    }

    if (ptr == NULL)
    {
        // printf("checkele->else if\n");
        newNode = createNode(alp, 1);
        root = joinNode(root, newNode);
    }
    else if (ptr->data == alp)
    {
        // printf("checkele->if\n");
        ptr->feq++;
    }
    // printf("checkele check");
    return root;
}

// function to count the frequency //
struct node *count(char *str, struct node *root)
{
    // printf("enter the count\n");

    for (int i = 0; str[i]; i++) // loop to traverse the string
    {

        // printf("enter the count -> for\n");
        root = checkEle(str[i], root); // calling the function to check wheter the element exist in list or not. argument are alphabate nad linked list.
        // traverse(root);
    }
    // traverse(root);
    return root;
}

struct node *sortLinkedList(struct node *root)
{
    // printf("\nentered in sort");
    if (root == NULL || root->right == NULL)
        return root;

    struct node *p, *q;
    int swapped;
    do
    {
        // printf("\nsort-> do while");
        swapped = 0;
        p = root;

        while (p->right != NULL)
        {
            // printf("\nsort-> do while-> while");
            q = p->right;

            if (p->feq < q->feq)
            {
                // printf("\nsort-> do while-> while->if");

                if (p->left != NULL)
                {
                    p->left->right = q;
                    // printf("\nsort-> do while-> while->if->if");
                }
                if (q->right != NULL)
                {
                    q->right->left = p;
                    // printf("\nsort-> do while-> while->if->if");
                }
                p->right = q->right;
                q->left = p->left;
                q->right = p;
                p->left = q;
                // printf("\nswap");

                if (q->left == NULL)
                {
                    root = q;
                    // printf("\n handel root");
                }
                swapped = 1;
            }
            else
            {
                p = p->right;
            }
        }

    } while (swapped);
    // printf("\n After the sort \n");
    // traverse(root);
    return root;
}

struct node *addFrq(struct node *left, struct node *right)
{
    struct node *parent;
    int newFrq;
    newFrq = left->feq + right->feq;
    parent = createNode('\0', newFrq);
    parent->left = left;
    parent->right = right;
    return parent;
}

struct node *huffmanTree(struct node *root)
{
    printf("entered huffman\n");
    // Handle edge cases
    if (root == NULL || root->right == NULL)
    {
        return root;
    }

    struct node *q = NULL;      // for second minimum node
    struct node *p = root;      // for first minimum node
    struct node *parent = NULL; // for new parent node
    struct node *temp = NULL;   // for keeping track of next node
    int nodesRemaining = 1;     // to track if we still have nodes to process

    // Go to last node (minimum frequency)
    while (p->right != NULL)
    {
        // printf("traverse->while\n");
        p = p->right;
        nodesRemaining++;
    }

    // Disconnect the link list connection
    if (p->left != NULL)
    {
        p->left->right = NULL;
    }

    do
    {
        // printf("huff->do while\n");
        if (q == NULL)
        { // First iteration or after parent becomes root
            // printf("huff-> do while-> first case\n");
            if (p == NULL)
            {
                break; // No more nodes to process
            }
            // Get last two nodes
            q = p->left; // Second last node
            if (q == NULL)
            {
                return p; // Only one node left
            }
            temp = q->left; // Third last node

            // Disconnect horizontal links
            q->left = NULL;
            p->left = NULL;
            if (temp != NULL)
            {
                temp->right = NULL;
            }

            // Create first subtree
            parent = (p->feq < q->feq) ? addFrq(p, q) : addFrq(q, p);
            // printf("Created parent with freq %d\n", parent->feq);
            nodesRemaining--;
        }
        else
        { // Subsequent iterations
            // printf("huff-> do while-> combining subtrees\n");
            q = parent;
            p = temp;

            if (p == NULL)
            {
                return q; // No more nodes to combine
            }

            // Get next node if available
            temp = p->left;
            if (temp != NULL)
            {
                temp->right = NULL;
            }
            p->left = NULL;

            // Create new subtree
            parent = (p->feq < q->feq) ? addFrq(p, q) : addFrq(q, p);
            printf("Created new parent with freq %d\n", parent->feq);
            nodesRemaining--;
        }
    } while (nodesRemaining > 0);

    // printf("huff -> do while finished\n");
    return parent;
}

void printEncodedMessage(StrNode *start)
{
    printf("Encoded message \n");
    while (start != NULL)
    {
        printf("%s", start->str);
        start = start->next;
    }
}

int findchar(char alp, char *LR, struct node *root, int index)
{
    // printf("\ninside findchar\n");
    if (root == NULL)
        return 0;
    if (root->data == alp)
    {
        LR[index] = '\0';
        // printf("inside findchar data == alp\n");
        // printf("\npath to '%c' : %s\n",alp, LR);
        return 1;
    }

    LR[index] = '0';
    // printf("going to left\n");
    if (findchar(alp, LR, root->left, index + 1))
        return 1;

    LR[index] = '1';
    // printf("going to right\n");
    if (findchar(alp, LR, root->right, index + 1))
        return 1;

    // printf("going to backtrack\n");
    LR[index] = '\0';

    return 0;
}

StrNode* encodingMessage(char *str, struct node *root)
{
    // printf("\ninside encode\n");
    StrNode *start = NULL;

    int inparr = 0;

    char LR[100];
    start = createNodeForLinkedLIst(start);
    StrNode *ptr = start;
    while (ptr->next != NULL)
        ptr = ptr->next;
    printf("ptr at last\n");
    for (int i = 0; str[i]; i++)
    {
        findchar(str[i], LR, root, 0);
        printf("\npath to '%c' : %s\n", str[i], LR);
        // printf("inside the for loop\n");

        if (start->str[inparr] == '\0')
        {
            //  printf("inside for->if\n");
            createNodeForLinkedLIst(start);
            inparr = 0;
            while (ptr->next != NULL)
                ptr = ptr->next;
            // printf("if->copying data from LR to linked list\n");
            for (int j = 0; LR[j]; j++)
            {
                ptr->str[inparr] = LR[j];
                inparr++;
            }
            // printf("if->copying complet\n");
        }
        else
        {
            // printf("else->copying data from LR to linked list\n");
            for (int j = 0; LR[j]; j++)
            {
                ptr->str[inparr] = LR[j];
                inparr++;
            }
            // printf("else->copying complet\n");
        }
    }
    printEncodedMessage(start);
    return start;  // Return the start pointer
}

void freeHuffmanTree(struct node* root) {
    if (root == NULL) {
        return;
    }
    
    // Post-order traversal to free nodes
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    MFree(root);
}

void freeEncodedList(StrNode* start) {
    StrNode* current = start;
    StrNode* next;
    
    while (current != NULL) {
        next = current->next;
        MFree(current->str);  // Free the string buffer first
        MFree(current);       // Then free the node itself
        current = next;
    }
}

void encode(char str[])
{
    struct node *root = NULL;
    root = count(str, root);
    printf("After counting frequencies:\n");
    traverse(root);
    
    root = sortLinkedList(root);
    printf("\nAfter sorting:\n");
    traverse(root);
    
    root = huffmanTree(root);
    printf("\nFinal Huffman Tree:\n");
    inorderTraversal(root);
    
    StrNode* encodedList = encodingMessage(str, root);  // Store the returned pointer
    
    // Free all allocated memory
    freeHuffmanTree(root);
    freeEncodedList(encodedList);  // Use the stored pointer
    
}

void decoder(char str[])
{
       printf("\n Please provide encoded message:-\n");

}
// Update main() to use these functions:
int main() {
    char choice[2];
    char str[100];
    do
    {   
        printf("\nProvide your chioice (for encode (-e), for decode (-d) & for exit (-o))\nSelect: ");
        fflush(stdin);
        scanf("%s", choice);
        
        if (!strcmp("-e", choice))
        {
            printf("Enter the string: ");
            fflush(stdin);
            fgets(str, sizeof(str), stdin);
            str[strlen(str) - 1] = '\0';
            encode(str);
        }
        else if (!strcmp("-d", choice))
        {
           printf("Please provide the key:-\n");
           scanf("%s",&str);
           decoder(str);
        }

        else if(!strcmp("-o", choice)) break;

        else printf("Warning : Invalid choice");

    } while (1);
    
    return 0;
}