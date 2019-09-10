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

// ============================================================================
//  Basic Queue                                                     queueT.hpp
//  Template created by Alice Fischer on 9/25/11
// ============================================================================

#pragma once
#include "tools.hpp"
// ----------------------------------------------------------------------------- 
template <class BT>
class Queue { 
private:
	class Cell { 
	public:
		BT data;
		Cell* next;
		Cell( BT value, Cell* next ){
			data = value;
			this->next = next;
		}
		~Cell(){}
	};
	// -------------------------------------------------------------------------
	Cell* head;        // Always points to oldest Cell in the Queue.
	Cell* tail;        // Always points to the youngest Cell in the Queue.
	
public: 
	Queue( );
	~Queue( );
	void    append( BT value );   
	BT      remove();
	bool    isempty () { return head==NULL; }
	void    print ( ostream& out );
	void    shiftAll( Queue<BT>& p );
	BT&    peek();
	void    shiftOne( Queue<BT>& p);
};
// ----------------------------------------------------------------------------- 
// ----------------------------------------------------------------------------- 
// Pre:  We have a newly allocated Queue.
// Post: The new Queue is initialized to the empty state and is ready to use.
template <class BT> 
Queue<BT>::Queue() {   
    head = tail = NULL;      
}
// ----------------------------------------------------------------------------- 
// Pre:  We have a Queue that may or may not contain data.
// Post: The cells on the Queue have been deallocated. The Queue itself 
//       has been returned to the state of a newly initialized Queue.
template <class BT>  
Queue<BT>::~Queue() { 
	Cell* scan;
    while ( head != NULL ) {  
		scan = head;
        head = head->next;
        delete scan;
    }
    tail = NULL;      
}
// ----------------------------------------------------------------------------- 
// Insert a new value into the Queue. 
// Pre:  this points at an initialized Queue that may contain data.
// Post: value has been inserted at the tail end of the Queue. 
template <class BT>  void 
Queue<BT>::append( BT value ) {   
    Cell* p = new Cell( value, NULL );  // Make a new cell. 
    if (head==NULL) head = p;           // Insert at head if Queue is empty.
    else tail->next = p;                // else connect new cell to end of queue.
    tail = p;							// Make tail point at newest cell.
}
// ----------------------------------------------------------------------------- 
// Print the Queue. 
// Pre:  The Queue may or may not contain data; out is an open output stream.
// Post: The data has been written to out.
template <class BT>  void 
Queue<BT>::print( ostream& out )
{   
	out <<"\n\nThis Queue contains:\n\n";
	for( Cell* scan = head; scan != NULL; scan=scan->next )
		out << scan->data << ' ';
}
// -----------------------------------------------------------------------------
template <class BT> ostream& operator<<( ostream& out, Queue<BT>& q) {
	return q.print(out); 
}
// ----------------------------------------------------------------------------- 
// Pre:   The Queue must contain data.
// Post:  The value at the head of the queue is removed.
// Error: If the queue is empty, this operation is undefined. 
template <class BT>  BT
Queue<BT>::remove( ) { 
	Cell* temp = head;			// Grab cell for later deallocation.
    BT d = head->data;			// Grab data from the cell.
    head = head->next;			// Link around the cell.
    delete temp;				// Then free its memory.
    return d;					// And return the data.
}
// -----------------------------------------------------------------------------
// Return the data from the head of the queue, but not remove the Cell 
// or deallocate any memory:
template <class BT>
BT& Queue<BT>::peek(){
	return head->data;
}
// -----------------------------------------------------------------------------
// Take the first Cell of p queue and append it to this queue:
template <class BT>
void  Queue<BT>::shiftOne( Queue<BT>& p){
	// updating the required pointers of this queue:
	if( this->isempty() )
		this->head = p.head;
	else
		this->tail->next = p.head;
	if( !p.isempty() )     this->tail = p.head;
	
	// updating the required pointers of this and p queue after shifting:
	p.head = p.head->next;
	if( p.isempty() )
		p.tail = NULL;
	else
		this->tail->next = NULL;
}
// -----------------------------------------------------------------------------
// The purpose is to "glue" one queue (the parameter, p) onto the end of
// another (this) queue:
template <class BT>
void  Queue<BT>::shiftAll( Queue<BT>& p ){

	if ( this->isempty() )	
		this->head = p.head;
	else 
		this->tail->next = p.head;	
	this->tail = p.tail;

	// Reset queue p to the empty state, ready for re-use.
	p.head = NULL;
	//p.tail = NULL;
}
// -----------------------------------------------------------------------------