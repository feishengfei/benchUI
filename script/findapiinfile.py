import os
import shutil
import re
import sys
import numpy as np

api='glVertexAttrib4'
num=['','N']
typ=['bi','ub','us','ui']
vec=['v']

for n in num:
    for t in typ:
        for v in vec:
            print(api+n.strip()+t.strip()+v.strip())
