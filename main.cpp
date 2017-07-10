#define GLUT_DISABLE_ATEXIT_HACK	
//#include <windows.h>
#include <math.h>
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
//#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include <GL/glut.h>
#include "TextureManager.h"
#include "Ship.h"
#include "Bonus.h"
#include "EnemyShip.h"
//#include "Rock.h"

#define KEY_ESC 27

using namespace std;

Ship *nave;
Enemy **enemigo;
Bonus **bono;
EnemyShip *nave_malvada;

int num_enemigos=20;
int num_bonos=5;

GLfloat sprites;
GLfloat texture;
GLfloat shoot;
GLfloat rock;
GLfloat black;
GLfloat grenade;

int timer = 0;
int timebase = 0;
int deltatime=0;
int anim = 0;
int iter = 0;
double x = 0.2;
double y = 0.666;


/*#define FILENAME "nine.wav"

ALuint buffer, source; 
void loadSound(){
  // Load pcm data into buffer
  buffer = alutCreateBufferFromFile(FILENAME);
  // Create sound source (use buffer to fill source)
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);
}
void cleanUpSound(){
  // Clean up sources and buffers
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
}
void playSound(){
  alSourcePlay(source);
}

bool shouldPlaySound = true;*/


string life="LIFE: ";
void draw_life()
{
	glRasterPos2i(-15, -12);
	//glColor3f( 0.0f, 0.0f, 1.0f);

	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < life.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)life[i]);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);

	for (int i = 0; i < nave->lives; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, sprites);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.666f);
		glVertex3d(-13.0f+i, -12.0f, 0);//dl
		glTexCoord2f(0.0f,1.0f);
		glVertex3d(-13.0f+i, -11.0f, 0);//ul
		glTexCoord2f(0.2f,1.0f);
		glVertex3d(-12.0f+i, -11.0f, 0);//ur
		glTexCoord2f(0.2f,0.666f);
		glVertex3d(-12.0f+i, -12.0f, 0);//dr
		glEnd();
	}
}

string score="SCORE: ";
void draw_score()
{
	stringstream ss;
	ss<<nave->total_score;
	glRasterPos2i(-7, -12);
	//glColor3f( 0.0f, 0.0f, 1.0f);

	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < score.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)score[i]);

	for (int i = 0; i < ss.str().size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)ss.str()[i]);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
}

string tm="TIME: ";
void draw_time()
{
	int t=timer/1000;

	stringstream minute;
	minute<<t/60;

	stringstream second;
	second<<t%60;

	glRasterPos2i(0, -12);
	//glColor3f( 0.0f, 0.0f, 1.0f);

	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < score.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)tm[i]);

	for (int i = 0; i < minute.str().size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)minute.str()[i]);

	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)':');

	if(t%60<10)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)'0');

	for (int i = 0; i < second.str().size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)second.str()[i]);	

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
}

void draw_grenade()
{
	if(nave->explode)
	{
		glBindTexture(GL_TEXTURE_2D, sprites);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3d(10.0f, -12.0f, 0);//dl
		glTexCoord2f(0.0f,1.0f);
		glVertex3d(10.0f, -11.0f, 0);//ul
		glTexCoord2f(1.0f,1.0f);
		glVertex3d(11.0f, -11.0f, 0);//ur
		glTexCoord2f(1.0f,0.0f);
		glVertex3d(11.0f, -12.0f, 0);//dr
		glEnd();
	}
}

bool t=true;

