/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BL2_SIZE   14*1024  /* default size = 14336*/

int main (int argc, char *argv[])
{
	FILE		*fp;
	unsigned char	src;
	char		*Buf, *a;
	int		BufLen;
	int		nbytes, fileLen;
	unsigned int	checksum = 0;
	int		i;

	/*if (argc != 4)*/
    if (argc != 3 && argc != 4)
	{
		printf("Usage: mkbl1 <source file> <destination file> [<size>] \n size = default is 14336. \n");
		return -1;
	}

 	BufLen =  argc == 3 ? BL2_SIZE : atoi(argv[3]); /*设定14336作为BufLen默认值命令行可以忽略该参数*/
    printf("argc  = %d. \n",argc);
    printf("bl2 file  = %s. \n",argv[1]);
    printf("BL2 size = %d. \n",BufLen);
	Buf = (char *)malloc(BufLen);
	memset(Buf, 0x00, BufLen);

	fp = fopen(argv[1], "rb");
	if( fp == NULL)
	{
		printf("source file open error\n");
		free(Buf);
		return -1;
	}

	fseek(fp, 0L, SEEK_END);
	fileLen = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

    printf("file len = %d. \n",fileLen);
/*
	if ( BufLen > fileLen )
	{
		printf("Usage: unsupported size\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	nbytes = fread(Buf, 1, BufLen, fp);*/
    nbytes = fread(Buf, 1, BufLen > fileLen ? fileLen : BufLen, fp); /*根据文件大小和Buf大小确定要读取的文件长度*/

	/*if ( nbytes != BufLen )*/
    if ( nbytes <= 0)
	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	fclose(fp);
    /*始终根据BufLen-4进行校验和计算,默认为BL2_SIZE - 4*/
	/*for(i = 0;i < (14 * 1024) - 4;i++)*/
    for(i = 0;i < BufLen - 4;i++)
	{
		checksum += (unsigned char)(Buf[i]);
	}
	*(unsigned int*)(Buf+i) = checksum; /*将校验和写入BufLen-4的地方*/

	fp = fopen(argv[2], "wb");
	if (fp == NULL)
	{
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}

	a	= Buf;
	nbytes	= fwrite( a, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	free(Buf);
	fclose(fp);

	return 0;
}
