#!/usr/bin/python

import subprocess

#constants
num_iter = 10000
num_buckets = 5000001

# make an array to hold the number of trials seen with values 0 to 40
buckets = [0] * num_buckets

# run a number of trials, and increment the appropriate bucket
for i in range(num_iter):
    output = subprocess.check_output(['./race'])
    output_arr = output.split()
    output_val = int(output_arr[2])
    buckets[output_val] = buckets[output_val] + 1

# print out the results
for i in range(len(buckets)):
    if buckets[i] != 0:
        print(str(i) + ": " + str(buckets[i]))
