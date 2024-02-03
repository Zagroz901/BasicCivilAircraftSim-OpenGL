#include<iostream>
#include <windows.h>		// Header File For Windows
#include <gl/GL.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <glut.h>			// Header File For The GLut32 Library
#include <fstream>
#include <math.h>
#include "math3d.h"
#include "texture.h"
#include <glaux.h>
#include "camera.h"
#include "Model_3DS.h"
#include "GLTexture.h" 
#include "mysky.h"
#include "Shape.h" 
int frameNum = 1;


Shape sh;
void drawShape();
void shipKeys();
int DrawGLScene(GLvoid);



//include lib file
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"GLAUX.LIB")

using namespace std;

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE; 	// Fullscreen Flag Set To Fullscreen Mode By Default

Camera cam;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
//******************************************
// ============= Members Definition =========

float backx=0,changex=0;

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}
	glViewport(0,0,width,height);						// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,10000.0f);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

Model_3DS *tree;
MySkyBox sky_box;



void drawShape(){
	glPushMatrix();{
		glTranslatef(sh.pos.x, sh.pos.y,sh.pos.z);
		//Apos
		//double pitch = sh.Apos.x;
		//double yaw = sh.Apos.y;
		//double roll = sh.Apos.z;

		glRotated(sh.pitch,1,0,0 );
		glRotated(sh.yaw,0,1,0 );
		glRotated(sh.roll,0,0,1 );
		tree->scale = 0.06;
		tree->Draw();
	}
	glPopMatrix();


}
int landTexture;
int runwayTexture;
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{

	//sh.pos.x = 30;
	//sh.pos.y = 3;
	//sh.pos.z= 10;
	//sh.v.x = 3;
	//sh.v.y = 0;
	//sh.v.z = -0.0001;

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations	
	glEnable(GL_TEXTURE_2D);

	//texture here
	//loading sky box textuers
	sky_box.init_skybox();
	landTexture = LoadTexture("assets/textuers/grass.bmp", 255);
	runwayTexture = LoadTexture("assets/textuers/runway5.bmp", 255);

	//*********************
	//models here
	//  loading fighter jet model and its textures  
	tree=new Model_3DS();
	tree->Load("assets/models/Airplane.3DS");
	tree->scale = 0.1;
	GLTexture tree_tex,tree1_tex ,  tree2_tex , tree3_tex ,tree4_tex , tree5_tex;
	tree_tex.LoadBMP("assets\\models\\jet1.bmp");
	tree1_tex.LoadBMP("assets\\models\\jet2.bmp");
	tree2_tex.LoadBMP("assets\\models\\jet3.bmp");
	tree3_tex.LoadBMP("assets\\models\\jet4.bmp");
	tree->Materials[0].tex=tree_tex;
	tree->Materials[3].tex=tree1_tex;
	tree->Materials[2].tex=tree2_tex;
	tree->Materials[1].tex=tree3_tex;
	tree->scale = 0.5;
	//****************************
	//camera here
	cam.MoveForward(-15);

	return true;										// Initialization Went OK
}

int main( HINSTANCE hInstance, HINSTANCE hPrevInstance,
		 LPSTR lpCmdLine, int nCmdShow)
{
	cout<<"Shape\n";
	return WinMain(hInstance,hPrevInstance,lpCmdLine,nCmdShow);;
}




void draw_Env(){
	sky_box.DrawTheSky(0, 10 ,0,16000, 16000, 16000);
	// Draw the land


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, landTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(200, 0); 	glVertex3f(-5000.0f, 0.0f, -5000.0f);
	glTexCoord2f(200, 200);	 glVertex3f(-5000.0f, 0.0f,5000.0f);
	glTexCoord2f(0, 200);  	 glVertex3f(5000.0f, 0.0f, 5000.0f);
	glTexCoord2f(0, 0);   	glVertex3f(5000.0f, 0.0f, -5000.0f);
	glEnd();
	glPopMatrix();


	//******************

	// Draw the runway
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, runwayTexture);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(6, 0);	glVertex3f(-60.0f, 0.6f, 0.0f);
	glTexCoord2f(6, 6);	glVertex3f(+60.0f, 0.6f, 0.0f);
	glTexCoord2f(0, 6);	glVertex3f(+60.0f, 0.6f, +2500.0f);
	glTexCoord2f(0, 0);	glVertex3f(-60.0f, 0.6f, +2500.0f);
	glEnd();
	//the midlle line in the runway 
	glBegin(GL_QUADS);
	glVertex3f(-2.0f, 0.7f, 0.0f);
	glVertex3f(+2.0f, 0.7f, 0.0f);
	glVertex3f(+2.0f, 0.7f, +2500.0f);
	glVertex3f(-2.0f, 0.7f, +2500.0f);
	glEnd();
	glPopMatrix();
}
void Draw()
{
	glPushMatrix();
	{
		tree->pos.z=1-50;
		tree->pos.x=1-160;
		tree->pos.y=1-125;
	}
	glPopMatrix();
}

