
// 系统调用定义
SYSCALL_DEFINE2(my_alloc_memory, size_t, size, unsigned long*, addr) {
    // 分配内存
    void* ptr = kmalloc(size, GFP_KERNEL);
    if (!ptr) {
        return -ENOMEM;
    }
    // 将地址传回用户空间
    put_user(ptr, addr);
    return 0;
}

SYSCALL_DEFINE3(my_copy_to_memory, unsigned long, addr, void __user*, user_data, size_t, size) {
    // 将用户空间数据复制到内核空间
    if (is_copy_from_user(addr, user_data, size)) {
        return -EFAULT;
    }
    return 0;
}

SYSCALL_DEFINE3(my_copy_from_memory, void __user*, user_data, unsigned long, addr, size_t, size) {
    // 将内核空间数据复制到用户空间
    if (is_copy_to_user(user_data, addr, size)) {
        return -EFAULT;
    }
    return 0;
}