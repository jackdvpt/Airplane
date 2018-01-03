/* AirplaneSim.cpp
 *
 * Assignment 3 for COMP330 2017
 *
 * Plane does not do loopde loops
 *
 */

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "Hanger.h"
#include "officePark.h"
#include "Pond.h"
#include "rowHouse.h"
#include "runway.h"
#include "SOIL.h"
#include "UtilityStructs.h"

using namespace std;
#define X_RES 1281
#define Y_RES 720

#define PI 3.14159265
vector<BasicSceneObject*> SceneRoot;

struct PlaneExtra {
	float speed;
	float height;
	float fuel;
	float compas;
	float radar;
	float prop;
	float propSpeed;
};
typedef struct point2d {
	float x;
	float z;
} point2d;

struct viewPortSpecs {
	float x;
	float y;
	float w;
	float h;
};
static int menu_id;
bool drop = false;
bool landing = false;
bool startup = true;
bool circle = false;
bool takeoff = false;
GLfloat camX;
GLfloat camY;
GLfloat camZ;
int wingCamOffset = 6;
GLfloat top;
GLfloat bottom;
GLfloat leftSide;
GLfloat rightSide;

struct PlaneExtra extraInfo;
struct viewPortSpecs WingCam;
struct viewPortSpecs CockpitCam;
struct viewPortSpecs TowerCam;
struct viewPortSpecs MapCam;
struct viewPortSpecs swapTemp1;
struct viewPortSpecs swapTemp2;
//Vector3 camPos;
Vector3 camWingPos;
Vector3 camLook;
Vector3 potPos;
Vector3 potRPY;
Vector3 speed;
Vector3 rpySpeed;
Vector3 temp;
Vector3 xIn;
Vector3 xOut;
Vector3 lightPos;
Vector3 planeRotate;
bool land;
bool roll;
float yp;
float yl;
float zl;
float posGoalPcent = 0;
Vector3 posStart;
Vector3 posGoal;
int rotation = 145;
//variables for texturing;
#define MAX_NO_TEXTURES 1
GLuint texture[MAX_NO_TEXTURES];

