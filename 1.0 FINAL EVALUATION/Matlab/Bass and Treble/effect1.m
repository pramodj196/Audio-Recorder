function [] = effect1()
fs = 8000;
noc = 1;
nob = 8;
audio = audiorecorder(fs,nob,noc);
i = 1;
while i==1
record(audio);
i = input('Input i:');
end
stop(audio);
audiodata = getaudiodata(audio);
N = length(audiodata);
ts = 1/fs:1/fs:N/fs;

audiowrite('original2.wav',audiodata,fs);
figure(1);
subplot(3,1,1);
plot(ts,audiodata);
title('Original audio wave');

N = length(audiodata);
for j = 1:1:4
    audiodata(N+j) = 0;
end

BassList = [];
for i = 1:1:N
    BassList(i) = 0.0284064700150113*audiodata(i) + 0.237008213590703*audiodata(i+1) + 0.469170632788571*audiodata(i+2) + 0.237008213590703*audiodata(i+3) + 0.0284064700150113*audiodata(i+4);
end
sound(BassList,fs);
audiowrite('Bass2.wav',BassList,fs);
subplot(3,1,2);
plot(BassList);
title('Audio with Bass feature');

TrebleList = [];
for i = 1:1:N
    TrebleList(i) = -0.0123835577654347*audiodata(i) + -0.103321704609266*audiodata(i+1) + 0.818123706312338*audiodata(i+2) + -0.103321704609266*audiodata(i+3) + -0.0123835577654347*audiodata(i+4);
end
sound(TrebleList,fs);
audiowrite('Treble2.wav',TrebleList,fs);
subplot(3,1,3);
plot(TrebleList);
title('Audio with Treble Feature');

Fn = fs/2;
Fv = linspace(0, 1, fix(N/2)+1)*Fn;                
Iv = 1:length(Fv);

FT_original = fft(audiodata)/N;                             
figure(2);
subplot(3,1,1);
plot(Fv, abs(FT_original(Iv))*2)
grid

FT_Bass = fft(BassList)/N;                             
subplot(3,1,2);
plot(Fv, abs(FT_Bass(Iv))*2)
grid

FT_Treble = fft(TrebleList)/N;                             
subplot(3,1,3);
plot(Fv, abs(FT_Treble(Iv))*2)
grid