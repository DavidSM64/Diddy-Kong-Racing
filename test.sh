#{
a=0
# Rename asm files that use the old name and replace it with a new one.
filenames=$(grep -rl "$1" asm/**/*/"$1".s)
echo $filenames
echo if [[ $filenames =~ "No such file or directory" ]]; then
  a=1
fi
#} &> /dev/null
echo $a