#ifndef __AIODEVICE_H
#define __AIODEVICE_H

struct aiodevice;
struct aiochannel {
	char *unit;
	struct aiodevice *aiodev;

	int value;
	char *name;
};

struct aiodevice {
	const char *name;
	int (*read)(struct aiochannel *, int *val);
	struct device_d dev;
	struct device_d *hwdev;
	struct aiochannel **channels;
	int num_channels;
	struct list_head list;
};

int aiodevice_register(struct aiodevice *aiodev);

struct aiochannel *aiochannel_get(struct device_d *dev, int index);
struct aiochannel *aiochannel_get_by_name(const char *name);

int aiochannel_get_value(struct aiochannel *aiochan, int *value);
int aiochannel_get_index(struct aiochannel *aiochan);

static inline const char *aiochannel_get_unit(struct aiochannel *aiochan)
{
	return aiochan->unit;
}

extern struct list_head aiodevices;
#define for_each_aiodevice(aiodevice) list_for_each_entry(aiodevice, &aiodevices, list)

#endif