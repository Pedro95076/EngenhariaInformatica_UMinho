import sys
import re
regex = "([Oo][Nn]|[Oo][Ff][Ff]|=|[-+]?\d+)"

file = open(sys.argv[1],"r")
content = file.read()

totalValue = 0
counterOn = True # contador começa a true

res = re.findall(regex,content)
for word in res:
    lowerWord = word.lower()
    match lowerWord:
        case _ if lowerWord.lstrip("+-").isdigit():
            number = int(word)
            # print(f"Got number {number}")
            if (counterOn == True):
                totalValue = totalValue + number
                # print(f"New total value: {totalValue}")
        case "=":
            print(f"Current total: {totalValue}")
        case "on":
            # print("Turned counter on")
            counterOn = True
        case "off":
            # print("Turned counter off")
            counterOn = False
        case _:
            print(f"Parser got incorrect word: {word}")

print(f"Final totalValue: {totalValue}")

