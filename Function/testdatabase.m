 function testdatabase(s,fs,datapath)
    
    type = 2;
    x=s; 
    x(x==0)=[];
    x = mymfcc(x,fs);
    load(datapath,'-mat');
    sound_id = size(data_save,1);
    
    
distmin = Inf;
k1 = 0;
      
for i=1:sound_id
  d = disteu(x, data_save{i,1}, type);
  dist = sum(min(d,[],2)) / size(d,1);
  message=strcat('# ',num2str(i), ' "', data_save{i,3}, '" Distance : ',num2str(dist));
  disp(message);
             
  if dist < distmin
    distmin = dist;
    k1 = i;
  end
end
      
%   if distmin < saiso
%     min_index = k1;
%     id = min_index;
%   else
%     id = NaN;
%     msgbox('Khong nhan dang duoc');
%   end
end
