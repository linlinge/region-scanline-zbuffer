clear
clc
[x1,y1,x2,y2,x3,y3]=textread('test_in_or_out_of_triangle.txt','%f%f%f%f%f%f');
rst=[];
P=[185 333 ]';
for i=1:length(x1)
A=[x1(i);y1(i)];
B=[x2(i);y2(i)];
C=[x3(i);y3(i)];
rst=[rst is_in(A,B,C,P)];
end
sum(rst)