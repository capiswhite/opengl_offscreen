

#define Width  800
#define Height 800

#include <iostream>
#include <EGL/egl.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <FreeImage.h>
//#include <GL/glut.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <memory.h>

using namespace std;

#define BMP_Header_Length 54

void grab(int FBO);
void setCube();
void drawCube();
void Rectangle();

int main(int argc, char *argv[])
{

    EGLDisplay display;
	EGLConfig config;
	EGLContext context;
	EGLSurface surface;
	//NativeWindowType native_window;
	EGLint num_config;

	const EGLint attribute_list[] = {
		EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
		EGL_BLUE_SIZE, 4,
		EGL_GREEN_SIZE, 4,
		EGL_RED_SIZE, 4,
		EGL_DEPTH_SIZE, 4,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
		EGL_NONE
	};
	const int pbufferWidth = Width;
	const int pbufferHeight = Height;
	const EGLint pbufferAttribs[] = {
		  EGL_WIDTH, pbufferWidth,
		  EGL_HEIGHT, pbufferHeight,
		  EGL_NONE
	};


	//* get an EGL display connection */
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (display == EGL_NO_DISPLAY)
	{
		cout << "Get display fail." << endl;
		return 0;
	}
	cout << display << endl;

	/* initialize the EGL display connection */
	EGLint major = 0;
	EGLint minor = 1;

	if (eglInitialize(display, &major, &minor))
	{
		cout << "ELG" << (EGLint)major << "." << (EGLint)minor << endl;
	}
	else
	{
		EGLint  err = eglGetError();

		cout << "eglInitialize fail." << endl;
		cout << err << endl;
	}


	/* get an appropriate EGL frame buffer configuration */
	if (!eglChooseConfig(display, attribute_list, &config, 1, &num_config))
	{
		cout << "eglChooseConfig fail." << endl;
	}
	else
	{

	}

	//EGLint attribute_list_2[] = {
	//EGL_CONTEXT_CLIENT_VERSION, 3,
	//EGL_NONE
	//};

	///* create an EGL rendering context */
	context = eglCreateContext(display, config, 0 , NULL);

	if (context == 0)
	{
		cout << "Creat Contest fail." << endl;
		//return false;
	}
	else
	{
		cout << "Susscess Creat Contest" << endl;
	}



	/* create a surface */
	//native_window = createNativeWindow();
	eglBindAPI(EGL_OPENGL_API);

	
    //EGLNativePixmapType pixmap;
    //surface = eglCreatePixmapSurface(display, config, pbufferAttribs);

    /* create an EGL Pbuff surface */
    surface = eglCreatePbufferSurface (display, config, pbufferAttribs);


	EGLint w,h;
	if(!eglQuerySurface(display ,surface,EGL_WIDTH,&w)||!eglQuerySurface(display ,surface,EGL_HEIGHT,&h))
	{
		cout << "Creat surface fail." << endl;
		//return false;
	}
	else 
	{
		cout << "Susscess Creat surface." << surface << endl;
	}


	/* connect the context to the surface */

	if (!eglMakeCurrent(display, surface, surface, context))
	{
		cout << "Connect fail." << endl;
		return 0;
	} 

    //glutInit(&argc, argv);
    //glutInitWindowSize(1, 1);
    //glutInitDisplayMode(GLUT_RGBA);

    //int window  = glutCreateWindow("project of openGL");
    //glutDestroyWindow(window);
    //glGetIntegerv(GL_AUX_BUFFERES, IntV);

    //glutDisplayFunc(Rectangle);
    //glutSwapBuffers(); 

    //glutMainLoop();

    //cout << "Susscess GLUT." << endl;

    //glewInit();

    //unsigned int m_tex = 0;
    //unsigned int m_FboID = 0;
	//unsigned int m_RboID = 0;
    
	// glGenTextures(1,&m_tex);
	// glBindTexture(GL_TEXTURE_2D,m_tex);
    // glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Width,Height,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL); 
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 

	// glGenRenderbuffers(1,&m_RboID);
	// glBindRenderbuffer(GL_RENDERBUFFER,m_RboID);
	// glRenderbufferStorageEXT(GL_RENDERBUFFER,GL_DEPTH_COMPONENT, Width, Height);
	// glBindRenderbufferEXT(GL_RENDERBUFFER,0);

	// glGenFramebuffersEXT(1,&m_FboID);
	// glBindFramebufferEXT(GL_FRAMEBUFFER,m_FboID);
	// glFramebufferTexture2DEXT(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_tex,0);
	// glFramebufferRenderbufferEXT(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,m_RboID);
	// GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
    // glBindFramebuffer(GL_FRAMEBUFFER,0);

    glClearColor(1.0f, 0.0f, 1.0f , 1.0f);
    glClearDepth(1.0);

    
    // glBindFramebuffer(GL_DRAW_FRAMEBUFFER,m_FboID);
    glViewport(0, 0, Width, Height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    //gluOrtho2D(0, 30,0, 20);
    
    glColor4f(1.0f, 1.0f, 1.0f , 1.0f);
    //glLineWidth(10);
    //glDrawBuffer(GL_FRONT);
    GLfloat  vertices_tri[] ={0.10f, 0.0f , 0.2f,
                              0.5f, 0.10f , 0.3f,
                            0.40f, 0.40f, 0.4f };
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices_tri);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    glFlush();
    glDisableClientState(GL_VERTEX_ARRAY);
    //glBegin(GL_TRIANGLES);
    //glVertex3f(0.10f, 0.0f , 0.2f );
    //glVertex3f(0.5f, 0.10f , 0.3f ) ;
    //glVertex3f(0.40f, 0.40f, 0.4f );
    //glEnd();
    //glFlush();
    
    // glColor4f(0.0f, 0.0f, 0.0f , 0.5f);
    // //glDrawBuffer(GL_BACK);
    // glBegin(GL_TRIANGLES);
    // glVertex2f(0.20f, 0.10f);
    // glVertex2f(0.25f, 0.10f);
    // glVertex2f(0.60f, 0.50f);
    // glEnd();
    // glFlush();
    //glutSwapBuffers();
    


    //glBindFramebuffer(GL_READ_FRAMEBUFFER,m_FboID);
    //glViewport(0, 0, Width, Height);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glBlitFramebuffer(0,0,Width,Height,0,0,Width,Height,GL_COLOR_BUFFER_BIT,GL_NEAREST);
    //glBlitFramebuffer(0,0,Width,Height,0,0, 200, 200 ,GL_COLOR_BUFFER_BIT,GL_NEAREST);
    //glBindFramebuffer(GL_READ_FRAMEBUFFER,m_FboID);
    //glFlush();
    //eglSwapBuffers(display, surface);

    glColor4f(1.0f, 1.0f, 0.0f , 1.0f);
    GLfloat vertices[] =   {0.0f, 0.0f, 0.0f,
                            0.0f, 0.2f, 0.0f,
                            0.0f, 0.2f, 0.2f,
                            0.0f, 0.0f, 0.2f,
                            0.2f, 0.0f, 0.0f,
                            0.2f, 0.2f, 0.0f,
                            0.2f, 0.2f, 0.2f ,
                            0.2f, 0.0f, 0.2f};          // 8个顶点坐标
                            
    GLubyte indices[] = {0,1,2, 2,3,0,   // 索引数组
                         0,3,4, 3,4,7,
                         0,5,1, 4,5,0,
                         4,6,7, 4,5,6,
                         5,2,1, 5,2,6,
                         7,3,2, 7,6,2};
    glLoadIdentity();
    gluLookAt( 0.5, 0.5 ,  0.5 , 0.2, 0.3, 0.4 ,  0, 1, 0);
    // 激活顶点数组
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
 
    // 绘制立方体
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
 
    // 禁用顶点数组
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();



    //glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
    grab(0);


    eglDestroySurface(display, surface);
    eglDestroyContext(display, context);
    eglTerminate(display);

    return 0;

}


