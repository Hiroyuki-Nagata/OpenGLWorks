//-----------------------------------------------------------------------------------------------------
// File : Main.cpp
//
// Xファイルの読み込み
//
// Date : May. 10, 2008
// Version : 1.0
// Author : Pocol
// Memo :
//-----------------------------------------------------------------------------------------------------

// Disable Warning C4996
#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif
#ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1
#endif

//
// include
//
#include <iostream>
#include "XLoader.h"
#include "Mouse.h"
using namespace std;

//
// Global Variable
//
int WindowPositionX = 100;
int WindowPositionY = 100;
int WindowWidth = 512;
int WindowHeight = 512;
char WindowTitle[] = "★　Xファイルの読み込み　★";
char Version[50];
char Vender[50];
char Renderer[50];
char FpsString[50] = {0};
double CurrentTime = 0.0;
double LastTime = 0.0;
double CurrentCount = 0.0;
double LastCount = 0.0;
int FrameCount = 0;
float Fps = 0.0f;
XModel model;
ViewCamera camera;

//
// Forward declarations
//
void Initialize();
void Shutdown();
void Display();
void Idle();
void Reshape(int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Special(int key, int x, int y);
void Render2D();
void Render3D();
void glutRenderText(void* bitmapfont, char* text);
void glutToggleFullScreen();



//----------------------------------------------------------------------------------------------------
// Name : main()
// Desc : アプリケーションのエントリーポイント
//----------------------------------------------------------------------------------------------------
int main( int argc, char **argv )
{
	//　GLUTコールバック関数などの設定
	glutInit(&argc, argv);
	glutInitWindowPosition(WindowPositionX, WindowPositionY);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(WindowTitle);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	
	//　OpenGL初期化
	Initialize();	

	//　メインループ
	glutMainLoop();

	//　後片付け
	Shutdown();

	return 0;
}


//----------------------------------------------------------------------------------------------------
// Name : Initialize()
// Desc : 初期化処理
//----------------------------------------------------------------------------------------------------
void Initialize()
{
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *vender = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);

	sprintf(Version, "OpenGL %s", version);
	sprintf(Vender, "%s", vender);
	sprintf(Renderer, "%s", renderer);

	//　カウンターの初期化
	CurrentCount = LastCount = glutGet(GLUT_ELAPSED_TIME);
	FrameCount = 0;

	//　モデルファイルの読み込み
	model.Load("Models/dosei.x");

	//　バックバッファをクリアする色の指定
	glClearColor(0.3, 0.3, 1.0, 1.0);

	//　深度テストON
	glEnable(GL_DEPTH_TEST);

	//　ライティング
	float pos[4] = { 0.0f, 10.0f, 10.0f, 1.0f };
	float amb[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	float dif[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float spe[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spe);

	//　ウィンドウを表示
	glutShowWindow();
}

//---------------------------------------------------------------------------------------------------
// Name : Idle()
// Desc : アイドリング時の処理
//---------------------------------------------------------------------------------------------------
void Idle()
{
	//　暇な時に再描画
	glutPostRedisplay();
}

//---------------------------------------------------------------------------------------------------
// Name : Reshape()
// Desc : サイズ変更
//---------------------------------------------------------------------------------------------------
void Reshape(int x, int y)
{
	//　ウィンドウサイズを保存
	WindowWidth = x;
	WindowHeight = y;

	//　サイズチェック
	if ( WindowWidth < 1 ) WindowWidth = 1;
	if ( WindowHeight < 1 ) WindowHeight = 1;

	//　ビューポートの設定
	glViewport(0, 0, WindowWidth, WindowHeight);

	//　射影行列の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 0.1, 1000.0);
}

//--------------------------------------------------------------------------------------------------
// Name : Render2D()
// Desc : 2次元シーンの描画
//--------------------------------------------------------------------------------------------------
void Render2D()
{
	bool isLighting = false;

	//　時間計測とFPS算出
	CurrentCount = glutGet(GLUT_ELAPSED_TIME);
	CurrentTime = (CurrentCount - LastCount)/1000.0;
	FrameCount++;
	if ( (CurrentTime - LastTime )>= 1.0 )
	{
		Fps = FrameCount/(CurrentTime - LastTime);
		sprintf(FpsString, "%.3f FPS", Fps);
		FrameCount = 0;
		LastTime = CurrentTime;
	}	

	//　3D　→　2D
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WindowWidth, WindowHeight, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	if ( glIsEnabled(GL_LIGHTING) )
	{
		isLighting = true;
		glDisable(GL_LIGHTING);
	}

	//　文字の描画
	glColor4f(1.0, 1.0, 1.0, 1.0); 
	glRasterPos2i(15, 15);
	glutRenderText(GLUT_BITMAP_HELVETICA_12 , Version);
	glRasterPos2i(15, 30);
	glutRenderText(GLUT_BITMAP_HELVETICA_12 , Vender);
	glRasterPos2i(15, 45);
	glutRenderText(GLUT_BITMAP_HELVETICA_12 , Renderer);
	glRasterPos2i(15, 60);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, FpsString);

	if ( !glIsEnabled(GL_LIGHTING) )
	{
		if ( isLighting )
			glEnable(GL_LIGHTING);
	}

	//　2D　→　3D
	glPopMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------------------------------------
// Name : Render3D()
// Desc : 3次元シーンの描画
//--------------------------------------------------------------------------------------------------
void Render3D()
{
	//　モデルの描画
	float scale = 1.0f/model.sphere.radius;	//　拡大係数
	model.Render(scale);	//　描画
}

//---------------------------------------------------------------------------------------------------
// Name : Display()
// Desc : ウィンドウへの描画
//---------------------------------------------------------------------------------------------------
void Display()
{
	//　バックバッファをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//　モデルビュー行列の設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//　視点の設定
	camera.Set();

	//
	glPushMatrix();
	
	//　3Dシーンの描画
	Render3D();	

	//　2Dシーンの描画
	Render2D();

	//
	glPopMatrix();

	//　ダブルバッファ
	glutSwapBuffers();

#if defined(_DEBUG) || defined(DEBUG)
	glutReportErrors();
#endif
}

//---------------------------------------------------------------------------------------------------
// Name : Mouse()
// Desc : マウス処理
//---------------------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y)
{
	camera.MouseInput(button, state, x, y);
}

//--------------------------------------------------------------------------------------------------
// Name : Motion()
// Desc : マウスドラッグ時
//-------------------------------------------------------------------------------------------------
void Motion(int x, int y)
{
	camera.MouseMotion(x, y);
}

//--------------------------------------------------------------------------------------------------
// Name : PassiveMotion()
// Desc : マウス移動時
//--------------------------------------------------------------------------------------------------
void PassiveMotion(int x, int y)
{
}

//--------------------------------------------------------------------------------------------------
// Name : Keyboard()
// Desc : キーボード処理
//--------------------------------------------------------------------------------------------------
void Keyboard(unsigned char key, int x, int y)
{
	switch ( key )
	{
	case '\033':
		exit(0);
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------
// Name : Special()
// Desc : 特殊キー処理
//--------------------------------------------------------------------------------------------------
void Special(int key, int x, int y)
{
	switch ( key )
	{
	case GLUT_KEY_F1:
		glutToggleFullScreen();
		break;

	case GLUT_KEY_F2:
		break;

	case GLUT_KEY_F3:
		break;

	case GLUT_KEY_F4:
		break;

	case GLUT_KEY_F5:
		break;

	case GLUT_KEY_F6:
		break;

	case GLUT_KEY_F7:
		break;

	case GLUT_KEY_F8:
		break;

	case GLUT_KEY_F9:
		break;

	case GLUT_KEY_F10:
		break;

	case GLUT_KEY_F11:
		break;

	case GLUT_KEY_F12:
		break;

	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;

	case GLUT_KEY_DOWN:
		break;

	case GLUT_KEY_PAGE_UP:
		break;

	case GLUT_KEY_PAGE_DOWN:
		break;

	case GLUT_KEY_HOME:
		break;

	case GLUT_KEY_END:
		break;

	case GLUT_KEY_INSERT:
		break;
	}
}

//--------------------------------------------------------------------------------------------------
// Name : Shutdown()
// Desc : 後片付け
//--------------------------------------------------------------------------------------------------
void Shutdown()
{
}

//--------------------------------------------------------------------------------------------------
// Name : glutRenderText()
// Desc : ASCII文字列の描画
//--------------------------------------------------------------------------------------------------
void glutRenderText(void* bitmapfont, char*text)
{
	for ( int i=0; i<(int)strlen(text); i++ )
		glutBitmapCharacter(bitmapfont, (int)text[i]);
}

//--------------------------------------------------------------------------------------------------
// Name : glutToggleFullScreen()
// Desc : フルスクリーンとウィンドウモードの切り替え
//--------------------------------------------------------------------------------------------------
void glutToggleFullScreen()
{
	static bool FullScreenMode = false;
	static int beforeWidth = WindowWidth;
	static int beforeHeight = WindowHeight;
	FullScreenMode ? FullScreenMode = false : FullScreenMode = true;
	if ( FullScreenMode )
	{
		beforeWidth = WindowWidth;
		beforeHeight = WindowHeight;
		glutFullScreen();
	}
	else
	{
		glutPositionWindow(WindowPositionX, WindowPositionY);
		glutReshapeWindow(beforeWidth, beforeHeight);
		glutShowWindow();
	}
}