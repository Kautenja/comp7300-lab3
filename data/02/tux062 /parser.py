"""Usage:
    python parser.py <text_file>

where <text_file> is a file with text output from a matrix experiment.
"""
from sys import argv
import re

REGEX = re.compile(r'^\s*[0-9]*:\s*Init and Transpose\s*Max\[\s*([0-9]*\s*)\]=\s*([0-9]*.[0-9]*)\s*Min\[\s*([0-9]*\s*)\]=\s*([0-9]*.[0-9]*)\s*Avg=\s*([0-9]*.[0-9]*)$')

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
        matches = REGEX.match(line)
        if matches is not None:
            data.append(matches.groups())

# import pandas and render graphs
from pandas import DataFrame, concat
# reorganize the list of tuple lists into two lists of tuples. one for rows
# and one for columns inside pandas dataframes making sure to convert
# everything to numeric type
columns = ['$index_{max}$', '$max$', 'index_{min}', 'min', 'avg']
df = DataFrame([[float(number) for number in _data] for _data in data], columns=columns)
# concatentate the dataframes and write them to file
df.to_csv(argv[1].split('.')[0] + '.csv')
