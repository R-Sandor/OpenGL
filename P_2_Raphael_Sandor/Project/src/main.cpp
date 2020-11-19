/// \file
/// This is the main file for the project Traffic Simulation.
/// \author Yuzhong Shen
/// \version 1.0
/// \date 12/10/2017
///

#include <iostream>
#include <sstream>
#include <string>

#include <gl/glew.h>
#include <gl/glut.h>

#include "ObjModel.h"
#include "TrafficLight.h"
#include "utility.h"

using namespace std;

int counter = 0; ///< Counter for the traffic signal.  Only one is needed.
int updateInterval = 20; ///< Update interval for the update function in miliseconds.
int numOUpdatesPerSec = 1000 / updateInterval;
/// Decided to define these here so if we change the update
/// interval we don't need to go through recalculating 
/// the number of intervals
int fiveSeconds = numOUpdatesPerSec * 5;
int sixSeconds = numOUpdatesPerSec * 6;
int elevenSeconds = numOUpdatesPerSec * 11;
int twelveSeconds = numOUpdatesPerSec * 12;

ObjModel car;
ObjModel surveillanceCamera;
//ObjModel skyscraper;

TrafficLight tLightNorthSouth;
TrafficLight tLightEW;

int carID; ///< Display List ID for car
int surveillanceCameraID; ///< Display list ID for surveillance camera
int terrainID; ///< Display list ID for terrain
//int buildingID; ///< Display list for buildings

Signal NS_Signal = Green;  ///< North-South signal.
Signal WE_Signal = Red;  ///< West-East signal.

Vector3 carPosition = { 3, 0, 45 }; ///< Car position with initial value.
Vector3 homePosition = carPosition; /// < Added a place for initial car location
Vector3 localCarSpeed = { 0, 0, 0 }; ///< Car speed in car's local space.

/// Played with a couple of different values for what the turn angle should be
/// somewhere betwen 1.25 - 2.5 felt good.
/// Decided to go with two since it is an even number and can demonstrate that 
/// N/S/SW/SE/NW/NE all work.
double	turn = 2;

Vector3 worldCarSpeed; ///< Car speed in world space.

/// How much we should increase/decrease the car's local car speed
double accelerate = .20;
double decelerate = -0.2;

float carDirection = 180;  ///< Car direction
string carHeading = "N"; ///< String for car heading
/// Adjusted offset to look like Dr. Shen screenshot.
Vector3	localCameraOffset = { 0, 0, -6.5 };  ///< Third person camera offset in the car's local space.

/// I had to setup the world camera offset otherwise when the camera 
/// would not be pointing the way one would expect.
Vector3 worldCameraOffset = { 0, 0, 6.5 };  ///< Third person camera offset in world space.

int winWidth; ///< Width of OpenGL window
int winHeight; ///< Height of OpenGL window
int sWidth; ///< Width of the small viewport
int sHeight; ///< Height of the small viewport

/// Update the small viewports' size automatically.
/// \param w Width of the OpenGL window
/// \param h Height of the OpenGL window
void reshape(int w, int h)
{
	winWidth = w, winHeight = h;
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

	sWidth = (winWidth-50)/3;
	sHeight = 100;
}

/// Updates the direction and the display string for heading.
void updateHeading() 
{
	// Compute the car's direction.
	if (carDirection == 0)
		carHeading = "S";
	else if (carDirection > 0 && carDirection < 90)
		carHeading = "SE";
	else if (carDirection == 90)
		carHeading = "E";
	else if (carDirection > 90 && carDirection < 180)
		carHeading = "NE";
	else if (carDirection == 180)
		carHeading = "N";
	else if (carDirection > 180 && carDirection < 270)
		carHeading = "NW";
	else if (carDirection == 270)
		carHeading = "W";
	else
		carHeading = "SW";
}

/// Simple addition/subtraction to keep everyting within 360 degrees.
void updateDirection() {
	if (carDirection > 360)
		carDirection -= 360;
	else if (carDirection < 0)
		carDirection += 360;
}

