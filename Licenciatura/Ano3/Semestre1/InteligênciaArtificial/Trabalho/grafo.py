import time

import matplotlib.pyplot as plt
import networkx as nx

from nodo import Node


class Graph:
    def __init__(self):
        self.nodes = {}
        self.edges = {}
        self.distances = {}
    
    def __str__(self):
        string = ''
        for edge in self.edges:
            for edge2 in self.edges[edge]:
                string=string+'('+ edge.name +','+ edge2.name +','+str(self.distances[(edge, edge2)])+')\n'
        return string[:-1]
    
    def add_node(self, node_name, node_cost):
        if node_name not in self.nodes:
            self.nodes[node_name]=Node(node_name, node_cost)
    
    def get_node_cost(self, node_name):
        return self.nodes[node_name].cost
    
    def add_edge(self, from_node, to_node, distance=-1,from_node_cost=0,to_node_cost=0):
        if from_node not in self.nodes:
            self.add_node(from_node,from_node_cost)
        if to_node not in self.nodes:
            self.add_node(to_node, to_node_cost)
        if from_node not in self.edges:
            self.edges[from_node] = [to_node]
        elif to_node not in self.edges[from_node]:    
            self.edges[from_node].append(to_node)
        self.distances[(from_node, to_node)] = distance

    def get_edge_cost(self, from_node, to_node):
        return self.distances[(from_node, to_node)]
    
    def to_pl_strs(self, estado):
        coords = estado.split(',')
        pl_coords = ''
        i = 0
        while i < len(coords):
            pl_coords+=(coords[i])+','+(coords[i+1])+','
            i += 4
        return pl_coords[:-1]

    def rpl(self, f, vertex, open_nodes, closed_nodes):
        vname = self.to_pl_strs(vertex)
        save_dic = {'vertex': vname, 'nodes': {}}

        for closed in closed_nodes:
            names = self.to_pl_strs(closed).split(',')
            i=0
            while i < len(names):
                name = names[i]+','+names[i+1]
                if name in save_dic['nodes']:
                    save_dic['nodes'][name] -= 1
                else:
                    save_dic['nodes'][name] = 0
                i+=2

        for openn in open_nodes:
            names = self.to_pl_strs(openn[0]).split(',')
            i=0
            while i < len(names):
                name = names[i]+','+names[i+1]
                if name in save_dic['nodes']:
                    save_dic['nodes'][name] += 1
                else:
                    save_dic['nodes'][name] = 0
                i+=2

        f.write(save_dic['vertex'])

        for node in save_dic['nodes']:
            f.write(';'+node+'('+str(save_dic['nodes'][node])+')')

        f.write('\n')

    def DFS(self, start, goals, replay=False, map='', hidden=[], removed=[], name=''):
        f=None
        fname=None
        
        if name=='':
            name=str(int(time.time()))
        # REPLAY FEATURES
        if replay:
            fname='replays/dfs/'+name+'.rpl'
            f=open(fname,'w')
            f.write(map+'\n')
        # END REPLAY FEATURES

        stack = [(start, [start])]
        visited = []

        while stack:
            (vertex, path) = stack.pop()

            if vertex not in visited and not (len(path)==1 and (vertex.split(',')[0], vertex.split(',')[1]) in hidden) and (vertex.split(',')[0], vertex.split(',')[1]) not in removed:
                visited.append(vertex)
                coords = vertex.split(',')
                pl=0
                tot,ended=0,0

                while pl < len(coords):
                    x,y=int(coords[pl]),int(coords[pl+1])
                    tot+=1

                    if (x,y) in goals:
                        ended+=1
                    pl+=4

                if tot==ended:

                    # REPLAY FEATURES
                    if replay:
                        f=open(fname,'a')

                        for p in path:
                            name=p.split(',')[0]+','+p.split(',')[1]
                            f.write(name+';')
                        f.close()
                    # END REPLAY FEATURES

                    return path,fname

                for e in self.edges[vertex]:

                    if e not in visited and not (len(path)==1 and (e.split(',')[0], e.split(',')[1]) in hidden) and (e.split(',')[0], e.split(',')[1]) not in removed:
                        stack.append((e, path + [e]))
                
                # REPLAY FEATURES
                if replay:
                    self.rpl(f, vertex, stack, visited)
                # END REPLAY FEATURES
        
        # REPLAY FEATURES
        if replay:
            f.close()
        # END REPLAY FEATURES

        return None,fname
        
    def BFS(self, start, goals, maxDepth=-2, replay=False, map='', hidden=[], removed=[], name=''):
        f = None
        fname = None

        if name == '':
            name = str(int(time.time()))

        # REPLAY FEATURES
        if replay:
            fname='replays/bfs/'+name+'.rpl'
            f=open(fname,'w')
            f.write(map+'\n')
        # END REPLAY FEATURES

        queue = [(start, [start], 0)]
        visited = []
        da=0

        while queue and da!=maxDepth+1:
            (vertex, path, depth) = queue.pop(0)
            da=depth

            if vertex not in visited and not (len(path)==1 and (vertex.split(',')[0], vertex.split(',')[1]) in hidden) and (vertex.split(',')[0], vertex.split(',')[1]) not in removed:
                visited.append(vertex)
                coords = vertex.split(',')
                pl=0
                ended=0

                while pl < len(coords):
                    x,y=int(coords[pl]),int(coords[pl+1])

                    if (x,y) in goals:
                        ended+=1
                    pl+=4

                if len(coords)/4==ended:
                    # REPLAY FEATURES
                    if replay:
                        f=open(fname,'a')

                        for p in path:
                            name=p.split(',')[0]+','+p.split(',')[1]
                            f.write(name+';')
                        f.close()
                    # END REPLAY FEATURES

                    return path,fname

                for e in self.edges[vertex]:
                    if e not in visited and not (len(path)==1 and (e.split(',')[0], e.split(',')[1]) in hidden) and (e.split(',')[0], e.split(',')[1]) not in removed:
                        queue.append((e, path + [e], depth+1))

            # REPLAY FEATURES
            if replay:
                self.rpl(f, vertex, queue, visited)
            # END REPLAY FEATURES

        # REPLAY FEATURES
        if replay:
            f.close()
        # END REPLAY FEATURES

        return visited,fname

    def greedy(self, start, goals, replay=False, map='', hidden=[], removed=[], name=''):
        f=None
        fname=None
        
        if name=='':
            name=str(int(time.time()))
        # REPLAY FEATURES
        if replay:
            fname='replays/greedy/'+name+'.rpl'
            f= open(fname,'w')
            f.write(map+'\n')
        # END REPLAY FEATURES

        open_nodes=[]
        closed_nodes=[]
        open_nodes.append((start, [start], 0))

        while open_nodes:
            open_nodes=sorted(open_nodes, key=lambda x: x[2])
            (vertex, path, cost) = open_nodes.pop(0)

            # REPLAY FEATURES
            if replay:
                self.rpl(f, vertex, open_nodes, closed_nodes)
            # END REPLAY FEATURES
            
            coords = vertex.split(',')
            pl=0
            tot,ended=0,0

            while pl < len(coords):
                x,y=int(coords[pl]),int(coords[pl+1])
                tot+=1
                if (x,y) in goals:
                    ended+=1
                pl+=4

            if tot==ended:
                # REPLAY FEATURES
                if replay:
                    for p in path:
                        name=p.split(',')[0]+','+p.split(',')[1]
                        f.write(name+';')
                    f.close()
                # END REPLAY FEATURES

                return path,fname

            closed_nodes.append(vertex)

            for e in self.edges[vertex]:
                if e not in closed_nodes and e not in [x[0] for x in open_nodes] and not (len(path)==1 and (e.split(',')[0], e.split(',')[1]) in hidden)  and (e.split(',')[0], e.split(',')[1]) not in removed:
                    open_nodes.append((e, path + [e], self.nodes[e].cost))
        
        # REPLAY FEATURES
        if replay:
            f.close()
        # END REPLAY FEATURES

        return None, fname

    def aStar(self, start, goals,replay=False, map='', hidden=[], removed=[], name=''):
        f=None
        fname=None
        
        if name=='':
            name=str(int(time.time()))
        # REPLAY FEATURES
        if replay:
            fname='replays/astar/'+name+'.rpl'
            f= open(fname,'w')
            f.write(map+'\n')
        # END REPLAY FEATURES

        open_nodes=[]
        closed_nodes=[]
        open_nodes.append((start, [start], 0))
        
        while open_nodes:
            open_nodes=sorted(open_nodes, key=lambda x: x[2])
            (vertex, path, cost) = open_nodes.pop(0)

            # REPLAY FEATURES
            if replay:
                self.rpl(f,vertex,open_nodes,closed_nodes)
            # END REPLAY FEATURES

            coords = vertex.split(',')
            pl=0
            tot,ended=0,0

            while pl < len(coords):
                x,y=int(coords[pl]),int(coords[pl+1])
                tot+=1

                if (x,y) in goals:
                    ended+=1
                pl+=4

            if tot==ended:
                # REPLAY FEATURES
                if replay:

                    for p in path:
                        name=p.split(',')[0]+','+p.split(',')[1]
                        f.write(name+';')
                    f.close()
                # END REPLAY FEATURES

                return path,fname

            closed_nodes.append(vertex)

            for e in self.edges[vertex]:
                if e not in closed_nodes and e not in [x[0] for x in open_nodes] and not (len(path)==1 and (e.split(',')[0], e.split(',')[1]) in hidden) and (e.split(',')[0], e.split(',')[1]) not in removed:
                    open_nodes.append((e, path + [e], cost+self.get_edge_cost(vertex,e)+self.nodes[e].cost))
        
        # REPLAY FEATURES
        if replay:
            f.close()
        # END REPLAY FEATURES

        return None,fname

    def dijkstra(self, start, goals, replay=False, map='', hidden=[], removed=[], name=''):
        f=None
        fname=None
        
        if name=='':
            name=str(int(time.time()))
        # REPLAY FEATURES
        if replay:
            fname='replays/dijkstra/'+name+'.rpl'
            f=open(fname,'w')
            f.write(map+'\n')
        # END REPLAY FEATURES

        open_nodes=[]
        closed_nodes=[]
        open_nodes.append((start, [start], 0))

        while open_nodes:
            open_nodes=sorted(open_nodes, key=lambda x: x[2])
            (vertex, path, cost) = open_nodes.pop(0)

            # REPLAY FEATURES
            if replay:
                self.rpl(f,vertex,open_nodes,closed_nodes)
            # END REPLAY FEATURES
            
            coords = vertex.split(',')
            pl=0
            tot,ended=0,0

            while pl < len(coords):
                x,y=int(coords[pl]),int(coords[pl+1])
                tot+=1

                if (x,y) in goals:
                    ended+=1
                pl+=4

            if tot==ended:

                # REPLAY FEATURES
                if replay:
                    for p in path:
                        name=p.split(',')[0]+','+p.split(',')[1]
                        f.write(name+';')
                    f.close()
                # END REPLAY FEATURES
                
                return path,fname

            closed_nodes.append(vertex)

            for e in self.edges[vertex]:
                if e not in closed_nodes and e not in [x[0] for x in open_nodes] and not (len(path)==1 and (e.split(',')[0], e.split(',')[1]) in hidden) and (e.split(',')[0], e.split(',')[1]) not in removed:
                    open_nodes.append((e, path + [e], cost+self.get_edge_cost(vertex,e)))
        # REPLAY FEATURES
        if replay:
            f.close()
        # END REPLAY FEATURES

        return None,fname

    def draw(self):
            lista_v = self.nodes.values()
            g = nx.Graph()
            for nodo in lista_v:
                n = nodo.get_name()
                g.add_node(n)
            
            for edge in self.edges:
                for adjacente in self.edges[edge]:
                    g.add_edge(edge, adjacente, weight=self.distances[(edge, adjacente)])

            pos = nx.spring_layout(g)
            nx.draw_networkx(g, pos, with_labels=True, font_weight='bold', font_size=6, arrows=True, node_size=50)
            #labels = nx.get_edge_attributes(g, 'weight')
            #nx.draw_networkx_edge_labels(g, pos, edge_labels=labels)

            plt.draw()
            plt.show()
