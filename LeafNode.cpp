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
  }

  else if (value < getMinimum()){
    shift(0);
    values[0] = value;
  }

  else {
    int search;
    // iterate through array and insert value
    for (search = 0; search <= count; search++)
      if (value < values[search])
	break;

    shift(search);
    // actual insert
    values[search] = value;                           

  }

  count++;

}


void LeafNode::addToLeft( ) 
{
  // give leftSibling smallest value
  leftSibling->insert(values[0]);
  
  // shift all values left one
  for (int i = 0; i < count - 1; i++)
    values[i] = values[i+1];

  // update the count
  count--;
}


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value) 
{
  LeafNode* newnode = NULL;  // in case the node splits;

  if (count < leafSize)      // make sure leaf node isn't full
  {
    addValue(value);         // insert value in sorted position in array
  }
  
  // ----More advanced cases---- //

  else   // need to place values elsewhere
  {
    // check that a leftSibling exists, and that it's not full 
    if(leftSibling && leftSibling->getCount() < leafSize){
      addToLeft();
      addValue(value);
    }
    // same for RS
    else if(rightSibling && rightSibling->getCount() < leafSize){
      // insert in sorted position, temporarily go over max
      addValue(value);
      //give the largest value to the right sibling, update count
      rightSibling->insert(values[--count]);
    }
    // if all else fails, we need to split
    else{
      addValue(value);   // add value anyway, as it makes splitting much simpler

      newnode = split();
    }
  }
  return newnode;       // NULL if not split, new node otherwise
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
  
   // update sibling pointers
  if(rightSibling)
    rightSibling->setLeftSibling(n);
  rightSibling = n;

  // <= leafSize because we have one value than the max
  for(int i = (count)/2; i <= leafSize; i++){  
    n->insert(values[i]);
    count--;
  } // the above should ensure half full
  
  return n;
  
} // LeafNode::split()
