#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <ctype.h>
#include "fileinfo.h"
#include "permissions.h"  // Thêm tệp khai báo hàm formatPermissions và getFileTypeIndicator
#include "sorting.h"
#include "utils.h"

// Hàm in thông tin chi tiết về tệp
void printFileInfo(const char *path, const char *name, const struct stat *fileStat, const LsOptions *options)
{
    // Nếu sử dụng option -i: hiển thị số inode
    if (options->showInodes)
        printf("%lu ", (unsigned long)fileStat->st_ino);

    // Nếu sử dụng option -s: hiển thị số block
    if (options->showBlockCount)
        printf("%lld ", (long long)(fileStat->st_blocks / 2));

    // Nếu sử dụng option -l: định dạng thông tin chi tiết
    if (options->useLongFormat)
    {
        // Lấy quyền truy cập và in ra
        char *permissions = formatPermissions(fileStat->st_mode); // Gọi hàm formatPermissions
        printf("%s ", permissions);
        free(permissions);

        // Hiển thị số lượng liên kết cứng
        printf("%3lu ", (unsigned long)fileStat->st_nlink);

        // Hiển thị thông tin người dùng và nhóm
        if (options->useNumericUIDs)
        {
            printf("%d %d ", fileStat->st_uid, fileStat->st_gid);
        }
        else
        {
            struct passwd *pw = getpwuid(fileStat->st_uid);
            struct group *gr = getgrgid(fileStat->st_gid);
            printf("%-8s %-8s ", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");
        }

        // Hiển thị kích thước tệp
        if (options->useHumanReadable)
            printf("%s ", formatHumanReadableSize(fileStat->st_size));
        else if (options->sizeInKilobytes)
            printf("%6lld ", (long long)fileStat->st_size / 1024);
        else
            printf("%8lld ", (long long)fileStat->st_size);

        // Hiển thị thời gian tệp được truy cập/sửa đổi
        time_t fileTime = options->useAccessTime ? fileStat->st_atime : options->useChangeTime ? fileStat->st_ctime : fileStat->st_mtime;
        char timeStr[26];
        strftime(timeStr, sizeof(timeStr), "%b %d %H:%M", localtime(&fileTime));
        printf("%s ", timeStr);
    }

    // Nếu sử dụng output thô (raw), in tên tệp trực tiếp
    if (options->useRawOutput)
    {
        printf("%s", name);
    }
    else
    {
        // In từng ký tự của tên tệp, kiểm tra các ký tự không in được
        for (const char *p = name; *p; p++)
        {
            if (options->showNonPrintable && !isprint(*p))
            {
                putchar('?');
            }
            else
            {
                putchar(*p);
            }
        }
    }

    // Thêm ký hiệu loại tệp (nếu được yêu cầu)
    if (options->addTypeIndicators)
        printf("%c", getFileTypeIndicator(fileStat->st_mode)); // Gọi hàm getFileTypeIndicator

    printf("\n");
}

// Hàm liệt kê các mục trong thư mục
void listDirectory(const char *path, const LsOptions *options) {
    DIR *dirStream;
    struct dirent *entry;
    struct stat fileStat;
    char fullPath[PATH_MAX];

    // Mở thư mục
    if ((dirStream = opendir(path)) == NULL) {
        perror("opendir failed");
        return;
    }

    // Đọc từng mục trong thư mục
    while ((entry = readdir(dirStream)) != NULL) {
        // Tạo đường dẫn đầy đủ của tệp/thư mục
        snprintf(fullPath, PATH_MAX, "%s/%s", path, entry->d_name);
        
        // Lấy thông tin về tệp/thư mục
        if (lstat(fullPath, &fileStat) == -1) {
            perror("lstat failed");
            continue;
        }

        // Gọi hàm printFileInfo để in thông tin của tệp/thư mục
        printFileInfo(path, entry->d_name, &fileStat, options);
    }

    // Đóng thư mục
    closedir(dirStream);
}

