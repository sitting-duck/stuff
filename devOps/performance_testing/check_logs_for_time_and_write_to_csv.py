# This script shows an example of a script I might write to check the logs for performance times, write all those times into a .csv file, which 
# can then be loaded into a spreadsheet for performance analysis. 
# Automated log checkers like this can make it easy to detect a regression automatically, on a regular basis. 
# You could attach this to your nighly builds on Jenkins for example if they run the program they have just built on the command line, and then 
# generate a nighly report.


import os, glob, math

def get_average_time(times):    
    # get the times, remove the smallest and largest one,average the rest
    # why remove the smallest and the largest time? 
    # the first time is always the largest because the model is loaded the first time, and all the other times a cached model is used,
    # the smallest time is also removed just for the sake of removing outliers and giving us more of an idea of what the average time was
    # you should run the model at least 10 times and take the average of all these times to get meaningful performance, 
    # GPU performance can vary a lot depending on what the computer is doing, temperature etc, so this helps clarify signal and reduce noise in your data

    #print("times: " + str(times))
    times.remove(max(times))
    times.remove(min(times))
    avg = sum(times)/len(times)
    avg = math.floor(avg)
    return avg

csvFile =  open("csv.csv", "w+")
csvFile.write("Model Name, ProcTime1, ProcTime2, ProcTime3\n")

for logfilename in glob.glob("*.log"):
    print("logfilename: " + logfilename)
    logfile = open(logfilename, "r")
    lines = logfile.readlines()
    times = []
    post_detail_times = []
    for line in lines:
        if "ProcTime1" in line: 
            model = line.split("ProcTime1: ")[1].replace(" ", "")
            model = model.replace("\"", "")
            
        if "ProcTime2" in line: 
            time = line.split("Proc")[1].replace(" ", "") # in ms
            time = time.replace("ms", "")
            times.append(int(time))
            
        if "ProcTime3" in line: 
            time = line.split("Proc")[1].replace(" ", "") # in ms
            time = time.replace("second", "millisecond")
            times.append(int(time))

    logfile.close()

    if len(times) > 1:
        avg_time = get_average_time(times)
        print("avg time: " + str(avg_time))


    csvFile.write(str(logfilename+", "+str(avg_time)+"\n"))

csvFile.close()
