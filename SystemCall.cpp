#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

// 假设的系统调用号351,352
#define __NR_write_file_to_kernel 351
#define __NR_read_kernel_to_file 352


// 调用系统调用
int main(int argc, char* argv[]) {
    if(argc < 3) {
            fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
            exit(EXIT_FAILURE);
     }

        // 分配一个足够大的缓冲区
     char kernel_buffer[4096]; // 实际应该根据文件大小动态分配

        // 调用系统调用将文件写入内核内存
     long ret = syscall(__NR_write_file_to_kernel, argv[1], kernel_buffer, sizeof(kernel_buffer));
     if (ret < 0) {
         perror("write_file_to_kernel");
         exit(EXIT_FAILURE);
      }

        // 调用系统调用从内核内存读取到文件
     ret = syscall(__NR_read_kernel_to_file, argv[2], kernel_buffer, sizeof(kernel_buffer));
     if (ret < 0) {
         perror("read_kernel_to_file");
         exit(EXIT_FAILURE);
        }

     return 0;
        
 }
