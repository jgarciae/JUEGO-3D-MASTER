#ifndef PROYECTILE_H
#define PROYECTILE_H

#include <math.h>
#include "Enemy.h"
#include "EnemyShip.h"

class Proyectile
{
public:
	GLfloat large;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat coordz;
	GLfloat velocity;
	bool state;
	GLfloat sprite;
	bool upgraded;

	double x;
	double y;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	Proyectile()
	{
		sprite = TextureManager::Inst()->LoadTexture("image/laser_blue.png", GL_BGRA_EXT, GL_RGBA);
		state=false;

		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;
	}


	/*GLfloat Right(){return coordx+large;}
	GLfloat Left(){return coordx-large;}
	GLfloat Up(){return coordy+large*4;}
	GLfloat Down(){return coordy-large*4;}*/

	void draw()
	{
		if(!state)
			return;

		/*if(upgraded)
		{
			timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
			deltatime = timer -timebase;// delta time
			timebase = timer;
			anim += deltatime;
			if (anim / 1000.0 > 10.0)
			{
				downgrade();
				//anim = 0;
			}
		}*/

		glPushMatrix();
		glTranslatef(coordx, coordy, coordz);
		glRotatef(90, 1.0, 0.0, 0.0);
		GLUquadricObj *obj = gluNewQuadric();
		glEnable(GL_TEXTURE_GEN_T);
    	glBindTexture(GL_TEXTURE_2D, sprite);
	    gluCylinder(obj, 0.1f, 0.4f, 5, 30, 30);
	    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    	glDisable(GL_TEXTURE_GEN_T);
	    glPopMatrix();

	    coordy+=velocity;
	}

	bool collision(Enemy *e)
	{
		if( sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) + pow(coordz - e->coordz, 2) ) 
			<= (large + e->radio) && e->state && state)
		{
			//e->state=false;
			//e->explosion();
			state=false;
			return true;
		}
		return false;
	}

	bool collisionShip(EnemyShip *es)
	{
		if( sqrt( pow(coordx - es->coordx, 2) + pow(coordy - es->coordy, 2) + pow(coordz - es->coordz, 2)) 
			<= (large + es->radio) && es->state && state)
		{
			es->state=false;
			state=false;
			return true;
		}
		return false;
	}

	void upgrade()
	{
		if(upgraded)
			return;
		sprite = TextureManager::Inst()->LoadTexture("image/laser_super.png", GL_BGRA_EXT, GL_RGBA);
		large=large*3.0f;
		upgraded=true;
		anim=0;
	}

	void downgrade()
	{
		if(!upgraded)
			return;
		sprite = TextureManager::Inst()->LoadTexture("image/laser_blue.png", GL_BGRA_EXT, GL_RGBA);
		large=large/3.0f;
		upgraded=false;
	}
	
};

class Proyectiles
{
public:
	int num;
	Proyectile *pry;
	int count;
	GLfloat large;
	GLfloat velocity;

	Proyectiles(int n)
	{
		num=n;
		pry=new Proyectile[num];
		count=0;
	}

	void initProyectile(GLfloat cx,GLfloat cy,GLfloat cz)
	{
		pry[count].large=large;
		pry[count].velocity=velocity;

		pry[count].coordx=cx;
		pry[count].coordy=cy;
		pry[count].coordz=cz;
		pry[count].state=true;

		count=(count+1)%num;
	}

	void draw()
	{
		for (int i = 0; i < num; ++i)
			pry[i].draw();
	}

	bool collision(Enemy *e)
	{
		for (int i = 0; i < num; ++i)
		{
			if (pry[i].collision(e))
				return true;
		}
		return false;
	}

	bool collisionShip(EnemyShip *es)
	{
		for (int i = 0; i < num; ++i)
		{
			if (pry[i].collisionShip(es))
				return true;
		}
		return false;
	}

	void upgrade()
	{
		for (int i = 0; i < num; ++i)
			pry[i].upgrade();
	}
};

#endif