#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;

template < class T >
class RadixSort
{
   private:
	/*
		Pre: bin is the queue holding the content, curr_char is the character that is compared by binSort every recursive call, num_chars is the number of characters, and getRadixChar is the static method pointer for comparison of item.
		Post: sorts through with recursion and arrange the items as it's being compared
	*/
		static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));

	/*
		Pre: sort is the unsorted list's copy, n is the number of items on list, num_chars is the amount of characters, and getRadixChar is the static method pointer for comparison of item.
		Post: list gets arranged in ascending order via adding the content into QueueLinked and using binSort recursion.
	*/
		static void radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 1
     
	/*
		Pre: sort is the unsorted list's copy, n is the number of items on list, num_chars is the amount of characters, and getRadixChar is the static method pointer for comparison of item.
		Post: list gets arranged in descending order via adding the content into QueueLinked and using comparison.
	*/
		static void radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 2
 
   public:
	/*
		Pre: sort is a list of the datatype <T>, num_to_sort is the number of items the list have, num_chars is the amount of characters, asc sees if it'll sort in ascending (true) or descending (false) order based on user's choice, and getRadixChar is the static method pointer for comparison of item.
		Post: creates a copy of the original list, sorts the new list (based on asc parameter), and returns the sorted list.
	*/
      static T** radixSort(T** sort, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index));
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index))
{
   //DO THIS
	T** sorter = new T*[num_to_sort];
	
	//copy unsorted and prepare for sort
	for (int i = 0; i < num_to_sort; i++)
   {
		sorter[i] = unsorted[i];
   }
   
   if (asc) //ascending
   {
		radixSortAsc(sorter, num_to_sort, num_chars, getRadixChar); 
   }
   else //descending
   {
		radixSortDesc(sorter, num_to_sort, num_chars, getRadixChar);
   }

	return sorter;
}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
	//main bin for all items in sort[]
	QueueLinked<T>* bin = new QueueLinked<T>();
	
	//add all elements in sort[] to bin
   for (int i = 0; i < n; i++)
   {
		bin->enqueue(sort[i]);
   }
	
	//int n being 1-based
   binSort(bin, 1, num_chars, getRadixChar);

	//add the sorted content from binSort back to sort[]
   for (int i = 0; i < n; i++)
   {
		sort[i] = bin->dequeue();
   }

   delete bin;
}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
	///error-checking
	if (curr_char > num_chars || bin->isEmpty())
   {
	   return;
   }
	
	//num_queues being the range of digits/letters/s.characters
	int num_queues = 37;
	QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];
	
	//instantiate each of the queues
	for (int i = 0; i < num_queues; i++)
   {
		bins[i] = new QueueLinked<T>();
   }
	
	for (int i = 0; i < num_queues; i++)
	{
		while (!bin->isEmpty())
		{
			//ascii conversion initialization
			int ascii_index;
			char ascii = (*getRadixChar) (bin->peek(), curr_char); //get the current element
		
			//ascii conversion
			//48-57 = numbers, 97-122 = lowercase letters, 65-90 uppercase letters
			if (ascii >= 48 && ascii <= 57)
			{
				ascii_index = ascii - 47; //numbers
			}
			else if (ascii >= 97 && ascii <= 122)
			{
				ascii_index = ascii - 86; //lowercase letters
			}
			else if (ascii >= 65 && ascii <= 90)
			{
				ascii_index = ascii - 54; //uppercase letters
			}

			else
			{
				ascii_index = 0; //unknown/special characters
			}
			
			//take item from main bin into sorter bins
			bins[ascii_index]->enqueue(bin->dequeue());
		}
	}

	for (int i = 0; i < num_queues; i++)
   {
		//recursively calls binSort again
	   binSort(bins[i], curr_char + 1, num_chars, getRadixChar);
	   
	   while (!bins[i]->isEmpty())
	   {
		   bin->enqueue(bins[i]->dequeue()); //add to main bin
	   }
   }
   
   for (int i = 0; i < num_queues; i++)
   {
	   delete bins[i];
   }
	
   delete[] bins;
}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   int num_queues = 37;  //covers letters and digits
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];  

   //must instantiate each of the queues
   for (int i = 0; i < num_queues; i++)
   {
      bins[i] = new QueueLinked<T>();
   }

   for (int i = num_chars; i > 0; i--)  //number of times to bin stuff
   {
      //DO THIS
		for (int j = 0; j < n; j++)
		{
			//ascii conversion initialization
			int ascii_index;
			char ascii = (*getRadixChar) (sort[j], i); //get the current element
			
			//ascii conversion
			//48-57 = numbers, 97-122 = lowercase letters, 65-90 uppercase letters
			if (ascii >= 48 && ascii <= 57)
			{
				ascii_index = ascii - 47; //numbers
			}
			else if (ascii >= 97 && ascii <= 122)
			{
				ascii_index = ascii - 86; //lowercase letters
			}
			else if (ascii >= 65 && ascii <= 90)
			{
				ascii_index = ascii - 54; //uppercase letters
			}
			
			else
			{
				ascii_index = 0; //unknown/special characters
			}
			
			//adds back to the queue
			bins[ascii_index]->enqueue(sort[j]);
		}

		int counter = 0;
	
		//remove all item and it is then sorted
		//num_queues - 1 for indexing
		for (int l = num_queues - 1; l >= 0; l--)
		{
			while (!bins[l]->isEmpty())
			{
				sort[counter] = bins[l]->dequeue();
				counter++;
			}
		}
   }

   for (int i = 0; i < num_queues; i++) 
   {
      delete bins[i];
   }

   delete[] bins;
}

#endif
