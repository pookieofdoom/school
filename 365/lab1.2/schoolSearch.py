# /bin/python

# Description: CPE 365 (Lab 1, Part 2) 
# Authors: Brandon Okumura and Anthony Dinh 
# Date: Sept 30, 2016

import time


def main():
    students = parseFile("list.txt", True)
    teachers = parseFile("teachers.txt", False)
    userMode(students, teachers)

def userMode(entries, teachers):
    while True: 
        input = raw_input("Enter A Command: ")
        # Store response, then print at the end
        toPrint = ''
        startTime = 0
        endTime = 0
        # this gets rid of duplicate spaces
        cmd = " ".join(input.split()).split(" ")

        #Given teacher last name, get all students who have that teacher
        if len(cmd) == 2 and (cmd[0] == 'T:' or cmd[0] == 'Teacher:'):  
            startTime = time.time()
            for t in teachers:
                if t.TLastName == cmd[1]:
                    for e in entries: 
                        if e.Classroom == t.Classroom:
                            toPrint = toPrint + e.studentName() + '\n'
            endTime = time.time()
        
        #Given grade number, get average GPA of that grade level
        if len(cmd) == 2 and (cmd[0] == 'A:' or cmd[0] == 'Average:'):
            startTime = time.time()
            tempGPA = 0.0
            studentCount = 0
            for e in entries: 
                if e.Grade == cmd[1]:
                    studentCount = studentCount + 1
                    tempGPA = tempGPA + float(e.GPA)
            try:
                toPrint = "Grade: " + cmd[1] + " -> Avg GPA: " + '%.2f' % (tempGPA / studentCount)
            except ZeroDivisionError:
                # or could not print anything
                toPrint = "Grade: " + cmd[1] + " -> Avg GPA: 0"
        endTime = time.time()
        
        #Given student last name, get information about student(grade, classroom, teacher)
        if len(cmd) == 2 and (cmd[0] == 'S:' or cmd[0] == 'Student:'):
            startTime = time.time()
            for e in entries:
                if e.StLastName == cmd[1]:
                    toPrint = toPrint + e.studentName() + " " + e.Grade + " " + e.Classroom + " " \
                    + str(e.getTeacher(teachers)) + "\n"
            endTime = time.time()
        
        #Given Student last name with B[us], get student name and bus route
        if len(cmd) == 3 and (cmd[0] == 'S:' or cmd[0] == 'Student:') and (cmd[2] == 'B' or cmd[2] == 'Bus'):
            startTime = time.time()
            for e in entries:
                if e.StLastName == cmd[1]:
                    toPrint = toPrint + e.studentName() + " " + e.Bus + "\n"
            endTime = time.time()
        
        #Given bus route, get information about student(name, grade, classroom)
        if len(cmd) == 2 and (cmd[0] == 'B:' or cmd[0] == 'Bus:'):
            startTime = time.time()
            for e in entries:
                if e.Bus == cmd[1]:
                    toPrint = toPrint + e.StFirstName + " " + e.StLastName + " " + e.Grade + " " \
                    + e.Classroom + "\n"
            endTime = time.time()
        
        #Given grade number, get all students
        if len(cmd) == 2 and (cmd[0] == 'G:' or cmd[0] == 'Grade:'):
            startTime = time.time()
            for e in entries: 
                if e.Grade == cmd[1]:
                    toPrint = toPrint + e.studentName() + "\n"
            endTime = time.time()
        
        #Given grade number and H[igh], get student with highest gpa (name, gpa, teacher, bus) 
        if len(cmd) == 3 and (cmd[0] == 'G:' or cmd[0] == 'Grade:') and (cmd[2] == 'H' or cmd[2] == 'High'):
            startTime = time.time()
            high_gpa = 0
            high_index = 0
            for idx, e in enumerate(entries):
                if e.Grade == cmd[1]:
                    if float(e.GPA) > high_gpa:
                        high_gpa = float(e.GPA)
                        high_index = idx
            # prints out the first highest one if duplicate
            if high_gpa != 0:
                toPrint = toPrint + entries[high_index].studentName() + " " + str(high_gpa) + " " \
                + entries[high_index].getTeacher(teachers) + " " + entries[high_index].Bus + "\n"
            endTime = time.time()
        
        #Given grade number and L[ow], get student with lowest gpa (name, gpa, teacher, bus)
        if len(cmd) == 3 and (cmd[0] == 'G:' or cmd[0] == 'Grade:') and (cmd[2] == 'L' or cmd[2] == 'Low'):
            startTime = time.time()
            low_gpa = 4.1
            low_index = 0
            for idx, e in enumerate(entries):
                if e.Grade == cmd[1]:
                    if float(e.GPA) < low_gpa:
                        low_gpa = float(e.GPA)
                        low_index = idx
            if low_gpa != 4.1:
                toPrint = toPrint + entries[low_index].studentName() + " " + str(low_gpa) + " " \
                 + entries[low_index].getTeacher(teachers) + " " + entries[low_index].Bus + "\n"
            endTime = time.time()

        #Q for quit
        if len(cmd) == 1 and (cmd[0] == 'Q' or cmd[0] == 'Quit'):
            return
        
        #Given classroom and S, get all students in that classroom
        if len(cmd) == 3 and (cmd[0] == 'C:' or cmd[0] == 'Classroom:') and cmd[2] == 'S':
            startTime = time.time()
            for e in entries: 
                if e.Classroom == cmd[1]:
                    toPrint = toPrint + e.studentName() + "\n"
            endTime = time.time()   
        
        #Given classroom and T, get all teachers that belong in that classroom
        if len(cmd) == 3 and (cmd[0] == 'C:' or cmd[0] == 'Classroom:') and cmd[2] == 'T':
            startTime = time.time()
            for t in teachers:
                if t.Classroom == cmd[1]:
                    toPrint = toPrint + t.name() + "\n"
            endTime = time.time()
    
        #Given grade number, find all teachers that teach it
        if len(cmd) == 2 and cmd[0] == 'TG:':
            startTime = time.time()
            teacherList = []
            for e in entries: 
                if e.Grade == cmd[1]:
                    if e.getTeacher(teachers) not in teacherList:
                        teacherList.append(e.getTeacher(teachers))
            for x in teacherList:
                toPrint = toPrint + x + "\n"
            endTime = time.time()

        #Given analy(z)e and grade number, get the average of all possible grades 
        if len(cmd) == 2 and (cmd[0] == 'Analyze:' or cmd[0] == 'z:'):
            startTime = time.time()

            if cmd[1] == 'G':
                toPrint = getAllStudentGrades(entries)
                        
            #Given analytics and T, output all teachers and their class gpa average
            if cmd[1] == 'T':
                toPrint = getAllTeacherGrades(entries, teachers)

            #Given analytics and B, output all possible bus routes and student gpa
            if cmd[1] == 'B':
                toPrint = getAllBusGrades(entries)

            #toPrint = "Grade: " + cmd[1] + " -> Avg GPA: " + '%.2f' % (totalGPA / studentCount)
            endTime = time.time()
      
        print toPrint
        print "Search Time: %s seconds" % (endTime - startTime)

