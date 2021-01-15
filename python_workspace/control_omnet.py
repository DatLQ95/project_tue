import subprocess
# cmd = ['ls']
cmd = ['./Metro_SC', '-u', 'Cmdenv', '-f', 'test_run.ini']
# cmd = ['ls', '-a']
# out = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# o,e = out.communicate()
# subprocess.run(['cd /home/dat_luong/project_tue/omnet/omnetpp-5.6.2/samples/Metro_SC'])

with subprocess.Popen(cmd, stdout=subprocess.PIPE) as proc:
    print(proc.stdout.readlines()[-1].decode("utf8"))
    #     print("False")
    # print("True")