
#include "blce1735a.h"
#include <iocsh.h>
#include <asynPortDriver.h>

//#include <iostream>

#include <epicsExport.h>

static const char *driverName = "blc1735";

// asyn
#define readPosParamString      "readPos"
#define connectStatusParamString	"connectStatus"
#define clearPosParamString		"clearPos"

#define NUM_Params  1   // Number of analog outputs on 1608G
#define MAX_SIGNALS     NUM_Params

/** Class definition for the blc1735 class
  */
class blc1735 : public asynPortDriver {
public:
  blc1735(const char *portName, int numOf1735);

  /* These are the methods that we override from asynPortDriver */
  //virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
  //virtual asynStatus getBounds(asynUser *pasynUser, epicsInt32 *low, epicsInt32 *high);
  virtual asynStatus readFloat64(asynUser *pasynUser, epicsFloat64 *value);

protected:
  // asyn 
  int readPos_;
  int connectStatus_;
  int clearPos_;
  #define FIRST_blc1735_PARAM  readPos_
  #define LAST_blc1735_PARAM   clearPos_

private:
  int numOf1735_;
};

#define NUM_PARAMS ((int)(&LAST_blc1735_PARAM - &FIRST_blc1735_PARAM + 1))

/** Constructor for the blc1735 class
  */
blc1735::blc1735(const char *portName, int numOf1735)
  : asynPortDriver(portName, MAX_SIGNALS, NUM_PARAMS, 
      asynFloat64Mask | asynOctetMask | asynDrvUserMask,  // Interfaces that we implement
      0,                                // Interfaces that do callbacks
      ASYN_CANBLOCK, 1, /* ASYN_CANBLOCK=1, ASYN_MULTIDEVICE=1, autoConnect=1 */
      0, 0),  /* Default priority and stack size */
    numOf1735_(numOf1735)
{
	//init 1735 dll
  int connect = init1735dll();
  // readPos parameter
  createParam(readPosParamString,            asynParamFloat64, &readPos_);
  createParam(connectStatusParamString,      asynParamOctet, &connectStatus_);
  createParam(clearPosParamString,            asynParamFloat64, &clearPos_);
  setStringParam(0,connectStatus_,"disconnected");
  if(connect == 0) setStringParam(0,connectStatus_,"Connected");
  setDoubleParam(0,readPos_, 222);
  setDoubleParam(0,clearPos_, 0);
}


asynStatus blc1735::readFloat64(asynUser *pasynUser, epicsFloat64 *value)
{
  int addr;
  int function = pasynUser->reason;
  int status=0;
  double pos;

  static const char *functionName = "readFloat64";

  this->getAddress(pasynUser, &addr);

  printf("process\n");
  
  if (function == readPos_) {
    getDoubleParam(0,readPos_, &pos);
	printf("%f\n",pos);
	
	if(1){
//ADD CODE here
	 pos = readsample(); 
//add new code above	
	}else{

	}
	
   // pos = 1001;
    *value = pos;
    setDoubleParam(0,readPos_, *value);
	printf("%f\n",pos);
	}else {
	 if(function == clearPos_) clearPos();
		
     status = asynPortDriver::readFloat64(pasynUser, value);
	} 
  callParamCallbacks(addr);
  return (status==0) ? asynSuccess : asynError;
}
	



/** 配置命令 */
extern "C" int blc1735Config(const char *portName, int numOf1735)
{
  blc1735 *pblc1735 = new blc1735(portName, numOf1735);
  pblc1735 = NULL;  /* This is just to avoid compiler warnings */
  return(asynSuccess);
}


static const iocshArg configArg0 = { "Port name",      iocshArgString};
static const iocshArg configArg1 = { "1735 number",      iocshArgInt};
static const iocshArg * const configArgs[] = {&configArg0,
                                              &configArg1};
static const iocshFuncDef configFuncDef = {"blc1735Config", 2, configArgs};
static void configCallFunc(const iocshArgBuf *args)
{
  blc1735Config(args[0].sval, args[1].ival);
}

void drvblc1735Register(void)
{
  iocshRegister(&configFuncDef,configCallFunc);
}

extern "C" {
epicsExportRegistrar(drvblc1735Register);
}
