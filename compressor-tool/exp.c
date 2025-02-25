struct node
{
    int data;
    struct node *next;
};

void linklisttraversal(struct node * ptr){
    while(ptr != NULL){
    printf("element : %d\n",ptr->data);
    ptr= ptr->next;
    }
} 

struct node * insertAtbegining(struct node* head , int data){
    struct node* ptr = (struct node *)malloc(sizeof(struct node));
    ptr->next = head;
    ptr->data = data;
    return ptr;
}


void createNode(int data){
    struct node * newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
}

int main(){
    struct node *head ;
    struct node *second;
    struct node *third ;
    head = (struct node*)malloc(sizeof(struct node));
    second = (struct node*)malloc(sizeof(struct node));
    third = (struct node*)malloc(sizeof(struct node));

    head ->data = 7;
    head -> next = second;

    second ->data = 5;
    second -> next = third;

    third ->data = 1;
    third -> next = NULL;

    linklisttraversal(head);
    head = insertAtbegining(head,56);
    linklisttraversal(head);