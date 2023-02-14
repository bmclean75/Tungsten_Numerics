/**************************
TUNGSTEN Arrays of matrices
 Copyright Ben McLean 2023
** drbenmclean@gmail.com **
**************************/

#include <iostream>

//#define TN_NOARRAYSOFMATRICES
#define TN_PARALLELARRAY
//#define TN_PARALLELMATRIX
#define TN_INITIALIZE

#include "TN_Numerics.h"

int main(void)
{
	
	cout << "TN_Numerics examples..." << endl;
	
	//*************
	//  Matrices
	//*************

	/*Matrices are defined at compile time by their datatype (typically 'double' for a floating
	-point number, but ints or other types can be used as well), and the number of rows and columns
	the matrix has, i.e.:
	TN_Matrix<datatype, nrows,ncols> mat1;
	*/
	TN_Matrix<double, 6, 10> mat1;
	TN_Matrix<double, 6, 10> mat2;
	TN_Matrix<double, 10, 4> mat4;
	TN_Matrix<double, 10, 4> mat5;
	TN_Matrix<double, 6, 4> mat6;
	mat1.setrandom();
	mat2.setrandom();
	mat4.setrandom();
	mat5.setrandom();
	mat6.setrandom();

	/*Matrices can be used in typical operations such as add, subtract, divide, multiply,
	and inverse. Expressions can be written intuitively and are deliberately made to reflect
	the mathematical expressions they represent, bridging the divide between math and code.
	If compiled with
	#define TN_NOARRAYSOFMATRICES
	these expressions will be evaluated without the creation of temporaries.
	An example expression could look like:
	*/
	mat6 = ((mat1 + 7.9) * mat4) - ((mat2 * 2.8 ) * (3.3 + mat5));
	cout << "mat6 = " << mat6 << endl;

	//************
	//  Arrays
	//************

	/*Arrays are defined at compile time by their datatype (typically 'double' for a floating-
	point number, but ints and other types can be used as well), and at run-time by their x, y,
	and z dimensions (expressed as a number of cells), i.e.,
	TN_Array<datatype> arr1(nx,ny,nz);
	*/
	TN_Array<double> arr1(2,3,1);
	TN_Array<double> arr2(2,3,1);
	TN_Array<double> arr3(2,3,1);
	arr1.setrandom();
	arr2.setrandom();
	arr3.setrandom();

	/*Arrays also provide the typical operations such as add, subtract, multiply, and divide,
	as well as spatial operators such as derivatives.
	An example expression could look like:	*/
	arr1 = (arr1 * 3.76) * (arr2 + 4.13) / arr3;
	cout << "arr1 = " << arr1 << endl;

	//***********************
	//  Arrays of Matrices
	//***********************

	/*It is possible, and finite-difference computations are a common use case, to use arrays
	of matrices. In this use case, the array typically represents a volume of space, and the
	matrices represent a physical property at each cell location. Arrays of matrices are
	instantiated by simply using a matrix type as the datatype for an array:	*/
	TN_Array<TN_Matrix<double, 6, 9> > am1(10,10,10);
	TN_Array<TN_Matrix<double, 6, 9> > am2(10,10,10);
	TN_Array<TN_Matrix<double, 9, 8> > am3(10,10,10);
	TN_Array<TN_Matrix<double, 9, 8> > am4(10,10,10);
	TN_Array<TN_Matrix<double, 6, 8> > am5(10,10,10);
	am1.setrandom();
	am2.setrandom();
	am3.setrandom();
	am4.setrandom();
	am5.setrandom();

	/*Again, typical mathematical operations are supported. Array operations are executed cell-wise,
	while matrix operations are executed according to mathematical constraints (e.g., matrix addition
	is completed in a cellwise manner, matrix multiply is executed according to matrix multiplication
	rules. An example expression could look like:	*/
	am5 = ((am1 + 2.88) - am2) * (am3 + am4 / 5.73);
	cout << "am5(0,0,0) = " << am5(0,0,0) << endl;

	cout << "all done!" << endl;
	return (0);
}
