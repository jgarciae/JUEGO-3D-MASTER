#ifndef ENEMYPROYECTILE_H
#define ENEMYPROYECTILE_H

#include <math.h>
#include "Enemy.h"

class EnemyProyectile
{
public:
	GLfloat large;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat coordz;
	GLfloat velocity;
	bool state;
	GLfloat sprite;

	double x;
	double y;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	EnemyProyectile()
	{
		sprite = TextureManager::Inst()->LoadTexture("image/death_shot.png", GL_BGRA_EXT, GL_RGBA);
		state=false;

		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;
	}


	GLfloat Right(){return coordx+large;}
	GLfloat Left(){return coordx-large;}
	GLfloat Up(){return coordy+large*4;}
	GLfloat Down(){return coordy-large*4;}

	void draw()
	{
		if(!state)
			return;
		
		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(coordx,coordy,coordz);

		glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    	glEnable(GL_TEXTURE_GEN_T);
    	glBindTexture(GL_TEXTURE_2D, sprite);
		glutSolidSphere(large,10,10);
		glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    	glDisable(GL_TEXTURE_GEN_T);

		glPopMatrix();
		glColor3f(1,1,1);

		coordy-=velocity;
	}


	
};

#endif