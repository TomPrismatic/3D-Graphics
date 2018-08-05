#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "ShaderLoader.h"
#include <iostream>


std::string raymanImage = "Dependencies/Rayman.jpg";
std::string faceImage = "Dependencies/AwesomeFace.png";

GLuint program;

GLuint VBO, VBOQuad;
GLuint VAO, VAOQuad;
GLuint EBO, EBOQuad;

GLuint texture;
GLfloat currentTime;


GLfloat verticesHex[] = { 
	//X        Y                Z                      Colour
	 -0.5f,  -(0.5 * sqrt(3)),   0.0f,             0.0f, 1.0f, 0.0f, //0  Left Bottom
	-1.0f,              0.0f,   0.0f,              0.0f, 0.0f, 1.0f, //1  Left Middle   
	-0.5f,   (0.5 * sqrt(3)),   0.0f,              0.5f, 0.5f, 0.0f, //2  Left Top
	 0.5f,   (0.5 * sqrt(3)),   0.0f,              0.5f, 0.0f, 0.5f, //3  Right Top
	 1.0f,              0.0f,   0.0f,              0.0f, 0.5f, 0.5f, //4  Right Middle
	 0.5f,   -(0.5 * sqrt(3)),   0.0f,             1.0f, 0.0f, 0.0f  //5  Eight Bottom
};

GLfloat verticesQuad[] = {
	// Positions               // Colors           // Tex Coords

	 -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f,       0.0f, 0.0f, // Top Left
	-0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,       0.0f, 1.0f, // Bottom Left
	 0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,       1.0f, 1.0f, // Bottom Right
	  0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f,	     1.0f, 0.0f // Top Right
};


GLuint indicesHex[] = 
{ 
	0, 2, 1, //Left Triangle
	3, 0, 2, //Top Triangle
	5, 3, 0, //Bottom Triangle
	4, 5, 3  //Right Triangle
};

GLuint indicesQuad[] = 
{
	0, 1, 2, //Left Triangle
	3, 0, 2  //Right Triangle
};



void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear red

	glUseProgram(program);
	glBindVertexArray(VAO); // Bind VAO 
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // Unbind VAO

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glBindVertexArray(VAOQuad); // Bind VAO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // Unbind VAO

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);

	glUseProgram(0); //Unbind Program
	
	glutSwapBuffers();
}

void init() 
{
	ShaderLoader shaderLoader; 
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); 
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHex), verticesHex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesHex), indicesHex, GL_STATIC_DRAW);

	// Quad
	glGenVertexArrays(1, &VAOQuad);
	glBindVertexArray(VAOQuad);
	glGenBuffers(1, &VBOQuad);
	glBindBuffer(GL_ARRAY_BUFFER, VBOQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesQuad), verticesQuad, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &EBOQuad);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOQuad);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesQuad), indicesQuad, GL_STATIC_DRAW);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int imageWidth, imageHeight, channels;
	unsigned char* image = SOIL_load_image(raymanImage.c_str(), &imageWidth, &imageHeight, &channels, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Update()
{
	glutPostRedisplay();
	currentTime = glutGet(GLUT_ELAPSED_TIME);  // Get current time. 
	currentTime = currentTime / 1000;  // Convert millisecond to seconds
	

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500); glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");
	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red
									 // register callbacks

	glewInit();
	init();

	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutMainLoop();
									 // Ensure this is the last glut line called return 0
}


