/*
 * PCTx.c - MATLAB Interfaces to PCTx Cable Endurance-RC
 * 
 * Syntax:
 *
 * - Open connection 
 *
 * ret = PCTx('open');
 *
 * ret: 1 for connection enstabilished, 0 otherwise
 *
 * - Send data 
 *
 * ret = PCTx('send',[valCh1,...,valCh10])
 *
 * ret: number of bytes sent, -1 in case of error
 *
 * - Close connection 
 *
 * PCTx('close');
 *
 * This is a MEX-file for MATLAB.
 *
 * Written by Andrea Alessandretti and Jean-Hubert Hours, March '15
 *
 * Compilation command on Mac Os X with R2014b
 * mex ./PCTx.c -D__MACOSX_CORE__ LDFLAGS='-bundle -Wl  -exported_symbols_list /Applications/MATLAB_R2014b.app/extern/lib/maci64/mexFunction.map -framework IOKit -framework CoreFoundation'
 */

#include "mex.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/hid/IOHIDLib.h>

#include "libPCTx.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //Command
    char *command;
    size_t commandLen;
    
    // Output (int)
    mwSize nd = 2;
    mwSize dims[] = { 1, 1 };
    int *ret;
    
    // Validate Command
    if (nrhs == 0 || ! mxIsChar (prhs[0])
    || mxGetNumberOfDimensions (prhs[0]) > 2)
        mexErrMsgTxt ("The first argument should be a string");
    
    //Read command
    commandLen = mxGetN(prhs[0])*sizeof(mxChar)+1;
    command    = mxMalloc(commandLen);
    mxGetString(prhs[0], command, (mwSize)commandLen);
    
    
    if (strcmp(command,"open")==0){
        
        mexPrintf("Open connection\n");
        plhs[0] = mxCreateNumericArray(nd,dims,mxINT32_CLASS,mxREAL);
        ret  =  (int * ) mxGetPr(plhs[0]);
        *ret =  rawhid_open(1,0x0925,0x1299,-1,-1);
        
    }else if (strcmp(command,"close")==0){
        
        mexPrintf("Close Connection\n");
        rawhid_close(0);
        
    }else if(strcmp(command,"send")==0){
        
        //mexPrintf("Send data\n");
        
        double *valuesChannels;
        int i;
        uint8_t buffer[BUFFER_SIZE];
        
        if (nrhs != 2)
            mexErrMsgTxt ("Two");
        if ( !mxIsDouble (prhs[1]))
            mexErrMsgTxt ("Double ");
        if ( mxGetN (prhs[1]) !=10 || mxGetM(prhs[1]) !=1 )
            mexErrMsgTxt ("site ");
        
        if (nrhs != 2 || !mxIsDouble (prhs[1]) || mxGetN (prhs[1]) !=10 || mxGetM(prhs[1]) !=1)
        mexErrMsgTxt ("The second argument should be a vector 1x10 of doubles");
    
        
        /* create a pointer to the real data in the input matrix  */
        valuesChannels = mxGetPr(prhs[1]);
        
        for (i = 0; i < 10; i++)
        {
            buffer[2*i]   = ((int)floor(valuesChannels[i]))%256;
            buffer[2*i+1] = ((int)floor(valuesChannels[i]))/256;
        }
        
        
        plhs[0] = mxCreateNumericArray(nd,dims,mxINT32_CLASS,mxREAL);
        ret =  (int * ) mxGetPr(plhs[0]);
        *ret =  rawhid_send(0, buffer, 20, 100);
    }
    
    mxFree(command);
    
}
