import csv
from oracle2mysql import *

with open('marathon.csv', 'rb') as source:
   rdr = csv.reader(source)
   with open('mod_marathon.csv', 'wb') as result:
      wtr = csv.writer(result)
      for r in rdr:
         wtr.writerow((r[0], time2mysqlQuotes(r[1]), time2mysqlQuotes(r[2]), r[3], r[4], r[5], r[6], r[7], r[8], r[9], r[10], r[11]))