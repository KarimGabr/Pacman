//#include <GL/glew.h>
#include <iostream>
//#include "darthv.cpp"
//#include "maze.cpp"
//#include "gimp_image.cpp"
#include <glut.h>
//#include <GLFW/glfw3.h>
#include <tuple>
#include <string>
#include <stdlib.h>
#include<time.h>
void ex(int refreshtime);

void ppp(int speed);

int lives = 3;
#define PI 3.1415926535897932384626433832795

bool powerups = false;

int pacmanMaze[34][30]
{ 	//designing the maze as 2d array as follows:
	//11:walls ,, 22:path with food ,, 33:path with no food ,, 44:power ups ,, 55:500 points food ,, 66:darthman start position

	{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 11, 11, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 11, 11 },
	{ 11, 11, 22, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 22, 11, 11 },
	{ 11, 11, 44, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 44, 11, 11 },
	{ 11, 11, 22, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 22, 11, 11 },
	{ 11, 11, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 11, 11 },
	{ 11, 11, 22, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 22, 11, 11 },
	{ 11, 11, 22, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 22, 11, 11 },
	{ 11, 11, 22, 22, 22, 22, 22, 22, 11, 11, 22, 22, 22, 22, 11, 11, 22, 22, 22, 22, 11, 11, 22, 22, 22, 22, 22, 22, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 33, 11, 11, 33, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 33, 11, 11, 33, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 11, 11, 33, 33, 33, 33, 11, 11, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 11, 33, 33, 33, 33, 33, 33, 11, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 11, 33, 33, 33, 33, 33, 33, 11, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 33, 33, 33, 33, 33, 33, 33, 22, 33, 33, 33, 11, 33, 33, 33, 33, 33, 33, 11, 33, 33, 33, 22, 33, 33, 33, 33, 33, 33, 33 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 11, 33, 33, 33, 33, 88, 33, 11, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 11, 33, 33, 33, 33, 33, 33, 11, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 11, 11, 11, 11, 11, 11, 11, 11, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 33, 11, 11, 11, 11, 11, 11, 11, 11, 33, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 11, 11, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 11, 11 },
	{ 11, 11, 22, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 22, 11, 11 },
	{ 11, 11, 22, 11, 11, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 22, 11, 11, 11, 11, 22, 11, 11 },
	{ 11, 11, 44, 22, 22, 11, 11, 22, 22, 22, 22, 22, 22, 22, 22, 55, 22, 22, 22, 22, 22, 22, 22, 11, 11, 22, 22, 44, 11, 11 },
	{ 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11 },
	{ 11, 11, 22, 22, 22, 22, 22, 22, 11, 11, 22, 22, 22, 22, 11, 11, 22, 22, 22, 22, 11, 11, 22, 22, 22, 22, 22, 22, 11, 11 },
	{ 11, 11, 22, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 22, 11, 11 },
	{ 11, 11, 22, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 22, 11, 11, 22, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 22, 11, 11 },
	{ 11, 11, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 66, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 }
};

int foodScore = 0;
std::string score = "";
std::string llives = "";
bool mainMenuText = true;

float xPacmanPos, yPacmanPos;
float canMoveUp;
float canMoveDown;
float canMoveRight;
float canMoveLeft;
float moveHorizontal = 0;
float moveVertical = 0;

float xEnemyPos, yEnemyPos;
float canMoveUpE;
float canMoveDownE;
float canMoveRightE;
float canMoveLeftE;
float moveHorizontalE = 0;
float moveVerticalE = 0;
/*
typedef struct
{
	GLfloat positionCoordinates[3];
} VertexData;

//#define Square_Size 

VertexData vertices[] = 
{
	{ 9.0f , 6.0f, 0.0f },
	{ 9.0f , 4.0f, 0.0f },
	{ 11.0f, 4.0f, 0.0f },
	{ 11.0f, 6.0f, 0.0f },
};
*/
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

void changeSize(int width, int height); //here in this app we are forcing a fixed size window so we don't need this function 
//however I am keeping it because my Cheeki Breeki bro Georgi keeps waiting for Teodora to show up

