function []= pitch_shift(AudioFile,n);
[snd,fs] = audioread(AudioFile);
%---------------------Representing the original audio signal---------------
Xt=snd(:,1);
t=1/fs:1/fs:length(Xt)/fs; 
Xf= abs(fft(Xt));
f = linspace(-fs/2, fs/2+1, length(Xt));
figure;
subplot(2,2,1);
plot(t,Xt);
xlabel("Time(s)");
ylabel("Amplitude");
title("Original audio signal in time domain");
subplot(2,2,2);
plot(f,Xf);
xlabel("Frequency(Hz)");
ylabel("Magnitude");
title("Original audio signal in frequency domain");

%-----------------Shifting the pitch of the audio signal-------------------
y=shiftPitch(snd,n);
filename = 'pitched audio.wav';
audiowrite(filename,y,fs);
[Y,fs] = audioread(filename);
sound(Y,fs)

%-----------------Representing the pitched audio signal--------------------
Y=Y(:,1);
Xf= abs(fft(Y));
f = linspace(-fs/2, fs/2+1, length(Y));
subplot(2,2,3);
plot(t,Y);
xlabel("Time(s)");
ylabel("Amplitude");
title("Pitched audio signal in time domain");
subplot(2,2,4);
plot(f,Xf);
xlabel("Frequency(Hz)");
ylabel("Magnitude");
title("Pitched audio signal in frequency domain");

