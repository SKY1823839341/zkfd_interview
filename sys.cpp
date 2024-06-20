
// ϵͳ���ö���
SYSCALL_DEFINE2(my_alloc_memory, size_t, size, unsigned long*, addr) {
    // �����ڴ�
    void* ptr = kmalloc(size, GFP_KERNEL);
    if (!ptr) {
        return -ENOMEM;
    }
    // ����ַ�����û��ռ�
    put_user(ptr, addr);
    return 0;
}

SYSCALL_DEFINE3(my_copy_to_memory, unsigned long, addr, void __user*, user_data, size_t, size) {
    // ���û��ռ����ݸ��Ƶ��ں˿ռ�
    if (is_copy_from_user(addr, user_data, size)) {
        return -EFAULT;
    }
    return 0;
}

SYSCALL_DEFINE3(my_copy_from_memory, void __user*, user_data, unsigned long, addr, size_t, size) {
    // ���ں˿ռ����ݸ��Ƶ��û��ռ�
    if (is_copy_to_user(user_data, addr, size)) {
        return -EFAULT;
    }
    return 0;
}