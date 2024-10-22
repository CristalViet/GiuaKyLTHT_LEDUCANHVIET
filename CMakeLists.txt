# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(lsprogram_project VERSION 1.0)

# Chỉ định thư mục chứa các tệp header
include_directories(include)

# Chỉ định các tệp nguồn
set(SRC_FILES
    src/main.c
    src/fileinfo.c   # Thêm tệp chứa hàm listDirectory
    src/permissions.c
    src/sorting.c
    src/utils.c
)

# Tạo tệp thực thi từ các tệp nguồn
add_executable(a.out ${SRC_FILES})

# Chỉ định tiêu chuẩn C cần sử dụng
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
