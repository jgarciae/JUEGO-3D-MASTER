#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>

using namespace std;

#define RANDOM ((float)rand()/RAND_MAX)
#define PI 3.1416
#define MAX 300

struct Particle
{
	//float	life;					
	//float	death;					
	GLfloat mass;    	
	GLfloat coordx, coordy, coordz;    			
	GLfloat velocx, velocy, velocz; 			
    GLfloat accelx, accely, accelz;
};

class Particles
{
private:
	Particle 	points[MAX];
	float		life;
	float 		death;
	float		red, green, blue;

public:
	Particles(){}

	void iniParticles(GLfloat cx, GLfloat cy,GLfloat cz, GLfloat acx, GLfloat acy, GLfloat ms)
	{
		GLfloat v, t, f;

		for(int i=0; i<MAX; i++)
		{
			v = 0.4*RANDOM+0.1;
		    f = RANDOM*PI;
		    t = 2.0*RANDOM*PI;

		    points[i].mass = ms;
		    points[i].coordx = cx;
		    points[i].coordy = cy;
		    points[i].coordz = cz;
		    points[i].velocx = v*cos(t)*sin(f); 
		    points[i].velocy = v*cos(f)*cos(t); 
		    points[i].velocz = v*sin(t)*sin(f); 
			points[i].accelx = acx;
		    points[i].accely = acy - (points[i].mass*0.01f);
		    points[i].accelz = 0.0f;
			//points[i].life = 1.0f;		                
			//points[i].death = 0.01f;	
		}
		life = 1.0;
		death = 0.01;

		red=RANDOM;
		green=RANDOM;
		blue=RANDOM;

		cout<<"Coordenada X: "<<cx<<endl;
		cout<<"Coordenada Y: "<<cy<<endl;
		cout<<"Coordenada Z: "<<cz<<endl;
	}

	void draw()
	{
		if(life<0.0)
			return;

		for (int i=0; i<MAX; i++)
		{
			//glColor4f(1.0,1.0,1.0, life);
			//glColor4f(red,green,blue, life);

			/*glBegin(GL_POINTS);				        
			glVertex3f(points[i].coordx, points[i].coordy, points[i].coordz);                  
			glEnd();*/

			GLfloat side=0.5f;
			glBegin(GL_QUADS);				        
			glVertex3f(points[i].coordx-side, points[i].coordy-side, points[i].coordz);
			glVertex3f(points[i].coordx-side, points[i].coordy+side, points[i].coordz);
			glVertex3f(points[i].coordx+side, points[i].coordy+side, points[i].coordz);
			glVertex3f(points[i].coordx+side, points[i].coordy-side, points[i].coordz);                  
			glEnd();

			/*glPushMatrix();
			glTranslatef(points[i].coordx, points[i].coordy, points[i].coordz);
			glutSolidSphere(1.0f,5,5);
			glPopMatrix();*/

			points[i].coordx += points[i].velocx;
			points[i].coordy += points[i].velocy;
			points[i].coordz += points[i].velocz;
			points[i].velocx += points[i].accelx;
			points[i].velocy += points[i].accely;
			points[i].velocz += points[i].accelz;
		}
		life -= death;
	}
	void print_life()
	{
		cout<<life<<endl;
	}
};

class Set_Particles
{
private:
	Particles 	*parts;
	int 		num_parts;
	int 		current;

public:
	Set_Particles(int n)
	{
		num_parts=n;
		parts=new Particles[num_parts];
		current=0;
	}

	void init(GLfloat cx, GLfloat cy, GLfloat cz,  GLfloat acx, GLfloat acy, GLfloat ms)
	{
		parts[current].iniParticles(cx, cy,cz, acx, acy, ms);
		current=(current+1)%num_parts;
	}
	
	void draw()
	{
		for (int i = 0; i < num_parts; ++i)
			parts[i].draw();
	}

	void print_state()
	{
		cout<<"Actual: "<<current<<endl;
		for (int i = 0; i < num_parts; ++i)
		{
			cout<<"Vida Particula "<<i<<": ";
			parts[i].print_life();
		}
	}

};

#endif