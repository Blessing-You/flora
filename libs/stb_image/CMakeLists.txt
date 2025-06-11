add_library(stb_image STATIC stb_image.c stb_image_resize2.c)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_LIST_DIR})