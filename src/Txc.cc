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

enum STATES {
    IDLE = 1, WAIT_FOR_REPLY, WAIT_FOR_LEADER,

};

enum MESSAGES {
    HEART_BEAT_ENUM = 1, CALL_HEART_BEAT_ENUM, LEADER_ENUM

};

void Txc::initialize() {
    CALL_HEART_BEAT_MSG = new cMessage(""+CALL_HEART_BEAT_ENUM);
    HEART_BEAT_MSG = new cMessage(""+HEART_BEAT_ENUM);
    //SETTING ATRIBUTS
    id = getIndex();
    leaderId = 0;
    state = IDLE;

    if (par("sendInitialMessage").boolValue()) {
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");
        heartBeat();
    }
}

void Txc::handleMessage(cMessage *msg) {
    // just send back the message we received

    if (msg == CALL_HEART_BEAT_MSG) {
        heartBeat();
    }

    if (strcmp(HEART_BEAT, msg->getName())==0){
        cMessage *msg = new cMessage("ok");
        send(msg, "out");
    }
}


void Txc::heartBeat(){

    if(leaderId == id){
        cMessage *msg = new cMessage(HEART_BEAT);
        send(msg, "out");
        scheduleAt(simTime() + 0.5, CALL_HEART_BEAT_MSG);
    }
}


}; // namespace
