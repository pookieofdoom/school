# /bin/python

import csv
import argparse

def main():
   csv_file, sql_script, table_name = read_args()
   print csv_file
   with csv_file:
      reader = csv.reader(csv_file)
      with sql_script as f:
         for idx, row in enumerate(reader):
            if idx == 0 or not row:
               #print idx
               print 'inserting header'
               f.write('-- Anthony Dinh\n')
               f.write('-- adinh03@calpoly.edu\n')
               f.write('-- CPE 365\n\n\n')
            elif not row:
               print 'do nothing'
            else:
               #print idx
               f.write('INSERT INTO ' + table_name +' VALUES(' )
               for i in range(len(row)):
                  #print row[i]
                  if i != len(row) - 1:
                     f.write(row[i] + ', ')
                  else:
                     f.write(row[i] + ');\n')
               

   csv_file.close()
   sql_script.close()

def read_args():
   parser = argparse.ArgumentParser()
   parser.add_argument("infile", help="csv filename that will be converted to mysql commands",
         type=argparse.FileType('r'))
   parser.add_argument("outfile", help="sql script that will contain the populating of database",
         type=argparse.FileType('w'))
   parser.add_argument("table_name", help="the user specifies the table_name that the inserts will be placed into",
         type=str)

   try:
        args = parser.parse_args()
   except IOError:
      print 'File does not exist'
      sys.exit()

   return (args.infile, args.outfile, args.table_name)

if __name__ == "__main__":
    main()
