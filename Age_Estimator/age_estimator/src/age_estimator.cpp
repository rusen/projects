#include <stdio.h>
#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <math.h>
using namespace std;
using namespace cv;

#define DEBUG 0
#define K_NN 12
#define MAX_INT 2147483647

CvHaarClassifierCascade *cascade_f;
CvHaarClassifierCascade *cascade_e;
CvHaarClassifierCascade *cascade_m;
CvHaarClassifierCascade *cascade_n;
CvMemStorage			*storage;

CvMat* foreheadMat;
CvMat* leftCheekMat;
CvMat* rightCheekMat;

unsigned char ** forehead2DArray;
unsigned char ** leftCheek2DArray;
unsigned char ** rightCheek2DArray;

double* histogram;
double** histograms;
int numPerson;

int detectEyes(IplImage *img, bool lbp, double* histogram, int predictType);
void getLBP(unsigned char** matrix, int width, int height, double* histogram);
void readCombined(double** histograms, char* fileName, int* numPerson);
double predictAge(double** histograms, int numPerson, double* histogram, int gender);

int detectEyes(IplImage *img, bool lbp, double* histogram, int predictType) {

	/* create a font */
	CvFont font1;
	cvInitFont( &font1, CV_FONT_VECTOR0, 0.8f, 0.8f, 0.8f,
	2 );

	cvResetImageROI(img);  // reset image ROI, convert eye coordinates to global

	//The grayscale image to be recorded.
	IplImage *grayImg;

	if (lbp) {	//Testing mode.
		grayImg= cvCreateImage( cvSize( img->width, img->height ), IPL_DEPTH_8U, 1 );
		cvCvtColor(img, grayImg, CV_RGB2GRAY);
	}
	/* detect faces */
	if(DEBUG) printf("detecting faces\n");
	CvSeq *faces = cvHaarDetectObjects(
			img, cascade_f, storage,
			1.1, 3, 0, cvSize( 40, 40 ) );

	/* draw a rectangle */
	for(int faceCounter = 0;faceCounter<faces->total;faceCounter++){
		int i;
		int eyeRectX, eyeRectY, eyeRectWidth, eyeRectHeight;

		CvRect *faceRect = (CvRect*)cvGetSeqElem(faces, faceCounter);

		cvRectangle(img,
				cvPoint(faceRect->x, faceRect->y),
				cvPoint(faceRect->x + faceRect->width, faceRect->y + faceRect->height),
				CV_RGB(255, 255, 255), 1, 8, 0);

		/* reset buffer for the next object detection */
		//    cvClearMemStorage(storage);

		/* Set the Region of Interest: estimate the eyes' position */

		if(DEBUG) printf("detecting eyes\n");

		int eyeROIx = faceRect->x;
		int eyeROIy = faceRect->y + (faceRect->height/5.5);
		int eyeROIWidth = faceRect->width;
		int eyeROIHeight = faceRect->height/3.0;

		cvSetImageROI(img,
				cvRect(eyeROIx, eyeROIy, eyeROIWidth, eyeROIHeight));

		/* detect eyes */
		CvSeq* eyes = cvHaarDetectObjects(
				img, cascade_e, storage,
				1.15, 3, 0, cvSize(25, 15));

		if(eyes->total != 1) {
			fprintf(stderr, "eye error %d\n", eyes-> total);
			cvResetImageROI(img);  // reset image ROI, convert eye coordinates to global
			cvClearMemStorage(storage);
			return 0;
		} else {
			if(DEBUG) printf("#eyes: %d\n", eyes->total);
		}

		cvResetImageROI(img);  // reset image ROI, convert eye coordinates to global
		CvRect * eyeRect;

		/* draw a rectangle for each eye found */
		for( i = 0; i < (eyes ? eyes->total : 0); i++ ) {
			eyeRect = (CvRect*)cvGetSeqElem( eyes, i );
			eyeRect->x += eyeROIx;
			eyeRect->y += eyeROIy;

			eyeRectX = eyeRect->x;
			eyeRectY = eyeRect->y;
			eyeRectWidth = eyeRect->width;
			eyeRectHeight = eyeRect->height;

			cvRectangle(img,
					cvPoint(eyeRect->x, eyeRect->y),
					cvPoint(eyeRect->x + eyeRect->width, eyeRect->y + eyeRect->height),
					CV_RGB(255, 0, 0), 1, 8, 0);

			//cout<<eyeRect->x<<" "<<faceRect->y<<" "<<eyeRect->x + eyeRect->width<<" "<<eyeRect->y<<endl;
			//cout<<faceRect->x<<" "<<faceRect->y<<" "<<eyeRect->x + faceRect->x <<" "<<eyeRect->y + faceRect->y + faceRect->height / 5.5<<endl;

			//Drawing the forehead.
			cvRectangle(img,
					cvPoint(eyeRect->x, faceRect->y),
					cvPoint(eyeRect->x + eyeRect->width, eyeRect->y),
					CV_RGB(255, 255, 255), 1, 8, 0);

			if (lbp){
				//Histogram Calculation takes place here.
				foreheadMat=cvCreateMat(eyeRect->width, eyeRect->y - faceRect->y, CV_8UC1);

				/* create new image for the grayscale version */


				cvGetSubRect(grayImg, foreheadMat, cvRect(eyeRect->x, faceRect->y, eyeRect->width, eyeRect->y - faceRect->y));

				int rowItr, colItr;
				forehead2DArray= (unsigned char **) malloc(sizeof(unsigned char *) * foreheadMat->width);

				for(rowItr=0;rowItr<foreheadMat->width;rowItr++){
					forehead2DArray[rowItr]=(unsigned char *) malloc(sizeof(unsigned char) * foreheadMat->height);
				}

				for(rowItr=0;rowItr<foreheadMat->width;rowItr++){
					for(colItr=0;colItr<foreheadMat->height;colItr++){
						forehead2DArray[rowItr][colItr] = foreheadMat->data.ptr[rowItr*foreheadMat->width + colItr];
					}
				}
				//Get the LBP Histogram of forehead.
				getLBP(forehead2DArray, foreheadMat->height, foreheadMat->width, histogram);

				//			for(int i=0; i<256; i++)
				//				cout<<histogram[i]<<" ";
				//			cout<<endl;

				//TODO: USE THESE HISTOGRAMS FOR TESTING.

			}
		}

		/* Set the Region of Interest: estimate the nose's position */
		int noseROIx = eyeRectX;
		int noseROIy = eyeRectY + eyeRectHeight;
		int noseROIWidth = eyeRectWidth;
		int noseROIHeight = eyeRectY + faceRect->width/2;

		cvSetImageROI(img,
				cvRect(noseROIx, noseROIy, noseROIWidth, noseROIHeight));

		/* detect nose */
		if(DEBUG) printf("detecting nose\n");
		CvSeq* nose = cvHaarDetectObjects(
				img, cascade_n, storage,
				1.15, 3, 0, cvSize(25, 15));

		if(nose->total != 1) {
			fprintf(stderr, "nose error\n");
			cvResetImageROI(img);  // Reset image ROI. Convert nose coordinates to global.
			cvClearMemStorage(storage);
			return 0;
		} else {
			if(DEBUG) printf("#nose: %d\n", nose->total);
		}

		cvResetImageROI(img);  // Reset image ROI. Convert nose coordinates to global.

		CvRect* noseRect;

		/* draw a rectangle for each eye found */
		for( i = 0; i < (nose ? nose->total : 0); i++ ) {
			noseRect = (CvRect*)cvGetSeqElem( nose, i );
			noseRect->x += noseROIx;
			noseRect->y += noseROIy;
			cvRectangle(img,
					cvPoint(noseRect->x, noseRect->y),
					cvPoint(noseRect->x + noseRect->width, noseRect->y + noseRect->height),
					CV_RGB(0, 0, 255), 1, 8, 0);

			//	cout << "left yanak" << endl;
			// draw left yanak
			cvRectangle(img,
					cvPoint(eyeRectX, noseRect->y),
					cvPoint(noseRect->x, noseRect->y + noseRect->height),
					CV_RGB(1, 1, 1), 1, 8, 0);

			if (lbp){
				if(DEBUG) printf("left yanak\n");
				//Histogram Calculation takes place here.
				//printf("%d %d\n", noseRect->x - eyeRectX, noseRect->height);
				leftCheekMat=cvCreateMat(noseRect->x - eyeRectX, noseRect->height, CV_8UC1);
				cvGetSubRect(grayImg, leftCheekMat, cvRect(eyeRectX, noseRect->y, noseRect->x - eyeRectX, noseRect->height));

				int rowItr, colItr;
				leftCheek2DArray= (unsigned char **) malloc(sizeof(unsigned char *) * leftCheekMat->width);

				for(rowItr=0;rowItr<leftCheekMat->width;rowItr++){
					leftCheek2DArray[rowItr]=(unsigned char *) malloc(sizeof(unsigned char) * leftCheekMat->height);
				}

				for(rowItr=0;rowItr<leftCheekMat->width;rowItr++){
					for(colItr=0;colItr<leftCheekMat->height;colItr++){
						leftCheek2DArray[rowItr][colItr] = leftCheekMat->data.ptr[rowItr*leftCheekMat->width + colItr];
					}
				}
				//Get the LBP Histogram of forehead.
				getLBP(leftCheek2DArray, leftCheekMat->height, leftCheekMat->width, histogram + 256);

				//TODO: USE THESE HISTOGRAMS FOR TESTING.

			}
			// draw right yanak

			cvRectangle(img,
					cvPoint(noseRect->x + noseRect->width, noseRect->y),
					cvPoint(eyeRectX + eyeRectWidth, noseRect->y + noseRect->height),
					CV_RGB(1, 1, 1), 1, 8, 0);

			if (lbp){
				if(DEBUG) printf("right yanak\n");
				//Histogram Calculation takes place here.
				if(DEBUG) printf("%d %d\n", (eyeRectX + eyeRectWidth) - (noseRect->x + noseRect->width),  noseRect->height);
				rightCheekMat=cvCreateMat((eyeRectX + eyeRectWidth) - (noseRect->x + noseRect->width), noseRect->height, CV_8UC1);

				cvGetSubRect(grayImg, rightCheekMat, cvRect(noseRect->x + noseRect->width, noseRect->y, (eyeRectX + eyeRectWidth) - (noseRect->x + noseRect->width), noseRect->height));

				int rowItr, colItr;
				rightCheek2DArray= (unsigned char **) malloc(sizeof(unsigned char *) * rightCheekMat->width);

				for(rowItr=0;rowItr<rightCheekMat->width;rowItr++){
					rightCheek2DArray[rowItr]=(unsigned char *) malloc(sizeof(unsigned char) * rightCheekMat->height);
				}

				for(rowItr=0;rowItr<rightCheekMat->width;rowItr++){
					for(colItr=0;colItr<rightCheekMat->height;colItr++){
						rightCheek2DArray[rowItr][colItr] = rightCheekMat->data.ptr[rowItr*rightCheekMat->width + colItr];
					}
				}

				//Get the LBP Histogram of forehead.
				getLBP(rightCheek2DArray, rightCheekMat->height, rightCheekMat->width, histogram + 512);

				double norm = 0;
				//Normalize the resulting histogram here.
				for(int histogramItr = 0; histogramItr < 768; histogramItr++) {
					norm += histogram[histogramItr] * histogram[histogramItr];
				}

				norm = sqrt(norm);

				for(int histogramItr = 0; histogramItr < 768; histogramItr++) {
					histogram[histogramItr]= histogram[histogramItr] / norm;
				}

				if(DEBUG) {
					for(int i=0; i<768; i++)
						cout<<histogram[i]<<" ";
					cout<<endl;
				}

	        	double predictedAge = predictAge(histograms, numPerson, histogram, predictType);



	        	/* put the coordinates in a char buffer */
	        	char thetext[5];
	        	sprintf(thetext, "%d", (int)predictedAge);

	        	/* write/put text into the image */
	        	cvPutText (img, thetext, cvPoint(faceRect->x + faceRect->width, faceRect->y + faceRect->height)
	        	, &font1, CV_RGB(49,79,79)); // with a 'nice' color.


				//TODO: USE THESE HISTOGRAMS FOR TESTING.

			}

		}
	}
	cvClearMemStorage(storage);
	return 1;
}

