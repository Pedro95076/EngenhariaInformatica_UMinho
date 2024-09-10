import sys
from time import sleep

from mapa import Map

def str_to_cords(string):
    coords = string.split(',')
    pl_coords = []
    i = 0
    while i < len(coords):
        pl_coords.append((int(coords[i]), int(coords[i+1])))
        i += 2
    return pl_coords

def show_replay(file, speed=0.005, mapa=None):

    map = Map()
    path = []
    lines=[]
    with open(file, 'r') as f:
        lines=f.readlines()
    if mapa==None:
        map.parse_map(lines[0].strip())
    else :
        map=mapa
    string=''
    n=0
    for line in lines[1:-1]:
        nodes = {}
        line = line.split(';')
        atual = str_to_cords(line[0])
        for node in line[1:]:
            node = node.split('(')
            nodes[(int(node[0].split(',')[0]), int(node[0].split(',')[1]))] = int(node[1].split(')')[0])
        for i in range(len(map.mapa)):
            for j in range(len(map.mapa[i])):
                if (j,i) in atual:
                    string += '\033[38;2;125;0;0m██\033[0m'
                elif (j,i) in nodes and nodes[(j,i)] <= 0:
                    string += '\033[38;2;{};{};0m██\033[0m'.format(nodes[(j, i)]*2+255, nodes[(j, i)]*2+125)
                elif (j,i) in nodes:
                    string += '\033[38;2;0;{};{}m██\033[0m'.format(nodes[(j, i)]*2+125,nodes[(j, i)]*2)
                elif map.mapa[i][j] == -1:
                    string += '██'
                elif map.mapa[i][j] == 0:
                    string += '  '
                elif map.mapa[i][j] == 1:
                    string += '▒▒'
            string += '\n'
        print('\033[2JStep '+str(n+1)+':\n'+string)
        sleep(speed)
        string=''
        n+=1
    for c in lines[-1].split(';')[:-1]:
        path.append((int(c.split(',')[0]),int(c.split(',')[1])))
    for i in range(len(path)-1):
        path+=map.get_supercover_line(path[i][0],path[i][1],path[i+1][0],path[i+1][1])
    for i in range(len(map.mapa)):
            for j in range(len(map.mapa[i])):
                if (j,i) in path:
                    string += '\033[38;2;0;0;125m██\033[0m'
                elif (j,i) in nodes and nodes[(j,i)] <= 0:
                    string += '\033[38;2;{};{};0m██\033[0m'.format(nodes[(j, i)]*2+255,nodes[(j, i)]*2+125)
                elif (j,i) in nodes:
                    string += '\033[38;2;0;{};{}m██\033[0m'.format(nodes[(j, i)]*2+125,nodes[(j, i)]*2)
                elif map.mapa[i][j] == -1:
                    string += '██'
                elif map.mapa[i][j] == 0:
                    string += '  '
                elif map.mapa[i][j] == 1:
                    string += '▒▒'
            string += '\n'
    print('\033[2JFinal (Step '+str(n)+')\n'+string)

if __name__ == '__main__':
    file=sys.argv[1]
    speed=0.1
    if len(sys.argv)>2:
        try:
            speed=float(sys.argv[2])
        except:
            speed=0.1
    show_replay(file, speed)
