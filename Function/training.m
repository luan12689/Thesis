function code = training(trainingdir, n)

k = 32;                         % number of centroids required

for i = 1:n                     % train a VQ codebook for each speaker
    file = sprintf('%ss%d.wav', trainingdir, i);           
    %disp(file);
   
    [s, fs] = audioread(file);
    s(s==0)=[];
%     s = pre_emph(s);
%     s=s/max(abs(s)); 
    v = mymfcc(s, fs);            % Compute MFCC's
   
    code{i} = vqlbg(v, k,2);      % Train VQ codebook
end