/// Callback function for special keys.
/// \param key ASCII code of the key pressed.
/// \param x X coordinate of the mouse cursor when the key is pressed.
/// \param y Y coordinate of the mouse cursor when the key is pressed.
void specialKey(int key, int x, int y)
{
	/// handle turning left
	if (key == GLUT_KEY_LEFT)
	{
		/// Handle the left turns.
		if (carDirection == 0)
			carDirection = 360;
		else
			carDirection += turn;

	}
	if (key == GLUT_KEY_RIGHT)
	{
		/// Handle the right turns.
		if (carDirection == 360)
			carDirection = 0;
		else
			carDirection += -turn;
	}
	if (key == GLUT_KEY_UP)
	{
		/// Acceleration.
		/// Determine the max speed.
		/// Since the relative real worlds speed
		/// appears to be that the velocity
		/// is (car speed * 100) /(1000/ numberinterverals*3) * 2.327.
		localCarSpeed.z += accelerate;
		if (localCarSpeed.z > 3)
		{
			localCarSpeed.z = 3;
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		/// Deceleration/ Reverse
		/// One thing to consider is the top reverse speed.
		/// A quick Google search gives 
		/// a range of speeds. I think 15 miles per hour is more than reasonable.
		localCarSpeed.z += decelerate;
		if (localCarSpeed.z < -.4) {
			localCarSpeed.z = -.4;
		}
	}

	/// Update car direction
	updateDirection();

	// Recalculate the world speed.
	worldCarSpeed = computeRotatedVector(localCarSpeed, carDirection);

	/// Update the third person camera offset in the world frame.
	worldCameraOffset = computeRotatedVector(localCameraOffset, carDirection);

	// Compute the car heading.
	updateHeading();

}

/// Keyboard callback
/// Handle regular key presses, and for P2, "r" for reset, "b" for break, and escape for quit.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'r':
			carPosition.x = homePosition.x;
			carPosition.y = homePosition.y;
			carPosition.z = homePosition.z;
			carDirection = 180;
			carHeading = "N";
			localCarSpeed.z = 0;
			worldCarSpeed.x = 0;
			worldCarSpeed.z = 0;
			localCameraOffset.x = 0;
			localCameraOffset.y = 0;
			localCameraOffset.z = -6.5;
			// We need this because we need to rotate the camera back to the origin. 
			worldCameraOffset = computeRotatedVector(localCameraOffset, carDirection);

			counter = 0;
			break;
	case 'b':
		/// Add code for breaking.
		/// Set the speed to 0 for the car.
		localCarSpeed.x = 0;
		localCarSpeed.z = 0;
		worldCarSpeed.x = 0;
		worldCarSpeed.z = 0;
		break;
	case 27:
		exit(0);
		break;
	}
	// Re-render
	glutPostRedisplay();
}

/// Function to draw the entire scene.
void drawScene()
{
	// Draw terrain
	glCallList(terrainID);

	// Draw building
	//glPushMatrix();
	//glTranslatef(30, 0, 30);
	//glCallList(buildingID);
	//glPopMatrix();

	glEnable(GL_LIGHTING);

	// North-East (NS_Signal)
	glPushMatrix();
	glTranslatef(10, 0, -10.5);
	glScalef(1/3.28/12, 1/3.28/12, 1/3.28/12);
	tLightNorthSouth.setSignal(NS_Signal);
	tLightNorthSouth.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, -10);
	glRotatef(-45, 0, 1, 0);
	glCallList(surveillanceCameraID);
	glPopMatrix();

	// South-East (WE_Signal)
	glPushMatrix();
	glTranslatef(10, 0, 10.5);
	glRotatef(-90, 0, 1, 0);
	glScalef(1 / 3.28 / 12, 1 / 3.28 / 12, 1 / 3.28 / 12);
	tLightEW.setSignal(WE_Signal);
	tLightEW.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, 10);
	glRotatef(-135, 0, 1, 0);
	glCallList(surveillanceCameraID);
	glPopMatrix();

	// South-West (NS_Signal)
	glPushMatrix();
	glTranslatef(-10, 0, 10.5);
	glRotatef(-180, 0, 1, 0);
	glScalef(1 / 3.28 / 12, 1 / 3.28 / 12, 1 / 3.28 / 12);
	tLightNorthSouth.setSignal(NS_Signal);
	tLightNorthSouth.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, 10);
	glRotatef(-225, 0, 1, 0);
	glCallList(surveillanceCameraID);
	glPopMatrix();

	// North-West (WE_Signal)
	glPushMatrix();
	glTranslatef(-10, 0, -10.5);
	glRotatef(-270, 0, 1, 0);
	glScalef(1 / 3.28 / 12, 1 / 3.28 / 12, 1 / 3.28 / 12);
	tLightEW.setSignal(WE_Signal);
	tLightEW.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, -10);
	glRotatef(-315, 0, 1, 0);
	glCallList(surveillanceCameraID);
	glPopMatrix();

	// Draw the car.
	glPushMatrix();
	// Set position.
	glTranslatef(carPosition.x, carPosition.y, carPosition.z);
	// Set rotation.
	glRotatef(carDirection, 0, 1, 0);
	/// Lets scale it to the same as our traffic light.
	glScalef(1 / 3.28 / 12, 1 / 3.28 / 12, 1 / 3.28 / 12);
	/// Draw by calling ID.
	glCallList(carID);
	car.Draw();
	// Pop matrix.
	glPopMatrix();

}

