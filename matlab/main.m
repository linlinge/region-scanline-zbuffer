function main
clear
clc
[x1,y1,x2,y2,x3,y3]=textread('../output/test_in_or_out_of_triangle.txt','%f%f%f%f%f%f');

rst=[];
for i=1:length(x1)
    A=[x1(i) y1(i)]';
    B=[x2(i) y2(i)]';
    C=[x3(i) y3(i)]';
    d=[345 210]';
    rst=[rst is_in(A,B,C,d)];
end

x=[x1(23) x2(23) x3(23) x1(23)]
y=[y1(23) y2(23) y3(23) y1(23)]
plot(x,y,'*')
find(rst==1)


function rst=is_in( A,  B, C, P)
barycentre=(A+B+C)/3;

if up_or_down(A,B,barycentre)==up_or_down(A,B,P)
    temp1=1;
else
    temp1=0;
end

if up_or_down(A,C,barycentre)==up_or_down(A,C,P)
    temp2=1;
else
    temp2=0;
end

if up_or_down(B,C,barycentre)==up_or_down(B,C,P)
    temp3=1;
else
    temp3=0;
end

rst=temp1*temp2*temp3;


function rst=up_or_down(p1,p2,p3)
rst=((p3(2)-p1(2))/(p2(2)-p1(2))-(p3(1)-p1(1))/(p2(1)-p1(1)))*sign(p2(2)-p1(2));
if rst>0
    rst=1;
elseif rst==0
    rst=0;
else
    rst=-1;
end