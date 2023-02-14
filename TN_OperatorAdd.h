/**************************
TUNGSTEN Arrays of matrices
 Copyright Ben McLean 2023
** drbenmclean@gmail.com **
**************************/

#ifndef TN_OPERATORADD
#define TN_OPERATORADD

#include <type_traits>

/*
All operators are of the pattern:
template<templated params>
static inline auto
operator _OPSYMB(const LHS &A, const RHS &B){
	return BinExpr<LHS, _OPNAME, RHS, NROWS, NCOLS, RTNTYPE> (A,B);
}
*/

// LHS datatype:
//*************

// datatype op Matrix
template <int nrows, int ncols, class datatype>
static inline auto
operator+(const datatype &A, const TN_Matrix<datatype, nrows, ncols> &B)
{
	return MatBinExpr<datatype, AddOp,
					  TN_Matrix<datatype, nrows, ncols>, nrows, ncols, datatype>(A, B);
}

// datatype op MatBinExpr
template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
static inline auto
operator+(const datatype &A, const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &B)
{
	return MatBinExpr<datatype, AddOp,
					  MatBinExpr<lhs, op, rhs, nrows, ncols, datatype>, nrows, ncols, datatype>(A, B);
}

// datatype op Array
template <class datatype>
static inline auto
operator+(const datatype &A, const TN_Array<datatype> &B)
{
	return ArrBinExpr<datatype, AddOp,
					  TN_Array<datatype>, datatype>(A, B);
}

// datatype op ArrBinExpr
template <class datatype, class lhs, class op, class rhs>
static inline auto
operator+(const datatype &A, const ArrBinExpr<lhs, op, rhs, datatype> &B)
{
	return ArrBinExpr<datatype, AddOp,
					  ArrBinExpr<lhs, op, rhs, datatype>, datatype>(A, B);
}

// datatype op array<matrix>
template <class datatype, int nrows, int ncols>
static inline auto
operator+(const datatype &A, const TN_Array<TN_Matrix<datatype, nrows, ncols>> &B)
{
	return ArrMatBinExpr<datatype,
						 AddOp,
						 TN_Array<TN_Matrix<datatype, nrows, ncols>>,
						 nrows, ncols,
						 MatBinExpr<datatype, AddOp, TN_Matrix<datatype, nrows, ncols>, nrows, ncols, datatype>>(A, B);
}

// datatype op ArrMatBinExpr
template <typename datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtntype>
static inline auto
operator+(const datatype &A, const ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype> &B)
{
	return ArrMatBinExpr<datatype,
						 AddOp,
						 ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype>,
						 nrows, ncols,
						 MatBinExpr<datatype, AddOp, rtntype, nrows, ncols, datatype>>(A, B);
}

// LHS Matrix
//**********

// matrix op datatype
template <int nrows, int ncols, class datatype>
static inline auto
operator+(const TN_Matrix<datatype, nrows, ncols> &A, const datatype &B)
{
	return MatBinExpr<TN_Matrix<datatype, nrows, ncols>, AddOp,
					  datatype, nrows, ncols, datatype>(A, B);
}

// matrix op matrix
template <int nrows, int ncols, class datatype>
static inline auto
operator+(const TN_Matrix<datatype, nrows, ncols> &A,
		  const TN_Matrix<datatype, nrows, ncols> &B)
{
	return MatBinExpr<TN_Matrix<datatype, nrows, ncols>, AddOp,
					  TN_Matrix<datatype, nrows, ncols>, nrows, ncols, datatype>(A, B);
}

// matrix op MatBinExpr
template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
static inline auto
operator+(const TN_Matrix<datatype, nrows, ncols> &A,
		  const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &B)
{
	return MatBinExpr<TN_Matrix<datatype, nrows, ncols>, AddOp,
					  MatBinExpr<lhs, op, rhs, nrows, ncols, datatype>, nrows, ncols, datatype>(A, B);
}

// matrix op array not defined

// matrix op ArrBinExpr not defined

// matrix op arrmat
template <class datatype, int nrows, int ncols>
static inline auto
operator+(const TN_Matrix<datatype, nrows, ncols> &A,
		  const TN_Array<TN_Matrix<datatype, nrows, ncols>> &B)
{
	return ArrMatBinExpr<TN_Matrix<datatype, nrows, ncols>,
						 AddOp,
						 TN_Array<TN_Matrix<datatype, nrows, ncols>>,
						 nrows, ncols,
						 MatBinExpr<TN_Matrix<datatype, nrows, ncols>,
									AddOp,
									TN_Matrix<datatype, nrows, ncols>,
									nrows, ncols,
									datatype>>(A, B);
}

