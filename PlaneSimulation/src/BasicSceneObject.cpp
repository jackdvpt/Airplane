
#include "BasicSceneObject.h"//** You NEED this to refer back to the header file.
#include <iostream>

BasicSceneObject::BasicSceneObject()
{
	active = true;
	displayActive = true;
	lighting = true;

	position = Vector3();
	speed = Vector3();
	scale = Vector3(1,1,1);
	rpy = Vector3();//yaw pitch and roll
	rpySpeed = Vector3();//yaw pitch roll speed
	//rgb = Vector3();//red green blue.
	colour.r = 1;
	colour.g = 1;
	colour.b = 1;
	colour.a = 1;
}

//Updating the logic in the scene object is simply
//adding its delta values to its current values.
//That is, add the speed vector to its position and
//add its roll/pitch/yaw speed values to its current
//yaw/pitch/roll.
void BasicSceneObject::Update()
{
	//position += speed;
	//rpy += rpySpeed;

}

void BasicSceneObject::DisplayToConsole()
{
	cout<<rpy.x<<","<<rpy.y<<","<<rpy.z<<","<<endl;
}

void BasicSceneObject::Display()
{
	if(!lighting)
	{
		glColor3f(colour.r,colour.g,colour.b);
	}
	else
	{	GLfloat setupMainView[4] = { colour.r,colour.g,colour.b, colour.a};
		GLfloat specular[4] = { 1, 1, 1, 1};
		GLfloat shininess = 50;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, setupMainView);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular );
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}

	glPushMatrix();

		glTranslatef(position.x,position.y,position.z);
		glRotatef(rpy.z,0,1,0);//yaw
		glRotatef(rpy.y,0,0,1);//pitch
		glRotatef(rpy.x,1,0,0);//roll
		//glScalef(scale.x,scale.y,scale.z);

		DrawModel();

	glPopMatrix();
}

void BasicSceneObject::DrawModel()
{
	glutSolidCube(3);
	glutSolidSphere(2,20,20);
}




