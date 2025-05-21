   cmake_minimum_required(VERSION 3.10)
   project(Assignment)

   set(CMAKE_CXX_STANDARD 11)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)

   find_package(OpenGL REQUIRED)
   find_package(GLEW REQUIRED)
   find_package(glfw3 REQUIRED)
   find_package(assimp REQUIRED)

   include_directories(
       ${OPENGL_INCLUDE_DIRS}
       ${GLEW_INCLUDE_DIRS}
       ${GLFW_INCLUDE_DIRS}
       ${GLM_INCLUDE_DIRS} 
       ${CMAKE_CURRENT_SOURCE_DIR}/../..
       ${CMAKE_CURRENT_SOURCE_DIR}/external
       ${ASSIMP_INCLUDE_DIRS}
   )

   add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

   add_executable(Assignment
       main.cpp
       Camera.cpp
       EBO.cpp
       Mesh.cpp
       Model.cpp
       Shader.cpp
       Texture.cpp
       VAO.cpp
       VBO.cpp
       assimp.cpp
       stb.cpp
          )


   target_link_libraries(Assignment
       ${OPENGL_LIBRARIES}
       GLEW::GLEW
       glfw
       assimp
   )

   file(COPY
       ${CMAKE_CURRENT_SOURCE_DIR}/vertexShader.glsl
       ${CMAKE_CURRENT_SOURCE_DIR}/fragmentShader.glsl
       ${CMAKE_CURRENT_SOURCE_DIR}/Models
       ${CMAKE_CURRENT_SOURCE_DIR}/Textures
       ${CMAKE_CURRENT_SOURCE_DIR}/external
       DESTINATION
       ${CMAKE_CURRENT_BINARY_DIR}
   )


   target_include_directories(Assignment PRIVATE
       ${CMAKE_CURRENT_SOURCE_DIR}
   )

