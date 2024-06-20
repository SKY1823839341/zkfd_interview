#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

// �����ϵͳ���ú�351,352
#define __NR_write_file_to_kernel 351
#define __NR_read_kernel_to_file 352


// ����ϵͳ����
int main(int argc, char* argv[]) {
    if(argc < 3) {
            fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
            exit(EXIT_FAILURE);
     }

        // ����һ���㹻��Ļ�����
     char kernel_buffer[4096]; // ʵ��Ӧ�ø����ļ���С��̬����

        // ����ϵͳ���ý��ļ�д���ں��ڴ�
     long ret = syscall(__NR_write_file_to_kernel, argv[1], kernel_buffer, sizeof(kernel_buffer));
     if (ret < 0) {
         perror("write_file_to_kernel");
         exit(EXIT_FAILURE);
      }

        // ����ϵͳ���ô��ں��ڴ��ȡ���ļ�
     ret = syscall(__NR_read_kernel_to_file, argv[2], kernel_buffer, sizeof(kernel_buffer));
     if (ret < 0) {
         perror("read_kernel_to_file");
         exit(EXIT_FAILURE);
        }

     return 0;
        
 }
