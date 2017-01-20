#!/usr/bin/python

import sys 
import argparse
from Storage import *
from constants import *
import numpy
import binascii
from collections import deque

#todo: 
#q: what to do to modify tlb when page is replaced
#q: does it matter which i evict in opt if none of them
    #are used in the future

def read_args():
    frames = 256
    pra = "FIFO"
    if len(sys.argv) < 2 or len(sys.argv) > 4:
        print "usage: memSim <reference-sequence-file.txt> <FRAMES>(optional) <PRA>(optional)"
        sys.exit()
    
    try:
        infile = file(sys.argv[1], 'r')
    except IOError:
        print 'File does not exist'
        sys.exit()
        
    if len(sys.argv) > 2:
        if sys.argv[2].isdigit():
            frames = int(sys.argv[2])
            if frames <= 0 or frames > 256:
                print "FRAMES must be > 0 and <= 256"
                sys.exit()
        else:
            print "FRAMES must be > 0 and <= 256"
            sys.exit()
        if len(sys.argv) == 4:
            if sys.argv[3] == "FIFO":
                pra = "FIFO"
            elif sys.argv[3] == "LRU":
                pra = "LRU"
            elif sys.argv[3] == "OPT":
                pra = "OPT"
            else:
                print "PRA must be either FIFO, LRU, or OPT (caps matter)"
                sys.exit()
    address_list = []
    for line in infile:
        address_list.append(int(line.strip('\n')))
    infile.close()
    return (address_list, frames, pra)
    

def read_backing_store(page_num):
    backing_store = file("BACKING_STORE.bin", "rb")
    backing_store.seek(page_num * 256)
    line = backing_store.read(256)
    backing_store.close()
    return binascii.hexlify(line).upper()

def print_output(current_address, frame_num, physical_mem):
    offset = current_address & 0xFF
    #test = physical_mem[frame_num][offset:offset+1]
    test = physical_mem[frame_num][offset*2:offset*2+2]
    #offset_value =  int(test, 16)
    if int(test,16) < int('0x80', 16):
        offset_value = int(test, 16)
    else:
        offset_value = (-int('0xff', 16) + int(test, 16)-1)
    print "%d, %d, %d\n%s" %(current_address, offset_value, frame_num, physical_mem[frame_num])

def init_memory(frames_arg, pra, address_list):
    my_tlb = tlb()
    physical_mem = [0] * frames_arg
    pra_queue = deque(maxlen=frames_arg)

        
    idx = 0
    page_table = []
    while idx < TABLE_ENTRY_SIZE:
        page_table.append(page_table_entry(-1, False))
        idx += 1
        
    return (my_tlb, physical_mem, page_table, pra_queue)

def check_full(physical_mem, frames_arg):
    count_zero = 0
    for idx in physical_mem:
        if idx != 0:
            count_zero += 1
    
    if count_zero == frames_arg:
        return True
    else:
        return False

def remove_from_page_table(page_table, old_idx):
    for idx, value in enumerate(page_table):
        if value.frame_num == old_idx:
            page_table[idx].valid = False

def lru_queue_add(pra, frame_num, pra_queue):
    #remove it from the queue if it is already in there
    if pra == 'LRU':
        try:
            pra_queue.remove(frame_num)
        except ValueError:
            pass
        pra_queue.append(frame_num)
        #print 'LRU Q:'+ str(pra_queue)   

def opt_load_queue(address_list):
    #going to store the page numbers of all the input given
    page_list = []
    for value in address_list:
        page_list.append(value >> 8)
        
    pra_queue = deque(page_list, maxlen=len(address_list))
    return pra_queue

def opt_evict(pra_queue, page_table):
    #look through page table for page that won't be/least used in the future
    valid_queue = []
    for idx, value in enumerate(page_table):
        if value.valid == True:
            valid_queue.append(opt_counter(idx,-1))

    #find closest idx used
    for page in valid_queue:
        for idx, value in enumerate(pra_queue):
            if page.page_num == value:
                page.last_idx = idx
                break
            
    #print 'valid in page table is '
    #for value in valid_queue:
        #print str(value)
        
    #look for lowest -1's
    for value in valid_queue:
        #-1 means that it is not in the reference input
        if value.last_idx == -1:
            #this imeplmentation returns the lowest idx found first
            return value.page_num
    num = -1
    store_idx = -1
    #look for biggest idx since that is the longest not used
    for idx, value in enumerate(valid_queue):
        if num < value.last_idx:
            num = value.last_idx
            store_idx = idx
    return valid_queue[store_idx].page_num
     
