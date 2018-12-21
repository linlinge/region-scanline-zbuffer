clear
clc
[rate(:,1) rate(:,2)]=textread('../output/time.txt','%f%f');
rate(1,:)=[];
sum(rate(:,1))/size(rate,1) 
sum(rate(:,2))/size(rate,1)