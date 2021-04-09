extern int r_dup(int oldfd, int newfd);

int dup(int oldfd) { return r_dup(oldfd, -1); }