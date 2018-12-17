function rst=is_in( A,  B, C, P)

v0 = C - A ;
v1 = B - A ;
v2 = P - A ;

dot00 = sum(v0.*v0);
dot01 = sum(v0.*v1);
dot02 = sum(v0.*v2);
dot11 = sum(v1.*v1);
dot12 = sum(v1.*v2);

inverDeno = 1 / (dot00 * dot11 - dot01 * dot01) ;
u = (dot11 * dot02 - dot01 * dot12) * inverDeno ;
if u < 0 || u > 1
   rst=0;
end

v = (dot00 * dot12 - dot01 * dot02) * inverDeno ;
if v < 0 || v > 1 
    rst=0;
end

if u + v <= 1 
    rst=1;
else
    rst=0;
end
    