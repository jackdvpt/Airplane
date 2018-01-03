/*
 * Hanger.cpp
 * Draws a airplane hanger for the plane to start and end in
 * Created on: 30/05/2017
 * Author: Jack Davenport
 */
#include "Hanger.h"

void Hanger::DrawModel() {
	glPushMatrix();
	glTranslatef(0,4,0);
	glScalef(1,0.1,1);
	glutSolidCube(15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,-3,0);
	glRotatef(90,0,0,1);
	glScalef(1,0.1,1);
	glutSolidCube(15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-3,-7.5);
	glRotatef(90,1,0,0);
	glScalef(1,0.1,1);
	glutSolidCube(15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-3,7.5);
	glRotatef(90,1,0,0);
	glScalef(1,0.1,1);
	glutSolidCube(15);
	glPopMatrix();
}


