#pragma once 

#include <iostream>

#include <GL/glew.h>

class Mesh
{
private:
GLuint VAO;
GLuint PointDrawCout;

public:
	
	void Create(GLfloat *vertices, GLuint v_size, GLuint *indices, GLuint i_size)
	{
		GLuint VBO;
		GLuint EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		
		
		glBindVertexArray(VAO);
		
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);
			
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			
		glBindVertexArray(0);
		
		PointDrawCout = i_size / sizeof(GLuint);
	}
	
	void CreateSquare()
	{
		GLfloat vertices[]
		{
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f
		};
		
		GLuint indeces[]
		{
			0, 1, 3,
			1, 2, 3
		};
		
		Create(vertices, sizeof(vertices), indeces, sizeof(indeces));
	}
	
	void CreateCube()
	{
		GLfloat vertices[]
		{
			 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

			  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			 -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		
		GLuint indeces[]
		{
			0, 1, 3,
			1, 2, 3,
			
			4, 5, 7,
			5, 6, 7,
			
			8, 9,  11,
			9, 10, 11,
			
			12, 13, 15,
			13, 14, 15,
			
			16, 17, 19,
			17, 18, 19,
			
			20, 21, 23,
			21, 22, 23
		};
		
		Create(vertices, sizeof(vertices), indeces, sizeof(indeces));
	}
	
	void CreateTriangle()
	{
		GLfloat vertices[]
		{
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f,  0.5f, 1.0f,
		};
		
		GLuint indeces[]
		{
			0, 1, 2
		};
		
		Create(vertices, sizeof(vertices), indeces, sizeof(indeces));
	}
	
	void CreatePyramid()
	{
		GLfloat vertices[]
		{
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.0f,  0.5f,  0.0f, 0.5f, 1.0f,
			 
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		};
		
		GLuint indeces[]
		{
			0, 1, 2,
			1, 4, 2,
			4, 3, 2,
			3, 0, 2,
			
			0, 1, 5,
			5, 6, 0
		};
		
		Create(vertices, sizeof(vertices), indeces, sizeof(indeces));
	}
	
	inline void Draw() const
	{
		glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, PointDrawCout, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};