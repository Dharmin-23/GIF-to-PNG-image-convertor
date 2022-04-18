#include<stdio.h>
#include<stdlib.h>
struct read_bin{
	unsigned short width;
	unsigned short height;
	unsigned short int end;
};
struct read_rgb{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
int main()
{
	FILE *fp=fopen("forconvertion_file.bin","rb");
	struct read_bin bin;
	struct read_rgb rgb;
	int i,j,k;
	fread(&bin.width,sizeof(unsigned short),1,fp);
	fread(&bin.height,sizeof(unsigned short),1,fp);
	//unsigned char red[bin.height][bin.width];
	//unsigned char green[bin.height][bin.width];
	//unsigned char blue[bin.height][bin.width];

	printf("Width=%d\n",bin.width);                                                                    printf("Height=%d\n",bin.height);

	for(i=0;i<10;i++)
	{
		fread(&rgb,sizeof(struct read_rgb),1,fp);
		//fread(&green[i][j],sizeof(unsigned char),1,fp);
		//fread(&blue[i][j],sizeof(unsigned char),1,fp);
			
		printf("rgb=%d ",rgb.r);
	}
	
	fread(&bin.end,sizeof(unsigned short int),1,fp);
	printf("%d",bin.end);
	fclose(fp);

	return 0;
}

	
