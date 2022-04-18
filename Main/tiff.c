#include<stdio.h>
#pragma pack(1)

struct HEADER 
{
	unsigned char ch1;
	unsigned char ch2;
	unsigned short int version;
	unsigned int ifd_offset;
};


struct TAG_info
{
	unsigned short int tag_id;
	unsigned short int data_type;
	unsigned int data_count;
	unsigned int data_offset;
};
struct read_bin{
	unsigned short int width;
	unsigned short int height;
	unsigned short int end;
};

struct read_rgb{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};


void write_tiff()
{
	FILE *tiff=fopen("tiff.tiff","wb");
	FILE *fp=fopen("TIFF_Intermediate.bin","rb");

	
	if(tiff==NULL)
	{
		printf("Error");
	}
	struct read_bin bin;
	struct read_rgb rgb;
			
	fread(&bin.width,sizeof(unsigned short int),1,fp);
	fread(&bin.height,sizeof(unsigned short int),1,fp);
	
	int pointer=0;
	int i,j,nextifdoffset=0;
	unsigned short int num_tag=12;
	//int x_reso = bin.width/10;
	//int y_reso = bin.height/8;
	
	pointer=158+(bin.height*4);
	
	struct HEADER h={'I','I',42,8};  
	fwrite(&h,sizeof(struct HEADER),1,tiff);                //Writing the header

	fwrite(&num_tag,sizeof(unsigned short int),1,tiff);      //Writing the number of tags(12)
	
	struct TAG_info t1={256,4,1,bin.width};
	struct TAG_info t2={257,4,1,bin.height};
	struct TAG_info t3={258,3,1,8};
	struct TAG_info t4={259,3,1,1};
	struct TAG_info t5={262,3,1,2};
	struct TAG_info t6={273,4,bin.height,158};
	struct TAG_info t7={277,3,1,3};
	struct TAG_info t8={278,3,1,1};
	struct TAG_info t9={279,4,bin.height,pointer};
	struct TAG_info t10={282,5,1,0};
	struct TAG_info t11={283,5,1,0};
	struct TAG_info t12={296,3,1,2};

	fwrite(&t1,sizeof(struct TAG_info),1,tiff);     //Supplying all the 12 neccessary tags
	fwrite(&t2,sizeof(struct TAG_info),1,tiff);
	fwrite(&t3,sizeof(struct TAG_info),1,tiff);
	fwrite(&t4,sizeof(struct TAG_info),1,tiff);
	fwrite(&t5,sizeof(struct TAG_info),1,tiff);
	fwrite(&t6,sizeof(struct TAG_info),1,tiff);
	fwrite(&t7,sizeof(struct TAG_info),1,tiff);
	fwrite(&t8,sizeof(struct TAG_info),1,tiff);
	fwrite(&t9,sizeof(struct TAG_info),1,tiff);
	fwrite(&t10,sizeof(struct TAG_info),1,tiff);
	fwrite(&t11,sizeof(struct TAG_info),1,tiff);
	fwrite(&t12,sizeof(struct TAG_info),1,tiff);
 
	fwrite(&nextifdoffset,4,1,tiff);                 //Extra 4 bytes for nextifdoffset(not needed)

	int stripbytecount=bin.width*3;
	pointer=158+(bin.height*8);
	for(i=0;i<bin.height;i++)               //Writing address of the beginning of each strip(stripOffset tag). We have considered height number of strips.
	{                                    
		fwrite(&pointer,4,1,tiff);
		pointer = pointer + 3*bin.width;
	}
	for(i=0;i<bin.height;i++)               //Writing the value of stripbytecounts tag(Memory each strip will accupy)
	{
		fwrite(&stripbytecount,4,1,tiff);
	}
        
	

	for(i=0;i<bin.height*3*bin.width;i++)
	{
		fread(&rgb,sizeof(struct read_rgb),1,fp);
		fwrite(&rgb,sizeof(struct read_rgb),1,tiff);
		
	}
	return;
}

int main()
{
	write_tiff();
	return 0;
}

