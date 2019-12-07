import os
from multiprocessing import Lock
import json

class jobs_tool:
    def __init__(self, gpu):
        self.file_path = "../working/job_in_progress." + gpu + ".json"

        self.lock = Lock()

    def get_job(self):
        self.lock.acquire()
        jobs_file = open(self.file_path, "rw")
        jobs_list = json.load(jobs_file)
        job = jobs_list[0] #jobs_list.pop(0)
        jobs_list_str = json.dumps(jobs_list)
        jobs_file.write(jobs_list_str)
        jobs_file.close()
        return job

    # Add a job to the current jobs file to indicate that this job is currently being processed.
    # This job is basically a message that we got from an SQS queue. It is deleted from queue immediately 
    # after it is pulled down, so this file is here to make sure we don't lose it in case the process crashes
    def add_job(self, job):
        print("add_job():")
        self.lock.acquire()
        if os.path.exists(self.file_path):
            jobs_file = open(self.file_path, 'w')
            try:
                jobs_list = json.load(jobs_file)
            except:
                print("\texception loading job in progress file")
                jobs_list = []
                jobs_file = open(self.file_path, 'w')
                jobs_file.write(json.dumps(jobs_list, sort_keys=True, indent=4))

            jobs_list.append(job)
            jobs_file.write(json.dumps(jobs_list, sort_keys=True, indent=4))
            print("write to file: ", json.dumps(jobs_list, sort_keys=True, indent=4))
            jobs_file.close()
        else:
            jobs_file = open(self.file_path, 'w+')
            jobs_list = []
            jobs_file.write(json.dumps(jobs_list))
            print("write to file: ", json.dumps(jobs_list))
            jobs_file.close()

        self.lock.release()        

    # Check if there are any unfinished jobs in the job file
    # Jobs are deleted from this file when they are finished. 
    # If you find a job in here it is either currently being processed by this server, or it failed 
    # during the process invokation to finish and get deleted from this file to indicated it is done
    def unfinished_jobs(self):
        print("unfinished_jobs(): ") 
        self.lock.acquire()        
        is_job = False
        if os.path.exists(self.file_path):
            jobs_file = open(self.file_path, 'r')
            try:
                jobs_list = json.load(jobs_file)
            except:
                print("\texception loading job in progress file")
                jobs_list = []
                jobs_file = open(self.file_path, 'w')
                jobs_file.write(json.dumps(jobs_list))                

            print("\tfrom file: ")
            print(jobs_list)
            
            if len(jobs_list) > 0:
                print("\tJobs file contains unfinished jobs")
                is_job = True

            jobs_file.close()
            
        else:
            print("\tcreate jobs file: ")
            jobs_file = open(self.file_path, 'w+')
            jobs_list = []
            jobs_file.write(json.dumps(jobs_list))
            print("\twrite to file: ", json.dumps(jobs_list))
            jobs_file.close()
            

        self.lock.release()
        return is_job