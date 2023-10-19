clc
L1 = Link('d', 0.1, 'a', 0, 'alpha', -pi/2);
L2 = Link('d', 0, 'a', 0.1, 'alpha', 0);
L3 = Link('d', 0, 'a', 0.1, 'alpha', 0);
L4 = Link('d', 0, 'a', 0, 'alpha', 0);
L5 = Link('d', 0, 'a', 0.1, 'alpha', 0);

dh_params = [L1 L2 L3 L4 L5];
% Create a robot model using the DH parameters
robot = SerialLink(dh_params, 'name', 'PEGASUS');

robot.plot([0.000000, -0.722734, 1.445468, 0.847266, 0])
%robot.teach();



x=robot.fkine([0.000000, -0.722734, 1.445468, 0.847266, 0])
j = x.t(1,1)