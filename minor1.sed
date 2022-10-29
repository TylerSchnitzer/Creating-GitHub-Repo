s/682/800/

s/\((.{3})\)/\1/

s/([[:digit:]]{3}) ([[:digit:]]{3}-[[:digit:]]{4})/\1-\2/

1,12s/-4321/-1234/

13,$s/Lane/Kate/

1,12s/Lane/Ln/

13,$s/([[:digit:]]{3})-([[:digit:]]{3})/\2-\1/

s/\@/\#/
s/;/,/

$s/$/\np.s. you winnings must be claimed by February 29th./