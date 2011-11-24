#include "testApp.h"

testApp::testApp()
{
    iCounter = 0;
    
    parsons = new ofxPachubeOutput(true);       /// threaded
 	parsons->setApiKey("LE6lKI-4z1K1IfVnTLXjw00VmplqKyQhNaETohUPZgs");
 	/// To read a feed you need a pachube api key. More info at www.pachube.com
	parsons->setFeedId(23656);
	parsons->setVerbose(false);
	parsons->setMinInterval(5);
	parsons->output(OFX_PACHUBE_EEML, true);    /// forcing update = ignoring min interval
    
    australia = new ofxPachubeOutput(true);       /// threaded
 	australia->setApiKey("LE6lKI-4z1K1IfVnTLXjw00VmplqKyQhNaETohUPZgs");
 	/// To read a feed you need a pachube api key. More info at www.pachube.com
	australia->setFeedId(22587);
	australia->setVerbose(false);
	australia->setMinInterval(5);
	australia->output(OFX_PACHUBE_EEML, true);    /// forcing update = ignoring min interval
    
    arizona = new ofxPachubeOutput(true);       /// threaded
 	arizona->setApiKey("LE6lKI-4z1K1IfVnTLXjw00VmplqKyQhNaETohUPZgs");
 	/// To read a feed you need a pachube api key. More info at www.pachube.com
	arizona->setFeedId(26118);
	arizona->setVerbose(false);
	arizona->setMinInterval(5);
	arizona->output(OFX_PACHUBE_EEML, true);    /// forcing update = ignoring min interval
    
    berlin = new ofxPachubeOutput(true);       /// threaded
 	berlin->setApiKey("LE6lKI-4z1K1IfVnTLXjw00VmplqKyQhNaETohUPZgs");
 	/// To read a feed you need a pachube api key. More info at www.pachube.com
	berlin->setFeedId(17475);
	berlin->setVerbose(false);
	berlin->setMinInterval(5);
	berlin->output(OFX_PACHUBE_EEML, true);    /// forcing update = ignoring min interval
    
    korea = new ofxPachubeOutput(true);       /// threaded
 	korea->setApiKey("LE6lKI-4z1K1IfVnTLXjw00VmplqKyQhNaETohUPZgs");
 	/// To read a feed you need a pachube api key. More info at www.pachube.com
	korea->setFeedId(24437);
	korea->setVerbose(false);
	korea->setMinInterval(5);
	korea->output(OFX_PACHUBE_EEML, true);    /// forcing update = ignoring min interval
    
    beijing = new ofxPachubeOutput(true);       /// threaded
 	beijing->setApiKey("LE6lKI-4z1K1IfVnTLXjw00VmplqKyQhNaETohUPZgs");
 	/// To read a feed you need a pachube api key. More info at www.pachube.com
	beijing->setFeedId(17473);
	beijing->setVerbose(false);
	beijing->setMinInterval(5);
	beijing->output(OFX_PACHUBE_EEML, true);    /// forcing update = ignoring min interval
    
}

testApp::~testApp()
{
    delete parsons;
    delete australia;
    delete arizona;
    delete berlin;
    delete korea;
    delete beijing;
}

