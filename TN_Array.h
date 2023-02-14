/**************************
TUNGSTEN Arrays of matrices
 Copyright Ben McLean 2023
** drbenmclean@gmail.com **
**************************/

//**************
//class TN_Array
//**************

#ifndef TN_ARRAY
#define TN_ARRAY

#include <omp.h>
#include <vector>

template <class datatype>
class TN_Array {

	protected:
	
	int m_nx, m_ny, m_nz; //array size
	int m_nynz; //used for indexing
	int m_nt; //total number of cells
	double m_dx, m_dy, m_dz; //cell dimensions
	double m_ox, m_oy, m_oz; //array origin coordinates
	vector<datatype> m_data; //array data
	
	private:
	
	//constructor tools
	void initialize(int nx, int ny, int nz){
		m_nx = nx;
		m_ny = ny;
		m_nz = nz;
		m_nynz = ny*nz;
		m_nt = nx*ny*nz;
			
		m_data.resize(m_nt);
		
		#ifdef TN_INITIALIZE
			#ifdef TN_PARALLELARRAY
				#pragma omp parallel for
			#endif
			for (int i=0; i<m_nt; ++i){
				m_data[i] = 0.0;
			}
		#endif
	};
	    
	void setcelldims(double dx, double dy, double dz){
		m_dx = dx;
	    m_dy = dy;
	    m_dz = dz;
	};
	    
	void setorigin(double ox, double oy, double oz){
		m_ox = ox;
		m_oy = oy;
		m_oz = oz;
	};

	public:
	
	//constructor, inc default constructor
	TN_Array(int nx = 1, int ny = 1, int nz = 1,
			double dx = 1.0, double dy = 1.0, double dz = 1.0,
			double ox = 0.0, double oy = 0.0, double oz = 0.0){
		initialize(nx, ny, nz);
		setcelldims(dx, dy, dz);
		setorigin(ox, oy, oz);
	};

	//destructor
	virtual ~TN_Array(){
	};

	//disable copy constructors etc
	//TN_Array(const TN_Array &) = delete;
	//TN_Array(const TN_Array&) = delete;
	//TN_Array(TN_Array&&) = delete;
	//TN_Array& operator=(const TN_Array&) = delete;
	//TN_Array& operator=(TN_Array&&) = delete;
	

	//resize
	void resize(int nx = 1, int ny = 1, int nz = 1,
			double dx = 1.0, double dy = 1.0, double dz = 1.0,
			double ox = 0.0, double oy = 0.0, double oz = 0.0){
		initialize(nx, ny, nz);
		setcelldims(dx, dy, dz);
		setorigin(ox, oy, oz);
	};

	//copy constructor
	//****************
	TN_Array(const TN_Array &array){	
		initialize(array.m_nx, array.m_ny, array.m_nz);
		setcelldims(array.m_dx, array.m_dy, array.m_dz);
		setorigin(array.m_ox, array.m_oy, array.m_oz);
		std::copy(array.m_data.begin(), array.m_data.end(), m_data.begin());
		//cout << "Called array copy constructor" << endl;
	};

	
	//operators
	//*********
	
	//Array = double or int etc
	TN_Array<datatype> operator = (const datatype &value){
		#ifdef TN_PARALLELARRAY
			#pragma omp parallel for
		#endif
		for (int i=0; i<m_nt; ++i){
            m_data[i] = value;
        }
		return *this;
	};

	template<typename expr>
    TN_Array<datatype> &operator = (const expr &expression){
    
		#ifdef TN_PARALLELARRAY
			#pragma omp parallel for
		#endif
		for(int i=0; i < m_nt; ++i){
			m_data[i] = expression.calc(i);
		}
		return *this;
	}

	//Array == Array
	bool operator == (const TN_Array<datatype> &a){
		
		bool equalarrays = true;
		for (int i=0; i<m_nt; ++i){
			if(m_data[i] != a(i)){
            	equalarrays = false;
				return equalarrays;
            }
        }
        return equalarrays;
	};
	
	//assign values
	//*************

	#include <cstdlib>
	void setrandom(int min=0, int max=9){
		if constexpr (	std::is_same_v<int, datatype> ||
						std::is_same_v<long int, datatype> ||
						std::is_same_v<double, datatype> ||
						std::is_same_v<long double, datatype>) {
			for(int i=0;i<m_nt;++i){
				m_data[i] = datatype(rand() % (max+1 - min) + min);
			}
		}
		else{ //datatype = TN_Matrix
			for(int i=0;i<m_nt;++i){
				m_data[i].setrandom(min,max);
			}
		}
	};

	//Array.set(set, of, comma, separated, values)
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
	
	//Read-indexing
	//*************
	
	//[i] indexing
	inline const datatype & operator[](int i) const {
		return m_data[i];
	};

	//(i) indexing
	inline const datatype & operator()(int i) const {
		return m_data[i];
	};
	
	//(i,j,k) indexing
	inline const datatype & operator()(int i, int j, int k) const {
		return m_data[(i*m_nynz)+(j*m_nz)+k];
	};
	
	//calc(i) indexing
	inline const datatype &calc(int i) const {
		return m_data[i];
	};

	//Write-indexing
	//**************
	
	//(i) indexing
	inline datatype & operator()(int i) {
		return m_data[i];
	};
	
	//(i,j,k) indexing
	inline datatype & operator()(int i, int j, int k) {
		return m_data[(i*m_nynz)+(j*m_nz)+k];
	};

	inline int get_nx() const {
		return m_nx;
	};

	inline int get_ny() const {
		return m_ny;
	};

	inline int get_nz() const {
		return m_nz;
	};

	inline int get_nt() const {
		return m_nt;
	};

	inline int get_dx() const {
		return m_dx;
	};

	inline int get_dy() const {
		return m_dy;
	};

	inline int get_dz() const {
		return m_dz;
	};

	inline int get_ox() const {
		return m_ox;
	};

	inline int get_oy() const {
		return m_oy;
	};

	inline int get_oz() const {
		return m_oz;
	};

	//Min/Max
	//*******

	//overload for general case
	datatype min() {
		datatype minimum = m_data[0];
		for(int i=1; i < m_nt; ++i){
			if(m_data[i] < minimum)
				minimum = m_data[i];
		}
		return minimum;
	};
	
	datatype max() {
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
template<class datatype>
std::ostream &operator<<(std::ostream &s, const TN_Array<datatype> &array){
	s << "Array[" << array.get_nx() << "," << array.get_ny() << ","  << array.get_nz() << "] :" << endl;
	for(int i=0; i<array.get_nx(); ++i){
		for(int j=0; j<array.get_ny(); ++j){
			for(int k=0; k<array.get_nz(); ++k){
				s << array(i,j,k) << " ";
			}
			s << endl;
		}
		s << endl;
	}
    return s;
};

#endif //TN_ARRAY


