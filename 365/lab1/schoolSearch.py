#~/usr/bin/python

def main():
	all = parseFile("students.txt")
	userMode(all)


def userMode(entries):
	while True:	
		input = raw_input("Enter A Command: ")

		#this gets rid of duplicate spaces
		cmd = " ".join(input.split()).split(" ")

		if len(cmd) == 2 and (cmd[0] == 'T:' or cmd[0] == 'Teacher:'):	
			for e in entries:
				if e.TLastName == cmd[1]:
					print e.studentName()

		if len(cmd) == 2 and (cmd[0] == 'A:' or cmd[0] == 'Average:'):
			tempGPA = 0.0
			studentCount = 0
			for e in entries: 
				if e.Grade == cmd[1]:
					studentCount = studentCount + 1
					tempGPA = tempGPA + float(e.GPA)
			try:
				print "Grade: " + cmd[1] + " -> Avg GPA: " + '%.2f' % (tempGPA/studentCount)
			except ZeroDivisionError:
				#or could not print anything
				print "Grade: " + cmd[1] + " -> Avg GPA: 0"

		if len(cmd) == 2 and (cmd[0] == 'S:' or cmd[0] == 'Student:'):
			for e in entries:
				if e.StLastName == cmd[1]:
					print e.studentName() + " " + e.Grade + " " + e.Classroom + " " + e.teacherName()

		if len(cmd) == 3 and (cmd[0] == 'S:' or cmd[0] == 'Student:') and (cmd[2] == 'B' or cmd[2] == 'Bus'):
			for e in entries:
				if e.StLastName == cmd[1]:
				   print e.studentName() + " " + e.Bus	
		
		if len(cmd) == 2 and (cmd[0] == 'B:' or cmd[0] == 'Bus:'):
			for e in entries:
				if e.Bus == cmd[1]:
					print e.StFirstName + " " + e.StLastName + " " + e.Grade + " " + e.Classroom

 		if len(cmd) == 2 and (cmd[0] == 'G:' or cmd[0] == 'Grade:'):
			for e in entries: 
				if e.Grade == cmd[1]:
					print e.studentName()

		if len(cmd) == 3 and (cmd[0] == 'G:' or cmd[0] == 'Grade:') and (cmd[2] == 'H' or cmd[2] == 'High'):
			high_gpa = 0
			high_index = 0
			for idx, e in enumerate(entries):
				if e.Grade == cmd[1]:
					if float(e.GPA) > high_gpa:
						high_gpa = float(e.GPA)
						high_index = idx
			#prints out the first highest one if duplicate
			if high_gpa != 0:
				print entries[high_index].studentName() + " " + str(high_gpa) + " " + entries[high_index].teacherName() + " " + entries[high_index].Bus

		if len(cmd) == 3 and (cmd[0] == 'G:' or cmd[0] == 'Grade:') and (cmd[2] == 'L' or cmd[2] == 'Low'):
			low_gpa = 4.1
			low_index = 0
			for idx, e in enumerate(entries):
				if e.Grade == cmd[1]:
					if float(e.GPA) < low_gpa:
						low_gpa = float(e.GPA)
						low_index = idx
			if low_gpa != 4.1:
				print entries[low_index].studentName() + " " + str(low_gpa) + " " + entries[low_index].teacherName() + " " + entries[low_index].Bus

		if len(cmd) == 1 and (cmd[0] == 'Q' or cmd[0] == 'Quit'):
			return

		print ""

def parseFile(fileName):
	entries = []
	try:
		f = open(fileName,'r')
		for line in f:
			tempEntry = line.split(',')
			tempEntryObj = Entry(tempEntry[0],tempEntry[1], tempEntry[2], tempEntry[3], tempEntry[4],tempEntry[5],tempEntry[6],tempEntry[7].strip('\n'))
			entries.append(tempEntryObj)
		return entries
	except IOError:
		print fileName + ' not found'
		exit()
	except IndexError:
		print fileName + ' does not have the correct format'
		exit()

class Entry:
	def __init__(self,StLastName,StFirstName,Grade,Classroom,Bus,GPA,TLastName,TFirstName):
		self.StLastName = StLastName
		self.StFirstName = StFirstName
		self.Grade = Grade
		self.Classroom = Classroom
		self.Bus = Bus
		self.GPA = GPA
		self.TLastName = TLastName
		self.TFirstName = TFirstName
	
	def studentName(self):
		return self.StLastName + " " + self.StFirstName	

	def teacherName(self):
		return self.TLastName + " " + self.TFirstName

if __name__ == "__main__":
	main()



