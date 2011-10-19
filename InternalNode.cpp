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
{

  BTreeNode* node = NULL;
  InternalNode* split = NULL;

  bool found = false;
  for (int index = 0; index < count; index++){
    if (value < keys[index]) {    // search children
      if(index == 0) 
	node = children[index]->insert(value);  // place at minimum if empty
      else
        node = children[index-1]->insert(value);   // place in sorted position
      found = true;
      break;
    }
  }
  if (!found)     // means value does not go in any of the first count-2 nodes
    node = children[count-1]->insert(value); // so insert in last node
 
  if (node){  // if the LeafNode split, insert it into the array
    if (count < internalSize)
      insert(node);
    else
     split =  insertWhenFull(node);
  }

  updateKeys();

  return split;   // NULL if we didn't split, second node otherwise
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  addChild(oldRoot);
  addChild(node2);
} // InternalNode::insert() */


void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  if (count < internalSize){        // make sure node isn't full
      addChild(newNode);        // insert value in sorted position in array
  } 


} // InternalNode::insert()

InternalNode* InternalNode::insertWhenFull(BTreeNode* node){

  InternalNode* newnode = NULL;

    // check that a leftSibling exists, and that it's not full 
    if(leftSibling && leftSibling->getCount() < internalSize){
      addToLeft();
      addChild(node);
    }
    // same for RS
    else if(rightSibling && rightSibling->getCount() < internalSize){
      // insert in sorted position, temporarily go over max
      addChild(node);
      // move largest child to right sibling
      ((InternalNode*)rightSibling)->insert((InternalNode*)children[--count]);
    }
    // if all else fails, we need to split
    else{
      addChild(node);   // add value anyway, as it makes splitting much simpler

      newnode = split();
    }
    return newnode;
}

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
  
  updateKeys();                    // make sure keys are right
  
  if (count == 0 || key > keys[count - 1]) {  // if new max or empty set 
    keys[count] = key;                        // no need to shift
    children[count] = child;
  }

  else  if (key < getMinimum()){   // is the smallest node
    shift(0);
    keys[0] = key;
    children[0] = child;
  }
  
  else{                            // typical insert
  int search;
  // iterate through array and insert key
  for (search = 0; search <= count; search++)
    if (key < keys[search])
      break;

  // actual insert
  shift(search);
  keys[search] = key;
  children[search] = child;
  }

  child->setParent(this);          // make sure parent pointer is right

  count++;                         // make sure count stays updated
 
   updateKeys();                    // make sure keys are right

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
  
  if(rightSibling)
    rightSibling->setLeftSibling(n);
  rightSibling = n;

  for(int i = (count)/2; i <= internalSize; i++){
    n->insert(children[i]);
    count--;
  } // the above should ensure half full
   
  return n;
} // LeafNode::split()


void InternalNode::updateKeys()
{
  for (int i = 0; i < count; i++)
    keys[i] = children[i]->getMinimum();
}


void InternalNode::addToLeft( ) 
{

  // give leftSibling smallest value
  ((InternalNode*)leftSibling)->insert(children[0]);
  
  // shift all values left one
  for (int i = 0; i < count - 1; i++){
    keys[i] = keys[i+i];
    children[i] = children[i+1];
  }
  // update the count
  count--;
}
