/* C++ program to construct tree using inorder and
   postorder traversals */
#include <iostream>
#include <queue>
using namespace std;

/* A binary tree node has data, pointer to left
   child and a pointer to right child */
struct Node
{
    int data;
    Node* left, * right;
};

// Utility function to create a new node
Node* newNode(int data);

/* Prototypes for utility functions */
int search(int arr[], int strt, int end, int value);

/* Recursive function to construct binary of size n
   from  Inorder traversal in[] and Preorder traversal
   post[].  Initial values of inStrt and inEnd should
   be 0 and n -1.  The function doesn't do any error
   checking for cases where inorder and postorder
   do not form a tree */
Node* buildUtil(int in[], int post[], int inStrt,
                int inEnd, int *pIndex)
{
    // Base case
    if (inStrt > inEnd)
        return NULL;

    /* Pick current node from Preorder traversal using
       postIndex and decrement postIndex */
    Node *node = newNode(post[*pIndex]);
    (*pIndex)--;

    /* If this node has no children then return */
    if (inStrt == inEnd)
        return node;

    /* Else find the index of this node in Inorder
       traversal */
    int iIndex = search(in, inStrt, inEnd, node->data);

    /* Using index in Inorder traversal, construct left and
       right subtress */
    node->right= buildUtil(in, post, iIndex+1, inEnd, pIndex);
    node->left = buildUtil(in, post, inStrt, iIndex-1, pIndex);

    return node;
}

// This function mainly initializes index of root
// and calls buildUtil()
Node *buildTree(int in[], int post[], int n)
{
    int pIndex = n-1;
    return buildUtil(in, post, 0, n - 1, &pIndex);
}

/* Function to find index of value in arr[start...end]
   The function assumes that value is postsent in in[] */
int search(int arr[], int strt, int end, int value)
{
    int i;
    for (i = strt; i <= end; i++)
    {
        if (arr[i] == value)
            break;
    }
    return i;
}

/* Helper function that allocates a new node */
Node* newNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return (node);
}

// /* This funtcion is here just to test  */
// void preOrder(Node* node)
// {
//     if (node == NULL) return;
//     cout << node->data << " ";
//     preOrder(node->left);
//     preOrder(node->right);
// }


void levelOrder(Node* node, int n)
{
  queue<Node*> q;
  for (int i = 0; i < n; i++)
  {
    cout << node->data << " ";;

    // put the node's children on the queue
    if (node->left != NULL)
      q.push(node->left);
    if (node->right != NULL)
      q.push(node->right);

    // get next node
    if (i != n-1)
    {
      node = q.front();
      q.pop();
    }

  }
}

int main()
{

  int numberOfNodes = 0;
  cin >> numberOfNodes;
  int post[numberOfNodes];
  int in[numberOfNodes];

  for (int i = 0; i < numberOfNodes; i++)
  {
    int element;
    cin >> element;
    post[i] = element;
  }

  for (int j = 0; j < numberOfNodes; j++)
  {
    int el;
    cin >> el;
    in[j] = el;
  }

  Node *root = buildTree(in, post, numberOfNodes);

  // std::cout << "Preorder of the tree: \n";
  // preOrder(root);
  // cout << "\n";

  //std::cout << "Level-order of the tree: \n";
  levelOrder(root, numberOfNodes);
  cout << "\n";


  return 0;

}
