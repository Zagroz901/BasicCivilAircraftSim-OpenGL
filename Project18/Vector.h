#pragma once
#include <iostream>
#include <string>
#include <cmath>


using namespace std;
class Vector
{
public:
	double x,y,z;


	 Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    Vector operator+(const Vector& b) const {
        return Vector(x + b.x, y + b.y, z + b.z);
    }

    Vector operator-(const Vector& b) const {
        return Vector(x - b.x, y - b.y, z - b.z);
    }

    Vector operator*(double d) const {
        return Vector(x * d, y * d, z * d);
    }
	 Vector operator/(double d) const {
        if (d != 0) {
            return Vector(x / d, y / d, z / d);
        } else {
            // Handle division by zero case
            return Vector(0, 0, 0);
        }
    }
	double shdeh(){ //The magnitude of a vector describes its size or length.
		return sqrt(x*x + y*y + z*z);
		// The reason you might want to use this function is to find out how "long" the vector is in space. 
	}
    // wahede
	//This function calculates the normalized (unit) vector of the current vector.
	// In physics, a normalized vector is a vector that has the same direction as the original vector but a magnitude of 1.
	Vector wahede(){
		double s = shdeh();
		if(s>0.00001) //The code checks if the magnitude is greater than a small threshold (0.00001 in this case) to avoid division by nearly zero (which would result in numerical instability).
			return (*this) / s;//To normalize a vector, you need to divide each component of the vector by its magnitude.
		else
		{
			Vector vv;
			return vv;
		}
	}
	//Which is a mathematical operation used in physics to find a new vector that is perpendicular to both input vectors.
	Vector cross(Vector b){
		Vector c;
		c.x = this->y*b.z - b.y*this->z;
		c.y = -this->x*b.z + b.x*this->z;
		c.z = this->x*b.y - b.x*this->y;
		return c;
	}
	Vector rotate_x(double theta_deg){


		Vector c;
		double theta_rad = ( theta_deg *  3.1415) /  180 ; //When you use trigonometric functions, they are typically designed to work with angles expressed in radians rather than degrees. The main reason for this choice is that using radians simplifies the mathematical properties of these functions.

		c.x = this->x;//The x-component of the rotated vector remains unchanged because we are rotating around the x-axis.
		c.y = this->y * cos(theta_rad) -  this->z*sin(theta_rad);
		//this->y * cos(theta_rad) This operation preserves the magnitude of the y-component while modifying its direction due to the rotation.
	   //this->z*sin(theta_rad); This operation introduces a change in the y-component due to the rotation.                 
		c.z = this->y*sin(theta_rad) + this->z*cos(theta_rad);
		return c;
	}
	Vector rotate_y(double theta_deg){

		
		Vector c;
		double theta_rad = ( theta_deg *  3.1415) /  180 ; 

		c.x = this->x * cos(theta_rad) + this->z*sin(theta_rad);
		c.y = this->y;
		c.z = -this->x*sin(theta_rad) + this->z*cos(theta_rad);
		return c;
	}
	Vector rotate_z(double theta_deg){
		Vector c;
		double theta_rad = ( theta_deg *  3.1415) /  180 ; 

		c.x = this->x * cos(theta_rad) -  this->y*sin(theta_rad);
		c.y = this->x * sin(theta_rad) +  this->y*cos(theta_rad);
		c.z = this->z;
		return c;
	}
	//The dot product is used to find the angle between vectors and to calculate projections, work, and energy in physics.
	double dot(Vector b) { //the dot product is a fundamental concept in physics that's used to calculate work, angles, projections, and more
		return this->x * b.x + this->y * b.y + this->z * b.z;

		//this help in calc Angle Between Vectors: The dot product is related to the angle between two vectors. If the dot product is positive, the vectors are roughly pointing in the same direction. If it's negative, they're pointing in opposite directions. If it's zero, the vectors are perpendicular.
	}

	//This function calculates the angle between the current vector and another vector b in terms of physics concepts.
	//This is useful in physics for understanding the orientation of vectors in relation to each other. The dot product is used to compute the angle
	double angleBetween(Vector b) {
		double dotProductValue = this->dot(b);// This line calculates the dot product between the current vector and vector b. The dot product, as explained earlier, is a measure of how aligned the two vectors are.
		double magnitudeA = this->shdeh();
		double magnitudeB = b.shdeh();

		if(magnitudeA < 0.001)
			return 0;

		if(magnitudeB < 0.001)
			return 0;

		double cosTheta = dotProductValue / (magnitudeA * magnitudeB);//function is used to calculate the angle in radians from the cosine value of the angle between two vectors

		if(cosTheta >= 1) //This condition checks if the calculated cosine value is greater than or equal to 1. This is important because if the cosine value exceeds 1, it indicates that the vectors are essentially parallel, and the angle between them is very close to 0 degrees.
			return 0;

		// Return angle in radians
		//cout << "cosTheta AOA " << cosTheta << endl;
		double rad = std::acos(cosTheta);
		//cout << "rad AOA " << rad << endl;

		double deg = (rad * 180) / 3.1415; //This line converts the angle from radians to degrees.
		return deg;
	}
	void print(string str = "") {
		cout <<  str << " (" <<this->x << " , " << this->y << " , " << this->z << ")" << this->shdeh();// <<endl;
	}
};

