#ifndef BONUS_H
#define BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>
#include "TextureManager.h"

class Bonus
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
	int type;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	GLfloat rotatex;
	GLfloat rotatey;
	GLfloat rotatez;

	Bonus(GLfloat r, int sc, int tp)
	{
		radio=r;
		score=sc;
		state=false;
		type=tp;
		switch(type)
		{
			case 0:
				imagen = TextureManager::Inst()->LoadTexture("image/grenade.png", GL_BGRA_EXT, GL_RGBA);
				break;
			case 1:
				imagen = TextureManager::Inst()->LoadTexture("image/ray.png", GL_BGRA_EXT, GL_RGBA);
				break;
			default:
				break;
		}
		coordx=rand()%20-10;
		coordy=rand()%5+30;
		coordz=rand()%20-10;

		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;

		rotatex=0.0f;
		rotatey=0.0f;
		rotatez=0.0f;
	}

	void setType(int tp)
	{
		type=tp;
		switch(type)
		{
			case 0:
				imagen = TextureManager::Inst()->LoadTexture("image/grenade.png", GL_BGRA_EXT, GL_RGBA);
				break;
			case 1:
				imagen = TextureManager::Inst()->LoadTexture("image/ray.png", GL_BGRA_EXT, GL_RGBA);
				break;
			default:
				break;
		}
	}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void draw()
	{
		if(!state)
		{
			revive(10.0);
			return;
		}

		glPushMatrix();
		glTranslatef(coordx,coordy,coordz);

		glRotatef(rotatex, 1.0, 0.0, 0.0);
		glRotatef(rotatey, 0.0, 1.0, 0.0);
		glRotatef(rotatez, 0.0, 0.0, 1.0);
		
		glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    	glEnable(GL_TEXTURE_GEN_T);
    	glBindTexture(GL_TEXTURE_2D, imagen);
		glutSolidCube(radio);	
		glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    	glDisable(GL_TEXTURE_GEN_T);
		glPopMatrix();

		rotatex++;
		rotatey++;
		rotatez++;

		coordy-=0.05f;
		if(Down()<-20)
			state=false;
	}

	void revive(float rv)
	{
		timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer -timebase;// delta time
		timebase = timer;
		anim += deltatime;

		if (anim / 1000.0 > rv)
		{
			state=true;
			coordx=rand()%20-10;
			coordy=rand()%5+5;
			coordx=rand()%20-10;
			int rn=rand()%2;
			setType(rn);
			anim=0;
		}
	}

	//~Bonus();
	
};

#endif