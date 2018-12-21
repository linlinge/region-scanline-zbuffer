[id,x1,y1,z1,x2,y2,z2,x3,y3,z3]=textread('../output/all_triangles.txt','%f%f%f%f%f%f%f%f%f%f');
i=17978;
i=i+1;
tri=[x1(i) y1(i);
    x2(i) y2(i);
    x3(i) y3(i);];
tri=[tri;tri(1,:)];
plot(tri(:,1),tri(:,2));