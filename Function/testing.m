function testing(testingdir, n, code)

for k = 1:n                     % read test sound file of each speaker
    file = sprintf('%ss%d.wav', testingdir, k);
    [s, fs] = audioread(file);      
        
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
