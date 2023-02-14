/**************************
TUNGSTEN Arrays of matrices
 Copyright Ben McLean 2023
** drbenmclean@gmail.com **
**************************/

#ifndef TN_STRUCTDIVOP
#define TN_STRUCTDIVOP

#include <type_traits>

/*
All operators are of the pattern:
template<any templated params>
static inline auto calc(const type1 &A, const type2 &B, int i){
		return A.calc(i) _OPSYMB B.calc(i);
	}
*/

struct DivOp
{
	//LHS datatype:
	//*************

	//datatype op Matrix
	template <int nrows, int ncols, class datatype>
	static inline auto calc(const datatype &A,
								const TN_Matrix<datatype, nrows, ncols> &B,
								int i)
	{
		return A / B.calc(i);
	}

	//datatype op MatBinExpr
	template <class datatype, class lhs, class op, class rhs, int nrows, int ncols>
	static inline auto
	calc(const datatype &A, const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &B, int i)
	{
		return A / B.calc(i);
	}

	//datatype op Array
	template <class datatype>
	static inline auto calc(const datatype &A,
								const TN_Array<datatype> &B,
								int i)
	{
		return A / B.calc(i);
	}

	//datatype op ArrBinExpr
	template <class datatype, class lhs, class op, class rhs>
	static inline auto
	calc(const datatype &A, const ArrBinExpr<lhs, op, rhs, datatype> &B, int i)
	{
		return A / B.calc(i);
	}

	//datatype op array<matrix>
	template <class datatype, int nrows, int ncols>
	static inline auto
								calc(	const datatype &A,
										const TN_Array<TN_Matrix<datatype, nrows, ncols> > &B,
										int i)
	{
		return A / B.calc(i);
	}

	//datatype op ArrMatBinExpr
	template<class datatype, class lhs, class op, class rhs,int nrows, int ncols, class rtntype>
	static inline auto
								calc(	const datatype &A,
										const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtntype> &B,
										int i)
	{
		return A / B.calc(i);
	}

	//LHS Matrix
	//**********

	//matrix op datatype
	template <int nrows, int ncols, class datatype>
	static inline auto calc(const TN_Matrix<datatype, nrows, ncols> &A,
								const datatype &B,
								int i)
	{
		return A.calc(i) / B;
	}

	//matrix op matrix not defined

	//matrix op MatBinExpr not defined

	//matrix op array not defined

	//matrix op ArrBinExpr not defined

	//matrix op arrmat not defined

	//matrix op ArrMatBinExpr not defined

	//LHS MatBinExpr
	//**************

	//MatBinExpr op datatype
	template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
	static inline auto
	calc(const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &A, const datatype &B, int i)
	{
		return A.calc(i) / B;
	}

	//MatBinExpr op matrix not defined

	//MatBinExpr op MatBinExpr not defined

	//MatBinExpr op array not defined

	//MatBinExpr op ArrBinExpr not defined

	//MatBinExpr op arrmat not defined

	//MatBinExpr op ArrMatBinExpr not defined
	

	//LHS Array
	//*********

	//array op datatype
	template <class datatype>
	static inline auto calc(const TN_Array<datatype> &A,
								const datatype &B,
								int i)
	{
		return A.calc(i) / B;
	}

