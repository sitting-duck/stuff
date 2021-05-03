import os
import glob
from pathlib import Path

def get_cpu():
    with open("sysinfo.txt", "r") as sys:
        sys.seek(0)
        out = sys.read()
        lines = out.splitlines()
        for line in lines:
            if "Processor: " in line:
                cpu = line.split(": ")[1]
                return cpu
    return "NONE_FOUND"

def get_cpu_memory():
    with open("sysinfo.txt", "r") as sys:
        sys.seek(0)
        out = sys.read()
        lines = out.splitlines()
        i = 0
        for line in lines:
            i = i+1
            if "Processor: " in line:
                memory_line = lines[i]
                mem = memory_line.split(": ")[1]
                mem = mem.replace(" RAM", "")
                #mem = mem.replace("MB", "")
            
                #if(len(mem) == 6 and mem[0] == "2" and mem[1] == "9"):
                #    mem = "30"

                return mem
        return "NONE_FOUND"
                
def get_selected_gpu(i):
    files = glob.glob("*" + str(i) + ".txt")
    for f in files:
        with open(f, "r") as txtFile:
            txtFile.seek(0)
            out = txtFile.read()
            lines = out.splitlines()
            for line in lines:
                if "SELECTED GPU: " in line:
                    device = line.split(": ")[1]
                    size = line.split("size: ")
#                    csvFile.write("SIZE, " + size + ", ")
                    #print("mah device: " + str(device))
                    return device
            return "NONE_FOUND"

def split_into_devices(lines):
    devices = []

    device = {}
    for line in lines:
        #print("line: " + line)
        if "Card name:" in line:
            devices.append(device)
            device = {}

        if ": " in line:
            tokens = line.split(":")
            key = tokens[0]
            key = key.replace(" ", "")
            value = tokens[1]
            value = value[1:]
            device[key] = value
    devices.append(device)

    #for d in devices:
    #    #print("mah device: " + d["Cardname"])
    #    for key, value in d.items():
    #        if key == "Cardname":
    #            print(key, ": ", value)

    devices.pop(0) # first item is empty object
    return devices

def get_display_devices():
    with open("sysinfo.txt", "r") as sys:
        sys.seek(0)
        out = sys.read()
        lines = out.splitlines()
        for i in range(0, len(lines)):
            line = lines[i]
            if "Display Devices" in line:
                device_lines = []
                while "Sound Devices" not in line:
                    device_lines.append(line)
                    i = i + 1
                    line = lines[i]

    # now we create a dictionary from the seqment of lines we have just captured
    devices = split_into_devices(device_lines)
    return devices
                                

def get_gpu_memory():
    with open("sysinfo.txt", "r") as sys:
        sys.seek(0)
        out = sys.read()
        lines = out.splitlines()
        for line in lines:
            if "Dedicated Memory: " in line:
                devices = get_display_devices()
                gpu_mem = devices[0]["DedicatedMemory"]
                #gpu_mem = gpu_mem.replace(" MB", "")
                gpu_mem = gpu_mem.replace(" ", "")
                print("gpu_mem: " + gpu_mem)
                #if len(gpu_mem) == 3:
                #    gpu_mem = str(0)
                #elif len(gpu_mem) == 4 and gpu_mem[0] == '8':
                #    gpu_mem= str(8)
                return gpu_mem


def selected_gpu_found(lines):
    for line in lines: 
        if "SELECTED_GPU" in line:
            return True
    return False

def onnx_problem(lines):
    for line in lines:
        if"ONNX problem" in line:
            return True
    return False

def get_pretty_name(net_name):
    if "model1" in net_name:
        pretty_name = "model1"
    elif "model2" in net_name:
        pretty_name = "model2"
    elif "model3" in net_name:
        pretty_name = "model3"
    else:
        pretty_name = "NONE_FOUND"
    return pretty_name

def get_scale(net_name):
    if "1X" in net_name:
        return "1"
    elif "2X" in net_name:
        return "2"
    else:
        return "4"

def get_block_multiply(net_name):
    return ""



# begin execution
path = "C:\\logs\\"
os.chdir(path)


with open("csv.csv", "w+") as csvFile:

    csvFile.write("User, CPU, RAM, GPU, VRAM, model1, model2, model3\n")

    os.chdir(path)
    stuff = os.listdir(path)
    folders = []
    for item in stuff:
        if os.path.isdir(item):
            folders.append(item)

    for folder in folders:

        os.chdir(path + folder + "\\logs\\")
       
        for i in range(0, 3):

            files = glob.glob("*" + str(i) + ".txt")
            if len(files) > 0:
                gpu = get_selected_gpu(str(i))
                if gpu == "Intel(R) UHD Graphics 630" or  gpu == "Intel(R) HD Graphics 4600":
                    continue

                print("folder: " + folder)
                csvFile.write(folder + ", ")
                cpu = get_cpu()
                csvFile.write('"' + cpu + '", ')

                cpu_mem = get_cpu_memory()
                csvFile.write(cpu_mem + ", ")

                gpu = get_selected_gpu(str(i))
                csvFile.write('"' + str(gpu) + '", ')
                
                devices = get_display_devices()
                for device in devices:
                    if device["Cardname"] == gpu:
                        gpu_mem = device["DedicatedMemory"]
                        csvFile.write(gpu_mem + ", ")
                        break
                #gpu_mem = get_gpu_memory()

            for f in files:

                with open(f, "r") as txtFile:
                    txtFile.seek(0)
                    out = txtFile.read()
                    lines = out.splitlines()

                    net_name = f.replace(".txt", "")
                    pretty_name = get_pretty_name(net_name)

                    scale = get_scale(net_name)

                    block_multiply = get_block_multiply(net_name)

                    #csvFile.write(f.replace(".txt", "") + ", ") # write down the net name

                    if(onnx_problem(lines)):
                        #csvFile.write("ONNX_PROBLEM[" + pretty_name + " " + scale + " " + block_multiply + "]\n")
                        #csvFile.write("ONNX_PROBLEM, ")
                        csvFile.write("-1, ")
                    else:
                        numtime = 0
                        sumtime = 0
                        for line in lines:
                            if "TIME: " in line and "TOTAL" not in line:
                                tokens = line.split(" ")
                            
                                if tokens[0] != "0":
                                   numtime = numtime + 1
                                   time = tokens[2]
                                   sumtime = sumtime + float(time)

                                #_, time = line.split("TIME: ")
                                #csvFile.write(time + "[TIME " + pretty_name + " " + scale + " " + block_multiply + "]\n")  # write down the time taken
                        avg_time = sumtime/numtime
                        csvFile.write(str(avg_time) + ", ")  # write down the time taken
            
            files = glob.glob("*" + str(i) + ".txt")
            if len(files) > 0:
                csvFile.write("\n") # new card, new line
            
    csvFile.close()
            
