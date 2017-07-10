#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>
#include "TextureManager.h"
#include "Ship.h"
#include "EnemyProyectile.h"

class EnemyShip
{
public:
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat coordz;
	GLfloat imagen;
	bool state;
	int respawn;
	int score;
	EnemyProyectile shot;

	GLfloat rotation;

	int timer;
	int timebase;
	int deltatime;

	int anim;
	int update;
	int rev;

	GLfloat mov;
	
	GLfloat velx;
	GLfloat velz;

	EnemyShip(GLfloat r,int sc)
	{
		imagen = TextureManager::Inst()->LoadTexture("image/navenemiga.png", GL_BGRA_EXT, GL_RGBA);

		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;
		update=0;
		rev=0;

		mov=0.01;

		radio=r;
		coordx=rand()%20-10;
		coordy=rand()%5+30;
		coordz=rand()%20-10;
		state=true;
		score=sc;

		shot.large=0.5f;
		shot.velocity=0.1f;

		rotation=0.0f;
	}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

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

	void draw(GLfloat cx, GLfloat cz)
	{
		timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer -timebase;// delta time
		timebase = timer;
		anim += deltatime;
		update += deltatime;
		if(!state)
		{
			revive(5.0);
			return;
		}
		/*glBindTexture(GL_TEXTURE_2D, imagen);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);//coordenadas de textura
		glVertex3d(Left(), Down(), 0);//dl
		glTexCoord2f(0.0,1.0);
		glVertex3d(Left(), Up(), 0);//ul
		glTexCoord2f(1.0,1.0);
		glVertex3d(Right(), Up(), 0);//ur
		glTexCoord2f(1.0,0.0);
		glVertex3d(Right(), Down(), 0);//dr
		glEnd();

		coordx+=mov;
		if(coordx >= 16.0f && coordx <= -16.0f)
			mov=mov*(-1.0f);

		shot.draw();*/


		glPushMatrix();
		glTranslatef(coordx,coordy,coordz);
		glRotatef(rotation, 0.0, 0.0, 1.0);
		
		//arriba
		normal(-1*radio,0*radio,-2.0f*radio,  0*radio, 1*radio, -2.0f*radio);
		glBegin(GL_TRIANGLES);
		glColor3f(1,1,0);
		glNormal3f(nx,ny,nz);
		glVertex3d(-1*radio, 0*radio, 0*radio);
		glVertex3d(0, 0, 2.0f*radio);
		glVertex3d(0*radio, 1*radio, 0*radio);
		glEnd();

		normal(0*radio, 1*radio, -2.0f*radio,  1*radio, 0*radio, -2.0f*radio);
		glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glNormal3f(nx,ny,nz);
		glVertex3d(0*radio, 1*radio, 0*radio);
		glVertex3d(0, 0, 2.0f*radio);
		glVertex3d(1*radio, 0*radio, 0*radio);
		glEnd();

		normal(1*radio, 0*radio, -2.0f*radio,  0*radio, -1*radio, -2.0f*radio);
		glBegin(GL_TRIANGLES);
		glColor3f(0,1,0);
		glNormal3f(nx,ny,nz);
		glVertex3d(1*radio, 0*radio, 0*radio);
		glVertex3d(0, 0, 2.0f*radio);
		glVertex3d(0*radio, -1*radio, 0*radio);
		glEnd();

		normal(0*radio, -1*radio, -2.0f*radio,  -1*radio, 0*radio, -2.0f*radio);
		glBegin(GL_TRIANGLES);
		glColor3f(0,0,1);
		glNormal3f(nx,ny,nz);
		glVertex3d(0*radio, -1*radio, 0*radio);
		glVertex3d(0, 0, 2.0f*radio);
		glVertex3d(-1*radio, 0*radio, 0*radio);
		glEnd();

		//abajo
		normal(-1*radio, 0*radio, 2.0f*radio,  0*radio, 1*radio, 2.0f*radio);
		glBegin(GL_TRIANGLES);
		glNormal3f(nx,ny,nz);
		glColor3f(0,0,1);
		glVertex3d(-1*radio, 0*radio, 0*radio);
		glVertex3d(0, 0, -2.0f*radio);
		glVertex3d(0*radio, 1*radio, 0*radio);
		glEnd();

		normal(0*radio, 1*radio, 2.0f*radio,  1*radio, 0*radio, 2.0f*radio);
		glBegin(GL_TRIANGLES);
		glColor3f(1,1,0);
		glNormal3f(nx,ny,nz);
		glVertex3d(0*radio, 1*radio, 0*radio);
		glVertex3d(0, 0, -2.0f*radio);
		glVertex3d(1*radio, 0*radio, 0*radio);
		glEnd();

		normal(1*radio, 0*radio, 2.0f*radio,  0*radio, -1*radio, 2.0f*radio);
		glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glNormal3f(nx,ny,nz);
		glVertex3d(1*radio, 0*radio, 0*radio);
		glVertex3d(0, 0, -2.0f*radio);
		glVertex3d(0*radio, -1*radio, 0*radio);
		glEnd();

		normal(0*radio, -1*radio, 2.0f*radio,  -1*radio, 0*radio, 2.0f*radio);
		glBegin(GL_TRIANGLES);
		glColor3f(0,1,0);
		glNormal3f(nx,ny,nz);
		glVertex3d(0*radio, -1*radio, 0*radio);
		glVertex3d(0, 0, -2.0f*radio);
		glVertex3d(-1*radio, 0*radio, 0*radio);
		glEnd();

		glPopMatrix();
		glColor3f(1,1,1);
		rotation++;

		coordx+=velx;
		coordz+=velz;

		updateCoords(cx,cz);

		shoot();
		shot.draw();
	}

	bool destroy()
	{
		if (state)
		{
			state=false;
			//part.iniParticles(coordx,coordy,coordz,0.0f,0.0f,1.0f);
			return true;
		}
		return false;
	}

	void updateCoords(GLfloat cx, GLfloat cz)
	{
		if(update/1000.0 > 2.0)
		{
			velx=(cx-coordx)*0.01;
			velz=(cz-coordz)*0.01;

			cout<<"Enemigo cambia direccion"<<endl;
			update=0;
		}
	}

	void shoot()
	{
		if (anim / 1000.0 > 5.0)
		{
			shot.state=true;
			shot.coordx=coordx;
			shot.coordy=coordy;
			shot.coordy=coordz;

			cout<<"Disparo enemigooooooooooooooooooooooooo"<<endl;
			anim=0;
		}
	}

	void revive(float rv)
	{
		rev += deltatime;
		if(rev/1000.0 > rv)
		{
			state=true;
			rev=0;
			cout<<"Revivio"<<endl;
		}
	}
	
};

#endif