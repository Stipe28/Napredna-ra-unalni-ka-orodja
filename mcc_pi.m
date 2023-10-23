function [y,k,x] = mcc_pi(in)


x=(10)*rand(1,in);
y=(10)*rand(1,in);
r=5;
k=sqrt((x-5).^2+(y-5).^2)<=r;
k=k.*y;
k(k==0)=nan;

end
