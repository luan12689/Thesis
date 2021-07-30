clear;
clc;
[Y,Fs] = audioread('C:\Users\Hi\Desktop\LVTN\GUI_matlab\Audio\s0.wav'); %doc file am thanh
% do dai cua 1 frame theo giay
fr_du = 0.01;
% do dai cua 1 frame theo sample
fr_le = fr_du * Fs;
% do dai cua file am thanh theo sample
N = length(Y);
% tao ma tran thoi gian cua file am thanh
time = (0:N-1)/Fs;
lap = 0.003;
% do theo sample cua 0.03
Overlap = lap * Fs;
% So giay cua tin hieu = nu_fr*fr_le -0.003*(nu_fr - 1)
% nu_fr = (sample_length - 0.03)/(fr_le - 0.03)
% tim so frame va lay gia tri nguyen
nu_fr = floor((N - lap)/(fr_le - lap));
%tao ma tran cot doc signal
SIGNAL = zeros(N,1);
for h=1:N
if (Y(h) >= 0)
SIGNAL(h) = 1;
else
SIGNAL(h) = -1;
end
end
% tao ma tran cot doc
E = zeros(nu_fr,1); % Nang luongZCR = zeros(nu_fr,1); %
Z = zeros(nu_fr,1); %
ZCR = zeros(nu_fr,1); %


function OutputE = Energy(inputE)
OutputE = sum(abs(inputE).^2);
end

function OutZCR = ZCRsolution2(fr_le,k,DoDai,SIGNAL)
Z2 = 0;
for p = (k-1)*fr_le+1:DoDai+fr_le*(k-1)-1
Z1 = abs(SIGNAL(p)-SIGNAL(p+1));
Z2 = Z1 + Z2;
end
OutZCR = Z2;
end

function Daura = ChuanHoa(Bien)
Daura = Bien/max(abs(Bien));
end

function Inter = TimGiaoDiem(z,e,nu_fr)
TamThoi = zeros(nu_fr,1);
for i=1:nu_fr
if (e(i) - z(i) > 0.005)
TamThoi(i) = 1;
end
end
Inter = TamThoi;
end

function PLOT4 (MATRIX, TIME, z, e, zcr, GiaoDiem, y)
subplot(4,1,1);
plot(MATRIX,z);
title('Zero Crossing Rate');
xlabel('Time (msec)');
subplot(4,1,3);
plot(TIME,y);
title('Signal and Energy');
%xlims = get(gca,'Xlim');
hold on;
plot(MATRIX,e);
%xlim(xlims);
xlabel('Time (msec)');
legend({'Signal','Short-Time Energy'});
hold off;
subplot(4,1,2)
plot(MATRIX,z);
xlabel('Time (msec)');
hold on;
plot(MATRIX,e);
title('Energy + Zero Crossing Rate');
legend({'Short-time ZCR','Short-Time Energy'});
hold off;
subplot(4,1,4);
stem(MATRIX,GiaoDiem);
xlabel('Time (msec)');
end