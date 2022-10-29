# Tyler Schnitzer . CSCE3600.201 . Rec 5 . 02/27/2022
# a bash script that curves five user grades by the user's amount
#!/bin/bash

# function of curving the grades
curve()
{
    incr=$1;
    shift 
    arr=$@;
    index=0;
    for i in "${grades[@]}";
    do
        let grades[$index]=$incr+$i
        index=$index+1;
  
    done
}

if [ "$#" != 1 ]
then
    echo "usage: ./rec05.sh <curve amount>"
else
    declare -a grades
    for i in {1..5}
    do
        read -p "Enter QUIZ #$i:" grades[$i-1]
        
    done
    curve $1 "${grades[@]}"
    
    echo "Curved Grades:"

    for (( i=1 ; i<=5 ; i++ ))
    do
        echo "grades[$i] = ${grades[$i-1]}"
    done
fi