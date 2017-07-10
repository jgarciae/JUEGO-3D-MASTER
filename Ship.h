#ifndef SHIP_H
#define SHIP_H

#include <GL/glut.h>
#include "TextureManager.h"
#include "Proyectile.h"
#include "Bonus.h"
#include <iostream>
#include <unistd.h>
#include "Particle.h"


using namespace std;

class Ship
{
public:
	int lives;
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat coordz;
	GLfloat cub;
	GLfloat cubd;
	GLfloat cubb;
	bool state;
	GLfloat sprite;
	int total_score;
	//Proyectile shot;
	Proyectiles *shots;

	bool explode;

	bool upgrade_shot;

	GLfloat rotx;
	GLfloat roty;

	int iter;
	double x;
	double y;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	Ship();

	Ship(GLfloat r, GLfloat xx, GLfloat yy,GLfloat zz, int lv)
	{
		//sprite = TextureManager::Inst()->LoadTexture("image/ship2.png", GL_BGRA_EXT, GL_RGBA);
		sprite = TextureManager::Inst()->LoadTexture("image/ship2.png", GL_RGB, GL_RGB);
		lives=lv;
		radio=r;
		coordx=xx;
		coordy=yy;
		coordz=zz;
		total_score=0;
		state=true;
		explode=false;

		shots=new Proyectiles(5);
		shots->large=0.25f;
		shots->velocity=0.5f;

		iter=0;
		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;

		rotx=0.0f;
		roty=0.0f;
		cub = TextureManager::Inst()->LoadTexture("image/cubiertanave.png", GL_BGRA_EXT, GL_RGB);
		cubd = TextureManager::Inst()->LoadTexture("image/cubiertanaveabajo.png", GL_BGRA_EXT, GL_RGB);
		cubb = TextureManager::Inst()->LoadTexture("image/cubiertaatras.png", GL_BGRA_EXT, GL_RGB);

		x = 0.25;
		y = 0.666;

		upgrade_shot=true;
	}

	void go_right(){coordx+=0.5;}
	void go_left(){coordx-=0.5;}
	void go_up(){coordz+=0.5;}
	void go_down(){coordz-=0.5;}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void rotate_right()
	{
		if(roty<=45.0f)
			roty++;
	}
	void rotate_left()
	{
		if(roty>=-45.0f)
			roty--;
	}
	void rotate_up()
	{
		if(rotx<=45.0f)
			rotx++;
	}
	void rotate_down()
	{
		if(rotx>=-45.0f)
			rotx-=2.0f;
	}

	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
	void normal(GLfloat ax,GLfloat ay, GLfloat az, GLfloat bx,GLfloat by, GLfloat bz)
	{
		nx=(ax*bz)-(az*by);
		ny=(az*bx)-(ax*bz);
		nz=(ax*by)-(ay*bx);
		GLfloat mod=(GLfloat)sqrt((nx*nx)+(ny*ny)+(nz*nz));
		nx/=mod;
		ny/=mod;
		nz/=mod;
	}

