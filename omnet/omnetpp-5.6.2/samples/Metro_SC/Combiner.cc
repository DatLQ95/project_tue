#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <math.h>
#include "MyPacket_m.h"

using namespace omnetpp;

class Combiner : public cSimpleModule
{
  private:

    int channel_index;

  protected:

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

Define_Module(Combiner);

void Combiner::initialize()
{

}

void Combiner::handleMessage(cMessage *msg)
{
    MyPacket *mypkt = check_and_cast<MyPacket *>(msg);

    if (mypkt->getIndex() == 10){

        send(mypkt,"SC_out");
    }
    else if(mypkt->getIndex() == 1){       //data packet

        channel_index = mypkt->getArrivalGate()->getIndex();
        send(mypkt,"out",channel_index);

    }
}

void Combiner::finish()
{
      EV << "finish"  << endl;
}