void defaultPositions(void) {
	lightPos.x = 10;
	lightPos.y = 5;
	lightPos.z = 10;

	camX = 30;
	camY = 20;
	camZ = 30;

	top = 12;
	bottom = -12;
	leftSide = -55;
	rightSide = 55;

	camWingPos.x = -19;
	camWingPos.y = 1.75;
	camWingPos.z = 36;

	MapCam.x = 0;
	MapCam.y = Y_RES / 2;
	MapCam.w = X_RES;
	MapCam.h = Y_RES / 2;

	WingCam.x = 0;
	WingCam.y = 0;
	WingCam.w = 430;
	WingCam.h = Y_RES / 2;

	CockpitCam.x = 430;
	CockpitCam.y = 0;
	CockpitCam.w = 430;
	CockpitCam.h = Y_RES / 2;

	TowerCam.x = 860;
	TowerCam.y = 0;
	TowerCam.w = 430;
	TowerCam.h = Y_RES / 2;

	extraInfo.height = -90;
	extraInfo.speed = -90;
	extraInfo.fuel = -90;

	rpySpeed.z = 2;

	temp = Vector3(0, 0, 0);

	posGoal = Vector3(4, 0, 0);
	posStart = Vector3(0, 0, 0);

	xIn = Vector3(0, 0, 0);
	xOut = Vector3(0, 90, 0);
}
void createScene(void) {
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new officePark);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new rowHouse);
	SceneRoot.push_back(new Pond);
	SceneRoot.push_back(new rowHouse);

	SceneRoot.push_back(new runway);
	SceneRoot.push_back(new runway);

	SceneRoot.push_back(new Hanger);
	SceneRoot.push_back(new Hanger);
	SceneRoot.at(0)->colour = Colour4(0.77, 0.10, 0.23, 1);
	SceneRoot.at(0)->position = Vector3(0, 0, -15);
	SceneRoot.at(0)->lighting = true;

	SceneRoot.at(1)->colour = Colour4(0.11, 0.33, 0.53, 1);
	SceneRoot.at(1)->position = Vector3(0, 0, 0);
	SceneRoot.at(1)->rpy = Vector3(0, 0, 90);
	SceneRoot.at(1)->lighting = true;

	SceneRoot.at(2)->colour = Colour4(0.53, 0.51, 0.70, 1);
	SceneRoot.at(2)->position = Vector3(0, 0, -15);
	SceneRoot.at(2)->rpy = Vector3(0, 0, 90);
	SceneRoot.at(2)->lighting = true;

	SceneRoot.at(3)->colour = Colour4(0.15, 0.76, 0.39, 1);
	SceneRoot.at(3)->position = Vector3(0, 0, -30);
	SceneRoot.at(3)->lighting = true;

	SceneRoot.at(4)->position = Vector3(-15, 0, -15);
	SceneRoot.at(4)->lighting = true;

	SceneRoot.at(5)->colour = Colour4(0.76, 0.46, 0.13, 1);
	SceneRoot.at(5)->position = Vector3(13, 0, 0);
	SceneRoot.at(5)->rpy = Vector3(0, 0, 90);
	SceneRoot.at(5)->lighting = true;

	SceneRoot.at(6)->colour = Colour4(0.51, 0.86, 0.92, 1);
	SceneRoot.at(6)->position = Vector3(13, 0, -15);
	SceneRoot.at(6)->rpy = Vector3(0, 0, 90);
	SceneRoot.at(6)->lighting = true;

	SceneRoot.at(7)->colour = Colour4(0.22, 0.10, 0.30, 1);
	SceneRoot.at(7)->position = Vector3(0, 0, 0);
	SceneRoot.at(7)->lighting = true;

	SceneRoot.at(8)->colour = Colour4(0.04, 0.57, 0.05, 1);
	SceneRoot.at(8)->position = Vector3(15, 0, -15);
	SceneRoot.at(8)->rpy = Vector3(0, 0, 46);
	SceneRoot.at(8)->lighting = true;

	SceneRoot.at(9)->colour = Colour4(0.25, 0.71, 0.58, 1);
	SceneRoot.at(9)->position = Vector3(15, 0, -15);
	SceneRoot.at(9)->rpy = Vector3(0, 0, -46);
	SceneRoot.at(9)->lighting = true;

	SceneRoot.at(10)->colour = Colour4(0.25, 0.71, 0.58, 1);
	SceneRoot.at(10)->position = Vector3(26, 0, -26);
	SceneRoot.at(10)->rpy = Vector3(0, 0, -46);
	SceneRoot.at(10)->lighting = true;

	SceneRoot.at(11)->colour = Colour4(0.25, 0.71, 0.58, 1);
	SceneRoot.at(11)->position = Vector3(25, 0, -4);
	SceneRoot.at(11)->rpy = Vector3(0, 0, 46);
	SceneRoot.at(11)->lighting = true;

	SceneRoot.at(12)->colour = Colour4(0.25, 0.30, 0.88, 1);
	SceneRoot.at(12)->position = Vector3(-34, 0, 25);
	SceneRoot.at(12)->lighting = true;

	SceneRoot.at(13)->colour = Colour4(0.84, 0.52, 0.61, 1);
	SceneRoot.at(13)->position = Vector3(-15, 0, 0);
	SceneRoot.at(13)->lighting = true;

	SceneRoot.at(14)->colour = Colour4(0.40, 0.40, 0.40, 1);
	SceneRoot.at(14)->position = Vector3(-5, 0, 20);
	SceneRoot.at(14)->scale = Vector3(5, 1, 5);
	SceneRoot.at(14)->rpy = Vector3(0, 0, rotation);
	SceneRoot.at(14)->lighting = true;

	SceneRoot.at(15)->colour = Colour4(0.40, 0.40, 0.40, 1);
	SceneRoot.at(15)->position = Vector3(7.125, 0.01, 11.975);
	SceneRoot.at(15)->scale = Vector3(5, 1, 5);
	SceneRoot.at(15)->rpy = Vector3(0, 0, 264);
	SceneRoot.at(15)->lighting = true;

	SceneRoot.at(16)->colour = Colour4(0.57, 0.77, 0.66, 1);
	SceneRoot.at(16)->position = Vector3(29, 3, 18);
	SceneRoot.at(16)->rpy = Vector3(0, 0, -9);
	SceneRoot.at(16)->lighting = true;

	SceneRoot.at(17)->colour = Colour4(0.10, 0.53, 0.70, 1);
	SceneRoot.at(17)->position = Vector3(-18, 3, 40);
	SceneRoot.at(17)->rpy = Vector3(0, 0, -123);
	SceneRoot.at(17)->lighting = true;

}
//Taken from Tim Lambert's "textures" example project, 2013.
int loadGLTexture(const char *fileName)  // Load Bitmaps And Convert To Textures
		{
	string name = "textures/";
	name += fileName;
	/* load an image file from texture directory as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture(name.c_str(), SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (texture[0] == 0) {
		std::cerr << fileName << " : " << SOIL_last_result();
		return false;
	}

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return true;                                    // Return Success
}
void init(void) {
	/* Skybox textures from :
	 * https://opengameart.org/content/sky-box-sunny-day
	 * 	used under creative commons
	 */

	//Load in textures
	loadGLTexture("skybox/Daylight Box_Front.bmp"); //1
	loadGLTexture("skybox/Daylight Box_Back.bmp");	//2
	loadGLTexture("skybox/Daylight Box_Left.bmp");	//3
	loadGLTexture("skybox/Daylight Box_Right.bmp"); //4
	loadGLTexture("skybox/Daylight Box_Top.bmp");	//5
	loadGLTexture("skybox/Daylight Box_Bottom.bmp");	//6
	loadGLTexture("spedometer1.png"); //7
	loadGLTexture("wall.png"); //8
	loadGLTexture("petrol.png"); //9
	loadGLTexture("comp.png"); //10
	loadGLTexture("radar.png"); //11
	loadGLTexture("WelcomeScreen.png"); //12
	loadGLTexture("WelcomeScreen1.png"); //13
	defaultPositions();
	createScene();

	//set BG and FG colour
	glClearColor(0, 0, 1, 0);

	glEnable( GL_DEPTH_TEST);
	//setting up the models
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//setup the depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);	// Enable lighting calculations
	glEnable(GL_LIGHT0);	// Turn on light #0.
}

