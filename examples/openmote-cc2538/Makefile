DEFINES+=PROJECT_CONF_H=\"project-conf.h\"

CONTIKI_PROJECT = openmote-demo test-timer test-adxl346 test-max44009 test-sht21

CONTIKI_TARGET_SOURCEFILES += board.c adxl346.c antenna.c
CONTIKI_TARGET_SOURCEFILES += max44009.c sht21.c tps62730.c

all: $(CONTIKI_PROJECT)

CONTIKI = ../..
CONTIKI_WITH_RIME = 1
include $(CONTIKI)/Makefile.include
