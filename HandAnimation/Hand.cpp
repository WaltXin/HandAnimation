// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cylinder.h>
#include <math.h>
#include <glew.h>;

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include <controls.h>
#include <shader.h>

#include <Primitive/ShapeGenerator.h>
#include <Skeleton.h>


using glm::mat4;

glm::vec4 &redColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
glm::vec4 &greenColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
glm::vec4 &blueColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
glm::vec4 &yellowColor = glm::vec4(1.0f,1.0f,0.0,1.0f);

Cylinder A3;
Cylinder A2;
Cylinder A1;
Cylinder B3;
Cylinder B2;
Cylinder B1;
Cylinder C3;
Cylinder C2;
Cylinder C1;
Cylinder D3;
Cylinder D2;
Cylinder D1;
Cylinder E2;
Cylinder E1;
Cylinder Croot;

Cylinder cube;
Cylinder cy;
Skeleton skeleton;

GLuint numIndices;

int main(void)
{
	//define the vector calca
	cy.initcy();
	glm::vec3 VA3 =cy.VA3;
	glm::vec3 VA2 =cy.VA2;
	glm::vec3 VA1 =cy.VA1;
	glm::vec3 VB3 =cy.VB3;
	glm::vec3 VB2 =cy.VB2;
	glm::vec3 VB1 =cy.VB1;
	glm::vec3 VC3 =cy.VC3;
	glm::vec3 VC2 =cy.VC2;
	glm::vec3 VC1 =cy.VC1;
	glm::vec3 VD3 =cy.VD3;
	glm::vec3 VD2 =cy.VD2;
	glm::vec3 VD1 =cy.VD1;
	glm::vec3 VE2 =cy.VE2;
	glm::vec3 VE1 =cy.VE1;
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(2048, 1400, " Hand Animation", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	//display skeleton structure 
	//skeleton.get_bone_by_ID(2);




	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
     //shader code 
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader"); // did not give programID


	//small finger
	A3.generateVertices(2.5f, 0.3f, 0.4f, redColor, redColor, 64);
	A3.generateObjectBuffer();

	A2.generateVertices(3.0f, 0.25f, 0.3f, yellowColor, yellowColor, 64);
	A2.generateObjectBuffer();
	
	A1.generateVertices(1.5f, 0.2f, 0.25f, blueColor, blueColor, 64);
	A1.generateObjectBuffer();
	//ring finger 
	B3.generateVertices(2.5f,0.3f,0.4f,redColor,redColor,64);
	B3.generateObjectBuffer();

	B2.generateVertices(3.0f, 0.25f, 0.3f, yellowColor, yellowColor, 64);
	B2.generateObjectBuffer();

	B1.generateVertices(1.5f, 0.2f, 0.25f, blueColor, blueColor, 64);
	B1.generateObjectBuffer();
	//middle finger 
	C3.generateVertices(2.5f,0.3f,0.4f,redColor,redColor,64);
	C3.generateObjectBuffer();
	
	C2.generateVertices(3.0f, 0.25f, 0.3f, yellowColor, yellowColor, 64);
	C2.generateObjectBuffer();
	
	C1.generateVertices(1.5f, 0.2f, 0.25f, blueColor, blueColor, 64);
	C1.generateObjectBuffer();
	//point finger
	D3.generateVertices(2.5f,0.3f,0.4f,redColor,redColor,64);
	D3.generateObjectBuffer();
	
	D2.generateVertices(3.0f, 0.25f, 0.3f, yellowColor, yellowColor, 64);
	D2.generateObjectBuffer();
	
	D1.generateVertices(1.5f, 0.2f, 0.25f, blueColor, blueColor, 64);
	D1.generateObjectBuffer();
	//thumb finger
	E2.generateVertices(2.5f, 0.3f, 0.4f,yellowColor,yellowColor,64);
	E2.generateObjectBuffer();

	E1.generateVertices(2.5f, 0.25f, 0.3f, redColor, redColor, 64);
	E1.generateObjectBuffer();
	//hand
	Croot.generateVertices(0.5f, 6.0f, 6.0f, redColor, redColor, 64);
	Croot.generateObjectBuffer();

	float angle_in_degrees1 = 90.0;
	float angle = 0;
	float angle_in_degrees2 = 90.0;
	float angle_in_degrees3 = 90.0;

	float ag = 0.0;
	float counter = 0.0;
	do{

		counter += 0.005;
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::vec3 myRotationAxis4C(1.0f, 0.0f, 0.0f);
		glm::vec3 myRotationAxis4C2(0.0f, 0.0f, 1.0f);
		glm::vec3 stoprotate(0.0f,0.0f,0.0f);
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");
		
		glm::mat4 ModelMatrix4Croot = glm::rotate(ModelMatrix, angle_in_degrees1, myRotationAxis4C);
		glm::mat4 MVP4Croot = ProjectionMatrix*ViewMatrix*ModelMatrix4Croot;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4Croot[0][0]);
		//Croot.draw();
		
		
		//cube
		//**********************************************************************
		/*cube.generateCubeBuffer();
		glm::mat4 ModelMatrix4Cube = glm::rotate(ModelMatrix, ag, stoprotate);
		glm::mat4 MVP = ProjectionMatrix*ViewMatrix*ModelMatrix4Cube;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		cube.drawCube();*/

		//**********************************************************************
		//cube

		//A3
		glm::mat4 ModelMatrixA3 = ModelMatrix4Croot*glm::rotate(glm::translate(
			ModelMatrix,
			VA3),
			angle = 0.3*sin(counter)*angle_in_degrees1-60, 
			myRotationAxis4C
			);
		glm::mat4 MVP4A3 = ProjectionMatrix*ViewMatrix*ModelMatrixA3;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4A3[0][0]);
		
		A3.draw();
		
		//A2  
		glm::mat4 ModelMatrix4A2 = ModelMatrixA3*glm::rotate(glm::translate(
			ModelMatrix, 
			VA2),
			angle_in_degrees2 = angle+90, 
			myRotationAxis4C
			);
		glm::mat4 MVP4A2 = ProjectionMatrix*ViewMatrix*ModelMatrix4A2;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4A2[0][0]);
		A2.draw();
		
		//A1
		glm::mat4 ModelMatrix4A1 = ModelMatrix4A2*glm::rotate(glm::translate(
			ModelMatrix, 
			VA1),
			angle_in_degrees3 = angle_in_degrees2+30, 
			myRotationAxis4C);
		glm::mat4 MVP4A1 = ProjectionMatrix*ViewMatrix*ModelMatrix4A1;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4A1[0][0]);
		A1.draw();
	

		//B3
		glm::mat4 ModelMatrix4B3 = ModelMatrix4Croot*glm::rotate(glm::translate(
			ModelMatrix,
		VB3),
			angle = 0.3*sin(counter)*angle_in_degrees1-60, 
			myRotationAxis4C
			);
		glm::mat4 MVP4B3 = ProjectionMatrix*ViewMatrix*ModelMatrix4B3;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4B3[0][0]);
		B3.draw();
		//B2
		glm::mat4 ModelMatrix4B2 = ModelMatrix4B3*glm::rotate(glm::translate(
			ModelMatrix, 
			VB2),
			angle_in_degrees2 = angle+90, 
			myRotationAxis4C
			);
		glm::mat4 MVP4B2 = ProjectionMatrix*ViewMatrix*ModelMatrix4B2;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4B2[0][0]);
		B2.draw();
		//B1
		glm::mat4 ModelMatrix4B1 = ModelMatrix4B2*glm::rotate(glm::translate(
			ModelMatrix, 
		VB1),
			angle_in_degrees3 = angle_in_degrees2+30, 
			myRotationAxis4C);
		glm::mat4 MVP4B1 = ProjectionMatrix*ViewMatrix*ModelMatrix4B1;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4B1[0][0]);
		A1.draw();
		//C3

		glm::mat4 ModelMatrix4C3 = ModelMatrix4Croot*glm::rotate(glm::translate(
			ModelMatrix,
			VC3),
			angle = 0.3*sin(counter)*angle_in_degrees1-60, 
			myRotationAxis4C
			);
		glm::mat4 MVP4C3 = ProjectionMatrix*ViewMatrix*ModelMatrix4C3;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4C3[0][0]);
		C3.draw();

		//C2
		glm::mat4 ModelMatrix4C2 = ModelMatrix4C3*glm::rotate(glm::translate(
			ModelMatrix, 
		VC2),
			angle_in_degrees2 = angle+90, 
			myRotationAxis4C
			);
		glm::mat4 MVP4C2 = ProjectionMatrix*ViewMatrix*ModelMatrix4C2;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4C2[0][0]);
		C2.draw();

		//C1
		glm::mat4 ModelMatrix4C1 = ModelMatrix4C2*glm::rotate(glm::translate(
			ModelMatrix, 
			VC1),
			angle_in_degrees3 = angle_in_degrees2+30, 
			myRotationAxis4C);
		glm::mat4 MVP4C1 = ProjectionMatrix*ViewMatrix*ModelMatrix4C1;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4C1[0][0]);
		C1.draw();

		//D3

		glm::mat4 ModelMatrix4D3 = ModelMatrix4Croot*glm::rotate(glm::translate(
			ModelMatrix,
		VD3),
			angle = 0.3*sin(counter)*angle_in_degrees1-60, 
			myRotationAxis4C
			);
		glm::mat4 MVP4D3 = ProjectionMatrix*ViewMatrix*ModelMatrix4D3;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4D3[0][0]);
		D3.draw();

		//D2
		glm::mat4 ModelMatrix4D2 = ModelMatrix4D3*glm::rotate(glm::translate(
			ModelMatrix, 
		VD2),
			angle_in_degrees2 = angle+90, 
			myRotationAxis4C
			);
		glm::mat4 MVP4D2 = ProjectionMatrix*ViewMatrix*ModelMatrix4D2;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4D2[0][0]);
		D2.draw();

		//D1
		glm::mat4 ModelMatrix4D1 = ModelMatrix4D2*glm::rotate(glm::translate(
			ModelMatrix, 
		VD1),
			angle_in_degrees3 = angle_in_degrees2+30, 
			myRotationAxis4C);
		glm::mat4 MVP4D1 = ProjectionMatrix*ViewMatrix*ModelMatrix4D1;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4D1[0][0]);
		D1.draw();

		//E2
		mat4 fingerA3RotateMatrix = glm::rotate(90.0f,glm::vec3(0.0f,0.0f,1.0f));
		glm::mat4 ModelMatrixE2 = ModelMatrix4Croot*glm::rotate(glm::translate(
			ModelMatrix,
			VE2),
			angle = 0.3*sin(counter)*angle_in_degrees1-60, 
			myRotationAxis4C2
			);

		//E1 
		glm::mat4 ModelMatrix4E1 = ModelMatrixE2*glm::rotate(glm::translate(
			ModelMatrix, 
			VE1),
			angle_in_degrees2 = angle+120, 
			myRotationAxis4C2
			);
		glm::mat4 MVP4E1 = ProjectionMatrix*ViewMatrix*ModelMatrix4E1;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4E1[0][0]);
		E1.draw();

		
		glm::mat4 MVP4E2 = ProjectionMatrix*ViewMatrix*ModelMatrixE2;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4E2[0][0]);
		E2.draw();


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0);

	glDeleteProgram(programID);
	
	glfwTerminate();

	return 0;
}

