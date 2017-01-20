
class tlb_entry:
    
    def __init__(self, page_num, frame_num):
        self.page_num = page_num
        self.frame_num = frame_num
        
    def __str__(self):
        return '(' + str(self.page_num) + ', ' + str(self.frame_num) + ')'
    
    
class tlb:
    
    def __init__(self):
        self.table = []
        self.max_size = 16
        self.count = 0
        
    def add (self, tlb_entry):

        if self.count < self.max_size:
            self.table.append(tlb_entry)
            self.count += 1
        else:
            self.table.pop(0)
            self.table.append(tlb_entry)
    
    def remove_frame(self, frame_num):
        #look through tlb to find that frame if it exist
        for idx, value in enumerate(self.table):
            if value.frame_num == frame_num:
                #delete by popping it out
                self.table.pop(idx)
                self.count -= 1
            
    def get_frame(self, idx):
        return self.table[idx].frame_num
    
    def find_page(self, page_num):
        idx = -1
        for i, value in enumerate(self.table):
            if value.page_num == page_num:
                idx = i
                break
        return idx
      
       
    def __str__(self):
        ret = ''
        for i in self.table:
            ret += str(i)
        return ret
    
    
class page_table_entry:
    
    def __init__(self, frame_num, valid):
        self.frame_num = frame_num
        self.valid = valid
        
    def __str__(self):
        return '(frame = ' + str(self.frame_num) +\
                    ', valid = ' + str(self.valid) + ')' 
                    
                    
                    
class opt_counter:
    
    def __init__(self, page_num, last_idx):
        self.page_num = page_num
        self.last_idx = last_idx
        
    def __str__(self):
        return '(page_num = ' + str(self.page_num) +\
                    ', last_idx = ' + str(self.last_idx) + ')' 