/// Initialization.
/// Set up lighting, generate display lists for the surveillance camera, 
/// car, and terrain.
void init()
{
	glClearColor(0.5, 0.5, 1.0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Note that the light is defined in the eye or camera frame.
	GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};

	GLfloat ambient[] = {0.3, 0.3, 0.3, 1};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);	
	glEnable(GL_LIGHT0);

	// Generate display list for the surveillance camera.
	surveillanceCameraID = glGenLists(1);
	
	glNewList(surveillanceCameraID, GL_COMPILE);
	surveillanceCamera.Draw();
	glEndList();
	
	// Generate display list for the car.
	carID = glGenLists(1);
	glNewList(carID, GL_COMPILE);
	car.Draw();
	glEndList();

	// Generate the display list for terrain, including road and grass.
	terrainID = glGenLists(1);
	glNewList(terrainID, GL_COMPILE);
	glDisable(GL_LIGHTING);

	// Grass
	glColor3f(0, 0.7, 0);
	glBegin(GL_QUADS);
		glVertex3f(-1000, 0, 1000);
		glVertex3f(-10, 0, 1000);
		glVertex3f(-10, 0, 10);
		glVertex3f(-1000, 0, 10);

		glVertex3f(10, 0, 1000);
		glVertex3f(1000, 0, 1000);
		glVertex3f(1000, 0, 10);
		glVertex3f(10, 0, 10);

		glVertex3f(10, 0, -10);
		glVertex3f(1000, 0, -10);
		glVertex3f(1000, 0, -1000);
		glVertex3f(10, 0, -1000);

		glVertex3f(-1000, 0, -10);
		glVertex3f(-10, 0, -10);
		glVertex3f(-10, 0, -1000);
		glVertex3f(-1000, 0, -1000);
	glEnd();

	// Roads
	glBegin(GL_QUADS);
		glColor3f(0.2, 0.2, 0.2);

		glVertex3f(-10, 0, 1000);
		glVertex3f(10, 0, 1000);
		glVertex3f(10, 0, -1000);
		glVertex3f(-10, 0, -1000);

		glVertex3f(-1000, 0, 10);
		glVertex3f(1000, 0, 10);
		glVertex3f(1000, 0, -10);
		glVertex3f(-1000, 0, -10);
	glEnd();

	// Yellow line
	// Northbound
	glBegin(GL_POLYGON);
		glColor3f(1, 1, 0);
		glVertex3f(-0.075, 0.05, -10);
		glVertex3f(0.075, 0.05, -10);
		glVertex3f(0.075, 0.05, -1000);
		glVertex3f(-0.075, 0.05,-1000);
	glEnd();
	
	// Southbound
	glBegin(GL_POLYGON);
		glColor3f(1, 1, 0);
		glVertex3f(-0.075, 0.05, 1000);
		glVertex3f(0.075, 0.05,  1000);
		glVertex3f(0.075, 0.05,  10);
		glVertex3f(-0.075, 0.05, 10);
	glEnd();
	
	// West 
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	  glVertex3f(-1000, 0.05, .075);
	  glVertex3f(-10, 0.05, -.075);
	  glVertex3f(-10, 0.05, .075);
	  glVertex3f(-1000, 0.05, -.075);
	glEnd();
		
	/// East
	glBegin(GL_POLYGON);
		glColor3f(1, 1, 0);
		glVertex3f(1000, .05, -0.075);
		glVertex3f(10, .05, -.075);
		glVertex3f(10, .05, .075);
		glVertex3f(1000, .05, .075);
	glEnd();
	
	/*
		Lines are spaced 9 meters apart betwen each and 3 meters long.
	*/
	/// Dashed white line.
	/// Northbound
	//-------------------------
	glColor3f(1, 1, 1);
	for (int i=10; i+12  <= 1000; i += 12) 
	{
		glBegin(GL_POLYGON);
		glVertex3f(4.9, 0.05, i);
		glVertex3f(4.9, 0.05, i+3);
		glVertex3f(5.1, 0.05, i+3);
		glVertex3f(5.1, 0.05, i);
		glEnd();
	}

	for (int i = -10; i-12 >= -1000; i -= 12)
	{
		glBegin(GL_POLYGON);
		glVertex3f(4.9, 0.05, i);
		glVertex3f(4.9, 0.05, i - 3);
		glVertex3f(5.1, 0.05, i - 3);
		glVertex3f(5.1, 0.05, i);
		glEnd();
	}
	//-------------------------

	/// Dashed white line. 
	/// Southbound
	//-------------------------
	glColor3f(1, 1, 1);
	for (int i = 10; i+12 <= 1000; i += 12)
	{
		glBegin(GL_POLYGON);
		glVertex3f(-4.9, 0.05, i);
		glVertex3f(-4.9, 0.05, i + 3);
		glVertex3f(-5.1, 0.05, i + 3);
		glVertex3f(-5.1, 0.05, i);
		glEnd();
	}

	for (int i = -10; i-12 >= -1000; i -= 12)
	{
		glBegin(GL_POLYGON);
		glVertex3f(-4.9, 0.05, i);
		glVertex3f(-4.9, 0.05, i - 3);
		glVertex3f(-5.1, 0.05, i - 3);
		glVertex3f(-5.1, 0.05, i);
		glEnd();
	}
	//-------------------------


	/// Dashed white line. 
	/// Westbound
	//-------------------------
	glColor3f(1, 1, 1);
	for (int i = -10; i - 6 >= -1000; i -= 12)
	{
		glBegin(GL_POLYGON);
			glVertex3f(i, .05, -5.1);
			glVertex3f(i-3, .05, -5.1);
			glVertex3f(i-3, .05, -4.9);
			glVertex3f(i, .05, -4.9);
		glEnd();
	}

	for (int i = -10; i - 6 >= -1000; i -= 12)
	{
		glBegin(GL_POLYGON);
		glVertex3f(i, .05, 5.1);
		glVertex3f(i - 3, .05, 5.1);
		glVertex3f(i - 3, .05, 4.9);
		glVertex3f(i, .05, 4.9);
		glEnd();
	}

	//-------------------------


	/// Dashed white line. 
	/// Eastbound
	//-------------------------
	glColor3f(1, 1, 1);
	for (int i = 10; i + 6 <= 1000; i += 12)
	{
		glBegin(GL_POLYGON);
		glVertex3f(i, .05, -5.1);
		glVertex3f(i + 3, .05, -5.1);
		glVertex3f(i + 3, .05, -4.9);
		glVertex3f(i, .05, -4.9);
		glEnd();
	}

	for (int i = 10; i + 6 <= 1000; i += 12)
	{
		glBegin(GL_POLYGON);
		glVertex3f(i, .05, 5.1);
		glVertex3f(i + 3, .05, 5.1);
		glVertex3f(i + 3, .05, 4.9);
		glVertex3f(i, .05, 4.9);
		glEnd();
	}
	glEndList();
	//-------------------------


	// If I get some extra time add some buildings
	//buildingID = glGenLists(1);
	//glNewList(buildingID, GL_COMPILE);
	//skyscraper.Draw();
	//glEndList();

}

