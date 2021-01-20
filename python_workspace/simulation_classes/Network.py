from .EdgeComputing import EdgeComputing
from .simulation_settings import environment_network

class Network():
    def __init__(self):
        self.edges = [EdgeComputing(node_index= i) for i in range(environment_network.get_node_number())]
        pass

    def deploy_application(self, application, node_index):
        if(self.edges[node_index].deploy_application(application=application, application_dst = node_index)):
            for i in range(application.get_user_number()):
                if(i == node_index):
                    continue
                else:
                    self.edges[i].deploy_user(application=application, application_dst= node_index)
            return True
        else:
            return False

    def get_source_list(self):
        return [i.get_source_list() for i in self.edges]

    def status(self):
        for i in self.edges:
            i.status()
    
    def is_application_belongs_to_node(self, application_index, node_index):
        return self.edges[node_index].is_contain_application(application_index)

    def is_application_belongs_to_other_node(self, application, node_index):
        for i in range(environment_network.get_node_number()):
            if(i == node_index):
                continue
            else:
                if(self.edges[i].is_contain_application(application.get_application_index())):
                    return i
        return -1

    def remove_application(self, application, node_index):
        self.edge[node_index].remove_application(application)
        for i in range(application.get_user_number()):
            if(i == node_index):
                continue
            else:
                self.edges[i].remove_user(application=application)

    def update_load_value(self,application, node_index):
        for i in range(environment_network.get_node_number()):
            if(i == node_index):
                self.edges[i].update_application_load_value(application= application, application_dst= node_index)
            else:
                if(self.edges[i].is_contain_user(application_index=application.get_application_index())):
                    self.edges[i].update_user_load_value(application, node_index)
                
            
                
    