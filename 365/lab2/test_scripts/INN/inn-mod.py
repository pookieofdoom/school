import csv
from oracle2mysql import *

with open('Reservations.csv', 'rb') as source:
   rdr = csv.reader(source)
   with open('mod_Reservations.csv', 'wb') as result:
      wtr = csv.writer(result)
      for idx, r in enumerate(rdr):
         if idx != 0:
            wtr.writerow((r[0], r[1], date2mysqlQuotes(r[2]), date2mysqlQuotes(r[3]), r[4], r[5], r[6], r[7], r[8]))