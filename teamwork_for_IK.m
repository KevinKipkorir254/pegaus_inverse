clc
%initializing our robot
clc
L1 = Link('d', 0.04, 'a', 0, 'alpha', -pi/2);
L2 = Link('d', 0, 'a', 0.15, 'alpha', 0);
L3 = Link('d', 0, 'a', 0.12, 'alpha', 0);
L4 = Link('d', 0, 'a', 0, 'alpha', -pi/2);
L5 = Link('d', 0.1, 'a', 0, 'alpha', 0);
dh_params = [L1 L2 L3 L4 L5];
% Create a robot model using the DH parameters
robot = SerialLink(dh_params, 'name', 'PEGASUS');



serialportlist("available")
arduinoObj = serialport("COM4",9600)


%r = 80;
% Generate points for the circle
%phi = 0:1:360;
%xx = r+20 * cosd(phi);
%yy = r * sind(phi);
%zz = zeros(1, 361);

a = 0.1;
r = 40;

t = 0:1:1000;

xx = r * cosd(t) + 80;
yy = r * sind(t);
zz = a*t;




figure(1);
plot3(xx, yy, zz,'b')
xlabel('X');
ylabel('Y');
title('6-Link Robot Arm Drawing a Circle');
axis equal
hold off;

%the Ik is as follows
link_1 = 40;
link_2 = 150;
link_3 = 120;
link_4 = 100;
link_5 = 100;

z=0;
pitch = 0.00001;
yaw = 1.57;

counter = 1;
theta_1 = 0:1:1000;
theta_2 = 0:1:1000;
theta_3 = 0:1:1000;
theta_4 = 0:1:1000;
theta_5 = 0:1:1000;


while(counter < 1001)


	 theta_1_ = atan(yy(counter) / xx(counter));
	 c_1 = cos(theta_1_ );
	 s_1 = sin(theta_1_ );

	%intermediate break
	 b_2 = link_1 - (link_5 * cos(pitch)) - zz(counter);
	 b_1 = c_1 * xx(counter) + s_1 * yy(counter) + link_5 * sin(pitch);

	%claculations for theta 3
	 c_3 = ((b_1 * b_1) + (b_2 * b_2) - (link_2 * link_2) - (link_3 * link_3)) / (2 * link_2 * link_3);
	 theta_3_ = acos(c_3);
	 s_3 = sin(theta_3_);

	%calculations for theta 2
	 c_2 = (((link_2 + link_3 * c_3) * b_1) + ((link_3 * s_3) * b_2)) / ((link_2 * link_2) + (link_3 * link_3) + (2 * link_2 * link_3 * c_3));
	 theta_2_ = -acos(c_2);

	%calculations for theta_4
	theta_4_ = pitch - theta_2_ - theta_3_;

	%calculations for theta_5
	 R_31 = -(cos(yaw) * sin(theta_2_ + theta_3_ + theta_4_));
	 R_32 = (sin(theta_2_ + theta_3_ + theta_4_) * sin(yaw));



   theta_5_ = atan(((R_32) / (-(R_31))));

	%fixing the points
	theta_1(counter) = theta_1_;
	theta_2(counter) = theta_2_;
	theta_3(counter) = theta_3_;
	theta_4(counter) = theta_4_;
	theta_5(counter) = theta_5_;
    fprintf("%f, %f, %f, %f, %f, %f, %f, %f\r\n", xx(counter), yy(counter), z, theta_1_, theta_2_, theta_3_, theta_4_ + 1.57, theta_5_);
    counter = counter + 1;


end

counter_1 = 1;
x_end = 0:1:1000;
y_end = 0:1:1000;
z_end = 0:1:1000;


fprintf("End effector positions\r\n");

while(counter_1<1001)

homogeneous = robot.fkine([ theta_1(counter_1), theta_2(counter_1), theta_3(counter_1), theta_4(counter_1), 0]);
x_end(counter_1) = homogeneous.t(1,1)*1000;
y_end(counter_1) = homogeneous.t(2,1)*1000;
z_end(counter_1) = homogeneous.t(3,1)*1000;
fprintf("%f, %f, %f\r\n", x_end(counter_1),  y_end(counter_1), z_end(counter_1));
counter_1 = counter_1 + 1;
end


figure(2)
plot3(xx, yy, zz,'r')
xlabel('X');
ylabel('Y');
title('6-Link Robot Arm Drawing a Circle');
axis equal
hold off;

fprintf('Length of xx: %d\n', length(xx));
fprintf('Length of yy: %d\n', length(yy));
fprintf('Length of zz: %d\n', length(zz));


figure(5);
axis([-0.5 0.5 -0.5 0.5 -0.2 1]);
hold on
xx = xx/1000;
yy = yy/1000;
zz = zz/1000;

plot3(xx, yy, zz,'r')

counter_1 = 1;

fprintf("animation\r\n");
while(counter_1<1001)


robot.plot([theta_1(counter_1), theta_2(counter_1), theta_3(counter_1), theta_4(counter_1), theta_5(counter_1)])

% Create a struct for joint data
jointData = struct( 'joint_1', rad2deg(theta_1(counter_1)), 'joint_2', rad2deg(theta_2(counter_1)), 'joint_3', rad2deg(theta_3(counter_1)),'joint_4', rad2deg(theta_4(counter_1)));

% Convert the struct to a JSON string
jsonString = jsonencode(jointData)


write(arduinoObj,jsonString,"int8");

fprintf("%f\r\n", counter_1);
pause(1);
counter_1 = counter_1 + 1;
end


