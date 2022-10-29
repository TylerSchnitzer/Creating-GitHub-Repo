#Tyler Schnitzer CSCE 3600.002 Feb 25. 2022
#
#!/bin/bash

ctrl-c()#This is the fuction that is called from Crtl C
{
	echo "(SIGINT) received"
	echo "Terminate Program? (Y/N)"
	read signal #this reads in the user input to put through an if statment
	if [ "$signal" = "Y" ]||[ "$signal" = "y" ];
	then
		exit 1 #if the statment is true it exits the script
	else
		echo "Continuing Execution"
		echo " "
		return #if it is false then it continues the script
	fi
}

getData(){ #this is a getData fuction to display the output
	lst=($1);
	date +%c #this is to display the date, time, day, and zone
	echo -e "UserID\tCount"
	for i in "${lst[@]}"; #The for loop is to get through all the arugments made by the user
	do
		cnt=$(ps aux|grep -v grep|awk '{print$1}'|grep ${i}|wc -l)
		echo -e "$i\t$cnt"
		total=$(($total+$cnt))
	done
	echo "$usrTotal USERS, TOTAL PROCESSES $total"
}
users=("$@")
if [ $# -eq 0 ];#this checks to see if there any following arugments made the user
then
	users=$(ps aux|awk '{print$1}'|sort -u|egrep -v "USER|\-"|tr -s '\n''')
	usrTotal=$(ps aux|awk '{print$1}'|sort -u|egrep -v "USER|\-"|wc -l) 
else
	users=("$@")
	usrTotal=${#users[@]}
fi

while true #This is an infinite loop 
do
	printf"\n"
	date
	getData "${users[*]}"; #this calls a function to display 
	sleep 5 #the loop will reset every 5 sec
	trap "ctrl-c" 2
done


