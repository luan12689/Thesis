% fid = fopen('dsp_coeffs.c','wt+');
% fprintf(fid, '#include <dsp_coeffs.h>\n');
% fprintf(fid, '#include <math.h>\n\n');
% fprintf(fid, '#define NaNf   NAN\n\n');
% fprintf(fid, 'word_t word_id[WORD_NUM] = {');
% for i = 1:length(word)
%     fprintf(fid, '%s,', word{i,:});
% end
% fprintf(fid, '};\n\n');
% % du lieu hamming
% fprintf(fid, 'const float HamWindow[256] = \n{\n');
% 
% for i = 1:16
%   j = (i-1)*16+1;
%   disp(j);
%   fprintf(fid, '%10ff,', ham(j:j+15));
%   fprintf(fid, '\n');
% end
% fprintf(fid, '};\n\n');

function waitHello
    disp('Waiting...');
    pause(3); %pauses 3 seconds
    disp('Hello World');
    quit;
end
