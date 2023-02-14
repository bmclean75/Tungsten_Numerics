/**************************
TUNGSTEN Arrays of matrices
 Copyright Ben McLean 2023
** drbenmclean@gmail.com **
**************************/

#ifndef TN_OPERATORDIV
#define TN_OPERATORDIV

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
operator/(const datatype &A, const TN_Matrix<datatype, nrows, ncols> &B)
{
	return MatBinExpr<datatype, DivOp,
					  TN_Matrix<datatype, nrows, ncols>, nrows, ncols, datatype>(A, B);
}

// datatype op MatBinExpr
template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
static inline auto
operator/(const datatype &A, const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &B)
{
	return MatBinExpr<datatype, DivOp,
					  MatBinExpr<lhs, op, rhs, nrows, ncols, datatype>, nrows, ncols, datatype>(A, B);
}

// datatype op Array
template <class datatype>
static inline auto
operator/(const datatype &A, const TN_Array<datatype> &B)
{
	return ArrBinExpr<datatype, DivOp,
					  TN_Array<datatype>, datatype>(A, B);
}

// datatype op ArrBinExpr
template <class datatype, class lhs, class op, class rhs>
static inline auto
operator/(const datatype &A, const ArrBinExpr<lhs, op, rhs, datatype> &B)
{
	return ArrBinExpr<datatype, DivOp,
					  ArrBinExpr<lhs, op, rhs, datatype>, datatype>(A, B);
}

// datatype op array<matrix>
template <class datatype, int nrows, int ncols>
static inline auto
operator/(const datatype &A, const TN_Array<TN_Matrix<datatype, nrows, ncols>> &B)
{
	return ArrMatBinExpr<datatype,
						 DivOp,
						 TN_Array<TN_Matrix<datatype, nrows, ncols>>,
						 nrows, ncols,
						 MatBinExpr<datatype, DivOp, TN_Matrix<datatype, nrows, ncols>, nrows, ncols, datatype>>(A, B);
}

// datatype op ArrMatBinExpr
template <typename datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtntype>
static inline auto
operator/(const datatype &A, const ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype> &B)
{
	return ArrMatBinExpr<datatype,
						 DivOp,
						 ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype>,
						 nrows, ncols,
						 MatBinExpr<datatype, DivOp, rtntype, nrows, ncols, datatype>>(A, B);
}

// LHS Matrix
//**********

// matrix op datatype
template <int nrows, int ncols, class datatype>
static inline auto
operator/(const TN_Matrix<datatype, nrows, ncols> &A, const datatype &B)
{
	return MatBinExpr<TN_Matrix<datatype, nrows, ncols>, DivOp,
					  datatype, nrows, ncols, datatype>(A, B);
}

// matrix op matrix not defined

// matrix op MatBinExpr not defined

// matrix op array not defined

// matrix op ArrBinExpr not defined

// matrix op arrmat not defined

// matrix op ArrMatBinExpr not defined


// LHS MatBinExpr
//**************

// MatBinExpr op datatype
template <class lhs, class op, class rhs, int nrows, int ncols, class datatype>
static inline auto
operator/(const MatBinExpr<lhs, op, rhs, nrows, ncols, datatype> &A, const datatype &B)
{
	return MatBinExpr<MatBinExpr<lhs, op, rhs, nrows, ncols, datatype>, DivOp,
					  datatype, nrows, ncols, datatype>(A, B);
}

// MatBinExpr op matrix not defined

// MatBinExpr op MatBinExpr not defined

//MatBinExpr op array not defined

//MatBinExpr op ArrBinExpr not defined

//MatBinExpr op arrmat not defined

//MatBinExpr op ArrMatBinExpr not defined

// LHS Array
//*********

// array op datatype
template <class datatype>
static inline auto
operator/(const TN_Array<datatype> &A, const datatype &B)
{
	return ArrBinExpr<TN_Array<datatype>, DivOp, datatype, datatype>(A, B);
}

