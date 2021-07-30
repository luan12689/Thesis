% clear all; close all;
trainingdir = 'C:\Users\Hi\Desktop\LVTN\Face_voice_recogition\record_bin\'

for i = 1:10                    
    file = sprintf('%ss%d.bin', trainingdir, i);  
    fileID = fopen(file);
%     s = fread(fileID,[hex2dec('f80') 1],'float');
    s = fread(fileID,[4096*2 1],'float');
    fclose(fileID);

    s1{i}=s/abs(max(s));
    
end

 for k = 1:10
    subplot(5,2,k);
    plot(s1{k},'k');
    title_speech=sprintf('s%d',k);
    title(title_speech);
  end 
