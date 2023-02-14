/**************************
TUNGSTEN Arrays of matrices
 Copyright Ben McLean 2023
** drbenmclean@gmail.com **
**************************/

#ifndef TN_STRUCTMULOP
#define TN_STRUCTMULOP

#include <type_traits>

/*
All calc's are of the pattern:
template<any templated params>
static inline auto calc(const type1 &A, const type2 &B, int i){
		return A.calc(i) _OPSYMB B.calc(i);
	}
*/

struct MulOp
{
	//LHS datatype:
	//*************

	//datatype op Matrix
	template <int nrows, int ncols, class datatype>
	static inline auto calc(const datatype &A,
								const TN_Matrix<datatype, nrows, ncols> &B,
								int i)
	{
		return A * B.calc(i);
	}

	//datatype op MatBinExpr
	template <class datatype, class lhs, class op, class rhs, int nrows, int ncols>
	static inline auto
	calc(const datatype &A, const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &B, int i)
	{
		return A * B.calc(i);
	}

	//datatype op Array
	template <class datatype>
	static inline auto calc(const datatype &A,
								const TN_Array<datatype> &B,
								int i)
	{
		return A * B.calc(i);
	}

	//datatype op ArrBinExpr
	template <class datatype, class lhs, class op, class rhs>
	static inline auto
	calc(const datatype &A, const ArrBinExpr<lhs, op, rhs, datatype> &B, int i)
	{
		return A * B.calc(i);
	}

	//datatype op array<matrix>
	template <class datatype, int nrows, int ncols>
	static inline auto
								calc(	const datatype &A,
										const TN_Array<TN_Matrix<datatype, nrows, ncols> > &B,
										int i)
	{
		return A * B.calc(i);
	}

	//datatype op ArrMatBinExpr
	template<class datatype, class lhs, class op, class rhs,int nrows, int ncols, class rtntype>
	static inline auto
								calc(	const datatype &A,
										const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtntype> &B,
										int i)
	{
		return A * B.calc(i);
	}

	//LHS Matrix
	//**********

	//matrix op datatype
	template <int nrows, int ncols, class datatype>
	static inline auto calc(const TN_Matrix<datatype, nrows, ncols> &A,
								const datatype &B,
								int i)
	{
		return A.calc(i) * B;
	}

	//matrix op matrix --- matrix multiply
	template <int arows, int acols, int bcols, class datatype>
	static inline auto calc(const TN_Matrix<datatype, arows, acols> &A,
								const TN_Matrix<datatype, acols, bcols> &B,
								int i)
	{
		datatype val = 0.0;
		//reverse-lookup target row and column from i
		int targetrow = i/bcols; //integer division, gives row
		int targetcol = i%bcols; //modulus, gives column
		for(int col=0;col<acols;col++){
			val += A.calc(targetrow,col)*B.calc(col,targetcol);
		}
		return val;
	}

	//matrix op MatBinExpr --- matrix multiply
	template <class datatype, class lhs, class op, class rhs, int arows, int acols, int bcols>
	static inline auto
	calc(const TN_Matrix<datatype, arows, acols> &A, const MatBinExpr<lhs, op, rhs, acols, bcols, datatype> &B, int i)
	{
		datatype val = 0.0;
		//reverse-lookup target row and column from i
		int targetrow = i/bcols; //integer division, gives row
		int targetcol = i%bcols; //modulus, gives column
		for(int col=0;col<acols;col++){
			val += A.calc(targetrow,col)*B.calc(col,targetcol);
		}
		return val;
	}

	//matrix op array not defined

	//matrix op ArrBinExpr not defined

	//matrix op arrmat
	template <class datatype, int arows, int acols, int bcols>
	static inline auto
	calc(	const TN_Matrix<datatype, arows, acols> &A,
			const TN_Array<TN_Matrix<datatype, acols, bcols> > &B, int i)
	{
		return A * B.calc(i);
	}

	//matrix op ArrMatBinExpr
	template <class datatype, int arows, int acols, int bcols, class lhs, class op, class rhs, class rtntype>
	static inline auto
	calc(	const TN_Matrix<datatype, arows, acols> &A,
			const ArrMatBinExpr<lhs, op, rhs, acols, bcols, rtntype> &B, int i)
	{
		return A * B.calc(i);
	}

	//LHS MatBinExpr
	//**************

	//MatBinExpr op datatype
	template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
	static inline auto
	calc(const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &A, const datatype &B, int i)
	{
		return A.calc(i) * B;
	}

