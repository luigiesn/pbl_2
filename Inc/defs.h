#ifndef DEFS_H
#define	DEFS_H

/**
 * @typedef Boolean type
 */
typedef enum{
    false, true
}bool_type;

#define bool bool_type

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef unsigned char byte;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

#endif	/* DEFS_H */