// matrix op ArrMatBinExpr
template <class datatype, int nrows, int ncols, class lhs, class op, class rhs, class rtntype>
static inline auto
operator+(const TN_Matrix<datatype, nrows, ncols> &A, const ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype> &B)
{
	return ArrMatBinExpr<TN_Matrix<datatype, nrows, ncols>,
						 AddOp,
						 ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype>,
						 nrows, ncols,
						 MatBinExpr<TN_Matrix<datatype, nrows, ncols>, AddOp, rtntype, nrows, ncols, datatype> >(A, B);
}


// LHS MatBinExpr
//**************

// MatBinExpr op datatype
template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
static inline auto
operator+(const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &A, const datatype &B)
{
	return MatBinExpr<MatBinExpr<lhs, op, rhs, nrows, ncols, datatype>, AddOp,
					  datatype, nrows, ncols, datatype>(A, B);
}

// MatBinExpr op matrix
template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
static inline auto
operator+(const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &A,
		  const TN_Matrix<datatype, nrows, ncols> &B)
{
	return MatBinExpr<MatBinExpr<lhs, op, rhs, nrows, ncols, datatype>, AddOp,
					  TN_Matrix<datatype, nrows, ncols>, nrows, ncols, datatype>(A, B);
}

// MatBinExpr op MatBinExpr
template <class lhs1, class op1, class rhs1, class lhs2, class op2, class rhs2, int nrows, int ncols, class datatype>
static inline auto
operator+(const MatBinExpr<lhs1, op1, rhs1, nrows, ncols, datatype> &A,
		  const MatBinExpr<lhs2, op2, rhs2, nrows, ncols, datatype> &B)
{
	return MatBinExpr<MatBinExpr<lhs1, op1, rhs1, nrows, ncols, datatype>, AddOp,
					  MatBinExpr<lhs2, op2, rhs2, nrows, ncols, datatype>, nrows, ncols, datatype>(A, B);
}

//MatBinExpr op array not defined

//MatBinExpr op ArrBinExpr not defined

//MatBinExpr op arrmat
template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
static inline auto
operator+(const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &A,
		  const TN_Array<TN_Matrix<datatype, nrows, ncols>> &B)
{
	return ArrMatBinExpr<MatBinExpr<lhs, op, rhs, nrows, ncols, datatype>,
						 AddOp,
						 TN_Array<TN_Matrix<datatype, nrows, ncols>>,
						 nrows, ncols,
						 MatBinExpr<MatBinExpr<lhs, op, rhs, nrows, ncols, datatype>,
									AddOp,
									TN_Matrix<datatype, nrows, ncols>,
									nrows, ncols,
									datatype> >(A, B);
}

//MatBinExpr op ArrMatBinExpr
template<class lhs1, class op1, class rhs1, int nrows, int ncols, class datatype,
		class lhs2, class op2, class rhs2, class rtn2 >
static inline auto
operator +(	const MatBinExpr<lhs1,op1,rhs1,nrows,ncols,datatype> &A,
			const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &B){
	return ArrMatBinExpr<	MatBinExpr<lhs1,op1,rhs1,nrows,ncols,datatype>,
							AddOp,
							ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2>,
							nrows,ncols,
							MatBinExpr<	MatBinExpr<lhs1,op1,rhs1,nrows,ncols,datatype>,
										AddOp,
										rtn2,
										nrows,ncols,
										datatype> > (A,B);
}

// LHS Array
//*********

// array op datatype
template <class datatype>
static inline auto
operator+(const TN_Array<datatype> &A, const datatype &B)
{
	return ArrBinExpr<TN_Array<datatype>, AddOp, datatype, datatype>(A, B);
}

// array op array
template <class datatype>
static inline auto
operator+(const TN_Array<datatype> &A, const TN_Array<datatype> &B)
{
	return ArrBinExpr<TN_Array<datatype>, AddOp, TN_Array<datatype>, datatype>(A, B);
}

