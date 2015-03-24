if PCTx('open')==0
    error('Connection Error!');
end

%% Control
minVal = 100;
maxVal = 600;

val = minVal;

for val =minVal:maxVal
    
    disp(val);
    
    ret = PCTx('send',[val,val,val,val,val,val,val,val,val,val]);
    if ret == -1
        PCTx('close');
        error('Communcation Error')
    end
end

for val =maxVal:-1:minVal
    
    disp(val);
    
    ret = PCTx('send',[val,val,val,val,val,val,val,val,val,val]);
    if ret == -1
        PCTx('close');
        error('Communcation Error')
    end
end

PCTx('close');