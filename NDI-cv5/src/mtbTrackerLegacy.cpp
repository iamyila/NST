//
//  mtbTrackerLegacy.cpp
//

#include "mtbTrackerLegacy.h"
#include "NDIsource.h"

namespace mtb{
    
    void mtbTrackerLegacy::registerUser(NDISource * s){
        user = s;
    }
    
    void mtbTrackerLegacy::drawToFbo(float receiverW, float receiverH, float processW, float processH){
        senderBlob.begin();
        
        float sx = (float)processW / receiverW;
        float sy = (float)processH / receiverH;
        ofPushMatrix();
        ofScale(sx, sy);
        int okBlobNum = 0;
        int nBlobs = contourFinder.blobs.size();
        for(int i=0; i<nBlobs; i++){
            int label = tracker.getCurrentLabels()[i];
            int age = tracker.getAge(label);
            ofxCvBlob & blob = contourFinder.blobs[i];
            ofRectangle & rect = blob.boundingRect;
            glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
            glm::vec2 velocity = ofxCv::toOf(tracker.getVelocity(i));
            float area = blob.area / (receiverW*receiverH);
            
            {
                ofSetLineWidth(1);
                ofNoFill();
                blob.draw();
                
                ofSetColor(255);
                stringstream ss;
                ss << label << " : " << age;
                ofDrawBitmapString(ss.str(), center.x, center.y);
            }
            
            user->addPointToHeatmap(center.x/receiverW, center.y/receiverH, area);

            okBlobNum++;
            if(okBlobNum >= maxBlobNum) break;
        }
        
        ofPopMatrix();
        senderBlob.end();
        
    }
}
