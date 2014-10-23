#include <Bone.h>
#include <glew.h>
#include <iostream>
#include <string>
#include <list>

/*GLuint ID;
//std::string Name;
std::list<std::string> childList;
std::list<std::string> parentList;
*/

Bone::Bone(int ID,char *name,int PID) // constructor
{
	this->ID = ID;
	strcpy_s(this->name,name);
	this->PID = PID;
}

Bone::Bone()
{

}