void resize(int width, int height); //function to force fixed window size
void renderScene(void); //function to render all scene objects
void drawLine(int width, int height, int xOffset, int yOffset, bool isVerticalDraw); //function to draw a line 
void drawCircle(float x, float y, float xOffset, float yOffset, float radius);//function to draw a circle
void renderBitmapString(float x, float y, int spacing, void *font, char *string); //function to render the string on screen as a 2d bitmap object
void setOrthographicProjection(double left, double right, double bottom, double top); //function to project a new matrix 
void restorePerspectiveProjection(); //function to return to previous matrix
void renderMaze(); //function to render maze
void renderSquare(); //function to render sqaure
void renderMainMenuText(); //function to render main menu text
void animate(int value); //animation function for menu text
void movementBehaviour();
void enemyBehaviour();

std::tuple<float, float> drawPacman(float x, float y, float xOffset, float yOffset);
std::tuple<float, float> drawEnemy(float x, float y, float xOffset, float yOffset);

int ttime = 0; // used for animtation
float speed = 1.2f; // 120 frames per second masterrace

int main()
{
	/*if (GLEW_OK != glewInit()) { return 1; }
	//while (GL_NO_ERROR != glGetError());
	GLuint _vertexBufferID = 0;*/
	// initialize glut and create window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 4, 0);
	glutCreateWindow("Darthman");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0, 45, 45, 0);
	/*
	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *) offsetof (VertexData, positionCoordinates));*/


	// register callback functions
	glutTimerFunc(1.0, animate, 0);
	glutDisplayFunc(renderScene);
	glutTimerFunc(1.0, animate, 0);
	glutTimerFunc(1000, ex, 1000);
	glutPostRedisplay();
	
	if (powerups == true) //bug
	{
		glutTimerFunc(1.0, ppp, 5000);

	}

	glutIdleFunc(renderScene);
	glutReshapeFunc(resize);

	// register keyboard entry
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	// enter glut event processing loop
	glutMainLoop();

	return 1;
}
	
void ppp(int speed)
{
	glutTimerFunc(speed, ppp, 500);
	ttime++;
	if (ttime >= 1)
	{
		ttime = 0;        // time is in tenths of a second
		powerups = false;
	}
		
	glutPostRedisplay();
}

	void ex( int refreshtime) 
	{
		enemyBehaviour();
		glutPostRedisplay();
		glutTimerFunc(refreshtime, ex, refreshtime);	
	}

void resize(int width, int height) 
{
	// creating fixed size window by forcing it to a particular size whenever you detect that it has been resized.
	glutReshapeWindow(700, 700);
}

void changeSize(int width, int height)
{

	// prevent division by zero when window is too short
	if (height == 0) height = 1;
	float ratio = 1.0* width / height;

	// use the projection matrix
	glMatrixMode(GL_PROJECTION);

	// reset matrix
	glLoadIdentity();

	// set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// set the correct perspective
	gluPerspective(45, ratio, 1, 133);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	renderMaze();
	
	renderSquare();

	renderMainMenuText();
	
	enemyBehaviour(); //bug

	glFlush(); 
}

void drawLine(int width, int height, int xOffset, int yOffset, bool isVerticalDraw)
{
	glBegin(GL_LINES);
	glVertex2i(width + xOffset, height + yOffset);
	if(isVerticalDraw) glVertex2i(width + xOffset, height + 1 + yOffset);
	else glVertex2i(width + 1 + xOffset, height + yOffset);
	glEnd();
}

void renderBitmapString(float x, float y, int spacing, void *font, char *string) 
{
	char *c;
	int x1 = x;

	for (c = string; *c != '\0'; c++) 
	{
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c) + spacing;
	}

	//delete[] string;
}

