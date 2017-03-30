## Script that downloads googleMap data for 
# @param output Output file name ending without .png
# @param lat1 Latitude of the top-left corner
# @param lon1 Longtitude of the top-left corner
# @param lat2 Latitude of the bottom-right corner
# @param lon2 Longtitude of the bottom-right corner
# @param resolution Resolution in meters (will lead to approximate calculation)
# @param maptype Either sattelite, roadmap, terrain, hybrid
# sample usage: python deneme33 38.07193 23.5528 38.02193 23.6028 4

import urllib
from time import sleep 
from PIL import Image
import math

def saveMap(lat,lon,zoomLevel,imageFile):
    pngLink="http://maps.google.com/maps/api/staticmap?center=%f,%f&zoom=%d&size=640x640&maptype=satellite&sensor=false" % (lat,lon,zoomLevel)
    f = urllib.urlopen( pngLink )
    local_file = open(imageFile, "w" + "b")
    local_file.write(f.read())
    local_file.close()
    f.close( )
    return


if __name__ == '__main__':
    import sys 
    
    # each tile of google is 256 pixels
    googleTileSize=256.0
    # maximum patch size
    googleMaxSize=640.0
    xBufferSize=40
    yBufferSize=40
    
    # find the zoom level for google maps by getting the circumference of the earth as 40000 km
    # each tile
    zoomLevel=math.floor(math.log(40000000.0/(googleTileSize*float(sys.argv[6])),2))
    print zoomLevel
    
    # by using the calculated zoom level, find out how many tiles are required on both x and y directions
    latDist=float(sys.argv[2])-float(sys.argv[4])
    lonDist=float(sys.argv[5])-float(sys.argv[3])
    pixelSizeInDegrees=(360.0/math.pow(2,zoomLevel))/googleTileSize
    pixelSizeInDegreesY=(180.0/math.pow(2,zoomLevel))/googleTileSize
    print (latDist/pixelSizeInDegrees,lonDist/pixelSizeInDegrees)
    yTileSize=math.ceil((latDist/pixelSizeInDegrees-yBufferSize)/(googleMaxSize-yBufferSize))
    xTileSize=math.ceil((lonDist/pixelSizeInDegrees-xBufferSize)/(googleMaxSize-xBufferSize))
    print (xTileSize,yTileSize)
    try:
        # get the first small tile
        newLat1=float(sys.argv[2])-(pixelSizeInDegrees*math.cos(math.radians(float(sys.argv[2]))))*googleMaxSize/2.0
        newLon1=float(sys.argv[3])+pixelSizeInDegrees*googleMaxSize/2.0
        imageFile="temp.png"
        saveMap(newLat1,newLon1,zoomLevel,imageFile)
        im = Image.new("RGB",(int(xTileSize*googleMaxSize), int(yTileSize*googleMaxSize)))
        nLat=newLat1
        for i in range(int(xTileSize)):
            for j in range(int(yTileSize)):
				#get the next tile for the next iteration
                nLat=newLat1-j*(googleMaxSize-yBufferSize)*(pixelSizeInDegrees*math.cos(math.radians(nLat)))
                nLon=newLon1+i*(googleMaxSize-xBufferSize)*pixelSizeInDegrees
                print (nLat,nLon)
                saveMap(nLat,nLon,zoomLevel,imageFile)
                
                imO = Image.open(imageFile)
                box = (0, 0, int(googleMaxSize), int(googleMaxSize))
                region = imO.crop(box)
                box = (int(i*(googleMaxSize-xBufferSize)),int(j*(googleMaxSize-yBufferSize)), int(i*(googleMaxSize-xBufferSize)+googleMaxSize), int(j*(googleMaxSize-yBufferSize)+googleMaxSize))
                im.paste(region, box)
                
        #crop the borders
        box = (0, 0, int(xTileSize*googleMaxSize-(xTileSize-1)*xBufferSize), int(yTileSize*googleMaxSize-(yTileSize-1)*yBufferSize))
        im = im.crop(box)
        imageFile=sys.argv[1]+".png"
        im.save(imageFile)
        #save the .wld file as well
        filename = sys.argv[1]+".wld"
        FILE = open(filename,"w")
        FILE.write(str(pixelSizeInDegrees)+"\n")
        FILE.write(str(0)+"\n")
        FILE.write(str(0)+"\n")
        FILE.write(str(-pixelSizeInDegrees*math.cos(math.radians(newLat1)))+"\n")
        FILE.write(str(float(sys.argv[3]))+"\n")
        FILE.write(str(float(sys.argv[2]))+"\n")
        FILE.close()
    except IOError:
        print 'Connection problem'
    

#kaynaklar
# http://www.techniqal.com/blog/2008/07/31/python-file-read-write-with-urllib2/
# http://code.google.com/apis/maps/documentation/staticmaps/
# http://docs.codehaus.org/display/GEOTDOC/Image+Plugin#ImagePlugin-WorldFile
# http://code.google.com/apis/maps/documentation/javascript/v2/overlays.html#Google_Maps_Coordinates

# python "%f" deneme33 38.07193 23.5528 38.02193 23.6028 4
