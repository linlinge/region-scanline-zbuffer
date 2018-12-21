clear
clc

for i=101:531
    str=['../output/check_in_out_pairs_' num2str(i) '.txt'];
    [id, flag]=textread(str,'%f%f');
    L1=length(find(flag==1));
    L2=length(find(flag==0));
    if  L1 ~= L2
        i
    end
    number_of_each_id=[];
    for j=1:length(id)
        number_of_each_id=[number_of_each_id length(find(id==id(j)))];
    end
    
    if length(number_of_each_id)~= length(find(number_of_each_id==2))
        i
    end
end






