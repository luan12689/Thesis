function [flag] = checkvoice(dist,number)
thresh0 =6.8;
thresh1 =6.4;
thresh2 =6.9;
thresh3 =6.9;
thresh4 =6.6;
thresh5 =7.3;
thresh6 =7.3;
thresh7 =7.85;
thresh8 =6.9;
thresh9 =7.82;

distmin = dist(1);

switch number(1)
    case 0
        if distmin > thresh0
            disp ('Reject this person at 0');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 0');
        end
        
    case 1
        if distmin > thresh1
            disp ('Reject this person at 1');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 1');
        end
        
    case 2
        if distmin > thresh2
            disp ('Reject this person at 2');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 2');
        end
        
    case 3
        if distmin > thresh3
            disp ('Reject this person at 3');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 3');
        end
    case 4
        if distmin > thresh4
            disp ('Reject this person at 4');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 4');
        end
    case 5
        if distmin > thresh5
            disp ('Reject this person at 5');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 5');
        end
    case 6
        if distmin > thresh6
            disp ('Reject this person at 6');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 6');
        end
    case 7
        if distmin > thresh7
            disp ('Reject this person at 7');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 7');
        end
    case 8
        if distmin > thresh8
            disp ('Reject this person at 8');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 8');
        end
    case 9
        if distmin > thresh9
            disp ('Reject this person at 9');
            flag = 0;
        else
            flag = 1;
            disp ('Accept this person at 9');
        end
        
end

end