#include <iostream>
using namespace std;

struct Node
{
  Node *next;
  int val;
};

/* 
  - you need to pass in Node** not Node*
    as the head will be re-assigned to
    the new node, which means you need
    to pass in a pointer that points to
    curren head of Node*, and we can later 
    change it to point to the new node(head).
*/
void push(Node **head, int val)
{
  Node *newNode = new Node;
  newNode->next = *head;
  newNode->val = val;
  /* the node pushed is the new head */
  *head = newNode;
}

void printList(Node *head)
{
  while (head != nullptr)
  {
    cout << head->val;
    if (head->next != nullptr)
      cout << " -> ";
    head = head->next;
  }
}

/* 0->2->-5->5->10->-10 */
void testFixture1(Node **head)
{
  push(head, -10);
  push(head, 10);
  push(head, 5);
  push(head, -5);
  push(head, 2);
  push(head, 0);
}
/* 0->1->2 */
void testFixture2(Node **head)
{
  push(head, 2);
  push(head, 1);
  push(head, 0);
}

/* takeaways
   - the two pointers solution is
     the best IMO
   - the key here is to move the
     negative numbers to the head
     one by one
     - it works because the smallest
       negative number will be 
       the last one to be moved
       to head as it will appear
       as the last one among negative
       numbers in the original list
     - for example
       0->2->-5->5->10->-10
       we will visit the negative numbers
       in this order -5 -> -10 
*/
void sortList(Node **head)
{
  Node *prev = (*head);
  Node *curr = (*head)->next;

  while (curr != nullptr)
  {
    /*
          - curr->val must be a negative value
            - since the list was sorted by abs value
              the smaller negative numbers will be
              after the bigger negative numbers
              -5 -> ... -> -10
              don't forget -5 is bigger than -10 :-) 
          - for negative values we are visiting from
            big to small in the list
            - keep moving them to the head one by
              one and you are done.
          - for positive numbers they are already
            in order so we don't need to do
            anything when we encounter them       
        */
    if (curr->val < prev->val)
    {
      /*  
              - move the curr to the head
            */
      // by pass curr
      prev->next = curr->next;
      /*
              - curr is the new head
                - its next will be the old head
                - and we set the head to point
                  to curr 
            */
      curr->next = (*head);
      (*head) = curr;

      /* align the curr with prev (two pointers) 
               - we can think of this as visiting a
                 another shorter, as the curr has been moved
                 to the head, which starts at prev.
               - so from that sense curr is reset to prev  
            */
      curr = prev;
    }
    /* must be positive numbers; prev can move on */
    else
    {
      prev = curr;
    }

    /*  
          - send the scout again out
            - at this point curr and prev should be the same
            - so the curr can advance to the next 
        */
    curr = curr->next;
  }
}

void test1()
{
  Node *head = nullptr;
  testFixture1(&head);
  cout << "test fixture 1" << endl;
  printList(head);
  sortList(&head);
  cout << endl
       << "test result 1:" << endl;
  printList(head);
}
void test2()
{
  Node *head = nullptr;
  testFixture2(&head);
  cout << "test fixture 2" << endl;
  printList(head);
  sortList(&head);
  cout << endl
       << "test result 2:" << endl;
  printList(head);
  cout << endl;
}

main()
{
  test1();
  test2();
  return 0;
}