void getLBP(unsigned char** matrix, int width, int height, double* histogram) {
	unsigned char pattern;

	// histogram size is 256
	for(int i = 0; i < 256; i++)
		histogram[i] = 0;

	for(int i = 1; i < height-1; i++) {
		for(int j = 1; j < width-1; j++) {
			pattern = 0;
			if(matrix[i-1][j-1] > matrix[i][j]) pattern += 128;  // top left
			if(matrix[i-1][j] > matrix[i][j])   pattern += 64;   // top
			if(matrix[i-1][j+1] > matrix[i][j]) pattern += 32;   // top right
			if(matrix[i][j+1] > matrix[i][j])   pattern += 16;   // right
			if(matrix[i+1][j+1] > matrix[i][j]) pattern += 8;    // bottom right
			if(matrix[i+1][j] > matrix[i][j])   pattern += 4;    // bottom
			if(matrix[i+1][j-1] > matrix[i][j]) pattern += 2;    // bottom left
			if(matrix[i][j-1] > matrix[i][j])   pattern += 1;    // left
			histogram[pattern] += 1;
		}
	}

}

int main() {
	histogram = (double*) malloc(768 * sizeof(double));
	histograms = (double**) malloc(1005 * sizeof(double *));
	for(int i = 0; i < 1005; i++) {
		histograms[i] = (double*) malloc(770 * sizeof(double));
	}
	numPerson = 0;
	readCombined(histograms, "/Users/rusi/Workspace/age_estimator/Debug/combined.txt", &numPerson);

	CvCapture *capture;
	    IplImage  *frame;
	    int       key = 0;

	    char *file1 = "/Developer/OpenCV-2.2.0/data/haarcascades/haarcascade_frontalface_alt2.xml";
	    char *file2 = "/Developer/OpenCV-2.2.0/data/haarcascades/haarcascade_mcs_eyepair_big.xml";
	    char *file3 = "/Developer/OpenCV-2.2.0/data/haarcascades/haarcascade_mcs_mouth.xml";
	    char *file4 = "/Developer/OpenCV-2.2.0/data/haarcascades/haarcascade_mcs_nose.xml";

	    //Learning histogram.

	//    FILE * histogramFile = fopen("histograms.txt","r");

	    /* load the classifier
	       note that I put the file in the same directory with
	       this code */

	    /* load the face classifier */
		cascade_f = (CvHaarClassifierCascade*)cvLoad(file1, 0, 0, 0);

	    /* load the eye classifier */
	    cascade_e = (CvHaarClassifierCascade*)cvLoad(file2, 0, 0, 0);

	    /* load the mouth classifier */
	    cascade_m = (CvHaarClassifierCascade*)cvLoad(file3, 0, 0, 0);

	    /* load the mouth classifier */
	    cascade_n = (CvHaarClassifierCascade*)cvLoad(file4, 0, 0, 0);

	    /* setup memory buffer; needed by the face detector */
	    storage = cvCreateMemStorage( 0 );

	    /* initialize camera */
	    capture = cvCaptureFromCAM( 0 );

	    /* always check */
	    assert( cascade_e && cascade_f && cascade_m && cascade_n && storage && capture );

	    /* create a window */
	    cvNamedWindow( "video", 1 );

	 //   frame=cvLoadImage("/Users/rusi/Dropbox/CENG740-shared (1)/project/dataset-sefa/imdb/female/bening_1958.jpg",1);

	    while( key != 'q' ) {
	        /* get a frame */
	       frame = cvQueryFrame( capture );

	        /* always check */
	        if( !frame ) break;

	        /* 'fix' frame */
	    //    cvFlip( frame, frame, -1 );
	    //    frame->origin = 0;

	        /* detect eyes */
	        int result;

	        if(key == 'm' || key == 'f') {
	        	// find closest histogram
	        	int g;
	        	if (key == 'm') g = 0;	// 0 for man, 1 for woman.
	        	else if(key == 'f') g = 1;

	        	 result = detectEyes(frame, (key == 'm' || key == 'f'), histogram, g);

	        }
	        else result = detectEyes(frame, false, histogram, 0);

	        cvShowImage( "video", frame );

	        /* quit if user press 'q' */
	        key = cvWaitKey( 100 );
	    }

	    /* free memory */
	    cvReleaseCapture( &capture );
	    cvDestroyWindow( "video" );
	    cvReleaseHaarClassifierCascade( &cascade_f );
	    cvReleaseHaarClassifierCascade( &cascade_e );
	    cvReleaseHaarClassifierCascade( &cascade_n );
	    cvReleaseHaarClassifierCascade( &cascade_m );
	    cvReleaseMemStorage( &storage );

	    return 0;


}

