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

    