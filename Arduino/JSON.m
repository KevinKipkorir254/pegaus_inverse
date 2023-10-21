
theta_1 = 10;
theta_2 = 20;
theta_3 = 30;
theta_4 = 40;
theta_5 = 50;



% Create an empty cell array to store joint data
joints = cell(1, 4);

% Populate the cell array with joint data
for i = 1:4
    jointName = sprintf('joint_%d', i);

    if(i == 1)

    jointValue = theta_1; % You can set the value as needed
    end



    if(i == 2)

    jointValue = theta_2; % You can set the value as needed
    end

    if(i == 3)

    jointValue = theta_3; % You can set the value as needed
    end

    if(i == 3)

    jointValue = theta_4; % You can set the value as needed
    end

    jointData = struct(jointName, jointValue);
    joints{i} = jointData;
end

% Convert the cell array to a JSON string
jsonString = jsonencode(joints)


% Create a struct for joint data
jointData = struct( 'joint_1', theta_1, 'joint_2', theta_2, 'joint_3', theta_3,'joint_4', theta_4);

% Convert the struct to a JSON string
jsonString = jsonencode(jointData)
