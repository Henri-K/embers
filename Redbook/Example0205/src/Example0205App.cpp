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
	void draw();
    void drawPatternString( uint n, Vec2i pos );
    void drawOneLine( float x1, float x2, float y1, float y2 );
    
    Font font;
};

void Example0205App::setup()
{
    font = Font( loadResource( "pf_tempesta_seven.ttf" ), 8 );
    gl::enableAlphaBlending();
}

void Example0205App::draw()
{
    int x = 10;
    int y = 10;
    int w = getWindowWidth() - 10;
    uint pattern;
	
	gl::clear( Color( .1, .16, .19 ) ); 
    
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

// -- Draws a single line segment
void Example0205App::drawOneLine( float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        glVertex2f ( x1, y1 ); 
        glVertex2f ( x2, y2 ); 
    glEnd();
}

// -- Draws the binary representation of the stipple to the screen above the actual line
void Example0205App::drawPatternString( uint n, Vec2i pos )
{
    // -- convert a 16 bit integer to binary
    std::bitset<16>  x(n);
    stringstream s;
    s << n;
    s << ": ";
    s << x;
    
    gl::drawString( s.str(), pos, Color( 0, 1, 1 ), font );
}


CINDER_APP_BASIC( Example0205App, RendererGl )
