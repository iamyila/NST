//
//  Heatmap.h
//

#pragma once

#include "ofMain.h"
#include "ofxHeatMap.h"
#include "NDISender.h"  // my own helper class

namespace mtb{
    
    class mtbHeatmap{
        
    public:
        
        void setup(string name, int w, int h, bool ndiOut){
            width = w;
            height = h;
            heatmap.setup(width, height);
            senderHeatmap.setup(name, width, height, ndiOut);
            bInit = true;
        }
        
        void drawFbo(int x, int y, int w, int h){
            senderHeatmap.draw(x, y, w, h);
        }
        
        void drawToFbo(){
            heatmap.update(heatColor);
            senderHeatmap.begin();
            ofSetColor(255, heatAlpha);
            heatmap.draw(0, 0);
            senderHeatmap.end();
        }
        
        void add(float x, float y, float area){
            float min = heatSizeMin * width * 0.01;
            float max = heatSizeMax * width * 0.01;
            float radius = ofMap(area, 0, 1, min, max, true);
            heatmap.setRadius(radius);
            heatmap.addPoint(x*width, y*height);
        }
        
        void clear(){
            if(bInit){
                heatmap.clear();
                bInit = false;
            }
        }
        
        void send(){
            senderHeatmap.send();
        }
        
        ofxHeatMap heatmap;
        NDISender senderHeatmap;
        
        int width, height;
        bool bInit = false;
        
        ofParameter<int> heatColor{ "Color Scheme", 1, 0, heatmap.schemes.size()-1 };
        ofParameter<int> heatAlpha{ "Alpha", 200, 0, 255 };
        ofParameter<int> heatSizeMin{ "Size Min %", 1, 1, 20 };
        ofParameter<int> heatSizeMax{ "Size Max %", 5, 1, 20 };
        ofParameterGroup grp{ "Heat Map", heatColor, heatAlpha, heatSizeMin, heatSizeMax};
        
        ofEventListeners listenerHolder;
    };
}
