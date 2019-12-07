import os
from multiprocessing import Lock
import json

from jobs_bork import *

jobs_bork = jobs_tool("0")

jobs = []

json_file = open("jobs.json", 'w+')
json.dump(jobs, json_file)
json_file.close()

# add a new job to the list
job1 = { "job1": "do the dishes" }
jobs.append(job1)

json_file = open("jobs.json", 'w')
#json.dump(jobs, json_file)
json_file.write(json.dumps(jobs, sort_keys=True, indent=4))
json_file.close()

json_file = open("jobs.json", 'w')
job2 = { "job2": "sweep the floors" }
jobs.append(job2)
json.dump(jobs, json_file)
json_file.close()