def insert_frame(physical_mem, frame, pra, frames_arg, pra_queue, page_table, my_tlb):
    offset = -1
    #check if physical_mem is full
    if check_full(physical_mem, frames_arg):                 
        #print 'FULL'
        if pra == 'FIFO' or pra == 'LRU':
            #first in first out
            old_idx = pra_queue.popleft()
            physical_mem[old_idx] = frame
            remove_from_page_table(page_table, old_idx)
            my_tlb.remove_frame(old_idx)            
            offset = old_idx
            if pra == 'FIFO':
                pra_queue.append(old_idx)
                #print 'FIFO Q: ' + str(pra_queue)
        
        elif pra == 'OPT':
            page_to_replace = opt_evict(pra_queue, page_table)
            frame_to_replace = page_table[page_to_replace].frame_num
            physical_mem[frame_to_replace] = frame
            page_table[page_to_replace].valid = False
            my_tlb.remove_frame(frame_to_replace)
            offset = frame_to_replace
            #print 'evicted ' + str(page_to_replace) + ' at frame ' + str(frame_to_replace)
    else:
        #find first non_zero and insert into that spot
        for idx, value in enumerate(physical_mem):
            if value == 0:
                physical_mem[idx] = frame
                offset = idx
                if pra == 'FIFO': #store location into FIFO queue
                    pra_queue.append(offset)
                    #print 'FIFO Q: ' + str(pra_queue)
                break
            
    return offset
            
def simulator_run():
    page_fault = 0
    tlb_miss = 0
    tlb_hit = 0
    address_list, frames_arg, pra = read_args()
    #print address_list
    my_tlb, physical_mem, page_table, pra_queue = init_memory(frames_arg, pra, address_list)

    if pra == 'OPT':
        pra_queue = opt_load_queue(address_list)
        #print pra_queue
    
    for current_address in address_list:
        p_num = current_address >> 8
        offset = current_address & 0xFF
        #print 'p_num = ' + str(p_num) + ' offset = ' + str(offset)     
        if pra == 'OPT':
            pra_queue.popleft()
            #print pra_queue    
            
        #1. check tlb
        tlb_check = my_tlb.find_page(p_num)
        if tlb_check != -1: #tlb hit
            #if hit, then go to frame immediately
            tlb_hit += 1
            frame_num = my_tlb.get_frame(tlb_check)
                
        else: #tlb miss
            tlb_miss += 1
        #2. tlb miss = page_table check
            if page_table[p_num].valid:
                #if hit, go to frame
                frame_num = page_table[p_num].frame_num             
                #update tlb
                my_tlb.add(tlb_entry(p_num, frame_num))
            else: #page fault
                page_fault += 1
                #3. page fault? = go to backing store
                frame = read_backing_store(p_num)    
                #set physical mem using alg
                frame_num = insert_frame(physical_mem, frame, pra, frames_arg, 
                                         pra_queue, page_table, my_tlb)
                my_tlb.add(tlb_entry(p_num, frame_num))
                page_table[p_num] = page_table_entry(frame_num, True)
        lru_queue_add(pra, frame_num, pra_queue)
        print_output(current_address, frame_num, physical_mem)

        
    print 'Number of Translated Addresses = %d' % len(address_list)
    print 'Page Faults = %d' % page_fault
    print 'Page Fault Rage = %.3f' % (float(page_fault) / len(address_list))
    print 'TLB Hits = %d' % tlb_hit
    print 'TLB Misses = %d' % tlb_miss
    #print 'TLB Hit Rate = %.3f' % (float(tlb_hit) / len(address_list))
    print 'TLB Miss Rate = %.3f' % (float(tlb_miss) / len(address_list))

def main():
    simulator_run()
    

    
if __name__ == '__main__':
    main()