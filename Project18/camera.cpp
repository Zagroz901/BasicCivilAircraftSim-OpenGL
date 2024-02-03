#include <windows.h>		// Header File For Windows
#include <gl/GL.h>				// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
//#include <gl/glut.h>			// Header File For The GLut32 Library
#include <fstream>
#include <math.h>

#include "camera.h"

#include <stdlib.h>   /* for exit */

#define SQR(x) (x*x)
float aaa=0;
#define NULL_VECTOR Vector3dCreate(0.0f,0.0f,0.0f)

Vector3dStruct Vector3dCreate ( GLfloat x, GLfloat y, GLfloat z )
{
	Vector3dStruct tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

GLfloat LengthVector3d( Vector3dStruct * v)
{
	return (GLfloat)(sqrt(SQR(v->x)+SQR(v->y)+SQR(v->z)));
}

Vector3dStruct NormalizeVector3d( Vector3dStruct v)
{
	Vector3dStruct res;
	float L = LengthVector3d(&v);
	if (L == 0.0f) return NULL_VECTOR;
	res.x = v.x / L;
	res.y = v.y / L;
	res.z = v.z / L;
	return res;
}

Vector3dStruct operator+ (Vector3dStruct v, Vector3dStruct u)
{
	Vector3dStruct res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	res.z = v.z+u.z;
	return res;
}
Vector3dStruct operator- (Vector3dStruct v, Vector3dStruct u)
{
	Vector3dStruct res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	res.z = v.z-u.z;
	return res;
}


Vector3dStruct operator* (Vector3dStruct v, float r)
{
	Vector3dStruct res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}

Vector3dStruct CrossProduct (Vector3dStruct * u, Vector3dStruct * v)
{
	Vector3dStruct resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;

	return resVector;
}
float operator* (Vector3dStruct v, Vector3dStruct u)	//dot product
{
	return v.x*u.x+v.y*u.y+v.z*u.z;
}




/***************************************************************************************/

Camera::Camera()
{
	
	Position = Vector3dCreate (0.0, 0.0,0.0);
	View = Vector3dCreate( 0.0, 0.0, -1.0);
	RightVector = Vector3dCreate (1.0, 0.0, 0.0);
	Up = Vector3dCreate (0.0, 1.0, 0.0);


	RotatedX = RotatedY = RotatedZ = 0.0;
}

void Camera::Move (Vector3dStruct Direction)
{
	Position = Position + Direction;
}

void Camera::RotateX (GLfloat Angle)
{

	RotatedX += Angle;
	//Rotate viewdir around the right vector:
	View = NormalizeVector3d(View*cosf(Angle*PIdiv180)+ Up*sinf(Angle*PIdiv180));
	//now compute the new UpVector (by cross product)
	Up = CrossProduct(&View, &RightVector)*-1;

	
}

void Camera::RotateY (GLfloat Angle)
{
	RotatedY += Angle;
	//Rotate viewdir around the up vector:
	View = NormalizeVector3d(View*cosf(Angle*PIdiv180)- RightVector*sinf(Angle*PIdiv180));
	//now compute the new RightVector (by cross product)
	RightVector = CrossProduct(&View, &Up);
}

void Camera::RotateZ (GLfloat Angle)
{
	RotatedZ += Angle;
	//Rotate viewdir around the right vector:
	RightVector = NormalizeVector3d(RightVector*cosf(Angle*PIdiv180)+ Up*sinf(Angle*PIdiv180));
	//now compute the new UpVector (by cross product)
	Up = CrossProduct(&View, &RightVector)*-1;
}

void Camera::Render( void )
{
	//calculate view point
	Vector3dStruct ViewPoint = Position+View;

	
	gluLookAt(	Position.x,Position.y,Position.z,
				ViewPoint.x,ViewPoint.y,ViewPoint.z,
				Up.x,Up.y,Up.z);

}

void Camera::MoveForward( GLfloat Distance )
{
	Position = Position + (View*Distance);
}

void Camera::MoveRight ( GLfloat Distance )
{
	Position = Position + (RightVector*Distance);
}

void Camera::MoveUpward( GLfloat Distance )
{
	Position = Position + (Up*Distance);
}

void Camera::SetRotateX(GLfloat Angle)
{
	
	View = Vector3dCreate( 0.0, 0.0, -1.0);
	RightVector = Vector3dCreate (1.0, 0.0, 0.0);
	Up = Vector3dCreate (0.0, 1.0, 0.0);
	RotatedX=Angle;
}


void Camera::Control_With_KeyBoard(bool keys[])
{
	if( keys['Y'] ){ aaa=0; }

	if( keys['T'] ){ aaa=1; }
	

	if (keys['i'] && Position.x > 1 && Position.x < 30 && aaa==1 && Position.z > 1 && Position.z < 10 ) MoveForward(0.2);
	if (keys['i'] && Position.x > 33 && Position.x < 63 && aaa==1 && Position.z > 1 && Position.z < 10 ) MoveForward(0.2);
	if (keys['i'] && Position.x > 66 && Position.x < 96 && aaa==1 && Position.z > 1 && Position.z < 10 ) MoveForward(0.2);
	if (keys['i'] && Position.x > 99 && Position.x < 121 && aaa==1 && Position.z > 1 && Position.z < 10 ) MoveForward(0.2);

	if (keys['i']  && aaa==0 )
		MoveForward(0.2);

	if (keys['k'] && Position.x > 0 && Position.x < 31&& aaa==1 && Position.z > 0 && Position.z < 12 ) MoveForward(-0.2);
	if (keys['k'] && Position.x > 32 && Position.x < 64&& aaa==1 && Position.z > 0 && Position.z < 12) MoveForward(-0.2);
	if (keys['k'] && Position.x > 65 && Position.x < 97&& aaa==1 && Position.z > 0 && Position.z < 12) MoveForward(-0.2);
	if (keys['k'] && Position.x > 98 && Position.x < 122&& aaa==1 && Position.z > 0 && Position.z < 12) MoveForward(-0.2);

	if (keys['S'] && aaa==0)
		MoveForward(-0.2);

	if (keys['j'])
		RotateY(0.4);
	if (keys['l'])
		RotateY(-0.4);

	if (keys['E']  && aaa==0 )
    MoveUpward(0.2);
  if (keys['E'] &&  Position.y <= 9 && aaa==1 )
    MoveUpward(0.5);

  if (keys['Q'] && aaa==0 && Position.y>0)
    MoveUpward(-0.2);
    if (keys['Q'] && Position.y >= 1  && aaa==1 )
    MoveUpward(-0.5);

	if (keys[VK_UP])
		RotateX(-0.4);
	if (keys[VK_DOWN])
		RotateX(0.4);
	if (keys[VK_LEFT])
		RotateZ(0.2);
	if (keys[VK_RIGHT])
		RotateZ(-0.2);

	
	
}