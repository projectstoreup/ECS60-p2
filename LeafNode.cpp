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
  if (this.getCount == 0)
    values[leafsize] = value;
    


  if (count < leafsize)      // make sure leaf node isn't full
    values[0] = value; /* <---- simplest case; assume leaf is empty */

/*   // search-insert

     // iterate through array and insert value
     for (int i = count - 1; i = 0; --i) 
       if (value > values[i])

        // Now must shift -- make into subfuction?
       for (int hole_it = count; hole_it < i; hole_it--)
         values[hole_it] = values[hole_it -1];

       // actual insert
       values[i] = value;              */

  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


