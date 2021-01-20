from simulation_classes.EdgeComputing import EdgeComputing
from simulation_classes.simulation_settings import environment_network, webserver_setting, uniform_setting
from simulation_classes.Application import Application
from simulation_classes.Network import Network
from simulation_classes.Omnet import Omnet



class Simulation():
    def __init__(self):
        self.network = Network()
        self.omnet = Omnet()
        self.env = environment_network()
        self.application_number = 0
        self.applications = list()
        self.report_data = list()
        self.add_application(application_index = 1, application_type= 1, priority=2)
        self.add_application(application_index = 2, application_type= 1, priority=4)
        self.add_application(application_index = 3, application_type= 1, priority=7)

        pass

    def add_application(self, application_index, application_type, priority):
        if(application_type == 1):
            self.applications.append(Application(application_index=application_index, env= self.env, server_pattern= webserver_setting.get_webserver_pattern(), user_patern=webserver_setting.get_user_server_pattern(), memory_demand=webserver_setting.get_webserver_memory_demand(), cpu_demand=webserver_setting.get_webserver_cpu_demand(), storage_demand=webserver_setting.get_webserver_storage_demand(), user_number= webserver_setting.get_user_number(), priority= priority))
        elif (application_type == 2):
            self.applications.append(Application(application_index=application_index, env= self.env, server_pattern= uniform_setting.get_uniform_pattern(), user_patern=uniform_setting.get_user_uniform_pattern(), memory_demand=uniform_setting.get_uniform_memory_demand(), cpu_demand=uniform_setting.get_uniform_cpu_demand(), storage_demand=uniform_setting.get_uniform_storage_demand(), user_number= uniform_setting.get_uniform_user_number(), priority= priority))
        else:
            #TODO: create new applications type here:
            pass
        pass

    def get_application(self, application_index):
        for i in self.applications:
            if (i.get_application_index() == application_index):
                return i

    def deploy_application(self, action):
        # Compare and see if the application is already deployed or not?
        for i in action.keys():
            if(not self.network.is_application_belongs_to_node(application_index= i, node_index= action.get(i))):

                if(self.network.deploy_application(application= self.get_application(application_index= i), node_index= action.get(i))):
                    self.application_number = self.application_number + 1
                else:
                    # can not deploy the application, due to 
                    pass
                #TODO: test this module!
                #check if application is deployed in other node, then delete it
                node_deployed = self.network.is_application_belongs_to_other_node(application= self.get_application(application_index= i), node_index= action.get(i))
                if(node_deployed != -1):
                    self.network.remove_application(application= self.get_application(application_index= i), node_index= node_deployed)
                    self.application_number = self.application_number - 1
                else:
                    pass
            else :
                #already in the node, no need to do anything!
                # update load value:
                self.network.update_load_value(application= self.get_application(application_index= i), node_index= action.get(i))
                pass
        pass

    def init_applications(self):
        """
        run simulation with specific parameters
        """
        web_server_application = Application(application_index=1, env= self.env, server_pattern= webserver_setting.get_webserver_pattern(), user_patern=webserver_setting.get_user_server_pattern(), memory_demand=webserver_setting.get_webserver_memory_demand(), cpu_demand=webserver_setting.get_webserver_cpu_demand(), storage_demand=webserver_setting.get_webserver_storage_demand(), user_number= webserver_setting.get_user_number(), priority= webserver_setting.get_priority()
        )

        web_server_application2 = Application(application_index=2, env= self.env, server_pattern= webserver_setting.get_webserver_pattern(), user_patern=webserver_setting.get_user_server_pattern(), memory_demand=webserver_setting.get_webserver_memory_demand(), cpu_demand=webserver_setting.get_webserver_cpu_demand(), storage_demand=webserver_setting.get_webserver_storage_demand(), user_number= webserver_setting.get_user_number(), priority= webserver_setting.get_priority()
        )

        web_server_application3 = Application(application_index=3, env= self.env, server_pattern= webserver_setting.get_webserver_pattern(), user_patern=webserver_setting.get_user_server_pattern(), memory_demand=webserver_setting.get_webserver_memory_demand(), cpu_demand=webserver_setting.get_webserver_cpu_demand(), storage_demand=webserver_setting.get_webserver_storage_demand(), user_number= webserver_setting.get_user_number(), priority= webserver_setting.get_priority()
        )

        if(self.network.deploy_application(application= web_server_application, node_index= 1)):
            self.application_number = self.application_number + 1
            
        if(self.network.deploy_application(application= web_server_application2, node_index= 3)):
            self.application_number = self.application_number + 1

        if(self.network.deploy_application(application= web_server_application3, node_index= 1)):
            self.application_number = self.application_number + 1


        self.network.status()
        # pass

    def create_ini_file(self):
        self.omnet.omnet_ini_file_create(self.network.get_source_list(), self.application_number)
        pass

    def run(self,action):
        """
        docstring
        """
        self.deploy_application(action=action)
        self.create_ini_file()
        self.network.status()
        if (self.omnet.omnet_run_simulation()):
            # get data file
            result = self.omnet.omnet_read_csa_file(number_application = self.application_number)
            print(result)
            self.report_data.append(result)
            self.env.increase_time_step()
            pass
        else: 
            pass

    def get_report(self):
        """
        docstring
        """
        return self.report_data

simulation = Simulation()
action = {1: 1, 2: 1, 3: 1}
for i in range(3):
    simulation.run(action)
simulation.get_report()