void drawSkyBox(float mainCamX, float mainCamY, float mainCamZ, int rotate,
		int scale) {

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);
	//Front
	glPushMatrix();
	glTranslatef(mainCamX, mainCamY, mainCamZ - scale);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-scale, -scale, 0);
	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(scale, -scale, 0);
	glTexCoord2f(0, 1);	//top left of front
	glVertex3f(-scale, scale, 0);
	glTexCoord2f(1, 1);	//top right of front
	glVertex3f(scale, scale, 0);
	glEnd();
	glPopMatrix();

	//Back
	glBindTexture(GL_TEXTURE_2D, 2);
	glPushMatrix();

	glTranslatef(mainCamX, mainCamY, mainCamZ + scale);
	glRotatef(180, 0, 0, 1);
	glRotatef(180, 1, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of back
	glVertex3f(-scale, -scale, 0);
	glTexCoord2f(1, 0);	//bottom right of back
	glVertex3f(scale, -scale, 0);
	glTexCoord2f(0, 1);	//top left of back
	glVertex3f(-scale, scale, 0);
	glTexCoord2f(1, 1);	//top right of back
	glVertex3f(scale, scale, 0);
	glEnd();
	glPopMatrix();

	//left
	glBindTexture(GL_TEXTURE_2D, 3);
	glPushMatrix();
	glTranslatef(mainCamX - scale, mainCamY, mainCamZ);
	glRotatef(90, 0, 1, 0);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-scale, -scale, 0);
	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(scale, -scale, 0);
	glTexCoord2f(0, 1);	//top left of left
	glVertex3f(-scale, scale, 0);
	glTexCoord2f(1, 1);	//top right of left
	glVertex3f(scale, scale, 0);
	glEnd();
	glPopMatrix();

	//right
	glBindTexture(GL_TEXTURE_2D, 4);
	glPushMatrix();
	glTranslatef(mainCamX + scale, mainCamY, mainCamZ);
	glRotatef(90, 0, 1, 0);
	glScalef(-1, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of right
	glVertex3f(-scale, -scale, 0);
	glTexCoord2f(1, 0);	//bottom right of right
	glVertex3f(scale, -scale, 0);
	glTexCoord2f(0, 1);	//top left of right
	glVertex3f(-scale, scale, 0);
	glTexCoord2f(1, 1);	//top right of right
	glVertex3f(scale, scale, 0);
	glEnd();
	glPopMatrix();

	//top
	glBindTexture(GL_TEXTURE_2D, 5);
	glPushMatrix();
	glTranslatef(mainCamX, mainCamY + scale, mainCamZ);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of top
	glVertex3f(-scale, -scale, 0);
	glTexCoord2f(1, 0);	//bottom right of top
	glVertex3f(scale, -scale, 0);
	glTexCoord2f(0, 1);	//top left of top
	glVertex3f(-scale, scale, 0);
	glTexCoord2f(1, 1);	//top right of top
	glVertex3f(scale, scale, 0);
	glEnd();
	glPopMatrix();

	//bottom

	glBindTexture(GL_TEXTURE_2D, 6);
	glPushMatrix();
	glTranslatef(mainCamX, mainCamY - scale, mainCamZ);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of bottom
	glVertex3f(-scale, -scale, 0);
	glTexCoord2f(1, 0);	//bottom right of bottom
	glVertex3f(scale, -scale, 0);
	glTexCoord2f(0, 1);	//top left of bottom
	glVertex3f(-scale, scale, 0);
	glTexCoord2f(1, 1);	//top right of bottom
	glVertex3f(scale, scale, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
void lights(void) {
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	GLfloat light_position[] = { 5, 0, 5, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void setupWingView(int ratio) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio == 1) {
		gluPerspective(90, ratio, 0.1, 100);
	} else {
		gluPerspective(70, ratio, 0.1, 100);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (ratio > 1) {
		wingCamOffset = 7;
	}
	gluLookAt(camWingPos.x + wingCamOffset, camWingPos.y + 2, camWingPos.z + 2,
			camWingPos.x - 2, camWingPos.y, camWingPos.z - 2, 0, 1, 0);
	glRotatef(-potRPY.z, 0, 1, 0);

}

void setupTopView(int ratio) {

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, 1);
	if (ratio > 1) {
		glOrtho(-25, 25, -25, 25, 1, 30);
	} else {
		glOrtho(-55, 55, leftSide, rightSide, 0.01, 30);
	}
	glMatrixMode(GL_MODELVIEW);

	gluLookAt(0, 0, 0, camLook.x, camLook.y, camLook.z, 0, 1, 0);
	glLoadIdentity();

}

void setupFrontView(int ratio) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio == 1) {
		gluPerspective(90, ratio, 0.001, 100);
	} else {
		gluPerspective(90, ratio, 0.001, 100);
	}

	glMatrixMode(GL_MODELVIEW);
	glRotatef(260, 0, 1, 0);
	gluLookAt(camWingPos.x + 1.9, camWingPos.y + yp, camWingPos.z - 3.1,
			camWingPos.x + 7.5, camWingPos.y + yl, camWingPos.z + 3 + zl, 0, 1,
			0);
	glRotatef(-potRPY.z, 0, 1, 0);
}

