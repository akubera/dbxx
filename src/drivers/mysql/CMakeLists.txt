#
# src/drivers/mysql/CMakeLists.txt
#

find_package (MySQL REQUIRED)

# TODO : check version and add correct subdirectory

add_subdirectory (v5_5)
