#include <iostream>
#include <queue>

using namespace std;

struct Node
{
  double data;
  int left,right;
};

Node nodeList[100000] = {};

void levelOrder(Node& t, int numberOfNodes)
{
  queue<Node> q;
  for (int i = 0; i < numberOfNodes; i++)
  {
    cout << t.data << " ";

    // put children on queue
    if (t.left != -1)
      q.push(nodeList[t.left]);
    if (t.right != -1)
      q.push(nodeList[t.right]);

    // get next node to visit
    if (i != numberOfNodes - 1)
    {
      t = q.front();
      q.pop();
    }

  }
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

  levelOrder(nodeList[0], numberOfNodes);
  cout << "\n";

  return 0;
}
