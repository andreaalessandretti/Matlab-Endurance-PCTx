
%PCTx.c - MATLAB Interfaces to PCTx Cable Endurance-RC
% 
% Syntax:
%
% - Open connection 
%
% ret = PCTx('open');
%
% ret: 1 for connection established, 0 otherwise
%
% - Send data 
%
% ret = PCTx('send',[valCh1,...,valCh10])
%
% ret: number of bytes sent, -1 in case of error
%
% - Close connection 
%
% PCTx('close');
%
% This is a MEX-file for MATLAB.
%
%
% Compilation command on Mac Os X with R2014b
% mex ./PCTx.c -D__MACOSX_CORE__ LDFLAGS='-bundle -Wl  -exported_symbols_list /Applications/MATLAB_R2014b.app/extern/lib/maci64/mexFunction.map -framework IOKit -framework CoreFoundation'