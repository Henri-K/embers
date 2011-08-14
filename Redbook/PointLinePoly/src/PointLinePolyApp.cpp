#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace ci::gl;
using namespace std;


class PointLinePolyApp : public AppBasic 
{
    
public:
    void prepareSettings( Settings *settings );
	void draw();
    
    Font font;
};

void PointLinePolyApp::prepareSettings(Settings *settings )
{
    settings->setFrameRate( 60.0f );
    settings->setWindowSize( 980, 270 );
    
    font = Font( loadResource( "pf_tempesta_seven.ttf" ), 8 );
}

void PointLinePolyApp::draw()
{
	gl::clear( Color( .1, .16, .19 ) ); 
    enableAlphaBlending();
    
    // -- square with vertical gradient
    glBegin(GL_QUADS);
    color( Color( 1, 1, 1 ) );
    glVertex2f( 0.0, 0.0);
    glVertex2f( 100.0, 0.0 );
    color( Color( 0, 0, 0 ) );
    glVertex2f( 100.0, 100.0 );
    glVertex2f( 0.0, 100.0);
    glEnd();
    
    ColorA textColor( 1, 1, 1, 1);
    gl::drawString( "GL_QUADS vert", Vec2f( 15.0f, 105.0f ), textColor, font );
    
    // -- square with horizontal gradient with second color fading to zero alpha
    glBegin(GL_QUADS);
    color( ColorA( 1, 1, 1, 1 ) );
    glVertex2f( 110.0, 0.0);
    glVertex2f( 110.0, 100.0);
    color( ColorA( 0, 0, 0, 0 ) );
    glVertex2f( 210.0, 100.0 );
    glVertex2f( 210.0, 0.0 );
    glEnd();
    
    gl::drawString( "GL_QUADS horz", Vec2f( 125.0f, 105.0f ), textColor, font );
    
    // -- simple blue circle
    color( Color( 1, 1, 1 ) );
    drawSolidCircle( Vec2f( 270.0f, 50.0f ), 50, 50 );
    gl::drawString( "gl::drawSolidCircle", Vec2f( 230.0f, 105.0f ), textColor, font );
    
    // -- yello circle using GL_POLYGON
    color( Color( 1, 1, 1 ) );
    glLineWidth( 1 );
    glBegin( GL_POLYGON );
    
    int radius = 50;
    int xpos = 380;
    int ypos = 50;
    for (int i = 0; i < 360; i++ ) 
    {
        float y = sin( ( M_PI * i ) / 180 ) * radius + ypos;
        float x = cos( ( M_PI * i ) / 180 ) * radius + xpos;
        
        glVertex2f( x, y );
    }
    glEnd();
    
    gl::drawString( "GL_POLYGON", Vec2f( 355.0f, 105.0f ), textColor, font );
    
    // -- red square using GL_QUAD_STRIP
    color( Color( 1, 1, 1 ) );
    glBegin( GL_QUADS );
    glVertex2f( 440.0, 0.0 );
    glVertex2f( 540.0, 0.0 );
    glVertex2f( 540.0, 100.0 );
    glVertex2f( 440.0, 100.0 );
    glEnd();
    
    gl::drawString( "GL_QUADS", Vec2f( 465.0f, 105.0f ), textColor, font );
    
    // -- arrowhead like shape using GL_QUAD_STRIP
    color( Color( 1, 1, 1 ) );
    glBegin( GL_QUAD_STRIP );
    glVertex2f( 550.0, 80.0 );
    glVertex2f( 550.0, 0.0 );
    glVertex2f( 600, 100.0 );
    glVertex2f( 600.0, 20.0 );
    glVertex2f( 650.0, 80.0 );
    glVertex2f( 650.0, 0.0 );
    glEnd();
    
    gl::drawString( "GL_QUAD_STRIP", Vec2f( 565.0f, 105.0f ), textColor, font );
    
    // -- disc using GL_QUAD_STRIP
    
    glBegin( GL_QUAD_STRIP );
    float outerRadius = 50.0;
    float innerRadius = 30.0;
    xpos = 710;
    
    for ( float i = 0; i <= 360; ++i )
    {
        color( ColorA( 1, 1, 1, i / 360 ) );
        float y = sin( ( M_PI * i ) / 180.0f ) * innerRadius + ypos;
        float x = cos( ( M_PI * i ) / 180.0f ) * innerRadius + xpos;
        
        glVertex2f( x, y );
        
        y = sin( ( M_PI * i ) / 180.0f ) * outerRadius + ypos;
        x = cos( ( M_PI * i ) / 180.0f ) * outerRadius + xpos;
        
        glVertex2f( x, y );
    }
    
    glEnd();   
    
    gl::drawString( "GL_QUAD_STRIP", Vec2f( 680.0f, 105.0f ), textColor, font );
    
    // -- polygon outline using GL_LINE_LOOP
    xpos = 820;
    int sides = 6;
	float degrees = 360 / sides;
	float angle = 0;
	
    color( Color( 1, 1, 1 ) );
    glBegin( GL_LINE_LOOP );
	for( int i = 0; i < sides; i++ ) 
	{
		float x = ( cos( M_PI * angle / 180 ) * ( radius ) ) + xpos;
		float y = ( sin( M_PI * angle / 180 ) * ( radius ) ) + ypos;
		
        glVertex2f( x, y );
		
        angle += degrees;
	}
    glEnd();
    gl::drawString( "GL_LINE_LOOP", Vec2f( 795.0f, 105.0f ), textColor, font );
    
    // -- polygon using PolyLine
    PolyLine<Vec2f> pl;
    angle = 0;
    xpos = 930;
    sides = 12;
    degrees = 360 / sides;
    color( Color( 1, 1, 1 ) );
    for( int i = 0; i <= sides; i++ ) 
	{
		float x = ( cos( M_PI * angle / 180 ) * ( radius ) ) + xpos;
		float y = ( sin( M_PI * angle / 180 ) * ( radius ) ) + ypos;
		
        pl.push_back( Vec2f( x, y ) );
		
        angle += degrees;
	}
    
    gl::draw( pl );
    
    gl::drawString( "gl::draw( polyline )", Vec2f( 890.0f, 105.0f ), textColor, font );
    
    // -- asterisk like shape using GL_LINES
    // -- need to set line width before calling glBegin
    glLineWidth( 10.0f );
    glBegin( GL_LINES );
    
    color( Color( 1, 1, 1 ) );
    
    // tl - br
    glVertex2i( 0, 130 );
    glVertex2i( 100, 230 );
    
    // middle vert
    glVertex2i( 50, 130 );
    glVertex2i( 50, 230 );
    
    // tr - bl
    glVertex2i( 100, 130 );
    glVertex2i( 0, 230 );
    
    // middle horz
    glVertex2i( 0, 180 );
    glVertex2i( 100, 180 );
    
    glEnd();
    
    gl::drawString( "GL_LINES", Vec2f( 30.0f, 240.0f ), textColor, font );
    
    // -- randomly placed points
    color( Color( 1, 1, 1 ) );
    for( int i = 0; i < 100; i++ )
    {
        // -- need to set point size before calling glBegin
        glPointSize( 1 + random() % 4 );
        glBegin( GL_POINTS );
        glVertex2i( random() % 110 + 110, random() % 110 + 130 );
        glEnd();
    }
    
    gl::drawString( "GL_POINTS", Vec2f( 135.0f, 240.0f ), textColor, font );
    
    // -- irregular polygon
    color( Color( 1, 1, 1 ) );
    glBegin( GL_POLYGON );
    glVertex2i( 230, 130 );
    glVertex2i( 230, 230 );
    glVertex2i( 250, 200 );
    glVertex2i( 290, 230 );
    glVertex2i( 330, 180 );
    glVertex2i( 300, 160 );
    glVertex2i( 230, 130 );
    glEnd();
    
    gl::drawString( "GL_POLYGON", Vec2f( 250.0f, 240.0f ), textColor, font );
}


CINDER_APP_BASIC( PointLinePolyApp, RendererGl )

