# Matlab-Endurance-PCTx
Matlab interface for the Endurance PCTx cable

## Getting started
1. Download the files in a folder
2. Compile the mex interface in Matlab. If you are using Mac Os Yosemite with Matlab R2014b try
``` matlab
mex ./PCTx.c -D__MACOSX_CORE__ LDFLAGS='-bundle -Wl  -exported_symbols_list /Applications/MATLAB_R2014b.app/extern/lib/maci64/mexFunction.map -framework IOKit -framework CoreFoundation'
```
3. Turn on your RC vehicle
4. Turn on your transmitter
5. Connect the Endurance PCTx cable
6. Hold the trainer switch
7. Run example.m