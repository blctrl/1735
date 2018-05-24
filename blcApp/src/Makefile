TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = blc
# blc.dbd will be created and installed
DBD += blc.dbd

# blc.dbd will be made up from these files:
blc_DBD += base.dbd
blc_DBD += asyn.dbd
blc_DBD += blc1735Support.dbd

# Include dbd files from all support applications:
#blc_DBD += xxx.dbd

blc_SRCS += blc1735.cpp
blc_SRCS += blce1735a.cpp
INC += E1735A.h
INC += blce1735a.h

# Add all the support libraries needed by this IOC
#blc_LIBS += xxx
blc_LIBS += asyn
# blc_registerRecordDeviceDriver.cpp derives from blc.dbd
blc_SRCS += blc_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
blc_SRCS_DEFAULT += blcMain.cpp
blc_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#blc_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
blc_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

