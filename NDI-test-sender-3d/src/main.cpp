#include "ofMain.h"
#include "ofApp.h"

int main() {
    ofGLFWWindowSettings settings;
    settings.setSize(1280, 720);
    settings.setGLVersion(3, 2);
    settings.title = "NST NDI Motion Test Sender";
    ofCreateWindow(settings);
    ofRunApp(std::make_shared<ofApp>());
    ofRunMainLoop();
}
