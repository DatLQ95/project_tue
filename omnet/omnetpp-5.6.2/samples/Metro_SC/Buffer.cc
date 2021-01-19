#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <math.h>
#include "MyPacket_m.h"
using namespace omnetpp;
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define APPLICATION_NUMBER 10

class Buffer : public cSimpleModule
{
    private:
        int Nodes;
        int Dst_table[100]; //20>channel
        bool free_channel[100];
        //cQueue buffer25[100];
        //cQueue buffer25_e;
        //int buffer25Length[100];
        //int buffer25eLength;

        cQueue buffer[100];
        //cQueue buffer400_e;
        int bufferLength[100];
        int bufferDst[100][100];
        //int buffer400eLength;

        int Txcount;
        //int Tx400count;

        int Rxcount;
        int Buf_count;
        //int Buf25_count;

        int application_number;

        bool delete_flag;
        int source_number;

        simtime_t Rec_time;
        simtime_t slot;

        int initial_msg_count;
        int Channel;
        int lost[APPLICATION_NUMBER];

        int capacity;
        int pktSent;

        MyPacket* local_pkt;


    public:
        Buffer();
        virtual ~Buffer();
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
};

Define_Module(Buffer);

Buffer::Buffer(){
      local_pkt = NULL;
}

Buffer::~Buffer(){
     cancelAndDelete(local_pkt);
}

void Buffer::initialize()
{
    initial_msg_count = 0;

    Channel                   = par("Channel");

    Txcount                 = par("Txcount"); //
    //Tx400count                = par("Tx400count"); //

    Rxcount                   = par("Rxcount");

    //Buf400_count              = par("Tx400count");
    source_number               = par("source_number");

    Rec_time = 4e-7;
    slot                      = par("slot");

    Nodes                     = par("Nodes");
    capacity                  = par("capacity");

    application_number = par("application_number");

    delete_flag = false;

    for(int i=0;i<100;i++){
        Dst_table[i] = -1;
        free_channel[i] = true;
    }

    for(int i=0;i<100;i++){
       bufferLength[i] = 0;
       //buffer400Length[i] = 0;
    }
    //buffer25eLength  = 0;
    //buffer400eLength = 0;

    for(int i=0;i<100;i++){
        while(buffer[i].length()>0){
            buffer[i].pop();
        }
        //while(buffer400[i].length()>0){
            //buffer400[i].pop();
        //}
    }
    //while(buffer25_e.length()>0){
    //    buffer25_e.pop();
    //}
    //while(buffer400_e.length()>0){
    //    buffer400_e.pop();
    //}
    for (int i =0; i < application_number; i ++){
        lost[i]=0;
    }

    WATCH(lost);

    pktSent=0;
    WATCH(pktSent);

    local_pkt = new MyPacket ("local_pkt");
    local_pkt->setIndex(0);
    scheduleAt(simTime(),local_pkt);

}

