#include "ofMain.h"
#include "ofApp.h"

int main() {
    ofGLFWWindowSettings settings;
    settings.setSize(1280, 720);
    settings.setGLVersion(3, 2);
    settings.title = "NST Cat Model Test";
    ofCreateWindow(settings);
    ofRunApp(std::make_shared<ofApp>());
    ofRunMainLoop();
}
