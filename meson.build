project('sistema-zoologico', 'c',
        version : '0.1')

add_global_arguments('-O3',
                     language : 'c') #-g

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)
thread_dep = dependency('threads')

src = [
  'SRC/main.c',
  'SRC/administrador.c',
  'SRC/veterinario.c',
  'SRC/animal.c',
  'SRC/bioma.c'
]

includes = include_directories('SRC/')

TSP_SA = static_library('sistema-zoologico', src,
                        dependencies: [ m_dep, thread_dep ],
                        include_directories: [ includes ],
                        install : true)

exe = executable('sistema-zoologico', src,
                 dependencies: [  m_dep, thread_dep ],
                 install : true)
