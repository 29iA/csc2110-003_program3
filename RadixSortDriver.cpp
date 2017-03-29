#include "RadixSort.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* list = CD::readCDs("cds.txt");
   int size = list->size();

   CD** cds = new CD*[size];

   ListArrayIterator<CD>* iter = list->iterator();
   int count = 0;
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      cds[count] = cd;
      count++;
   }
   delete iter;

   //DO THIS
	//test both radix sort methods using the cds array
	
	//creates new array
	CD** array = new CD*[size];
	
	//calls radixSort with ascending algorithm
	cout << "Sorting method 1: Ascending.\n";
	array = RadixSort<CD>::radixSort(cds, size, 42, true, &CD::getRadixChar);
	
	//displaying results
	cout << "Ready to display. Press ENTER to continue...";
	cin.get();
	
	//re-instantiating iterator
	iter = list->iterator();
	count = 0;
	
	//displaying...
	while (iter->hasNext())
   {
	   CD* next = iter->next();
		CD* c = array[count];
	   String* key = c->getKey();
	   key->displayString();
	   cout << endl;
		count++;
   }
	
	delete iter;
	cout << endl;
	
	//calls radixSort with descending algorithm
	cout << "Sorting method 2: Descending.\n";
	array = RadixSort<CD>::radixSort(cds, size, 42, false, &CD::getRadixChar);
	
	//displaying results
	cout << "Ready to display. Press ENTER to continue...";
	cin.get();
	
	//re-instantiating iterator
	iter = list->iterator();
	count = 0;
	
	//displaying...
	while (iter->hasNext())
   {
	   CD* next = iter->next();
		CD* c = array[count];
	   String* key = c->getKey();
	   key->displayString();
	   cout << endl;
		count++;
   }
	
	delete iter;
	cout << endl;
	
	cout << "Sorting completed. Press ENTER to finish...";
	cin.get();

   delete[] cds;

   deleteCDs(list);
   delete list;

   return 0;
}
