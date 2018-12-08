mpera : my-redis.o segment.o algorithms.o test_segment.o mem.o key-pair.o
	g++ -g -o mpera my-redis.o segment.o algorithms.o test_segment.o mem.o key-pair.o

test_segment.o : test_segment.cc
	g++ -g -c -o test_segment.o test_segment.cc

my-redis.o : my-redis.cc
	g++ -g -c -o my-redis.o my-redis.cc

segment.o : segment.cc
	g++ -g -c -o segment.o segment.cc

algorithms.o : algorithms.cc
	g++ -g -c -o algorithms.o algorithms.cc

mem.o : mem.cc
	g++ -g -c -o mem.o mem.cc

key-pair.o : key-pair.cc
	g++ -g -c -o key-pair.o key-pair.cc


clean : 
	rm *.o mpera
