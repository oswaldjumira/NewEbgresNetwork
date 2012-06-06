#
# OMNeT++/OMNEST Makefile for NewEbgresNetwork
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I../MiXiM/base/modules -I../MiXiM/base/utils -L../MiXiM/out/$(CONFIGNAME)/tests/testUtils -L../MiXiM/out/$(CONFIGNAME)/base -L../MiXiM/out/$(CONFIGNAME)/modules -lmiximtestUtils -lmiximbase -lmiximmodules -KMIXIM_PROJ=../MiXiM
#

# Name of target to be created (-o option)
TARGET = NewEbgresNetwork$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../MiXiM/base/modules \
    -I../MiXiM/base/utils \
    -I. \
    -IDocumentation \
    -ILogFiles \
    -IScripts \
    -Iconfiguration \
    -Ihost \
    -Inetwork_interface_card \
    -Iperformance \
    -Iphysical_layer \
    -Iresults \
    -Iutilities

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../MiXiM/out/$(CONFIGNAME)/tests/testUtils -L../MiXiM/out/$(CONFIGNAME)/base -L../MiXiM/out/$(CONFIGNAME)/modules  -lmiximtestUtils -lmiximbase -lmiximmodules
LIBS += -Wl,-rpath,`abspath ../MiXiM/out/$(CONFIGNAME)/tests/testUtils` -Wl,-rpath,`abspath ../MiXiM/out/$(CONFIGNAME)/base` -Wl,-rpath,`abspath ../MiXiM/out/$(CONFIGNAME)/modules`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/ebgresApplLayer.o \
    $O/NewEbgresNetwLayer.o \
    $O/EbgresRouter.o \
    $O/configuration/Configuration.o \
    $O/host/NodeInformation.o \
    $O/performance/Item.o \
    $O/performance/Performance.o \
    $O/performance/ItemVector.o \
    $O/performance/CommunicationLinkVector.o \
    $O/performance/RouteVector.o \
    $O/performance/Node.o \
    $O/performance/Queue.o \
    $O/performance/NodeData.o \
    $O/performance/CommunicationLink.o \
    $O/physical_layer/EbgresPhysicalLayer.o \
    $O/EbgresApplLayerMessage_m.o \
    $O/EbgresNetwMessage_m.o

# Message files
MSGFILES = \
    EbgresApplLayerMessage.msg \
    EbgresNetwMessage.msg

