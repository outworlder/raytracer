#ifndef MATHCLASS
#define MATHCLASS

#include <math.h>

class Point {
 public:
	 float x;
	 float y;
	 float z;

	 Point& operator = (const Point& p) {
		x=p.x;
		y=p.y;
		z=p.z;
	 }

	 Point() {
		x=0;
		y=0;
		z=0;
	 }
	 
	 Point(float x, float y, float z) {
		this->x=x;
		this->y=y;
		this->z=z;
	 }
};

class Vector {
 protected:
	 float x;
	 float y;
	 float z;
	 
 public:
   Vector operator + (const Vector& p) {
		return Vector(x+p.x,y+p.y,z+p.z);
	}

   Vector operator - (const Vector& p) {
		return Vector(x-p.x,y-p.y,z-p.z);
	}

   Vector operator = (const Vector& p){
		if (this!=&p) {
			x=p.x;
			y=p.y;
			z=p.z;
		}
		return *this;
	}

   float   operator * (const Vector& v) {
		return x*v.x+y*v.y+z*v.z;
	}
	
   Vector operator % (const Vector& v) {
		return Vector(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
	}

	Vector operator / (const float d) {
		return Vector(x/d,y/d,z/d);
	}

	Vector& operator -() {
		x=-x;
		y=-y;
		z=-z;
		return *this;
	}
   
	friend Vector operator + (const Vector& v, const float o) {
		return Vector(v.x+o,v.y+o,v.z+o);
	}
   friend Vector operator * (const Vector& v, const float o) {
   	return Vector(v.x*o,v.y*o,v.z*o);
	}
	
   friend Vector operator * (const Vector& v, const int o) {
		   return Vector(v.x*o,v.y*o,v.z*o);
	}
  
   friend Vector operator * (const float o, const Vector& v) {
		   return Vector(v.x*o,v.y*o,v.z*o);
	}
	
   friend Vector operator * (const int o, const Vector& v) {
		   return Vector(v.x*o,v.y*o,v.z*o);
	}

   Point Position(void) {
		return Point(x,y,z);
	}

   void Normalize(void) {
   	float len;
   	len=this->Length();
		if (len>0) {
   		x=x/len;
   		y=y/len;
  			z=z/len;
		}
	}
	
   float Length(void) {
   	return static_cast<float> (sqrt(x*x+y*y+z*z));
	}

   Vector(const Vector& v) {
	   x=v.x;
	   y=v.y;
	   z=v.z;
	}
   Vector(void) {
	   x=0;
	   y=0;
	   z=0;
	}

	Vector(float x, float y, float z) {
	   this->x=x;
	   this->y=y;
	   this->z=z;
	}
};
#endif