void setupSideView(int ratio) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float top = camLook.y;
	if (ratio == 1) {
		gluPerspective(90, ratio, 0.1, 100);
	} else {
		gluPerspective(60, ratio, 0.1, 100);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, camLook.x, top, camLook.z, 0, 1, 0);
	glPushMatrix();
	glPopMatrix();

}
void drawRoom() {
	GLfloat floorMat[] = { 0.2, 0.5, 0.4, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorMat);
	int size = 55;
	point2d corners[] = { { -size, -size }, { size, -size }, { size, size }, {
			-size, size } };
	int nCorners = sizeof(corners) / sizeof(corners[0]);
	//draw floor;
	glNormal3f(0, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < nCorners; i++) {
		glVertex3f(corners[i].x, 0, corners[i].z);
	}
	glEnd();
}

void lightObjectInit() {
	glEnable(GL_LIGHTING);	// Enable lighting calculations
	glEnable(GL_LIGHT0);	// Turn on light #0.
	GLfloat sphereAmbient[4] = { 1, 0, 1, 1 };
	GLfloat specular[4] = { 1, 0, 0, 1 };
	GLfloat shininess = 50;
	//glColor3f(1, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphereAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void instruments(void) {
	glPushMatrix();
	GLfloat setupMainView2[4] = { 0.5, 0.5, 0.5, 1 };
	GLfloat specular2[4] = { 0, 0, 1, 1 };
	GLfloat shininess2 = 50;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, setupMainView2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);
	glTranslatef(4, 2, 2);
	glRotatef(2, 0, 0, 1);
	glRotatef(extraInfo.height, 0, 0, 1);
	glScalef(0.25, 1.5, 0.25);
	glTranslatef(0, 0.5, 0);

	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 7);
	glPushMatrix();

	glTranslatef(4, 2, 2);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-2, -2, 0);

	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(2, -2, 0);

	glTexCoord2f(0, 1);	//top left of front
	glVertex3f(-2, 2, 0);
	glTexCoord2f(1, 1);	//top right of front
	glVertex3f(2, 2, 0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(8, 2, 2);
	glRotatef(2, 0, 0, 1);
	glRotatef(extraInfo.speed, 0, 0, 1);
	glScalef(0.25, 1.5, 0.25);
	glTranslatef(0, 0.5, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 7);
	glPushMatrix();
	glTranslatef(8, 2, 2);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-2, -2, 0);

	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(2, -2, 0);

	glTexCoord2f(0, 1);	//top left of front
	glVertex3f(-2, 2, 0);
	glTexCoord2f(1, 1);	//top right of front
	glVertex3f(2, 2, 0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(12, 2, 2);
	glRotatef(2, 0, 0, 1);
	glRotatef(extraInfo.fuel, 0, 0, 1);
	glScalef(0.25, 1.5, 0.25);
	glTranslatef(0, 0.5, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 9);
	glPushMatrix();
	glTranslatef(12, 2, 2);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-2, -2, 0);

	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(2, -2, 0);

	glTexCoord2f(0, 1);	//top left of front
	glVertex3f(-2, 2, 0);
	glTexCoord2f(1, 1);	//top right of front
	glVertex3f(2, 2, 0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 2, 2);
	glRotatef(2, 0, 0, 1);

	glScalef(0.25, 1.5, 0.25);
	glTranslatef(0, 0.5, 0);
	//glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 10);
	glPushMatrix();
	glTranslatef(16, 2, 2);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-2, -2, 0);

	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(2, -2, 0);

	glTexCoord2f(0, 1);	//top left of front
	glVertex3f(-2, 2, 0);
	glTexCoord2f(1, 1);	//top right of front
	glVertex3f(2, 2, 0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 2, 2);
	glRotatef(2, 0, 0, 1);

	glScalef(0.25, 1.5, 0.25);
	glTranslatef(0, 0.5, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 11);
	glPushMatrix();
	glTranslatef(20, 2, 2);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-2, -2, 0);

	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(2, -2, 0);

	glTexCoord2f(0, 1);	//top left of front
	glVertex3f(-2, 2, 0);
	glTexCoord2f(1, 1);	//top right of front
	glVertex3f(2, 2, 0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void airPlane(void) {
	lightObjectInit();

	glRotatef(rotation, 0, 1, 0);
	glRotatef(planeRotate.x, 1, 0, 0);
	glRotatef(potRPY.y, 0, 0, 1);
	glPushMatrix();
	GLfloat mat1[] = { 0.18, 0.16, 0.16, 1.0 };

	GLfloat col[4] = { .75, .75, .75, 0.75 };
	GLfloat specular[4] = { 1, 1, 1, 1 };
	GLfloat shininess = 50;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat1);
	glBegin(GL_POLYGON);
	GLUquadricObj *obj = gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	gluCylinder(obj, 1.25, 1.25, 6, 30, 30);

	glEnd();
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat1);
	glTranslatef(3.75, 0, 2);
	glScalef(5.0f, 0.5f, 2.0f);
	glutSolidCube(1);
	glPushMatrix();
	glTranslatef(-1.5, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glTranslatef(0, 0, 4);

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat1);
	glRotatef(45, 1, 0, 0);
	//glRotatef(hats, 1, 0, 0);

	glTranslatef(-1.2, 0, 0.8);
	glScalef(0.1, 0.1, 0.1);
	instruments();
	glPopMatrix();
	glBegin(GL_POLYGON);
	GLUquadricObj *obj1 = gluNewQuadric();

	gluCylinder(obj1, 1.25, 2, 1.5, 30, 30);

	glEnd();
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat1);
	glTranslatef(3.5, 0, -0.9);
	glRotatef(extraInfo.prop, 0, 0, 1);

	glScalef(0.5, 3, 0.25);
	//glColor3f(1, 1, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.5, 0, -0.9);
	glRotatef(extraInfo.prop, 0, 0, 1);
	glRotatef(90, 0, 0, 1);
	glScalef(0.5, 3, 0.25);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.5, 0, -0.75);
	glRotatef(-extraInfo.prop, 0, 0, 1);

	glScalef(0.5, 3, 0.25);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 0, -0.75);
	glRotatef(-extraInfo.prop, 0, 0, 1);
	glRotatef(90, 0, 0, 1);
	glScalef(0.5, 3, 0.25);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}
