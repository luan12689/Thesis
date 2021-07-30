function soundSegment=findSegment(express)
if express(1)==0
         voicedIndex=find(express); % Find the position of 1 in express
else
    voicedIndex=express;
end

soundSegment = [];
k = 1;
 soundSegment(k).begin = voicedIndex(1); % Set the starting position of the first group of segments
for i=1:length(voicedIndex)-1,
	 if voicedIndex(i+1)-voicedIndex(i)>1, % This group has a segment end
     soundSegment(k).end = voicedIndex(i); % Set the end position of the segment in this group.
	 soundSegment(k+1).begin = voicedIndex(i+1);% Set the starting position of the next set of segments  
     k = k+1;
    end
end
 soundSegment(k).end = voicedIndex(end); % The last group has the end position of the segment
 % Calculate the length of each segment in a group
for i=1 :k
    soundSegment(i).duration=soundSegment(i).end-soundSegment(i).begin+1;
end

end
