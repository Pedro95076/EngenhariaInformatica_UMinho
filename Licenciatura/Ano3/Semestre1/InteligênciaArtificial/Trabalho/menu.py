class Menu:
    def __init__(self, options, title='Menu'):
        self.title = title
        self.options = options
        self.selected = 0
    
    def show(self):
        while True:
            print('\033[2J')
            print(self.title)
            for i in range(len(self.options)-1):
                print(i+1,') '+self.options[i])
            print('0 ) '+self.options[-1])
            key = input('-> ')
            try :
                if int(key) <len(self.options)+1 and int(key)>0:
                    return int(key)-1
                else:
                    return len(self.options)-1
            except:
                continue

