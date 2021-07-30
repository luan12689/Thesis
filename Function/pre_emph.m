function data_plot = pre_emph(data_rec)
a=1; 
b=0.95;

data_plot = filter([a b], 1, data_rec); % Pre-emphasis
end