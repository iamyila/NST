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

	string connect(const ofxNDI::Source& source) {
		if (source.p_ndi_name.empty()) {
			return "";
		}
		cout << "Try to connect to selected source: " << source.p_ndi_name << " ...";
		receiver.disconnect();
		bool ok = receiver.setup(source);
		if (ok) {
			video.setup(receiver);
			cout << " OK! (selected)" << endl;
			return source.p_ndi_name;
		}
		cout << " failed" << endl;
		return "";
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

		const string nameUpper = ofToUpper(name);
		int exactIdx = -1;
		vector<int> containsIdx;

		for (int i = 0; i < static_cast<int>(sources.size()); ++i) {
			const string srcUpper = ofToUpper(sources[i].p_ndi_name);
			if (srcUpper == nameUpper) {
				exactIdx = i;
				break;
			}
			if (ofIsStringInString(srcUpper, nameUpper)) {
				containsIdx.push_back(i);
			}
		}

		int chosenIdx = -1;
		string matchType = "";
		if (exactIdx >= 0) {
			chosenIdx = exactIdx;
			matchType = "exact";
		} else if (containsIdx.size() == 1) {
			chosenIdx = containsIdx.front();
			matchType = "contains";
		} else if (containsIdx.size() > 1) {
			cout << endl;
			cout << " Ambiguous match. Please type a more specific source name." << endl;
			for (int idx : containsIdx) {
				cout << "  - " << sources[idx].p_ndi_name << endl;
			}
			cout << endl;
			return "";
		}

		if (chosenIdx < 0) {
			cout << endl;
			cout << " Not found" << endl;
			cout << endl;
			return "";
		}

		receiver.disconnect();
		const bool ok = receiver.setup(sources[chosenIdx]);
		if (!ok) {
			cout << " Found candidate, but setup failed." << endl;
			cout << endl;
			return "";
		}

		video.setup(receiver);
		cout << " OK! (" << matchType << ")" << '\n';
		cout << endl;
		return sources[chosenIdx].p_ndi_name;
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
