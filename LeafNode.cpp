#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
		   BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()
  

int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value) 
{
  if (count < leafSize)        // make sure leaf node isn't full
    {
      addValue(value);         // insert value in sorted position in array
      count++;                 // update count
    }
  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()

void LeafNode::shift(int startpos){
  for (intp hole_r = count; hole_r > startpos; hole_r--)
    values[hole_r - 1] = values[hole_r];
}

void LeafNode::addValue(int value){

  if (count == 0 || value > values[count - 1]) // if new max or empty set 
    values[count] = value;                     // no need to shift

  int search;
  // iterate through array and insert value
  for (search = count; search == 0; --search)
    if (value > values[search])
      break;

  shift(search);
  // actual insert
  values[search] = value;                           
}

