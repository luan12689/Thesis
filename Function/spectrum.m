function [m,fre] = spectrum(s,fs)


m_pho = fft(s);
L = length(s);
m_pho = abs(m_pho/L);
m_pho = m_pho(1:L/2+1);
m_pho(2:end-1) = 2*m_pho(2:end-1);
f = fs*(0:(L/2))/L;

m = m_pho;
fre = f;

end