void grab(int FBO)
{
    GLint viewPort[4] = {0};
    
    glGetIntegerv(GL_VIEWPORT, viewPort);

    unsigned char *mpixels =new unsigned char[Width * Height * 4];//Width和Height为所要保存的屏幕图像的宽度与高度
    cout<< FBO <<endl;
    //glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);   
    //eglGetCurrentSurface(EGL_READ);

    glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3], GL_RGBA, GL_UNSIGNED_BYTE, mpixels);   
    //glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[0]);

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    //glBindFramebuffer(GL_READ_FRAMEBUFFER,0);                  
    for(int i=0; i<(int)Width*Height*4; i+=4)
    { 
        //cout<< (int)mpixels[i] <<" "<< (int)mpixels[i+1] <<" "<<(int)mpixels[i+2]<<" "<<(int)mpixels[i+3] <<endl; 
        mpixels[i] ^= mpixels[i+2] ^= mpixels[i] ^= mpixels[i+2];
    }

    FreeImage_Initialise();
    FIBITMAP* bitmap =FreeImage_Allocate(Width, Height, 32, 8, 8, 8);
 
    for(int y = 0 ;y < FreeImage_GetHeight(bitmap); y++)
    {
        BYTE *bits = FreeImage_GetScanLine(bitmap, y);
        for(int x = 0; x < FreeImage_GetWidth(bitmap); x++)
        {
            bits[0] = mpixels[(y*Width+x)*4+0];
            bits[1] = mpixels[(y*Width+x)*4+1];
            bits[2] = mpixels[(y*Width+x)*4+2];
            bits[3] = 255;
            bits += 4;
        }
 
    }
    char filename[50];
    time_t timep;
    time (&timep);
    snprintf(filename,50,"test_%d_%s.png", FBO , ctime(&timep));  
    bool bSuccess = FreeImage_Save(FIF_PNG, bitmap, filename , PNG_DEFAULT);
    FreeImage_Unload(bitmap);
    FreeImage_DeInitialise();
}

