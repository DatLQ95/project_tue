from Simulation import Simulation
from simulation_classes.simulation_settings import environment_network


# env = environment_network()
# simulation = Simulation(env=env)
# simulation.init_applications()
# simulation.create_ini_file()
# simulation.run()

class Control():
    def __init__(self):
        self.env = environment_network()
        self.simulation = Simulation(env=self.env)
        self.result = list()
        self.record_data = list()
        pass

    def send_action(self):
        self.deploy_application()
        self.result = self.simulation.run()
        pass

    def add_applications(self):
        self.simulation.add_application(application_index = 1, application_type= 1, priority=2)
        self.simulation.add_application(application_index = 2, application_type= 2, priority=4)
        self.simulation.add_application(application_index = 3, application_type= 2, priority=7)
        pass

    def control_record(self):
        self.record_data.append(self.result)
        self.env.increase_time_step()
        pass

    def get_report(self):
        return self.record_data

control = Control()
control.add_applications()
for i in range(3):
    control.send_action()
    control.control_record()

print(control.get_report())