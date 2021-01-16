package Metro_SC;

simple Source
{
    parameters:
        @display("i=block/source");
        double load;//= default(0.5);       
        int Nodes;//= default(8);
        int Channel;
        int message_count;
        int source_number;
        int node_dst;
        int application_index;
        double slot;

    gates:
        output out;
        //input in;
}

simple Interface
{
    parameters:
        @display("i=block/source");
        // double load;//= default(0.5);
        int Nodes;//= default(8);
        int Channel;
        int Txcount;

    gates:
        //output buffer_out[Txcount];
        input WSS_in[Channel];
        //input source_in[Txcount];
        //output source_out[Txcount];
}

simple Combiner
{
    parameters:
        @display("i=block/source");

        int Channel;

    gates:
        input SC_in;
        input buffer_in[Channel];  //Channel = 4;
        input pass_in[Channel];
        output out[Channel];
        output SC_out;
}


simple Buffer
{
    parameters:
        @display("i=block/queue");
        int Txcount;
        int Rxcount;
        double slot;//= default(0.95us);
        int capacity;//= default(30);
        int Channel;
        int source_number;

        int Nodes;
    gates:
        input source_in[source_number];
        input SC_in;
        output SC_out;
        output out[Channel];
}


simple WSS1
{
    parameters:
        @display("i=block/routing");
        int Nodes;//= default(8);
        int Channel;
        int Rxcount;

    gates:
        input in[Channel];
        input SC_in;
        output SC_out;
        output drop_out[Channel];
        output pass_out[Channel];
}
network Metro_SC
{
    parameters:
        int Nodes;
        int Channel;
        // double load;
        int Txcount; //traffic amount
        int source_number;

        @display("i=block/network;bgb=878,823;bgi=background/streetmap,s");

    types:
    submodules:

        Interface[Nodes]: Interface {
            @display("p=163.74599,390.344,i,200,280,100;i=abstract/switch");
        }
        buffer[Nodes]: Buffer {
            @display("p=433.348,479.65997,i,200,280,100");
        }
        WSS1[Nodes]: WSS1 {
            @display("p=276.218,615.28796,i,200;i=abstract/dispatcher"); //80
        }
        combiner[Nodes]: Combiner {
            @display("p=613.634,615.28796,i,200;i=abstract/cache");
        }
        source[Nodes*source_number]: Source {
        //source[Nodes*20]: Source {
            @display("p=325.83798,291.10397");
        }

    connections:

        //for i=0..Nodes-1, for j=0..Txcount-1 {
            //Interface[i].buffer_out[j] --> buffer[i].Interface_in[j];
        //}

        for i=0..Nodes-1, for j=0..source_number-1 {
            //Interface[i].source_out[j] --> source[i].in;
           source[j + i*source_number].out --> buffer[i].source_in[j];
        }

        for i=0..Nodes-1 {
            //            controller.SC_out[i] --> buffer[i].SC_in_C;
            WSS1[i].SC_out --> {  delay = 0.015us; } --> buffer[i].SC_in;      /////////////////////
            buffer[i].SC_out --> {  delay = 0.015us; } --> combiner[i].SC_in; /////////////////////
        }

        for i=0..Nodes-2 {
            //{  delay = 100us; datarate = 10Gbps; }
            combiner[i].SC_out --> {  delay = 100us; } --> WSS1[i+1].SC_in;
        }
        //{  delay = 100us; datarate = 10Gbps; }
        combiner[Nodes-1].SC_out --> {  delay = 100us; } --> WSS1[0].SC_in;

        for i=0..Nodes-1, for j=0..Channel-1 {
            //{  delay = 100us; datarate = 10Gbps; }            
            WSS1[i].pass_out[j] --> {  delay = 0.43us; } --> combiner[i].pass_in[j]; //0.43us = rectime (0.4us) + 0.03
            buffer[i].out[j] --> {  delay = 0.015us; } --> combiner[i].buffer_in[j];
        }

        for i=0..Nodes-1, for j=0..Channel-1 {
            //{  delay = 100us; datarate = 10Gbps; }            
            WSS1[i].drop_out[j] --> {  delay = 0.015us; } --> Interface[i].WSS_in[j];
        }

        for i=0..Nodes-2, for j=0..Channel-1 {
            //{  delay = 100us; datarate = 10Gbps; }
            combiner[i].out[j] --> {  delay = 100us; } --> WSS1[i+1].in[j];
        }
        for j=0..Channel-1 {
            //{  delay = 100us; datarate = 10Gbps; }
            combiner[Nodes-1].out[j] --> {  delay = 100us; } --> WSS1[0].in[j];
        }

}




