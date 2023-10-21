%communication with arduino
clc


theta_1 = 10;
theta_2 = 20;
theta_3 = 30;
theta_4 = 40;
theta_5 = 50;


% Create a struct for joint data
jointData = struct( 'joint_1', theta_1, 'joint_2', theta_2, 'joint_3', theta_3,'joint_4', theta_4);

% Convert the struct to a JSON string
jsonString = jsonencode(jointData)


serialportlist("available")
arduinoObj = serialport("COM4",9600)




while(1)
write(arduinoObj,jsonString,"int8")
pause(2);
end