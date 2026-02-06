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

	string connect(string name /*, bool highestBandwidth*/) {
		if (name == "") {
			return "";
		}

		auto sources = ofxNDI::listSources();
		cout << "Listing existing NDI sources..\n\n";
		cout << "Found " << sources.size() << " sources" << "\n";
		for (auto& s : sources) {
			cout << s.p_ndi_name << "\n";
		}

		cout << "\n";
		cout << "Try to connect to " << name << " ...";

		bool found = false;
		string longName = "";
		string nameUpper = ofToUpper(name);
		for (auto& s : sources) {
			found = ofIsStringInString(ofToUpper(s.p_ndi_name), nameUpper);
			
			if (found) {
				longName = s.p_ndi_name;
				/*

				lowest bandwidth automatically use 640x360
				no matter what resolution we send from OBS
				
				ofxNDIReceiver::Settings settings;
				settings.bandwidth = highestBandwidth
					? NDIlib_recv_bandwidth_highest
					: NDIlib_recv_bandwidth_lowest;

				bool ok= receiver.setup(s, settings);
				*/
				bool ok = receiver.setup(s);

				if (ok) {
					cout << " OK!" << '\n';
					/*cout << "Connected with " 
						 << (highestBandwidth ? "Highest" : "Lowest") 
						 << " Bandwidth" << '\n';					
					*/
					video.setup(receiver);
					break;
				};
			}
		}
		cout << endl;
		if (!found) {
			cout << " Not found" << endl;
		}
		cout << endl;

		return longName;
	}

	bool isConnected() {
		return receiver.isConnected();
	}

	int getWidth() {
		return xres;
	}

	int getHeight() {
		return yres;
	}

	bool update() {
		if (receiver.isConnected()) {
			video.update();

			if (video.isFrameNew()) {
				auto& frame = video.getFrame();
				xres = frame.xres;
				yres = frame.yres;

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

	void disconnect() {
		receiver.disconnect();
	}

private:
	ofxNDIReceiver receiver;
	ofxNDIRecvVideoFrameSync video;
	//ofxNDIRecvVideoThreading video;

	ofPixels pixels;
	int xres = 0;
	int yres = 0;

};
