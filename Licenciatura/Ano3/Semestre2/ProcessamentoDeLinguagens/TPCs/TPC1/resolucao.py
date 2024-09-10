import sys

# read the dataset from the stdin
def read_dataset():
    data = []
    next(sys.stdin)
    #ignore the first line of the dataset (header)
    for line in sys.stdin:
        data.append(line)
    return data

# create an alphabetically ordered list of the different sports modalities
def sports_list(data):
    sports = []

    for line in data:
        sport = line.split(',')[8]

        if sport not in sports:
            sports.append(sport)
    
    sports.sort()
    return sports

# get the percentage of the athletes that are fit and unfit
def athletes_status(data):
    fit = 0
    unfit = 0

    for line in data:
        status = line.split(',')[12]

        #if status is true then the athlete is fit, else is unfit
        if status == "true\n":
            fit += 1
        else:
            unfit += 1

    total = fit + unfit

    fit_percentage = (fit / total) * 100
    unfit_percentage = (unfit / total) * 100

    return (fit_percentage, unfit_percentage)

# distribution of the athletes per age group ([0,4], [5,9], etc)
def athletes_age(data):
    age_groups = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    for line in data:
        age = int(line.split(',')[5])

        group = age // 5

        age_groups[group] += 1
    
    # convert the values to percentages  
    total = sum(age_groups)
    percentages = [(f"{i*5}-{i*5+4}", (age_groups[i] / total) * 100) for i in range(len(age_groups))]

    return percentages

# main that receives the filename as an argument
def main():
    data = read_dataset()
    print(sports_list(data))
    print(athletes_status(data))
    print(athletes_age(data))

if __name__ == "__main__":
    main()



