import subprocess
from .simulation_settings import omnet_settings, environment_network


import pandas as pd
import numpy as np

class Omnet():
    def __init__(self):
        pass

    def omnet_ini_file_create(self, list_source, application_number):
        """
        create ini file with specific definition
        """
        #TODO: write create ini file from source list!
        # Writing to file 
        with open(omnet_settings.get_file_resporatory(), "w") as ini_file: 
            # Writing data to a file 
            ini_file.write(omnet_settings.get_ini_file_content()) 
            ini_file.write(self.convertToString(list_source, application_number))
            # file1.writelines(L) 
        pass

    def preprocessing_list_source(self, list_source):
        source_number = max([len(i) for i in list_source])
        for node in list_source:
            while len(node) < source_number:
                node.append([0,0,0])
        return list_source

    def convertToString(self, list_source, application_number):
        """
        convert list of sources to omnet .ini file
        """
        stringToWrite = str()
        node = len(list_source)
        source_number = max([len(i) for i in list_source])
        stringToWrite = stringToWrite + "\n**.Nodes = " +str(node) + "\n"
        stringToWrite = stringToWrite + "**.source_number = " +str(source_number) + "\n"
        #TODO: add application number: 
        stringToWrite = stringToWrite + "**.application_number = " + str(application_number) + "\n"
        list_source = self.preprocessing_list_source(list_source)
        for i in range(node):
            stringToWrite = stringToWrite + "##Node: " + str(i) + "\n\n"
            for j in range(len(list_source[i])):
                stringToWrite = stringToWrite + "Metro_SC.source[" + str(i*source_number + j) + "].load = " + str(list_source[i][j][0]) + "\n"
                stringToWrite = stringToWrite + "Metro_SC.source[" + str(i*source_number + j) + "].application_index = " + str(list_source[i][j][1]) + "\n"
                stringToWrite = stringToWrite + "Metro_SC.source[" + str(i*source_number + j) + "].node_dst = " + str(list_source[i][j][2]) + "\n\n"
        return stringToWrite

    def convert_to_csv_file(self):
        #TODO: catch exception
        print(omnet_settings.get_result_directory())
        cmd =  omnet_settings.get_convert_to_csv_cmd()
        with subprocess.Popen(cmd, stdout=subprocess.PIPE, cwd = omnet_settings.get_result_directory()) as proc: 
            print(proc.stdout.readlines())
        pass

    def get_result_array(self, number_application):
        result = pd.read_csv(omnet_settings.get_csv_file_directory(), iterator=True, chunksize=1000)
        chunks = [ chunk[chunk['type'] == 'scalar'] for chunk in result ]
        # tmp = pd.concat(chunks)
        tmp = pd.concat(chunks)
        interface_values = [tmp[tmp['module'] == 'Metro_SC.Interface[' + str(i) + ']'] for i in range(environment_network.get_node_number())]
        buffer_values = [tmp[tmp['module'] == 'Metro_SC.buffer[' + str(i) + ']'] for i in range(environment_network.get_node_number())]

        latency = list()
        for i in interface_values:
            name = i.name.tolist()
            value = i.value.tolist()
            for j in range(len(i)):
                if name[j] == "#Messages latency":
                    latency.append(value[j])

        final_latency = [list() for i in range(number_application)]
        for i in range(len(latency)):
            final_latency[i%number_application].append(latency[i])

        number_packet_arrival = list()
        for i in interface_values:
            name = i.name.tolist()
            value = i.value.tolist()
            for j in range(len(i)):
                if name[j] == "#Messages arrived":
                    number_packet_arrival.append(value[j])
        
        final_number_packet_arrival = [list() for i in range(number_application)]
        for i in range(len(number_packet_arrival)):
            final_number_packet_arrival[i%number_application].append(number_packet_arrival[i])

        packet_loss = list()
        for i in buffer_values:
            name = i.name.tolist()
            value = i.value.tolist()
            for j in range(len(i)):
                if name[j] == "pack loss":
                    packet_loss.append(value[j])
            
        final_packet_loss = [list() for i in range(number_application)]
        for i in range(len(packet_loss)):
            final_packet_loss[i%number_application].append(packet_loss[i])

        application_list = [list() for i in range(number_application)]
        for i in range(number_application):
            application_list[i].append(i)
            application_list[i].append(final_latency[i])
            application_list[i].append(final_number_packet_arrival[i])
            application_list[i].append(final_packet_loss[i])
        return application_list

    def omnet_read_csa_file(self, number_application):
        """
        read the file and return the result values
        """
        self.convert_to_csv_file()
        result = self.get_result_array(number_application= number_application)
        return result

    def omnet_run_simulation(self):
        cmd = omnet_settings.get_simulation_cmd()
        with subprocess.Popen(cmd, stdout=subprocess.PIPE, cwd = omnet_settings.get_omnet_directory()) as proc:
            return (proc.stdout.readlines()[-1].decode("utf8") == "End.\n")



    
# # cmd = ['ls']
# cmd = ['./Metro_SC', '-u', 'Cmdenv', '-f', 'test_run.ini']
# # cmd = ['ls', '-a']
# # out = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# # o,e = out.communicate()
# # subprocess.run(['cd /home/dat_luong/project_tue/omnet/omnetpp-5.6.2/samples/Metro_SC'])


    #     print("False")
    # print("True")

    