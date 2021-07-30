% clear all
% 
% if ~isempty(instrfind)
%      fclose(instrfind);
%      delete(instrfind);
% end
% 
% s = serial('COM8'); %#ok<SERIAL>
% s.Timeout=10;	
% s.BaudRate = 115200;
% s.InputBufferSize=38400;
% 
% %
% fopen(s);
%   
% veri=fscanf(s,"uint8",1000);
% veri=double(veri);
% fclose(s);

%%%%%% 172*144 resim %%%%%%%%%%%%%%
resim1=[];
veri;
resim1(:,:,1)=[0.5 0.2 0.3;0.2 0.7 0.9;0.5 0.5 0.5];
resim1(:,:,2)=[0.0 0.0 0.0;0.0 0.0 0.0;0.0 0.0 0.0];        
resim1(:,:,3)=[0.9 0.2 0.2;0.2 0.7 0.1;0.5 0.5 0.2];
i=1;
for stun=1:120
for genislik=1:160

RGB=bitor(bitshift(fi(uint16(veri(i))),8),fi(uint16(veri(i+1))));

R=double(bitshift(RGB,-11))/31;
G=double(bitand(bitshift(RGB,-5),uint16(63)))/63;
B=double(bitand(RGB,uint16(31)))/31;


resim1(genislik,stun,1)=R;%stun satýr RGB
resim1(genislik,stun,2)=G;
resim1(genislik,stun,3)=B;
i=i+2
end
end
image(resim1)
resim2=[];
veri;
resim2(:,:,1)=[0.5 0.2 0.3;0.2 0.7 0.9;0.5 0.5 0.5];
resim2(:,:,2)=[0.0 0.0 0.0;0.0 0.0 0.0;0.0 0.0 0.0];        
resim2(:,:,3)=[0.9 0.2 0.2;0.2 0.7 0.1;0.5 0.5 0.2];
i=1;
for stun=1:144
for genislik=1:172

RGB=bitor(bitshift(fi(uint16(veri2(i+1))),8),fi(uint16(veri2(i))));

R=double(bitshift(RGB,-11))/32;
G=double(bitand(bitshift(RGB,-5),uint16(63)))/64;
B=double(bitand(RGB,uint16(31)))/32;


resim2(stun,genislik,1)=R;%stun satýr RGB
resim2(stun,genislik,2)=G;
resim2(stun,genislik,3)=B;
i=i+2
end
end
