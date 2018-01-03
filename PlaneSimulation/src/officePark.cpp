#include "officePark.h"

officePark::officePark() {
	subCubeSep = 0.75;
	subCubeSize = 0.35;
	BasicSceneObject();
}

void build(void) {
	float scale = 1;
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 8);
	glPushMatrix();
	glTranslatef(0, 0, 0 - scale);
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

	glBindTexture(GL_TEXTURE_2D, 8);
	glPushMatrix();

	glTranslatef(0, 0, scale);

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
	//glRotatef(rotate, 0, 1, 0);
	glEnd();
	glPopMatrix();

	//left
	glBindTexture(GL_TEXTURE_2D, 8);
	glPushMatrix();
	//glRotatef(rotate, 0, 1, 0);
	glTranslatef(-scale, 0, 0);
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
	glBindTexture(GL_TEXTURE_2D, 8);
	glPushMatrix();
	//glRotatef(rotate, 0, 1, 0);
	glTranslatef(scale, 0, 0);
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
	glBindTexture(GL_TEXTURE_2D, 8);
	glPushMatrix();

	glTranslatef(0, scale, 0);

	glRotatef(90, 1, 0, 0);
	//glRotatef(rotate, 0, 1, 0);
	//glScalef(-1,1,1);
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
	glDisable(GL_TEXTURE_2D);
}

void building(float size) {
	glPushMatrix();
	glScalef(1.75, size-2, 1.75);
	build();
	glPopMatrix();
}

void officePark::DrawModel() {

	building(8);
	glTranslatef(-7, 0, -7);
	building(15);
	glTranslatef(9, 0, 12);
	building(9);
	glTranslatef(0, 0, -10);
	building(16);
	glTranslatef(-17, 0, 4);
	building(12);
	glTranslatef(-7, 0, 1);
	building(19);
	glTranslatef(8, 0, 15);
			building(10);
	glTranslatef(-6, 0, 7);
		building(14);
}