	//array op array
	template <class datatype>
	static inline auto calc(const TN_Array<datatype> &A,
								const TN_Array<datatype> &B,
								int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//array op ArrBinExpr
	template <class datatype, class lhs, class op, class rhs>
	static inline auto
	calc(const TN_Array<datatype> &A, const ArrBinExpr<lhs, op, rhs, datatype> &B, int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//array op arrmat
	template <class datatype,int nrows,int ncols>
	static inline auto
	calc(	const TN_Array<datatype> &A,
			const TN_Array<TN_Matrix<datatype,nrows,ncols> > &B, int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//array op ArrMAtBinExpr
	template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
	static inline auto
	calc(	const TN_Array<datatype> &A,
			const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &B,
			int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//LHS ArrBinExpr
	//**************

	//ArrBinExpr op datatype
	template <class lhs, class op, class rhs, class datatype>
	static inline auto
	calc(const ArrBinExpr<lhs, op, rhs, datatype> &A, const datatype &B, int i)
	{
		return A.calc(i) / B;
	}

	//ArrBinExpr op array
	template <class lhs, class op, class rhs, class datatype>
	static inline auto
	calc(const ArrBinExpr<lhs, op, rhs, datatype> &A, const TN_Array<datatype> &B, int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//ArrBinExpr op ArrBinExpr
	template <class lhs1, class op1, class rhs1, class datatype, class lhs2, class op2, class rhs2>
	static inline auto
	calc(const ArrBinExpr<lhs1, op1, rhs1, datatype> &A, const ArrBinExpr<lhs2, op2, rhs2, datatype>  &B, int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//ArrBinExpr op arrmat
	template <class lhs,class op,class rhs,class datatype,int nrows,int ncols>
	static inline auto
	calc(	const ArrBinExpr<lhs,op,rhs,datatype> &A,
			const TN_Array<TN_Matrix<datatype,nrows,ncols> > &B,
			int i)
	{
		return A.calc(i) / B.calc(i);
	}


	//ArrBinExpr op ArrMatBinExpr
	template <class lhs1,class op1,class rhs1,class datatype,class lhs2,class op2,class rhs2,int nrows,int ncols,class rtn2>
	static inline auto
	calc(	const ArrBinExpr<lhs1,op1,rhs1,datatype> &A,
			const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &B,
			int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//LHS array<matrix>
	//*****************

	//arrmat op datatype
	template <class datatype, int nrows, int ncols>
	static inline auto
								calc(	const TN_Array<TN_Matrix<datatype, nrows, ncols> > &A,
										const datatype &B,
										int i)
	{
		return A.calc(i) / B;
	}

	//arrmat op mat not defined

	//arrmat op MatBinExpr not defined

	//arrmat op array
	template <class datatype,int nrows,int ncols>
	static inline auto
	calc(	const TN_Array<TN_Matrix<datatype,nrows,ncols> > &A,
			const TN_Array<datatype> &B, int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//arrmat op ArrBinExpr
	template <class datatype,int nrows,int ncols,class lhs,class op,class rhs>
	static inline auto
	calc(	const TN_Array<TN_Matrix<datatype,nrows,ncols> > &A,
			const ArrBinExpr<lhs,op,rhs,datatype> &B, int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//arrmat op arrmat not defined

	//arrmat op ArrMatBinExpr not defined

	//LHS ArrMatBinExpr
	//*****************

	//ArrMatBinExpr op datatype
	template<class datatype, class lhs, class op, class rhs,int nrows, int ncols, class rtntype>
	static inline auto
								calc(	const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtntype> &A,
										const datatype &B,
										int i)
	{
		return A.calc(i) / B;
	}

	//ArrMatBinExpr op mat not defined

	//ArrMatBinExpr op MatBinExpr not defined

	//ArrMatBinExpr op array
	template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
	static inline auto
	calc(	const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &A,
			const TN_Array<datatype> &B,
			int i)
	{
		return A.calc(i) / B.calc(i);
	}


	//ArrMatBinExpr op ArrBinExpr
	template <class lhs1,class op1,class rhs1,class datatype,class lhs2,class op2,class rhs2,int nrows,int ncols,class rtn2>
	static inline auto
	calc(	const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &A,
			const ArrBinExpr<lhs1,op1,rhs1,datatype> &B,
			int i)
	{
		return A.calc(i) / B.calc(i);
	}

	//ArrMatBinExpr op arrmat not defined

	//ArrMatBinExpr op ArrMatBinExpr not defined

};

#endif //STRUCTDIVOP