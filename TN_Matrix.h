/**************************
TUNGSTEN Arrays of matrices
 Copyright Ben McLean 2023
** drbenmclean@gmail.com **
**************************/

//****************
//class TN_Matrix
//****************
//a class for fast matrices of compile-time-specified size

#ifndef TN_MATRIX
#define TN_MATRIX

#include <vector>

using namespace std;

template <class datatype, int nrows, int ncols> class TN_Matrix{

	protected:
	
	int m_nrows, m_ncols; //matrix size
	int m_nt; //total number of cells
	vector<datatype> m_data; //matrix cell data
	
	
	private:
	
	
	public:
	
	//constructors
	//************
	
	//constructor
	TN_Matrix() : m_nrows(nrows), m_ncols(ncols), m_nt(nrows*ncols), m_data(nrows*ncols){
		#ifdef TN_INITIALIZE
			for(int i=0;i<m_nt;++i)
				m_data[i] = 0;
		#endif
	};
	
	//destructor
	~TN_Matrix(){};

	//default copy constructor etc

	//structure-fetching functions
	//****************************
	
	//matrix size
	inline int get_nrows() const{
		return m_nrows;
	};
	inline int get_ncols() const{
		return m_ncols;
	};
	inline int get_ntot() const{
		return m_nt;
	};
	
	
	//index reverse-lookup
	inline int get_row(const int &i) const{
		return i/m_ncols; //integer division, gives whole number of rows
	};
	
	inline int get_col(const int &i) const{
		return i%m_ncols; //modulus, gives remainder, which equals number of cols
	};
	

	//Read-indexing
	//*************
	
	//Matrix(i) indexing
	inline const datatype & operator()(int i) const {
		return m_data[i];
	};
	
	//Matrix(row,col) indexing
	inline const datatype & operator()(int row, int col) const {
		return m_data[(row*m_ncols)+col];
	};
	
	//Matrix[i] indexing
	inline const datatype & operator[](int i) const {
		return m_data[i];
	};
	
	//Write-indexing
	//**************
	
	//Matrix(row,col) indexing
	inline datatype & operator()(int row, int col) {
		return m_data[row*m_ncols+col];
	};
	
	//Matrix[i] indexing
	inline datatype & operator[](int i) {
		return m_data[i];
	};

	//Assignment
	//**********
	
	//assignment by datatype
	TN_Matrix<datatype,nrows,ncols> &operator=(const datatype &val){
    
		#ifdef TN_PARALLELMATRIX
			#pragma omp parallel for
		#endif
		for(int i=0;i < m_nt;++i){
			m_data[i] = val;
		}
		return *this;
	};

	//assignment by TN_Matrix (use of nrows,ncols forces compile-time compatability)
	template<typename expr>
    TN_Matrix<datatype,nrows,ncols> &operator=(const TN_Matrix<datatype,nrows,ncols> &m){
		#ifdef TN_PARALLELMATRIX
			#pragma omp parallel for
		#endif
		for(int i=0;i < m_nt;++i){
			m_data[i] = m[i];
		}
		return *this;
	}

	//assignment by expression (use of nrows,ncols forces compile-time compatability)
	template<class LHS, class Op, class RHS, class RtnType>
    TN_Matrix<datatype,nrows,ncols> &operator=(const MatBinExpr<LHS,Op,RHS,nrows,ncols,RtnType> &expression){
    
		#ifdef TN_PARALLELMATRIX
			#pragma omp parallel for
		#endif
		for(int i=0;i < m_nt;++i){
			m_data[i] = expression.calc(i);
		}
		return *this;
	}
	
	//Matrix.set(set, of, comma, separated, values)
	void set(
	const datatype v00=0, const datatype v01=0, const datatype v02=0,
	const datatype v03=0, const datatype v04=0, const datatype v05=0,
	const datatype v06=0, const datatype v07=0, const datatype v08=0,
	const datatype v09=0, const datatype v10=0, const datatype v11=0,
	const datatype v12=0, const datatype v13=0, const datatype v14=0,
	const datatype v15=0, const datatype v16=0, const datatype v17=0,
	const datatype v18=0, const datatype v19=0, const datatype v20=0,
	const datatype v21=0, const datatype v22=0, const datatype v23=0,
	const datatype v24=0, const datatype v25=0, const datatype v26=0,
	const datatype v27=0, const datatype v28=0, const datatype v29=0,
	const datatype v30=0, const datatype v31=0, const datatype v32=0,
	const datatype v33=0, const datatype v34=0, const datatype v35=0 ){
		datatype values[] = {
			v00,v01,v02,v03,v04,v05,
			v06,v07,v08,v09,v10,v11,
			v12,v13,v14,v15,v16,v17,
			v18,v19,v20,v21,v22,v23,
			v24,v25,v26,v27,v28,v29,
			v30,v31,v32,v33,v34,v35};
			
		for(int i=0;i<m_nt;++i){
			m_data[i] = values[i];
		}
	};

	#include <cstdlib>
	void setrandom(int min=0, int max=9){
		for(int i=0;i<m_nt;++i){
			m_data[i] = rand() % (max + 1 - min) + min;
		}
	};

	//operators
	//*********
	
	//Matrix == Matrix
	bool operator == (const TN_Matrix<datatype, nrows, ncols> &m){
		
		bool equalmatrices = true;
		for (int i=0; i<m_nt; ++i){
            if(m_data[i] != m.m_data[i]){
            	equalmatrices = false;
            }
        }
        return equalmatrices;
	};

	bool operator != (const TN_Matrix<datatype, nrows, ncols> &m){
		
		bool unequalmatrices = false;
		for (int i=0; i<m_nt; ++i){
            if(m_data[i] != m.m_data[i]){
            	unequalmatrices = true;
            }
        }
        return unequalmatrices;
	};

	bool operator < (const TN_Matrix<datatype, nrows, ncols> &m){
		datatype thismin = this->min();
		datatype thatmin = m.min();
		if(thismin < thatmin)
			return true;
		else
			return false;
	};

	bool operator > (const TN_Matrix<datatype, nrows, ncols> &m){
		datatype thismax = this->max();
		datatype thatmax = m.max();
		if(thismax > thatmax)
			return true;
		else
			return false;
	};
	
	//expression templates tools
	//**************************
	
	//calc(index) for templated expressions
	inline const datatype & calc(int i) const{
		return m_data[i];
	};
	
	inline const datatype & calc(int row, int col) const{
		return m_data[row*m_ncols+col];
	};

	//Min/Max
	//*******

	datatype min() const {
		datatype minimum = m_data[0];
		for(int i=1; i < m_nt; ++i){
			if(m_data[i] < minimum)
				minimum = m_data[i];
		}
		return minimum;
	};
	
	datatype max() const {
		datatype maximum = m_data[0];
		for(int i=1; i < m_nt; ++i){
			if(m_data[i] > maximum)
				maximum = m_data[i];
		}
		return maximum;
	};

	
	
};

