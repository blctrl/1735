#include "blce1735a.h"
#include "E1735A.h"
#include "stdio.h"

int init1735dll(){
	int status;
	status = Initialize_E1735A_DLL();
	printf("%d\n",status);
	if (status == 0) { 
	printf("The E1735A.dll was initialized successfully\n");
	if((E1735A_ReadDeviceCount() > 0) && E1735A_SelectDevice(0)){
		//E1735A_ResetDevice();
		printf("The e1735a was found and selected successfully\n");
		status = 8;
	E1735A_SetSampleTriggers(TB_SOFTWARE);
	}else{
		printf("The e1735a was not found and selected successfully\n");
	}
	}else printf("Failed to initialize E1735A.dll\n");


    return (status==8)? 0:1;
}

int end1735dll(){
	
	int status;
	status = Finalize_E1735A_DLL();
	 if (status == 0) { 
	printf("The E1735A.dll was ended successfully\n");
	}else printf("Failed to end E1735A.dll\n");
    return (status==0)? 0:1;
	
}    

double readsample(){ 
	double sample;   
	//1735A_ResetDevice();
    bool status;
	//status = E1735A_SetSampleTriggers(TB_SOFTWARE);
	//printf("status %d", status);
	if(1)
		{			
			
			if(sample =  E1735A_ReadSample())
			{ 
				printf("Laser Sample = %f mm\n", sample);
				return sample; 
			}else{
				printf("       Error = %d\n", E1735A_ReadLastError());
				printf("     Trigger = %d\n", E1735A_ReadLastTrigger());	
			}	
		}else{
			printf("     SampleTriggers = %d\n", E1735A_GetSampleTriggers());
		}			
	}    
bool clearPos(){
	printf("Clearing position!\n");
	bool s = E1735A_ResetDevice();
	printf("%d\n",s);
	return s;
}
	