#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lsprogram.h"
#include "fileinfo.h"
#include "sorting.h"
#include "permissions.h"
#include "utils.h"
#include <pwd.h>
#include <grp.h>

// Hàm chính (main)
int main(int argc, char *argv[])
{
    LsOptions options = {0}; // Khởi tạo tất cả các tùy chọn về 0
    int opt;

    // Phân tích cú pháp các tùy chọn dòng lệnh
    while ((opt = getopt(argc, argv, "AacdefFhiklnqRrSstuw")) != -1)
    {
        switch (opt)
        {
        case 'A':
            options.showAlmostAll = 1; // Hiển thị gần như tất cả các mục (trừ '.' và '..')
            break;
        case 'a':
            options.showAll = 1; // Hiển thị tất cả các mục, bao gồm cả mục ẩn
            break;
        case 'c':
            options.useChangeTime = 1; // Sử dụng thời gian thay đổi để sắp xếp
            options.useAccessTime = 0;
            break;
        case 'd':
            options.listDirectories = 1; // Hiển thị thư mục thay vì nội dung bên trong
            break;
        case 'F':
            options.addTypeIndicators = 1; // Thêm ký hiệu loại tệp vào cuối tên tệp
            break;
        case 'f':
            options.disableSorting = 1; // Vô hiệu hóa sắp xếp, hiển thị theo thứ tự tự nhiên
            break;
        case 'h':
            options.useHumanReadable = 1; // Hiển thị kích thước tệp ở định dạng dễ đọc (KB, MB, GB)
            options.sizeInKilobytes = 0;
            break;
        case 'i':
            options.showInodes = 1; // Hiển thị số inode của tệp
            break;
        case 'k':
            options.sizeInKilobytes = 1; // Hiển thị kích thước tệp theo đơn vị kilobyte
            options.useHumanReadable = 0;
            break;
        case 'l':
            options.useLongFormat = 1; // Hiển thị chi tiết thông tin tệp
            options.useNumericUIDs = 0;
            break;
        case 'n':
            options.useNumericUIDs = 1; // Hiển thị UID và GID dưới dạng số
            options.useLongFormat = 1;
            break;
        case 'q':
            options.showNonPrintable = 1; // Hiển thị các ký tự không in được dưới dạng '?'
            options.useRawOutput = 0;
            break;
        case 'R':
            options.isRecursive = 1; // Liệt kê nội dung của thư mục con một cách đệ quy
            break;
        case 'r':
            options.reverseOrder = 1; // Sắp xếp theo thứ tự ngược
            break;
        case 'S':
            options.sortBySize = 1; // Sắp xếp theo kích thước tệp
            break;
        case 's':
            options.showBlockCount = 1; // Hiển thị số lượng block mà tệp sử dụng
            break;
        case 't':
            options.sortByTime = 1; // Sắp xếp theo thời gian sửa đổi
            break;
        case 'u':
            options.useAccessTime = 1; // Sử dụng thời gian truy cập để sắp xếp
            options.useChangeTime = 0;
            break;
        case 'w':
            options.useRawOutput = 1; // Hiển thị tên tệp thô, không chỉnh sửa
            options.showNonPrintable = 0;
            break;
        default:
            // Nếu người dùng nhập tùy chọn không hợp lệ, in ra thông báo sử dụng
            fprintf(stderr, "Usage: %s [-AacdefFhiklnqRrSstuw] [file...]\n", argv[0]);
            exit(EXIT_FAILURE); // Thoát chương trình với mã lỗi
        }
    }

    // Nếu không có đường dẫn nào được chỉ định, sử dụng thư mục hiện tại
    if (optind >= argc)
    {
        listDirectory(".", &options); // Liệt kê nội dung của thư mục hiện tại
    }
    else
    {
        // Liệt kê nội dung của từng đường dẫn được chỉ định
        for (; optind < argc; optind++)
        {
            char *path = argv[optind];
            listDirectory(path, &options); // Liệt kê nội dung của thư mục path
        }
    }

    return 0; // Chương trình kết thúc thành công
}

