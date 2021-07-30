clc
clear all

load('database.dat','-mat');
ham = hamming(256);
mel = melfb_v2(20, 256, 8000);
word = (data_save(:,3));
% enum = unique(word_id, 'stable');

%% FILE .H
fid = fopen('dsp_coeffs.h','wt+');
fprintf(fid, '#ifndef __DSP_COEFFS_H\n');
fprintf(fid, '#define __DSP_COEFFS_H\n\n');
fprintf(fid, '#define WORD_NUM %d\n', length(data_save));
fprintf(fid, '#define CENTROID %d\n', centroid);
fprintf(fid, '#define MELFB_NUM %d\n\n', 20);
fprintf(fid, 'typedef enum\n{\n');
fprintf(fid, 'UNKNOWN = 0,\n');
fprintf(fid, '%s,\n',word{:,1} ); % day la ten cac word
fprintf(fid, '}word_t;\n\n');
fprintf(fid, '#endif // __DSP_COEFFS_H\n\n');
fclose(fid);

%% FILE .C
%% Header
fid = fopen('dsp_coeffs.c','wt+');
fprintf(fid, '#include <dsp_coeffs.h>\n');
fprintf(fid, '#include <math.h>\n\n');
fprintf(fid, '#define NaNf   NAN\n\n');
fprintf(fid, 'word_t word_id[WORD_NUM] = {');
for i = 1:length(word)
    fprintf(fid, '%s,', word{i,:});
end
fprintf(fid, '};\n\n');
fprintf (fid,'const char word_string[][10] = {"UNKNOW","KHONG","MOT","HAI","BA","BON","NAM","SAU","BAY","TAM","CHIN",}; \n\n')

%% Hamming
% du lieu hamming
fprintf(fid, 'const float HamWindow[256] = \n{\n');
for i = 1:16
  j = (i-1)*16+1;
  fprintf(fid, '%10ff,', ham(j:j+15));
  fprintf(fid, '\n');
end
fprintf(fid, '};\n\n');
%% Mel
% du lieu cua so mel
fprintf(fid, 'const float MelFb[MELFB_NUM*129] = \n{\n');
for i = 1:20
  fprintf(fid, '%10ff,', mel(i,:));
  fprintf(fid, '\n');
end
fprintf(fid, '};\n\n');
%% Voice
% du lieu giong noi
fprintf(fid, 'const float Word[WORD_NUM][MELFB_NUM*CENTROID] = {\n');
for i = 1:length(data_save)
  fprintf(fid, '{ /* %s */\n', data_save{i,3});
  for j = 1:20
    fprintf(fid, '%10ff,', data_save{i,1}(j,:));
    fprintf(fid, '\n');
  end
  fprintf(fid, '},\n');
end
fprintf(fid, '};\n\n');
fclose(fid);