// array op ArrBinExpr
template <class lhs, class op, class rhs, class datatype>
static inline auto
operator+(const TN_Array<datatype> &A,
		  const ArrBinExpr<lhs, op, rhs, datatype> &B)
{
	return ArrBinExpr<TN_Array<datatype>, AddOp,
					  ArrBinExpr<lhs, op, rhs, datatype>, datatype>(A, B);
}

//array op arrmat
template<class datatype,int nrows,int ncols>
static inline auto
operator +(	const TN_Array<datatype> &A,
			const TN_Array<TN_Matrix<datatype,nrows,ncols> > &B){
	return ArrMatBinExpr<	TN_Array<datatype>,
							AddOp,
							TN_Array<TN_Matrix<datatype, nrows, ncols> >,
							nrows,ncols,
							MatBinExpr<	datatype,
										AddOp,
										TN_Matrix<datatype, nrows, ncols>,
										nrows,ncols,
										datatype> > (A,B);
}

//array op ArrMatBinExpr
template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
static inline auto
operator +(	const TN_Array<datatype> &A,
			const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &B){
	return ArrMatBinExpr<	TN_Array<datatype>,
							AddOp,
							ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn>,
							nrows, ncols,
							MatBinExpr<	datatype,
										AddOp,
										rtn,
										nrows, ncols,
										datatype> > (A,B);
}


// LHS ArrBinExpr
//**************

// ArrBinExpr op datatype
template <class lhs, class op, class rhs, class datatype>
static inline auto
operator+(const ArrBinExpr<lhs, op, rhs, datatype> &A, const datatype &B)
{
	return ArrBinExpr<ArrBinExpr<lhs, op, rhs, datatype>, AddOp,
					  datatype, datatype>(A, B);
}

// ArrBinExpr op array
template <class lhs, class op, class rhs, class datatype>
static inline auto
operator+(const ArrBinExpr<lhs, op, rhs, datatype> &A, const TN_Array<datatype> &B)
{
	return ArrBinExpr<ArrBinExpr<lhs, op, rhs, datatype>, AddOp,
					  TN_Array<datatype>, datatype>(A, B);
}

// ArrBinExpr op ArrBinExpr
template <class lhs1, class op1, class rhs1, class datatype, class lhs2, class op2, class rhs2>
static inline auto
operator+(const ArrBinExpr<lhs1, op1, rhs1, datatype> &A, const ArrBinExpr<lhs2, op2, rhs2, datatype> &B)
{
	return ArrBinExpr<ArrBinExpr<lhs1, op1, rhs1, datatype>, AddOp,
					  ArrBinExpr<lhs2, op2, rhs2, datatype>, datatype>(A, B);
}

//ArrBinExpr op arrmat
template <class lhs,class op,class rhs,class datatype,int nrows,int ncols>
static inline auto
operator +(	const ArrBinExpr<lhs,op,rhs,datatype> &A,
			const TN_Array<TN_Matrix<datatype,nrows,ncols> > &B)
{
	return ArrMatBinExpr<	ArrBinExpr<lhs,op,rhs,datatype>,
							AddOp,
							TN_Array<TN_Matrix<datatype,nrows,ncols> >,
							nrows, ncols,
							MatBinExpr<	datatype,
										AddOp,
										TN_Matrix<datatype,nrows,ncols>,
										nrows, ncols,
										datatype> >(A, B);
}

//ArrBinExpr op ArrMatBinExpr
template <class lhs1,class op1,class rhs1,class datatype,class lhs2,class op2,class rhs2,int nrows,int ncols,class rtn2>
static inline auto
operator +(	const ArrBinExpr<lhs1,op1,rhs1,datatype> &A,
			const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &B)
{
	return ArrMatBinExpr<	ArrBinExpr<lhs1,op1,rhs1,datatype>,
							AddOp,
							ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2>,
							nrows, ncols,
							MatBinExpr<	datatype,
										AddOp,
										rtn2,
										nrows, ncols,
										datatype> >(A, B);
}


// LHS array<matrix>
//*****************

// arrmat op datatype
template <class datatype, int nrows, int ncols>
static inline auto
operator+(const TN_Array<TN_Matrix<datatype, nrows, ncols> > &A, const datatype &B)
{
	return ArrMatBinExpr<	TN_Array<TN_Matrix<datatype, nrows, ncols>>,
							AddOp,
							datatype,
							nrows, ncols,
							MatBinExpr<TN_Matrix<datatype, nrows, ncols>, AddOp, datatype, nrows, ncols, datatype>>(A, B);
}