	//MatBinExpr op matrix
	template <class datatype, class lhs, class op, class rhs, int arows, int acols, int bcols>
	static inline auto
	calc(const MatBinExpr<lhs, op, rhs, arows, acols, datatype> &A, const TN_Matrix<datatype, acols, bcols> &B, int i)
	{
		datatype val = 0.0;
		//reverse-lookup target row and column from i
		int targetrow = i/bcols; //integer division, gives row
		int targetcol = i%bcols; //modulus, gives column
		for(int col=0;col<acols;col++){
			val += A.calc(targetrow,col)*B.calc(col,targetcol);
		}
		return val;
	}

	//MatBinExpr op MatBinExpr
	template <class datatype, class lhs1, class op1, class rhs1, class lhs2, class op2, class rhs2, int arows, int acols, int bcols>
	static inline auto
	calc(	const MatBinExpr<lhs1, op1, rhs1, arows, acols, datatype> &A,
			const MatBinExpr<lhs2, op2, rhs2, acols, bcols, datatype> &B, int i)
	{
		datatype val = 0.0;
		//reverse-lookup target row and column from i
		int targetrow = i/bcols; //integer division, gives row
		int targetcol = i%bcols; //modulus, gives column
		for(int col=0;col<acols;col++){
			val += A.calc(targetrow,col)*B.calc(col,targetcol);
		}
		return val;
	}

	//MatBinExpr op array not defined

	//MatBinExpr op ArrBinExpr not defined

	//MatBinExpr op arrmat
	template <class lhs, class op, class rhs, int arows, int acols, int bcols, class datatype>
	static inline auto
	calc(	const MatBinExpr<lhs, op, rhs, arows, acols, datatype> &A,
			const TN_Array<TN_Matrix<datatype, acols, bcols> > &B, int i)
	{
		return A * B.calc(i);
	}

	//MatBinExpr op ArrMatBinExpr
	template<class lhs1, class op1, class rhs1, int arows, int acols, int bcols, class datatype,
		class lhs2, class op2, class rhs2, class rtn2 >
	static inline auto
		calc(	const MatBinExpr<lhs1,op1,rhs1,arows,acols,datatype> &A,
				const ArrMatBinExpr<lhs2,op2,rhs2,acols,bcols,rtn2> &B, int i)
	{
		return A * B.calc(i);
	}
	

	//LHS Array
	//*********

	//array op datatype
	template <class datatype>
	static inline auto calc(const TN_Array<datatype> &A,
								const datatype &B,
								int i)
	{
		return A.calc(i) * B;
	}

