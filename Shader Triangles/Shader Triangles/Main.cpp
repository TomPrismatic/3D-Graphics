#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "ShaderLoader.h"
#include <iostream>

GLuint program;
GLuint VBO;
GLuint VAO;

GLfloat vertices[] = { // Position 
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Left 
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Right 
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Top   
};


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); //clear red

	glUseProgram(program);
	glBindVertexArray(VAO); // Bind VAO 
	glDrawArrays(GL_TRIANGLES, 0, 3); //GL_POINTS, GL_LINES
	glBindVertexArray(0); // Unbind VAO


	glutSwapBuffers();
}

void init() 
{
	ShaderLoader shaderLoader; 
	const char* pointer = "VertexShader.vs";
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); 
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));;
	glEnableVertexAttribArray(1);

}

void Update()
{
	glutPostRedisplay();
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


