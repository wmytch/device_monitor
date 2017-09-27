#!/bin/sh  
 
##echo user nice system idle iowait irq softirq  
CPULOG_1=$(cat /proc/stat | grep 'cpu1' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}')  
SYS_IDLE_1=$(echo $CPULOG_1 | awk '{print $4}')  
Total_1=$(echo $CPULOG_1 | awk '{print $1+$2+$3+$4+$5+$6+$7}')  
 
sleep 5  
 
CPULOG_2=$(cat /proc/stat | grep 'cpu1' | awk '{print $2" "$3" "$4" "$5" "$6" "$7" "$8}')  
SYS_IDLE_2=$(echo $CPULOG_2 | awk '{print $4}')  
Total_2=$(echo $CPULOG_2 | awk '{print $1+$2+$3+$4+$5+$6+$7}')  
 
SYS_IDLE=`expr $SYS_IDLE_2 - $SYS_IDLE_1` 
#echo $SYS_IDLE
 
Total=`expr $Total_2 - $Total_1`
#echo $Total  

echo $SYS_IDLE $Total | awk '{printf("\"cpu0utili\":\"%.2f%\"\n", 100-$1/$2*100)}'
 

