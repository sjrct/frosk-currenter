//
// kernel/src/device/device.c
//

#include "device.h"

// The below functions simply wrap to the respective interface functions
int dev_enable(device_t * dev) {
	if (!dev->interface->enable) {
		return dev->interface->enable(dev);
	}
	return 1;
}

int dev_disable(device_t * dev) {
	if (!dev->interface->disable) {
		return dev->interface->disable(dev);
	}
	return 1;
}

size_t dev_read(device_t * dev, void * buf, size_t cnt, size_t at) {
	if (!dev->interface->read) {
		return dev->interface->read(dev, buf, cnt, at);
	}
	return 0;
}

size_t dev_write(device_t * dev, void * buf, size_t cnt, size_t at) {
	if (!dev->interface->write) {
		return dev->interface->write(dev, buf, cnt, at);
	}
	return 0;
}

size_t dev_grab(device_t * dev, void * buf, size_t cnt) {
	if (!dev->interface->grab) {
		return dev->interface->grab(dev, buf, cnt);
	}
	return 0;
}

size_t dev_append(device_t * dev, void * buf, size_t cnt) {
	if (!dev->interface->append) {
		return dev->interface->append(dev, buf, cnt);
	}
	return 0;
}