// arrmat op mat
template <class datatype, int nrows, int ncols>
static inline auto
operator+(const TN_Array<TN_Matrix<datatype, nrows, ncols>> &A,
		  const TN_Matrix<datatype, nrows, ncols> &B)
{
	return ArrMatBinExpr<	TN_Array<TN_Matrix<datatype, nrows, ncols>>,
							AddOp,
							TN_Matrix<datatype, nrows, ncols>,
							nrows, ncols,
							MatBinExpr<	TN_Matrix<datatype, nrows, ncols>,
										AddOp,
										TN_Matrix<datatype, nrows, ncols>,
										nrows, ncols,
										datatype>>(A, B);
}

// arrmat op MatBinExpr
template<class datatype,int nrows,int ncols,class lhs,class op,class rhs>
static inline auto
operator +(	const TN_Array<TN_Matrix<datatype, nrows, ncols> > &A,
			const MatBinExpr<lhs,op,rhs,nrows,ncols,datatype> &B){
	return ArrMatBinExpr<	TN_Array<TN_Matrix<datatype, nrows, ncols> >,
							AddOp,
							MatBinExpr<lhs,op,rhs,nrows,ncols,datatype>,
							nrows,ncols,
							MatBinExpr<	TN_Matrix<datatype, nrows, ncols>,
										AddOp,
										MatBinExpr<lhs,op,rhs,nrows,ncols,datatype>,
										nrows,ncols,
										datatype> > (A,B);
}


// arrmat op array
template<class datatype,int nrows,int ncols>
static inline auto
operator +(	const TN_Array<TN_Matrix<datatype,nrows,ncols> > &A,
			const TN_Array<datatype> &B){
	return ArrMatBinExpr<	TN_Array<TN_Matrix<datatype, nrows, ncols> >,
							AddOp,
							TN_Array<datatype>,
							nrows,ncols,
							MatBinExpr<	TN_Matrix<datatype, nrows, ncols>,
										AddOp,
										datatype,
										nrows,ncols,
										datatype> > (A,B);
}

// arrmat op ArrBinExpr
template<class datatype,int nrows,int ncols,class lhs,class op,class rhs>
static inline auto
operator +(	const TN_Array<TN_Matrix<datatype,nrows,ncols> > &A,
			const ArrBinExpr<lhs,op,rhs,datatype> &B){
	return ArrMatBinExpr<	TN_Array<TN_Matrix<datatype, nrows, ncols> >,
							AddOp,
							ArrBinExpr<lhs,op,rhs,datatype>,
							nrows,ncols,
							MatBinExpr<	TN_Matrix<datatype, nrows, ncols>,
										AddOp,
										datatype,
										nrows,ncols,
										datatype> > (A,B);
}

// arrmat op arrmat
template <class datatype, int nrows, int ncols>
static inline auto
operator+(const TN_Array<TN_Matrix<datatype, nrows, ncols>> &A, const TN_Array<TN_Matrix<datatype, nrows, ncols>> &B)
{
	return ArrMatBinExpr<TN_Array<TN_Matrix<datatype, nrows, ncols>>, AddOp,
						 TN_Array<TN_Matrix<datatype, nrows, ncols>>, nrows, ncols,
						 MatBinExpr<TN_Matrix<datatype, nrows, ncols>,
									AddOp,
									TN_Matrix<datatype, nrows, ncols>,
									nrows, ncols,
									datatype>>(A, B);
}

// arrmat op ArrMatBinExpr
template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
static inline auto
operator+(	const TN_Array<TN_Matrix<datatype, nrows, ncols>> &A,
			const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &B)
{
	return ArrMatBinExpr<TN_Array<TN_Matrix<datatype, nrows, ncols>>, AddOp,
						 ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn>, nrows, ncols,
						 MatBinExpr<TN_Matrix<datatype, nrows, ncols>,
									AddOp,
									rtn,
									nrows, ncols,
									datatype>>(A, B);
}

// LHS ArrMatBinExpr
//*****************

