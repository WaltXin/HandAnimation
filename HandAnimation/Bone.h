#include<string>
class Bone
{
public:
	Bone();
	Bone(int ID,char *name,int PID);
	int y;
	int x;
	int r_z;
	int r_y;
	int r_x;
	int rotated_X;
	int rotated_Y;
	int is_marked;
	float start_arc_x,end_arc_x;
	float start_arc_y,end_arc_y;
	float start_arc_z,end_arc_z;
	double LengthRatio;
	float bone_init_x,bone_init_y,bone_init_z;

	char name[80];
	int ID;
	int PID;
	int CID;

private:

};
