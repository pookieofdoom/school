import csv
from oracle2mysql import *

with open('receipts.csv', 'rb') as source:
   rdr = csv.reader(source)
   with open('mod_receipts.csv', 'wb') as result:
      wtr = csv.writer(result)
      for idx, r in enumerate(rdr):
         if idx != 0:
            wtr.writerow((r[0], date2mysqlQuotes(r[1]), r[2]))