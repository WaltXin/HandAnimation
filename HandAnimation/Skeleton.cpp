#include "Skeleton.h"
#include <cylinder.h>
//Cylinder cy;

//#include <Bone.h>
//Hand hand; 

//Cylinder cy;

Skeleton::Skeleton() // Build the Bone tree set the Parent ID(pid) and Child ID(cid) and add into the vector list
{
	Bone handBone = Bone(1,"roots",0);
	bonevec.push_back(handBone);

	handBone = Bone(2,"A3",1);
	handBone.bone_init_x = 0; // initial the A3 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(3,"B3",1);
	handBone.bone_init_x = 0; // initial the B3 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(4,"C3",1);
	handBone.bone_init_x = 0; // initial the C3 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(5,"D3",1);
	handBone.bone_init_x = 0; // initial the D3 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(6,"E2",1);
	handBone.bone_init_x = 0; // initial the E2 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(7,"A2",2);
	handBone.bone_init_x = 0; // initial the A2 position    second lawer 
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(8,"B2",3);
	handBone.bone_init_x = 0; // initial the B2 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(9,"C2",4);
	handBone.bone_init_x = 0; // initial the C2 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(10,"D2",5);
	handBone.bone_init_x = 0; // initial the D2 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(11,"E1",6);
	handBone.bone_init_x = 0; // initial the E1 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(12,"A1",7);
	handBone.bone_init_x = 0; // initial the A1 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(13,"B1",8);
	handBone.bone_init_x = 0; // initial the B1 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(14,"C1",9);
	handBone.bone_init_x = 0; // initial the C1 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);

	handBone = Bone(15,"D1",10);
	handBone.bone_init_x = 0; // initial the D1 position
	handBone.bone_init_y = 1;
	handBone.bone_init_z = 1;
	bonevec.push_back(handBone);


}

bone_vector::iterator Skeleton::get_bone_by_name(char *name) // function: get the bone by name 
{
	bone_vector::iterator theIterator;
	bone_vector::iterator theIterator2;
	//theIterator2 = 0;
	for(theIterator=bonevec.begin();theIterator!=bonevec.end();theIterator++)
	{
		if(0==strncmp(theIterator->name,name,4))
		{
			theIterator2=theIterator;
			break; 
		}
	}
	return theIterator2;    //theIterator 2
	
}



Bone* Skeleton::get_bone_by_ID(int ID)
{
	return (&bonevec[ID-1]);
}



