# 假设内核源码树在/lib/modules/build
KDIR := /lib/modules/build

# 编译器和标志
CC := gcc
CROSS_COMPILE :=
KBUILD_EXTRA_SYMBOLS :=

# 内核模块编译 标志
ifneq ($(KERNELRELEASE),)
obj-m := my_module.o
else
# 否则，外部Makefile，需要调用内核构建系统
all:
    $(MAKE) -C $(KDIR) M=$(PWD) modules $(KBUILD_EXTRA_SYMBOLS)

clean:
    $(MAKE) -C $(KDIR) M=$(PWD) clean

# 用户空间程序编译
a.out: my_program.c
    $(CC) $< -o $@

endif

# 默认目标是编译内核模块和用户空间程序
default: all a.out

# 清除
.PHONY: clean
clean:
    $(MAKE) -C $(KDIR) M=$(PWD) clean
    rm -f a.out
