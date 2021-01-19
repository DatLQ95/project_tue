#----------------------------------------------------------------------------------------------
#Time environment setting:
node_number = 4
class environment_network():
    def __init__(self):
        self.timestep = 0

    def get_time_step(self):
        return self.timestep

    def increase_time_step(self):
        self.timestep = self.timestep + 1

    def get_node_number():
        return node_number

#----------------------------------------------------------------------------------------------
#Webserver application setting:
webserver_pattern = [0.52,0.64,0.76,0.93,0.86,0.65,0.55,0.51,0.42,0.32,0.21]
user_server_pattern = [ 
    [0.01,0.01,0.012,0.013,0.009,0.008,0.005,0.007,0.004,0.008,0.009],
    [0.012,0.02,0.02,0.013,0.009,0.002,0.006,0.007,0.004,0.068,0.059],
    [0.02,0.025,0.01,0.013,0.009,0.028,0.015,0.027,0.024,0.048,0.039],
    [0.05,0.052,0.02,0.043,0.029,0.048,0.025,0.037,0.054,0.068,0.039]
]

webserver_cpu_demand = 2
webserver_memory_demand = 4
webserver_storage_demand = 30
user_number = 4
priority = 1

class webserver_setting():
    def get_webserver_pattern():
        return webserver_pattern

    def get_user_server_pattern():
        return user_server_pattern
    
    def get_webserver_cpu_demand():
        return webserver_cpu_demand

    def get_webserver_memory_demand():
        return webserver_memory_demand

    def get_webserver_storage_demand():
        return webserver_storage_demand

    def get_user_number():
        return user_number

    def get_priority():
        return priority
    
#----------------------------------------------------------------------------------------------
#EdgeComputing:
edgecomputing_cpu = 20
edgecomputing_storage = 400
edgecomputing_memory = 30
edgecomputing_bandwidth = 4

class edgecomputing_settings():
    def get_cpu():
        """
        docstring
        """
        return edgecomputing_cpu

    def get_storage():
        """
        docstring
        """
        return edgecomputing_storage

    def get_memory():
        """
        docstring
        """
        return edgecomputing_memory

    def get_bandwidth():
        """
        docstring
        """
        return edgecomputing_bandwidth

#----------------------------------------------------------------------------------------------
#Omnet settings:
file_directory = "/home/dat_luong/project_tue/omnet/omnetpp-5.6.2/samples/Metro_SC/test.ini"

ini_file_content = "[General]\nnetwork = Metro_SC\ncpu-time-limit = 180s\ndebug-on-errors = true\n\n**.Nodes = 4#${Nodes = 4,8,16}\n**.Channel = 32# ${Channel = 4,8,16,32}\n**.buffer[*].capacity = 10\n**.Txcount = 2\n##**.Rxcount = ${Rxcount = 2,3,4,5,6}\n**.Rxcount = 2\n**.slot = 1e-6"

omnet_directory = "/home/dat_luong/project_tue/omnet/omnetpp-5.6.2/samples/Metro_SC"

result_directory = omnet_directory + "/results"

run_sim_cmd = ['./Metro_SC', '-u', 'Cmdenv', '-f', 'test.ini']

convert_to_csv_cmd = ['scavetool', 'x', 'General-#0.sca', '-o', 'result.csv']

csv_file_directory = '/home/dat_luong/project_tue/omnet/omnetpp-5.6.2/samples/Metro_SC/results/result.csv'

class omnet_settings():
    def get_file_resporatory():
        return file_directory

    def get_ini_file_content():
        return ini_file_content

    def get_simulation_cmd():
        return run_sim_cmd

    def get_omnet_directory():
        return omnet_directory

    def get_convert_to_csv_cmd():
        return convert_to_csv_cmd

    def get_result_directory():
        return result_directory

    def get_csv_file_directory():
        return csv_file_directory
