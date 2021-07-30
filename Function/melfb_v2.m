function s = melfb_v2(p, n, fs)

mel_low  = 0;
mel_high = 2595*log10(1+((fs/2)/700));
mel_points = linspace(mel_low,mel_high,p+2);
hz_points  = 700*((10.^(mel_points/2595))-1);

fbank = zeros(p, floor(n/2)+1);
f = floor((n+1)*hz_points / fs);
f(1) = 1;

for m =2:p+1
    fm_left   = f(m-1);
    fm_center = f(m);
    fm_right  = f(m+1);
   
    for k = fm_left:fm_center
        fbank(m-1,k) = (k - f(m-1))/(f(m) - f(m-1));
    end
    fbank(m-1,fm_center) = 1;
    for k = fm_center:fm_right
        fbank(m-1,k) = (f(m+1) - k)/(f(m+1) - f(m));
    end
end
%s = sparse(fbank);
s = fbank;
end