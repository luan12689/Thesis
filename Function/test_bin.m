function test_bin (testingdir,n,code)

fs = 8000;
for k = 1:n                     % read test sound file of each speaker
    
    file = sprintf('%ss%d.bin', testingdir, k);  
    fileID = fopen(file);
    s = fread(fileID,[hex2dec('f80') 1],'float');
    fclose(fileID);
        
    v = mymfcc(s, fs);            % Compute MFCC's
   
    distmin = inf;
    k1 = 0;
   
    for l = 1:length(code)      % each trained codebook, compute distortion
        d = disteu(v, code{l},2); 
        dist = sum(min(d,[],2)) / size(d,1);
      
        if dist < distmin
            distmin = dist;
            k1 = l;
        end      
    end
   
    msg = sprintf('Speaker %d matches with speaker %d', k, k1);
    disp(msg);
end

end