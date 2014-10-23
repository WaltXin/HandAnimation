#pragma once

#include <Bone.h>
#include <string>
#include <vector>

typedef std::vector<Bone> bone_vector;

class Skeleton
{
private:
	bone_vector bonevec;
public:
	Skeleton();
	int ID;
	Bone* get_bone_by_ID(int ID);
	bone_vector::iterator get_bone_by_name(char *name);
	float CalculatePosition();

};