void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
	glEnable(GL_BLEND);//utilizar transparencia
	timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa

	/*if(shouldPlaySound){
    loadSound();
    playSound();
    shouldPlaySound = false;
  }else{
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if(state != AL_PLAYING){
      cleanUpSound();
    }
  }*/

    /*gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);

    if(t)
    {
    	glRotatef(30.0, 1.0, 0.0, 0.0);
    	//t=false;
    }


    glutSolidCube(8);*/

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3d(-16, -12, 0); //dl
	glTexCoord2f(0.0, 1.0f); //ul
	glVertex3d(-16, 12, 0);
	glTexCoord2f(1.0, 1.0f); //ur
	glVertex3d(16, 12, 0);
	glTexCoord2f(1.0, 0.0); //dr
	glVertex3d(16, -12, 0);
	glEnd();

	//if (iter == 5) iter = 0;
	nave->draw();
	
	//if(nave->ifShot())
	//	nave->shot.draw();

	for (int i = 0; i < num_enemigos; ++i)
	{
		enemigo[i]->draw();

		if(nave->shot.collision(enemigo[i]))
		{
			enemigo[i]->destroy();
			cout<<"Enemigo "<<i<<" destruido"<<endl;
			nave->win(enemigo[i]->score);
			cout<<"Puntaje: "<<nave->total_score<<endl;
		}

		cout<<"nave->collision(enemigo[i]): "<<nave->collision(enemigo[i])<<endl;
		if(nave->collision(enemigo[i]))
		{
			nave->destroy();
			cout<<"should be destroyed"<<endl;
		}
	}

	nave_malvada->draw();
	if(nave->shot.collisionShip(nave_malvada))
		nave->win(nave_malvada->score);

	for (int i = 0; i < num_bonos; ++i)
	{
		bono[i]->draw();

		if(nave->bonus_collision(bono[i]))
		{
			cout<<"Bono "<<i<<" cogido"<<endl;
			nave->win(bono[i]->score);
			cout<<"Puntaje: "<<nave->total_score<<endl;
		}
	}


	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, black);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);//coordenadas de textura
	glVertex3d(-16, -12, 0); //dl
	glTexCoord2f(0.0f, 1.0f); //ul
	glVertex3d(-16, -11, 0);
	glTexCoord2f(1.0f, 1.0f); //ur
	glVertex3d(16, -11, 0);
	glTexCoord2f(1.0f, 0.0f); //dr
	glVertex3d(16, -12, 0);
	glEnd();

	draw_life();
	draw_score();
	draw_time();
	draw_grenade();

	glutSwapBuffers();

}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	//glClearColor(0.4f, 0.4f, 0.4f, 0.2f); //(R, G, B, transparencia) en este caso un fondo negro
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//modo projeccion 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Get a handle for our "myTextureSampler" uniform
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / 50.0f, width / 50.0f, -height / 50.0f, height / 50.0f, -1.0f, 1.0f);

	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	case 'a':
		nave->shoot();
		cout<<"Disparo"<<endl;
		break;
	case 'd':
		if(!nave -> explode)
			break;
		for (int i = 0; i < num_enemigos; ++i)
		{
			if(enemigo[i]->destroy())
				nave->win(enemigo[i]->score);
		}
		nave -> explode=false;
		cout<<"Explosion"<<endl;
		cout<<"Puntaje: "<<nave->total_score<<endl;
		break;

	default:
		break;
	}

}

GLvoid window_arrow(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_RIGHT: //d
		if(nave->Right()<15)
			nave->go_right();
		cout<<"mueve derecha"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_LEFT: //f
		if(nave->Left()>-15)
			nave->go_left();
		cout<<"mueve izquiera"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_UP: //e
		if(nave->Up()<0)
			nave->go_up();
		cout<<"mueve arriba"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_DOWN: //g
		if(nave->Down()>-10)
			nave->go_down();
		cout<<"mueve abajo"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	default:
		break;
	}

}

//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}

int main(int argc, char** argv) 
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600); //tamaño de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("Milky Way"); //titulo de la ventana

	init_GL();


	texture = TextureManager::Inst()->LoadTexture("image/space1.jpg", GL_BGR_EXT, GL_RGB);
	sprites = TextureManager::Inst()->LoadTexture("image/nave.png", GL_BGRA_EXT, GL_RGBA);
	black = TextureManager::Inst()->LoadTexture("negro.png", GL_BGRA_EXT, GL_RGBA);
	grenade = TextureManager::Inst()->LoadTexture("image/grenade.png", GL_BGRA_EXT, GL_RGBA);

	nave=new Ship(2.0f,0.0f,-5.0f,3);

	//Rock roca(2);
	//enemigo=new Enemy(2.0f);
	enemigo=new Enemy*[num_enemigos];
	for (int i = 0; i < num_enemigos; ++i)
		enemigo[i]=new Enemy(1.0f,50);

	bono=new Bonus*[num_bonos];
	for (int i = 0; i < num_bonos; ++i)
		bono[i]=new Bonus(0.75f,25,rand()%2);

	nave_malvada=new EnemyShip(1.0f,100);
	
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	glutKeyboardFunc(&window_key);
	glutSpecialFunc(&window_arrow);
	glutIdleFunc(&window_idle);
	glutMainLoop(); //bucle de rendering

	return 0;
}

//g++ main.cpp -lGL -lGLU -lglut -lfreeimage

//g++ main.cpp -lopenal -lalut -lGL -lGLU -lglut -lfreeimage -lm
