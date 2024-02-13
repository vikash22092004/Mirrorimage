#include <stdio.h>

int main()
{
	FILE *fp = fopen("lena512_endsem.bmp","rb");					
	FILE *fo = fopen("lena_rotate.bmp","wb");	
		    	
	int i,j;

	unsigned char byte[54],colorTable[1024];
	
	if(fp==NULL)											
	{											
		printf("File does not exist.\n");
	}

	for(i=0;i<54;i++)										
	{									
		byte[i] = getc(fp);								
	}

	fwrite(byte,sizeof(unsigned char),54,fo);				
 
	int height = *(int*)&byte[18];
	int width = *(int*)&byte[22];
	int bitDepth = *(int*)&byte[28];

    printf("Image dimensions are\n");
	printf("Width: %d\n",width);
	printf("Height: %d\n",height );

	int size = height*width;								

	if(bitDepth <= 8)										
	{
		fread(colorTable,sizeof(unsigned char),1024,fp);
		fwrite(colorTable,sizeof(unsigned char),1024,fo);
	}

	unsigned char image[width][height];					
	unsigned char out_image[width][height];

	fread(image,sizeof(unsigned char),size,fp);			


			for(i=0;i<width;i++)								
			{
				for(j=0;j<height;j++)
				{
					out_image[width-i][j]=image[i][j];
				}
			}
	
	fwrite(out_image,sizeof(unsigned char),size,fo);		

	fclose(fp);
	fclose(fo);

	return 0;
}