// This function handles the user input for controlling the aircraft.
void shipKeys() {
   // double d = 0.001;  // The increment value for control adjustments
    
    // Control the pitch, roll, and yaw of the plane using keyboard inputs
    if (keys['W']) {
		sh.elevator = 1;  // Pitch up
    }else if (keys['S']) {
        sh.elevator = -1;  // Pitch down
	} else
	{
		sh.elevator = 0;

	}

    if (keys['A']) {
		sh.aileron = 1;  // Roll left
    }
    else if (keys['D']) {
		sh.aileron = -1;  // Roll right
    }else
	{
		sh.aileron = 0;
	}


    if (keys['Q']) {
		sh.rudder = 1;  // Yaw left
    }
    else if (keys['E']) {
		sh.rudder = -1;  // Yaw right
	}else
	{
		sh.rudder = 0;  

	}

   

    // Manage the aircraft's fuel level
    if (keys['P']) {
        sh.decrease_fuel();  // Reduce fuel
    }
    if (keys['I']) {
        sh.increase_fuel();  // Increase fuel
    }
}


int DrawGLScene(GLvoid)									
{	
	//cout << endl << frameNum++ << endl ;
	//Sleep(10);
	//system("cls");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	cam.Render();
	cam.Control_With_KeyBoard(keys);
	glColor3f(1.0f,1.0f,1.0f);

	//here we draw the Sky Box
	glPushMatrix(); 
	draw_Env();
	glPopMatrix();
	//Fighte Jet Draw

	shipKeys();
	glPushMatrix();
	{
		sh.flyPlaneFly();
		drawShape();
	}
	glPopMatrix();
	//sh.v.print("v ");

	cam.Position.x = sh.pos.x ;
	cam.Position.y = sh.pos.y + 2;
	cam.Position.z = sh.pos.z + 20;

	return true;

} 

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right-WindowRect.left,	// Calculate Window Width
		WindowRect.bottom-WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
						 UINT	uMsg,			// Message For This Window
						 WPARAM	wParam,			// Additional Message Information
						 LPARAM	lParam){
							 switch (uMsg)									// Check For Windows Messages
							 {
							 case WM_ACTIVATE:							// Watch For Window Activate Message
								 {
									 if (!HIWORD(wParam))					// Check Minimization State
									 {
										 active=TRUE;						// Program Is Active
									 }
									 else
									 {
										 active=FALSE;						// Program Is No Longer Active
									 }

									 return 0;								// Return To The Message Loop
								 }

							 case WM_SYSCOMMAND:							// Intercept System Commands
								 {
									 switch (wParam)							// Check System Calls
									 {
									 case SC_SCREENSAVE:					// Screensaver Trying To Start?
									 case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
										 return 0;							// Prevent From Happening
									 }
									 break;									// Exit
								 }

							 case WM_CLOSE:								// Did We Receive A Close Message?
								 {
									 PostQuitMessage(0);						// Send A Quit Message
									 return 0;								// Jump Back
								 }

							 case WM_KEYDOWN:							// Is A Key Being Held Down?
								 {
									 keys[wParam] = TRUE;					// If So, Mark It As TRUE
									 return 0;								// Jump Back
								 }

							 case WM_KEYUP:								// Has A Key Been Released?
								 {
									 keys[wParam] = FALSE;					// If So, Mark It As FALSE
									 return 0;								// Jump Back
								 }

							 case WM_SIZE:								// Resize The OpenGL Window
								 {
									 ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
									 return 0;								// Jump Back
								 }
							 }

							 // Pass All Unhandled Messages To DefWindowProc
							 return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
				   HINSTANCE	hPrevInstance,		// Previous Instance
				   LPSTR		lpCmdLine,			// Command Line Parameters
				   int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	//{
	fullscreen=FALSE;							// Windowed Mode
	//}

	// Create Our OpenGL Window
	if (!CreateGLWindow("train",700,500,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done=TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}
			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("Rami shaya Fighter jet simulation",700,500,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}

			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}


