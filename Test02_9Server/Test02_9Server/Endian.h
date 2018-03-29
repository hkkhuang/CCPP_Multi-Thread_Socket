
#ifndef _ENDIAN_H
#define _ENDIAN_H

/* Endian.h 
    ��С�����ֽ�����֮���ת������

���ߣ��۷�
������http://afanihao.cn
��C/C++ѧϰָ�ϡ�ϵ�н̳� - ����Դ��

�汾: 2015-07-01 (���°汾�뵽��������)
���̵̳�Դ��������ʹ�ã����뱣������˵�����֣�лл��
*/

/////////////// big-endian functions ////////////

// int -> bytes, 32bits , big-endidan
inline void itob_32be(unsigned int a, unsigned char bytes[])
{
	bytes[0] = (unsigned char) ( a >> 24 );
	bytes[1] = (unsigned char) ( a >> 16 );
	bytes[2] = (unsigned char) ( a >> 8 );
	bytes[3] = (unsigned char) ( a );
}

// int -> bytes, 32bits , big-endidan
inline unsigned int btoi_32be(unsigned char bytes[])
{
	unsigned int a = 0;
	a += ( bytes[0] << 24 );
	a += ( bytes[1] << 16 );
	a += ( bytes[2] << 8 );
	a += ( bytes[3]  );
	return a;
}

// short -> bytes, 16bits , big-endidan
inline void itob_16be(unsigned short a, unsigned char bytes[])
{
	bytes[0] = (unsigned char) ( a >> 8 );
	bytes[1] = (unsigned char) ( a );
}

// short -> bytes, 16bits , big-endidan
inline unsigned short btoi_16be(unsigned char bytes[])
{
	unsigned short a = 0;
	a += ( bytes[0] << 8 );
	a += ( bytes[1]  );
	return a;
}



/////////////// little-endian functions ////////////

// int -> bytes, 32bits , little-endidan
inline void itob_32le(unsigned int a, unsigned char bytes[])
{
	bytes[0] = (unsigned char) ( a  );
	bytes[1] = (unsigned char) ( a >> 8 );
	bytes[2] = (unsigned char) ( a >> 16 );
	bytes[3] = (unsigned char) ( a >> 24);
}

// int -> bytes, 32bits , little-endidan
inline unsigned int btoi_32le(unsigned char bytes[])
{
	unsigned int a = 0;
	a += ( bytes[0]  );
	a += ( bytes[1] << 8 );
	a += ( bytes[2] << 16 );
	a += ( bytes[3] << 24 );
	return a;
}

// short -> bytes, 16bits , little-endidan
inline void itob_16le(unsigned short a, unsigned char bytes[])
{
	bytes[1] = (unsigned char) ( a  );
	bytes[0] = (unsigned char) ( a >> 8 );
}

// short -> bytes, 16bits , little-endidan
inline unsigned short btoi_16le(unsigned char bytes[])
{
	unsigned short a = 0;
	a += ( bytes[1]  );
	a += ( bytes[0] << 8 );
	return a;
}



#endif
