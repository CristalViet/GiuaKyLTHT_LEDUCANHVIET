#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <sys/stat.h>

/*
 * Hàm formatPermissions
 * Chuyển đổi quyền truy cập của tập tin (mode) thành chuỗi đại diện.
 * Chuỗi này bao gồm các ký tự thể hiện quyền đọc, ghi, và thực thi cho chủ sở hữu, nhóm, và người khác.
 */
char *formatPermissions(mode_t mode);

/*
 * Hàm getFileTypeIndicator
 * Trả về ký hiệu đại diện cho loại tập tin dựa trên giá trị mode.
 * Các ký hiệu bao gồm '/' cho thư mục, '@' cho liên kết mềm, '*' cho tập tin thực thi, v.v.
 */
char getFileTypeIndicator(mode_t mode);

#endif // PERMISSIONS_H

