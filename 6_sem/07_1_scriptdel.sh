rm -rf ./Old
rm -rf ./New

mkdir ./Old
mkdir ./New

datecomplete=0

for arg in "$@"
do
	if [[ $datecomplete -eq 0 ]]
	then
		datevar=$(date -d $arg +%Y%m%d)
		let datecomplete=${datecomplete}+1
		echo $datevar
	else
		echo $arg
		cp -R -p "$arg" ./Old
		cp -R -p "$arg" ./New
	fi
done
find ./New -type f ! -newermt $datevar -delete
find ./Old -type f -newermt $datevar -delete