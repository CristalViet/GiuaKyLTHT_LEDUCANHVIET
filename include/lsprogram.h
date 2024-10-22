#ifndef LSPROGRAM_H
#define LSPROGRAM_H

/*
 * Cấu trúc LsOptions
 * Lưu trữ các tùy chọn để điều chỉnh hành vi của chương trình ls.
 * Mỗi trường đại diện cho một tùy chọn cụ thể khi thực hiện liệt kê tệp tin và thư mục.
 */
typedef struct
{
    int showAll;              // Hiển thị tất cả các tập tin, bao gồm cả tập tin ẩn.
    int showAlmostAll;        // Hiển thị tất cả ngoại trừ '.' và '..'.
    int useChangeTime;        // Sử dụng thời gian thay đổi tập tin để sắp xếp.
    int listDirectories;      // Liệt kê thư mục thay vì nội dung bên trong.
    int addTypeIndicators;    // Thêm ký hiệu loại tập tin (ví dụ: '/' cho thư mục).
    int disableSorting;       // Vô hiệu hóa việc sắp xếp.
    int useHumanReadable;     // Hiển thị kích thước tập tin dưới dạng dễ đọc (KB, MB...).
    int showInodes;           // Hiển thị số inode của các tập tin.
    int sizeInKilobytes;      // Hiển thị kích thước tập tin tính theo kilobyte.
    int useLongFormat;        // Hiển thị dưới định dạng chi tiết (bao gồm quyền truy cập, kích thước,...).
    int useNumericUIDs;       // Hiển thị UID và GID dưới dạng số thay vì tên.
    int showNonPrintable;     // Hiển thị các ký tự không in được dưới dạng '?'
    int isRecursive;          // Liệt kê nội dung thư mục một cách đệ quy.
    int reverseOrder;         // Đảo ngược thứ tự sắp xếp.
    int sortBySize;           // Sắp xếp theo kích thước tập tin.
    int showBlockCount;       // Hiển thị số block được sử dụng bởi tập tin.
    int sortByTime;           // Sắp xếp theo thời gian (mặc định là thời gian sửa đổi).
    int useAccessTime;        // Sử dụng thời gian truy cập để sắp xếp.
    int useRawOutput;         // Hiển thị tên tệp mà không có bất kỳ ký tự không in được nào.
} LsOptions;

#endif // LSPROGRAM_H

