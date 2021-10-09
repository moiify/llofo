/*
 * version.h
 *
 *  Created on: 2018/1/15
 *      Author: lc
 */

#ifndef _USER_VERSION_H_
#define _USER_VERSION_H_

#define VERSION_MAJOR   6
#define VERSION_MINOR   0
#define VERSION_MICRO   6

#define VERSION_INT(a, b, c)    (a << 16 | b << 8 | c)
#define VERSION_DOT(a, b, c)    a##.##b##.##c
#define VERSION(a, b, c)        VERSION_DOT(a, b, c)

#define STRINGIFY(s)         TOSTRING(s)
#define TOSTRING(s) #s

#define VERSION_STR STRINGIFY(VERSION(VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO))

#define VERSION_NUM VERSION_INT(VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO)

#endif /* _USER_VERSION_H_ */

