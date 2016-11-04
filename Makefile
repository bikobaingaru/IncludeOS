#################################################
#          IncludeOS SERVICE makefile           #
#################################################

# The name of your service
SERVICE = IRCd
SERVICE_NAME = IncludeOS IRC Service

# Your service parts
FILES = service.cpp ircd.cpp client.cpp client_new.cpp client_msg.cpp client_cmd.cpp channel.cpp \
				timeout.cpp modes.cpp transform.cpp

# Your disk image
DISK=

# Drivers to be used with service
#EXTRA_LIBS=--whole-archive -lvirtionet --no-whole-archive

# Your own include-path
LOCAL_INCLUDES=

# IncludeOS location
ifndef INCLUDEOS_INSTALL
#INCLUDEOS_INSTALL=$(HOME)/includeos
INCLUDEOS_INSTALL=$(HOME)/IncludeOS_install
endif

# Include the installed seed makefile
#include $(INCLUDEOS_INSTALL)/share/includeos/Makeseed
include /home/gonzo/IncludeOS_install/Makeseed

# Disable crash context buffer
#CPPOPTS += -DDISABLE_CRASH_CONTEXT
