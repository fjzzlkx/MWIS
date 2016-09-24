%计算最初根据邻居排列的初始state
function [ state_vec ] = compute_state_init( num_of_node )
%COMPUTE_STATE_INIT Summary of this function goes here
%   Detailed explanation goes herestate_vec = [];
    %num_of_node = 20;
    %a = ones(num_of_node);
    state_vec = [];
    for i = 0:num_of_node./2 -1 
        part1 = ones(num_of_node - 2 *  i, i) * 2;
        part2 = ones(num_of_node - 2 * i);
        part2 = part2 + eye(num_of_node - 2 * i);
        part2(:,num_of_node -  2 *i )=  part2(:,num_of_node -  2*i)  -  ones(num_of_node - 2 * i,1); 
        part3 = zeros(num_of_node - 2 * i, i);
        part = [part1,part2,part3];
        %part(1,:) = [];
        state_vec = [state_vec;part];
    end
    state_vec;
    state_vec = unique(state_vec,'rows');
    %可能的第二部分最大值
    if rem(num_of_node,2) == 1
        middle = round(num_of_node / 2);
        part4 = ones(middle,middle-1)*2;
        part5  = eye(middle);
        %state_vec = [state_vec;part4,part5];
        index_temp = nchoosek(1:middle+1,3);
        part7 = zeros(size(index_temp,1),middle + 1);
        for i = 1:size(index_temp,1)
            part7(i,index_temp(i,:)) = 1;
        end
        part6 = [ones(size(part7,1),middle-2)*2];
    end

    if rem(num_of_node,2) == 0
         middle = round(num_of_node / 2);
         index_temp = nchoosek(1:middle+1,2);
         part5 = zeros(size(index_temp,1),middle + 1);
        for i = 1:size(index_temp,1)
            part5(i,index_temp(i,:)) = 1;
        end
        part4 = [ones(size(part5,1),middle-1)*2];
        
        index_temp = nchoosek(1:middle+2,4);
        part7 = zeros(size(index_temp,1),middle + 2);
        for i = 1:size(index_temp,1)
            part7(i,index_temp(i,:)) = 1;
        end
        part6 = [ones(size(part7,1),middle-2)*2];
    end
    state_vec = [state_vec;part4,part5;part6,part7];
    state_vec = unique(state_vec,'rows');
end

