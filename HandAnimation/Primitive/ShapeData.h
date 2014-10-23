#pragma once
#include<glew.h>
#include<Primitive\Vertex.h>
class Vertex;

struct ShapeData
{
	ShapeData():
		vertices(0), numVertices(0),
		indices(0),numIndices(0){}
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;
	GLsizeiptr vertexBufferSize() const
	{
		return numVertices*sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const
	{
		return numIndices*sizeof(GLushort);
	}
	void cleanUp()
	{
		delete []vertices;
		delete []indices;
		numVertices=numIndices=0;
	}
};