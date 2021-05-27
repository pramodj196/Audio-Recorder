mp3filename = 'high.m4a'
wavFileName = 'output.wav'

signal   = audioread(mp3filename);
info = audioinfo(mp3filename);
Fs = info.SampleRate; 

% sound(signal(:,1),Fs);

N = 8;
Fc = 0.2;

num2 = fir1(N,Fc,'low');
den2 = [1];
fvtool(num2,den2);
subplot(2,1,1);
plot(signal);
FILTER2 = filter(num2,den2,signal(:,1));
subplot(2,1,2);
plot(FILTER2);
sound(FILTER2,Fs);
audiowrite(wavFileName, FILTER2, Fs);