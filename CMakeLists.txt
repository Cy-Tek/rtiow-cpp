cmake_minimum_required(VERSION 3.26)
project(rtiow_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -flto -ffast-math")

add_executable(rtiow_cpp main.cpp
        Vec3.h
        Image.h
        Ray.h
        Hittable.h
        Sphere.h
        HittableList.h
        Common.h
        Interval.h
        Camera.h
        Material.cpp)
