import copy


class Node:
    def __init__(self, name, cost):
        self.name = name
        self.cost = cost
    
    def __str__(self):
        return self.name
    
    def __hash__(self):
        return hash(self.name)

    def __eq__(self, __o: object) -> bool:
        if __o.__class__ == Node:
            return self.name == __o.name
        else:
            return False

    def get_name(self):
        return self.name
    
    def clone(self):
        return Node(copy.deepcopy(self.name), copy.deepcopy(self.map), copy.deepcopy(self.map))