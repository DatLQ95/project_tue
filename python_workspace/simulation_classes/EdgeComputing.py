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
        self.application_index_list = list()
        self.user_list = list()
        pass

    def deploy_user(self, application, application_dst):
        """
        user in the next node of application node will be index 0 -> last user index 2 
        """
        self.user_list.append(application.get_application_index())
        self.source.append([application.get_user_load(node_index=self.node_index), application.get_application_index(), application_dst])
        pass

    def deploy_application(self, application, application_dst):
        """
        deploy application to specific node destination which is application_dst variable
        """
        #TODO: add bandwidth condition here also!!!
        if(self.cpu >= application.get_application_cpu_demand() and self.memory >= application.get_application_memory_demand() and self.storage >= application.get_application_storage_demand()):
            self.application_index_list.append(application.get_application_index())
            self.cpu = self.cpu - application.get_application_cpu_demand()
            self.memory = self.memory - application.get_application_memory_demand()
            self.storage = self.storage - application.get_application_storage_demand()
            for i in range(application.get_user_number() - 1):
                self.source.append([round(application.get_application_load() * application.get_application_ratio_user(node_index=application_dst)[i], 3), application.get_application_index(), application.get_dst_user(node_index=application_dst)[i]])
            return True
        else : 
            return False

    def remove_application(self, application):
        """
        docstring
        """
        self.cpu = self.cpu + application.get_application_cpu_demand()
        self.memory = self.memory + application.get_application_memory_demand()
        self.storage = self.storage + application.get_application_storage_demand()
        self.application_index_list.remove(application.get_application_index())
        for i in self.source:
            if (i[1] == application.get_application_index()):
                self.source.remove(i)

    def remove_user(self, application):
        for i in self.source:
            if (i[1] == application.get_application_index()):
                self.source.remove(i)
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

    def is_contain_application(self, application_index):
        return application_index in self.application_index_list

    def is_contain_user(self, application_index ):
        return application_index in self.user_list

    def update_application_load_value(self, application, application_dst):
        source_list = list()
        for i in self.source:
            if (i[1] != application.get_application_index()):
                source_list.append(i)
        self.source = source_list
        for i in range(application.get_user_number() - 1):
            self.source.append([round(application.get_application_load() * application.get_application_ratio_user(node_index=application_dst)[i], 3), application.get_application_index(), application.get_dst_user(node_index=application_dst)[i]])

    def update_user_load_value(self, application, application_dst):
        source_list = list()
        for i in self.source:
            if i[1] != application.get_application_index():
                source_list.append(i)
        self.source = source_list
        self.source.append([application.get_user_load(node_index=self.node_index), application.get_application_index(), application_dst])       
