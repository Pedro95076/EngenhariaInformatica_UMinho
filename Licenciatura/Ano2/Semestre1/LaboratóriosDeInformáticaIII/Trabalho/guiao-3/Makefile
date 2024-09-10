guiao-3 : ./obj/main.o ./obj/auxiliarFunc.o ./obj/auxiliarStruct.o ./obj/auxiliarTree.o ./obj/HT_commits.o ./obj/HT_repos.o ./obj/HT_users.o ./obj/interface.o ./obj/queries.o ./obj/verification.o
	gcc -O2 -Wall -g ./obj/main.o ./obj/auxiliarFunc.o ./obj/auxiliarStruct.o ./obj/auxiliarTree.o ./obj/HT_commits.o ./obj/HT_repos.o ./obj/HT_users.o ./obj/interface.o ./obj/queries.o ./obj/verification.o -o guiao-3

test : ./obj/test.o ./obj/auxiliarFunc.o ./obj/auxiliarStruct.o ./obj/auxiliarTree.o ./obj/HT_commits.o ./obj/HT_repos.o ./obj/HT_users.o ./obj/interface.o ./obj/queries.o ./obj/verification.o
	gcc -O2 -Wall -g ./obj/test.o ./obj/auxiliarFunc.o ./obj/auxiliarStruct.o ./obj/auxiliarTree.o ./obj/HT_commits.o ./obj/HT_repos.o ./obj/HT_users.o ./obj/interface.o ./obj/queries.o ./obj/verification.o -o test

./obj/main.o : ./src/main.c
	gcc -c -Wall -g ./src/main.c -o ./obj/main.o

./obj/auxiliarFunc.o : ./src/auxiliarFunc.c ./src/auxiliarFunc.h
	gcc -c -Wall -g ./src/auxiliarFunc.c -o ./obj/auxiliarFunc.o

./obj/auxiliarStruct.o : ./src/auxiliarStruct.c ./src/auxiliarStruct.h
	gcc -c -Wall -g ./src/auxiliarStruct.c -o ./obj/auxiliarStruct.o

./obj/auxiliarTree.o : ./src/auxiliarTree.c ./src/auxiliarTree.h
	gcc -c -Wall -g ./src/auxiliarTree.c -o ./obj/auxiliarTree.o

./obj/HT_commits.o : ./src/HT_commits.c ./src/HT_commits.h
	gcc -c -Wall -g ./src/HT_commits.c -o ./obj/HT_commits.o

./obj/HT_repos.o : ./src/HT_repos.c ./src/HT_repos.h
	gcc -c -Wall -g ./src/HT_repos.c -o ./obj/HT_repos.o

./obj/HT_users.o : ./src/HT_users.c ./src/HT_users.h
	gcc -c -Wall -g ./src/HT_users.c -o ./obj/HT_users.o

./obj/interface.o : ./src/interface.c ./src/interface.h
	gcc -c -Wall -g ./src/interface.c -o ./obj/interface.o

./obj/queries.o : ./src/queries.c ./src/queries.h
	gcc -c -Wall -g ./src/queries.c -o ./obj/queries.o

./obj/verification.o : ./src/verification.c ./src/verification.h
	gcc -c -Wall -g ./src/verification.c -o ./obj/verification.o

./obj/test.o : ./src/test.c
	gcc -c -Wall -g ./src/test.c -o ./obj/test.o

clean:
	rm -f ./obj/*.o ./saida/*.txt ./src/tests/saida/*.txt ./guiao-3 ./test