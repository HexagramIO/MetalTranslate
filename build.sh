mkdir -p build
cd build
#cmake .. -DWITH_MKL=OFF -DOPENMP_RUNTIME=NONE -DWITH_DNNL=ON -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/icu4c
cmake .. -DWITH_MKL=OFF -DOPENMP_RUNTIME=NONE -DWITH_ACCELERATE=ON -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/icu4c
make