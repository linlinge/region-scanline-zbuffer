close all
clc
clear
[x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,x5,y5,z5,x6,y6,z6]=textread('1.txt','%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f');

for i=1:100
    tri=[x1(i) y1(i) z1(i);
        x2(i) y2(i) z2(i);
        x3(i) y3(i) z3(i);
        x1(i) y1(i) z1(i)];
    hold on
    plot(tri(:,1),tri(:,2))
end