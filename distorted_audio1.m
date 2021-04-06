function [] = distorted_audio1(path)
[snd,fs] = audioread(path);
A = [0.5 0.6 0.7 0.8 0.9 2 3 4];
random = randi(length(A));
index = A(random);
player = audioplayer(snd,index*fs);
play(player);
pause;
stop(player);

%-----------Writing the output to the output.wav file----------------------
filename = 'output.wav';
audiowrite(filename,snd,fs*index);
[y,Fs] = audioread(filename);

%--------Representing the original signal in time and frequency domains----
Xt_1=snd(:,1);
t_1=1/fs:1/fs:length(Xt_1)/fs; 
Xf_1= abs(fft(Xt_1));
f_1= linspace(-fs/2, fs/2+1, length(Xt_1));
figure;
subplot(2,2,1);
plot(t_1,Xt_1);
xlabel("Time(s)");
ylabel("Amplitude");
title("Audio signal in time domain");
subplot(2,2,2);
plot(f_1,Xf_1);
xlabel("Frequency(Hz)");
ylabel("Magnitude");
title("Audio signal in frequency domain");

%---------Representing the output signal in time and frequency domains-----
Xt_2=y(:,1);
t_2=1/Fs:1/Fs:length(Xt_2)/Fs;
Xf_2= abs(fft(Xt_2));
f_2= linspace(-Fs/2, Fs/2+1, length(Xf_2));
subplot(2,2,3);
plot(t_2,Xt_2);
xlabel("Time(s)");
ylabel("Amplitude");
title("Output audio signal in time domain");
subplot(2,2,4);
plot(f_2,Xf_2);
xlabel("Frequency(Hz)");
ylabel("Magnitude");
title("Output audio signal in frequency domain");
