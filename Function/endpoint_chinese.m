


clear all;
 [x,fs]=audioread('C:\Users\Hi\Desktop\LVTN\GUI_matlab\Audio\s0.wav'); %Read audio
 x=x(:,1);% extract a channel
wlen=960;% set window length
 win=hanning(wlen); %Set Haining window  
 inc=400;% set frame shift
lx=length(x);
 xf=enframe(x,win,inc)';% frame, add Haining window    
 fnx=size(xf,2);% number of frames
tx=(0:lx-1)/fs;                
frametimex=frame2time(fnx,wlen,inc,fs);

for i=1:fnx
    xf1=xf(:,i);
    xe=xf1.*xf1;
    Enx(i)=sum(xe);
end

% Function used
function frameTime=frame2time(frameNum,framelen,inc,fs)
%  Calculate the time corresponding to each frame after framing
frameTime=(((1:frameNum)-1)*inc+framelen/2)/fs;
end