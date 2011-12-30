#WeiboSDK Set the automake options.while execute the automake command, use this option.
AUTOMAKE_OPTIONS=foreign

lib_LTLIBRARIES = libWeiboSDK.la

SOURCEDIR=$(top_srcdir)/src
INCLUDEDIR=$(top_srcdir)/include

cpp_sources = \
	$(SOURCEDIR)/Parsing/ParsingHandle.cxx\
	$(SOURCEDIR)/Parsing/ParsingObject.cxx\
	$(SOURCEDIR)/SDKHelper.cxx\
	$(SOURCEDIR)/SDKManager.cxx\
	$(SOURCEDIR)/SDKMethodImpl.cxx\
	$(top_srcdir)/third-party/common/strconv.cpp\
        $(top_srcdir)/third-party/common/bbiconv.cc\
        $(top_srcdir)/third-party/common/Urlcode.cpp	

INCLUDES = \
	-I.\
	-I/opt/local/include\
	-I$(top_srcdir)/include\
        -I$(top_srcdir)/third-party/common\
	-I$(top_srcdir)/third-party/include\
        -I$(top_srcdir)/third-party/include/libutil

libWeiboSDK_la_SOURCES = $(cpp_sources)

# This is the destnation include directory of install
libWeiboSDKincludedir = $(includedir)

# This is the destnation library directory of install
libdir = $(prefix)/lib/$(PLATFORM_NAME)

libWeiboSDKinclude_HEADERS= \
        $(INCLUDEDIR)/compat.hxx\
        $(INCLUDEDIR)/IWeibo.hxx\
        $(INCLUDEDIR)/IWeiboDef.hxx\
        $(INCLUDEDIR)/IWeiboMethod.hxx\
        $(INCLUDEDIR)/ParsingObject.hxx

AM_CXXFLAGS=-D_LINUX -DONLY_EPOLL -D_SERVER -pthread
