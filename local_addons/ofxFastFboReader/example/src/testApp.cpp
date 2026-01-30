#include "testApp.h"

//#include "ofxTimeMeasurements.h"
#include "ofxFastFboReader.h"

ofFbo fbo;

int mode = 0;

ofxFastFboReader reader;

ofImage image;
ofFloatPixels pix;

//--------------------------------------------------------------
void testApp::setup()
{
//	ofSetFrameRate(60);
//	ofSetVerticalSync(true);
	
	ofBackground(0);
    ofSetWindowShape(500, 500);
	fbo.allocate(500, 500, GL_RGB);
}

//--------------------------------------------------------------
void testApp::update()
{

	fbo.begin();
    ofFloatColor c(0.1, 0.2, 0.3, 1);
    ofClear(c);
	fbo.end();
	
    if(reader.readToPixels(fbo, pix, OF_IMAGE_COLOR)){
        for(int i=0; i<pix.getWidth()*pix.getHeight(); i++){
            ofFloatColor c = pix.getColor(i);
            printf("i %05d : %0.1f, %0.1f, %0.1f, %0.1f\n", i, c.r, c.g, c.b, c.a);
        }
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofDrawBitmapString("press space to change method", 10, 18);
    
    
    ofTexture tex;
    tex.loadData(pix);
    tex.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	if (key == ' ')
	{
		mode++;
		mode = mode % 2;
	}
	else if (key == '1')
	{
		reader.setAsync(true);
	}
	else if (key == '2')
	{
		reader.setAsync(false);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
