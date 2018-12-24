[id,xc,flag]=textread('../output/plot_line.txt','%f%f%f');

idx=1;
for i=2:length(id)
    pos1=idx(end);
    pos2=i;
    if id(pos1) == id(pos2)
        idx=[idx i];
        hold on
        plot([xc(pos1) xc(pos2)],ones(1,2),'r-');
    elseif flag(pos1)==0
            idx=[idx pos2];
            hold on
            plot([xc(pos1) xc(pos2)],ones(1,2),'g-');
    elseif flag(pos1) == 1 && flag(pos2) ==1
        
    end     
end