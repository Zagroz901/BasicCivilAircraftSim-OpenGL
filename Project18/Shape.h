#pragma once
#include "Vector.h"
#include <iostream>
#include <cmath>

// gimble lock

using namespace std;
class Shape
{
public:
	Vector v,a,pos;
	Vector Av,Aa,Apos;

	double pitch, roll, yaw;
	double rudder, elevator, aileron;
	// omega , alpha , theta
	// Apos = pitch , roll , yaw
	double m , m_without_fuel , p , s , m_fuel_burn,m_fuel_burn_change,m_fuel_burn_max , m_fuel , v_engine_out , dt;
	double dElevator;
	double IElevator;
	double omegaPitch;
	double clElevator;
	double aElevator;

	double dAileron;
	double IAileron;
	double omegaRoll;
	double clAileron;
	double aAileron;

	double dRudder;
	double IRudder;
	double omegaYaw;
	double clRudder;
	double aRudder;


	Shape(){
		dt = 0.01;
		m_without_fuel = 20000.0; // وزن الطائرة بدون وقود بالكيلوجرام
		m_fuel = 50000.0; // وزن الوقود بالكيلوجرام
		m = m_without_fuel + m_fuel;
		m_fuel_burn = 100.0; // معدل احتراق الوقود بالكيلوجرام/الثانية
		m_fuel_burn_max = 100000.0; // الحد الأقصى لمعدل احتراق الوقود
		m_fuel_burn_change = 10.0; // تغيير معدل احتراق الوقود
		p = 1.225; // كثافة الهواء بالكيلوجرام/متر مكعب (القيمة الواقعية)
        s = 25.0;  // مساحة الجناح بالمتر مربع (القيمة الواقعية)
		v_engine_out = 900.0;
		

		rudder = 0;
		elevator = 0;
		aileron = 0;

		dElevator = 40;
		IElevator = 40000;
		omegaPitch = 0;
		clElevator = 0.5;
		aElevator = 2;

		dAileron = 40;
		IAileron = 40000;
		omegaRoll = 0;
		clAileron = 0.5;
		aAileron = 2;

		dRudder = 40;
		IRudder = 4000;
		omegaYaw = 0;
		clRudder = 0.5;
		aRudder = 2;
		// 500 to 900 meters per second

		//259000 

	}

	Vector F_total(){


		Vector ff =
			F_gravity() +
			F_Drag() +
			F_Lift()+
			F_Ground()+
			F_thrust()
			;

		//F_Drag().print("F_Drag : ");
		//F_Lift().print("F_Lift : ");
		//F_thrust().print("thrust : ");
		ff.print("F_total ");
		v.print("V       ");
		cout << endl;
		return ff;
	}


	//The AOA method calculates the angle of attack of the aircraft. This angle is crucial in aerodynamics as it affects the lift and drag forces acting on the aircraft. It's the angle between the aircraft's velocity vector and its "front" vector (or the reference line on the aircraft).
	double AOA(){//AOA stands for "Angle of Attack." In aerodynamics, the angle of attack is the angle between the oncoming air (or fluid) and a reference line on an object. It's a crucial parameter that affects the lift and drag forces experienced by the object
		
		if((v-Front()).shdeh() < 0.01)
			return 0;

		double	aoa =  v.angleBetween(Front()); /// This line calculates the angle between the object's velocity vector v and its "front" vector using the angleBetween() function. This gives you the actual angle of attack.
		// cout << "aoa" << aoa << endl;

		if(Front().wahede().y > v.wahede().y)
			return aoa;
		else
			return -aoa;
	}

