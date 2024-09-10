import json

def create_new_db(file_path):
    count_genre=1
    count_cast=1
    # The db will be a dict of lists
    new_db = {
        "films": [],
        "cast":[],
        "genres":[],
    }
    # Open the json to analyze your information
    with open(file_path, 'r') as file:
        line = file.readline()
        while line:
            line = line.strip()
            if line:
                # Create the object with the right struct
                film_in_db = json.loads(line)

                #To create the cast
                list_ids_cast=[]
                for actor in film_in_db.get('cast', []):
                    encontrado=False
                    cod=''

                    count=0
                    while encontrado==False and count<len(new_db['cast']):
                        if new_db['cast'][count]['actor']==actor:
                            encontrado=True
                            cod= new_db['cast'][count]['id']
                        count+=1
                        
                    if encontrado==False:
                        new_cast={
                            "id": f'a{count_cast}',
                            "actor": actor,
                        }
                        count_cast+=1
                        new_db['cast'].append(new_cast)
                        list_ids_cast.append(f'a{count_cast}')
                    else:
                        list_ids_cast.append(cod)

                #To create the genres
                list_ids_genres=[]
                for genre in film_in_db.get('genres', []):
                    encontrado=False
                    cod=''

                    count=0
                    while encontrado==False and count<len(new_db['genres']):
                        if new_db['genres'][count]['genre']==genre:
                            encontrado=True
                            cod= new_db['genres'][count]['id']
                        count+=1
                        
                    if encontrado==False:
                        new_cast={
                            "id": f'g{count_genre}',
                            "genre": genre,
                        }
                        count_genre+=1
                        new_db['genres'].append(new_cast)
                        list_ids_genres.append(f'g{count_genre}')
                    else:
                        list_ids_genres.append(cod)
                
                # Try to obtain the values and if it doesn't work, put a empty object
                new_film = {
                    "title": film_in_db['title'],
                    "id": film_in_db.get('_id', {}).get('$oid', ''),
                    "year": film_in_db.get('year', ''),
                    "cast": list_ids_cast,
                    "genres": list_ids_genres,
                }
                
                new_db['films'].append(new_film)
                
                
            line = file.readline()
    
    with open("new_db.json", 'w+') as new_file:
        json.dump(new_db, new_file, indent=2)

# Example usage
file_path = "filmes.json"
create_new_db(file_path)
