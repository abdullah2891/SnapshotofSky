%my directory for serial reading python
clf
clear all
clc
commandStr='python [absolute dir]/solar_dome_demo.py ';






%call python file when you need data for xbee 
%the payload information is loaded to 
%data_python as string object
tic

 b=0;
for i=1:1
    %several snapshots
    A=[];
   
    pos_arm=[];
for i=1:17
[status, data_python]= system(commandStr);
data=str2num(data_python)
t=10:10:170;
A=[A data(1:17)];




%%%position of the arm
if  mod(data(18),10)==0 && data(18)<=170 && data(18)>=10  %filtering out wrong data
    primary_arm(i)=data(18);
else
    primary_arm(i)=data(19);
end
%%%%%%%%%%%%%%%%%
%subplot(2,1,1);
plot(t,data(1:17),'--o')





end
%x=1:289;
%plot(x,A,'--o')    
  





matrix=reshape(A,17,17);

%%%%%%%%%%%
c=[matrix primary_arm(:)];% adding index
c=sortrows(c,18); %sort the index
c(:,18) = [];  % delete the row
matrix=c;
%%%%%%%%%%%%%

%subplot(2,1,2);


drawnow;
imagesc(matrix,[0 1023])
colormap(jet(1023))
end

toc
