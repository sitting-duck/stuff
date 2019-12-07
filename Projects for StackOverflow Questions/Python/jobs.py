import os
from multiprocessing import Lock
import json

class jobs_tool:
    def __init__(self, gpu):
        self.file_path = "../working/job_in_progress." + gpu + ".json"

        self.lock = Lock()

    def delete_job(self, session_id):
        print("get_job()")
        self.lock.acquire()
        jobs_file = open(self.file_path, "r")
        jobs_list = json.load(jobs_file)
        jobs_file.close()
        i = -1
        for job in jobs_list:
            i = i + 1
            print("i: ", i)
            if job["SessionId"] == session_id:
                found = True
                break

        if i != -1 and found == True:
            jobs_list.pop(i)
            print("\tremoved job with session id: ", session_id)
        else:
            print("job not found, nothing deleted")

        jobs_file = open(self.file_path, "w")

        json.dump(jobs_list, jobs_file, indent=4, sort_keys=True)
        jobs_file.close()
        self.lock.release()
        return job

    def pop_job(self):
        print("pop_job()")
        self.lock.acquire()
        jobs_file = open(self.file_path, "r")
        jobs_list = json.load(jobs_file)
        job = jobs_list.pop(0)
        jobs_file.close()

        jobs_file = open(self.file_path, 'w')
        json.dump(jobs_list, jobs_file)
        jobs_file.close()
        self.lock.release()
        return job

    # Add a job to the current jobs file to indicate that this job is currently being processed.
    # This job is basically a message that we got from an SQS queue. It is deleted from queue immediately 
    # after it is pulled down, so this file is here to make sure we don't lose it in case the process crashes
    def add_job(self, job):
        print("add_job():")
        self.lock.acquire()
        if os.path.exists(self.file_path):
            jobs_file = open(self.file_path, 'r')

            try:
                jobs_file.seek(0)
                jobs_list = json.load(jobs_file)
                print("got jobs_list: ", jobs_list)
            except Exception as e:
                print("\texception loading json file: ", str(e))
                jobs_list = []
                jobs_file = open(self.file_path, 'w')

                json.dump(jobs_list, jobs_file, indent=4, sort_keys=True)

            jobs_file.close()

            jobs_list.append(job)
            #jobs_list_str = json.dumps(jobs_list, sort_keys=True, indent=4)
            print("jobs_list after append: ", jobs_list)

            #jobs_file.truncate(0) # clear the file
            #jobs_file.write(jobs_list_str)
            jobs_file = open(self.file_path, 'w')
            jobs_file.truncate(0) # clear the file
            json.dump(jobs_list, jobs_file, indent=4, sort_keys=True)
            #print("write to file: ", jobs_list_str)
            jobs_file.close()
        else:
            jobs_file = open(self.file_path, 'w+')
            jobs_list = []
            json.dump(jobs_list, jobs_file)
            #jobs_file.truncate(0) # clear the file
            #jobs_file.write(json.dumps(jobs_list), sort_keys=True, indent=4)
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
            #print("\tfile contents: ", jobs_file.read())

            try:
                jobs_file.seek(0)
                jobs_list = json.load(jobs_file)
            except Exception as e:
                print("\texception loading job in progress file", str(e))
                jobs_list = []
                jobs_file = open(self.file_path, 'w')
                #jobs_file.truncate(0) # clear the file
                #jobs_file.write(json.dumps(jobs_list, sort_keys=True, indent=4))
                json.dump(jobs_list, jobs_file)

            #print("\tfrom file: ")
            print(jobs_list)

            if len(jobs_list) > 0:
                print("\tJobs file contains unfinished jobs")
                is_job = True

            jobs_file.close()

        else:
            print("\tcreate jobs file: ")
            jobs_file = open(self.file_path, 'w+')
            jobs_list = []
            #jobs_file.truncate(0) # clear the file
            #jobs_file.write(json.dumps(jobs_list, sort_keys=True, indent=4))
            json.dump(jobs_list, jobs_file)
            #print("\twrite to file: ", json.dumps(jobs_list))
            jobs_file.close()

             self.lock.release()
             print("is_job: ", is_job)
             return is_job