// ArrMatBinExpr op datatype
template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtntype>
static inline auto
operator+(const ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype> &A, const datatype &B)
{
	return ArrMatBinExpr<ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype>,
						 AddOp,
						 datatype,
						 nrows, ncols,
						 MatBinExpr<rtntype, AddOp, datatype, nrows, ncols, datatype>>(A, B);
}

//ArrMatBinExpr op mat
template <class datatype, int nrows, int ncols, class lhs, class op, class rhs, class rtntype>
static inline auto
operator+(const ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype> &A, const TN_Matrix<datatype, nrows, ncols> &B)
{
	return ArrMatBinExpr<	ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype>,
							AddOp,
							TN_Matrix<datatype, nrows, ncols>,
							nrows, ncols,
							MatBinExpr<rtntype, AddOp, TN_Matrix<datatype, nrows, ncols>, nrows, ncols, datatype> >(A, B);
}

//ArrMatBinExpr op MatBinExpr
template<class lhs1, class op1, class rhs1, int nrows, int ncols, class datatype,
		class lhs2, class op2, class rhs2, class rtn2 >
static inline auto
operator +(	const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &A,
			const MatBinExpr<lhs1,op1,rhs1,nrows,ncols,datatype> &B){
	return ArrMatBinExpr<	ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2>,
							AddOp,
							MatBinExpr<lhs1,op1,rhs1,nrows,ncols,datatype>,
							nrows,ncols,
							MatBinExpr<	rtn2,
										AddOp,
										MatBinExpr<lhs1,op1,rhs1,nrows,ncols,datatype>,
										nrows,ncols,
										datatype> > (A, B);
}

//ArrMatBinExpr op array
template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
static inline auto
operator +(	const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &A,
			const TN_Array<datatype> &B){
	return ArrMatBinExpr<	ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn>,
							AddOp,
							TN_Array<datatype>,
							nrows, ncols,
							MatBinExpr<	rtn,
										AddOp,
										datatype,
										nrows, ncols,
										datatype> > (A,B);
}

//ArrMatBinExpr op ArrBinExpr
template <class lhs1,class op1,class rhs1,class datatype,class lhs2,class op2,class rhs2,int nrows,int ncols,class rtn2>
static inline auto
operator +(	const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &A,
			const ArrBinExpr<lhs1,op1,rhs1,datatype> &B)
{
	return ArrMatBinExpr<	ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2>,
							AddOp,
							ArrBinExpr<lhs1,op1,rhs1,datatype>,
							nrows, ncols,
							MatBinExpr<	rtn2,
										AddOp,
										datatype,
										nrows, ncols,
										datatype> >(A, B);
}

//ArrMatBinExpr op arrmat
template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
static inline auto
operator+(	const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &A,
			const TN_Array<TN_Matrix<datatype, nrows, ncols> > &B)
{
	return ArrMatBinExpr<ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn>, AddOp,
						 TN_Array<TN_Matrix<datatype, nrows, ncols> >, nrows, ncols,
						 MatBinExpr<rtn,
									AddOp,
									TN_Matrix<datatype, nrows, ncols>,
									nrows, ncols,
									datatype> >(A, B);
}

//ArrMatBinExpr op ArrMatBinExpr
template <class lhs1,class op1,class rhs1,int nrows,int ncols,class mlhs1,class mop1,class mrhs1,class datatype,
	class lhs2,class op2,class rhs2,class mlhs2,class mop2,class mrhs2>
static inline auto
	operator+(	const ArrMatBinExpr<lhs1,op1,rhs1,nrows,ncols,MatBinExpr<mlhs1,mop1,mrhs1,nrows,ncols,datatype> > &A,
				const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,MatBinExpr<mlhs2,mop2,mrhs2,nrows,ncols,datatype> > &B)
{
	return ArrMatBinExpr<	ArrMatBinExpr<lhs1,op1,rhs1,nrows,ncols,MatBinExpr<mlhs1,mop1,mrhs1,nrows,ncols,datatype> >, 
							AddOp,
						 	ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,MatBinExpr<mlhs2,mop2,mrhs2,nrows,ncols,datatype> >,
							nrows, ncols,
							MatBinExpr<	MatBinExpr<mlhs1,mop1,mrhs1,nrows,ncols,datatype>,
										AddOp,
										MatBinExpr<mlhs2,mop2,mrhs2,nrows,ncols,datatype>,
										nrows, ncols,
										datatype> >(A, B);
}
#endif // OPERATORADD