[snd,fs] = audioread('power_of_love_original.wav');
player = audioplayer(snd,fs);
play(player);
pause;
stop(player);

%---------------------Representing the original audio signal---------------
Xt=snd(:,1);
t=1/fs:1/fs:length(Xt)/fs; 
Xf= abs(fft(Xt));
f = linspace(-fs/2, fs/2+1, length(Xt));
figure;
subplot(2,1,1);
plot(t,Xt);
xlabel("Time(s)");
ylabel("Amplitude");
title("Original audio signal in time domain");

%-----------------------------Echo-----------------------------------------
new=Xt;
mag=0.8;
for m=1:3
    mag=mag-0.2;
    p= true;
    for n=1:length(t)
        if (p== true) &&  t(n)>=m/1.5 
            p=false;
            r=length(new(n:length(Xt)));
            new(n:length(Xt))=new(n:length(Xt))+(mag*Xt(1:r));
        end
    end
end

%------------------------plotting the graph--------------------------------
subplot(2,1,2);
plot(t,new);
xlabel("Time(s)");
ylabel("Amplitude");
title("Echoed audio signal in time domain");

%------------------------------play the echoed audio file------------------
filename = 'echoed.wav';
audiowrite(filename,new,fs);
[y,fs]= audioread('echoed.wav');
player = audioplayer(y,fs);
play(player);
pause;
stop(player);