void Buffer::handleMessage(cMessage *msg)
{
    int src = getIndex();
    MyPacket *temp_msg = check_and_cast<MyPacket *>(msg);

    int control_msg_count = floor(1e-4/slot.dbl());

    if(slot.dbl() == 1e-5) control_msg_count = 10;

    if(temp_msg->getIndex()==0){
        if(initial_msg_count<control_msg_count){

         MyPacket *ctrl_pkt = new MyPacket();

         char msgname[20];
         sprintf(msgname, "Control Msg");
         ctrl_pkt -> setName(msgname);
         ctrl_pkt -> setIndex(10);
         ctrl_pkt -> setBitLength(2000);

         for(int i=0;i<Channel;i++){
             ctrl_pkt -> setDst_table(i,Dst_table[i]);
         }

         send(ctrl_pkt,"SC_out");
         EV<<"Sending control packet\n";
         bubble("Sending control packet");
         initial_msg_count++;

        scheduleAt(simTime()+slot,local_pkt); //
        }
        else{
            if(local_pkt->isScheduled())
            cancelEvent(local_pkt);
        }
    }

    if (temp_msg -> getIndex()==1){

        int buf_index = temp_msg->getArrivalGate()->getIndex();
        int dst_index = temp_msg->getDst_inter();
            if (buffer[buf_index].length()+1>=capacity)
            {

                    delete msg;
                    bubble("Packet lost");
                    lost[temp_msg -> getApplication_index()]++;

            }
            else
            {
                EV<<"Packet in buffer\n";
                buffer[buf_index].insert(msg);
                bufferDst[buf_index][bufferLength[buf_index]] = dst_index;
                bufferLength[buf_index]++;
            }

    }

    else if(temp_msg->getIndex()==10){     //control to send signal

        int m[100];

        for(int i=0;i<Channel;i++){
            Dst_table[i] = -1 ;
            m[i] = -1;
        }

        for(int i=0;i<Channel;i++){
            Dst_table[i] = temp_msg->getDst_table(i) ;
            EV<<"dst table "<<i<<" = "<<Dst_table[i]; //
        }

        int d_flag;
        int d_flag_f;

        if(delete_flag == true){
            d_flag = 1;
            for(int i=0;i<100;i++){
                if((bufferLength[i] != 0)){
                    d_flag = 0;
                    break;
                }
            }
            //if(((buffer25eLength-1) !=0)||((buffer400eLength -1) !=0)){
            //    d_flag = 0;
            //}
        }
        else{
            d_flag = 0;
        }

        if(d_flag == 1){
           d_flag_f = 1;
           for(int i=0;i<Channel;i++){
              if(Dst_table[i] != -1){
                  d_flag_f = 0;
                  break;
              }
            }
        }
        else{
            d_flag_f = 0;
        }

        if(d_flag_f == 1){
            delete(temp_msg);
        }
        else{

            int k = 0;
            //
            int node_occupied_channel[40];

            for(int j=0;j<40;j++){
                 node_occupied_channel[j] = 0;
            }
            for(int i=0;i<Channel;i++){
                if(Dst_table[i] == -1){
                    m[k] = i;
                    k++;
                }
                else{
                    node_occupied_channel[Dst_table[i]]++;
                }
            }



             for(int i=0;i<MIN(k,Txcount);i++){

                /*int d = -1;
                int l = 0;
                for(int t=0;t<Txcount;t++){
                   if(bufferLength[t] > l) {d=t; l = bufferLength[t];}
                }*/
                int d = -1;
                int l = 3 ; //bufferLength[0];
                int pkt_sent_this_loop = 0;

                for(int t=0;t<source_number;t++){
                    if(bufferLength[t] > 0 ) {
                        if ((node_occupied_channel[bufferDst[t][bufferLength[t]-1]] < Rxcount) && (bufferLength[t] > l )) {
                             d=t; l = bufferLength[t];
                        }
                    }
                }

                if((d!=-1)&&(bufferLength[d]>=4)){
                    MyPacket *send_msg = check_and_cast<MyPacket *>(buffer[d].pop());
                    MyPacket *send_msg1 = check_and_cast<MyPacket *>(buffer[d].pop());
                    delete(send_msg1);
                    MyPacket *send_msg2 = check_and_cast<MyPacket *>(buffer[d].pop());
                    delete(send_msg2);
                    MyPacket *send_msg3 = check_and_cast<MyPacket *>(buffer[d].pop());
                    delete(send_msg3);
                    bufferLength[d] = bufferLength[d] - 4 ;
                    Dst_table[m[i]] = send_msg->getDst_inter();
                    simtime_t delay_time = 4e-7;//slot + Rec_time;// + 2e-7;
                    sendDelayed(send_msg,slot,"out",m[i]);  // to simulate transmit latency  2e-6 1us slot
                    EV<<"Sending data packet in channel"<<m[i]<<"to"<<Dst_table[m[i]]<<"\n";
                    bubble("Sending data packet");
                    pktSent++;
                    //pkt_sent_this_loop ++ ;
                    //if ( pkt_sent_this_loop > MIN(k,Txcount) ) exit;
                }

             }

             for(int i=0;i<Channel;i++){
                 temp_msg -> setDst_table(i,Dst_table[i]);
             }
             sendDelayed(temp_msg,Rec_time,"SC_out");  // to simulate transmit latency  400e-9
             EV<<"Sending control packet\n";
             bubble("Sending control packet");
        }

    }

    else if(temp_msg->getIndex()==5){
        delete(temp_msg);
        delete_flag = true;
    }
}

void Buffer::finish()
{
    recordScalar("#Messages sentFbuffer", pktSent);
    for (int i; i < application_number; i ++)
    {
        recordScalar("pack loss", lost[i]);
    }
}