	// Function to calculate linear velocity due to rotation
Vector linearVelocityDueToRotation(Vector rotationAxis, double angularVelocity) {
    double radius = rotationAxis.shdeh();
    return rotationAxis * (radius * angularVelocity);
}


//This method calculates the thrust force produced by the aircraft's engines. It considers properties like temperature, pressure, and the specific gas constant for air.
	void flyPlaneFly(){//This method simulates the flight of the aircraft over time. It updates the position, velocity, and acceleration based on the forces acting on the object and its mass.
	m = m_without_fuel + m_fuel;

		

        if (pos.y <= 0 && v.wahede().y <= 0)
       {
		   

            a = F_total() / m;
            v = a * dt + v;
            pos = v * dt + pos;
			updatePitch();
			updateRoll();
			updateYaw();
			
			/*if(pos.y <= 0 && v.y <=0) {
				pos.y = 0;
				v.y = 0;
			}
			

			/*if(v.shdeh() > 200)
				v = v.wahede() * (200);*/
			//Av = Av + Aa * dt;
            //Apos = Apos + Av * dt;
       }
			else
       
        {
            a = (F_total() - F_gravity()) / m;
            v = a * dt + v;
            pos = v * dt + pos;
			updatePitch();
			updateRoll();
			updateYaw();
			
			// Av = Av + Aa * dt;
            //Apos = Apos + Av * dt;
        }

	

	}
	Vector F_gravity(){
		Vector g ,f;
		g.y= -9.8;
		f = g*m;
		return f;
	}
	//not complete
	//This method calculates the thrust force produced by the aircraft's engines. It considers properties like temperature, pressure, and the specific gas constant for air.
	double thrust_shdeh(){
		if(m_fuel <= 0 ){
			return 0 ;
		}
		//		cout << "brn " << m_fuel_burn*dt << endl;
		//		m_fuel =  m_fuel - (m_fuel_burn*dt) ;

		const double gamma = 1.4;
		const double R = 287.05; // Specific gas constant for air in J/(kg*K)

		// Default values for user inputs (example values)
		double Tt = 1000.0; // Total temperature in Kelvin
		double pe = 101325.0; // Pressure at the exit in Pa
		double pt = 3000000.0; // Pressure at the combustion chamber in Pa

		// Calculate exhaust gas velocity
		double term1 = 2 * gamma * R * Tt;
		double term2 = gamma - 1;
		double term3 = 1 - pow(pe / pt, term2 / gamma);

		double term4 = term1 / term2 * term3;


		v_engine_out =  sqrt(term4);

		//cout << "term " << v_engine_out << endl;

		return v_engine_out * m_fuel_burn*dt;
		//return 10000000;
	}
	void increase_fuel()
	{
		if(m_fuel_burn + m_fuel_burn_change <= m_fuel_burn_max)
			m_fuel_burn+=m_fuel_burn_change;
	}
	void decrease_fuel()
	{
		if(m_fuel_burn > m_fuel_burn_change)
			m_fuel_burn-=m_fuel_burn_change;
	}

	Vector F_thrust()
	{
		Vector dir = Front();
		

		if (m_fuel > 0)
		{
			Vector f = dir * thrust_shdeh();
			return f;
		}
		else
		{
			return Vector(); // No thrust when fuel is depleted
		} 
	}
	Vector F_Lift()
	{
		Vector  f , dir , right;
		right = Right();
		dir = right.cross(v).wahede();
		double v2 = v.shdeh() * v.shdeh() ; 
		double l = 0.5 * cal_Cl() * v2 * p * s;
		return dir * l ; 
	}
	Vector F_Drag()
	{
		Vector  D , vw , Dw ;
		vw = v.wahede(); 
		Dw = vw*(-1); 

		double v2 = v.shdeh() * v.shdeh() ; 
		double d = 0.5 * p * cal_Cd() * s * v2; 


		D = Dw * d;
		return D ; 
	}
	Vector F_Ground()//calculates the force when the object is in contact with the ground.
	{
		Vector  w,g,l;
		w = F_gravity();
		l = F_Lift();
		if( this->pos.y <= 0){
			if( abs(w.y) >= abs(l.y))
				g.y = abs(w.y) - abs(l.y);
			else
				g.y=0;
		}
		else
		{
			g.y=0;
		}
		//cout << g.y << " - " << g.y << endl;
		/*	l.print();
		g.print();
		w.print();*/

		return g ; 
	}
	