void setCube(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);//设置黑色
    glLoadIdentity();//加载单位矩阵
    gluLookAt(6, 0, 2.5, 0, 0, 0, 1, 1, 0);
    //前三个参数设置观察者的观察位置，中三个参数设置观察点的位置，后三个参数设置观察者的观察方向
    glLineWidth(2.0f);//设置边的像素宽，默认为1.0f
    glutWireCube(2.0);
    glFlush();
}
 
void drawCube(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(4, 0, 1.5, 0, 0, 0, 1, 1, 0);
 
    //绘制正方体的面
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
        //---1---
        glNormal3f(-1, 0, 0);//设置点的法向量
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        //---2---
        glNormal3f(-1, 0, 0);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        //---3---
        glNormal3f(0, 1, 0);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        //---4---
        glNormal3f(0, -1, 0);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        //---5---
        glNormal3f(0, 0, 1);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        //---6---
        glNormal3f(0, 0, -1);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
    glEnd();
 
    //draw
    glColor3f(0, 0, 0);
    glLineWidth(2.0f);
    //绘制正方体的边
    glBegin(GL_LINES);
        //---1---
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        //---2---
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        //---3---
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        //---4---
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    glFlush();
}

void Rectangle(void) {
    //gl开头的函数为openGL的标准函数
    
    //（使用当前缓冲区的值来）清除指定的缓冲区
    glClearColor(0.5f, 0.2f, 0.3f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.5f, 0.0f);
    //画矩形
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
 
    //画三角
    glColor3f(0.0f, 0.0f, 0.7f);
    glLineWidth(10);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.10f, 0.0f);
    glVertex2f(0.5f, 0.10f);
    glVertex2f(0.40f, 0.40f);
    glEnd();

    //画直线
    glBegin(GL_LINES);
        glVertex2f(0.8f, 0.8f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
 
    //刷新缓冲，保证绘图命令能被执行
    glFlush();
}
