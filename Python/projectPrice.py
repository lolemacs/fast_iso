import sys
from graph_tool.all import *
from random import random, randint, shuffle
from math import log


f = open("out","w")
h = open("degs","w")

if (len(sys.argv) != 2):
    print "use:%s <n>" % (sys.argv[0])
    sys.exit(1)

n = int(sys.argv[1])

g = price_network(n) #preferential attachment network model directed


dists = shortest_distance(g)
for i in range(len(list(g.vertices()))):
    h.write("%s " % g.vertex(i).out_degree())
    vec = dists[g.vertex(i)].a
    for v in vec:
        f.write("%s " % v)
    f.write("\n")

f.close()
h.close()
