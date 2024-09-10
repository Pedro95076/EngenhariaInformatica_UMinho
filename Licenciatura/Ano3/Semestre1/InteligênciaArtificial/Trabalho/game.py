import pickle
import threading
import time

from grafo import Graph
from rwlock import ReadWriteLock


class Game():

    ###########################################################
    # Class 'Game'                                            #
    ###########################################################
    # Inicia a classe de jogo, responsável pela criação       #
    # do grafo, para tal necessita de receber um mapa.        #
    # O grafo resultante é composto por todos os possiveis    #
    # estados, do tipo: 'x,y,vx,vy,p,m'                       #
    # Onde x,y são as coordenadas atuais,                     #
    # vx,vy as respetivas velocidades                         #
    ###########################################################
    def __init__(self, map):
        self.g=[]
        self.map=map
        self.start=map.get_players()
        self.start_state=[]
        for p in self.start:
            self.start_state+=[str(p[0])+','+str(p[1])+',0,0']
        self.goal=map.get_goals()
        node_cost=[]
        for p in self.start:
            dist_to_end=[]
            for g in self.goal:
                dist_to_end.append(len(self.map.get_supercover_line(p[0],p[1],g[0],g[1])))
            node_cost+=[min(dist_to_end)]
        i=0
        while i<len(self.start):
            g=Graph()
            g.add_node(self.start_state[i],node_cost[i])
            self.g.append(g)
            i+=1
        self.moves={'NW':(-1,-1),'N':(0 ,-1),'NE':( 1,-1),
                    'W' :(-1, 0),'K':(0 , 0),'E' :( 1, 0),
                    'SW':(-1, 1),'S':(0 , 1),'SE':( 1, 1)}
                
    def to_pl_coords(self,estado):
        coords = estado.split(',') 
        pl_coords = []
        i = 0
        while i < len(coords):
            pl_coords.append((int(coords[i]),int(coords[i+1])))
            i+=4
        return pl_coords

    def exec_expansion(self, id, heur,tc_lock,states,to_check):
        tc_lock.wacquire()
        if len(to_check)==0:
            tc_lock.wrelease()
            return
        state=to_check.pop(0)
        states.append(state)
        tc_lock.wrelease()
        for s in self.expande(id, state, heur):
            coords=s.split(',')
            x,y,at,tot,ended=0,0,0,0,0
            pl=0
            while pl < len(coords):
                x,y=int(coords[pl]),int(coords[pl+1])
                tot+=1
                if (x,y) in self.goal:
                    ended+=1
                pl+=4
            tc_lock.racquire()
            cstates=states
            cto_check=to_check
            tc_lock.rrelease()
            if s not in cstates and s not in cto_check  and  tot!=ended:
                tc_lock.wacquire()
                to_check.append(s)
                tc_lock.wrelease()

    ###########################################################
    # Partindo do estado inicial e conforme o mapa, utiliza   #
    # todas as ações possíveis como transições de estado      #
    # para construir o grafo que será utilizado para procura  #
    ###########################################################
    def cria_grafo(self, heur):
        id=0
        while id < len(self.start):
            states=[]
            tc_lock=ReadWriteLock()
            to_check=[self.start_state[id]]
            sz=len(to_check)
            while sz>0 or threading.activeCount()>1:
                tc_lock.racquire()
                sz=len(to_check)
                tc_lock.rrelease()
                if threading.activeCount()<=16 and sz>0:
                    thread=threading.Thread(target=self.exec_expansion,args=(id,heur,tc_lock,states,to_check))
                    thread.start()
            id+=1

    ############################################################
    # Dado um estado expande a lista de procura para           #
    # todos os possiveis estados, provenientes do atual,       #
    # tendo em conta as coordenadas e velocidades atuais.      # 
    #                                                          #
    # É de notar que as velocidades são comulativas, ou seja,  #
    # a velocidade atual é somada à velocidade da ação         #
    # pretendida.                                              #
    ############################################################ 
    def expande(self, id, estado, heur):
        lista=[]
        cur=estado.split(',')
        for mv in self.moves:

            # Variáveis de estado
            x=int(cur[0])
            y=int(cur[1])
            vx=int(cur[2])
            vy=int(cur[3])
            points=0
            node_cost=0
            dx,dy=self.moves[mv]
            x1,y1=x+vx+dx,y+vy+dy
            # Obter percurso até ao próximo estado
            path=self.map.get_supercover_line(x,y,x1,y1)
            
            # Verifica se o caminho pode ser efetuado
            i=0
            wall=False
            path_len=len(path)
            while (path and i<path_len):
                cord_x,cord_y = path[i]
                piece=self.map.get_piece(cord_x,cord_y)
                points+=piece[1]
                if piece[0]==-1: # Caso encontre um obstáculo
                    vx,vy=0,0
                    wall=True
                    break
                elif piece[0]==1: # Caso chegue à meta
                    x,y=path[i]
                    vx,vy=vx+dx,vy+dy
                    wall=True
                    break
                i+=1
            if not wall:
                if (x,y)==(x1,y1): #Penalização por não se mover
                    node_cost+=10
                x,y=x1,y1
                vx,vy=vx+dx,vy+dy

            # Nome do nodo
            node_name=str(x)+','+str(y)+','+str(vx)+','+str(vy)
            
            # Calculo do peso do nodo:
            # Para tal usa-se a menor distancia entre o nodo e um dos objetivos
            dist_to_end=[]
            for g in self.goal:
                if heur==0 or heur==3: #heuristica de supercover line 
                    dist_to_end.append(len(self.map.get_supercover_line(x,y,g[0],g[1])))
                elif heur==1: #heuristica de manhattan
                    dist_to_end.append(abs(x-g[0])+abs(y-g[1]))
                elif heur==2: #heuristica de euclidiana
                    dist_to_end.append(((x-g[0])**2+(y-g[1])**2)**0.5)
            node_cost+=min(dist_to_end)

            # Calculo do custo da aresta:
            # Para tal usa-se a deiferenca de pontuacoes entre o estado atual
            # e apos efetuar o movimento.
            edge_cost=points

            # Adiciona a aresta ao grafo entre o nodo atual e o nodo criado
            self.g[id].add_edge(estado,node_name,edge_cost,None,node_cost)

            # Adiciona o nodo criado à lista de nodos a serem expandidos
            lista.append(node_name)
        return lista

    def runalg(self, func, rep=False, map=''):
        fname=str(int(time.time()))
        if len(self.start_state)==1:
            t_start=time.time()
            res=func(self.g[0],self.start_state[0],self.goal,replay=rep,map=map, name=fname+'player1_r0.txt')
            t_end=time.time()
            print('Execution Time: ',(t_end-t_start)*1000)
        else:
            goals=self.goal
            t_start=time.time()
            pl_amount=len(self.start_state)
            res=[]
            i=0
            while i<pl_amount:
                alg=func(self.g[i],self.start_state[i],goals,replay=rep,map=map, name=fname+'player'+str(i+1)+'_r0.txt')
                res.append(alg[0])
                if rep:
                    print('Search for Player ',i+1,' from start to end saved in: ',alg[1])
                i+=1
            maxl=max([len(x) for x in res])
            i=1
            while i<maxl:
                recheck=False
                at=[]
                tc=[]
                rm=[]
                for j in range(pl_amount):
                    if len(res[j])>i:
                        tc.append(j)
                        at.append((res[j][i].split(',')[0],res[j][i].split(',')[1]))
                    else:
                        rm.append((res[j][-1].split(',')[0],res[j][-1].split(',')[1]))
                        at.append((res[j][-1].split(',')[0],res[j][-1].split(',')[1]))
                tc.reverse()
                for j in tc:
                    val=(res[j][i].split(',')[0],res[j][i].split(',')[1])
                    if at.count(val)>1:
                        at.remove(val)
                        alg=func(self.g[j],res[j][i-1],goals,replay=rep,map=map,hidden=at, removed=rm, name=fname+'player'+str(j+1)+'_r'+str(i)+'.txt')
                        new_list=alg[0]
                        if rep:
                            print('Re-search in step',i,'for Player',j+1,'from',res[j][i-1],'to end saved in:',alg[1])
                        if new_list!=[] and new_list!=None and len(new_list)>1 and (new_list[1].split(',')[0],new_list[1].split(',')[1]) not in at:
                            res[j] = res[j][:i] + new_list[1:]
                            at.append((new_list[1].split(',')[0],new_list[1].split(',')[1]))
                        else:
                            men=1
                            nval=res[j][i-men].split(',')[0]+','+res[j][i-men].split(',')[1]+',0,0'
                            while (nval.split(',')[0], nval.split(',')[1]) in at:
                                men+=1
                                nval=res[j][i-men].split(',')[0]+','+res[j][i-men].split(',')[1]+',0,0'
                            alg=func(self.g[j],nval,goals,replay=rep,map=map,removed=rm,name=fname+'player'+str(j+1)+'_r'+str(i)+'.txt')
                            new_list=alg[0]
                            if rep:
                                print('Re-search in step',i,'for Player',j+1,'from',res[j][i-1],'to end saved in:',alg[1])
                            res[j] = res[j][:i] + new_list
                            at.append((nval.split(',')[0],nval.split(',')[1]))
                        recheck=True
                    if recheck:
                        break

                maxl=max([len(x) for x in res])
                if not recheck:
                    i+=1
            
            flist=[]
            i=0
            while i<maxl:
                step=''
                for j in range(pl_amount):
                    if len(res[j])>i:
                        step+=res[j][i]+','
                    else:
                        step+=res[j][-1]+','
                flist.append(step[:-1])
                i+=1
            res=flist,None
            t_end=time.time()
            print('Execution Time: ',(t_end-t_start)*1000)
        return res

    # Encontra a solução utilizando DFS (recorre à classe grafo e node implementada antes
    def solucaoDFS(self,rep=False,map=''):
        return self.runalg(Graph.DFS,rep,map)

    # Encontra a solução utilizando BFS (recorre à classe grafo e node implementada antes
    def solucaoBFS(self,rep=False,map=''):
        return self.runalg(Graph.BFS,rep,map)

    # Encontra a solução utilizando A* (recorre à classe grafo e node implementada antes
    def solucaoAS(self,rep=False,map=''):
        return self.runalg(Graph.aStar,rep,map)

    # Encontra a solução utilizando Greedy (recorre à classe grafo e node implementada antes
    def solucaoGreedy(self,rep=False,map=''):
        return self.runalg(Graph.greedy,rep,map)

    def solucaoDijkstra(self,rep=False,map=''):
        return self.runalg(Graph.dijkstra,rep,map)      

    def get_state_move(self,state1, state2):
        mv=''
        i=0
        stt1 = state1.split(',')
        stt2 = state2.split(',')
        while i<len(stt1):
            xdiff=int(stt2[i])-int(stt1[i])
            ydiff=int(stt2[i+1])-int(stt1[i+1])
            vxdiff=int(stt2[i+2])-int(stt1[i+2])
            vydiff=int(stt2[i+3])-int(stt1[i+3])
            if vxdiff<=1 and vydiff<=1 and vxdiff>=-1 and vydiff>=-1:
                for key in self.moves:
                    if self.moves[key]==(vxdiff,vydiff):
                        mv+=key
            elif xdiff==0 and ydiff==0:
                mv+='Crash'
            else:
                mv+='Backtrack'
            mv+=','
            i+=4
        mv=mv[:-1]
        return mv

    def get_move_list(self,caminho):
        move_list=[]
        i=1
        if caminho==None:
            return None
        while i<len(caminho):
            move_list.append(self.get_state_move(caminho[i-1],caminho[i]))
            i+=1
        return move_list

    def save_state(self,filename):
        with open(filename,'wb') as f:
            pickle.dump(self,f,pickle.HIGHEST_PROTOCOL)
    
    def load_state(filename):
        with open(filename,'rb') as f:
            game=pickle.load(f)
        return game

    def check_score(self, path):
        score=0
        if path==None:
            return score
        for p in path:
            for mv in p.split(','):
                if mv in self.moves:
                    score+=1
                elif mv=='Backtrack':
                    score+=10
                else:
                    score+=25
        return score
