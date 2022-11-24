#include <stdio.h>
#include <string.h>

#include "genmegadevice/HmDeviceIF.h"


int main (int argc, char *argv[]) {
   int iRet = 0; 
   printf("Hello World!");
   iRet = BCS_Open("/dev/ttyS8",BCS_MOBILEPHONE_DISABLE);
   if(iRet == HM_DEV_OK ){
            printf("\n BCS OPEN SUCCESS: \n");
   } else {
            printf("\n BCS OPEN FAIL(Default: ComPort8): ");
            BCS_Close();
    }
   return 0;
}
