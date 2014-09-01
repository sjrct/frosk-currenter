//
// include/kernel/device.h
//

#ifndef _DEVICE_H_
#define _DEVICE_H_

typedef struct device device_t;
typedef struct interface interface_t;

#include <stddef.h>

struct interface {
	// These functions should be called through their respective dev_* functions
	// declared below. Note that these are ignored when NULL (enable/disable
	// return 1, read/write/grab/append return 0).
	int (* enable )(device_t * dev);
	int (* disable)(device_t * dev);
	size_t (* read  )(device_t * dev, void * buf, size_t cnt, size_t at);
	size_t (* write )(device_t * dev, void * buf, size_t cnt, size_t at);
	size_t (* grab  )(device_t * dev, void * buf, size_t cnt);
	size_t (* append)(device_t * dev, void * buf, size_t cnt);
};

struct device {
	// The interface the device uses
	interface_t * interface;

	// The smallest unit (in bytes) that can be written or read
	size_t granularity;

	// The number of units (w/ repsect to granularity) that exist
	size_t count;

	// Device-defined data
	void * local;
};

// Functions for enabling and disabling the device
int dev_enable (device_t *);
int dev_disable(device_t *);

// These two functions perform arbitrary offset data access
// They return the amount (relative to granularity) of data read or written
// The 'cnt' and 'at' parameters are relative to granularity
size_t dev_read (device_t * dev, void * buf, size_t cnt, size_t at);
size_t dev_write(device_t * dev, void * buf, size_t cnt, size_t at);

// These functions perform stream-style data access
// See dev_read/dev_write for return value/parameter information
size_t dev_grab  (device_t * dev, void * buf, size_t cnt);
size_t dev_append(device_t * dev, void * buf, size_t cnt);

#endif

