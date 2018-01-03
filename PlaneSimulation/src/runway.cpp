/*
 * runway.cpp
 *	Draws a runway (as a square) and then stretches it out
 *  Created on: 30/05/2017
 *      Author: Jack Davenport
 */
#include "runway.h"

void run(void) {

	glBegin(GL_POLYGON);
	glVertex3f(1, 0.1, 1);
	glVertex3f(-1, 0.1, 1);
	glVertex3f(-1, 0.1, -1);
	glVertex3f(1, 0.1, -1);
	glEnd();

	glTranslatef(0, 0, -0.75);
	glutSolidCube(0.25);

	glTranslatef(0, 0, 0.5);
	glutSolidCube(0.25);

	glTranslatef(0, 0, 0.5);
	glutSolidCube(0.25);

	glTranslatef(0, 0, 0.5);
	glutSolidCube(0.25);
}
void runway::DrawModel() {
	glScalef(8, 1, -15);
	run();

}