	void draw()
	{
		timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer -timebase;// delta time
		timebase = timer;
		anim += deltatime;

		if(!state)
			return;
//<<<<<<< HEAD
		
		//glTranslatef(5.0, 0.0, 0.0);

		glBindTexture(GL_TEXTURE_2D, sprite);
//=======
		glPushMatrix();
		glTranslatef(coordx,coordy,coordz)	;

		//glRotatef(45.0, 1.0, 0.0, 0.0);
		glRotatef(rotx, 1.0, 0.0, 0.0);
		glRotatef(roty, 0.0, 1.0, 0.0);

		//normal(2*radio, radio, radio, )
		glBindTexture(GL_TEXTURE_2D, cubb);
		glBegin(GL_QUADS);
		normal(-2*radio,-1*radio,radio, 0,0,2*radio);
		glNormal3f(nx,ny,nz);
		glTexCoord2f(0.5,0.0);
		glVertex3d(0*radio,-1*radio,-1*radio);
		glTexCoord2f(0.0,0.5);
		glVertex3d(-2*radio,-2*radio,0*radio);
		normal(2*radio,radio,radio, 0,0,0);
		glNormal3f(nx,ny,nz);
		glTexCoord2f(0.5,1.0);
		glVertex3d(0*radio,-1*radio,1*radio);
		glTexCoord2f(1.0,0.5);
		glVertex3d(2*radio,-2*radio,0*radio);
		glEnd();

			normal(2*radio,4*radio,0,  2*radio,radio,radio);
			glBindTexture(GL_TEXTURE_2D, cub);
			glBegin(GL_TRIANGLES);
			//glColor3f(1,1,0); //amarillo
			glNormal3f(nx,ny,nz);
			glTexCoord2f(0.0,0.0);
			glVertex3d(-2*radio,-2*radio,0*radio);
			glTexCoord2f(1.0,1.0);
			glVertex3d(0*radio,2*radio,0*radio);
			glTexCoord2f(1.0,0.25);
			glVertex3d(0*radio,-1*radio,1*radio);
			glEnd();

			normal(-2*radio,4*radio,0, -2*radio,radio,radio);
			glBindTexture(GL_TEXTURE_2D, cub);
			glBegin(GL_TRIANGLES);
			//glColor3f(1,0,0);//rojo
			glNormal3f(nx,ny,nz);
			glTexCoord2f(0.0,0.0);
			glVertex3d(2*radio,-2*radio,0*radio);
			glTexCoord2f(1.0,1.0);
			glVertex3d(0*radio,2*radio,0*radio);
			glTexCoord2f(1.0,0.25);
			glVertex3d(0*radio,-1*radio,1*radio);
			glEnd();


			normal(-2*radio,4*radio,0, -2*radio,radio,-1*radio);
			glBindTexture(GL_TEXTURE_2D, cubd);
			glBegin(GL_TRIANGLES);
			//glColor3f(0,1,0);//verde
			glNormal3f(nx,ny,nz);
			glTexCoord2f(0.0,0.0);
			glVertex3d(2*radio,-2*radio,0*radio);
			glTexCoord2f(1.0,1.0);
			glVertex3d(0*radio,2*radio,0*radio);
			glTexCoord2f(1.0,0.25);
			glVertex3d(0*radio,-1*radio,-1*radio);
			glEnd();

			normal(2*radio,4*radio,0, 2*radio,radio,-1*radio);
			glBindTexture(GL_TEXTURE_2D, cubd);
			glBegin(GL_TRIANGLES);
			//glColor3f(0,0,1);//azul
			glNormal3f(nx,ny,nz);
			glTexCoord2f(0.0,0.0);
			glVertex3d(-2*radio,-2*radio,0*radio);
			glTexCoord2f(1.0,1.0);
			glVertex3d(0*radio,2*radio,0*radio);
			glTexCoord2f(1.0,0.25);
			glVertex3d(0*radio,-1*radio,-1*radio);
			glEnd();


		glPopMatrix();
		glColor3f(1,1,1);

		if (anim / 1000.0 > 0.15)
		{
			iter=(iter+1)%5;
			anim = 0;
		}
		shots->draw();

	}

	

	void win(int sc)
	{
		total_score+=sc;
	}

	void shoot()
	{
		shots->initProyectile(coordx, coordy+radio+shots->large, coordz);
	}


	bool destroy()
	{
		if (state)
		{
			state=false;
			lives--;
			return true;
		}
		return false;
	}

	bool bonus_collision(Bonus *b)
	{
		if( sqrt( pow(coordx - b->coordx, 2) + pow(coordy - b->coordy, 2) ) <= (radio + b->radio) && b->state && state)
		{
			b->state=false;
			if(b->type==0)
				explode=true;
			if(b->type==1)
				shots->upgrade();
			return true;
		}
		return false;
	}

	bool collision(Enemy *e)
	{


		if(sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) +  pow(coordz - e->coordz, 2)) 
			<= e->radio+radio && e->state && state )
		{				
			e->state=false;
			sleep(1);
			if(lives==0){
				state=false;
			}	
				
			//explosion();
			lives--;
			return true;
		}
		return false;
	}

	bool collisionShot(EnemyShip *ep)
	{
		if(sqrt( pow(coordx - ep->shot.coordx, 2) + pow(coordy - ep->shot.coordy, 2) +  pow(coordz - ep->shot.coordz, 2)) 
			<= ep->shot.large + radio && ep->shot.state && state )
		{				
			ep->shot.state=false;
			sleep(1);
			if(lives==0){
				state=false;
			}	
				
			//explosion();
			lives--;
			return true;
		}
		return false;	
	}

	//~Ship();
	
};

#endif
