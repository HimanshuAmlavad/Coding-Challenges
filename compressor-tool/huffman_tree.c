#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int feq;
    char data;
    struct node *left;
    struct node *right;
};

// struct node *createNode(struct node *root)
// {
//     struct node *newNode;
//     newNode = (struct node *)malloc(sizeof(struct node));

//     newNode->left = NULL;
//     newNode->right = NULL;

//     return newNode;
// }

// function to create a node and add to link list.
struct node *createNode(char alp, int feq)
{
    // printf("entered in create node\n");
    struct node *newnode = NULL;                          // creating two struct node type pointer newnode which is a new node of list, ptr which address of what root has which is null currently.
    newnode = (struct node *)malloc(sizeof(struct node)); // creating new node;
    newnode->data = alp;                                  // storing alphabate into new nodes's data.
    newnode->feq = feq;                                   // assigning frepuency to 1 because we storing the alphabat which means it occure one's.
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
    traverse(root);
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
    traverse(root);
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
    if (root == NULL || root->right == NULL) {
        return root;
    }

    struct node *q = NULL;      // for second minimum node
    struct node *p = root;      // for first minimum node
    struct node *parent = NULL; // for new parent node
    struct node *temp = NULL;   // for keeping track of next node
    int nodesRemaining = 1;     // to track if we still have nodes to process
    
    // Go to last node (minimum frequency)
    while (p->right != NULL) {
        printf("traverse->while\n");
        p = p->right;
        nodesRemaining++;
    }
    
    // Disconnect the link list connection
    if (p->left != NULL) {
        p->left->right = NULL;
    }

    do {
        printf("huff->do while\n");
        if (q == NULL) { // First iteration or after parent becomes root
            printf("huff-> do while-> first case\n");
            if (p == NULL) {
                break;  // No more nodes to process
            }
            // Get last two nodes
            q = p->left;        // Second last node
            if (q == NULL) {
                return p;  // Only one node left
            }
            temp = q->left;     // Third last node
            
            // Disconnect horizontal links
            q->left = NULL;
            p->left = NULL;
            if (temp != NULL) {
                temp->right = NULL;
            }
            
            // Create first subtree
            parent = (p->feq < q->feq) ? addFrq(p, q) : addFrq(q, p);
            printf("Created parent with freq %d\n", parent->feq);
            nodesRemaining--;
        }
        else { // Subsequent iterations
            printf("huff-> do while-> combining subtrees\n");
            q = parent;
            p = temp;
            
            if (p == NULL) {
                return q;  // No more nodes to combine
            }
            
            // Get next node if available
            temp = p->left;
            if (temp != NULL) {
                temp->right = NULL;
            }
            p->left = NULL;
            
            // Create new subtree
            parent = (p->feq < q->feq) ? addFrq(p, q) : addFrq(q, p);
            printf("Created new parent with freq %d\n", parent->feq);
            nodesRemaining--;
        }
    } while (nodesRemaining > 0);

    printf("huff -> do while finished\n");
    return parent;
}

int main() 
{
    char str[20];
    struct node *root = NULL;
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    // printf("mainfunction input taken\n%s", str);

    root = count(str, root);
    printf("After counting frequencies:\n");
    traverse(root);
    
    root = sortLinkedList(root);
    printf("\nAfter sorting:\n");
    traverse(root);
    
    root = huffmanTree(root);
    printf("\nFinal Huffman Tree:\n");
    inorderTraversal(root);
    
    return 0;
}