	//array op array
	template <class datatype>
	static inline auto calc(const TN_Array<datatype> &A,
								const TN_Array<datatype> &B,
								int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//array op ArrBinExpr
	template <class datatype, class lhs, class op, class rhs>
	static inline auto
	calc(const TN_Array<datatype> &A, const ArrBinExpr<lhs, op, rhs, datatype> &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//array op arrmat
	template <class datatype,int nrows,int ncols>
	static inline auto
	calc(	const TN_Array<datatype> &A,
			const TN_Array<TN_Matrix<datatype,nrows,ncols> > &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//array op ArrMAtBinExpr
	template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
	static inline auto
	calc(	const TN_Array<datatype> &A,
			const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &B,
			int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//LHS ArrBinExpr
	//**************

	//ArrBinExpr op datatype
	template <class lhs, class op, class rhs, class datatype>
	static inline auto
	calc(const ArrBinExpr<lhs, op, rhs, datatype> &A, const datatype &B, int i)
	{
		return A.calc(i) * B;
	}

	//ArrBinExpr op array
	template <class lhs, class op, class rhs, class datatype>
	static inline auto
	calc(const ArrBinExpr<lhs, op, rhs, datatype> &A, const TN_Array<datatype> &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//ArrBinExpr op ArrBinExpr
	template <class lhs1, class op1, class rhs1, class datatype, class lhs2, class op2, class rhs2>
	static inline auto
	calc(const ArrBinExpr<lhs1, op1, rhs1, datatype> &A, const ArrBinExpr<lhs2, op2, rhs2, datatype>  &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//ArrBinExpr op arrmat
	template <class lhs,class op,class rhs,class datatype,int nrows,int ncols>
	static inline auto
	calc(	const ArrBinExpr<lhs,op,rhs,datatype> &A,
			const TN_Array<TN_Matrix<datatype,nrows,ncols> > &B,
			int i)
	{
		return A.calc(i) * B.calc(i);
	}


	//ArrBinExpr op ArrMatBinExpr
	template <class lhs1,class op1,class rhs1,class datatype,class lhs2,class op2,class rhs2,int nrows,int ncols,class rtn2>
	static inline auto
	calc(	const ArrBinExpr<lhs1,op1,rhs1,datatype> &A,
			const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &B,
			int i)
	{
		return A.calc(i) * B.calc(i);
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
		return A.calc(i) * B;
	}

	//arrmat op mat
	template <class datatype, int arows, int acols, int bcols>
	static inline auto
	calc(	const TN_Array<TN_Matrix<datatype, arows, acols> > &A,
			const TN_Matrix<datatype, acols, bcols> &B, int i)
	{
		return A.calc(i) * B;
	}

	//arrmat op MatBinExpr
	template <class datatype,int arows,int acols, int bcols, class lhs,class op,class rhs>
	static inline auto
	calc(	const TN_Array<TN_Matrix<datatype, arows, acols> > &A,
			const MatBinExpr<lhs,op,rhs,acols,bcols,datatype> &B, int i)
	{
		return A.calc(i) * B;
	}

	//arrmat op array
	template <class datatype,int nrows,int ncols>
	static inline auto
	calc(	const TN_Array<TN_Matrix<datatype,nrows,ncols> > &A,
			const TN_Array<datatype> &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//arrmat op ArrBinExpr
	template <class datatype,int nrows,int ncols,class lhs,class op,class rhs>
	static inline auto
	calc(	const TN_Array<TN_Matrix<datatype,nrows,ncols> > &A,
			const ArrBinExpr<lhs,op,rhs,datatype> &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//arrmat op arrmat
	template <class datatype, int arows, int acols, int bcols>
	static inline auto
	calc(const TN_Array<TN_Matrix<datatype, arows, acols> > &A,
		 const TN_Array<TN_Matrix<datatype, acols, bcols> > &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//arrmat op ArrMatBinExpr
	template <class datatype, class lhs, class op, class rhs, int arows, int acols, int bcols, class rtn>
	static inline auto
	calc(const TN_Array<TN_Matrix<datatype, arows, acols>> &A,
		 const ArrMatBinExpr<lhs,op,rhs,acols,bcols,rtn> &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//LHS ArrMatBinExpr
	//*****************

	//ArrMatBinExpr op datatype
	template<class datatype, class lhs, class op, class rhs,int nrows, int ncols, class rtntype>
	static inline auto
								calc(	const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtntype> &A,
										const datatype &B,
										int i)
	{
		return A.calc(i) * B;
	}

	//ArrMatBinExpr op mat
	template <class datatype, int arows, int acols, int bcols, class lhs, class op, class rhs, class rtntype>
	static inline auto
	calc(	const ArrMatBinExpr<lhs, op, rhs, arows, acols, rtntype> &A,
			const TN_Matrix<datatype, acols, bcols> &B, int i)
	{
		return A.calc(i) * B;
	}

	//ArrMatBinExpr op MatBinExpr
	template<class lhs1, class op1, class rhs1, int arows, int acols, int bcols, class datatype,
		class lhs2, class op2, class rhs2, class rtn2 >
	static inline auto
		calc(	const ArrMatBinExpr<lhs2,op2,rhs2,arows,acols,rtn2> &A,
				const MatBinExpr<lhs1,op1,rhs1,acols,bcols,datatype> &B, int i)
	{
		return A.calc(i) * B;
	}

	//ArrMatBinExpr op array
	template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
	static inline auto
	calc(	const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &A,
			const TN_Array<datatype> &B,
			int i)
	{
		return A.calc(i) * B.calc(i);
	}


	//ArrMatBinExpr op ArrBinExpr
	template <class lhs1,class op1,class rhs1,class datatype,class lhs2,class op2,class rhs2,int nrows,int ncols,class rtn2>
	static inline auto
	calc(	const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &A,
			const ArrBinExpr<lhs1,op1,rhs1,datatype> &B,
			int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//ArrMatBinExpr op arrmat
	template <class datatype, class lhs, class op, class rhs, int arows, int acols, int bcols, class rtn>
	static inline auto
	calc(const ArrMatBinExpr<lhs,op,rhs,arows,acols,rtn> &A,
		 const TN_Array<TN_Matrix<datatype, acols, bcols> > &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

	//ArrMatBinExpr op ArrMatBinExpr
	template <class lhs1,class op1,class rhs1,int arows,int acols,int bcols,class mlhs1,class mop1,class mrhs1,class datatype,
	class lhs2,class op2,class rhs2,class mlhs2,class mop2,class mrhs2>
	static inline auto
	calc(	const ArrMatBinExpr<lhs1,op1,rhs1,arows,acols,MatBinExpr<mlhs1,mop1,mrhs1,arows,acols,datatype> > &A,
			const ArrMatBinExpr<lhs2,op2,rhs2,acols,bcols,MatBinExpr<mlhs2,mop2,mrhs2,acols,bcols,datatype> > &B, int i)
	{
		return A.calc(i) * B.calc(i);
	}

};

#endif //STRUCTMULOP