#method to calculate the average gpa over all possible grade levels
def getAllStudentGrades(students):
    studentCount = 0
    totalGPA = 0.0
    gradeList = []
    toPrint = ""
    for student in students:
        if int(student.Grade) not in gradeList:
            gradeList.append(int(student.Grade))
    gradeList.sort()
    for grade in gradeList:
        for student in students:
            if int(student.Grade) == grade:
                studentCount = studentCount + 1
                totalGPA = totalGPA + float(student.GPA)
        toPrint += "Grade: " + str(grade) + " -> Avg GPA: " + '%.2f' % (totalGPA / studentCount) + '\n'
        studentCount = 0
        totalGPA = 0.0
    return toPrint

#method to calculate the average GPA for all the teachers' students
def getAllTeacherGrades(students, teachers):
    studentCount = 0
    totalGPA = 0.0
    teacherList = []
    toPrint = ""
    for teacher in teachers:
        for student in students:
            if student.getTeacherLastName(teachers) == teacher.TLastName:
                studentCount = studentCount + 1
                totalGPA = totalGPA + float(student.GPA)
        toPrint += teacher.name() + " -> Avg GPA: " + '%.2f' % (totalGPA / studentCount) + '\n'
        studentCount = 0
        totalGPA = 0.0
    return toPrint

#method to get the average GPA depending on the bus route the student takes
def getAllBusGrades(students):
    studentCount = 0
    totalGPA = 0.0
    busList = []
    toPrint = ""
    for student in students:
        if int(student.Bus) not in busList:
            busList.append(int(student.Bus))
    busList.sort()
    for route in busList:
        for student in students:
            if int(student.Bus) == route:
                studentCount = studentCount + 1
                totalGPA = totalGPA + float(student.GPA)
        toPrint += "Bus Route: " + str(route) + " -> Avg GPA: " + '%.2f' % (totalGPA / studentCount) + '\n'
        studentCount = 0
        totalGPA = 0.0
    return toPrint
                
    
#this function opens the file depending on the parameter isStudent and parses out information into an array
def parseFile(fileName, isStudent):
    entries = []
    try:
        f = open(fileName, 'r')
        for line in f:
            tempEntry = line.split(',')
            if isStudent:
                tempEntryObj = Student(tempEntry[0], tempEntry[1], tempEntry[2], tempEntry[3], tempEntry[4], tempEntry[5].strip('\n'))
            if not isStudent:
                tempEntryObj = Teacher(tempEntry[0].strip(), tempEntry[1].strip(), tempEntry[2].strip().strip('\n'))
            entries.append(tempEntryObj)
        return entries
    except IOError:
        print fileName + ' not found'
        exit()
    except IndexError:
        print fileName + ' does not have the correct format'
        exit()

#student object with attributes that match file
class Student:
    def __init__(self, StLastName, StFirstName, Grade, Classroom, Bus, GPA):
        self.StLastName = StLastName
        self.StFirstName = StFirstName
        self.Grade = Grade
        self.Classroom = Classroom
        self.Bus = Bus
        self.GPA = GPA
      
    def studentName(self):
        return self.StLastName + " " + self.StFirstName 

    def getTeacher(self, teacherList):
        for teacher in teacherList:
            if teacher.Classroom == self.Classroom:
                return teacher.name()
        return None

    def getTeacherLastName(self, teacherList):
        for teacher in teacherList:
            if teacher.Classroom == self.Classroom:
                return teacher.TLastName
        return None


#teacher object 
class Teacher:
    def __init__(self, TLastName, TFirstName, Classroom):
        self.TLastName = TLastName
        self.TFirstName = TFirstName
        self.Classroom = Classroom

    def name(self):
        return self.TLastName + " " + self.TFirstName

#MAIN
if __name__ == "__main__":
    main()