/// Display callback.
/// Displays 4 viewports.  For for each viewport, set up position and size, projection, 
/// and camera (ModelView matrix).
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Generate head-up display (HUD)
	stringstream ss;
	ss << "Heading: " << carHeading << "  " << "Speed: ";

	double speed; 
	/// If we're going in reverse we not
	/// really going negative mph
	if (localCarSpeed.z < 0)
		speed = localCarSpeed.z * -1;
	else
		speed = localCarSpeed.z;
	

	// I suspect there is some time wasted to drawing because my interval even out of debugging doesn't go 
	// a true 20 millisecond update!!
	// if my speed calculation is based on that it will be wrong...
	// So I multiplied it by the same scaling factor I added to the timer. Seems to work pretty good.
	// If I go straight to north from south at the North traffic light 
	// it takes 1 minute at ~33.5 mph
	// which is the correct amount of time to cover 1000 meters at that speed.
	speed = std::floor((speed * (100 / updateInterval * 3) * 2.236936) * 10) / 10;
	ss <<speed<< " m/h";

	/// Put the text string underneath the second viewport
	glColor3f(1, 1, 0);
	glWindowPos2f(winWidth / 2-125, winHeight - sHeight - 75);
	printLargeString(ss.str());

	// Setup viewport, projection, and camera for the main view.
	glViewport(0, 0, winWidth, winHeight - sHeight - 50);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (float) winWidth / (winHeight - sHeight - 50), 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Update the code here for the correct third person camera that moves with the car.
	gluLookAt(carPosition.x + worldCameraOffset.x, carPosition.y + 2 + worldCameraOffset.y, carPosition.z + worldCameraOffset.z, carPosition.x, carPosition.y + 1.5,
		carPosition.z, 0, 1, 0);
	drawScene();

	// Setup viewport, projection, and camera for the South-East camera and draw the scene again.
	// Left most view port.
	glViewport(sWidth * 0 + 25, winHeight - sHeight - 50, sWidth-25, sHeight + 50);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (float)winWidth / (winHeight - sHeight - 50), 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0, 3.364, 10, 3.0, 3.0, 0.0, 0, 1.0, 0.0);
	drawScene();

	// Setup the viewport, projection, camera for the top view and draw the scene again.
	// Ariel view
	glLoadIdentity();
	glViewport((sWidth * 1) + 25, winHeight - sHeight - 50, sWidth - 25, sHeight + 50);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)(winWidth)/ (winHeight - sHeight - 50), 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 30, 0, 0, 0, -1, 0, 1, 0);
	drawScene();

	// Setup viewport, projection, camera for the South-West camera and draw the scene again.
	glLoadIdentity();
	glViewport((sWidth * 2) + 25, winHeight - sHeight - 50, sWidth, sHeight + 50);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (float)winWidth / (winHeight - sHeight - 50), 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-10.0, 3.364, 10, 7.0, 3.0, 0.0, 0, 1.0, 0.0);
	drawScene();

	glutSwapBuffers();
	glFlush();
}

