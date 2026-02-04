#include "ofMain.h"
#include "testApp.h"

int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(4,1);
    ofCreateWindow(settings);
    ofRunApp(new testApp());
}
