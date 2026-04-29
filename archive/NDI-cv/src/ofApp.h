#pragma once

#include "ofMain.h"
#include "ofxNDIVideoGrabber.h"
#include "ofxNDIReceiver.h"
#include "ofxNDIRecvStream.h"
#include "ofxOpenCv.h"

#include "ofxOsc.h"

#include "ofxGui.h"

// send host (aka ip address)
#define HOST "localhost"

/// send port
#define PORT 12345


#define MAX_CAMS 10

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
    void NDIconnect();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    void exit();
    
    void NDIConnectButtonPressed();
    ofxCvGrayscaleImage     grayImage[MAX_CAMS];
    ofxCvGrayscaleImage     grayImageFixed[MAX_CAMS];
    ofxCvGrayscaleImage     grayBg[MAX_CAMS];
    ofxCvGrayscaleImage     grayDiff[MAX_CAMS];
    ofxCvContourFinder     contourFinder[MAX_CAMS];
    
    ofxIntSlider fps;
    bool                bLearnBakground[MAX_CAMS];

    float camWidth;
    float camHeight;
    int camsUsed;
    char NDI_streams[10][32] = { "sender1", "sender2", "sender3", "sender4", "sender5", "sender6","sender7", "ALASTAIR-MCNEILL-BROWNS-IPHONE", "OBS", "OBS Preview" };
    
    float scaleX, scaleY;
    
    ofTrueTypeFont font;
    ofxOscSender oscSender;
    ofImage img;
    
    bool exitSender[MAX_CAMS];
    
    ofVec2f blobCenter[MAX_CAMS];
    float area[MAX_CAMS];
    float oldX, oldY;
    
    ofxIntSlider threshold;
    ofxIntSlider frameCounterBGSet;
    ofxIntSlider minBlobSize;
    ofxIntSlider maxBlobSize;
    
    ofxColorSlider color;
    ofxVec2Slider center;
    ofxIntSlider circleResolution;
    ofxToggle showNDI[MAX_CAMS];
    ofxToggle bgTeachnique[MAX_CAMS];
    
    ofxButton twoCircles;
    ofxButton NDIConnectButton;
    ofxLabel screenSize;
    
    ofxPanel gui;
    
    int moveImage;
    ofSoundPlayer ring;
    
    bool bHide;

    int showInRows;
    
    float frameCounter;
private:

    ofxNDIReceiver receiver_[MAX_CAMS];
    ofxNDIRecvVideoFrameSync video_[MAX_CAMS];
    ofPixels pixels_[MAX_CAMS];

};
