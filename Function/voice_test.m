clear all
clc
close all

addpath('MY FUNCTIONS');
load('my_database.dat','-mat');

%% Intilize paramters %%
fs = 8000;
sound_id=length(data_save);

%% Read binary file %%
fileID = fopen('data_record.bin');
%rec_data = fread(fileID,[4096*4 1],'float');
rec_data = fread(fileID,[hex2dec('f80') 1],'float');
fclose(fileID);

%nor_data = rec_data/abs(max(rec_data));
preem_data = filter([1 -0.9375], 1, rec_data);
%tach_data = endcut(preem_data, 16, 0.00005, 0.06);
mfcc_data = mymfcc(rec_data, fs);
% speech_id = nhandang(mfcc_data, 30, fs, 2);
% [en_upper en_lower] = envelope(rec_data, 50, 'peak');
% mfcc_sample = mfcc(data_save{speech_id,5},8000);

%% Phat lai tin hieu da xu ly %%
data_play = audioplayer(rec_data,fs);
play(data_play);
while (isplaying(data_play))
  disp('Tin hieu sau khi tach');
  pause(0.5);
end
disp(['-->TU TRUNG KHOP: "', data_save{speech_id,3}, '"']);
%% ve bieu do %%
subplot(2,1,1)
plot(rec_data);
title('Tin hieu tu bo nho vdk');
grid on
subplot(2,1,2)
plot(en_upper);
title('Duong bao tin hieu');
grid on

figure
subplot(2,1,1)
ve_pho(rec_data, fs)
title('Truoc pre-emphasis');
subplot(2,1,2)
ve_pho(preem_data, fs)
title('Sau pre-emphasis');

figure
subplot(2,1,1)
plot(mfcc_data)
title('TIN HIEU THU AM');
subplot(2,1,2)
plot(mfcc_sample)
title('TIN HIEU MAU');