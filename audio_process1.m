function [] = audio_process1(path)
mp3filename = path
wavFileName = 'output.wav'

signal   = audioread(mp3filename);
info = audioinfo(mp3filename);
Fs = info.SampleRate;
audiowrite(wavFileName, signal, Fs);

[snd,fs] = audioread(wavFileName); % Reads sound file to Xt and sampling freq to fs
% Play sound
player = audioplayer(snd, fs);
play(player);
pause;
stop(player);
%---------------------Representing the audio signal in time domain and frequency domain-------------------------
Xt=snd(:,1);
t=linspace(1,info.Duration,length(Xt));
figure;
plot(t,Xt);
xlabel("Time(s)");
ylabel("Amplitude");
title("Audio signal in time domain");

Xf= abs(fft(Xt));
f= linspace(1,fs,length(Xf));
figure;
plot(f,Xf);
xlabel("Frequency(Hz)");
ylabel("Magnitude");
title("Audio signal in frequency domain");