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

  if (count == 0 || value > values[count - 1]) {  // if new max or empty set 
    values[count] = value;                        // no need to shift
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

  // ----More advanced cases---- //
  else   // need to place values elsewhere
  {
    // check that a leftSibling exists, and that it's not full 
    if(leftSibling && leftSibling->getCount() < leafSize)
      leftSibling->insert(value);
    // same for RS
    else if(rightSibling && rightSibling->getCount() < leafSize)
      rightSibling->insert(value);
    // if all else fails, we need to split
    else{
      addValue(value);
      count++;
      LeafNode* newnode = split();
      return newnode;
    }
  }
 
  return NULL; // we didn't split, dont return anything
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
} // LeafNode::print()


LeafNode* LeafNode::split()
{
  LeafNode *n = new LeafNode(leafSize, parent, this, rightSibling);
  
  rightSibling = n;

  for(int i = (count + 1)/2; i < leafSize; i++){
    n->insert(values[i]);
    count--;
  } // the above should ensure half full
   
  return n;
} // LeafNode::split()