void setOrthographicProjection(double left, double right, double bottom, double top)
{
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(left, right, bottom, top);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() 
{
	glMatrixMode(GL_PROJECTION);
	
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void animate(int value) 
{
	glutTimerFunc(speed, animate, 0);
	ttime++;
	if (ttime >= 10)
		ttime = 0;        // time is in tenths of a second
	glutPostRedisplay();
}

void renderMaze()
{
	int const xOffset = 8; // X offset to shift the maze to the center of the screen in the drawing process
	int const yOffset = 3; // Y offset to shift the maze to the center of the screen in the drawing process

	int const mazeHeight = 34;
	int const mazeWidth = 30;

	for (int height = 0; height < mazeHeight; height++)
	{
		for (int width = 0; width < mazeWidth; width++)
		{
			if (pacmanMaze[height][width] == 11)
			{
				glColor3f(0.0, 0.0, 1.0);

				if (pacmanMaze[height][width + 1] == 11 && width != mazeWidth - 1)
					drawLine(width, height, xOffset, yOffset, false);

				if (pacmanMaze[height + 1][width] == 11 && height != mazeHeight - 1)
					drawLine(width, height, xOffset, yOffset, true);
			}
			
			if (pacmanMaze[height][width] == 22)
			{
				glColor3f(0.92f, 0.77f, 0.65f);
				drawCircle(width, height, xOffset, yOffset, 0.065f);
			}
			
			if (pacmanMaze[height][width] == 44)
			{ 
				glColor3f(0.92f, 0.77f, 0.65f);
				drawCircle(width, height, xOffset, yOffset, 0.28f);
			}

			if (pacmanMaze[height][width] == 55)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				drawCircle(width, height, xOffset, yOffset, 0.6f);
			}

			if (pacmanMaze[height][width] == 66)
			{
				glColor3f(1.0f, 0.0f, 1.0f);
				if (pacmanMaze[height + 1][width] == 11)	canMoveDown = false;
				if (pacmanMaze[height - 1][width] == 11)	canMoveUp = false;
				//std::cout << width << ", " << height << std::endl;
				/*while (true)
				{

				}*/
				std::tie(xPacmanPos, yPacmanPos) = drawPacman(width, height, xOffset, yOffset);
			}


			if (pacmanMaze[height][width] == 88)
			{
				glColor3f(0.0f, 1.0f, 1.0f);
				if (pacmanMaze[height + 1][width] == 11)	canMoveDown = false;
				if (pacmanMaze[height - 1][width] == 11)	canMoveUp = false;
				//std::cout << width << ", " << height << std::endl;
				/*while (true)
				{

				}*/
				std::tie(xEnemyPos, yEnemyPos) = drawEnemy(width, height, xOffset, yOffset);
			}

				
		}
	}
}

void renderMainMenuText()
{
	/*char * writable = new char[score.size() + 1];
	std::copy(score.begin(), score.end(), writable);
	writable[score.size()] = '\0';
	delete[] writable;*/

	char *cstr = new char[score.length() + 1];
	strcpy(cstr, score.c_str());

	char *cstr1 = new char[llives.length() + 1];
	strcpy(cstr1, llives.c_str());


	glColor3f(1.0f, 1.0f, 0.0f);
	setOrthographicProjection(0.0,800.0,800.0,0.0);
	glPushMatrix();
	glLoadIdentity();
	if(lives != 0)renderBitmapString(250, 690, 0, GLUT_BITMAP_HELVETICA_18, "P       A       C       M       A       N");
	else if (lives == 0) {
		renderBitmapString(250, 690, 0, GLUT_BITMAP_HELVETICA_18, "G   A   M   E    O   V    E    R");

	}
	if (ttime > 5 && mainMenuText == true)
		renderBitmapString(300, 735, 0, GLUT_BITMAP_HELVETICA_18, "Press Space to start...");
	if (mainMenuText == false)
		renderBitmapString(300, 735, 0, GLUT_BITMAP_HELVETICA_18, cstr);
	if (lives > 0)
		renderBitmapString(400, 735, 0, GLUT_BITMAP_HELVETICA_18, cstr1);
	glPopMatrix();
	restorePerspectiveProjection();
	glutSwapBuffers();
}

void renderSquare()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_QUADS, 0, 4);
	glEnd();
}

