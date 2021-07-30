%%addpath(genpath('sap-voicebox-master/voicebox'))
clear all; close all;
[x,Fs]=audioread('C:\Users\Hi\Desktop\LVTN\GUI_matlab\Audio\s9.wav');
x = x / max(abs(x)); 
FrameLen = 256;      
inc = 90;           
amp1 = 10;         
amp2 = 2;      
zcr1 = 10;          
zcr2 = 5; 
minsilence = 6; 
minlen  = 15;    
status  = 0;     
count   = 0;     
silence = 0;     
tmp1  = enframe(x(1:end-1), FrameLen,inc);
tmp2  = enframe(x(2:end)  , FrameLen,inc);
signs = (tmp1.*tmp2)<0;
diffs = (tmp1 -tmp2)>0.02;
zcr   = sum(signs.*diffs,2); 
amp = sum((abs(enframe(filter([1 -0.9375], 1, x), FrameLen, inc))).^2, 2);
amp1 = min(amp1, max(amp)/4);
amp2 = min(amp2, max(amp)/8);
 
for n=1:length(zcr)
   goto = 0;
   switch status
   case {0,1}                   
      if amp(n) > amp1          
         x1 = max(n-count-1,1); 
         status  = 2;
         silence = 0;
         count   = count + 1;
      elseif amp(n) > amp2 || zcr(n) > zcr2 
         status = 1;
         count  = count + 1;
      else                    
         status  = 0;
         count   = 0;
      end
   case 2,                       
      if amp(n) > amp2 ||zcr(n) > zcr2     
         
         count = count + 1;
      else                       
         silence = silence+1;
         if silence < minsilence 
            count  = count + 1;
         elseif count < minlen   
            status  = 0;
            silence = 0;
            count   = 0;
         else                    
            status  = 3;
         end
      end
   case 3,
      break;
   end
end   
 
count = count-silence/2;
x2 = x1 + count -1;          
 
subplot(3,1,1)
plot(x)
axis([1 length(x) -1 1])
xlabel('number of frames'); ylabel('Speech');
line([x1*inc x1*inc], [-1 1], 'Color', 'red');
line([x2*inc x2*inc], [-1 1], 'Color', 'red');
 
subplot(3,1,2)
plot(amp);
axis([1 length(amp) 0 max(amp)])
xlabel('number of frames'); ylabel('Energy');
line([x1 x1], [min(amp),max(amp)], 'Color', 'red');
line([x2 x2], [min(amp),max(amp)], 'Color', 'red');
 
subplot(3,1,3)
plot(zcr);
axis([1 length(zcr) 0 max(zcr)])
xlabel('number of frames'); ylabel('ZCR');
line([x1 x1], [min(zcr),max(zcr)], 'Color', 'red');
line([x2 x2], [min(zcr),max(zcr)], 'Color', 'red');
