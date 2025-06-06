#ifndef FS_H
#define FS_H

#include "../core/util.h"

#define BLOCK_SIZE 512 
#define MAX_FILES 256
#define MAX_FILENAME_LENGTH
#define FS_MAGIC 0xABCD1234
#define MAX_DATA_BLOCKS 1008

// Superblock Structure
typedef struct {
    u32 magic;           // Magic number to identify filesystem
    u32 total_blocks;    // Total number of blocks
    u32 inode_blocks;    // Number of inode blocks
    u32 data_blocks;     // Number of data blocks
    u32 free_inode_bitmap; // Position of inode bitmap
    u32 free_data_bitmap;  // Position of data bitmap
} superblock_t;

// Inode Structure
typedef struct {
    u32 size;                 // File size
    u32 data_block_indices[12]; // Indices of data blocks
} inode_t;

// Directory Entry Structure
typedef struct {
    char filename[MAX_FILENAME_LENGTH]; // Filename
    u32 inode_index;               // Index of corresponding inode
} dir_entry_t;

// File system init function
void fs_init();

//======================================
//           FILE OPERATIONS
//=======================================

// File Management Functions
int open(const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode);
int close(int fd);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);
int unlink(const char *pathname);
int remove(const char *pathname);

// Directory Operations
int mkdir(const char *pathname, mode_t mode);
int rmdir(const char *pathname);
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
int chdir(const char *path);
char *getcwd(char *buf, size_t size);

// File Information and Attributes
int stat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int utime(const char *filename, const struct utimbuf *times);
int utimes(const char *filename, const struct timeval times[2]);

// File System Operations
int mount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data);
int umount(const char *target);
void sync(void);
int fsync(int fd);
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);

// Advanced Operations
int link(const char *oldpath, const char *newpath);
int symlink(const char *target, const char *linkpath);
ssize_t readlink(const char *pathname, char *buf, size_t bufsiz);
int rename(const char *oldpath, const char *newpath);
int dup(int oldfd);
int dup2(int oldfd, int newfd);

// I/O Control
int ioctl(int fd, unsigned long request, ...);
int fcntl(int fd, int cmd, ...);

#endif // FS_H