//--------------------------------------------------------------
void testApp::setup(){
    
	// open an outgoing connection to HOST:PORT
	sender.setup( HOST, PORT ); //defined in testApp.h
    
    enviroFactorTag[0] = "temperature";
    enviroFactorTag[1] = "light";
    enviroFactorTag[2] = "humidity";
    enviroFactorTag[3] = "noise";
    enviroFactorTag[4] = "carbonDioxide";
    enviroFactorTag[5] = "carbonMonoxide";
    enviroFactorTag[6] = "airQuality";
    
    for(int i=0; i<7; i++){
        enviroFactorVal[i] = 0;
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    /// Values are updated from Pachube if min interval has passed since last update
    /// Override this by setting the 'force' argument to true
    /// Feeds can be read as EEML or CSV
    //parsons->output(OFX_PACHUBE_CSV, false);
    parsons->output(OFX_PACHUBE_EEML, false);
    australia->output(OFX_PACHUBE_EEML, false);
    arizona->output(OFX_PACHUBE_EEML, false);
    berlin->output(OFX_PACHUBE_EEML, false);
    korea->output(OFX_PACHUBE_EEML, false);
    beijing->output(OFX_PACHUBE_EEML, false);
    
    /// A counter to see if threads are working
    iCounter++;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(10, 10, 10);
    ofSetColor(255,255,255);
    ofFill();
    
    ofDrawBitmapString("counter: " +ofToString(int(iCounter)), 20, ofGetHeight()-5);
    currentLastResponseTime = ofToString(int(parsons->getLastResponseTime())); 
    ofDrawBitmapString(">>> Electromechanical Solenoid Orchestra <<< ", 20, 20);
    ofDrawBitmapString(">>>      Pachube/OSC Controller v01      <<< ", 20, 35);
    ofDrawBitmapString("server response time: " + currentLastResponseTime, 20, 50);
    
    string oscInfo = "sending osc messages to: " + string( HOST ) +" "+ ofToString( PORT );
    ofDrawBitmapString(oscInfo, 820, 20);
    
    /// ------  PARSONS  ------
    if (parsons->getLastRequestOk())
        ofSetColor(250, 250, 250);
    else
        ofSetColor(250, 60, 40);
    
    //text offset
    offsetX = 0;
    offsetY = 65;
    
    currentFeedID = ofToString(parsons->getFeedId());    
    currentTitle = parsons->getTitle();
    currentGetStatus = parsons->getStatus();
    
    ofDrawBitmapString("TEST FEED", 20 + offsetX, 20 + offsetY);
    ofDrawBitmapString("Feed ID: " + currentFeedID, 20 + offsetX, 35 + offsetY);
    ofDrawBitmapString("Title: " + currentTitle, 20 + offsetX, 50 + offsetY);
    if(currentGetStatus == "frozen"){
        ofSetColor(250, 60, 40);
    }
    ofDrawBitmapString("Status: " + currentGetStatus, 20 + offsetX, 65 + offsetY);
 
    for (int i = 0; i < parsons->getDatastreamCount(); i++) {
        enviroFactorVal[i] = parsons->getValue(i);
        ofDrawBitmapString(enviroFactorTag[i] + ": \n" + ofToString(enviroFactorVal[i]),20 + offsetX, 80+offsetY+30*i);
        ofxOscMessage m;
        m.setAddress("/parsons/"+enviroFactorTag[i]);
        m.addIntArg( enviroFactorVal[i] );
        sender.sendMessage( m );
    }
    
    
    /// ------  AUSTRALIA  ------
    if (australia->getLastRequestOk())
        ofSetColor(250, 250, 250);
    else
        ofSetColor(250, 60, 40);
    
    //text offset
    offsetX = 0;
    offsetY = 350;
    
    currentFeedID = ofToString(australia->getFeedId());    
    currentTitle = australia->getTitle();
    currentGetStatus = australia->getStatus();
    
    ofDrawBitmapString("AUSTRALIA", 20 + offsetX, 20 + offsetY);
    ofDrawBitmapString("Feed ID: " + currentFeedID, 20 + offsetX, 35 + offsetY);
    ofDrawBitmapString("Title: " + currentTitle, 20 + offsetX, 50 + offsetY);
    if(currentGetStatus == "frozen"){
        ofSetColor(250, 100, 90);
    }
    ofDrawBitmapString("Status: " + currentGetStatus, 20 + offsetX, 65 + offsetY);
    
    for (int i = 0; i < australia->getDatastreamCount(); i++) {
        enviroFactorVal[i] = australia->getValue(i);
        ofDrawBitmapString(enviroFactorTag[i] + ": \n" + ofToString(enviroFactorVal[i]),20 + offsetX, 80+offsetY+30*i);
        ofxOscMessage m;
        m.setAddress("/australia/"+enviroFactorTag[i]);
        m.addIntArg( enviroFactorVal[i] );
        sender.sendMessage( m );
    }
    
    /// ------  KOREA  ------
    if (korea->getLastRequestOk())
        ofSetColor(250, 250, 250);
    else
        ofSetColor(250, 60, 40);
    
    //text offset
    offsetX = 400;
    offsetY = 65;
    
    currentFeedID = ofToString(korea->getFeedId());    
    currentTitle = korea->getTitle();
    currentGetStatus = korea->getStatus();    
    
    ofDrawBitmapString("KOREA", 20 + offsetX, 20 + offsetY);
    ofDrawBitmapString("Feed ID: " + currentFeedID, 20 + offsetX, 35 + offsetY);
    ofDrawBitmapString("Title: " + currentTitle, 20 + offsetX, 50 + offsetY);
    if(currentGetStatus == "frozen"){
        ofSetColor(250, 100, 90);
    }
    ofDrawBitmapString("Status: " + currentGetStatus, 20 + offsetX, 65 + offsetY);
    
    for (int i = 0; i < korea->getDatastreamCount(); i++) {
        enviroFactorVal[i] = korea->getValue(i);
        ofDrawBitmapString(enviroFactorTag[i] + ": \n" + ofToString(enviroFactorVal[i]),20 + offsetX, 80+offsetY+30*i);
        ofxOscMessage m;
        m.setAddress("/korea/"+enviroFactorTag[i]);
        m.addIntArg( enviroFactorVal[i] );
        sender.sendMessage( m );
    }
    
    /// ------  BEIJING  ------
    if (beijing->getLastRequestOk())
        ofSetColor(250, 250, 250);
    else
        ofSetColor(250, 60, 40);
    
    //text offset
    offsetX = 400;
    offsetY = 350;
    
    currentFeedID = ofToString(beijing->getFeedId());    
    currentTitle = beijing->getTitle();
    currentGetStatus = beijing->getStatus();
    
    ofDrawBitmapString("BEIJING", 20 + offsetX, 20 + offsetY);
    ofDrawBitmapString("Feed ID: " + currentFeedID, 20 + offsetX, 35 + offsetY);
    ofDrawBitmapString("Title: " + currentTitle, 20 + offsetX, 50 + offsetY);
    if(currentGetStatus == "frozen"){
        ofSetColor(250, 100, 90);
    }
    ofDrawBitmapString("Status: " + currentGetStatus, 20 + offsetX, 65 + offsetY);
    
    for (int i = 0; i < beijing->getDatastreamCount(); i++) {
        enviroFactorVal[i] = beijing->getValue(i);
        ofDrawBitmapString(enviroFactorTag[i] + ": \n" + ofToString(enviroFactorVal[i]),20 + offsetX, 80+offsetY+30*i);
        ofxOscMessage m;
        m.setAddress("/beijing/"+enviroFactorTag[i]);
        m.addIntArg( enviroFactorVal[i] );
        sender.sendMessage( m );
    }
    
    /// ------  ARIZONA  ------
    if (arizona->getLastRequestOk())
        ofSetColor(250, 250, 250);
    else
        ofSetColor(250, 60, 40);
    
    //text offset
    offsetX = 800;
    offsetY = 65;
    
    currentFeedID = ofToString(arizona->getFeedId());    
    currentTitle = arizona->getTitle();
    currentGetStatus = arizona->getStatus();
    
    ofDrawBitmapString("ARIZONA", 20 + offsetX, 20 + offsetY);
    ofDrawBitmapString("Feed ID: " + currentFeedID, 20 + offsetX, 35 + offsetY);
    ofDrawBitmapString("Title: " + currentTitle, 20 + offsetX, 50 + offsetY);
    if(currentGetStatus == "frozen"){
        ofSetColor(250, 100, 90);
    }
    ofDrawBitmapString("Status: " + currentGetStatus, 20 + offsetX, 65 + offsetY);
    
    for (int i = 0; i < arizona->getDatastreamCount(); i++) {
        enviroFactorVal[i] = arizona->getValue(i);
        ofDrawBitmapString(enviroFactorTag[i] + ": \n" + ofToString(enviroFactorVal[i]),20 + offsetX, 80+offsetY+30*i);
        ofxOscMessage m;
        m.setAddress("/arizona/"+enviroFactorTag[i]);
        m.addIntArg( enviroFactorVal[i] );
        sender.sendMessage( m );
    }
    
    /// ------  BERLIN  ------
    if (berlin->getLastRequestOk())
        ofSetColor(250, 250, 250);
    else
        ofSetColor(250, 60, 40);
    
    //text offset
    offsetX = 800;
    offsetY = 350;
    
    currentFeedID = ofToString(berlin->getFeedId());    
    currentTitle = berlin->getTitle();
    currentGetStatus = berlin->getStatus();
    
    ofDrawBitmapString("BERLIN", 20 + offsetX, 20 + offsetY);
    ofDrawBitmapString("Feed ID: " + currentFeedID, 20 + offsetX, 35 + offsetY);
    ofDrawBitmapString("Title: " + currentTitle, 20 + offsetX, 50 + offsetY);
    if(currentGetStatus == "frozen"){
        ofSetColor(250, 100, 90);
    }
    ofDrawBitmapString("Status: " + currentGetStatus, 20 + offsetX, 65 + offsetY);
    
    for (int i = 0; i < berlin->getDatastreamCount(); i++) {
        enviroFactorVal[i] = berlin->getValue(i);
        ofDrawBitmapString(enviroFactorTag[i] + ": \n" + ofToString(enviroFactorVal[i]),20 + offsetX, 80+offsetY+30*i);
        ofxOscMessage m;
        m.setAddress("/berlin/"+enviroFactorTag[i]);
        m.addIntArg( enviroFactorVal[i] );
        sender.sendMessage( m );
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    /// Press 'e' to refresh feed info compleately as EEML
    //if (key == 'e')
    //    parsons->output(OFX_PACHUBE_EEML, true);

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

