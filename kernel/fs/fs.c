#include "fs.h"

unsigned char fs_memory[BLOCK_SIZE * 1024]; // 512KB filesystem.

// Pointers to the filesystem sections, see (Global variables).
superblock_t *sb;
inode_t *inodes;
unsigned char *data_blocks;
unsigned char *free_inode_bitmap;
unsigned char *free_data_bitmap;

void fs_init() {

    //Init superblock at the start.
    sb = (superblock_t *)fs_memory; 
    sb->magic = FS_MAGIC;

    //Assign the right values.
    sb->total_blocks = 1024;
    sb->inode_blocks = 16;
    sb->data_blocks = 1008;
    
    //Calculate the bitmap pos.
    sb->free_inode_bitmap = sizeof(superblock_t); //Calculate the pos for the inodes.
    sb->free_data_bitmap = sb->free_inode_bitmap + sb->inode_blocks; // Calculate the pos for the data.
    
    //Set up the pointers to the diffrent parts.
    inodes = (inode_t *)(fs_memory + sb->free_inode_bitmap + sb->inode_blocks); //Create inode_t struct with the memory + the offset of the free_inode_bitmap + the location of the blocks.
    data_blocks = fs_memory + BLOCK_SIZE * (sb->free_data_bitmap + sb->data_blocks); //Create data blocks with the size of the mem with the block size and with the offset and the location.
    free_inode_bitmap = fs_memory + sb->free_inode_bitmap; //Make a pointer to the already defined method.
    free_data_bitmap = fs_memory + sb->free_data_bitmap; //Make a pointer to the already defined method.

    //Make memsets to and set every block to 0 (free).
    memset(free_inode_bitmap, 0, sb->inode_blocks);
    memset(free_data_bitmap, 0, sb->data_blocks);
}


// Claude wrote all of these functions for me, I don't know if am ever going to keep all of them. But we'll see.

//=======================================
//       FILE MANAGEMENT FUNCTIONS          
//=======================================


int open(const char *pathname, int flags, mode_t mode) {
  
}

int creat(const char *pathname, mode_t mode) {
  
}

int close(int fd) {

}

ssize_t read(int fd, void *buf, size_t count) {

}

ssize_t write(int fd, const void *buf, size_t count) {

}

off_t lseek(int fd, off_t offset, int whence) {

}

int unlink(const char *pathname) {

}

int remove(const char *pathname) {

}


//=======================================
//         DIRECTORY OPERATIONS
//=======================================


int mkdir(const char *pathname, mode_t mode) {

}

int rmdir(const char *pathname) {

}

DIR *opendir(const char *name) {

}

struct dirent *readdir(DIR *dirp) {

}

int closedir(DIR *dirp) {

}

int chdir(const char *path) {

}

char *getcwd(char *buf, size_t size) {

}


//=======================================
//   FILE INFORMATION AND ATTRIBUTES
//=======================================


int stat(const char *pathname, struct stat *statbuf) {

}

int fstat(int fd, struct stat *statbuf) {

}

int lstat(const char *pathname, struct stat *statbuf) {

}

int chmod(const char *pathname, mode_t mode) {

}

int fchmod(int fd, mode_t mode) {

}

int chown(const char *pathname, uid_t owner, gid_t group) {

}

int fchown(int fd, uid_t owner, gid_t group) {

}

int utime(const char *filename, const struct utimbuf *times) {

}

int utimes(const char *filename, const struct timeval times[2]) {

}


//=======================================
//       FILE SYSTEM OPERATIONS
//======================================= 


int mount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data) {

}

int umount(const char *target) {

}

void sync(void) {

}

int fsync(int fd) {

}

int truncate(const char *path, off_t length) {

}

int ftruncate(int fd, off_t length) {

}

//=======================================
//   FILE INFORMATION AND ATTRIBUTES
//=======================================


int link(const char *oldpath, const char *newpath) {

}

int symlink(const char *target, const char *linkpath) {

}

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz) {

}

int rename(const char *oldpath, const char *newpath) {

}

int dup(int oldfd) {

}

int dup2(int oldfd, int newfd) {

}


//=======================================
//             I/O CONTROL
//=======================================


int ioctl(int fd, unsigned long request, ...) {

}

int fcntl(int fd, int cmd, ...) {

}
