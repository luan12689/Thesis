
function code = train_bin(trainingdir, n)
% trainingdir = 'C:\Users\Hi\Desktop\LVTN\Face_voice_recogition\record_bin\'
k = 32;                         % number of centroids required\
fs = 8000;

for i = 1:10                    % train a VQ codebook for each speaker  
    file = sprintf('%ss%d.bin', trainingdir, i);  
    fileID = fopen(file);
    s = fread(fileID,[4096*2 1],'float');
    fclose(fileID);
    %disp(file);
    s(s==0)=[];
%     s = pre_emph(s);
%     s=s/max(abs(s)); 
    v = mymfcc(s, fs);            % Compute MFCC's
   
    code{i} = vqlbg(v, k,2);      % Train VQ codebook
end
end


    