%Download images from Google Earth.

resolution=1;   %resolution in meters.

fileId=fopen('Airport_Coordinates.txt');

counter=0;

down_limit=-1;

while 1
    
    tempLine=fgetl(fileId);

    %End of File!
    if fileId==''
        break
    end
    ['python googleMap.py ./images/airport' int2str(counter) ' ' tempLine ' ' int2str(resolution)];
    
    if counter>down_limit 
            system(['python googleMap.py ./images/airport' int2str(counter) ' ' tempLine ' ' int2str(resolution)]);
    end
    
    counter=counter+1;
    
    if counter==1 
        break;
    end
    
end