#include <iostream>

using namespace std;

struct Node
{
  double data;
  int left,right;
};

Node nodeList[100000] = {};

void preorder(Node& t)
{
  cout << t.data << " ";
  if (t.left != -1)
    preorder(nodeList[t.left]);
  if (t.right != -1)
    preorder(nodeList[t.right]);
}

void inorder(Node& t)
{
  if (t.left != -1)
    inorder(nodeList[t.left]);
  cout << t.data << " ";
  if (t.right != -1)
    inorder(nodeList[t.right]);
}

void postorder(Node& t)
{
  if (t.left != -1)
    postorder(nodeList[t.left]);
  if (t.right != -1)
    postorder(nodeList[t.right]);
  cout << t.data << " ";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int numberOfNodes;
  cin >> numberOfNodes;

  double num = 0;
  int left, right = -1;

  for (int i = 0; i < numberOfNodes; i++)
  {
    cin >> num >> left >> right;
    nodeList[i].data = num;
    nodeList[i].left = left;
    nodeList[i].right = right;
    //nodeList[left].root = nodeList[right].root =false;
  }

  preorder(nodeList[0]);
  cout << "\n";
  inorder(nodeList[0]);
  cout << "\n";
  postorder(nodeList[0]);
  cout << "\n";

  return 0;
}
