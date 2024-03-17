for file in ../ply/*.ply; do
	nohup ./pto "$( basename $file )"  > /dev/null 2>&1 &
	tmp=$(basename "$1" .ply)
	nasm -f elf64 $tmp.asm -o $tmp.o
done;
