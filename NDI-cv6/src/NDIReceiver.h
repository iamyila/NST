//
//  NDIReceiver.h
//

#pragma once

#include "ofMain.h"

#ifdef TARGET_WIN32
#include "ofxNDI.h"
#else
#include "ofxNDIVideoGrabber.h"
#include "ofxNDIReceiver.h"
#include "ofxNDIRecvStream.h"
#endif
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
		fbo.allocate(w, h, GL_RGBA);
		fbo.begin();
		ofClear(0, 0, 0, 0);
		fbo.end();
	}

	void connect(string name) {
#ifdef TARGET_WIN32

		if (receiver.OpenReceiver()) {

			int nsenders = receiver.GetSenderCount();

			if (nsenders <= 0) {
				return;
			}

			bool found = false;
			cout << "Looking for NDI source : " << name;
			for (int i = 0; i < nsenders; i++) {

				string sName = receiver.GetSenderName(i);
				found = ofIsStringInString(sName, name);
				cout << "...";

				if (found) {
					receiver.SetSenderIndex(i);	
					cout << " ok ";
					cout << receiver.GetSenderName(i) << endl;
					break;
				}
			}

			if (!found) {
				cout << " Not found" << endl;
			}
			cout << endl;
		}
#else
		if (name == "") {
			continue;
		}

		auto sources = ofxNDI::listSources();
		cout << "Looking for NDI source : " << name;

		bool found = false;
		for (auto & s : sources) {
			found = ofIsStringInString(s.p_ndi_name, name_or_url) || ofIsStringInString(s.p_url_address, name_or_url);
			cout << ".";

			if (found) {
				receiver.setup(s);
				cout << " ok!" << endl;
				video.setup(ndi->receiver);
				break;
			}
		}
		if (!found) {
			cout << " Not found" << endl;
		}
		cout << endl;
#endif
	
	}

	bool isConnected() {
#ifdef TARGET_WIN32
		return receiver.ReceiverConnected();
#else
		return receiver.isConnected();
#endif
	}

	void update() {
#ifdef TARGET_WIN32
	receiver.ReceiveImage(fbo);
#else
#endif
	}

	
	void draw(int x, int y) {
		fbo.draw(x, y, fbo.getWidth(), fbo.getHeight());
	}

	void draw(int x, int y, int w, int h) {
		fbo.draw(x, y, w, h);
	}
	
	string getInfo() {
	
		char str[256];
		if (receiver.ReceiverCreated()) {
			if (receiver.ReceiverConnected()) {
				// Show received sender information and received fps
				sprintf_s(str, 256, "%s\n%dx%d/%4.2fp\n", receiver.GetSenderName().c_str(), receiver.GetSenderWidth(), receiver.GetSenderHeight(), receiver.GetSenderFps());
			}
			else {
				// Nothing received
				sprintf_s(str, 256, "Connecting to [%s]", receiver.GetSenderName().c_str());
			}
		}
		string s(str);
		return s;
	}

//private:
#ifdef TARGET_WIN32
	ofxNDIreceiver receiver;
#else
	ofxNDIReceiver receiver;
	ofxNDIRecvVideoFrameSync video;
	//ofxNDIRecvVideoThreading video;
#endif

	ofFbo fbo;
};

