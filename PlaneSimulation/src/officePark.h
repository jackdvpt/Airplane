#include "BasicSceneObject.h"

#ifndef SPACECRATE_H_
#define SPACECRATE_H_
class officePark: public BasicSceneObject
{
	public:
	officePark();

		float subCubeSize;
		float subCubeSep;

	private:
		virtual void DrawModel();
};




#endif /* SPACECRATE_H_ */
