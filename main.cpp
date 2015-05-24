
/*
----------------------------------------------------------------------------------------------------------------------------
                                     

                      Développé par Mezlini Mohamed 
                      le jeu est développe directement sur le system d'exploitation ubuntu                       
                      pour faire marché le jeu il suffit de mettre les images et le fichier de code dans le même dossier 
                      installer opencv sur ubuntu avec c++
                      puis lancer l'éxecution 
                      
                      Mail: mezlinimohamed11@gmail.com
                      twitter:MdMezlini
                              

                        
                        
----------------------------------------------------------------------------------------------------------------------------
*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

#include <iostream>

using namespace std;
using namespace cv;


int etape=0; 

int nbImgch;
int lastX = -1;
int lastY = -1;
IplImage *imgTracking; 

  char tab[14][20]={"Image01.png","Image02.png","Image03.png","Image04.png","Image05.png","Image06.png","Image07.png","Image08.png","Image09.png","Image10.png","Image11.png","Image12.png","Image07.png","Image11.png"};
  char alea[24][20];//tableau qui sera rempli aleatoirement 
  int pos[24]; 
  int posimgachange=0; 
  int imgachange=0;
  char imgToChange[20]; 
  char quitter[20]="quit02.jpg"; 
 


void init(){

  int i=0, nbImgch=25;
  srand(time(NULL));//time should write like this .
     
  for(i=0; i <24 ; i++){
    nbImgch=rand()%14;
    strcpy(alea[i],tab[nbImgch]); 
  }
  nbImgch=rand()%24;
  imgachange=nbImgch;
  strcpy(imgToChange,alea[nbImgch]);  
  for(i=0; i<24 ; i++){
    if(strcmp(alea[i],alea[nbImgch])==0) {
      pos[i]=1;
      posimgachange++; 
      } 
    else pos[i]=0; 
  }
}


int change(int pos_x , int pos_y ){
  // int e = 5; 
  if (etape ==0){

    if(((pos_x>=300)&&(pos_x<=450))&&((pos_y>=370)&&(pos_y<=420))) return 2;
    if(((pos_x>=550)&&(pos_x<=680))&&((pos_y>=0)&&(pos_y<=50))) return 0;
    return -1;  
 

  }
  else if (etape==1){
  //retourner la position de chaque point par rapport la le tableau 
  if(((pos_x>=25)&&(pos_x<=90))&&((pos_y>=100)&&(pos_y<=170))) return 0; 
  if(((pos_x>=120)&&(pos_x<=190))&&((pos_y>=100)&&(pos_y<=170))) return 1; 
  if(((pos_x>=220)&&(pos_x<=290))&&((pos_y>=100)&&(pos_y<=170))) return 2; 
  if(((pos_x>=320)&&(pos_x<=390))&&((pos_y>=100)&&(pos_y<=170))) return 3; 
  if(((pos_x>=420)&&(pos_x<=490))&&((pos_y>=100)&&(pos_y<=170))) return 4; 
  if(((pos_x>=520)&&(pos_x<=590))&&((pos_y>=100)&&(pos_y<=170))) return 5;

  if(((pos_x>=25)&&(pos_x<=90))&&((pos_y>=200)&&(pos_y<=270))) return 6; 
  if(((pos_x>=120)&&(pos_x<=190))&&((pos_y>=200)&&(pos_y<=270))) return 7; 
  if(((pos_x>=220)&&(pos_x<=290))&&((pos_y>=200)&&(pos_y<=270))) return 8; 
  if(((pos_x>=320)&&(pos_x<=390))&&((pos_y>=200)&&(pos_y<=270))) return 9; 
  if(((pos_x>=420)&&(pos_x<=490))&&((pos_y>=200)&&(pos_y<=270))) return 10; 
  if(((pos_x>=520)&&(pos_x<=590))&&((pos_y>=200)&&(pos_y<=270))) return 11; 
   
  
  if(((pos_x>=25)&&(pos_x<=90))&&((pos_y>=300)&&(pos_y<=370))) return 12; 
  if(((pos_x>=120)&&(pos_x<=190))&&((pos_y>=300)&&(pos_y<=370))) return 13; 
  if(((pos_x>=220)&&(pos_x<=290))&&((pos_y>=300)&&(pos_y<=370))) return 14; 
  if(((pos_x>=320)&&(pos_x<=390))&&((pos_y>=300)&&(pos_y<=370))) return 15; 
  if(((pos_x>=420)&&(pos_x<=490))&&((pos_y>=300)&&(pos_y<=370))) return 16; 
  if(((pos_x>=520)&&(pos_x<=590))&&((pos_y>=300)&&(pos_y<=370))) return 17;
  
  if(((pos_x>=25)&&(pos_x<=90))&&((pos_y>=400)&&(pos_y<=470))) return 18; 
  if(((pos_x>=120)&&(pos_x<=190))&&((pos_y>=400)&&(pos_y<=470))) return 19; 
  if(((pos_x>=220)&&(pos_x<=290))&&((pos_y>=400)&&(pos_y<=470))) return 20; 
  if(((pos_x>=320)&&(pos_x<=390))&&((pos_y>=400)&&(pos_y<=470))) return 21; 
  if(((pos_x>=420)&&(pos_x<=490))&&((pos_y>=400)&&(pos_y<=470))) return 22; 
  if(((pos_x>=520)&&(pos_x<=590))&&((pos_y>=400)&&(pos_y<=470))) return 23;



  //signaler quitter 
  if(((pos_x>=550)&&(pos_x<=680))&&((pos_y>=0)&&(pos_y<=50))) return -2;
   
  return -1; 
}
else {//dans l'interface de 

 
  if(((pos_x>=490)&&(pos_x<=670))&&((pos_y>=320)&&(pos_y<=400))) return 1;//pour jouer une autre fois
  if(((pos_x>=490)&&(pos_x<=670))&&((pos_y>=421)&&(pos_y<=470))) return 0;//pour sortir du jeu 
  return -1; 

}


}



  
//This function threshold the HSV image and create a binary image
IplImage* GetThresholdedImage(IplImage* imgHSV){       
    IplImage* imgThresh=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1);
    cvInRangeS(imgHSV, cvScalar(170,160,60), cvScalar(180,2556,256), imgThresh); 
    return imgThresh;
}


void trackObject(IplImage* imgThresh){
    // Calculate the moments of 'imgThresh'
    CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
    cvMoments(imgThresh, moments, 1);
    double moment10 = cvGetSpatialMoment(moments, 1, 0);
    double moment01 = cvGetSpatialMoment(moments, 0, 1);
    double area = cvGetCentralMoment(moments, 0, 0);

     // if the area<1000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
   
          
   if(area>100){
          
         lastX = moment10/area;
        lastY = moment01/area;
    }  

     free(moments); 
}



void changerImage(){
  if(change(lastX, lastY)!=-1){
    if(pos[change(lastX, lastY)]==1){
      pos[change(lastX, lastY)]=0;
      strcpy(alea[change(lastX, lastY)],"ok.jpg");//pour changer l'image trouver avec l'image oki 
      posimgachange--; 

      if(posimgachange==0)etape=2; //pour finir le jeu 
    }
  }


}

   void cvShowManyImages(IplImage *DispImage, int nArgs, ...) {
        static CvMemStorage* storage = 0;
         storage = cvCreateMemStorage(0);

               // img - Used for getting the arguments 
       IplImage *img;
   
       // [[DispImage]] - the image in which input images are to be copied
       // IplImage *DispImage;
   
       int size;
       int i;
       int m, n;
       int x, y;
   
       // w - Maximum number of images in a row 
       // h - Maximum number of images in a column 
       int w, h;
    
       // scale - How much we have to resize the image
       float scale;
       int max;
   
       // If the number of arguments is lesser than 0 or greater than 12
    // return without displaying 
    if(nArgs <= 0) {
        printf("Number of arguments too small....\n");
        return;
    }
    else if(nArgs > 24) {
        printf("Number of arguments too large....\n");
     return;
    }
    // Determine the size of the image, 
    // and the number of rows/cols 
    // from number of arguments 
    else if (nArgs == 1) {
        w = h = 1;
        size = 300;
    }
    else if (nArgs == 2) {
        w = 2; h = 1;
        size = 300;
    }
    else if (nArgs == 3 || nArgs == 4) {
        w = 2; h = 2;
        size = 300;
    }
    else if (nArgs == 5 || nArgs == 6) {
        w = 3; h = 2;
        size = 200;
    }
    else if (nArgs == 7 || nArgs == 8) {
          w = 4; h = 2;
       size = 200;
   }
   else {
        w = 6; h = 4;
       size = 75;
    }
    // Create a new 3 channel image
    // DispImage = cvCreateImage( cvSize(100 + size*w, 60 + size*h), 8, 3 );

   // Used to get the arguments passed
    va_list args;
 va_start(args, nArgs);
    // Loop for nArgs number of arguments
    for (i = 0, m = 40, n = 30; i < nArgs; i++, m += (30 + size)) {
     // Get the Pointer to the IplImage
        img = va_arg(args, IplImage*);

        // Check whether it is NULL or not
        // If it is NULL, release the image, and return
        if(img == 0) {
            printf("Invalid arguments");
          cvReleaseImage(&DispImage);
           return;
        }

        // Find the width and height of the image
        x = img->width;
        y = img->height;

        // Find whether height or width is greater in order to resize the image
        max = (x > y)? x: y;

        // Find the scaling factor to resize the image
        scale = (float) ( (float) max / size );

        // Used to Align the images
        if( i % w == 0 && m!= 20) {
            m = 20;
            n+= 20 + size;
        }

        // Set the image ROI to display the current image
        cvSetImageROI(DispImage, cvRect(m, n, (int)( x/scale ), (int)( y/scale )));

        // Resize the input image and copy the it to the Single Big Image
        cvResize(img, DispImage);

        // Reset the ROI in order to display the next image
        cvResetImageROI(DispImage);
    //cvReleaseImage(&DispImage);


    cvReleaseImage(&img);
    }
    cvClearMemStorage( storage );

    
}



//******************************************afficher les parametres du jeu 
void afficher_parametres(IplImage * DispImage)
{ 
  IplImage * img=cvLoadImage(imgToChange);
  IplImage * quit=cvLoadImage(quitter);

  // Set the image ROI to display the current image
  
        cvSetImageROI(DispImage, cvRect(0, 0, 50, 50));
         // Resize the input image and copy the it to the Single Big Image
        cvResize(img, DispImage);

        // Reset the ROI in order to display the next image
        cvResetImageROI(DispImage);
        //cvReleaseImage(&DispImage);

        //image quit 

        cvSetImageROI(DispImage, cvRect(580, 0, 70,60 ));
        cvResize(quit, DispImage);
        cvResetImageROI(DispImage);
        //********************* set text dans une endroit bien definit

    CvPoint p1; 
    p1.x=75; 
    p1.y=55; 
    CvFont font;
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 2, 2, 0.0, 5, 0.3); 
    char  text [4];

    sprintf(text,"%d" , posimgachange);  

    cvPutText( DispImage, text , p1 , &font, CV_RGB(255,50,0));
       
    cvReleaseImage(&img);

    cvReleaseImage(&quit);
    
}

//************************************************************************
//fonctio de la page d'accueil 

void accueil(IplImage * DispImage){

    //afficher l'icone de quitter 
    IplImage *quit=cvLoadImage(quitter); 
    cvSetImageROI(DispImage, cvRect(580, 0, 70,60 ));
    cvResize(quit, DispImage);
    cvResetImageROI(DispImage);
    cvReleaseImage(&quit);



    IplImage *fond=cvLoadImage("fond04.jpeg"); 
    cvSetImageROI(DispImage, cvRect(40, 80, 450,150 ));
    cvResize(fond, DispImage);
    cvResetImageROI(DispImage);
    cvReleaseImage(&fond);


    CvPoint p1,p2,p3,p4; 
    p2.x=p3.x=p4.x=p1.x=50; 
    p1.y=100; 
    p2.y=130; 
    p3.y=160; 
    p4.y=190; 

    CvFont font;
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 0.5, 0.5, 0.2, 1, 0.1); 
 

    cvPutText( DispImage, "Pour gagner ton match, passez ton marqueur " , p1 , &font, CV_RGB(255,255,255));
    cvPutText( DispImage, "rouge sur la ballon qui s'affiche dans la grille " , p2 , &font, CV_RGB(255,255,255));
    cvPutText( DispImage, "dont la couleur est identique a celle " , p3 , &font, CV_RGB(255,255,255));
    cvPutText( DispImage, "Ã  gauche en haut  " , p4 , &font, CV_RGB(255,255,255));


    //afficher l'icone de jouer


    IplImage *jouer=cvLoadImage("fond04.jpeg"); 
    cvSetImageROI(DispImage, cvRect(300, 370, 150,50 ));
    cvResize(jouer, DispImage);
    cvResetImageROI(DispImage);
    cvReleaseImage(&jouer);


    CvPoint pfond;
    pfond.x=320; 
    pfond.y=400; 
   
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 2, 0.5, 0.2, 2, 0.1); 
    cvPutText( DispImage, "Jouer " , pfond, &font, CV_RGB(255,255,255));
 


    if(change(lastX,lastY)==2)etape=1; 
    if (change(lastX,lastY)==0)exit(0); 
    



}

//*************************************************************************



// Create a string that contains the exact cascade name
// Contains the trained classifer for detecting hand
//const char *cascade_name="hand.xml";


//The function detects the hand from input frame and draws a rectangle around the detected portion of the frame
void detect_and_draw( IplImage* img )
{ static CvMemStorage* storage = 0;
storage = cvCreateMemStorage(0);


  //params(img); 
  cvClearMemStorage( storage );

   printf("l'image qu'il faut changer est dans la ligne %d et dans la colonne %d \n", change(lastX, lastY)/10, change(lastX, lastY)%10);
   changerImage(); 
  cvShowManyImages(img ,24 , cvLoadImage(alea[0]), cvLoadImage(alea[1]), cvLoadImage(alea[2]), cvLoadImage(alea[3]), cvLoadImage(alea[4]),cvLoadImage(alea[5]), cvLoadImage(alea[6]), cvLoadImage(alea[7]), cvLoadImage(alea[8]),cvLoadImage(alea[9]), cvLoadImage(alea[10]), cvLoadImage(alea[11]), cvLoadImage(alea[12]), cvLoadImage(alea[13]), cvLoadImage(alea[14]), cvLoadImage(alea[15]), cvLoadImage(alea[16]), cvLoadImage(alea[17]), cvLoadImage(alea[18]), cvLoadImage(alea[19]),cvLoadImage(alea[20]) ,cvLoadImage(alea[21]), cvLoadImage(alea[22]), cvLoadImage(alea[23]));
  afficher_parametres(img);
  if(change(lastX,lastY)==-2)exit(0); 
 


}
//fonction de la  fin normale du jeu

void fin( IplImage* DispImage ,int imgfelicitaion){


    CvPoint p1,p2; 
    p2.x=p1.x=90; 
    p1.y=105; 
    p2.y=150; 
    CvFont font;
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX,  1.5, 0.5, 0.2, 2, 0.1); 
 

    cvPutText( DispImage, "Felicitaion vous avez Gagner   " , p1 , &font, CV_RGB(0,50,205));
    cvPutText( DispImage, "           Gagner   " , p2 , &font, CV_RGB(0,50,205));
    

    IplImage *img=cvLoadImage("felicit01.jpg");
    
    if((imgfelicitaion>=10)&& (imgfelicitaion<20)) {//cette image est de taille plus grans 
      cvSetImageROI(DispImage, cvRect(225, 215, 250,250 ));
    }
    else if((imgfelicitaion>=20)&& (imgfelicitaion<30)) {//cette image est de taille plus grans 
      cvSetImageROI(DispImage, cvRect(200, 190, 300,300 ));
    }


    else if((imgfelicitaion>=30)&& (imgfelicitaion<40)) {//cette image est de taille plus grans 
     cvSetImageROI(DispImage, cvRect(225, 215, 250,250 ));
    }
    else{ //On affiche l'image numero 1 par rapport a la transition de l'image 
        cvSetImageROI(DispImage, cvRect(250, 240, 200,200 ));
   }
    

    cvResize(img, DispImage);
    cvResetImageROI(DispImage);
    cvReleaseImage(&img);


    

    IplImage *jouer=cvLoadImage("fond04.jpeg"); 
    cvSetImageROI(DispImage, cvRect(490, 320, 150,50 ));
    cvResize(jouer, DispImage);
    cvResetImageROI(DispImage);
    cvReleaseImage(&jouer);


    CvPoint pFond,pQuit;
    pQuit.x=pFond.x=490; 
    pFond.y=350;
    pQuit.y=450; 
   
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 2, 0.5, 0.2, 2, 0.1); 
    cvPutText( DispImage, "Rejouer " , pFond, &font, CV_RGB(255,255,255));


     IplImage *Quitter=cvLoadImage("fond04.jpeg"); 
    cvSetImageROI(DispImage, cvRect(490, 420, 160,50 ));
    cvResize(Quitter, DispImage);
    cvResetImageROI(DispImage);
    cvReleaseImage(&Quitter);


   
   cvPutText( DispImage, "Quitter " , pQuit, &font, CV_RGB(255,255,255));

    if(change(lastX,lastY)==0){

      exit(0); 
    }
    else if(change(lastX,lastY)==1){
      etape=1; 
    }

 
}

// A Simple Camera Capture Framework


int main(){

     //init();  
      CvCapture* capture =0;       
      capture = cvCaptureFromCAM(0);
      if(!capture){
         printf("Capture failure\n");
         return -1;
      }
      
      IplImage* frame=0;
      frame = cvQueryFrame(capture);           
      if(!frame) return -1;
   
     //create a blank image and assigned to 'imgTracking' which has the same size of original video
     imgTracking=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U, 3);
     cvZero(imgTracking); //covert the image, 'imgTracking' to black

     //numero pour afficher permettre a l'image de felicitation de se tabiliser un peu
      int imgfelicitaion=0,intialiser=0;
      //iterate through each frames of the video 

      while(true){


            IplImage* frame = cvQueryFrame(capture);           
            if(!frame) break;
            frame=cvCloneImage(frame); 
            
            cvSmooth(frame, frame, CV_GAUSSIAN,3,3); //smooth the original image using Gaussian kernel

            IplImage* imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3); 
            cvCvtColor(frame, imgHSV, CV_BGR2HSV); //Change the color format from BGR to HSV
            IplImage* imgThresh = GetThresholdedImage(imgHSV);
          
            cvSmooth(imgThresh, imgThresh, CV_GAUSSIAN,3,3); //smooth the binary image using Gaussian kernel
            
           //track the possition of the ball
           trackObject(imgThresh);

            // Add the tracking image and the frame
           cvAdd(frame, imgTracking, frame);

          if(etape==0){
            if(intialiser==0){intialiser=1; }
           accueil(frame);
         }
         if(etape==1){
          if(intialiser!=0){intialiser=0; //pour inialiser les tableau
            init(); 
          }
           detect_and_draw(frame);
         }
         if(etape==2){
          if(intialiser==0){intialiser=1;}
          imgfelicitaion++; 
           fin(frame,imgfelicitaion);
           if(imgfelicitaion>40)imgfelicitaion=0; //rendre le comteur a zero 
         }

          cvNamedWindow( "result", 1 );
          cvShowImage( "result", frame);

           //Clean up used images

           cvReleaseImage(&imgHSV);
           cvReleaseImage(&imgThresh);    
           
            cvReleaseImage(&frame);


            // IplImage *dest=cvCloneImage(frame); 
            // cvCopy(frame, dest);
            // cvReleaseImage(&dest); 
     
           //Wait 10mS
            int c = cvWaitKey(10);
            //If 'ESC' is pressed, break the loop
            if((char)c==27 ) break;  
              
      }
         cvReleaseCapture(&capture);  

       cvReleaseImage(&imgTracking);  
      cvDestroyAllWindows() ;   

      return 0;
}