/// Updates the dynamic objects.
/// Update the car position and traffic signals.
void update()
{
	// Update car position.
	/// We calculated where the car's change of position is, added it here.
	carPosition.x += worldCarSpeed.x;
	carPosition.z += worldCarSpeed.z;

	// State machine for the traffic signals using three variables: NS_Signal, WE_Signal, and counter.
	// Add 3 to the counter since the clock seems a little slow.
	counter += 3;
	if (counter <= fiveSeconds)
	{
		NS_Signal = Green;
		WE_Signal = Red;
	}
	else if (counter > fiveSeconds && counter <= sixSeconds)
	{
		NS_Signal = Yellow;
		WE_Signal = Red;
	}
	else if (counter > sixSeconds && counter <= twelveSeconds)
	{
		NS_Signal = Red;
		if (counter > elevenSeconds && counter <= twelveSeconds)
			WE_Signal = Yellow;
		else
			WE_Signal = Green;
	}
	else if (counter > twelveSeconds)
	{
		counter = 0;
	}
}

/// Set the interval between updates.
/// \param miliseconds is the number of miliseconds passed before this function is called.  It is the third
/// parameter of glutTimerFunc().
void timer(int miliseconds)
{
	update();
	glutTimerFunc(updateInterval, timer, updateInterval);	
	glutPostRedisplay();
}

/// Main function
/// GLUT initialization, load 3D models, and register GLUT callbacks.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	winWidth = 1300, winHeight = 800;
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Traffic Simulation");
	glewInit();

	// Load the 3D models.
	/// I added a seperate traffic light for EW/NS traffic.
	/// thought I could use just the base model but that doesn't make sense
	/// If I changed one, I would change all four.
	tLightEW.ReadFile("Models/TrafficLight.obj");
	tLightNorthSouth.ReadFile("Models/TrafficLight.obj");
	car.ReadFile("Models/Honda_S2000_inch.obj");
	surveillanceCamera.ReadFile("Models/camera.obj");
	
	//skyscraper.ReadFile("Models/skyscraper.obj");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutTimerFunc(0, timer, updateInterval);
	glutMainLoop();

	system("pause");
}