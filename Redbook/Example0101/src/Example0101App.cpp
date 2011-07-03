#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rect.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Example0101App : public AppBasic {
  public:
	void setup();
	void draw();
    
    Rectf rect; 
};

void Example0101App::setup()
{
    setWindowSize( 250, 250 );
    rect.set( 50, 50, 200, 200 );
}

void Example0101App::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
    gl::color( Color( 1.0f, 1.0f, 1.0f ) );
    gl::pushMatrices();
        gl::drawSolidRect( rect );
    gl::popMatrices();
    
    // -- or
    /*
    glBegin(GL_POLYGON);  
        glVertex3f( 50.0f, 50.0f, 0.0f );
        glVertex3f( 200.0f, 50.0f, 0.0f );
        glVertex3f( 200.0f, 200.0f, 0.0f );
        glVertex3f( 50.0f, 200.0f, 0.0f );
    glEnd(); 
    */
    
    // -- original
    /*
     glClearColor (0.0, 0.0, 0.0, 0.0); 
     glClear (GL_COLOR_BUFFER_BIT); 
     glColor3f (1.0, 1.0, 1.0); 
     glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); 
     glBegin(GL_POLYGON);  
    
        glVertex3f( .25f, .25f, 0.0f );
        glVertex3f( .75f, .25f, 0.0f );
        glVertex3f( .75f, .75f, 0.0f );
        glVertex3f( .25f, .75f, 0.0f );
    
     glEnd(); 
     glFlush();
    */
}

CINDER_APP_BASIC( Example0101App, RendererGl )
