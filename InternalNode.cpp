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
  LeafNode* node;
  for (int index = 0; index < count; index++)	
    if (value < keys[index]) {    // search children
      if(index == 0) 
	node = children[index]->insert(value);  // place at minimum if empty
      else
        node = children[index-1]->insert(value);   // place in sorted position
   }
  
  if (node)
    insert(node);

  // students must write this
  return NULL; // to avoid warnings for now.
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  // students must write this
} // InternalNode::insert() */


void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  if (count < leafSize){      // make sure leaf node isn't full
      addChild(newNode);         // insert value in sorted position in array
      count++;          
  } 
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


void InternalNode::addChild(BTreeNode* child)
{
  int key = child->getMinimum();

  if (count == 0 || key > keys[count - 1]) {  // if new max or empty set 
    keys[count] = key;                        // no need to shift
    children[count] = child;
    return;
  }

  if (key < getMinimum()){
    shift(0);
    keys[0] = key;
    children[0] = child;
    return;
  }

  int search;
  // iterate through array and insert key
  for (search = 0; search <= count; search++)
    if (key > keys[search])
      break;

  shift(--search);  //otherwise inserts one element too far
  // actual insert
  keys[search] = key;                           
}


void InternalNode::shift(int startpos){
  for (int hole_r = count; hole_r > startpos; hole_r--){
    keys[hole_r] = keys[hole_r -1];
    children[hole_r] = children[hole_r-1];
  }
} // LeafNode::print()


InternalNode* InternalNode::split()
{
  InternalNode *n = new InternalNode(internalSize, leafSize, parent, this, rightSibling);
  
  rightSibling = n;

  for(int i = (count + 1)/2; i < leafSize; i++){
    n->insert(children[i]);
    count--;
  } // the above should ensure half full
   
  return n;
} // LeafNode::split()
