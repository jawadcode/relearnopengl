project(
  'relearnopengl',
  'cpp',
  default_options: ['cpp_std=c++20', 'warning_level=3']
)

sources = ['src/main.cpp']

glbinding = dependency('glbinding', version: '3.3.0')
glfw = dependency('glfw3', version: '3.4')
spdlog = dependency('spdlog', version: '1.14.1')

executable(
  'relearnopengl',
  sources,
  dependencies: [glbinding, glfw, spdlog]
)
