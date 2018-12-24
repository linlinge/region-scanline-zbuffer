clear
clc
[rate(:,1) rate(:,2)]=textread('../output/time.txt','%f%f');
rate(1,:)=[];
[num2str(sum(rate(:,1))/size(rate,1)) ' (ms)  ' num2str(sum(rate(:,2))/size(rate,1)) 'fps']