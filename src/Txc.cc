//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Txc.h"

namespace hello_world {

Define_Module(Txc);

const char* HEART_BEAT = "Heart Beat";

// POSSIBLE STATES FOR A NODE    
enum STATES {
    IDLE = 1, WAIT_FOR_REPLY, WAIT_FOR_LEADER,

};

    
enum MESSAGES {
    HEART_BEAT_ENUM = 1, CALL_HEART_BEAT_ENUM, LEADER_ENUM

};

// Responsible for instantiating node attributes
void Txc::initialize() {
    
    // Responsible for creating a message object that will be used in the future to indicate 
    // the need to send a heartbeat to all network nodes.
    /*
        Messages to be scheduled must be compared to the instantiated object itself of the class.
        For those that are not, you should use other activities, such as the message text or define another object 
        that inherits from cMessage that contains other attributes.
    */
    CALL_HEART_BEAT_MSG = new cMessage(""+CALL_HEART_BEAT_ENUM);
    
    //Responsible for creating a heartbeat message that will be sent to all network nodes.
    HEART_BEAT_MSG = new cMessage(""+HEART_BEAT_ENUM);
    
    //SETTING ATRIBUTS
    leaderId = 0;
    state = IDLE;

    // This attribute is defined in the file. HELLO_WORLD-CPP-OMNETPP/simulations/omnetpp.ini
    // Define the fist node to send a message
    if (par("sendInitialMessage").boolValue()) {
        // Create a message with text "tictocMsg"
        cMessage *msg = new cMessage("tictocMsg");
        // Send a msg from the output called "out"
        send(msg, "out");
        // Call a fist heartBeat();
        heartBeat();
    }
}

// Responsible for handling incoming messages
void Txc::handleMessage(cMessage *msg) {
    // just send back the message we received
    
    // Verify if msg is a CALL_HEART_BEAT_MSG
    if (msg == CALL_HEART_BEAT_MSG) {
        heartBeat();
    }
    
     // Verify if msg is a HEART_BEAT
    if (strcmp(HEART_BEAT, msg->getName())==0){
        cMessage *msg = new cMessage("ok");
        send(msg, "out");
    }
}


void Txc::heartBeat(){
    // Send a heartbeat if i am the leader
    if(leaderId == id){
        cMessage *msg = new cMessage(HEART_BEAT);
        send(msg, "out");
        // 
        // Schedule the message to be sent in 0.5 second
        scheduleAt(simTime() + 0.5, CALL_HEART_BEAT_MSG);
    }
}


}; // namespace
