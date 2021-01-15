#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <math.h>
#include "MyPacket_m.h"

using namespace omnetpp;

class WSS1 : public cSimpleModule
{
  private:

    int channel_index;
    int Channel;
    int Dst_table[100];
    int Rxcount;
    int drop_index;
    int delete_index;

  protected:

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

Define_Module(WSS1);

void WSS1::initialize()
{

    Channel = par("Channel");
    Rxcount = par("Rxcount");
    drop_index = 0;
    delete_index = 0;
    WATCH(delete_index);

    for(int i=0;i<100;i++){
       Dst_table[i] = -1;
    }
}

void WSS1::handleMessage(cMessage *msg)
{
    MyPacket *mypkt = check_and_cast<MyPacket *>(msg);
    int src = getIndex();

    int k;
    int m[100];
    for(int t=0;t<Channel;t++){
        m[t] = -1;
    }

    if (mypkt->getIndex() == 10){
        k = 0;
        for(int i=0;i<Channel;i++){
            Dst_table[i] = mypkt->getDst_table(i) ;
            EV<<"dst table "<<i<<" = "<<Dst_table[i]; //

            if(Dst_table[i] == src){
              if(k < Rxcount){
                  EV<<"m "<<k<<" = "<<m[k];
                  m[k] = i;
                  k++;
                  mypkt->setDst_table(i,-1);
                  Dst_table[i] = 1000;
              }
              /*
              else{ ///
                  m[k] = i;
                  k++;
                  mypkt->setDst_table(i,-1);
                  Dst_table[i] = -1000;
              } ///
              */
           }
        }
        send(mypkt,"SC_out");
        drop_index = 0;
    }
    else if(mypkt->getIndex() == 1){       //data packet

        channel_index = mypkt->getArrivalGate()->getIndex(); //
        EV<<"CAHNNEL = "<<channel_index;

        if(Dst_table[channel_index] == 1000){
            send(mypkt,"drop_out",channel_index);
            EV<<"drop a packet";
            EV<<"dst"<<mypkt->getDestination()<<"Channel"<<channel_index;
            bubble("drop a packet");
            drop_index++;}
        /*
        else if(Dst_table[channel_index] == -1000){
            //send(mypkt,"drop_out",channel_index);
            //EV<<"drop a packet";
            //EV<<"dst"<<mypkt->getDestination()<<"Channel"<<channel_index;
            //bubble("drop a packet");
            delete(mypkt);
            delete_index++;}
        */
        else{
            send(mypkt,"pass_out",channel_index);
            EV<<"pass a packet";
            EV<<"dst"<<mypkt->getDestination()<<"Channel"<<channel_index;
            bubble("pass a packet");
        }
    }

}

void WSS1::finish()
{
      EV << "finish"  << endl;
      recordScalar("#MessagLostF WSS", delete_index);
}
