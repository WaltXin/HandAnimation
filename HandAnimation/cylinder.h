#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include<glm/glm.hpp>
#include "maths_funcs.h"
#include <Glew.h>
#include <vector>
using namespace std;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class Cylinder {
public:
	Cylinder(){
		
	};

	Cylinder(const float height, const float radiusTop, const float radiusBottom, const glm::vec4& colorTop, const glm::vec4& colorBottom, const int segments = 16) 
	{
		generateVertices(height, radiusTop, radiusBottom, colorTop, colorBottom, segments);
		
	};

	void initcy()
	{
		VA3 =glm::vec3(4*sin(15.0)*sin(15.0)/cos(15.0),0,4*sin(15.0)-6);
		VA2 =glm::vec3(2.5 * cos((90.0)*3.14 / 180), 2.5 * sin((90.0)*3.14 / 180), 0);
		VA1 =glm::vec3(3 * cos((90.0)*3.14 / 180), 3 * sin((90.0)*3.14 / 180), 0);
		VB3 =glm::vec3(2*sin(15.0)*sin(15.0)/cos(15.0),0,4*sin(15.0)-6);
		VB2 =glm::vec3(1.25 * cos((90.0)*3.14 / 180), 2.5 * sin((90.0)*3.14 / 180), 0);
		VB1 =glm::vec3(1.5 * cos((90.0)*3.14 / 180), 3 * sin((90.0)*3.14 / 180), 0);
		VC3 =glm::vec3(0.1*sin(15.0)*sin(15.0)/cos(15.0),0,4*sin(15.0)-6);
		VC2 =glm::vec3(0.08 * cos((90.0)*3.14 / 180), 2.5 * sin((90.0)*3.14 / 180), 0);
		VC1 =glm::vec3(0.1 * cos((90.0)*3.14 / 180), 3 * sin((90.0)*3.14 / 180), 0);
		VD3 =glm::vec3(-2*sin(15.0)*sin(15.0)/cos(15.0),0,4*sin(15.0)-6);
		VD2 =glm::vec3(-1.25 * cos((90.0)*3.14 / 180), 2.5 * sin((90.0)*3.14 / 180), 0);
		VD1 =glm::vec3(-1.5 * cos((90.0)*3.14 / 180), 3 * sin((90.0)*3.14 / 180), 0);
		VE2 =glm::vec3(-6*sin(15.0)*sin(15.0)/cos(15.0),0,4*sin(15.0)-3);
		VE1 =glm::vec3(-3 * cos((90.0)*3.14 / 180), 2.5 * sin((90.0)*3.14 / 180), 0);
	}

	// generate a cylinder with the bottom base center at (0,0,0), up on the Y axis
	void generateVertices(const float height, const float radiusTop, const float radiusBottom, const glm::vec4& colorTop, const glm::vec4& colorBottom, const int segments = 16)
	{
		vertex_positions.empty();
		vertex_colors.empty();
		nbSegments = segments;

		double angle = 0.0;
		vertex_positions.push_back(glm::vec4(0,height,0,1));
		vertex_colors.push_back(colorTop);
		for(unsigned int i = 0; i<nbSegments; ++i)
		{
			angle = ((double)i)/((double)nbSegments)*2.0*3.14;
			vertex_positions.push_back(glm::vec4(radiusTop*std::cos(angle),height,radiusTop*std::sin(angle),1.0));
			vertex_colors.push_back(colorTop);
			vertex_indexes.push_back(0);
			vertex_indexes.push_back((i+1)%nbSegments + 1);
			vertex_indexes.push_back(i+1);
		}

		vertex_positions.push_back(glm::vec4(0,0,0,1));
		vertex_colors.push_back(colorBottom);
		for(unsigned int i = 0; i<nbSegments; ++i)
		{
			angle = ((double)i)/((double)nbSegments)*2.0*3.14;
			vertex_positions.push_back(glm::vec4(radiusBottom*std::cos(angle),0.0,radiusBottom*std::sin(angle),1.0));
			vertex_colors.push_back(colorBottom);
			vertex_indexes.push_back(nbSegments+1);
			vertex_indexes.push_back(nbSegments+2+(i+1)%nbSegments);
			vertex_indexes.push_back(nbSegments+i+2);
		}

		for(unsigned int i = 0; i<nbSegments; ++i)
		{
			vertex_indexes.push_back(i+1);
			vertex_indexes.push_back((i+1)%nbSegments + 1);
			vertex_indexes.push_back(nbSegments+2+(i+1)%nbSegments);

			vertex_indexes.push_back(i+1);
			vertex_indexes.push_back(nbSegments+2+(i+1)%nbSegments);
			vertex_indexes.push_back(nbSegments+i+2);
		}

	}

	void generateObjectBuffer() {
		
		//Initialize VAO
		glGenVertexArrays( 1, &vertex_array_object_id );
		glBindVertexArray( vertex_array_object_id );

		//Calc Array Sizes
		vertexArraySize = vertex_positions.size()*sizeof(glm::vec4);
		colorArraySize = vertex_colors.size()*sizeof(glm::vec4);
		//cube array size***********************
		//cubeverteArraySize = ;
		//cube array size***************************

		//Initialize VBO
		glGenBuffers( 1, &buffer_object_id );
		glBindBuffer( GL_ARRAY_BUFFER, buffer_object_id );
		glBufferData( GL_ARRAY_BUFFER, vertexArraySize + colorArraySize, NULL, GL_STATIC_DRAW );
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertexArraySize, (const GLvoid*)(&vertex_positions[0]) );
		glBufferSubData( GL_ARRAY_BUFFER, vertexArraySize, colorArraySize, (const GLvoid*)(&vertex_colors[0]));

		//Set up Vertex Arrays  
		glEnableVertexAttribArray( 0 ); //SimpleShader attrib at position 0 = "vPosition"
		glVertexAttribPointer( (GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		glEnableVertexAttribArray( 1 ); //SimpleShader attrib at position 1 = "vColor"
		glVertexAttribPointer( (GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexArraySize));

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//Initialize IBO
		glGenBuffers(1, &index_buffer_object_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_indexes.size()*sizeof(GLuint), (const GLvoid*)(&vertex_indexes[0]), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void generateCubeBuffer()
	{
			static const GLfloat g_vertex_buffer_data[] = { 
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f, 1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,//
				-1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f,-1.0f, 1.0f
		};

		// One color for each vertex. They were generated randomly.
		static const GLfloat g_color_buffer_data[] = { 
			0.583f,  0.771f,  0.014f,
			0.609f,  0.115f,  0.436f,
			0.327f,  0.483f,  0.844f,
			0.822f,  0.569f,  0.201f,
			0.435f,  0.602f,  0.223f,
			0.310f,  0.747f,  0.185f,
			0.597f,  0.770f,  0.761f,
			0.559f,  0.436f,  0.730f,
			0.359f,  0.583f,  0.152f,
			0.483f,  0.596f,  0.789f,
			0.559f,  0.861f,  0.639f,
			0.195f,  0.548f,  0.859f,
			0.014f,  0.184f,  0.576f,
			0.771f,  0.328f,  0.970f,
			0.406f,  0.615f,  0.116f,
			0.676f,  0.977f,  0.133f,
			0.971f,  0.572f,  0.833f,
			0.140f,  0.616f,  0.489f,
			0.997f,  0.513f,  0.064f,
			0.945f,  0.719f,  0.592f,
			0.543f,  0.021f,  0.978f,
			0.279f,  0.317f,  0.505f,
			0.167f,  0.620f,  0.077f,
			0.347f,  0.857f,  0.137f,
			0.055f,  0.953f,  0.042f,
			0.714f,  0.505f,  0.345f,
			0.783f,  0.290f,  0.734f,
			0.722f,  0.645f,  0.174f,
			0.302f,  0.455f,  0.848f,
			0.225f,  0.587f,  0.040f,
			0.517f,  0.713f,  0.338f,
			0.053f,  0.959f,  0.120f,
			0.393f,  0.621f,  0.362f,
			0.673f,  0.211f,  0.457f,
			0.820f,  0.883f,  0.371f,
			0.982f,  0.099f,  0.879f
		};
		glGenVertexArrays( 1, &vertex_array_object_id );
		glBindVertexArray( vertex_array_object_id );

		//Calc Array Sizes
		vertexArraySize = vertex_positions.size()*sizeof(glm::vec4)*7;
		colorArraySize = vertex_colors.size()*sizeof(glm::vec4)*7;
		//cube array size***********************
		//cubeverteArraySize = ;
		//cube array size***************************

		//Initialize VBO
		glGenBuffers( 1, &buffer_object_id );
		glBindBuffer( GL_ARRAY_BUFFER, buffer_object_id );
		glBufferData( GL_ARRAY_BUFFER, vertexArraySize + colorArraySize, NULL, GL_STATIC_DRAW );
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertexArraySize, (const GLvoid*)(&vertex_positions[0]) );
		glBufferSubData( GL_ARRAY_BUFFER, vertexArraySize, colorArraySize, (const GLvoid*)(&vertex_colors[0]));

		//Set up Vertex Arrays  
		glEnableVertexAttribArray( 0 ); //SimpleShader attrib at position 0 = "vPosition"
		glVertexAttribPointer( (GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		glEnableVertexAttribArray( 1 ); //SimpleShader attrib at position 1 = "vColor"
		glVertexAttribPointer( (GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexArraySize));

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//Initialize IBO
		glGenBuffers(1, &index_buffer_object_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_indexes.size()*sizeof(GLuint), (const GLvoid*)(&vertex_indexes[0]), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void draw(){
		glBindVertexArray(vertex_array_object_id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object_id);
		int size;  
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		size /= sizeof(GLuint);
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void drawCube()
	{
		glBindVertexArray(vertex_array_object_id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object_id);
		int size;  
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		size /= sizeof(GLuint);
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

public:
	glm::vec3 VA3 ;
	glm::vec3 VA2 ;
	glm::vec3 VA1 ;
	glm::vec3 VB3 ;
	glm::vec3 VB2 ;
	glm::vec3 VB1 ;
	glm::vec3 VC3 ;
	glm::vec3 VC2 ;
	glm::vec3 VC1 ;
	glm::vec3 VD3 ;
	glm::vec3 VD2 ;
	glm::vec3 VD1 ;
	glm::vec3 VE2 ;
	glm::vec3 VE1 ;


private:
	int nbSegments;
	std::vector<glm::vec4> vertex_positions;
	std::vector<glm::vec4> vertex_colors;
	std::vector<GLuint>	 vertex_indexes;
	//cube
	std::vector<glm::vec4> cubevertex_position;
	std::vector<glm::vec4> cubevertex_colors;
	std::vector<GLuint> cubevertex_indexes;

	GLuint vertexArraySize;
	GLuint colorArraySize;

	GLuint cubeverteArraySize;
	GLuint cubecolorArraySize;

	GLuint buffer_object_id;
	GLuint vertex_array_object_id;
	GLuint index_buffer_object_id;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	
};

#endif // __CYLINDER_H__