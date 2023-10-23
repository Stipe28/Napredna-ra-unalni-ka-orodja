function [pi_vrednost,napaka] = area_pi(k,in)
ratio=(sum(k>0)/in);
pi_vrednost=ratio*4;
napaka= abs(pi-pi_vrednost);
end