void drawCircle(float x, float y, float xOffset, float yOffset, float radius)
{
	GLfloat twicePi = 2.0f * PI;

	x = x + xOffset;
	y = y + yOffset;

	if (pacmanMaze[int(yPacmanPos)][int(xPacmanPos)] == 22)
	{
		pacmanMaze[int(yPacmanPos)][int(xPacmanPos)] = 99;
		foodScore++;
		score = std::to_string(foodScore);
		/*std::cout << score << std::endl; while (true)
		{

		}*/
	}
	if (pacmanMaze[int(yPacmanPos)][int(xPacmanPos)] == 55)
	{
		pacmanMaze[int(yPacmanPos)][int(xPacmanPos)] = 99;
		foodScore += 500;
		score = std::to_string(foodScore);
		/*std::cout << score << std::endl; while (true)
		{

		}*/
	}
	else if (pacmanMaze[int(yPacmanPos)][int(xPacmanPos)] == 44)
	{
		pacmanMaze[int(yPacmanPos)][int(xPacmanPos)] = 99;
		powerups = true;
		/*std::cout << score << std::endl; while (true)
		{

		}*/
	}
	else 
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for (int i = 0; i <= 100; i++) 
		{
			glVertex2f(
				x + (radius * cos(i *  twicePi / 100)),
				y + (radius * sin(i * twicePi / 100))
			);
		}
		glEnd();
	}
}

std::tuple<float,float> drawPacman(float x, float y, float xOffset, float yOffset)
{
	 //setOrthographicProjection(0.0, 45.0, 45.0, 0.0);
	 //glPushMatrix();
	 //glLoadIdentity();

	 float xnew, ynew;

	 x = x + xOffset;
	 y = y + yOffset;
	 
	 glBegin(GL_QUADS);
	 glVertex2f(x - 0.7 + moveHorizontal, y + 0.7 + moveVertical);
	 glVertex2f(x - 0.7 + moveHorizontal, y - 0.7 + moveVertical);
	 glVertex2f(x + 0.7 + moveHorizontal, y - 0.7 + moveVertical);
	 glVertex2f(x + 0.7 + moveHorizontal, y + 0.7 + moveVertical);
	 glEnd();

	 xnew = x + moveHorizontal - xOffset;
	 ynew = y + moveVertical - yOffset;

	 //std::cout << xnew << ", " << ynew << std::endl;
	


	 //glPopMatrix();
	 //restorePerspectiveProjection();
	 //glutSwapBuffers();
	 return std::make_tuple(xnew, ynew);
}


 void processNormalKeys(unsigned char key, int x, int y)
 {
	 switch (key)
	 {
		 // press esc to exit
	 case 27:
		 exit(0); break;
		 // press space to pause rotation
	 case 32:
		 mainMenuText = false; break;
	 default:break;
	 }
 }

 void processSpecialKeys(int key, int x, int y)
 {
	 if (mainMenuText == false && lives > 0)
	 {
		 movementBehaviour();

		 switch (key)
		 {

		 case GLUT_KEY_LEFT:
			 if (canMoveLeft == true)
			 {
				 moveHorizontal -= 1.0f;
				 break;
			 }
			 break;

		 case GLUT_KEY_RIGHT:
			 if (canMoveRight == true)
			 {
				 moveHorizontal += 1.0f;
				 break;
			 }
			 break;

		 case GLUT_KEY_UP:
			 if (canMoveUp == true)
			 {
				 moveVertical -= 1.0f;
				 break;
			 }
			 break;

		 case GLUT_KEY_DOWN:
			 if (canMoveDown == true)
			 {
				 moveVertical += 1.0f;
				 break;
			 }
			 break;

		 default:break;
		 }
	 }
 }

 void movementBehaviour()
 {
	 canMoveDown = true;
	 canMoveUp = true;
	 canMoveLeft = true;
	 canMoveRight = true;

	 //std::cout << int(xPacmanPos) << ", " << int(yPacmanPos) << std::endl;
	 if (pacmanMaze[int(yPacmanPos)][int(xPacmanPos) + 1] == 11)canMoveRight = false;
	 if (pacmanMaze[int(yPacmanPos)][int(xPacmanPos) - 1] == 11) canMoveLeft = false;
	 if (pacmanMaze[int(yPacmanPos) + 1][int(xPacmanPos)] == 11) canMoveDown = false;
	 if (pacmanMaze[int(yPacmanPos) - 1][int(xPacmanPos)] == 11) canMoveUp = false;
	 llives = std::to_string(lives);
	 if (xPacmanPos == xEnemyPos && yPacmanPos == yEnemyPos && powerups == false)
	 {
		 if (lives > 0)
		 {
			 lives--;
		 }
	 }
	 if (xPacmanPos == xEnemyPos && yPacmanPos == yEnemyPos && powerups == true)
	 {
		 if (lives < 4)
		 {
			 lives++;
		 }
	 }
 }

