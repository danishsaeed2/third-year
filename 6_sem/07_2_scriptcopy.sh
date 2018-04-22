rm -rf ./Old
rm -rf ./New

mkdir ./Old
mkdir ./New

datecomplete=0

for arg in "$@"
do
	if [[ $datecomplete -eq 0 ]]
	then
		datevar=$(date -d $1 +%Y%m%d)
		let datecomplete=${datecomplete}+1
		echo $datevar
	else
		echo $arg
		
		find "$arg" -type d -exec mkdir -p ./Old{} \;
		find "$arg" -type f ! -newermt $datevar -exec cp -p -R {} ./Old/{} \;

		find "$arg" -type d -exec mkdir -p ./New{} \;
		find "$arg" -type f -newermt $datevar -exec cp -p -R {} ./New/{} \;
	fi
done