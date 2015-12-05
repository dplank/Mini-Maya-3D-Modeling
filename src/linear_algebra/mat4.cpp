#include "mat4.h"

#define ILOOP for(int i=0; i<4; i++)
#define JLOOP for(int j=0; j<4; j++)

using namespace std;

//static mat4 mat4::rotate(float, float, float, float);
const float pi = 3.141;

//// constructor ////
mat4::mat4() {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			data[i][j]=0;
}

mat4::mat4(float diag) {

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			if(i!=j)
				data[i][j]=0;
			else
				data[i][j]=diag;
}

mat4::mat4(const vec4 &row0, const vec4 &row1, const vec4 &row2, const vec4 &row3) {
	//first row of matrix
	for(int i=0; i<4; i++)
		data[0][i]=row0[i];
	//second row of matrix
	for(int i=0; i<4; i++)
		data[1][i]=row1[i];
	//third row of matrix
	for(int i=0; i<4; i++)
		data[2][i]=row2[i];
	//forth row of matrix
	for(int i=0; i<4; i++)
		data[3][i]=row3[i];
}

mat4::mat4(const mat4 &m2) {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			data[i][j]=m2[i][j];
}

//// Getters and Setters

vec4 mat4::operator[]( unsigned int index ) const {
	if ( index<0 || index>3){
		cerr<<"Index out of range"<<endl;
		int i;
		cin>>i;
		exit(0);
	}
	return data[index];
}

vec4 &mat4::operator[] (unsigned int index) {
	if ( index<0 || index>3){
		cerr<<"Index out of range"<<endl;
		int i;
		cin>>i;
		exit(0);
	}
	return data[index];
}


/// Matrix transformation matrices AND static functions

mat4 mat4::rotate(float angle, float x, float y, float z) {
	static mat4 m;

	float angleRad = angle*pi/180;
	float norm = sqrt(x*x+y*y+z*z);
	float a = x/norm;
	float b = y/norm;
	float c = z/norm;

	//first row
	m[0][0] = a*a + (1 - a*a)*cos(angleRad);
	m[0][1] = a*b*(1 - cos(angleRad)) - c*sin(angleRad);
	m[0][2] = a*c*(1 - cos(angleRad)) + b*sin(angleRad);
	m[0][3] = 0;
	//second row
	m[1][0] = a*b*(1 - cos(angleRad)) + c*sin(angleRad);
	m[1][1] = b*b + (1 - b*b)*cos(angleRad);
	m[1][2] = b*c*(1-cos(angleRad)) - a*sin(angleRad);
	m[1][3] = 0;
	//third row
	m[2][0] = a*c*(1 - cos(angleRad)) - b*sin(angleRad);
	m[2][1] = b*c*(1 - cos(angleRad)) + a*sin(angleRad);
	m[2][2] = c*c + (1 - c*c)*cos(angleRad);
	m[2][3] = 0;
	//fourth row
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;

	return m;
}

mat4 mat4::translate(float x, float y, float z) {
	static mat4 m;
	// making 4x3 matrix a unit matrix with last row all zero element
	for(int i=0; i<4; i++) {
		for(int j=0; j<3; j++) {
			if(i!=j)
				m[i][j]=0;
			else
				m[i][j]=1;
		}
	}
	//for 
	m[0][3]=x;
	m[1][3]=y;
	m[2][3]=z;
	m[3][3]=1;

	return m;
}

mat4 mat4::scale(float x, float y, float z) {
	static mat4 m;
	//making a matrix with one only at [3][3]
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			if(i!=j)
				m[i][j]=0;
			else if(i==3)
				m[i][j]=1;

	//setting scale element
	m[0][0]=x;
	m[1][1]=y;
	m[2][2]=z;	

	return m;
}

mat4 mat4::identity() {
	static mat4 m(1);
	return m;
}


///// Operator funtions

//Assignment operator
mat4 &mat4::operator=(const mat4 &m2) {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			data[i][j] = m2[i][j];
	return (*this);
}

//Test equality operator
bool mat4::operator==(const mat4 &m2) const {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			if( data[i][j] != m2[i][j] )
				return false;
	return true;
}

bool mat4::operator!=(const mat4 &m2) const {
	if( (*this) == m2)
		return false;
	return true;
}

//Element-wise arithmetic

//arithmatic operator with equal
mat4 &mat4::operator+= (const mat4 &m2) {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			data[i][j]+=m2[i][j];
	
	return (*this);
}

mat4 &mat4::operator-= (const mat4 &m2) {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			data[i][j] -= m2[i][j];

	return (*this);
}

mat4 &mat4::operator*= (float c) {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			data[i][j] *= c;

	return *this;
}

mat4 &mat4::operator/= (float c) {
	if(c){
		cout<<"in divide equal"<<endl;
		(*this)*=(1/c);
		return (*this);
	} else {
		cerr<<"Divide by zero error"<<endl;
		int i;
		cin>>i;
		exit(0);
	}

}

//arithmatic operator
mat4 mat4::operator+ (const mat4 &m2) const {
	mat4 m;

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			m[i][j] = m2[i][j] + data[i][j];
	return m;
}

mat4 mat4::operator- (const mat4 &m2) const {
	mat4 m;

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			m[i][j] = data[i][j] - m2[i][j];
	return m;
}

mat4 mat4::operator* (float c) const {
	mat4 m;

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			m[i][j] = data[i][j]*c;
	
	return m;
}

mat4 mat4::operator/ (float c) const {
	if(c){
		return (*this) * (1/c);
	} else {
		cerr<<"Divide by zero error!"<<endl;
		int i;
		cin>>i;
		exit(0);
	}
}


///// Matirx multiplication (m1 * m2)
mat4 mat4::operator* (const mat4 &m2) const {
	mat4 m;

	ILOOP {
		JLOOP {
			for(int k=0; k<4; k++){
				m[i][j] += (*this)[i][k] * m2[k][j]; 
			}
		}
	}

	return m;
}

///// Matrix vector multiplication (m * v)
vec4 mat4::operator* (const vec4 &v) const {
	vec4 resultV;

	ILOOP {
		JLOOP {
			resultV[i] += data[i][j]*v[j];
		}
	}

	return resultV;
}

///// Matrix transpose
mat4 transpose( const mat4 &m) {
	mat4 resultM;

	ILOOP
		JLOOP
			resultM[j][i] = m[i][j];

	return resultM;
}

//// Give column vector of given column index
vec4 column( const mat4 &m, unsigned int index) {
	vec4 v;

	ILOOP
		v[i] = m[i][index];

	return v;
}

//// constant matrix multiplication of ( c * m )
mat4 operator* (float c, const mat4 &m) {
	mat4 resultM;

	ILOOP
		JLOOP
			resultM[i][j] = m[i][j]*c;

	return resultM;
}

//// vector matrix multiplication of ( v * m )
vec4 operator* (const vec4 &v, const mat4 &m) {
	vec4 resultV;

	ILOOP
		JLOOP
			resultV[i] += v[j]*m[j][i];

	return resultV;
}

//// printing matirx
std::ostream &operator<< (std::ostream &o, const mat4 &m) {
	o<<endl;
	ILOOP {
		o<<"[ ";
		JLOOP{
			o<<m[i][j]<<" ";
		}
		o<<"]"<<endl;
	}

	return o;
}
