#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"
#include "SimpleGUI.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace mowa::sgui;

class SuperformulaApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    SimpleGUI * gui;
    
    float radius;
    float a;
    float b;
    int m;
    float n1;
    float n2;
    float n3;
    
    PolyLine<Vec2f> poly;
};

void SuperformulaApp::setup()
{
    setWindowSize( 480, 270 );
    
    gui = new SimpleGUI( this );
    
    gui->addParam( "m", &m, 1, 60 );
    gui->addParam( "n1", &n1, 0.0f, 5.0f );
    gui->addParam( "n2", &n2, -10.0f, 10.0f );
    gui->addParam( "n3", &n3, -10.0f, 10.0f );
    gui->addParam( "radius", &radius, 0.01f, 200.0f );
    
    a = 1.0f;
    b = 1.0f;
    m = 3;
    n1 = 1.0f;
    n2 = 1.0f;
    n3 = 1.0f;
    
    radius = 100;
}

void SuperformulaApp::mouseDown( MouseEvent event )
{
    
}

void SuperformulaApp::update()
{
    Vec2i center = getWindowCenter();

    poly = PolyLine<Vec2f>();
    
    for( float i = 0; i <= 360; ++i )
    {
        float radians = ( i * M_PI ) / 180.0f;
        float r = pow( ( pow( abs( cos( m * radians / 4 ) / a ), n2 ) + pow( abs( sin( m * radians / 4 ) / b ),  n3 ) ), -( 1 / n1 ) );
        float x = center.x + r * cos ( radians ) * radius;
        float y = center.y + r * sin ( radians ) * radius;
        
        poly.push_back( Vec2f( x, y ) );
    }
}

void SuperformulaApp::draw()
{
	gl::clear( Color( .1, .16, .19 ) );  
    
    gl::color( Color( 0, 1, 1 ) );
    
    glLineWidth( 2.0f );
    gl::draw( poly );
    
    gui->draw();
}


CINDER_APP_BASIC( SuperformulaApp, RendererGl )
