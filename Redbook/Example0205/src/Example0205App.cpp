#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Font.h"

#include <bitset>
#include <sstream>

using namespace ci;
using namespace ci::app;
using namespace std;

class Example0205App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
    void drawOneLine( float x1, float x2, float y1, float y2 );
	void update();
	void draw();
    void drawPatternString( uint n, Vec2i pos );
    
    Font font;
};

void Example0205App::setup()
{
    // -- convert a 16 bit integer to binary
    //std::bitset<16>  x(0x0101);
    //std::cout << x << std::endl;
    font = Font( loadResource( "Andale Mono.ttf" ), 10 );
    gl::enableAlphaBlending();
}

void Example0205App::mouseDown( MouseEvent event )
{
}

void Example0205App::update()
{
}

void Example0205App::draw()
{
    int x = 10;
    int y = 10;
    int w = getWindowWidth() - 10;
    uint pattern;
	
	gl::clear( Color( 0, 0, 0 ) ); 
    
    gl::color( Color::white() );
    glLineWidth( 1.0f );
    glEnable( GL_LINE_STIPPLE );
    
    // -- dotted 
    pattern = 0x0101;
    drawPatternString( pattern, Vec2i( x, y ) );
    glLineStipple( 2, pattern );
    drawOneLine( x, y + 15, w, y + 15 );
   
    
    // -- dashed
    y += 25;
    pattern = 0x00FF;
    drawPatternString( pattern, Vec2i( x, y ) );
    glLineStipple( 1, pattern );   
    drawOneLine( x, y + 15, w, y + 15 );
    
    
    // -- dash / dot / dash
    y += 25;
    pattern = 0x1C47;
    drawPatternString( pattern, Vec2i( x, y ) );
    glLineStipple(1, 0x1C47); 
    drawOneLine( x, y + 15, w, y + 15 );
    
    
    // -- wide lines
    glLineWidth( 5.0f ); 
    
    // -- dotted 
    y += 25;
    pattern = 0x0101;
    drawPatternString( pattern, Vec2i( x, y ) );
    glLineStipple( 1, pattern ); 
    drawOneLine( x, y + 15, w, y + 15 );
    
    // -- dashed
    y += 30;
    pattern = 0x00FF;
    drawPatternString( pattern, Vec2i( x, y ) );
    glLineStipple(1, pattern); 
    drawOneLine( x, y + 15 , w, y + 15 );
    
    // -- dash / dot / dash
    y += 30;
    pattern = 0x1C47;
    drawPatternString( pattern, Vec2i( x, y ) );
    glLineStipple( 1, pattern ); 
    drawOneLine( x, y + 15, w, y + 15 ); 
     
    // -- reset line width
    glLineWidth( 1.0f );
    
    // -- line strip ( not using drawOneLine() )
    // -- dash / dot / dash
    y += 30;
    pattern = 0x1C47;
    drawPatternString( pattern, Vec2i( x, y ) );
    glLineStipple ( 1, pattern );
    glBegin ( GL_LINE_STRIP ); 
    for ( int i = 0; i < 6; i++ )
        glVertex2f ( x + ( i * ( w / 5.0f ) ), y + 15 );
    glEnd ();
    
    // -- dash / dot / dash
    y += 25;
    drawPatternString( pattern, Vec2i( x, y ) );
    for ( int i = 0; i < 6; i++) 
        drawOneLine ( x + ( i * ( w / 6.0f ) ), y + 15, x + ( ( i + 1.0f ) * ( w / 6.0f ) ), y + 15 );
    
    // -- stretch factor
    // -- dash / dot / dash
    y += 25;
    pattern = 0x1C47;
    drawPatternString( pattern, Vec2i( x, y ) );
    glLineStipple ( 5, pattern );
    drawOneLine ( x, y + 15, w, y + 15 );
    glDisable ( GL_LINE_STIPPLE );
}

void Example0205App::drawOneLine( float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        glVertex2f ( x1, y1 ); 
        glVertex2f ( x2, y2 ); 
    glEnd();
}

void Example0205App::drawPatternString( uint n, Vec2i pos )
{
    std::bitset<16>  x(n);
    stringstream s;
    s << n;
    s << ": ";
    s << x;
    
    gl::drawString( s.str(), pos, Color( 0, 1, 1 ), font );
}


CINDER_APP_BASIC( Example0205App, RendererGl )
