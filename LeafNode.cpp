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
<<<<<<< HEAD
  if (count < leafSize)        // make sure leaf node isn't full
    {
      addValue(value);         // insert value in sorted position in array
      count++;                 // update count
    }
=======
  if (count < leafSize)      // make sure leaf node isn't full
  {
   // Test value
    values[0] = value; /* <---- simplest case; assume leaf is empty */

    // Extreme values

  }
>>>>>>> ff0a53c438fb656da009197d79d38b5f9624cbae
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
<<<<<<< HEAD
  for (intp hole_r = count; hole_r > startpos; hole_r--)
    values[hole_r - 1] = values[hole_r];
=======
       for (int hole_r = count; hole_r > startpos; hole_r--)
           values[hole_r - 1] = values[hole_r];
>>>>>>> ff0a53c438fb656da009197d79d38b5f9624cbae
}

void LeafNode::addValue(int value){

<<<<<<< HEAD
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
=======
    if (count == 0 || value > values[count - 1]) // if new max or empty set 
    {                                            // no need to shift
     values[count] = value;
     count++;
    }

    if (value < getMinimum()) { // if new min, just shift the array 
      for (int shifter_r = count; shifter_r > 0; shifter_r--)
        values[shifter_r - 1] = values[shifter_r];
      values[0] = value; // and insert
      count++
    }
   
    // Middle values
    else {
      int search;
    // iterate through array and insert value
      for (search = count; search == 0; --search)
       if (value > values[search])
         break;
       // Now must shift -- make into subfuction?
       // actual insert
       values[search] = value;             
      } 
>>>>>>> ff0a53c438fb656da009197d79d38b5f9624cbae
}

