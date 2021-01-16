from simulation_classes.EdgeComputing import EdgeComputing
from simulation_classes.simulation_settings import environment_network, webserver_setting
from simulation_classes.Application import Application
from simulation_classes.Network import Network


class Simulation():
    def __init__(self, env):
        self.network = Network()
        self.env = env
        pass

    def init_applications(self):
        """
        run simulation with specific parameters
        """
        web_server_application = Application(application_index=1, env= self.env, server_pattern= webserver_setting.get_webserver_pattern(), user_patern=webserver_setting.get_user_server_pattern(), memory_demand=webserver_setting.get_webserver_memory_demand(), cpu_demand=webserver_setting.get_webserver_cpu_demand(), storage_demand=webserver_setting.get_webserver_storage_demand(), user_number= webserver_setting.get_user_number(), priority= webserver_setting.get_priority()
        )
        self.network.deploy_application(application= web_server_application, node_index= 0)
        # self.network.status()
        print(self.network.get_source_list())
        # pass

    def create_ini_file(self):

        pass

    def run(parameter_list):
        """
        docstring
        """

        pass

    def funcname(parameter_list):
        """
        docstring
        """
        pass

env = environment_network()
simulation = Simulation(env=env)
simulation.init_applications()