void drawScene() {
	glPushMatrix();

	glTranslatef(29, 4, 18);
	glRotatef(-9, 0, 1, 0);
	glPopMatrix();
	glPushMatrix();

	glPushMatrix();

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, -8, 0);

	drawSkyBox(10, 10, 10, 0, 30);
	glPopMatrix();

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);

	glRotatef(potRPY.z, 0, 1, 0);
	glTranslatef(camWingPos.x, camWingPos.y, camWingPos.z);

	glPushMatrix();

	glPopMatrix();
	airPlane();
	glPopMatrix();

	drawRoom();
	for (unsigned int i = 0; i < SceneRoot.size(); i++) {
		SceneRoot.at(i)->Display();
	}
}
void startCam(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, 1.7777777, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 1, 10, 0,
			1, 0, 0, 1, 0);
}
void drawTitle(void) {
	glPushMatrix();

	glTranslatef(0, -8, 0);

	drawSkyBox(10, 10, 10, 0, 30);
	glPopMatrix();

	glTranslatef(0, 1, 2.6);
	glRotatef(-rotation, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	airPlane();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 12);
	glPushMatrix();

	glTranslatef(4, 2, 2);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-2, -2, 0);

	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(2, -2, 0);

	glTexCoord2f(0, 1);	//top left of front
	glVertex3f(-2, 2, 0);
	glTexCoord2f(1, 1);	//top right of front
	glVertex3f(2, 2, 0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9, 3, 0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 13);
	glPushMatrix();

	glTranslatef(4, 2, 2);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);	//bottom left of front
	glVertex3f(-2, -2, 0);

	glTexCoord2f(1, 0);	//bottom right of front
	glVertex3f(2, -2, 0);

	glTexCoord2f(0, 1);	//top left of front
	glVertex3f(-2, 2, 0);
	glTexCoord2f(1, 1);	//top right of front
	glVertex3f(2, 2, 0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void display(void) {
	if (startup) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, X_RES, Y_RES);
		startCam();
		drawTitle();
	} else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the screen
		glTranslatef(0, 10, 0);
		glViewport(WingCam.x, WingCam.y, WingCam.w, WingCam.h);
		setupWingView(WingCam.w / WingCam.h);
		drawScene();

		glViewport(MapCam.x, MapCam.y, MapCam.w, MapCam.h);
		setupTopView(MapCam.w / (MapCam.h));
		glPushMatrix();
		drawScene();
		glPopMatrix();

		glViewport(CockpitCam.x, CockpitCam.y, CockpitCam.w, CockpitCam.h);
		setupFrontView(CockpitCam.w / CockpitCam.h);
		drawScene();

		glViewport(TowerCam.x, TowerCam.y, TowerCam.w, TowerCam.h);
		setupSideView(TowerCam.w / TowerCam.h);
		drawScene();
	}
	float lp[] = { lightPos.x, lightPos.y, lightPos.z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lp);

	glEnable(GL_LIGHTING);               // Enable lighting calculations
	glEnable(GL_LIGHT0);                            // Turn on light #0.
	//OpenGL house cleaning
	glFlush(); //put everything on the pipeline
	glutPostRedisplay(); //post the ready scenes.
	glutSwapBuffers(); //swap the buffers

}