double distance(double* hist1, double* hist2) {
	double d = 0;
	double dEuc = 0;
	for(int i = 0; i < 768; i++) {
		d += abs(hist1[i] - hist2[i]);
		dEuc+=((hist1[i] - hist2[i]) * (hist1[i] - hist2[i]));
	}
	//return d;
	return sqrt(dEuc);
}
double predictAge(double** histograms, int numPerson, double* histogram, int gender) {
	double minDistance=MAX_INT;
	double prevMinDistance = 0;
	int age;
	double d;
	int k_age=0;


	//int minDForKNN=0;

	for(int k_itr=0; k_itr <K_NN; k_itr++){

		minDistance=MAX_INT;

		for(int i = 0; i < numPerson; i++) {

			if(histograms[i][0] != gender)
				continue;

			else {

				d = distance(histogram, histograms[i]+2);
		//		cout<<"Distance to Sample:"<< d << endl;
				if (minDistance > d && prevMinDistance < d) {
					minDistance = d;
					age = histograms[i][1];
				}

			}
		}

		prevMinDistance = minDistance;
		cout<<" Previous Minimum Distance:"<<prevMinDistance<<", Minimum Distance: "<<minDistance<<endl;
		cout<<" AGE " << k_itr<< " FOUND: " << age << endl;
		k_age += age;
		//printf("md = %d\n", minDForKNN);
		//k_age+=age;
	}

	//return k_age/(float)K_NN;
	return k_age / (float)K_NN;
	//return age;
}

void readCombined(double** histograms, char* fileName, int* numPerson) {
	printf("read combined begin\n");
	FILE* fp = fopen(fileName, "r");
	if(!fp) {
		fprintf(stderr, "can't open file\n");
	}
	int n;
	*numPerson = 0;
	while(fscanf(fp, "%d", &n) != EOF) {
		double norm = 0;
		histograms[*numPerson][0] = n;  //gender
		fscanf(fp, "%d", &n); histograms[*numPerson][1] = n;  // age

		for(int i = 0; i < 768; i++) {
			fscanf(fp,"%d", &n); histograms[*numPerson][i+2] = n;
			norm += n * n;
		}

		norm = sqrt(norm);

		for(int i = 0; i < 768; i++) {
			histograms[*numPerson][i+2] /= norm;
		}
		//Let's normalize the histogram we just read.

		*numPerson += 1;
	}

	fclose(fp);
}
