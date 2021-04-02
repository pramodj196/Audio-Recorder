function [] = distorted_audio1(path)
[snd,fs] = audioread(path);
A = [0.5 0.6 0.7 0.8 0.9 2 3 4];
random = randi(length(A));
index = A(random);
player = audioplayer(snd,index*fs);
play(player);
pause;
stop(player);