// array op array
template <class datatype>
static inline auto
operator/(const TN_Array<datatype> &A, const TN_Array<datatype> &B)
{
	return ArrBinExpr<TN_Array<datatype>, DivOp, TN_Array<datatype>, datatype>(A, B);
}

// array op ArrBinExpr
template <class lhs, class op, class rhs, class datatype>
static inline auto
operator/(const TN_Array<datatype> &A,
		  const ArrBinExpr<lhs, op, rhs, datatype> &B)
{
	return ArrBinExpr<TN_Array<datatype>, DivOp,
					  ArrBinExpr<lhs, op, rhs, datatype>, datatype>(A, B);
}

//array op arrmat
template<class datatype,int nrows,int ncols>
static inline auto
operator /(	const TN_Array<datatype> &A,
			const TN_Array<TN_Matrix<datatype,nrows,ncols> > &B){
	return ArrMatBinExpr<	TN_Array<datatype>,
							DivOp,
							TN_Array<TN_Matrix<datatype, nrows, ncols> >,
							nrows,ncols,
							MatBinExpr<	datatype,
										DivOp,
										TN_Matrix<datatype, nrows, ncols>,
										nrows,ncols,
										datatype> > (A,B);
}

//array op ArrMatBinExpr
template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
static inline auto
operator /(	const TN_Array<datatype> &A,
			const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &B){
	return ArrMatBinExpr<	TN_Array<datatype>,
							DivOp,
							ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn>,
							nrows, ncols,
							MatBinExpr<	datatype,
										DivOp,
										rtn,
										nrows, ncols,
										datatype> > (A,B);
}


// LHS ArrBinExpr
//**************

// ArrBinExpr op datatype
template <class lhs, class op, class rhs, class datatype>
static inline auto
operator/(const ArrBinExpr<lhs, op, rhs, datatype> &A, const datatype &B)
{
	return ArrBinExpr<ArrBinExpr<lhs, op, rhs, datatype>, DivOp,
					  datatype, datatype>(A, B);
}

// ArrBinExpr op array
template <class lhs, class op, class rhs, class datatype>
static inline auto
operator/(const ArrBinExpr<lhs, op, rhs, datatype> &A, const TN_Array<datatype> &B)
{
	return ArrBinExpr<ArrBinExpr<lhs, op, rhs, datatype>, DivOp,
					  TN_Array<datatype>, datatype>(A, B);
}

// ArrBinExpr op ArrBinExpr
template <class lhs1, class op1, class rhs1, class datatype, class lhs2, class op2, class rhs2>
static inline auto
operator/(const ArrBinExpr<lhs1, op1, rhs1, datatype> &A, const ArrBinExpr<lhs2, op2, rhs2, datatype> &B)
{
	return ArrBinExpr<ArrBinExpr<lhs1, op1, rhs1, datatype>, DivOp,
					  ArrBinExpr<lhs2, op2, rhs2, datatype>, datatype>(A, B);
}

//ArrBinExpr op arrmat
template <class lhs,class op,class rhs,class datatype,int nrows,int ncols>
static inline auto
operator /(	const ArrBinExpr<lhs,op,rhs,datatype> &A,
			const TN_Array<TN_Matrix<datatype,nrows,ncols> > &B)
{
	return ArrMatBinExpr<	ArrBinExpr<lhs,op,rhs,datatype>,
							DivOp,
							TN_Array<TN_Matrix<datatype,nrows,ncols> >,
							nrows, ncols,
							MatBinExpr<	datatype,
										DivOp,
										TN_Matrix<datatype,nrows,ncols>,
										nrows, ncols,
										datatype> >(A, B);
}

//ArrBinExpr op ArrMatBinExpr
template <class lhs1,class op1,class rhs1,class datatype,class lhs2,class op2,class rhs2,int nrows,int ncols,class rtn2>
static inline auto
operator /(	const ArrBinExpr<lhs1,op1,rhs1,datatype> &A,
			const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &B)
{
	return ArrMatBinExpr<	ArrBinExpr<lhs1,op1,rhs1,datatype>,
							DivOp,
							ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2>,
							nrows, ncols,
							MatBinExpr<	datatype,
										DivOp,
										rtn2,
										nrows, ncols,
										datatype> >(A, B);
}


