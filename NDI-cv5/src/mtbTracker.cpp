//
//  mtbTracker.cpp
//  NDI-cv5
//
//  Created by Hiroshi Matoba on 10/30/20.
//

#include "mtbTracker.h"
#include "NDIsource.h"

namespace mtb{
    
    void mtbTracker::registerUser(NDISource * s){
        user = s;
    }
    
    void mtbTracker::drawToFbo(float receiverW, float receiverH, float processW, float processH){
        
        senderBlob.begin();
        
        float sx = (float)processW / receiverW;
        float sy = (float)processH / receiverH;
        ofPushMatrix();
        ofScale(sx, sy);
        
        // Candidates
        if(bDrawCandidates){
            ofPushStyle();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofSetColor(0, 255, 0);
            ofNoFill();
            for(int i=0; i<contourFinder.blobs.size(); i++){
                const auto & b = contourFinder.blobs[i];
                const ofRectangle & rect = b.boundingRect;
                glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
                
                ofPushMatrix();
                ofTranslate(center.x, center.y);
                ofDrawRectangle(0, 0, rect.width, rect.height);
                
                // text
                int label = tracker.getCurrentLabels()[i];
                drawLabelAndAge(label);
                ofPopMatrix();
                
            }
            ofPopStyle();
        }
        
        // Selected
        auto itr = selectedBlobs.begin();
        for(; itr!=selectedBlobs.end(); ++itr){
            
            int label = itr->first;
            bool bNoteOnSent = itr->second;
            int age = tracker.getAge(label);
            int index = tracker.getIndexFromLabel(label);
            ofxCvBlob & blob = contourFinder.blobs[index];
            ofRectangle & rect = blob.boundingRect;
            glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
            glm::vec2 velocity = ofxCv::toOf(tracker.getVelocity(index));
            float area = blob.area / (receiverW*receiverH);
            
            ofPushStyle();
            ofPushMatrix();
            if(bNoteOnSent){
                ofSetLineWidth(1);
                ofNoFill();
                blob.draw();
                drawLabelAndAge(label, center.x, center.y);
            }else{
                ofTranslate(center);
                ofSetColor(255, 200);
                ofNoFill();
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0, 0, rect.width, rect.height);
                drawLabelAndAge(label);
            }
            ofPopMatrix();
            ofPopStyle();
            
            
            // Heatmap
            user->addPointToHeatmap(center.x/receiverW, center.y/receiverH, area);
        }
        
        ofPopMatrix();
        senderBlob.end();
    }
}