void animateScene() {
	extraInfo.prop += extraInfo.propSpeed;
	if (takeoff) {
		if (camWingPos.x <= 7) {
			camWingPos.x += 0.125;
			camWingPos.z -= 0.125;
			extraInfo.speed += 1;
			if ((camWingPos.z > 4) && (camWingPos.z < 14)) {
				extraInfo.height += 2.5;
				camWingPos.y += 0.2;
				planeRotate.x -= 0.25;
				yp += 0.025;
				yl += 0.025;
			}
			extraInfo.propSpeed += 0.2;
		} else {
			circle = true;
			if (camWingPos.z > 7) {
				camWingPos.z -= 0.1;
			}
		}
	}
	if (circle) {
		if (planeRotate.x < -2) {
			planeRotate.x += 0.25;
			yp -= 0.025;
			yl -= 0.025;
		}
		takeoff = false;
		potRPY += rpySpeed;
		posGoalPcent += 0.001;
		extraInfo.fuel += 0.1;
	}
	if (extraInfo.fuel > 120) {
		circle = false;
		rpySpeed = Vector3(0, 0, 0);
		extraInfo.fuel = 120;
		if (extraInfo.propSpeed > 0) {
			extraInfo.propSpeed -= 1;
		}
		if (camWingPos.y > 1.9) {
			camWingPos.y -= 0.15;
		}
		if (extraInfo.height > -90) {
			extraInfo.height -= 2.5;
		}
		if (extraInfo.speed > -90) {
			extraInfo.speed -= 19;
		}
	}
	if (roll) {
		if ((!takeoff) && (!land) && (!landing) && (circle)) {
			if (potRPY.y < 360) {
				potRPY.y += 2;

			} else {
				potRPY.y = 0;
				roll = false;
			}
		} else {
			roll = false;
		}
	}
	if (land) {
		if ((int) potRPY.z % 360 == 190) {
			landing = true;
		}
	}
	if (landing) {
		if (camWingPos.y > 1.9) {
			camWingPos.y -= 0.15;
			extraInfo.height -= 2.5;
			extraInfo.speed -= 1.5;
		}
		if (extraInfo.propSpeed >= 0) {
			extraInfo.propSpeed -= 0.2;
		} else {
			if (camWingPos.x < 28) {
				camWingPos.x += 0.15;
			}
			if (camWingPos.z > -14) {
				camWingPos.z -= 0.15;
			}
		}
		if ((int) potRPY.z % 360 > 300) {
			potRPY.z = 300;
			if (camWingPos.x < 18) {
				camWingPos.x += 0.15;
			}
			if (camWingPos.z > -4) {
				camWingPos.z -= 0.15;

			}
			if (extraInfo.speed > -90) {
				extraInfo.speed -= 1.5;
			}

		}

	}
}