//overloaded "<<" operator
//************************
#include <ostream>
template<class datatype,int nrows,int ncols>
std::ostream &operator<<(std::ostream &s, const TN_Matrix<datatype,nrows,ncols> &m){
	s << "Matrix[" << nrows << "," << ncols << "] :" << endl;
	for(int i=0; i<nrows; ++i){
		for(int j=0; j<ncols; ++j){
			s << m(i,j) << " ";
		}
		s << endl;
	}
    return s;
};

//*******************
// Matrix Inverse etc
//*******************

//matrix transpose
template<class datatype, int nrows, int ncols> 
TN_Matrix<datatype,ncols,nrows> transpose(const TN_Matrix<datatype,nrows,ncols> &m){
	TN_Matrix<datatype,ncols,nrows> t;
	for(int r=0;r<nrows;++r){
		for(int c=0;c<ncols;++c){
			t(c,r) = m(r,c);
		}
	}
	return t;
};

//see https://www.geeksforgeeks.org/adjoint-inverse-matrix/

//Function to get cofactor of A[p][q], where "A" is a square matrix of dimensions n*n
template<class datatype, int n>
TN_Matrix<datatype,n-1,n-1> cofactor(const TN_Matrix<datatype,n,n> &A, int p, int q)
{
	int i = 0, j = 0;
	TN_Matrix<datatype,n-1,n-1> temp;
	
	//for each row and col
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			//copy into temporary matrix those elements which are not in given row and column
            if (row != p && col != q) {
                temp(i,j) = A(row,col);
				j++;
				if (j == n - 1) { //if row is filled, increase row index and reset col index
					j = 0;
					i++;
				}
			}
		}
	}

	return temp;
};



template<class datatype, int n>
datatype determinant(const TN_Matrix<datatype,n,n> &A, int ncol = n)
{
	datatype det = 0; // Initialize result

	//if matrix contains single element
    /*if (ncol == 1)
		return A(0,0);*/

	TN_Matrix<datatype,n-1,n-1> temp; // To store cofactors
	int sign = 1; // To store sign multiplier

	// Iterate for each element of first row
	for(int c = 0; c < ncol; c++) {
        //Getting Cofactor of A(0,c)
		temp = cofactor(A, 0, c);
		det += sign * A(0,c) * determinant(temp, ncol - 1);

		//terms are to be added with alternate sign
		sign = -sign;
	}
	return det;
};

//overload to prevent determinant from recursing once matrix is size 1*1
template<class datatype>
datatype determinant(const TN_Matrix<datatype,1,1> &A, int /*ncol*/)
{
	return A(0,0);
};

template<class datatype, int n>
TN_Matrix<datatype,n,n> adjoint(const TN_Matrix<datatype,n,n> &A)
{
	TN_Matrix<datatype,n,n> adj;
	
	if (n == 1) {
		adj(0,0) = 1;
		return adj;
	}

	//temp is used to store cofactors of A
    int sign = 1;
	TN_Matrix<datatype,n-1,n-1> temp;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// Get cofactor of A[i][j]
			temp = cofactor(A, i, j);

			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Interchanging rows and columns to get the
			// transpose of the cofactor matrix
			adj(j,i) = (sign) * (determinant(temp, n - 1));
		}
	}
	return adj;
};

template<class datatype, int n>
TN_Matrix<datatype,n,n> inverse(const TN_Matrix<datatype,n,n> &A)
{
	TN_Matrix<datatype,n,n> inv;

	//Find determinant of A
	datatype det = determinant(A);
	if (det == 0) {
		cout << "Singular matrix, can't find its inverse";
		return inv;
	}

	//Find adjoint
	TN_Matrix<datatype,n,n> adj = adjoint(A);

	//Find Inverse
	inv = adj/det;

	return inv;
};






#endif //TN_Matrix
