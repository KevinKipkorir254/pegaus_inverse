clc

a = 0.1;
r = 40;

t = 0:1:1000;


xx = r * cosd(t) + 80;
yy = r * sind(t);
zz = a*t;


plot3(xx, yy, zz,'r')