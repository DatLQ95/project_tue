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
webserver_pattern = [1,1,1,3,3,3,3,4,6,4,4]
user_server_pattern = [ 
    [1,1,1,3,3,3,3,4,6,4,4],
    [1,1,1,3,3,3,3,4,6,4,4],
    [1,1,1,3,3,3,3,4,6,4,4],
    [1,1,1,3,3,3,3,4,6,4,4]
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

