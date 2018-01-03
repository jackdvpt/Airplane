/*
 * pond.cpp
 *		Draws a lovely pond, and some ducks
 *  Created on: 30/05/2017
 *      Author: Jack Davenport
 */
#include "Pond.h"
void drawDuck() {
	glPushMatrix();
	GLfloat setupMainView[4] = { 0.96, 0.92, 0.26, 1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, setupMainView);

	glutSolidCube(0.5);
	glPopMatrix();
}
void Pond::DrawModel() {

	glBegin(GL_TRIANGLE_FAN);
	//glNormal3f(0, 0, 1);
	glVertex3f(0, 0.1, 0);
	glVertex3f(0, 0.1, 15);
	glVertex3f(10, 0.1, 10);
	glVertex3f(15, 0.1, 0);
	glVertex3f(10, 0.1, -10);
	glVertex3f(0, 0.1, -15);
	glVertex3f(-10, 0.1, -10);
	glVertex3f(-15, 0.1, 0);
	glVertex3f(-10, 0.1, 10);
	glVertex3f(0, 0.1, 15);
	glEnd();
	//Draw some ducks
	glPushMatrix();
	glTranslatef(3, 0, 3);
	drawDuck();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	drawDuck();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-7, 0, 6);
	drawDuck();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(8, 0, -2);
	drawDuck();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 0, -8);
	drawDuck();
	glPopMatrix();
}

