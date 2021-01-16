from .simulation_settings import edgecomputing_settings

class EdgeComputing():
    def __init__(self, node_index):
        """
        docstring
        """
        self.cpu = edgecomputing_settings.get_cpu()
        self.memory = edgecomputing_settings.get_memory()
        self.storage = edgecomputing_settings.get_storage()
        self.bandwidth = edgecomputing_settings.get_bandwidth()
        self.node_index = node_index
        self.source = list()
        pass

    def deploy_user(self, application, application_dst):
        """
        user in the next node of application node will be index 0 -> last user index 2 
        """
        self.source.append([application.get_user_load(node_index=self.node_index), application.get_application_index(), application_dst])
        pass

    def deploy_application(self, application, application_dst):
        """
        deploy application to specific node destination which is application_dst variable
        """
        if(self.cpu >= application.get_application_cpu_demand() and self.memory >= application.get_application_memory_demand() and self.storage >= application.get_application_storage_demand()):
            self.cpu = self.cpu - application.get_application_cpu_demand()
            self.memory = self.memory - application.get_application_memory_demand()
            self.storage = self.storage - application.get_application_storage_demand()
            for i in range(application.get_user_number() - 1):
                self.source.append([application.get_application_load() * application.get_application_ratio_user(node_index=application_dst)[i], application.get_application_index(), application.get_dst_user(node_index=application_dst)[i]])
            return True
        else : 
            return False

    def remove_application(self, parameter_list):
        """
        docstring
        """
        pass

    def status(self):
        """
        docstring
        """
        print(self.node_index)
        print(self.source)
        pass

    def get_source_list(self):
        return self.source