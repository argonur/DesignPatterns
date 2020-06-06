#!/bin/bash

# get path to script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
pushd $DIR

if [ -d "build" ]; then
    echo "Delete build folder."
    rm -r build
fi

mkdir -p build/Release

pushd ./build
echo "Generate with cmake and build with ninja:"
cmake \
-B ./Release/ \
-DPROJECT_ROOT:PATH=$(pwd)/.. \
-DCMAKE_BUILD_TYPE:STRING=Release \
..
popd > /dev/null

pushd ./build/Release

generationResult=-1

cmake --build . 

if [ $? -eq 0 ]
then
    echo "Generation finished successfully."
    generationResult=0
else
    echo "Generation failed."
    generationResult=1
fi

popd > /dev/null
popd > /dev/null

exit $generationResult
