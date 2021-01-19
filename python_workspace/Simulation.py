from simulation_classes.EdgeComputing import EdgeComputing
from simulation_classes.simulation_settings import environment_network, webserver_setting
from simulation_classes.Application import Application
from simulation_classes.Network import Network
from simulation_classes.Omnet import Omnet



class Simulation():
    def __init__(self, env):
        self.network = Network()
        self.omnet = Omnet()
        self.env = env
        self.application_number = 0
        pass

    def init_applications(self):
        """
        run simulation with specific parameters
        """
        # web_server_application = Application(application_index=1, env= self.env, server_pattern= webserver_setting.get_webserver_pattern(), user_patern=webserver_setting.get_user_server_pattern(), memory_demand=webserver_setting.get_webserver_memory_demand(), cpu_demand=webserver_setting.get_webserver_cpu_demand(), storage_demand=webserver_setting.get_webserver_storage_demand(), user_number= webserver_setting.get_user_number(), priority= webserver_setting.get_priority()
        # )
        # self.network.deploy_application(application= web_server_application, node_index= 0)

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

    def run(self):
        """
        docstring
        """
        if (self.omnet.omnet_run_simulation()):
            # get data file
            print(self.omnet.omnet_read_csa_file(number_application = self.application_number))
            pass
        else: 
            pass

    def funcname(parameter_list):
        """
        docstring
        """
        pass

env = environment_network()
simulation = Simulation(env=env)
simulation.init_applications()
simulation.create_ini_file()
simulation.run()
