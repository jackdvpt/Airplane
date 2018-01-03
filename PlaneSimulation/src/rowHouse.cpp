/*
 * QuadCube.cpp
 *	Draws a row of houses
 *  Created on: 30/05/2017
 *      Author: Jack Davenport
 */

#include "rowHouse.h"

void house() {
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(1, 0, 0);			// Top Right Of The Quad (Front)
	glVertex3f(1, 1, 0);			// Top Right Of The Quad (Front)
	glVertex3f(0.5, 1.5, 0);			// Top Right Of The Quad (Front)
	glVertex3f(0, 1, 0);			// Top Right Of The Quad (Front)
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0.5, 1.5, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(0.5, 1.5, 1);
	glVertex3f(0.5, 1.5, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-1, -1, 0);
	glVertex3f(0.5, 1.5, 1);
	glVertex3f(0.5, 1.5, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(0.5, 1.5, 1);
	glEnd();
}
void rowHouse::DrawModel() {
	//glTranslatef(1, 0,0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();
	glTranslatef(1.25, 0, 0);
	house();

}

