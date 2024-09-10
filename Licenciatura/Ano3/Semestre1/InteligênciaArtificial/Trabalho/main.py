import glob
import platform
import time

import replay
from game import Game
from mapa import Map
from menu import Menu


def show_map():
    while True:
        print('\033[2J')
        maps=glob.glob('maps/*.rmap')
        maps.sort()
        map_menu=Menu(maps+['Exit'],title='Map Select').show()
        if map_menu==len(maps):
            return
        map=Map()
        map.parse_map(maps[map_menu])
        print(maps[map_menu]+':\n\n'+str(map))
        input("Press Enter to continue...")
    

def run_algos():
    while True:
        print('\033[2J')
        maps=glob.glob('maps/*.rmap')
        cached=glob.glob('cached/*.stt')
        cached.sort()
        maps.sort()
        type_menu=Menu(['New Map','Cached Map','Cancel'],title='Type').show()
        game=None
        mapn=None
        if type_menu==2:
            return
        elif type_menu==1:
            map_menu=Menu(cached+['Exit'],title='Map Select').show()
            if map_menu==len(cached):
                return
            mapn=cached[map_menu]
            game=Game.load_state(mapn)
        else:
            map_menu=Menu(maps+['Exit'],title='Map Select').show()
            if map_menu==len(maps):
                return
            map=Map()
            mapn=maps[map_menu]
            map.parse_map(mapn)
            heur_menu = Menu(['Manhatan','Euclidean','Supercover', 'Default'], title='Heuristic Select').show()
            game = Game(map)
            game.cria_grafo(heur_menu)
            if platform.system()!='Windows':
                game.save_state('cached/'+(maps[map_menu].split('/')[1].split('.')[0])+'.stt')
        while True:
            algo_menu = Menu(['BFS','DFS','Greedy','A Star','Dijkstra','Exit'], title='Algo Select').show()
            f=None
            if algo_menu==0:
                replay_menu = Menu(['Yes','No'], title='Replay').show()
                rep=replay_menu==0
                print('\033[2J')
                print('Solution BFS:')
                path,f=game.solucaoBFS(rep,mapn)
            elif algo_menu==1:
                replay_menu = Menu(['Yes','No'], title='Replay').show()
                rep=replay_menu==0
                print('\033[2J')
                print('Solution DFS:')
                path,f = game.solucaoDFS(rep,mapn)
            elif algo_menu==2:
                replay_menu = Menu(['Yes','No'], title='Replay').show()
                rep=replay_menu==0
                print('\033[2J')
                print('Solution Greedy')
                path,f = game.solucaoGreedy(rep, mapn)
            elif algo_menu==3:
                replay_menu = Menu(['Yes','No'], title='Replay').show()
                rep=replay_menu==0
                print('\033[2J')
                print('Solution A-Star:')
                path,f = game.solucaoAS(rep,mapn)
            elif algo_menu==4:
                replay_menu = Menu(['Yes','No'], title='Replay').show()
                rep=replay_menu==0
                print('\033[2J')
                print('Solution Dijkstra:')
                path,f = game.solucaoDijkstra(rep,mapn)
            elif algo_menu==5:
                break
            move_list = game.get_move_list(path)
            score = game.check_score(move_list)
            print(game.map.print_path(path))
            print('Path: '+str(move_list))
            print('Score: '+str(score))
            input("Press Enter to continue...")
            path_menu = Menu(['Show Moves','Exit']).show()
            if path_menu==0:
                game.map.show_path(path)
            if f!=None:
                search_menu = Menu(['Show Steps','Exit']).show()
                if search_menu==0:
                    replay.show_replay(f, mapa=game.map)
            input("Press Enter to continue...")

def run_tests():
    maps=glob.glob('maps/*.rmap')
    maps.sort()
    for map in maps:
        print('-------------------------------------------------------------------')
        print('Map: '+map)
        nm=Map()
        nm.parse_map(map)
        game=Game(nm)
        game.cria_grafo(0)
        print('\nBFS: ')
        path,f=game.solucaoBFS()
        moves=game.get_move_list(path)
        score=game.check_score(moves)
        print('Score: '+str(score))
        print('\nDFS: ')
        path,f=game.solucaoDFS()
        moves=game.get_move_list(path)
        score=game.check_score(moves)
        print('Score: '+str(score))
        print('\nGreedy: ')
        path,f=game.solucaoGreedy()
        moves=game.get_move_list(path)
        score=game.check_score(moves)
        print('Score: '+str(score))
        print('\nA Star: ')
        path,f=game.solucaoAS()
        moves=game.get_move_list(path)
        score=game.check_score(moves)
        print('Score: '+str(score))
        print('\nDijkstra: ')
        path,f=game.solucaoDijkstra()
        moves=game.get_move_list(path)
        score=game.check_score(moves)
        print('Score: '+str(score))
    input("Press Enter to continue...")
    


def build_graph():
    while True:
        print('\033[2J')
        maps=glob.glob('maps/*.rmap')
        maps.sort()
        map_menu=Menu(maps+['Exit'],title='Map Select').show()
        if map_menu==len(maps):
            return
        map=Map()
        map.parse_map(maps[map_menu])
        heur_menu = Menu(['Manhatan','Euclidean','Supercover', 'Default'], title='Heuristic Select').show()
        game = Game(map)
        t_start=time.time()
        game.cria_grafo(heur_menu)
        t_end=time.time()
        print('Build Time: '+str(t_end-t_start))
        nodes = 0
        for g in game.g:
            nodes += len(g.nodes)
        print('Number of Nodes:'+str(nodes))
        n_edges = 0
        for g in game.g:
            for edge in g.edges:
                n_edges += len(g.edges[edge])
        print('Number of Edges:'+str(n_edges))
        if platform.system()!='Windows':
            game.save_state('cached/'+(maps[map_menu].split('/')[1].split('.')[0])+'.stt')
        input("Press Enter to continue...")

def load_all():
    maps=glob.glob('maps/*.rmap')
    maps.sort()
    for map in maps:
        print('-------------------------------------------------------------------')
        print('Map: '+map)
        mapo=Map()
        mapo.parse_map(map)
        game = Game(mapo)
        t_start=time.time()
        game.cria_grafo(3)
        t_end=time.time()
        print('Build Time: '+str(t_end-t_start))
        nodes = 0
        for g in game.g:
            nodes += len(g.nodes)
        print('Number of Nodes:'+str(nodes))
        n_edges = 0
        for g in game.g:
            for edge in g.edges:
                n_edges += len(g.edges[edge])
        print('Number of Edges:'+str(n_edges))
        if platform.system()!='Windows':
            game.save_state('cached/'+(map.split('/')[1].split('.')[0])+'.stt')
    print('-------------------------------------------------------------------')    
    input("Press Enter to continue...")

def show_graph():
    while True:
        maps=glob.glob('cached/*.stt')
        maps.sort()
        map_menu=Menu(maps+['Exit'],title='Graph Select').show()
        if map_menu==len(maps):
            return
        game=Game.load_state(maps[map_menu])
        for g in game.g:
            g.draw()

def main():
    run=True
    while run:
        print('\033[2J')
        options=['Run Algos','Build Graph','Build All','Show Map','Show Graph','Run Tests','Exit']
        main_menu=Menu(options,title='Main Menu').show()
        if main_menu==0:
            run_algos()
        elif main_menu==1:
            build_graph()
        elif main_menu==2:
            load_all()
        elif main_menu==3:
            show_map()
        elif main_menu==4:
            show_graph()
        elif main_menu==5:
            run_tests()
        elif main_menu==6:
            run=False

if __name__ == '__main__':
    main()
    
