%  function save2database(s,fs,centroid,speaker_id,row,name)
 
% load("database.dat","-mat");
% load ('code_luan.mat');

row = 2;
word_id = 1;
centroid =32;
name = ["KHONG";"MOT";"HAI";"BA";"BON";"NAM";"SAU";"BAY";"TAM";"CHIN";
    "KHONG";"MOT";"HAI";"BA";"BON";"NAM";"SAU";"BAY";"TAM";"CHIN"];

% s(s==0)=[];
 
% mfcc = mymfcc(s,fs);
% code = vqlbg(mfcc, k,2);
for x=1:length(code)
%     data_save{(x+10),1} = code{x};
%     data_save{(x+10),2} = x;
%     data_save{(x+10),3} = name((x+10));
    
    data_save{(x),1} = code{x};
    data_save{(x),2} = x;
    data_save{(x),3} = name((x));
end

save('database.dat','data_save','centroid','code','-append');
%run('database2cfile.m');

%  end