CPULoadAvg()
{
	avgOneMinute=`cat /proc/loadavg | awk {'print $1'}`
	
	avgFiveMinute=`cat /proc/loadavg | awk {'print $2'}`
	
	avgFifteenMinute=`cat /proc/loadavg | awk {'print $3'}`
	
	
	
	
	echo $avgOneMinute $avgFiveMinute $avgFifteenMinute | awk '{printf("{\"CPULoadAvg\":[{\"avgOneMinute\":%s},{\"avgFiveMinute\":%s},{\"avgFifteenMinute\":%s}]}", $1, $2, $3)}'
}

StorageUtili()
{
	
	used=`df | awk {'print $3'} | awk 'NR>1' | awk 'BEGIN{sum=0}{sum+=$1}END{print sum}'`
    #echo "used: $used"
	total=`df | awk {'print $2'} | awk 'NR>1' | awk 'BEGIN{sum=0}{sum+=$1}END{print sum}'`
	#echo "total: $total"
	
	Utili=`awk 'BEGIN{printf "%.2f%\n",('$used'/'$total')*100}'`
	
	echo $Utili | awk '{printf("{\"StorageUtili\":\"%.2f%\"}", $1)}'

}

KernelVersion()
{
	kernelVersion=`uname -r`
	echo $kernelVersion | awk '{printf("{\"KernelVersion\":\"%s\"}", $1)}'
}
CPULoadAvg
StorageUtili
KernelVersion

