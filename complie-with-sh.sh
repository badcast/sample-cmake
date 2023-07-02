#!/usr/bin/sh

script_dir=$(dirname $(readlink -f $0))
build_dir="$script_dir/build"
obj_dir="$build_dir/objects"

src_lib="$script_dir/sample_lib"
src_exe="$script_dir/sample_bin"
include="$script_dir/include"

nl_static="libsample_lib-static.a"
nl_shared="libsample_lib-shared.so"
ex_static="exec-sample-static"
ex_shared="exec-sample-shared"
arr_files=("$nl_static" "$nl_shared" "$ex_static" "$ex_shared")
arr_length=${#arr_files[@]}

mkdir -p "$obj_dir"

cd $build_dir

#compile lib
g++ -O2 -DNDEBUG -I $include "$src_lib/sample_library.cpp" -c -fPIC -o  "$obj_dir/sample_lib.o" &&

#create static lib
ar rcs libsample_lib-static.a "$obj_dir/sample_lib.o" &&

#create shared lib
g++ -O2 -DNDEBUG -shared "$obj_dir/sample_lib.o" -o libsample_lib-shared.so &&

#compiling object exec
g++ -O2 -DNDEBUG -I $include $src_exe/sample_bin.cpp -c -fPIC -o "$obj_dir/sample_bin.o" &&

#create with static-exec
g++ -DNDEBUG "$obj_dir/sample_bin.o" -L. -l sample_lib-static -o $ex_static &&

#create with shared-exec
g++ -DNDEBUG "$obj_dir/sample_bin.o" -L. -l sample_lib-shared -o $ex_shared

#check
if [ ! $? == 0 ]; then
    echo "Compilling error"
    exit $?
else
    echo "Compilling complete"
fi

mkdir -p $build_dir/output

for ((i=0;i<$arr_length;i++)); do
    mv $build_dir/${arr_files[$i]} $build_dir/output
done

echo $compiled_files

#remove caches
#rm -rf "$build_dir"
