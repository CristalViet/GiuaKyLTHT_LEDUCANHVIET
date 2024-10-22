#include <stdlib.h>
#include <sys/stat.h>
#include "permissions.h"

/*
 * Hàm formatPermissions
 * Chuyển đổi mode của tệp thành chuỗi đại diện cho quyền truy cập (permissions)
 * dựa trên giá trị của mode_t (mô tả quyền truy cập của tệp/thư mục).
 * Trả về chuỗi chứa 10 ký tự mô tả quyền và kiểu tệp.
 */
char *formatPermissions(mode_t mode)
{
    // Cấp phát bộ nhớ cho chuỗi chứa quyền truy cập
    char *permissions = malloc(11);
    if (!permissions)
        return NULL; // Kiểm tra lỗi cấp phát bộ nhớ

    /*
     * Xác định kiểu tệp và gán ký tự đầu tiên của chuỗi 'permissions' 
     * dựa trên kiểu của tệp (tệp thường, thư mục, liên kết mềm, v.v.).
     */
    if (S_ISREG(mode))
        permissions[0] = '-'; // Tệp thường
    else if (S_ISDIR(mode))
        permissions[0] = 'd'; // Thư mục
    else if (S_ISLNK(mode))
        permissions[0] = 'l'; // Liên kết mềm
    else if (S_ISBLK(mode))
        permissions[0] = 'b'; // Thiết bị khối
    else if (S_ISCHR(mode))
        permissions[0] = 'c'; // Thiết bị ký tự
    else if (S_ISFIFO(mode))
        permissions[0] = 'p'; // FIFO (named pipe)
    else if (S_ISSOCK(mode))
        permissions[0] = 's'; // Socket
    else
        permissions[0] = '?'; // Kiểu tệp không xác định

    /*
     * Thiết lập các quyền truy cập cho người dùng (USR), nhóm (GRP) và người khác (OTH).
     * Các ký tự tương ứng là r (read), w (write), và x (execute).
     * Nếu quyền thực thi (execute) liên quan đến SUID/SGID hoặc Sticky bit,
     * sẽ hiển thị ký tự 's', 'S', 't', hoặc 'T'.
     */
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_ISUID) ? ((mode & S_IXUSR) ? 's' : 'S') : ((mode & S_IXUSR) ? 'x' : '-');
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_ISGID) ? ((mode & S_IXGRP) ? 's' : 'S') : ((mode & S_IXGRP) ? 'x' : '-');
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & 01000) ? ((mode & S_IXOTH) ? 't' : 'T') : ((mode & S_IXOTH) ? 'x' : '-');
    permissions[10] = '\0'; // Ký tự kết thúc chuỗi

    return permissions; // Trả về chuỗi quyền truy cập đã được định dạng
}

/*
 * Hàm getFileTypeIndicator
 * Xác định ký tự biểu thị loại tệp (ví dụ: '/', '@', '|', '=' hoặc '*')
 * dựa trên quyền truy cập của tệp hoặc thư mục.
 */
char getFileTypeIndicator(mode_t mode)
{
    // Nếu là thư mục, trả về ký tự '/'
    if (S_ISDIR(mode))
        return '/';
    
    // Nếu là liên kết mềm, trả về ký tự '@'
    if (S_ISLNK(mode))
        return '@';
    
    // Nếu là FIFO, trả về ký tự '|'
    if (S_ISFIFO(mode))
        return '|';
    
    // Nếu là socket, trả về ký tự '='
    if (S_ISSOCK(mode))
        return '=';

    // Nếu có quyền thực thi cho người dùng, trả về ký tự '*'
    if (mode & S_IXUSR)
        return '*';

    // Mặc định trả về ký tự khoảng trắng (không có ký tự đặc biệt nào)
    return ' ';
}

