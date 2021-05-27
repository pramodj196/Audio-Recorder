mp3filename = 'Faded.m4a'
wavFileName = 'output1.wav'

signal   = audioread(mp3filename);
info = audioinfo(mp3filename);
Fs = info.SampleRate; 

sound(signal(:,1),Fs)

N = 8;
Fc = 0.2;

num1 = fir1(N,Fc,'high');
den1 = [1];
fvtool(num1,den1);
subplot(2,1,1);
plot(signal);
FILTER1 = filter(num1,den1,signal(:,1));
subplot(2,1,2);
plot(FILTER1);
% sound(FILTER1,Fs);
audiowrite(wavFileName, FILTER1, Fs);