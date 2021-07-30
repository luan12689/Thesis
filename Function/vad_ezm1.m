function [voiceseg,vsl,SF,NF,amp,zcr]=vad_ezm1(x,wlen,inc,NIS)
x=x(:);% convert x into a column array
maxsilence = 15;% initialization
minlen  = 6;    
status  = 0;
count   = 0;
silence = 0;
 
 y=enframe(x,wlen,inc)';% frame
 fn=size(y,2);% number of frames
 amp=sum(y.^2);% Find the short-term average energy
 zcr=zc2(y,fn);% calculate the short-term average zero-crossing rate
 
%  ampth=mean(amp(1:NIS));% Calculate the average value of the energy and the zero-crossing rate of the initial no-talk interval               
%  zcrth=mean(zcr(1:NIS));
%  amp2=2*ampth; amp1=4*ampth;% set energy and zero crossing rate threshold
%  zcr2=2*zcrth;
 
amp1 = 1;         
amp2 = 0.25;        
zcr2 = 0.5; 

 % Start endpoint detection
xn=1;
for n=1:fn
   switch status
       case {0,1}% 0 = mute, 1 = may start
             if amp(n)> amp1% sure to enter the voice segment
         x1(xn) = max(n-count(xn)-1,1);
         status  = 2;
         silence(xn) = 0;
         count(xn)   = count(xn) + 1;
             elseif amp(n)> amp2 | ...% may be in the voice segment
             zcr(n) > zcr2
         status = 1;
         count(xn)  = count(xn) + 1;
             else% mute state
         status  = 0;
         count(xn)   = 0;
         x1(xn)=0;
         x2(xn)=0;
      end
       case 2,% 2 = speech segment
             if amp(n)> amp2 & ...% stay in the voice segment
         zcr(n) > zcr2
         count(xn) = count(xn) + 1;
         silence(xn) = 0;
             else% Voice will end
         silence(xn) = silence(xn)+1;
                   if silence(xn) <maxsilence% The silence is not long enough, the voice is not over yet
            count(xn)  = count(xn) + 1;
                   elseif count(xn) <minlen% The voice length is too short, it is considered silent or noise
            status  = 0;
            silence(xn) = 0;
            count(xn)   = 0;
                   else% end of speech
            status  = 3;
            x2(xn)=x1(xn)+count(xn);
         end
      end
       case 3,% End of speech, ready for the next speech
        status  = 0;          
        xn=xn+1; 
        count(xn)   = 0;
        silence(xn)=0;
        x1(xn)=0;
        x2(xn)=0;
   end
end 
 
el=length(x1);             
 if x1(el)==0, el=el-1; end% Get the actual length of x1
 if x2(el)==0% If the last value of x2 is 0, set it to fn
    fprintf('Error: Not find endding point!\n');
    x2(el)=fn;
end
SF=zeros(1,fn);% Press x1 and x2 to assign values ??to SF and NF
NF=ones(1,fn);
for i=1 : el
    SF(x1(i):x2(i))=1;
    NF(x1(i):x2(i))=0;
end
speechIndex=find(SF==1);% Calculate voiceseg
voiceseg=findSegment(speechIndex);
vsl=length(voiceseg);

end


function zcr=zc2(y,fn)
if size(y,2)~=fn, y=y'; end
wlen=size(y,1);% set frame length
 zcr=zeros(1,fn);% initialization
 delta=0.01;% set a small threshold
for i=1:fn
         yn=y(:,i);% Take a frame
         for k=1: wlen% center cut processing
        if yn(k)>=delta
            ym(k)=yn(k)-delta;
        elseif yn(k)<-delta
            ym(k)=yn(k)+delta;
        else
            ym(k)=0;
        end
    end
         zcr(i)=sum(ym(1:end-1).*ym(2:end)<0);% Get the processed frame of data to find the zero crossing rate
end
end