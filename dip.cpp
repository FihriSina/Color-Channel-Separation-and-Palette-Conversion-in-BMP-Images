#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#pragma pack(1)
typedef unsigned char BYTE;//1 bytes of memory
typedef unsigned short WORD;//2 bytes of memory
typedef unsigned int DWORD;//4 bytes of memory
typedef int LONG;//4 bytes of memory
typedef struct _BMPFH//takes 14 bytes of memory
{
	BYTE bftype1;//1 byte and must be 'B'
	BYTE bftype2;//1 byte and must be 'M'
	DWORD bfsize;//4 bytes gives us the all size of bmp file (including headers,palette (if it has) data)
	WORD bfreserved1;// 2 btyes of memory could be set as 0
	WORD bfreserved2;// 2 btyes of memory could be set as 0
	DWORD bfOffbits;//4 bytes of memeory gives the position of data starts in the bmp file
} BMPFH;
typedef struct _BMPIH//40 bytes for windows bitmap file
{
	DWORD bisize;//4 bytes and it gives the size of info header
	LONG  biw;//4 bytes and it is the width of image
	LONG bih;//4 bytes and it is the height of iimage
	WORD biplane;//2 bytes which is not important for us
	WORD bibitcount;//2 bytes it is about the type of bitmap file if it is 1 2 color, 4 (16 colors) ..
	DWORD biComp;//4 bytes not important
	DWORD bisizeimage;//4 bytes and it gives the size of data in the image 
	LONG bix;//4 bytes not importatnt
	LONG biy;//4 bytes not important
	DWORD biclused;//4 bytes not important
 	DWORD biclimp;//4 byets not importatnt for us
}  BMPIH;
typedef struct _PALET//in palette it describes colors (what is the color number)
{
	BYTE rgbblue;//blue commponent
	BYTE rgbgreen;//green component
	BYTE rgbred;//red component
	BYTE rgbreserved;//reserved byte the user can use this for therir aims
} PALET;
typedef struct _IMAGE
{
	BMPFH   bmpfh;
	BMPIH   bmpih;
	PALET   *palet;
	BYTE    *data;
}  IMAGE;
IMAGE *ImageRead(IMAGE *image,char *filename)
{
	BMPFH bmpfh;
	BMPIH bmpih;
	FILE *fp;
	DWORD r,rowsize,size;
	fp=fopen(filename,"rb");//tries to open the filename
	if(fp==NULL) {printf("File is not found..");exit(1);}
	fread(&bmpfh,sizeof(BMPFH),1,fp);//reads bitmap file header from the file and set to bmph
	if(bmpfh.bftype1!='B' || bmpfh.bftype2!='M')
	{
		printf("This is not a bitmap file.");
		exit(1);
	}
    fread(&bmpih,sizeof(BMPIH),1,fp);//reads bitmap info header from the file and set to bmpih
	image=(IMAGE *) malloc(bmpfh.bfsize);//allocates memory for image
	if(image==NULL) {printf("There is no enough memory for this operation");exit(1);}
	image->bmpfh=bmpfh;//sets bmpfh to image 
	image->bmpih=bmpih;//sets bmpih to image
	
	r=0;//r is set to 0 in case 24 bits per pixel or more (this kind of images does not have color palette)
    if(bmpih.bibitcount==1) r=2;//if the image 1 bit per pixel (the number of clor is 2)
	if(bmpih.bibitcount==4) r=16;//if the image 4 bits per pixel (the number of clor is 16)
	if(bmpih.bibitcount==8) r=256;////if the image 8 bits per pixel (the number of clor is 256)
	if(r!=0)
	{
		image->palet=(PALET *) malloc(4*r);//allocate memory for color palette
		fread(image->palet,sizeof(BYTE),4*r,fp);//read color palette from image to the memory
	}
	rowsize=(image->bmpih.biw*image->bmpih.bibitcount+31)/32*4;//calculates 1 row of image size 
	size=rowsize*image->bmpih.bih;//all size of image is calculated and set to size 
	image->data=(BYTE *)malloc(size);//allocates enough memory for iamage data
	fread(image->data,size,1,fp);//reads image data from file and sets to image->data
	fclose(fp); //closes the file
	return image;//returns the adress of image on the memory
}       
void ImageWrite(IMAGE *image,char *filename)
{
	FILE *fp;
	int r,rowsize,size;
	
	fp=fopen(filename,"wb");//opens the file );exit(1);}
	if(fp==NULL) {printf("Fie opening error!");exit(1);}
	fwrite(&image->bmpfh,sizeof(BMPFH),1,fp);//writes the bitmap file header to the file
	fwrite(&image->bmpih,sizeof(BMPIH),1,fp);//writes he bitmep info header to the file		
	r=0;
    if(image->bmpih.bibitcount==1) r=2;//if the image has 2 colors
	if(image->bmpih.bibitcount==4) r=16;//if the image has 16 colors
	if(image->bmpih.bibitcount==8) r=256;//if the image has 256 colors
	if(r!=0) fwrite(image->palet,4*r,1,fp);//if the image has color palette the palette is written to the file
	rowsize=(image->bmpih.biw*image->bmpih.bibitcount+31)/32*4;//a row size of image is calculated 
	size=rowsize*image->bmpih.bih;//all size of image is calculated
	fwrite(image->data,size,1,fp);//write image data to the file
	fclose(fp);//closes the file 
}
void writeInfo(IMAGE *image,char *fname)
{
	printf("--------Info about %s  image file\n",fname);
	printf("bfType value		:%c%c\n",image->bmpfh.bftype1,image->bmpfh.bftype2);
	printf("bfsize			:%d\n",image->bmpfh.bfsize);
	printf("bfreserved1		:%d\n",image->bmpfh.bfreserved1);
	printf("bfreserved2		:%d\n",image->bmpfh.bfreserved2);
	printf("bfOffbits		:%d\n",image->bmpfh.bfOffbits);
	printf("bisize			:%d\n",image->bmpih.bisize);
	printf("Width			:%d\n",image->bmpih.biw);
	printf("Height			:%d\n",image->bmpih.bih);
	printf("biplane			:%d\n",image->bmpih.biplane);
	printf("bibitcount		:%d\n",image->bmpih.bibitcount);
	printf("Compression		:%d\n",image->bmpih.biComp);
	printf("bisizeimage		:%d\n",image->bmpih.bisizeimage);
	printf("bix			:%d\n",image->bmpih.bix);
	printf("biy			:%d\n",image->bmpih.biy);
	printf("bi color used		:%d\n",image->bmpih.biclused);
	printf("bi color imp.		:%d\n",image->bmpih.biclimp);
}

