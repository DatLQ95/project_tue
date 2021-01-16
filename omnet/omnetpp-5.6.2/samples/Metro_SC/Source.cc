#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <math.h>
#include "MyPacket_m.h"

using namespace omnetpp;

class Source : public cSimpleModule
{
private:
    double load;
    simtime_t slot;
    long studiedSlots;
    long message_count;
    int Nodes;
    
    int node_dst;
    int application_index;

    long pktSent;
    long pktSent_1;
    long pktSent_2;
    int msg_count;
    int source_number;
    // int Txcount;

    int sum;

    int this_node;

    MyPacket* local_pkt;
    int arrivals;

    simtime_t time_latency;
    simtime_t latency;


    int dest_gen(int N,int src);

public:
    Source();
    virtual ~Source();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

Define_Module(Source);

Source::Source(){

      local_pkt = NULL;
}

Source::~Source(){

      cancelAndDelete(local_pkt);
}

void Source::initialize()
{
    node_dst = par("node_dst");

    application_index = par("application_index");

    slot = par("slot");

    message_count = par("message_count");

    source_number = par("source_number");

    msg_count = 0;
    sum = 0;
    local_pkt = new MyPacket ("local_pkt");

    pktSent_1 = 0;
    pktSent_2 = 0;

    local_pkt->setIndex(0);

    int control_msg_count = floor(1e-4/slot.dbl());

    if(slot.dbl() == 1e-5) control_msg_count = 10;

    scheduleAt(simTime()+control_msg_count*slot,local_pkt); //100*slot

    load=par("load");
    Nodes = par("Nodes");

    studiedSlots=0;
    WATCH(studiedSlots);
    pktSent=0;
    WATCH(pktSent);

}

void Source::handleMessage(cMessage *msg)
{
    MyPacket *temp_msg = check_and_cast<MyPacket *>(msg);
    int src = getIndex();

    this_node = getIndex()/source_number;

    if(temp_msg->getIndex()==0){

    if (SIMTIME_DBL(simTime()) < 0.05){

        if (application_index > 0){

            if(uniform(0,10) < load){

                    MyPacket *pkt = new MyPacket();
                    int inter_dst = node_dst;
                    pkt->setApplication_index(application_index);
                    pkt->setBitLength(100000);
                    pkt->setIndex(1);
                    pkt->setSource(this_node);
                    pkt->setDst_inter(inter_dst);
                    pkt->setEnd2EndStartTime(SIMTIME_DBL(simTime()));
                    //pkt->setPri_latency(pri_latency);
                    //pkt->setPri_realiablity(pri_realiablity);
                    //pkt->setApplication_index(application_index);

                    send(pkt, "out");
                    EV<<"Sending a packet";
                    bubble("Sending a packet");

                    pktSent++;
                    msg_count++;  //100*slot
            }
        }

        scheduleAt(simTime()+slot/4,local_pkt);
    }

    else{

         MyPacket *FinishMsg = new MyPacket();
         FinishMsg->setIndex(5);   //finish
         FinishMsg->setApplication_index(1);
         sendDelayed(FinishMsg,100*slot,"out");

         EV<<"as counter value reaches 10000, send finish msg "<<"\n";
         if(local_pkt->isScheduled())
         cancelEvent(local_pkt);
    }


    }
}

int Source::dest_gen(int N,int src){

    int dest;

    dest = intuniform(0,N-1);

    while (src==dest) dest = intuniform(0,N-1);

    return dest;
}

void Source::finish()
{
    EV << "Messages sentFsource:     " << pktSent << endl;
    recordScalar("#MessagesendF source", pktSent);
    recordScalar("#Slot studied", studiedSlots);
}



