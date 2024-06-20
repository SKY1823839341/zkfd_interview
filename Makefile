# �����ں�Դ������/lib/modules/build
KDIR := /lib/modules/build

# �������ͱ�־
CC := gcc
CROSS_COMPILE :=
KBUILD_EXTRA_SYMBOLS :=

# �ں�ģ����� ��־
ifneq ($(KERNELRELEASE),)
obj-m := my_module.o
else
# �����ⲿMakefile����Ҫ�����ں˹���ϵͳ
all:
    $(MAKE) -C $(KDIR) M=$(PWD) modules $(KBUILD_EXTRA_SYMBOLS)

clean:
    $(MAKE) -C $(KDIR) M=$(PWD) clean

# �û��ռ�������
a.out: my_program.c
    $(CC) $< -o $@

endif

# Ĭ��Ŀ���Ǳ����ں�ģ����û��ռ����
default: all a.out

# ���
.PHONY: clean
clean:
    $(MAKE) -C $(KDIR) M=$(PWD) clean
    rm -f a.out
