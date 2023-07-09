#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import sys

data = np.genfromtxt('data_complexity_1mop_heap.csv' if len(sys.argv) == 1 else sys.argv[1],
                     delimiter=',',
                     names=['nb', 'insert' ])

fig, axes = plt.subplots()
axes.set_xscale('symlog', base=2)
axes.set_title("Time to insert/extract all (min) nodes in/from heap")
axes.set_xlabel('# of nodes')
axes.set_ylabel('time')

# time to insert
axes.plot(data['nb'], data['insert'], c='r', label='insert')


# legend
axes.legend()

plt.show()
