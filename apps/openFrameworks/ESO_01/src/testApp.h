#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxPachube.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 7999

class testApp : public ofBaseApp{

	public:
    
        testApp();
        ~testApp();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
    
        string currentFeedID;    
        string currentTitle;
        string currentGetStatus;
        string currentLastResponseTime;   
        
        string enviroFactorTag[7];
        int enviroFactorVal[7];
        
        int offsetX;
        int offsetY;
    
private:
    ofxPachubeOutput*               parsons;
    ofxPachubeOutput*               arizona;
    ofxPachubeOutput*               australia;
    ofxPachubeOutput*               berlin;
    ofxPachubeOutput*               korea;
    ofxPachubeOutput*               beijing;
    
    int                             iCounter;
    
    ofxOscSender sender;

};

#endif