# Other makefile variables (-K)
MIXIM_PROJ=../MiXiM

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f NewEbgresNetwork NewEbgresNetwork.exe libNewEbgresNetwork.so libNewEbgresNetwork.a libNewEbgresNetwork.dll libNewEbgresNetwork.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f Documentation/*_m.cc Documentation/*_m.h
	-rm -f LogFiles/*_m.cc LogFiles/*_m.h
	-rm -f Scripts/*_m.cc Scripts/*_m.h
	-rm -f configuration/*_m.cc configuration/*_m.h
	-rm -f host/*_m.cc host/*_m.h
	-rm -f network_interface_card/*_m.cc network_interface_card/*_m.h
	-rm -f performance/*_m.cc performance/*_m.h
	-rm -f physical_layer/*_m.cc physical_layer/*_m.h
	-rm -f results/*_m.cc results/*_m.h
	-rm -f utilities/*_m.cc utilities/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc Documentation/*.cc LogFiles/*.cc Scripts/*.cc configuration/*.cc host/*.cc network_interface_card/*.cc performance/*.cc physical_layer/*.cc results/*.cc utilities/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/EbgresRouter.o: EbgresRouter.cc \
	EbgresRouter.h
$O/ebgresApplLayer.o: ebgresApplLayer.cc \
	$(MIXIM_PROJ)/base/utils/ImNotifiable.h \
	EbgresRouter.h \
	$(MIXIM_PROJ)/base/modules/Blackboard.h \
	configuration/Configuration.h \
	$(MIXIM_PROJ)/base/modules/BaseUtility.h \
	NewEbgresNetwLayer.h \
	EbgresApplLayerMessage_m.h \
	ebgresApplLayer.h \
	host/NodeInformation.h \
	EbgresNetwMessage_m.h
$O/EbgresApplLayerMessage_m.o: EbgresApplLayerMessage_m.cc \
	EbgresApplLayerMessage_m.h
$O/NewEbgresNetwLayer.o: NewEbgresNetwLayer.cc \
	$(MIXIM_PROJ)/base/utils/ImNotifiable.h \
	EbgresRouter.h \
	$(MIXIM_PROJ)/base/modules/Blackboard.h \
	$(MIXIM_PROJ)/base/modules/BaseUtility.h \
	configuration/Configuration.h \
	NewEbgresNetwLayer.h \
	EbgresApplLayerMessage_m.h \
	host/NodeInformation.h \
	EbgresNetwMessage_m.h
$O/EbgresNetwMessage_m.o: EbgresNetwMessage_m.cc \
	EbgresNetwMessage_m.h
$O/configuration/Configuration.o: configuration/Configuration.cc \
	EbgresRouter.h \
	$(MIXIM_PROJ)/base/utils/ImNotifiable.h \
	$(MIXIM_PROJ)/base/modules/Blackboard.h \
	$(MIXIM_PROJ)/base/modules/BaseUtility.h \
	NewEbgresNetwLayer.h \
	configuration/Configuration.h \
	EbgresApplLayerMessage_m.h \
	host/NodeInformation.h \
	EbgresNetwMessage_m.h
$O/host/NodeInformation.o: host/NodeInformation.cc \
	$(MIXIM_PROJ)/base/utils/ImNotifiable.h \
	EbgresRouter.h \
	$(MIXIM_PROJ)/base/modules/Blackboard.h \
	$(MIXIM_PROJ)/base/modules/BaseUtility.h \
	NewEbgresNetwLayer.h \
	configuration/Configuration.h \
	EbgresApplLayerMessage_m.h \
	host/NodeInformation.h \
	EbgresNetwMessage_m.h
$O/performance/Performance.o: performance/Performance.cc \
	performance/RoutingInformation.h \
	performance/Information.h \
	performance/Queue.h \
	performance/CommunicationLinkVector.h \
	performance/Router.h \
	performance/Performance.h \
	performance/NodeData.h \
	performance/GraphFileCreator.h \
	performance/Item.h \
	performance/DataFileCreator.h \
	performance/SystemController.h \
	performance/Route.h \
	performance/LinkedList.h \
	performance/LinkBreak.h \
	performance/Node.h \
	EbgresNetwMessage_m.h \
	performance/NetworkLayerInformation.h
$O/performance/CommunicationLinkVector.o: performance/CommunicationLinkVector.cc
$O/performance/Queue.o: performance/Queue.cc \
	performance/Item.h \
	performance/Queue.h
$O/performance/Performance_n.o: performance/Performance_n.cc
$O/performance/RouteVector.o: performance/RouteVector.cc
$O/performance/NodeData.o: performance/NodeData.cc
$O/performance/Node.o: performance/Node.cc \
	performance/Item.h \
	performance/RoutingInformation.h \
	performance/Information.h \
	performance/Queue.h \
	performance/Router.h \
	performance/Node.h \
	performance/NodeData.h \
	performance/NetworkLayerInformation.h
$O/performance/Item.o: performance/Item.cc \
	performance/Item.h
$O/performance/ItemVector.o: performance/ItemVector.cc \
	performance/ItemVector.h
$O/performance/CommunicationLink.o: performance/CommunicationLink.cc \
	performance/CommunicationLink.h
$O/physical_layer/EbgresPhysicalLayer.o: physical_layer/EbgresPhysicalLayer.cc \
	physical_layer/EbgresPhysicalLayer.h

