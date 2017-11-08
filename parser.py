"""Usage:
    python parser.py <text_file>

where <text_file> is a file with text output from a matrix experiment.
"""
from sys import argv
import re

# the regular expression for detecting row wise lines in the output:
#   1: Rowwise    Max[ 1]=  6.479 Min[ 1]=  6.479 Avg=  6.479
ROWWISE = re.compile(r'^\s*[0-9]*:\s*Rowwise\s*Max\[\s*([0-9]*\s*)\]=\s*([0-9]*.[0-9]*)\s*Min\[\s*([0-9]*\s*)\]=\s*([0-9]*.[0-9]*)\s*Avg=\s*([0-9]*.[0-9]*)$')
# the regular expression for detecting column wise lines in the output:
#      Columnwise Max[ 1]= 47.949 Min[ 2]= 47.309 Avg= 47.629
COLUMNWISE = re.compile(r'^\s*Columnwise\s*Max\[\s*([0-9]*\s*)\]=\s*([0-9]*.[0-9]*)\s*Min\[\s*([0-9]*\s*)\]=\s*([0-9]*.[0-9]*)\s*Avg=\s*([0-9]*.[0-9]*)$')


# verify command line arguments
if len(argv) < 2:
    # wrong number of command line arguments passed, print the documentation
    print(__doc__)
    exit(-1)

# open the file and iterate over the lines to collect the test data
with open(argv[1]) as text_file:
    # keep the data as a list of lists of tuples: [[(max, min, avg), (max, min, avg)]]
    data = []
    for line in text_file.readlines():
        row_matches = ROWWISE.match(line)
        if row_matches is not None:
            data.append([row_matches.groups()])
            # print(row_matches.groups())
            continue
        column_matches = COLUMNWISE.match(line)
        if column_matches is not None:
            data[-1].append(column_matches.groups())


# import pandas and render graphs
from pandas import DataFrame, concat
# reorganize the list of tuple lists into two lists of tuples. one for rows
# and one for columns inside pandas dataframes making sure to convert
# everything to numeric type
columns = ['$index_{max}$', '$max$', 'index_{min}', 'min', 'avg']
# build the row wise data dataframe
row_wise = DataFrame([[float(number) for number in _data[0]] for _data in data],
                     columns=columns)
row_wise['style'] = 'Rowwise'
# build the columnwise data dataframe
column_wise = DataFrame([[float(number) for number in _data[1]] for _data in data],
                        columns=columns)
column_wise['style'] = 'Columnwise'

# concatentate the dataframes and write them to file
concat([row_wise, column_wise]).to_csv(argv[1].split('.')[0] + '.csv')
