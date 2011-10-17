#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[(int)ISize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [(int)ISize];
} // InternalNode::InternalNode()

int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value) 
/* base case: check if full array, if not add */
{
  for (int index = 0; index < count; index++)	
    if (value < keys[index]) {    // search children
      if(index == 0) 
	children[index]->insert(value);  // place at minimum if empty
      else
        children[index-1]->insert(value);   // place in sorted position
   }
  // students must write this
  return NULL; // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  // students must write this
} // InternalNode::insert() */

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  // students may write this
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


