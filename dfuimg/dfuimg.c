#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define FILE_NAME_MAX 512

uint32_t flip_bytes (uint32_t num)
{
    uint32_t b0,b1,b2,b3;
    uint32_t res;

    b0 = (num & 0x000000ff) << 24u;
    b1 = (num & 0x0000ff00) << 8u;
    b2 = (num & 0x00ff0000) >> 8u;
    b3 = (num & 0xff000000) >> 24u;

    res = b0 | b1 | b2 | b3;

    return res;
}


uint32_t file_size (char *fname)
{
    struct stat *buf = malloc(sizeof(struct stat));
    
    stat(fname, buf);
    uint32_t size = buf->st_size;
    
    free(buf);

    return size;
}

void print_help ()
{
    printf ("--input-file <in-file>\n");
    printf ("--output-file <out-file>\n");
}

int main (int argc, char** argv)
{

    char fi [FILE_NAME_MAX];
    char fo [FILE_NAME_MAX];

    memset (fi, 0x0, FILE_NAME_MAX);
    memset (fo, 0x0, FILE_NAME_MAX);    
    
    int getopt_ret, option_index;
    static struct option long_options[] =
	{
	    {"input-file",  required_argument, 0, 'i'},
	    {"output-file",  required_argument, 0, 'o'},
	    {"help",  optional_argument, 0, 'h'},
	    {0, 0, 0, 0}
	};


    
    while (1)
    {
        getopt_ret = getopt_long( argc, argv, "hi:o:",
                                  long_options,  &option_index);
	
        if (getopt_ret == -1) break;
	
        switch(getopt_ret)
        {
	case 0:
	    break;
	case 'i':
	    strncpy (fi, optarg, FILE_NAME_MAX - 1);
	    break;
	case 'o':
		strncpy (fo, optarg, FILE_NAME_MAX - 1);
	    break;
	case 'h':
	    break;
        }
    }     

    if (0 == strlen (fi))
    {
	print_help ();	
	return 0;
    }
    
    printf("input file: '%s'\n", fi);

    if (0 == strlen(fo))
	snprintf (fo, FILE_NAME_MAX - 1, "%s.img", fi);

    printf("output file: '%s'\n", fo);

    uint32_t fi_size = file_size (fi);
    
    printf("'%s' size:%" PRIu32 " bytes\n", fi, fi_size);

    
    uint32_t le_size = flip_bytes (fi_size);


    printf("'%s' size:%" PRIX32 " bytes\n", fi, fi_size);

    printf("'%s' little endian size:%" PRIX32 " \n", fi, le_size);



    FILE *fdi = fopen(fi, "r");
    FILE *fdo = fopen(fo, "w");
    
    if(!fdi || !fdo)
    {
	printf ("error opening files");
	return -2;
    }


    size_t l1;
    unsigned char buffer[8192];
    uint8_t sz_buf [4];
    
    sz_buf[0] = (le_size & 0xff000000) >> 24;
    sz_buf[1] = (le_size & 0x00ff0000) >> 16;    
    sz_buf[2] = (le_size & 0x0000ff00) >> 8;
    sz_buf[3] = (le_size & 0x000000ff);
    
    fwrite(&sz_buf[0], 4, sizeof (uint8_t), fdo);
    
    //Data to be read
    while((l1 = fread(buffer, 1, sizeof buffer, fdi)) > 0)
    {
	size_t l2 = fwrite(buffer, 1, l1, fdo);

	/*
	if(l2 < l1)
	{
	    if(ferror(fdo))
		// handle error
	    else
		// Handle media full
	}
	*/
    }

    
    fclose(fdi);
    fclose(fdo);    
    
    return 0;
}
