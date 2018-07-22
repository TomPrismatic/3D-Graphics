#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "ShaderLoader.h"
#include <iostream>

GLuint program;


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); //clear red

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3); //GL_POINTS, GL_LINES

	glutSwapBuffers();
}

void init() 
{
	ShaderLoader shaderLoader; 
	const char* pointer = "VertexShader.vs";
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500); glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");
	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red
									 // register callbacks

	glewInit();
	init();

	glutDisplayFunc(render);
	glutMainLoop();
									 // Ensure this is the last glut line called return 0
}


