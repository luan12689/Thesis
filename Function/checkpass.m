function [k,flag] = checkpass(word,password) 
    k = 0;
    
    for jj = 1:length(password)
        if (word(jj) == password(jj))
            k=k+1;
            disp ('match');
        else
            disp ('no match');
            break;   
        end
    end

    if (k == length(password))
        flag = 1;
    else
        flag = 0;
    end
    
end    