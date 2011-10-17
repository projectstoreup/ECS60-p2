#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p, 
  BTreeNode *left, BTreeNode *right) : 
  BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()


void LeafNode::addValue(int value)
{

  if (count == 0 || value > values[count - 1])
  {                                            // if new max or empty set 
    values[count] = value;                     // no need to shift
    return;
  }

  if (value < getMinimum()){
    shift(0);
    values[0] = value;
    return;
  }

  int search;
  // iterate through array and insert value
  for (search = 0; search <= count; search++)
    if (value > values[search])
      break;

  shift(--search);
  // actual insert
  values[search] = value;                           
}


/* addtoLeft pseudocode

int addtoLeft( ) {
  leftSibling->insert(values[0]);
  for( each element in left sibling )
    value[i] = value[i - 1];
    value[count - 1] = last;
}

*/
  
int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value) 
{
  if (count < leafSize)      // make sure leaf node isn't full
  {
    addValue(value);         // insert value in sorted position in array
    count++;                 // update count
  }

/*  More advanced cases

  else   // need to place values elsewhere
  {
    // check that a leftSibling exists, and that it's not full 
    if(leftSibling && leftSibling->getCount > leafSize)
      addtoLeft(value);
    // same for RS
    else if(rightSibling && rightSibling->getCount < leafSize)
      addtoRight(value);
    // if all else fails, we need to split
    else
      split();
  }

*/
    
  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()

void LeafNode::shift(int startpos)
{
  for (int hole_r = count; hole_r > startpos; hole_r--)
    values[hole_r] = values[hole_r -1];
}

void LeafNode::split()
{
  LeafNode *n = newleaf(leafSize, parent,  // check this
   this, rightSibling, NULL)
  
  for(int = (leafSize + 1)/2; i < leafSize; i++)
    // the above should ensure half full
    // insert the 'insert new values' algorithm here
}
