class NetworkFunction():
    def __init__(self, bandwidth_pattern, cpu = None, memory = None, storage = None, env = None, node = None, application_index = None):
        self.bandwidth_pattern = bandwidth_pattern
        self.cpu = cpu
        self.memory = memory
        self.storage = storage
        self.env = env
        self.node = node
        self.application_index = application_index

    def get_load(self):
        return self.bandwidth_pattern[self.env.get_time_step()]

    def get_cpu_demand(self):
        return self.cpu

    def get_memory_demand(self):
        return self.memory

    def get_storage_demand(self):
        return self.storage

    def get_application_index(self):
        return self.application_index

