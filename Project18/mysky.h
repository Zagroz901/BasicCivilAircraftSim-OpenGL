#pragma once
class MySkyBox
{
public:
	
	
	
	float x,y,z;
	int SKYBoxFRONT, SKYBoxBACK, SKYBoxLEFT, SKYBoxRIGHT, SKYBoxUP, SKYBoxDOWN;

public:

	MySkyBox()
	{
		this->x=0;
		this->y=0;
		this->z=0;
		
		
	}

	~MySkyBox(void)
	{
	}

	void init_skybox()
	{
	  
		SKYBoxFRONT = LoadTexture("assets/textuers/clouds1/front.bmp", 255);
		SKYBoxBACK = LoadTexture("assets/textuers/clouds1/back.bmp", 255);
		SKYBoxLEFT = LoadTexture("assets/textuers/clouds1/right.bmp", 255);
		SKYBoxRIGHT = LoadTexture("assets/textuers/clouds1/left.bmp", 255);
		SKYBoxUP = LoadTexture("assets/textuers/clouds1/up.bmp", 255);
		SKYBoxDOWN = LoadTexture("assets/textuers/clouds1/down.bmp", 255);
	}

	void DrawTheSky(float x, float y, float z, float width, float height, float length)
{


	glPushMatrix();
	
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;
	float newx = x + width;
	float newy = y + height;
	float newz = z + length;


	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SKYBoxFRONT);
	
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, newz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, newy, newz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(newx, newy, newz);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(newx, y, newz);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SKYBoxBACK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(newx, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(newx, newy, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, newy, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SKYBoxLEFT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, newy, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, newy, newz);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, newz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SKYBoxRIGHT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(newx, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(newx, y, newz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(newx, newy, newz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(newx, newy, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SKYBoxUP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(newx, newy, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(newx, newy, newz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, newy, newz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, newy, z);
	glEnd();

	// Draw Down side

	glBindTexture(GL_TEXTURE_2D, SKYBoxDOWN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, newz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, newz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	glColor3f(1, 1, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPopMatrix();
}

};

