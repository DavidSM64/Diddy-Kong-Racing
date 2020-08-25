if [[ $# == 0 || (($1 != "us_1.0") && ($1 != "us_1.1") && ($1 != "eu_1.0") && ($1 != "eu_1.1") && ($1 != "jp"))]]; then
    echo 'Usage: ./generate_ld.sh <version>'
    echo 'Acceptable versions: us_1.0, us_1.1, eu_1.0, eu_1.1, jp'
    exit 1
fi

python3 ./tools/python/generate_ld.py "$1"
