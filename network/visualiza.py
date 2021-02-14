import matplotlib.pyplot as plt
from numpy import loadtxt
import csv
with open('received_data.dat', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',')
    for row in spamreader:
        # do something
        print(float(row[100]))
