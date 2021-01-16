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



#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <omnetpp.h>
#include <math.h>
#include "MyPacket_m.h"

using namespace omnetpp;

class Interface: public cSimpleModule
{
private:
    // double probToSend;
    simtime_t slot;
    long studiedSlots;
    int Nodes;
    //int Buf_count;
    //int Buf25_count;
    //int Tx25count;
    //int Txcount;
    long pktErr;

    int msg_count;

    int arrivals;
    simtime_t time_latency;
    simtime_t latency[10];

    int current_tx;
    //int previous_tx;

    MyPacket* local_pkt;

    cStdDev latJitter; //
    cHistogram latCDF; //
    cOutVector lat_rec;//

    int dest_gen(int N,int src);
    int tx_gen(int pre_tx,int N);
public:
    Interface();
    virtual ~Interface();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

Define_Module(Interface);

Interface::Interface(){

      local_pkt = NULL;
}

Interface::~Interface(){

      cancelAndDelete(local_pkt);
}

void Interface::initialize()
{
    slot = 1e-6;
    msg_count = 0;
    local_pkt = new MyPacket ("local_pkt");

    local_pkt->setIndex(0);

    current_tx = 0;
    //previous_tx = 0;


    scheduleAt(simTime()+100*slot,local_pkt); //100*slot

    // probToSend                = par("load");
    Nodes                     = par("Nodes");
    //Buf_count              = par("Buf_count");


    arrivals = 0;
    time_latency = 0;

    for (int i = 0; i < 10; i++){
        latency[i] = 0;
    }

    studiedSlots=0;
    WATCH(studiedSlots);
    pktErr=0;
    WATCH(pktErr);
}

void Interface::handleMessage(cMessage *msg)
{
    MyPacket *temp_msg = check_and_cast<MyPacket *>(msg);

    int dst_intra = -1;
    int dst_inter = -1;
    int src = getIndex();

    if(temp_msg->getIndex()==1){
       //int dst_intra = temp_msg->getDst_intra();
       int dst_inter = temp_msg->getDst_inter();

       if(dst_inter == src){
            bubble("Packet received");
            int application_index = temp_msg -> getApplication_index();
            time_latency = simTime() - temp_msg->getEnd2EndStartTime();

            //latJitter.collect(time_latency);
            //latCDF.collect(time_latency);
            //lat_rec.record(time_latency);

            latency[application_index] = latency[application_index] + time_latency;
            time_latency = 0;
            arrivals++;
            delete(msg);

        }
        if(dst_inter != src){

            //char msgname[20];
            //sprintf(msgname, "pkt-%d-to-%d", src, dst_inter);
            //temp_msg -> setName(msgname);

            //current_tx = temp_msg->getArrivalGate()->getIndex();

            //send(temp_msg, "buffer_out",current_tx);
            //EV<<"Sending a packet";
            //bubble("Sending a packet");
            //pktSent++;


            delete(msg);
            pktErr++;




        }

    }
    else if(temp_msg->getIndex()==5){

            current_tx = temp_msg->getArrivalGate()->getIndex();

            send(msg, "buffer_out",current_tx);
            EV<<"Sending a packet";
            bubble("Sending a packet");

            //current_tx = tx_gen(previous_tx,Buf_count); //round-robin
            //previous_tx = current_tx;

     }
}

int Interface::dest_gen(int N,int src){

    int dest;

    dest = intuniform(0,N-1);

    if(src==dest&&dest==N-1)
        dest--;
    if(src==dest)
        dest++;

    return dest;
}

int Interface::tx_gen(int pre_tx, int N){

    int tx = 0;
    if(pre_tx < N-1){
        tx = pre_tx + 1;
    }
    else{
        tx = 0;
    }
    return tx;
}

void Interface::finish()
{
    // This function is called by OMNeT++ at the end of the simulation.
    EV << "Messages pktErr from the Interface:     " << pktErr << endl;

    //EV << "jitter = " << latJitter.getStddev() << endl;

    //latJitter.record();
    //latCDF.record();
    //latCDF.saveToFile("1.csv");


    recordScalar("#Messages arrived1", arrivals);
    for (int i =0; i < 10; i++){
        recordScalar("#Messages latency", latency[i]);
    }
    

    recordScalar("#Messages Err", pktErr);
    //recordScalar("#Slot studied", studiedSlots);
}



