//
//  NDIReceiver.h
//

#pragma once

#include "ofMain.h"

#include "ofxNDIVideoGrabber.h"
#include "ofxNDIReceiver.h"
#include "ofxNDIRecvStream.h"
using namespace std;

class NDIReceiver {

public:

	NDIReceiver() {};
	~NDIReceiver() {};

	void setup(string name, int w, int h) {
		allocate(w, h);
	}

	void allocate(int w, int h) {
		cout << "allocate Receiver: " << w << ", " << h << endl;
		pixels.allocate(w, h, GL_RGBA);
	}

	void connect(string name) {
		if (name == "") {
			return;
		}

		auto sources = ofxNDI::listSources();
		cout << "Looking for NDI source : " << name;

		bool found = false;
		for (auto& s : sources) {
			found = ofIsStringInString(s.p_ndi_name, name) || ofIsStringInString(s.p_url_address, name);
			cout << ".";

			if (found) {
				receiver.setup(s);
				cout << " ok!" << endl;
				video.setup(receiver);
				break;
			}
		}
		if (!found) {
			cout << " Not found" << endl;
		}
		cout << endl;

	}

	bool isConnected() {
		return receiver.isConnected();
	}

	bool update() {
		if (receiver.isConnected()) {
			video.update();

			if (video.isFrameNew()) {
				auto& frame = video.getFrame();
				int xres = frame.xres;
				int yres = frame.yres;

				if (xres != 0 && yres != 0) {
					video.decodeTo(pixels);
					return true;
				}
			}
		}
		return false;
	}

	ofPixels& getPixels() {
		return pixels;
	}

	void draw(int x, int y) {
		//fbo.draw(x, y, fbo.getWidth(), fbo.getHeight());
	}

	void draw(int x, int y, int w, int h) {
		//fbo.draw(x, y, w, h);
	}

	void disconnect() {
		receiver.disconnect();
	}

private:
	ofxNDIReceiver receiver;
	ofxNDIRecvVideoFrameSync video;
	//ofxNDIRecvVideoThreading video;

	ofPixels pixels;
};
