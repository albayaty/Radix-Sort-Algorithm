/* ==============================================
*  Copyright ©  2014  Ali M. Al-Bayaty
*  
*  Radix Sort Algorithm is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  any later version.
*  
*  Radix Sort Algorithm is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/* ==============================================
*  
*  Radix Sort Algorithm
*  
*  MSEE Student: Ali M. Al-Bayaty
*  Instructor: Dr. Alice Fischer
*  CS 620: Data Structures
*  Personal Website: <http://albayaty.github.io/>
*
*  ==============================================
*/

//  ----------------------------------------------------------------------------
//  Header file for Radix class.                                      Radix.hpp
//  The declaration part of the class
//  Created by Ali Al-Bayaty on Mon Nov 21, 2011
// -----------------------------------------------------------------------------

#pragma once
#include "queueT.hpp"
#define BUCKS 265

class Radix {
private:
	//  -----------------------------------------------------------------------
	Queue<long unsigned> buckets[BUCKS];  // Array of queue for buckets of 8-bit 4 fields
	Queue<long unsigned> collector;       // Queue that will hold the data initially, and 
	                                      // to collect the data from all the buckets
	short int pass;                       // To count the phases of the algorithm in progress
public:
	// ---------------------------------------------- Constructor and Destructor
	Radix( const char* filename="numbers.txt" ){
		
		long unsigned data;
		pass = 0;                // init to the first phase
		ifstream fin(filename);
		if( !fin )  fatal("ERROR: Can not open the input \"numbers.txt\" file ...");
		
		// adding all the inputs from the file to the queue:
		for(;;){
			fin >> data;
			if(fin.eof())  break;
			collector.append(data);
		}
		fin.close();	
	}

	~Radix(void){}
	// ------------------------------------------------ Functions and Prototypes
	// To access the data of each Cell from the collector queue,
    // then calculate the correct bucket:
	void distribute(void);
	// To gather up all the Cells from the buckets and shift them
	// back into the collector:
	void collect(void);
	// To sort the data according to the radix sort algorithm:
	void sort(void);
};
// -----------------------------------------------------------------------------
// To access the data of each Cell from the collector queue,
// then calculate the correct bucket:
void Radix::distribute(){
	unsigned long index;
	
	// loop until the end of the queue:
	for( ; !collector.isempty() ;  ){		
		index = collector.peek();  // To check without removing the cell
		index >>= pass*8;          // Calculating the subscript   
		index &= 0xFF;             // Masking the subscript with 8-bit
		// Store the peeked cell with the designated bucket:
		buckets[index].shiftOne(collector);		
	}
}
// -----------------------------------------------------------------------------
// To gather up all the Cells from the buckets and shift them back into the collector:
void Radix::collect(){
	int counter;

	// Loop for all 265 buckets:
	for( counter=0 ; counter<BUCKS ; counter++ ){
		if( !buckets[counter].isempty() )    // When not empty, concatenate to the collector
			collector.shiftAll(buckets[counter]);
	}
}
// -----------------------------------------------------------------------------
// To sort the data according to the radix sort algorithm:
void Radix::sort(){
		
	ofstream fout("out.txt");
	if( !fout )  fatal("ERROR: Can not open the output \"out.txt\" file ...");

	// count until the max. numbers of bytes in the "unsigned long", then for each
	// pass distribute() then collect, with printing each pass to the screen:
	for( ; pass<sizeof(unsigned long) ; pass++ ){
		distribute();
		collect();
		cout << endl << "PASS = " << pass << endl;
		collector.print(cout);
		cout << endl << right << setw(50) << setfill('-') << " " << setfill(' ') << endl;
	}
	
	// Printing the sorted contents of collector queue to "out.txt" file:
	for( ; !collector.isempty() ;  ){
		fout << collector.remove() << endl;
	}
	fout.close();
}
// -----------------------------------------------------------------------------