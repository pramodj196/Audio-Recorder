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