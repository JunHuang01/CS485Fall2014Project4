PROGS = mcput mcget mcdel mclist
Host := 127.0.0.1
Port= 8888
SecreteKey = 12345
FileName := MyFile
INC_DIR := include
CL_DIR := client

ALL: clean $(PROGS)
	
mcput: $(CL_DIR)/mcput.c $(INC_DIR)/csapp.c
	gcc $(CL_DIR)/mcput.c $(INC_DIR)/csapp.c -lpthread -g -o mcput

mcget: $(CL_DIR)/mcget.c $(INC_DIR)/csapp.c
	gcc $(CL_DIR)/mcget.c $(INC_DIR)/csapp.c -lpthread -g -o mcget

mcdel: $(CL_DIR)/mcdel.c $(INC_DIR)/csapp.c
	gcc $(CL_DIR)/mcdel.c $(INC_DIR)/csapp.c -lpthread -g -o mcdel

mclist: $(CL_DIR)/mclist.c $(INC_DIR)/csapp.c
	gcc $(CL_DIR)/mclist.c $(INC_DIR)/csapp.c -lpthread -g -o mclist

clean:
	rm -f *.o $(PROGS)

test_all: mcput_test mcget_test mcdel_test mclist_test

mcput_test:
	@echo "===== Started mcput test====="
	./mcput 0
	./mcput 0 0 0 0 0 0
	./mcput $(Host) $(Port) $(SecreteKey) $(FileName)
	./mcput $(Port) $(SecreteKey) $(FileName)
	@echo "===== Ended mcput test======"

mcget_test:
	@echo "===== Started mcget test======"
	./mcget 0
	./mcget 0 0 0 0 0 
	./mcget $(Host) $(Port) $(SecreteKey) $(FileName)
	./mcget $(Port) $(SecreteKey) $(FileName)
	@echo "===== Ended mcget test======"

mcdel_test:
	@echo "===== Started mcdel test====="
	./mcdel 0
	./mcdel 0 0 0 0 0 0
	./mcdel $(Host) $(Port) $(SecreteKey) $(FileName)
	./mcdel $(Port) $(SecreteKey) $(FileName)
	@echo "===== Ended mcdel test======"

mclist_test:
	@echo "===== Started mclist test====="
	./mclist 0
	./mclist 0 0 0 0 0 0
	./mclist $(Host) $(Port) $(SecreteKey)
	./mclist $(Port) $(SecreteKey)
	@echo "===== Ended mclist test======"




