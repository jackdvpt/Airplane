#include "UtilityStructs.h"
#include <iostream>
#include <GL/glut.h>
#include <vector>
using namespace std;

#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

class BasicSceneObject {
public:
	//default constructor
	BasicSceneObject();

	BasicSceneObject(Vector3 pos, Vector3 speed, Vector3 scale, Vector3 ypr,
			Vector3 yprSpeed, Vector3 rgb);

	//the function to update the object's attributes.
	virtual void Update();

	//display the damn thing
	virtual void Display();

	//display stuff to console
	virtual void DisplayToConsole();

	Vector3 position;
	Vector3 speed;
	Vector3 scale;
	Vector3 rpy; //yaw pitch and roll
	Vector3 rpySpeed; //yaw pitch roll speed
	Colour4 colour; //red green blue.
	bool lighting;
	bool displayActive;
	bool active;

protected:

	virtual void DrawModel();

};

#endif /* SCENEOBJECT_H_ */
