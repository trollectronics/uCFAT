#ifndef FAT_H_
#define FAT_H_

#include <stdint.h>
#include <stdbool.h>
#include <posix-file.h>

typedef enum FATType FATType;
enum FATType {
	FAT_TYPE_FAT16,
	FAT_TYPE_FAT32,
};

struct FATDirList {
	char		filename[13];
	uint8_t		attrib;
	uint8_t		padding[2];
} __attribute__((packed));

int fat_init(int (* read_sector_call)(uint32_t sector, uint8_t *data), int (* write_sector_call)(uint32_t sector, uint8_t *data), uint8_t *buffer);
void fat_close(int fd);
int fat_open(const char *path, int flags);
uint32_t fat_fsize(int fd);
uint32_t fat_ftell(int fd);
bool fat_seek(int fd, uint32_t pos);
bool fat_read_sect(int fd);
bool fat_write_sect(int fd);
bool fat_delete_file(const char *path);
bool fat_create_file(char *path, char *name, uint8_t attrib);
uint8_t fat_get_stat(const char *path);
void fat_set_stat(const char *path, uint8_t stat);
void fat_set_fsize(const char *path, uint32_t size);
int fat_dirlist(const char *path, struct FATDirList *list, int size, int skip);
bool fat_valid();
FATType fat_type();
int fat_get_label(char *buf);

/* These should be provided by you */
/* Returns < 0 on error */
//int write_sector_call(uint32_t sector, uint8_t *data);
//int read_sector_call(uint32_t sector, uint8_t *data);


#endif