// LHS array<matrix>
//*****************

// arrmat op datatype
template <class datatype, int nrows, int ncols>
static inline auto
operator/(const TN_Array<TN_Matrix<datatype, nrows, ncols> > &A, const datatype &B)
{
	return ArrMatBinExpr<	TN_Array<TN_Matrix<datatype, nrows, ncols>>,
							DivOp,
							datatype,
							nrows, ncols,
							MatBinExpr<TN_Matrix<datatype, nrows, ncols>, DivOp, datatype, nrows, ncols, datatype>>(A, B);
}

// arrmat op mat not defined

// arrmat op MatBinExpr not defined

// arrmat op array
template<class datatype,int nrows,int ncols>
static inline auto
operator /(	const TN_Array<TN_Matrix<datatype,nrows,ncols> > &A,
			const TN_Array<datatype> &B){
	return ArrMatBinExpr<	TN_Array<TN_Matrix<datatype, nrows, ncols> >,
							DivOp,
							TN_Array<datatype>,
							nrows,ncols,
							MatBinExpr<	TN_Matrix<datatype, nrows, ncols>,
										DivOp,
										datatype,
										nrows,ncols,
										datatype> > (A,B);
}

// arrmat op ArrBinExpr
template<class datatype,int nrows,int ncols,class lhs,class op,class rhs>
static inline auto
operator /(	const TN_Array<TN_Matrix<datatype,nrows,ncols> > &A,
			const ArrBinExpr<lhs,op,rhs,datatype> &B){
	return ArrMatBinExpr<	TN_Array<TN_Matrix<datatype, nrows, ncols> >,
							DivOp,
							ArrBinExpr<lhs,op,rhs,datatype>,
							nrows,ncols,
							MatBinExpr<	TN_Matrix<datatype, nrows, ncols>,
										DivOp,
										datatype,
										nrows,ncols,
										datatype> > (A,B);
}

// arrmat op arrmat not defined

// arrmat op ArrMatBinExpr not defined

// LHS ArrMatBinExpr
//*****************

// ArrMatBinExpr op datatype
template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtntype>
static inline auto
operator/(const ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype> &A, const datatype &B)
{
	return ArrMatBinExpr<ArrMatBinExpr<lhs, op, rhs, nrows, ncols, rtntype>,
						 DivOp,
						 datatype,
						 nrows, ncols,
						 MatBinExpr<rtntype, DivOp, datatype, nrows, ncols, datatype>>(A, B);
}

//ArrMatBinExpr op mat not defined

//ArrMatBinExpr op MatBinExpr not defined

//ArrMatBinExpr op array
template <class datatype, class lhs, class op, class rhs, int nrows, int ncols, class rtn>
static inline auto
operator /(	const ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn> &A,
			const TN_Array<datatype> &B){
	return ArrMatBinExpr<	ArrMatBinExpr<lhs,op,rhs,nrows,ncols,rtn>,
							DivOp,
							TN_Array<datatype>,
							nrows, ncols,
							MatBinExpr<	rtn,
										DivOp,
										datatype,
										nrows, ncols,
										datatype> > (A,B);
}

//ArrMatBinExpr op ArrBinExpr
template <class lhs1,class op1,class rhs1,class datatype,class lhs2,class op2,class rhs2,int nrows,int ncols,class rtn2>
static inline auto
operator /(	const ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2> &A,
			const ArrBinExpr<lhs1,op1,rhs1,datatype> &B)
{
	return ArrMatBinExpr<	ArrMatBinExpr<lhs2,op2,rhs2,nrows,ncols,rtn2>,
							DivOp,
							ArrBinExpr<lhs1,op1,rhs1,datatype>,
							nrows, ncols,
							MatBinExpr<	rtn2,
										DivOp,
										datatype,
										nrows, ncols,
										datatype> >(A, B);
}

//ArrMatBinExpr op arrmat not defined

//ArrMatBinExpr op ArrMatBinExpr not defined

#endif // OPERATORDIV