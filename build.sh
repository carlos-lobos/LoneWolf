#!/bin/bash

set -e  # detener si ocurre un error

# INI :: Re-build del proyecto
BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
cd .. >/dev/null 2>&1
# FIN :: Re-build del proyecto


# Aseguramos la existencia de un enlace simbólico al binario lonewolf creado por cmake en la carpeta build/
test ! -L lonewolf && ln -s build/lonewolf .


# INI :: Ejecutar tests de lonwolf
echo -e "\n[INI] Ejecutando todos los tests de lonwolf...\n"

# Navegar a la carpeta de tests
TESTS_DIR="tests"
if [ ! -d "$TESTS_DIR" ]; then
    mkdir $TESTS_DIR 2>/dev/null
fi

# Ejecutar todos los archivos de prueba que terminen en .sh
cd $TESTS_DIR
for test_script in *.lw; do
  if [ -f "$test_script" ] ; then
    echo "Ejecutando $test_script ..."
    ./../lonewolf "$test_script"
  fi
done

echo -e "\n[END] Todos los tests han sido ejecutados.\n"
# FIN :: Ejecutar tests de lonwolf