// ------------------------------------------------------
// AÞAMALAR:

/* 1. input.bmp adlý 24-bit BMP dosyasý belleðe yüklendi.
    - ImageRead() fonksiyonu kullanýlarak BMP baþlýklarý ve piksel verileri okundu.
    - Dosyanýn 24-bit olup olmadýðý kontrol edildi.*/

/* 2. Kýrmýzý kanal (red8.bmp) çýkarýldý:
/   - Her pikselin kýrmýzý (R) deðeri alýndý.
    - Bu deðerler 8-bit gri seviye gibi iþlendi ama palet sadece kýrmýzý tonlarýnda tanýmlandý.
    - red8.bmp adýyla kaydedildi.*/

/* 3. Yeþil kanal (green8.bmp) çýkarýldý:
    - Her pikselin yeþil (G) deðeri alýndý.
    - Palet sadece yeþil tonlarýndan oluþacak þekilde ayarlandý.
    - green8.bmp dosyasý olarak kaydedildi.*/

/* 4. Mavi kanal (blue8.bmp) çýkarýldý:
    - Her pikselin mavi (B) deðeri alýndý.
    - Palet sadece mavi tonlarýndan oluþturuldu.
    - blue8.bmp adýyla kaydedildi.*/

/* 5. Tüm dosyalar standart BMP formatýna uygun olarak kaydedildi.
    - 8-bit BMP formatýnda paletli dosyalar üretildi.
    - Her dosyada palet (renk tablosu) yalnýzca tek renk tonlarýný içeriyor.*/

// Bu iþlemlerle görüntünün RGB kanallarý baþarýyla ayrýldý.
// ------------------------------------------------------

