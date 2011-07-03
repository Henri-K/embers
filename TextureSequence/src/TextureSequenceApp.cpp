#include <string>
#include <vector>

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "TextureSequence.h"

using namespace ci;
using namespace ci::app;
using namespace std;

// -- TextureSequence example creates a sequence from the images in a supplied directory
// -- Animates the sequence to follow the mouse cursor in a smooth manner
class TextureSequenceApp : public AppBasic 
{
  public:
	void setup();
    void mouseMove( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    Vec2i previousMousePosition;
    Vec2i mousePosition;
    Vec2f targetPosition;
    Vec2i targetOffset;
    TextureSequence sequence;
    Texture currentTexture;
    float scale;
    
    bool cursorVisible;
};

void TextureSequenceApp::setup()
{
    setFrameRate( 60.0f );
    scale = 1.0f;
    mousePosition.set( 0, 0 );
    previousMousePosition.set( 0, 0 );
    
    sequence.createFromDir( getResourcePath() + "/orb_cursor/" );
    
    hideCursor();
    cursorVisible = false;
}

void TextureSequenceApp::keyDown( KeyEvent event )
{
    int code = event.getCode();
    
    switch( code )
    {
        // -- toggle fullscreen
        case KeyEvent::KEY_f:
            setFullScreen( !isFullScreen() );
            break;
        
        // -- speed up the image sequence
        case KeyEvent::KEY_RIGHT:
            sequence.setPlayheadFrameInc( sequence.getPlayheadFrameInc() + 1 );
            break;
        
        // -- slow down the image sequence
        case KeyEvent::KEY_LEFT:
            sequence.setPlayheadFrameInc( sequence.getPlayheadFrameInc() - 1 );
            break;
        
        // -- stop the image sequence
        case KeyEvent::KEY_s:
            sequence.stop();
            break;
        
        // -- toggle play/pause
        case KeyEvent::KEY_SPACE:
            if( sequence.isPlaying() ) 
            {
                sequence.pause();
            } else {
                sequence.play();
            }
            break;
            
        // -- toggle cursor visibility    
        case KeyEvent::KEY_m:
            if( cursorVisible )
            {
                cursorVisible = false;
                hideCursor();
            } else {
                cursorVisible = true;
                showCursor();
            }
            break;
    }
}

void TextureSequenceApp::mouseMove( MouseEvent event )
{
    previousMousePosition = mousePosition;
    mousePosition = event.getPos();
}

void TextureSequenceApp::update()
{
    sequence.update();
    currentTexture = sequence.getCurrentTexture();
    Area area = currentTexture.getCleanBounds();
    targetPosition += ( ( mousePosition - targetPosition ) * 0.1f );
    targetOffset = Vec2i( area.getWidth() * 0.5f, area.getHeight() * 0.5f );
    
    // -- sets the target scale based on how fast the mouse is moving
    float targetScale = ( 1.0f - ( mousePosition.distance( previousMousePosition ) / 100.0f ) );
    scale += ( targetScale - scale ) * 0.1f;
}

void TextureSequenceApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    if( currentTexture )
    {
        if( sequence.isPlaying() || sequence.isPaused() )
        {
            gl::enableAlphaBlending();
            gl::pushMatrices();
            gl::translate( targetPosition );
            gl::scale( Vec3f( scale, scale, 1.0f ) );
            gl::translate( -targetOffset );
            gl::draw( currentTexture );
            gl::popMatrices();
            gl::disableAlphaBlending();
        }
    }
}

CINDER_APP_BASIC( TextureSequenceApp, RendererGl )
