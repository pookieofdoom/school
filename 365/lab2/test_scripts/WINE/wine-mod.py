import csv

with open('wine.csv', 'rb') as source:
   rdr = csv.reader(source)
   with open('mod_wine.csv', 'wb') as result:
      wtr = csv.writer(result)
      for r in rdr:
         wtr.writerow((r[0], r[1], r[2], r[3], r[5], r[6], r[7], r[8], r[9]))