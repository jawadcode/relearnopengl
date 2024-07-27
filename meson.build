project(
  'relearnopengl',
  'cpp',
  default_options: ['cpp_std=c++20', 'warning_level=3']
)

sources = ['src/main.cpp', 'src/logger.cpp', 'src/window.cpp']

fmt = dependency('fmt', version: '10.2.1')
glbinding = dependency('glbinding', version: '3.3.0')
glfw = dependency('glfw3', version: '3.4')
khr = dependency('khrplatform', version: 'cci.20200529')
stb = dependency('stb', version: 'cci.20240213')

executable(
  'relearnopengl',
  sources,
  dependencies: [fmt, glbinding, glfw, khr, stb],
  native: true,
)
