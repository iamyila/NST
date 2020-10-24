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

	void connect(string name, bool highestBandwidth) {
		if (name == "") {
			return;
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
		for (auto& s : sources) {
			found = ofIsStringInString(s.p_ndi_name, name) || ofIsStringInString(s.p_url_address, name);
			
			if (found) {
				ofxNDIReceiver::Settings settings;
				settings.bandwidth = highestBandwidth
					? NDIlib_recv_bandwidth_highest
					: NDIlib_recv_bandwidth_lowest;
				bool ok = receiver.setup(s, settings);
				
				if (ok) {
					cout << " OK!" << '\n';
					cout << "Connected with " 
						 << (highestBandwidth ? "Highest" : "Lowest") 
						 << " Bandwidth" << '\n';					
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

	void disconnect() {
		receiver.disconnect();
	}

private:
	ofxNDIReceiver receiver;
	ofxNDIRecvVideoFrameSync video;
	//ofxNDIRecvVideoThreading video;

	ofPixels pixels;
};
