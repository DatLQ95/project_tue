import urllib.request, json 
import time
from threading import Thread
from threading import Event
import numpy

class NetData(Thread):
    def __init__(self, event):
        Thread.__init__(self)
        self.stopped = event
        self.received_data = "./media_received_data.dat"
        self.sent_data = "./media_sent_data.dat"

    def run(self):
        # run this for a lot of time
        while not self.stopped.wait(1):
            # exception control here:
            with urllib.request.urlopen("http://131.155.35.53:19999/api/v1/allmetrics?format=json") as url:
                data = json.loads(url.read().decode())
                with open(self.received_data, 'a') as out:
                    out.write(str(data["net.eno1"]["dimensions"]["received"]["value"]) + ', ')
                with open(self.sent_data, 'a') as out:
                    out.write(str(data["net.eno1"]["dimensions"]["sent"]["value"]) + ', ')
                
                # data_get=[data["net.eno1"]["dimensions"]["received"]["value"], data["net.eno1"]["dimensions"]["sent"]["value"]]
                print(data["net.eno1"]["dimensions"]["received"]["value"])
                print(data["net.eno1"]["dimensions"]["sent"]["value"])

    def getData():
        pass


# netData = NetData()
# print(netData.getMetric())

stopFlag = Event()
thread = NetData(stopFlag)
thread.start()
# this will stop the timer
# stopFlag.set()


# print(data["net.eno1"]["dimensions"]["received"]["value"])
# print(data["mem.available"]["dimensions"]["MemAvailable"]["value"])
# print(data["system.load"]["dimensions"]["load15"]["value"])