void animateSceneTimer(int milis) {
	animateScene();
	glutTimerFunc(milis, animateSceneTimer, milis);
}

void keyboard(unsigned char key, int x, int y) {
	if (key == '2') {
		roll = true;
	}
	if (key == '4') {
		land = true;
	}
	if (key == '1') {
		takeoff = true;
	}
	if ((int) key == 27) {
		exit(0);
	}
	if ((int) key == 9) {
		swapTemp1 = CockpitCam;
		CockpitCam = WingCam;
		WingCam = MapCam;
		swapTemp2 = TowerCam;
		TowerCam = swapTemp1;
		MapCam = swapTemp2;
	}
	startup = false;
	rotation = 145;
}
void menu(int num) {
	if (num == 0) {
		exit(0);
	}

	if (num == 2) {
		roll = true;
	}
	if (num == 4) {
		land = true;
	}
	if (num == 1) {
		takeoff = true;
	}

	if (num == 9) {
		swapTemp1 = CockpitCam;
		CockpitCam = WingCam;
		WingCam = MapCam;
		swapTemp2 = TowerCam;
		TowerCam = swapTemp1;
		MapCam = swapTemp2;
	}
}
void createMenu(void) {
	menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Takeoff       | 1", 1);
	glutAddMenuEntry("Corkscrew     | 2", 2);
	glutAddMenuEntry("Land          | 4", 4);
	glutAddMenuEntry("Swap Camera   | tab", 9);
	glutAddMenuEntry("Quit          | esc", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitWindowSize(X_RES, Y_RES);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Airplane Fly");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	createMenu();
	init();
	animateSceneTimer(50);
	glutMainLoop();

	return 0;
}