std::tuple<float,float> drawEnemy(float x, float y, float xOffset, float yOffset)
{
	 //setOrthographicProjection(0.0, 45.0, 45.0, 0.0);
	 //glPushMatrix();
	 //glLoadIdentity();

	 float xnew, ynew;

	 x = x + xOffset;
	 y = y + yOffset;
	 
	 glBegin(GL_QUADS);
	 glVertex2f(x - 0.7 + moveHorizontalE, y + 0.7 + moveVerticalE);
	 glVertex2f(x - 0.7 + moveHorizontalE, y - 0.7 + moveVerticalE);
	 glVertex2f(x + 0.7 + moveHorizontalE, y - 0.7 + moveVerticalE);
	 glVertex2f(x + 0.7 + moveHorizontalE, y + 0.7 + moveVerticalE);
	 glEnd();

	 xnew = x + moveHorizontalE - xOffset;
	 ynew = y + moveVerticalE - yOffset;

	 //std::cout << xnew << ", " << ynew << std::endl;
	
	 if (powerups == true)
	 {
		 glColor3f(0.4f, 0.5f, 0.6f);
	 }

	 //glPopMatrix();
	 //restorePerspectiveProjection();
	 //glutSwapBuffers();
	 return std::make_tuple(xnew, ynew);
}

void enemyBehaviour()
{
	canMoveDownE = true;
	canMoveUpE = true;
	canMoveLeftE = true;
	canMoveRightE = true;

	std::cout << int(xEnemyPos) << ", " << int(yEnemyPos) << std::endl;
	if (pacmanMaze[int(yEnemyPos)][int(xEnemyPos) + 1] == 11)canMoveRightE = false;
	if (pacmanMaze[int(yEnemyPos)][int(xEnemyPos) - 1] == 11) canMoveLeftE = false;
	if (pacmanMaze[int(yEnemyPos) + 1][int(xEnemyPos)] == 11) canMoveDownE = false;
	if (pacmanMaze[int(yEnemyPos) - 1][int(xEnemyPos)] == 11) canMoveUpE = false;

	std::cout << int(xEnemyPos) << ", " << int(yEnemyPos) << std::endl;

	int moveRandom;

	srand (time(NULL));
	moveRandom = rand() % 4 + 1;
	if (moveRandom == 4 && canMoveRightE == true)
	{
		moveHorizontalE += 1.0;
		moveRandom = rand() % 3 + 1;
		if (moveRandom == 3 && canMoveLeftE == true)  moveHorizontalE -= 1.0;
		if (moveRandom == 2 && canMoveDownE == true)  moveVerticalE += 1.0;
		if (moveRandom == 1 && canMoveUpE == true)    moveVerticalE -= 1.0;
	}
	else if (moveRandom == 3 && canMoveLeftE == true)  
	{
		moveHorizontalE -= 1.0;
		moveRandom = rand() % 3 + 1;
		if (moveRandom == 3 && canMoveRightE == true)  moveHorizontalE += 1.0;
		if (moveRandom == 2 && canMoveDownE == true)  moveVerticalE += 1.0;
		if (moveRandom == 1 && canMoveUpE == true)    moveVerticalE -= 1.0;
	}
	else if (moveRandom == 2 && canMoveDownE == true)  
	{
		moveVerticalE   += 1.0;
		moveRandom = rand() % 3 + 1;
		if (moveRandom == 3 && canMoveLeftE == true)  moveHorizontalE -= 1.0;
		if (moveRandom == 2 && canMoveRightE == true)  moveVerticalE += 1.0;
		if (moveRandom == 1 && canMoveUpE == true)    moveVerticalE -= 1.0;
	}
	else if (moveRandom == 1 && canMoveUpE == true)    
	{
		moveVerticalE   -= 1.0;
		moveRandom = rand() % 3 + 1;
		if (moveRandom == 3 && canMoveLeftE == true)  moveHorizontalE -= 1.0;
		if (moveRandom == 2 && canMoveDownE == true)  moveVerticalE += 1.0;
		if (moveRandom == 1 && canMoveRightE == true)    moveVerticalE += 1.0;
	}
}