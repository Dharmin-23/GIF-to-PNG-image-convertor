#include<stdio.h>
#include<stdlib.h>

struct BMP_header
{
	char name[2];
	unsigned int size;
	int g;
	unsigned int image_offset;
};

struct DIB_header{
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned short int cplanes;
	unsigned int compression;
	unsigned int image_size;
};

struct RGB_data{
	unsigned char blue;
	unsigned char red;
	unsigned char green;
}

struct Image{
	int height;
	int width;
	struct RGB **rgb;
};

	
void g(FILE *FP,int height,int width)
{
	
	struct bmp_header header;
}

void openbmpfile(){
	FILE *fp=fopen("pic.bmp","rb");
	struct BMP_header header;
	struct DIB_header dibheader;
	fread(&header.name,2,1,fp);
	fread(&header.size,3*sizeof(int),1,fp);
	fread(&dibheader,sizeof(struct DIB_header),1,fp);

	fseek