int main() {
    IMAGE *image = NULL;
    image = ImageRead(image, "input.bmp");

    if (image->bmpih.bibitcount != 24) {
        printf("Yalnizca 24 bit BMP dosyalari destekleniyor.\n");
        exit(1);
    }

    writeInfo(image, "input.bmp");
    printf("-----------------------------------------KIRMIZI-----------------------------------------------\n");
    // Kýrmýzý Kanal 
    IMAGE *redImage = (IMAGE*)malloc(sizeof(IMAGE));
    memcpy(&redImage->bmpfh, &image->bmpfh, sizeof(BMPFH));
    memcpy(&redImage->bmpih, &image->bmpih, sizeof(BMPIH));

    redImage->bmpih.bibitcount = 8;

    int genislik = image->bmpih.biw;
    int yukseklik = image->bmpih.bih;
    int satirBoyut24 = ((genislik * 3 + 3) / 4) * 4; 
    int satirBoyut8 = ((genislik + 3) / 4) * 4;      
    int dataSize8 = satirBoyut8 * yukseklik;

    redImage->bmpfh.bfOffbits = sizeof(BMPFH) + sizeof(BMPIH) + 256 * sizeof(PALET);
    redImage->bmpfh.bfsize = redImage->bmpfh.bfOffbits + dataSize8;
    redImage->bmpih.bisizeimage = dataSize8;

    redImage->data = (BYTE*)malloc(dataSize8);
    redImage->palet = (PALET*)malloc(256 * sizeof(PALET));

    for (int i = 0; i < 256; i++) {
        redImage->palet[i].rgbred = i;
        redImage->palet[i].rgbgreen = 0;
        redImage->palet[i].rgbblue = 0;
        redImage->palet[i].rgbreserved = 0;
    }

    for (int y = 0; y < yukseklik; y++) {
        for (int x = 0; x < genislik; x++) {
            int index24 = y * satirBoyut24 + x * 3;
            BYTE red = image->data[index24 + 2]; 
            int index8 = y * satirBoyut8 + x;
            redImage->data[index8] = red;
        }
    }

    printf("-----------------------------------------YESIL-------------------------------------------------\n");

    ImageWrite(redImage, "red8.bmp");
	
	// Yeþil Kanal
    IMAGE *greenImage = (IMAGE*)malloc(sizeof(IMAGE));
    memcpy(&greenImage->bmpfh, &image->bmpfh, sizeof(BMPFH));
    memcpy(&greenImage->bmpih, &image->bmpih, sizeof(BMPIH));

    greenImage->bmpih.bibitcount = 8;
    greenImage->bmpfh.bfOffbits = sizeof(BMPFH) + sizeof(BMPIH) + 256 * sizeof(PALET);
    greenImage->bmpfh.bfsize = greenImage->bmpfh.bfOffbits + dataSize8;
    greenImage->bmpih.bisizeimage = dataSize8;

    greenImage->data = (BYTE*)malloc(dataSize8);
    greenImage->palet = (PALET*)malloc(256 * sizeof(PALET));

    for (int i = 0; i < 256; i++) {
        greenImage->palet[i].rgbred = 0;
        greenImage->palet[i].rgbgreen = i;
        greenImage->palet[i].rgbblue = 0;
        greenImage->palet[i].rgbreserved = 0;
    }

    for (int y = 0; y < yukseklik; y++) {
        for (int x = 0; x < genislik; x++) {
            int index24 = y * satirBoyut24 + x * 3;
            BYTE green = image->data[index24 + 1]; 
            int index8 = y * satirBoyut8 + x;
            greenImage->data[index8] = green;
        }
    }

    ImageWrite(greenImage, "green8.bmp");

    printf("-----------------------------------------MAVI--------------------------------------------------\n");
	// Mavi Kanal
    IMAGE *blueImage = (IMAGE*)malloc(sizeof(IMAGE));
    memcpy(&blueImage->bmpfh, &image->bmpfh, sizeof(BMPFH));
    memcpy(&blueImage->bmpih, &image->bmpih, sizeof(BMPIH));

    blueImage->bmpih.bibitcount = 8;
    blueImage->bmpfh.bfOffbits = sizeof(BMPFH) + sizeof(BMPIH) + 256 * sizeof(PALET);
    blueImage->bmpfh.bfsize = blueImage->bmpfh.bfOffbits + dataSize8;
    blueImage->bmpih.bisizeimage = dataSize8;

    blueImage->data = (BYTE*)malloc(dataSize8);
    blueImage->palet = (PALET*)malloc(256 * sizeof(PALET));


    for (int i = 0; i < 256; i++) {
        blueImage->palet[i].rgbred = 0;
        blueImage->palet[i].rgbgreen = 0;
        blueImage->palet[i].rgbblue = i;
        blueImage->palet[i].rgbreserved = 0;
    }

    for (int y = 0; y < yukseklik; y++) {
        for (int x = 0; x < genislik; x++) {
            int index24 = y * satirBoyut24 + x * 3;
            BYTE blue = image->data[index24 + 0];
            int index8 = y * satirBoyut8 + x;
            blueImage->data[index8] = blue;
        }
    }

    ImageWrite(blueImage, "blue8.bmp");

    return 0; 

}