	Vector Right(){
		Vector a,  b , c ,d;
		a.x = 1;
		
		


		
		b = a.rotate_z(roll);
		c = b.rotate_x(pitch);
		d = c.rotate_y(yaw);


		return d.wahede();
	}
	Vector Front(){
		Vector a , b , c ,d;
		a.z = -1;
		b = a.rotate_z(roll);
		c = b.rotate_x(pitch);
		d = c.rotate_y(yaw);
		
		return d.wahede();
	}
	//not complete
	Vector Up(){
		Vector a , b , c ,d;
		a.y = 1;
		/*b = a.rotate_z(roll);
		c = b.rotate_x(pitch);
		d = c.rotate_y(yaw);*/

		return d.wahede();}
	//not complete
	//The coefficient of lift, often denoted as "Cl," is a dimensionless value that quantifies the lift generated by an airfoil (such as an aircraft's wing) at a specific angle of attack. 
	double cal_Cl()
	{
		double x = AOA();
		double y = -0.0002 * pow(x ,  3) + 0.0001 * pow(x , 2 )  + 0.1157 * x + 0.4391 ; 
		return y ; 
	}
	//not complete

	//The coefficient of drag, often denoted as "Cd," is another dimensionless value that quantifies the drag experienced by an airfoil as it moves through the air. Drag opposes the aircraft's motion and is caused by air resistance. Minimizing drag is essential for achieving fuel efficiency and high-speed flight.
	double cal_Cd()
	{
		double x = AOA();
		double y = -0.0002 * pow(x ,  3) + 0.0001 * pow(x , 2 )  + 0.1157 * x + 0.4391 ; 
		return y ; 
	}
	

	void updatePitch() {

		double Lift = (0.5)* p * v.shdeh() * v.shdeh() * clElevator * elevator * aElevator;
		double  angleDrag = -2000000 * omegaPitch; 

		double Torque = Lift * dElevator + angleDrag;
		double alpha  = Torque / IElevator;
		//double dt = 0.1;
		omegaPitch += alpha * dt;

		if(omegaPitch > 2)
			omegaPitch = 2;
		if(omegaPitch < -2)
			omegaPitch = -2;

		pitch += omegaPitch*dt;

		if (pitch > 40)
		{
			pitch = 40;
		}

		if(pitch < -20) {
			pitch = -20;
		}

		// Calculate linear velocity due to rotation
   /* double radius =12;
    Vector linearVelocityDueToRotation =  radius * omegaPitch;
    
    // Add the calculated linear velocity to the current velocity
    v = v+ linearVelocityDueToRotation;*/

	}

	void updateRoll() {
		double Lift = (0.5)* p * v.shdeh() * v.shdeh() * clAileron * aileron * aAileron;
		double  angleDrag = -1000000 * omegaRoll; 

		double Torque = Lift * dAileron + angleDrag;
		double alpha  = Torque / IAileron;
		//double dt = 0.1;
		omegaRoll += alpha * dt;

		if(omegaRoll > 2)
			omegaRoll = 2;
		if(omegaRoll < -2)
			omegaRoll = -2;

		roll += omegaRoll*dt;

		if (roll > 50)
		{
			roll = 50;
		}

		if(roll < -50) {
			roll = -50;
		}

	//	double radius =12;
  //  Vector linearVelocityDueToRotation =  radius * omegaRoll;
    
    // Add the calculated linear velocity to the current velocity
    //v = v+ linearVelocityDueToRotation;
	}

	void updateYaw() {
		double Lift = (0.5)* p * v.shdeh() * v.shdeh() * clRudder * rudder * aRudder;
		double  angleDrag = -1000000 * omegaYaw; 

		double Torque = Lift * dRudder + angleDrag;
		double alpha  = Torque / IRudder;
		//double dt = 0.1;
		omegaYaw += alpha * dt;

		if(omegaYaw > 2)
			omegaYaw = 2;
		if(omegaYaw < -2)
			omegaYaw = -2;

		yaw += omegaYaw*dt;

		if (yaw > 50)
		{
			yaw = 50;
		}

		if(yaw < -50) {
			yaw = -50;
		}
		//double radius =2;
   // Vector linearVelocityDueToRotation =  radius * omegaYaw;
    
    // Add the calculated linear velocity to the current velocity
   // v = v+ linearVelocityDueToRotation;
	}
};



