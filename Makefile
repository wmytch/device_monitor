PROJECT_DIR=.
FLATBUFFERS_DIR=$(PROJECT_DIR)/flatbuffers

INC_PATH=-I. -I./include -I$(FLATBUFFERS_DIR)/include -I$(GLOG_DIR)/include -I$(JSON_DIR)/include
LIB_PATH=-L ./lib

LIBS=-lpthread  -levent_core -levent_openssl -levent_pthreads -lcrypto -lssl -lzmq

CPP=g++
CC=g++
CFLAGS=-g
CPPFLAGS=-std=c++11
LDFLAGS=

OBJECTS=client.o easylogging++.o ini.o ServerConfig.o log_client.o 
TARGET=client

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CPP) -o $@ $(CPPFLAGS) $(LIBS) $(INC_PATH) $(OBJECTS)

include $(OBJECTS:.o=.d)

%.o: %.cpp
	$(CPP) -c $(CFLAGS) $(CPPFLAGS) $(INC_PATH) $< -o $@

%.d: %.cpp
	set -e; rm -f $@; \
	$(CPP) -MM $(CFLAGS) $(CPPFLAGS) $(INC_PATH) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY:clean
clean:
	rm -f $(OBJECTS) *.d *.d.*

