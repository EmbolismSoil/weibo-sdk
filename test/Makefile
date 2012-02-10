BIN = test
top_srcdir = ..
CXXFLAGS= -g -O2 -Wall
CC = g++

LIB_NAME = 
PLATFORM_KEY = $(shell uname)

ifeq ($(shell uname),Darwin)
	LIB_NAME=dylib
else
	LIB_NAME=a
endif

# DEFS = -D_USE_JSON_PARSER
LIBS = \
       $(top_srcdir)/../weibo-sdk-util/lib/$(PLATFORM_KEY)/libcppunit.a\
       $(top_srcdir)/lib/$(PLATFORM_KEY)/libWeiboSDK.$(LIB_NAME)\
       $(top_srcdir)/../weibo-sdk-util/lib/$(PLATFORM_KEY)/libHttpEngine.$(LIB_NAME)\
       $(top_srcdir)/../weibo-sdk-util/lib/$(PLATFORM_KEY)/libutil.$(LIB_NAME)\
       $(top_srcdir)/../weibo-sdk-util/lib/$(PLATFORM_KEY)/libjson.$(LIB_NAME)\
       -lcurl -lpthread -lssl

INCLUDES = \
	-I. \
	-I/opt/local/include \
        -I$(top_srcdir)/third-party/include/libutil \
	-I$(top_srcdir)/third-party/common \
	-I$(top_srcdir)/third-party/include \
	-I$(top_srcdir)/include

SRCS = \
        ParsingDataStruct.cpp\
	UNITTestIDBuilderPolicy.cpp\
	WeiboTestCase.cpp\
	WeiboUnitTest.cpp\
	WeiboUnitTestHelper.cpp

OBJS=$(patsubst %.cpp, %.o, $(SRCS))

.cpp.o :
	$(CC) $(CXXFLAGS) $(DEFS) $(INCLUDES) -c -o $@ $<

$(BIN) : $(OBJS) Makefile 
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJS) $(LIBS)

clean :
	-rm -f $(BIN) $(OBJS)
