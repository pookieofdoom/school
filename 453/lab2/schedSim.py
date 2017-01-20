#!/usr/bin/python


import sys 
import os.path
from job import *
import argparse
from collections import deque

def read_args():
    
    parser = argparse.ArgumentParser()
    parser.add_argument("infile", help="Txt File name holding list of jobs",
                        type=argparse.FileType('r'))
    parser.add_argument("-p", "--alg", help="Algorithm being used", default="FIFO",
                        type=str)
    parser.add_argument("-q", "--quantum", help="Quantum if RR is used",
                        default = 1, type=int)
    try:
        args = parser.parse_args()
    except IOError:
        print 'File does not exist'
        sys.exit()
    alg_check(args.alg)
    return (args.infile, args.alg, args.quantum)
    
    
def alg_check(alg):
    if alg != 'FIFO' and alg != 'RR' and alg != 'SRJN':
        print 'Invalid Algorithm (FIFO, RR or SRJN (caps matter)'
        sys.exit()    
    
def find_min_arrival(array):
    i = 0
    min = array[0].arrival_time
    for idx, time in enumerate(array):
       if min > time.arrival_time:
           min = time.arrival_time
           i = idx
    return array[i]
    

def assign_id(array):
    id = 0
    sorted_array = []
    for i in xrange(len(array)):
       job = find_min_arrival(array)
       job.id = id
       id = id + 1
       sorted_array.append(job)
       array.remove(job)
    return sorted_array


def schedule(alg, array, quantum):
    if alg == 'FIFO':
       fifo(array)
    
    if alg == 'RR':
        rr(array, quantum)
    
    if alg == 'SRJN':
        srjn(array)   
       
    print_average(array)

     
def fifo(array):

    for idx, job in enumerate(array):
        time = 0
        if idx != 0:
            while job.arrival_time > array[idx-1].finish_time + time:
                time +=1
            job.start_time = array[idx-1].finish_time + time
            job.finish_time = job.start_time + job.run_time
            job.finish = True
        else:
            job.start_time = job.arrival_time
            job.finish_time = job.run_time + job.start_time
            job.finish = True
        job.set_time()
        print job

        

def rr(array, quantum):
    q = deque()
    #the first process that arrives
    time = array[0].arrival_time
    #add the first one to the queue
    array[0].arrived = True
    array[0].start_time = time
    q.append(array[0])
    run_array = []
    run_array = save_run(array)
    
    while not check_finish(array):
        if len(q) != 0:   
            time, old_job = process_q(q, time, quantum)
        else:
            time+=1

        for job in array:
            if (time >= job.arrival_time and job.finish == False
             and job.arrived == False):
                job.arrived = True           
                q.append(job)

        if old_job.finish == False:
            q.append(old_job)
            
    array = restore_run(run_array, array)   
    for job in array:
        job.set_time()
        print job

def process_q(q, time, quantum):
    job = q.popleft()   
    if job.run_time > quantum:
        if job.id != 0 and job.start_time == 0:
            job.start_time = time
        job.run_time -= quantum
        time += quantum           
    else:
        if job.id != 0 and job.start_time == 0:
            job.start_time = time
        time += job.run_time
        job.run_time = 0
        job.finish_time = time
        job.finish = True
    return time, job

def check_finish(array):
    for job in array:
        if job.finish == False:
            return False   
    return True

def save_run(array):
    save_array = []
    for job in array:
        save_array.append(job.run_time)
    return save_array

def restore_run(run_array, array):
    for i in xrange(len(array)):
        array[i].run_time = run_array[i]
    return array


def srjn(array):
    time = 0
    zero_arrive = False
    run_array = []
    run_array = save_run(array)
    
    while not check_finish(array):
        for job in array:
            if (time >= job.arrival_time and job.finish == False
             and job.arrived == False):
                job.arrived = True
                
        shortest_idx = find_shortest_job(array)
        if shortest_idx != -1:
            
            if array[shortest_idx].id != 0 and array[shortest_idx].start_time == 0:
                array[shortest_idx].start_time = time
            
            if array[shortest_idx].id == 0 and zero_arrive == False:
                array[shortest_idx].start_time = time
                zero_arrive = True
            
            shortest_job = array[shortest_idx]
            shortest_job.run_time -= 1
            time +=1
            if shortest_job.run_time == 0:
                shortest_job.finish = True
                shortest_job.finish_time = time
        else:
            time += 1
    array = restore_run(run_array, array)   
    for job in array:
        job.set_time()
        print job

def find_shortest_job(array):
    i = -1

    for idx, job in enumerate(array):
        if (job.arrived and job.finish == False):
            i = idx
            break
    if i == -1:
        return -1
            
    for idx, job in enumerate(array):
        if (job.arrived and array[i].run_time > job.run_time
                and job.finish == False):
            i = idx
    return i

def print_average(array): 
    avg_response = 0
    avg_turn = 0
    avg_wait = 0
    for x in array:
        avg_response = avg_response + x.response 
        avg_turn = avg_turn + x.turn_around
        avg_wait = avg_wait + x.wait_time
    print 'Average -- Response: %3.2f  Turnaround %3.2f  Wait %3.2f' %(avg_response/len(array), avg_turn/len(array), avg_wait/len(array))



     
def main():
    array_of_jobs = []
    infile, alg, quantum = read_args()
    line = infile.readline()

    while line != '' :
        run_time, arrival_time = map(float, line.split())
        array_of_jobs.append(Job(run_time, arrival_time))
        line = infile.readline()

    infile.close()
    array_of_jobs = assign_id(array_of_jobs)
    schedule(alg, array_of_jobs, quantum)
    
    
if __name__ == '__main__':
    main()
    