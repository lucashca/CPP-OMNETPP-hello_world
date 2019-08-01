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

#ifndef __HELLO_WORLD_TCX_H
#define __HELLO_WORLD_TCX_H

#include <omnetpp.h>

using namespace omnetpp;

namespace hello_world {

/**
 * Implements the Txc simple module. See the NED file for more information.
 */
class Txc : public cSimpleModule
{
private:

    cMessage *CALL_HEART_BEAT_MSG;
    cMessage *HEART_BEAT_MSG;

   int id;
   int leaderId;
   int state;
   bool failed;



 protected:
   virtual void initialize();
   virtual void handleMessage(cMessage *msg);
   virtual void heartBeat();

};
}; // namespace

#endif
