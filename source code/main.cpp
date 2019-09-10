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
//  Main program for Radix Sort Algorithm                              main.cpp
//  Created by Ali Al-Bayaty on Mon Nov 21, 2011
//  ----------------------------------------------------------------------------

#include "Radix.hpp"

int main( void ) {	
	
	// Information message:
	banner();
	// Creating the Radix object:	
	Radix rdx("numbers.txt");
	// Implementing the algorithm with sort():
	rdx.sort();

    bye();
	return 0;
}
//  ----------------------------------------------------------------------------