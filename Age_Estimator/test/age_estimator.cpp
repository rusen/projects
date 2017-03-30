#include <stdio.h>
#include <iostream>
#include "cv.h"
#include "highgui.h"

using namespace std;

CvHaarClassifierCascade *cascade_f;
CvHaarClassifierCascade *cascade_e;
CvHaarClassifierCascade *cascade_m;
CvHaarClassifierCascade *cascade_n;
CvMemStorage			*storage;

CvMat* foreheadMat;
CvMat* leftCheekMat;
CvMat* rightCheekMat;

int histogram[768];	//256 * 3, for forehead, leftCheek and rightCheek histograms.


unsigned char ** forehead2DArray;
unsigned char ** leftCheek2DArray;
unsigned char ** rightCheek2DArray;

void detectEyes(IplImage *img, bool lbp);
void getLBP(unsigned char** matrix, int width, int height, int* histogram);

int main( int argc, char** argv )
{
    CvCapture *capture;
    IplImage  *frame;
    int       key;

    char *file1 = "/Developer/OpenCV-2.2.0/data/haarcascades/haarcascade_frontalface_alt2.xml";
    char *file2 = "/Developer/OpenCV-2.2.0/data/haarcascades/haarcascade_mcs_eyepair_small.xml";
    char *file3 = "/Developer/OpenCV-2.2.0/data/haarcascades/haarcascade_mcs_mouth.xml";
    char *file4 = "/Developer/OpenCV-2.2.0/data/haarcascades/haarcascade_mcs_nose.xml";

    //Learning histogram.




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
    cvNamedWindow( "forehead", 1 );
    cvNamedWindow( "leftCheek", 1 );
    cvNamedWindow( "rightCheek", 1 );

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
        detectEyes( frame, key == 'a');

        cvShowImage( "video", frame );
        /* quit if user press 'q' */
        key = cvWaitKey( 100 );
    }

    /* free memory */
    cvReleaseCapture( &capture );
    cvDestroyWindow( "video" );
    cvReleaseHaarClassifierCascade( &cascade_f );
    cvReleaseHaarClassifierCascade( &cascade_e );
    cvReleaseMemStorage( &storage );

    return 0;

}

void detectEyes(IplImage *img, bool lbp)
{
	int eyeRectX, eyeRectY, eyeRectWidth, eyeRectHeight;

//	cout << "detect function" << endl;

	int i;

	//The grayscale image to be recorded.
	IplImage *grayImg;

	if (lbp){	//Testing mode.
		grayImg= cvCreateImage( cvSize( img->width, img->height ), IPL_DEPTH_8U, 1 );
		cvCvtColor(img, grayImg, CV_RGB2GRAY);
	}
    /* detect faces */
	CvSeq *faces = cvHaarDetectObjects(
		img, cascade_f, storage,
		1.1, 3, 0, cvSize( 40, 40 ) );

    /* return if not found */
    if (faces->total == 0) return;

    /* draw a rectangle */
	CvRect *faceRect = (CvRect*)cvGetSeqElem(faces, 0);
	cvRectangle(img,
				cvPoint(faceRect->x, faceRect->y),
				cvPoint(faceRect->x + faceRect->width, faceRect->y + faceRect->height),
				CV_RGB(255, 255, 255), 1, 8, 0);

    /* reset buffer for the next object detection */
//    cvClearMemStorage(storage);

    /* Set the Region of Interest: estimate the eyes' position */

//	cout << "detect eyes" << endl;

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
			cvShowImage( "forehead" , foreheadMat);

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

//	cvResetImageROI(img);

	/* reset buffer for the next object detection */
//	cvClearMemStorage(storage);

//	cout << "detect mouth" << endl;

	/* Set the Region of Interest: estimate the mouth's position */
	int mouthROIx = faceRect->x;
	int mouthROIy = faceRect->y + (0.5 * faceRect->height);
	int mouthROIWidth = faceRect->width;
	int mouthROIHeight = 0.5 * faceRect->height;

	cvSetImageROI(img, cvRect(mouthROIx, mouthROIy, mouthROIWidth, mouthROIHeight));

	/* detect mouth */
	CvSeq* mouth = cvHaarDetectObjects(
		img, cascade_m, storage,
		1.15, 3, 0, cvSize(25, 15));

	cvResetImageROI(img);  // Reset image ROI.

    CvRect* mouthRect;
	/* draw a rectangle for each eye found */
	for( i = 0; i < (mouth ? mouth->total : 0); i++ ) {
		mouthRect = (CvRect*)cvGetSeqElem( mouth, i );
		mouthRect->x += mouthROIx;
		mouthRect->y += mouthROIy;
		cvRectangle(img,
					cvPoint(mouthRect->x, mouthRect->y),
					cvPoint(mouthRect->x + mouthRect->width, mouthRect->y + mouthRect->height),
					CV_RGB(0, 255, 0), 1, 8, 0);
	}


	/* Set the Region of Interest: estimate the nose's position */
	int noseROIx = faceRect->x;
	int noseROIy = faceRect->y + (0.3 * faceRect->height);
	int noseROIWidth = faceRect->width;
	int noseROIHeight = 0.7 * faceRect->height;

	cvSetImageROI(img,
				cvRect(noseROIx, noseROIy, noseROIWidth, noseROIHeight));

	/* detect nose */
//	cout << "detect nose" << endl;
	CvSeq* nose = cvHaarDetectObjects(
		img, cascade_n, storage,
		1.15, 3, 0, cvSize(25, 15));

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
					//Histogram Calculation takes place here.
					leftCheekMat=cvCreateMat(noseRect->x - eyeRectX, noseRect->height, CV_8UC1);

					cvGetSubRect(grayImg, leftCheekMat, cvRect(eyeRectX, noseRect->y, noseRect->x - eyeRectX, noseRect->height));
					cvShowImage( "leftCheek" , leftCheekMat);

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
//		cout << "right yanak" << endl;
		cvRectangle(img,
					cvPoint(noseRect->x + noseRect->width, noseRect->y),
					cvPoint(eyeRectX + eyeRectWidth, noseRect->y + noseRect->height),
					CV_RGB(1, 1, 1), 1, 8, 0);

		if (lbp){
							//Histogram Calculation takes place here.
							rightCheekMat=cvCreateMat((eyeRectX + eyeRectWidth) - (noseRect->x + noseRect->width), noseRect->height, CV_8UC1);

							cvGetSubRect(grayImg, rightCheekMat, cvRect(noseRect->x + noseRect->width, noseRect->y, (eyeRectX + eyeRectWidth) - (noseRect->x + noseRect->width), noseRect->height));
							cvShowImage( "rightCheek" , rightCheekMat);

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

							for(int i=0; i<768; i++)
								cout<<histogram[i]<<" ";
							cout<<endl;

							//TODO: USE THESE HISTOGRAMS FOR TESTING.

				}

	}

	cvClearMemStorage(storage);
}

void getLBP(unsigned char** matrix, int width, int height, int* histogram) {
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

