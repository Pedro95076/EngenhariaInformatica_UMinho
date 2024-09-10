############################################################ 
# Class Map                                                #
############################################################
# Esta classe representa o mapa do jogo. Ela é responsável #
# por carregar um mapa e armazenar as informações          #
# necessárias para o jogo.                                 #
############################################################

from time import sleep


class Map:
    def __init__(self):
        self.mapa = []
        self.player = []
        self.goals = []

    ############################################################
    # A função __str__ é chamada quando se pretende imprimir   #
    # um objeto da classe Map. Esta retorna uma string com o   #
    # mapa.                                                    #
    ############################################################

    def __str__(self):
        string = ''
        for i in range(len(self.mapa)):
            for j in range(len(self.mapa[i])):
                if (j,i) in self.player:
                    string += 'P'
                elif self.mapa[i][j] == -1:
                    string += 'X'
                elif self.mapa[i][j] == 0:
                    string += '-'
                elif self.mapa[i][j] == 1:
                    string += 'F'
            string += '\n'
        return string[:-1]

    ############################################################
    # A função parse_map recebe o nome de um arquivo e         #
    # carrega o mapa contido neste arquivo.                    #
    #                                                          #
    # O arquivo deve conter um mapa de caracteres.             #
    # Os caracteres possíveis são:                             #
    #                                                          #
    # X: Parede                                                #
    # -: Espaço vazio                                          #
    # P: Posição inicial do jogador                            #
    # F: Posição de um objetivo                                #
    #                                                          #
    # O mapa deve ser retangular.                              #
    ############################################################

    def parse_map(self, filename):
        max = 0
        x = 0
        y = 0
        with open(filename,'r') as f:
             for line in f.readlines():
                x=0
                l=[]
                for c in line:
                    if c == 'X':
                        x+=1
                        l.append(-1)
                    elif c == '-':
                        x+=1
                        l.append(0)
                    elif c == 'P':
                        l.append(0)
                        self.player.append((x,y))
                        x+=1
                    elif c == 'F':
                        l.append(1)
                        self.goals.append((x,y))
                        x+=1
                if len(l) > max:
                    max = len(l)
                else:
                    for i in range(max - len(l)):
                        l.append('#')
                self.mapa.append(l)
                y+=1

    ############################################################
    # A função get_player retorna a posição do jogador.        #
    ############################################################

    def get_players(self):
        return self.player
    
    ############################################################
    # A função get_goals retorna uma lista com as posições     #
    # dos objetivos.                                           #
    ############################################################

    def get_goals(self):
        return self.goals

    ############################################################
    # A função get_piece retorna o conteúdo de uma posição do  #
    # mapa.                                                    #
    #                                                          #
    # O conteúdo de uma posição é um tuplo (x, y), onde x é    #
    # o valor da posição e y é o custo de se mover para esta   #
    # posição.                                                 #
    ############################################################
    
    def get_piece(self, x, y):
        if y>=len(self.mapa) or x>=len(self.mapa[0]) or y<0 or x<0:
            return (-1, 25)
        if self.mapa[y][x] == -1:
            return (-1, 25)
        elif self.mapa[y][x] == 0:
            return (0, 1)
        elif self.mapa[y][x] == 1:
            return (1, 0)

    ############################################################
    # A função get_supercover_line recebe duas posições e      #
    # retorna uma lista com todas as posições que estão        #
    # entre as duas posições.                                  #                                            
    ############################################################

    def get_supercover_line(self,x0,y0,x1,y1):
        dx=abs(x1-x0)
        dy=abs(y1-y0)
        sx=1 if x0<x1 else -1
        sy=1 if y0<y1 else -1
        err=dx-dy
        pos_list=[]
        while True:
            pos_list.append((x0,y0))
            if x0==x1 and y0==y1:
                break
            e2=2*err
            if e2>-dy:
                err-=dy
                x0+=sx
            if e2<dx:
                err+=dx
                y0+=sy
        return pos_list    
        
    def print_path(self, path):
        color = ['\033[38;2;255;19;2m', '\033[38;2;112;255;2m', '\033[38;2;2;145;255m', '\033[38;2;255;120;2m',
                 '\033[38;2;2;255;247m', '\033[38;2;255;230;2m', '\033[38;2;154;2;255m', '\033[38;2;255;2;230m']
        player_stops = {}
        player_path = {}
        if path==None:
            return "No path found"
        
        for state in path:
            spliter = state.split(',')
            n=0
            while n<len(spliter):
                c=int(n/4)
                if color[c] in player_stops:
                    player_stops[color[c]].append((int(spliter[n+0]),int(spliter[n+1])))
                else:
                    player_stops[color[c]] = [(int(spliter[n+0]),int(spliter[n+1]))]
                n+=4
        
        for player in player_stops:
            for i in range(len(player_stops[player])-1):
                if player in player_path:
                    player_path[player]+=self.get_supercover_line(player_stops[player][i][0],player_stops[player][i][1],player_stops[player][i+1][0],player_stops[player][i+1][1])
                else:
                    player_path[player] = self.get_supercover_line(player_stops[player][i][0],player_stops[player][i][1],player_stops[player][i+1][0],player_stops[player][i+1][1])
        
        string = ''
        for player in player_stops:
            for i in range(len(self.mapa)):
                for j in range(len(self.mapa[i])):
                    added = False
                    if (j, i) in player_stops[player] and not added:
                        string += player+'⛟\033[0m '
                        added = True
                    if (j, i) in player_path[player] and not added:
                        string += player+'><\033[0m'
                        added = True
                    if added:
                        continue
                    elif self.mapa[i][j] == -1:
                        string += '██'
                    elif self.mapa[i][j] == 0:
                        string += '  '
                    elif self.mapa[i][j] == 1:
                        string += '▒▒'
                string += '\n'

        for i in range(len(self.mapa)):
            for j in range(len(self.mapa[i])):
                added = False
                for player in player_stops:
                    if (j, i) in player_stops[player] and not added:
                        string += player+'⛟\033[0m '
                        added = True
                for player in player_stops:
                    if (j, i) in player_path[player] and not added:
                        string += player+'><\033[0m'
                        added = True
                if added:
                    continue
                elif self.mapa[i][j] == -1:
                    string += '██'
                elif self.mapa[i][j] == 0:
                    string += '  '
                elif self.mapa[i][j] == 1:
                    string += '▒▒'
            string += '\n'
        return string[:-1]
    
    def show_path(self, path):
        color = ['\033[38;2;255;19;2m', '\033[38;2;112;255;2m', '\033[38;2;2;145;255m', '\033[38;2;255;120;2m', 
                 '\033[38;2;2;255;247m', '\033[38;2;255;230;2m', '\033[38;2;154;2;255m', '\033[38;2;255;2;230m']
        player_stops = {}
        player_velos = {}
        player_path = {}
        string = ''

        for state in path:
            spliter = state.split(',')
            n=0
            while n<len(spliter):
                c=int(n/4)
                if color[c] in player_stops:
                    player_stops[color[c]].append((int(spliter[n+0]),int(spliter[n+1])))
                    player_velos[color[c]].append((int(spliter[n+2]),int(spliter[n+3])))
                else:
                    player_stops[color[c]] = [(int(spliter[n+0]),int(spliter[n+1]))]
                    player_velos[color[c]] = [(int(spliter[n+2]),int(spliter[n+3]))]
                n+=4
        
        for player in player_stops:
            for i in range(len(player_stops[player])-1):
                if player in player_path:
                    player_path[player].append(self.get_supercover_line(player_stops[player][i][0],player_stops[player][i][1],player_stops[player][i+1][0],player_stops[player][i+1][1]))
                else:
                    player_path[player] = [self.get_supercover_line(player_stops[player][i][0],player_stops[player][i][1],player_stops[player][i+1][0],player_stops[player][i+1][1])]
        
        for n in range(len(path)-1):
            crash = {}
            reset = {}
            for player in player_stops:
                if player_velos[player][n+1][0]==0 and player_velos[player][n+1][1]==0:
                    if (abs(player_velos[player][n][0])>1 or abs(player_velos[player][n][1])>1) and (abs(player_stops[player][n+1][0]-player_stops[player][n][0])>1 or abs(player_stops[player][n+1][1]-player_stops[player][n][1])>1):
                        crash[player]=False
                        reset[player]=True
                    elif abs(player_velos[player][n][0])>1 or abs(player_velos[player][n][1])>1:
                        crash[player]=True
                        reset[player]=False
                    else:
                        crash[player]=False
                        reset[player]=False
                else:
                    crash[player]=False
                    reset[player]=False
            for i in range(len(self.mapa)):
                for j in range(len(self.mapa[i])):
                    added = False
                    for player in player_stops:
                        if (j, i) == player_stops[player][n+1] and reset[player]:
                            string += player+'⏮\033[0m '
                            added = True
                        elif (j, i) == player_stops[player][n+1] and crash[player]:
                            string += player+'✸\033[0m '
                            added = True
                        elif (j, i) == player_stops[player][n+1]:
                            string += player+'⛟\033[0m '
                            added = True
                        
                    for player in player_stops:
                        if (j, i) in player_path[player][n] and not added and not reset[player]:
                            string += player+'><\033[0m'
                            added = True
                    if added:
                        continue
                    elif self.mapa[i][j] == -1:
                        string += '██'
                    elif self.mapa[i][j] == 0:
                        string += '  '
                    elif self.mapa[i][j] == 1:
                        string += '▒▒'
                string += '\n'
            print('\033[2JStep '+str(n+1)+':\n'+string)
            sleep(1)
            string=''
