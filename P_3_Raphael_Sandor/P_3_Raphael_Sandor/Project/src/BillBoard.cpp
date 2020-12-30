#include "Billboard.h"


Billboard::Billboard(void)
{
}

Billboard::~Billboard(void)
{
}

void Billboard::ReadFile(string fileName)
{
	// Read the texture file, generate the texture object, and configure
	// the texturing parameters.
	textureImage.ReadFile(fileName);
	glGenTextures(1, &textureNumber);
	glBindTexture(GL_TEXTURE_2D, textureNumber);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage.width, textureImage.height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, textureImage.image);
}

/**
 * Sets the size of the billboard.
 * 
 * \param width		- Width of the billboard.
 * \param height	- Height of the billboard.
 */
void Billboard::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

/**
 * Sets the location in the world for the billboard.
 * 
 * \param location - Vector3 a struct of position x,y,z.
 */
void Billboard::SetLocation(Vector3 location)
{
	// we want a deep copy. Simply setting this->location = location;
	// could lead to this data being changed inadvertently 
	memcpy(&this->location, &location, sizeof(Vector3));
}

/**
 * Set the orientation of the billboard.
 * 
 * \param orientation	- the angle of the billboard.
 */
void Billboard::SetOrientation(float orientation)
{
	this->orientation = orientation;
}


/**
 * Draw the billboard.
 * 
 * This funtion draws the pilar and the actual board of the billboard.
 */
void Billboard::Draw()
{	
	// Draw the board and pillar.  Use texture mapping for the board only.
	// The pillar is drawn just using simple geometry, i.e., a rectangle.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureNumber);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(location.x, location.y, location.z);
	glRotatef(orientation, 0, 1, 0);
	glScalef(width, height, 1);

	// Front of billboard
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 0);
		glVertex3f(-.5, 0, 0);
		glTexCoord2f(1, 0);
		glVertex3f(.5, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3f(.5, 1, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-.5, 1, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(location.x, location.y, location.z);
    glRotatef(orientation, 0, 1, 0);
    glScalef(width, height, 1);
	// Right side
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glVertex3f(.5, 1, -.5);
		glVertex3f(.5, 0, -.5);
		glVertex3f(.5, 0, 0);
		glVertex3f(.5, 1, 0);
	glEnd();

	//Left side
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glVertex3f(-.5, 1, -.5);
		glVertex3f(-.5, 0, -.5);
		glVertex3f(-.5, 0, 0);
		glVertex3f(-.5, 1, 0);
	glEnd();

	// Top of billboard
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glVertex3f(-.5, 1, -.5);
		glVertex3f(-.5, 1, 0);
		glVertex3f(.5, 1, 0);
		glVertex3f(.5, 1, -.5);
	glEnd();

	// bottom of billboard
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glVertex3f(-.5, 0, -.5);
		glVertex3f(.5, 0, -.5);
		glVertex3f(-.5, 0, 0);
		glVertex3f(.5, 0, 0);
	glEnd();

	glPopMatrix();

	/// Draw the back of the billboard
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureNumber);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(location.x, location.y, location.z);	
	glRotatef(orientation, 0, 1, 0);
	glScalef(-width, height, 1);

	// back of billboard
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 0);
		glVertex3f(-.5, 0, -.5);
		glTexCoord2f(1, 0);
		glVertex3f(.5, 0, -.5);
		glTexCoord2f(1, 1);
		glVertex3f(.5, 1, -.5);
		glTexCoord2f(0, 1);
		glVertex3f(-.5, 1, -.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Draw the pillar
	//---------------------------------------------
	glPushMatrix();
	glColor3f(0.753f, 0.753f, .753f);  // Set the color to silver to look similar to a pole.

	glTranslatef(location.x, 0, location.z);
	glRotatef(orientation, 0, 1, 0);

	// Front-front pillar
	glBegin(GL_QUADS);
		glVertex3f(-.2, location.y, 0);
		glVertex3f(.2, location.y, 0);
		glVertex3f(.2, 0, 0);
		glVertex3f(-.2, 0, 0);
	glEnd();
	// Left-side of pillar
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glVertex3f(-.2, location.y, 0);
		glVertex3f(-.2, location.y, -.5);
		glVertex3f(-.2, 0, -.5);
		glVertex3f(-.2, 0, 0);
	glEnd();
	// Right-side of pillar
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(.2, location.y, 0);
	glVertex3f(.2, location.y, -.5);
	glVertex3f(.2, 0, -.5);
	glVertex3f(.2, 0, 0);
	glEnd();
	// Back-side of pillar
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(.2, location.y, 0);
	glVertex3f(.2, location.y, -.5);
	glVertex3f(.2, 0, -.5);
	glVertex3f(.2, 0, 0);
	glEnd();
	glPopMatrix();
	//---------------------------------------------
	glColor3f(1.0f, 1.0f, 1.0f);              // Set the color back to white

}
