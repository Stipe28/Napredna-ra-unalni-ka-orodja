clc
clear
rng(9)
in=1e3;
[y,k,x]=mcc_pi(in);
[vrednost_pi,napaka]=area_pi(k,in)





figure(1)
scatter(x,y,'b')
hold on
scatter(x,k,'r')
grid on
xlabel('x','FontSize',20)
ylabel('y','FontSize',20)

