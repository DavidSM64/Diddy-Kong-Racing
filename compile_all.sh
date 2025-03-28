#!/bin/bash

# do us v77 last as that will make it easier to keep decompiling with the default version
regions=('pal' 'jpn' 'us' 'pal' 'us')
versions=('v77' 'v79' 'v80' 'v80' 'v77')

for i in ${!regions[@]}; do
    region=${regions[$i]}
    version=${versions[$i]}
    echo "Compiling $region.$version"
    make REGION=$region VERSION=$version cleanextract && make REGION=$region VERSION=$version -j12
    if [[ $(sha1sum -c --quiet ver/verification/dkr.$region.$version.sha1) = "" ]]; then echo "$region.$version OK"; else echo "Failed $region.$version"; exit 1; fi
done
