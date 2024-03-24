
int _lseek(int fd, int offset, int whence)
{
    (void)fd;
    (void)offset;
    (void)whence;
    return -1;
}

int _close(int fd)
{
    (void)fd;
    return -1;
}

int _write(int fd, char *buf, int count)
{
    (void)fd;
    (void)buf;
    (void)count;
    return -1;
}

int _read(int fd, char *buf, int count)
{
    (void)fd;
    (void)buf;
    (void)count;
    return -1;
}
