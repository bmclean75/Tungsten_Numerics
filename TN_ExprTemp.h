/**************************
TUNGSTEN Arrays of matrices
Copyright Ben McLean 2023
** drbenmclean@gmail.com **
**************************/

#include <memory>

#ifndef TN_EXPRTEMP
#define TN_EXPRTEMP

using namespace std;

#ifdef TN_NOARRAYSOFMATRICES

	/*If no arrays of matrices, MatBinExpr and ArrBinExpr can use references to streamline code,
	allowing straight-through processing of expressions without the creation of temporaries,
	meaning memory-use and execution-time is minimised*/
	template<class LHS, class Op, class RHS, int nrows, int ncols, class RtnType>
	class MatBinExpr
	{	
		protected :
		const LHS & left_;
		const RHS & right_;
		const int nrows_, ncols_;
		
   		public :
		//empty constructor will be optimized away, but triggers
		//type identification needed for template expansion
		MatBinExpr(const LHS &leftArg, const RHS &rightArg) : left_(leftArg),
			right_(rightArg), nrows_(nrows), ncols_(ncols)
		{};
		//empty destructor will be optimized away
		~MatBinExpr(){};
		
		//calculate value of expression at specified index by recursing
		inline RtnType calc(int i) const{
			return Op::calc(left_, right_, i);
		};
		
		//calculate value of expression at specified index by recursing
		inline RtnType calc(int row, int col) const{
			return Op::calc(left_, right_, row*ncols_+col);
		};
	};

	template<class LHS, class Op, class RHS, class RtnType>
	class ArrBinExpr
	{	
		protected :
		const LHS left_;
		const RHS right_;
		
   		public :
		//empty constructor will be optimized away, but triggers
		//type identification needed for template expansion
		ArrBinExpr(const LHS leftArg, const RHS rightArg) : left_(leftArg),
			right_(rightArg)
		{};
		
		//empty destructor will be optimized away
		~ArrBinExpr(){};
		
		//calculate value of expression at specified index by recursing
		inline RtnType calc(int i) const{
			return Op::calc(left_, right_, i);
		};
		
	};

#else //There are arrays of matrices...

	/*If there are arrays of matrices, MatBinExpr and ArrBinExpr must use copy-by-value
	to prevent dangling pointers. This makes them slower by around 3x, but prevents segfaults.*/
	template<class LHS, class Op, class RHS, int nrows, int ncols, class RtnType>
	class MatBinExpr
	{	
		protected :
		const LHS left_;
		const RHS right_;
		const int nrows_, ncols_;
		
   		public :
		//empty constructor will be optimized away, but triggers
		//type identification needed for template expansion
		MatBinExpr(const LHS leftArg, const RHS rightArg) : left_(leftArg),
			right_(rightArg), nrows_(nrows), ncols_(ncols)
		{};
		//empty destructor will be optimized away
		~MatBinExpr(){};
		
		//calculate value of expression at specified index by recursing
		inline RtnType calc(int i) const{
			return Op::calc(left_, right_, i);
		};
		
		//calculate value of expression at specified index by recursing
		inline RtnType calc(int row, int col) const{
			return Op::calc(left_, right_, row*ncols_+col);
		};
	};

	template<class LHS, class Op, class RHS, class RtnType>
	class ArrBinExpr
	{	
		protected :
		const LHS left_;
		const RHS right_;
		
   		public :
		//empty constructor will be optimized away, but triggers
		//type identification needed for template expansion
		ArrBinExpr(const LHS leftArg, const RHS rightArg) : left_(leftArg),
			right_(rightArg)
		{};
		
		//empty destructor will be optimized away
		~ArrBinExpr(){};
		
		//calculate value of expression at specified index by recursing
		inline RtnType calc(int i) const{
			return Op::calc(left_, right_, i);
		};
		
	};
#endif //TN_NOARRAYSOFMATRICES

	/*Note ArrMatBinExpr uses references to streamline code to straight-through processing
	without the creation of temporaries, meaning memory-use due to the often-large
	TN_Array<TN_Matrix> > type is minimised.*/
	template<class LHS, class Op, class RHS, int nrows, int ncols, class RtnType>
	class ArrMatBinExpr
	{	
		protected :
		const LHS & left_;
		const RHS & right_;
		const int nrows_, ncols_;
		
   		public :
		ArrMatBinExpr(const LHS &leftArg, const RHS &rightArg) : left_(leftArg),
			right_(rightArg), nrows_(nrows), ncols_(ncols)
		{};

		~ArrMatBinExpr(){};
		
		inline RtnType calc(int i) const{
			return Op::calc(left_, right_, i);
		};

		inline RtnType calc(int row, int col) const{
			return Op::calc(left_, right_, row*ncols_+col);
		};
		
	};

#endif //TN_EXPRTEMP

