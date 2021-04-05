function [] = record_audio1()
fs = 44100;
noc = 2;
nob = 16;
audio = audiorecorder(fs,nob,noc);
i = 1;
while i==1
record(audio);
i = input('Input i:');
end
stop(audio);
audiodata = getaudiodata(audio);
sound(audiodata(:,1),fs);
audiowrite('sample1.wav',audiodata,fs);