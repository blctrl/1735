#!../../bin/win32-x86/blc

## You may have to change blc to something else
## everywhere it appears in this file

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/blc.dbd"
blc_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=Administrator")
dbLoadRecords("db/blc1735.db")
dbLoadRecords("db/autotest.db","P=Autotest:")

blc1735Config("blc1735",1)

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=Administrator"
