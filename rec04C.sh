#/bin/sh/
echo Enter a number between 1 and 10:
read num
while [ $num != "7" ]
do
    echo Sorry, you are not correct. Try again!
    echo Enter a number between 1 and 10:
    read num
done
    echo Congratulations, the number is $num.
