#!/usr/bin/python

class Job:
    
    def __init__(self, run_time, arrival_time, id = 0, start_time = 0,
                 finish_time = 0, turn_around = 0, wait_time = 0, response = 0,
                 arrived = False, finish = False):
        self.run_time = run_time
        self.arrival_time = arrival_time
        self.id = id
        self.start_time = start_time
        self.finish_time = finish_time
        self.turn_around = turn_around
        self.wait_time = wait_time
        self.response = response
        self.arrived = arrived
        self.finish = finish
        
    def __str__(self):
        #a = '\nProcess|Burst|Arrival|Start|Wait|Finish|Ta |Response\n'
        #b = str(self.id) + '\t '  + str(self.run_time)+ '\t ' + str(self.arrival_time) + '  '
        #c = str(self.start_time) + '    ' + str(self.wait_time) + '\t ' + str(self.finish_time) + '\t ' + str(self.turn_around) + '\t ' + str(self.response)
        #return a + b + c
        return 'Job %3d -- Response: %3.2f  Turnaround %3.2f  Wait %3.2f' % (self.id, self.response, self.turn_around, self.wait_time)
        #return "(%d,%d,%d)" %(self.id, self.run_time,self.arrival_time)
    
    def __repr__(self):
        return str(self)
    
    
    def set_time(self):
        self.wait_time = self.finish_time - self.run_time - self.arrival_time
        self.turn_around = self.finish_time - self.arrival_time
        #in certain examples, that +1 is not suppose to be there
        self.response = self.start_time - self.arrival_time + 1