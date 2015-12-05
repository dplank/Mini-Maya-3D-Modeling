#include "vec4.h"
#include <math.h>

using namespace std;

//// Constructors /////

vec4::vec4() {
	data[0]=data[1]=data[2]=data[3]=0;
}

vec4::vec4(float x, float y, float z, float w) {
	data[0]=x; data[1]=y, data[2]=z, data[3]=w;
} 

vec4::vec4(const vec4 &v2) {
	for(int i=0; i<4; i++)
		data[i]=v2.data[i];
}

//// Getters and Setters //////

float vec4::operator[] (unsigned int index) const {
	if ( index<0 || index>3){
		cerr<<"Index out of range"<<endl;
		int i;
		cin>>i;
		exit(0);
	}	
	return data[index];
}

float &vec4::operator[] (unsigned int index) {
	if ( index<0 || index>3){
		cerr<<"Index out of range"<<endl;
		int i;
		cin>>i;
		exit(0);
	}	
	return data[index];
}

//// Operator Functions ///////

//equality
vec4 &vec4::operator= (const vec4 &v2) {
	this->data[0] = v2.data[0];
	this->data[1] = v2.data[1];
	this->data[2] = v2.data[2];
	this->data[3] = v2.data[3];

	return (*this);
}

//test for equality
bool vec4::operator== (const vec4 &v2) const {
	if( data[0]==v2.data[0] && data[1]==v2.data[1] &&
		data[2]==v2.data[2] && data[3]==v2.data[3] )
		return true;
	else
		return false;

}

//test for inequality
bool vec4::operator!= (const vec4 &v2) const { //to test
	if ( *this == v2 )
		return false;
	else
		return true;
}

//Arithmetic:
vec4 &vec4::operator+= (const vec4 &v2) {
	data[0] += v2.data[0];
	data[1] += v2.data[1];
	data[2] += v2.data[2];
	data[3] += v2.data[3];

	return (*this);
}

vec4 &vec4::operator-= (const vec4 &v2) { // to test
	(*this) += (vec4(0,0,0,0) - v2);

	return (*this);
}

//multiplication and division by scalar
vec4 &vec4::operator*= (float c) {
	for(int i=0; i<4; i++) //SOME CHANGE DONE HERE FROM i<4 TO i<3
		data[i] *= c;
	return (*this);
}

vec4 &vec4::operator/= (float c) { // to test
	if(c) {
		(*this) *= 1/c;
		return (*this);
	} else {
		cerr<<"divide by zero execption";
		int i;
		cin>>i;
		exit(0);
	}
}


vec4 vec4::operator+ ( const vec4 &v2) const {
	// vec4 *v = new vec4(0,0,0,0) ; not need heap allocation as magic is done by "operator=" overloading
	vec4 v;
	for(int i=0; i<4; i++)
		v.data[i] = data[i] + v2.data[i] ;

	return (v);
}

vec4 vec4::operator- (const vec4 &v2) const {
	vec4 v ;

	for(int i=0; i<4; i++)
		v.data[i] = data[i] - v2.data[i];

	return (v);
}

vec4 vec4::operator* (float c) const {
	vec4 v;

	for(int i=0; i<4; i++) //SOME CHANGE DONE HERE FROM i<4 TO i<3
		v.data[i] = data[i] * c;
	return v;
}

vec4 vec4::operator/ (float c)  const { //to test
	if(c){
		return (*this)*(1/c);
	}
	else {
		cerr<<"Divide by zero error"<<endl;
		exit(0);
	}
}


float dot( const vec4 &v1, const vec4 &v2) {
	float result = 0;
	for(int i=0; i<3; i++) //SOME CHANGE DONE HERE FROM i<4 TO i<3
		result += v1[i] * v2[i];

	return result;
}

vec4 cross ( const vec4 &v1, const vec4 &v2) {
	vec4 v;

	for(int i=0; i<3; i++) {
		v[i] = v1[(i+1)%3] * v2[(i+2)%3]
			 - v2[(i+1)%3] * v1[(i+2)%3];
	}
	
	return v;
}

float length( const vec4 &v) {

    return sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3] );
}

vec4 operator* (float c, const vec4 &v) {
	vec4 pv;
	
	for(int i=0; i<4; i++) {
		pv[i] = v[i]*c;
	}

	return pv;
}

std::ostream &operator<<(std::ostream &o, const vec4 &v) {

	o<<"("<<v[0]<<", "<<v[1]<<", "<<v[2]<<", "<<v[3]<<")"<<endl;
	
	return o;
}
