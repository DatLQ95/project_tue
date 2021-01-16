from .NetworkFunction import NetworkFunction
from .simulation_settings import environment_network, webserver_setting

class Application():
    def __init__(self, env, priority, application_index, server_pattern, user_patern, memory_demand, cpu_demand, storage_demand, user_number):
        self.application_index = application_index
        self.priority = priority
        self.user_number = user_number
        self.server = NetworkFunction(bandwidth_pattern=server_pattern, cpu=cpu_demand, memory=memory_demand, storage=storage_demand, env=env, application_index= self.application_index)
        self.user = [NetworkFunction(bandwidth_pattern=user_patern[i], env=env, application_index= self.application_index) for i in range(self.user_number)]
        
    def get_application_cpu_demand(self):
        """
        docstring
        """
        return self.server.get_cpu_demand()

    def get_application_memory_demand(self):
        """
        docstring
        """
        return self.server.get_memory_demand()

    def get_application_storage_demand(self):
        """
        docstring
        """
        return self.server.get_storage_demand()

    def get_application_ratio_user(self, node_index):
        """
        docstring
        """
        user_loads = [self.user[i].get_load() for i in range(self.user_number)]
        return [user_loads[i] / sum(user_loads) for i in range(len(user_loads)) if i != node_index]

    def get_dst_user(self, node_index):
        return [i for i in range(self.user_number) if i != node_index]

    def get_user_number(self):
        return self.user_number

    def get_application_priority(self):
        return self.priority

    def get_application_load(self):
        return self.server.get_load()

    def get_user_load(self, node_index):
        return self.user[node_index].get_load()
    
    def get_application_index(self):
        """
        docstring
        """
        return self.application_index
    