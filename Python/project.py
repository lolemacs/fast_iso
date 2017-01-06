import sys
from graph_tool.all import *
from random import random, randint, shuffle
from math import log


#Funcao de threshold do G(n,p) para ser conexo eh ((log n)/n)
def sampler(n):
	#Funcao de threshold do g(n,p) para ser conexo
    prob = 10*log(n)/n
    #modelo g(n,p) nao tem grau minimo, e garantindo o threshold sera conexo!
    deg = 0
    for i in range(n):
		#Aumento o grau de um no com probabilidade p => equivalente a 
		# criar aresta entre dois nos com probabilidade p, como o G(n,p)
        if random() <= prob: deg += 1
    return (deg,deg)


f = open("out","w")
h = open("degs","w")

if (len(sys.argv) != 2):
    print "use:%s <n>" % (sys.argv[0])
    sys.exit(1)

n = int(sys.argv[1])

#Numero de vertices na maior componente conexa do grafo
ncc=0

#gera grafo garantidamente conexo
while n != ncc :
	g = random_graph(n, lambda: sampler(n), model="erdos") #modelo de randomizacao das arestas erdos e renyi
	l = label_largest_component(g)
	u = GraphView(g, vfilt=l)   # extrai maior componente conexa de g e coloca em u
	ncc = u.num_vertices() # atualiza numero de vertices da maior componente conexa do grafo gerado
	print "N %d e NCC %d" % (n, ncc)

dists = shortest_distance(g)
for i in range(len(list(g.vertices()))):
    h.write("%s " % g.vertex(i).out_degree())
    vec = dists[g.vertex(i)].a
    for v in vec:
        f.write("%s " % v)
    f.write("\n")

f.close()
h.close()
