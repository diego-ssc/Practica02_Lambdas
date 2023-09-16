# Sistema Zoológico

El siguiente programa implementa una base de datos en archivos .csv para la
administración de un zoológico.

## Instalación
Ejecutar:

```
meson setup -Dbuildtype=release build
```
en el directorio raíz.

Y:

```
meson compile -C build/
```
para compilar el programa.

## Uso:
```
./build/sistema-zoologico
```

## Dependencias

### [Meson](https://mesonbuild.com/)
```
meson
Version: 1.2.1
```
### [Doxygen](https://www.doxygen.nl/)
Para generar documentación dentro de la carpeta Docs
```
doxygen Doxyfile
```
